#include "yolo_lidar_fusion/yolo_lidar_fusion.h"
#include "yolo_lidar_fusion/utils.h"

void ROSPixelCloudFusionApp::CloudCallback(const sensor_msgs::PointCloud2::ConstPtr &in_cloud_msg)
{
    double start = ros::Time::now().toSec();
    auto input_header = in_cloud_msg->header;
    // Check and retrieve the transform for the left, right, back, and front cameras if not available
    if (!camera_lidar_tf_ok_l_)
    {
        camera_lidar_tf_l_ = FindTransform(image_frame_id_l_, in_cloud_msg->header.frame_id);
        transform_l = transformTFToEigenMatrix(camera_lidar_tf_l_);
    }
    if (!camera_lidar_tf_ok_r_)
    {
        camera_lidar_tf_r_ = FindTransform(image_frame_id_r_, in_cloud_msg->header.frame_id);
        transform_r = transformTFToEigenMatrix(camera_lidar_tf_r_);

    }
    if (!camera_lidar_tf_ok_b_)
    {
        camera_lidar_tf_b_ = FindTransform(image_frame_id_b_, in_cloud_msg->header.frame_id);
        transform_b = transformTFToEigenMatrix(camera_lidar_tf_b_);

    }
    if (!camera_lidar_tf_ok_f_)
    {
        camera_lidar_tf_f_ = FindTransform(image_frame_id_f_, in_cloud_msg->header.frame_id);
        transform_f = transformTFToEigenMatrix(camera_lidar_tf_f_);
    }

    std::cout << "work"  <<std::endl;
    // If either left, right, back, or front camera information or transforms are not available, wait and return
    if (!camera_info_ok_l_ || !camera_lidar_tf_ok_l_ || !camera_info_ok_r_ || !camera_lidar_tf_ok_r_ || 
        !camera_info_ok_b_ || !camera_lidar_tf_ok_b_ || !camera_info_ok_f_ || !camera_lidar_tf_ok_f_)
    {
        ROS_INFO("[%s] Waiting for Camera-Lidar TF and Intrinsics to be available for all cameras.", __APP_NAME__);
        return;
    }
    std::cout << "work1"  <<std::endl;

    // Point cloud containers
    pcl::PointCloud<pcl::PointXYZI>::Ptr intensity(new pcl::PointCloud<pcl::PointXYZI>);
    // pcl::PointCloud<pcl::PointXYZ>::Ptr filtered_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    // pcl::PointCloud<pcl::PointXYZ>::Ptr filtered_cloud2(new pcl::PointCloud<pcl::PointXYZ>);

    // Convert ROS message to PCL point cloud
    // TODO : downsampling,

    pcl::PointCloud<pcl::PointXYZ>::Ptr in_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr ground_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr fused_clustered_cloud(new pcl::PointCloud<pcl::PointXYZ>);

    pcl::fromROSMsg(*in_cloud_msg, *in_cloud);
    pcl::fromROSMsg(*in_cloud_msg, *intensity);
    
    // CropBox 필터 적용
    Eigen::Vector4f min_pt(-2.0, -0.8, -std::numeric_limits<float>::max(), 1.0); // 박스의 최소 좌표
    Eigen::Vector4f max_pt(1.0, 0.8, std::numeric_limits<float>::max(), 1.0);   // 박스의 최대 좌표
    applyCropBoxFilter(in_cloud, in_cloud, min_pt, max_pt, true); // 박스 안의 포인트를 제외

        
    if(use_voxel_filter){
        pcl::VoxelGrid<pcl::PointXYZ> voxel_filter;
        voxel_filter.setInputCloud(in_cloud); // 원래 포인트 클라우드 입력
        voxel_filter.setLeafSize(voxel_size, voxel_size, voxel_size); // 리프 크기 설정 (0.1m로 설정 예시)
        voxel_filter.filter(*in_cloud); 
    }

    // Ground segmentation 적용
    if (use_ground_filter) {
        segmentGround(in_cloud, ground_cloud, in_cloud, num_iterations, distance_threshold, true);
    }
    
    if (pub_filtered_cloud) {
        sensor_msgs::PointCloud2 output_cloud;
        // PCL 포인트 클라우드를 ROS 메시지로 변환
        pcl::toROSMsg(*in_cloud, output_cloud);
        // 메시지에 헤더 추가 (예: 프레임 ID 및 타임스탬프 설정)
        output_cloud.header = input_header;

        // 퍼블리시
        publisher_filtered_cloud_.publish(output_cloud);
    }
    std::cout << "work2"  <<std::endl;

    pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud_l(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud_r(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud_b(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud_f(new pcl::PointCloud<pcl::PointXYZ>);

    pcl::PointCloud<pcl::PointXYZ>::Ptr sliced_cloud_l(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr sliced_cloud_r(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr sliced_cloud_b(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr sliced_cloud_f(new pcl::PointCloud<pcl::PointXYZ>);

    pcl::PointCloud<pcl::PointXYZI>::Ptr sliced_cloud_test(new pcl::PointCloud<pcl::PointXYZI>);
    pcl::PointCloud<pcl::PointXYZI>::Ptr transformed_cloud_test(new pcl::PointCloud<pcl::PointXYZI>);

    pcl::PassThrough<pcl::PointXYZ> pass_b;
    pass_b.setInputCloud(in_cloud);
    pass_b.setFilterFieldName("x");
    pass_b.setFilterLimits(std::numeric_limits<float>::lowest(), -1.0);
    pass_b.filter(*sliced_cloud_b);

    pcl::PassThrough<pcl::PointXYZ> pass_f;
    pass_f.setInputCloud(in_cloud);
    pass_f.setFilterFieldName("x");
    pass_f.setFilterLimits(1.0, std::numeric_limits<float>::max()); 
    pass_f.filter(*sliced_cloud_f);

    pcl::PassThrough<pcl::PointXYZ> pass_l;
    pass_l.setInputCloud(in_cloud);
    pass_l.setFilterFieldName("y");
    pass_l.setFilterLimits(1.0, std::numeric_limits<float>::max()); 
    pass_l.filter(*sliced_cloud_l);

    pcl::PassThrough<pcl::PointXYZ> pass_r;
    pass_r.setInputCloud(in_cloud);
    pass_r.setFilterFieldName("y");
    pass_r.setFilterLimits(std::numeric_limits<float>::lowest(), -1.0);
    pass_r.filter(*sliced_cloud_r);

    pcl::PassThrough<pcl::PointXYZI> pass_test;
    pass_test.setInputCloud(intensity);
    pass_test.setFilterFieldName("y");
    pass_test.setFilterLimits(std::numeric_limits<float>::lowest(), -1.0);
    pass_test.filter(*sliced_cloud_test);

    // // 변환된 행렬을 사용하여 포인트 클라우드 변환
    pcl::transformPointCloud(*sliced_cloud_f, *transformed_cloud_f, transform_f);
    pcl::transformPointCloud(*sliced_cloud_l, *transformed_cloud_l, transform_l);
    pcl::transformPointCloud(*sliced_cloud_r, *transformed_cloud_r, transform_r);
    pcl::transformPointCloud(*sliced_cloud_b, *transformed_cloud_b, transform_b);



    // // Prepare containers for transformed points
    // std::vector<pcl::PointXYZ> transformed_point_l(in_cloud->points.size());
    // std::vector<pcl::PointXYZ> transformed_point_r(in_cloud->points.size());
    // std::vector<pcl::PointXYZ> transformed_point_b(in_cloud->points.size());
    // std::vector<pcl::PointXYZ> transformed_point_f(in_cloud->points.size());
    polygons_2d_l_ = polygons_2d_l;
    polygons_2d_r_ = polygons_2d_r;
    polygons_2d_b_ = polygons_2d_b;
    polygons_2d_f_ = polygons_2d_f;

    // projectLidarToImage(image_msg_, sliced_cloud_test, transform_l, camera_model_l, fx_l_, fy_l_, cx_l_, cy_l_, polygons_2d_l_);
    
    // if(image_msg_) projectLidarToImage(image_msg_, sliced_cloud_test, transform_r, camera_model_r, fx_r_, fy_r_, cx_r_, cy_r_, polygons_2d_r_);
    
    std::cout << "work3"  <<std::endl;

    // std::cout << polygons_2d_b_.size() << std::endl;

    std::vector<pcl::PointCloud<pcl::PointXYZ>> filtered_clouds_l(polygons_2d_l_.size());
    std::vector<pcl::PointCloud<pcl::PointXYZ>> filtered_clouds_f(polygons_2d_f_.size());
    std::vector<pcl::PointCloud<pcl::PointXYZ>> filtered_clouds_b(polygons_2d_b_.size());
    std::vector<pcl::PointCloud<pcl::PointXYZ>> filtered_clouds_r(polygons_2d_r_.size());

    double check1 = ros::Time::now().toSec();

    // Left side
    for (size_t i = 0; i < transformed_cloud_l->points.size(); i++){
        int u_l = int(transformed_cloud_l->points[i].x * fx_l_ / transformed_cloud_l->points[i].z + cx_l_);
        int v_l = int(transformed_cloud_l->points[i].y * fy_l_ / transformed_cloud_l->points[i].z + cy_l_);
        if (u_l >= 0 && u_l < image_size_l_.width && v_l >= 0 && v_l < image_size_l_.height && transformed_cloud_l->points[i].z > 0){
            for (size_t j = 0; j < polygons_2d_l_.size(); j++)
            {
                // if(use_polygon_resize) AdjustPolygonSize(polygons_2d_l_[j],  min_width, min_height, scale_w, scale_h);
                if (IsPointInPolygon(polygons_2d_l_[j], u_l, v_l))
                {
                    filtered_clouds_l[j].points.push_back(sliced_cloud_l->points[i]);  // 각 polygon에 맞는 point 추가
                    // break;
                }
            }
        }
    }

    // Front side
    for (size_t i = 0; i < transformed_cloud_f->points.size(); i++){
        int u_f = int(transformed_cloud_f->points[i].x * fx_f_ / transformed_cloud_f->points[i].z + cx_f_);
        int v_f = int(transformed_cloud_f->points[i].y * fy_f_ / transformed_cloud_f->points[i].z + cy_f_);
        if (u_f >= 0 && u_f < image_size_f_.width && v_f >= 0 && v_f < image_size_f_.height && transformed_cloud_f->points[i].z > 0){
            for (size_t j = 0; j < polygons_2d_f_.size(); j++)
            {
                // if(use_polygon_resize) AdjustPolygonSize(polygons_2d_f_[j],  min_width, min_height, scale_w, scale_h);
                if (IsPointInPolygon(polygons_2d_f_[j], u_f, v_f))
                {
                    filtered_clouds_f[j].points.push_back(sliced_cloud_f->points[i]);  // 각 polygon에 맞는 point 추가
                    // break;
                }
            }
        }
    }

    // Back side
    for (size_t i = 0; i < transformed_cloud_b->points.size(); i++){
        int u_b = int(transformed_cloud_b->points[i].x * fx_b_ / transformed_cloud_b->points[i].z + cx_b_);
        int v_b = int(transformed_cloud_b->points[i].y * fy_b_ / transformed_cloud_b->points[i].z + cy_b_);
        if (u_b >= 0 && u_b < image_size_b_.width && v_b >= 0 && v_b < image_size_b_.height && transformed_cloud_b->points[i].z > 0){
            for (size_t j = 0; j < polygons_2d_b_.size(); j++)
            {
                // if(use_polygon_resize) AdjustPolygonSize(polygons_2d_b_[j],  min_width, min_height, scale_w, scale_h);
                if (IsPointInPolygon(polygons_2d_b_[j], u_b, v_b))
                {
                    filtered_clouds_b[j].points.push_back(sliced_cloud_b->points[i]);  // 각 polygon에 맞는 point 추가
                    // break;
                }
            }
        }
    }

    // Right side
    for (size_t i = 0; i < transformed_cloud_r->points.size(); i++){
        int u_r = int(transformed_cloud_r->points[i].x * fx_r_ / transformed_cloud_r->points[i].z + cx_r_);
        int v_r = int(transformed_cloud_r->points[i].y * fy_r_ / transformed_cloud_r->points[i].z + cy_r_);
        if (u_r >= 0 && u_r < image_size_r_.width && v_r >= 0 && v_r < image_size_r_.height && transformed_cloud_r->points[i].z > 0){
            for (size_t j = 0; j < polygons_2d_r_.size(); j++)
            {
                // if(use_polygon_resize) AdjustPolygonSize(polygons_2d_r_[j],  min_width, min_height, scale_w, scale_h);
                if (IsPointInPolygon(polygons_2d_r_[j], u_r, v_r))
                {
                    filtered_clouds_r[j].points.push_back(sliced_cloud_r->points[i]);  // 각 polygon에 맞는 point 추가
                    // break;
                }
                // std::cout << filtered_clouds_r[j].points.size() <<std::endl;
            }
        }
    }

    std::vector<pcl::PointCloud<pcl::PointXYZ>> combined_filtered_clouds;
    combined_filtered_clouds.reserve(filtered_clouds_l.size() + filtered_clouds_f.size() + filtered_clouds_b.size() + filtered_clouds_r.size());
    combined_filtered_clouds.insert(combined_filtered_clouds.end(), filtered_clouds_l.begin(), filtered_clouds_l.end());
    combined_filtered_clouds.insert(combined_filtered_clouds.end(), filtered_clouds_f.begin(), filtered_clouds_f.end());
    combined_filtered_clouds.insert(combined_filtered_clouds.end(), filtered_clouds_b.begin(), filtered_clouds_b.end());
    combined_filtered_clouds.insert(combined_filtered_clouds.end(), filtered_clouds_r.begin(), filtered_clouds_r.end());

    if(pub_fused_cloud){
        pcl::PointCloud<pcl::PointXYZ>::Ptr fused_cloud(new pcl::PointCloud<pcl::PointXYZ>);

        // combined_filtered_clouds에 있는 모든 포인트 클라우드를 fused_cloud에 추가
        for (const auto& cloud : combined_filtered_clouds) {
            *fused_cloud += cloud;  // += 연산자로 포인트 클라우드 병합
        }
        sensor_msgs::PointCloud2 output_cloud;
        // PCL 포인트 클라우드를 ROS 메시지로 변환
        pcl::toROSMsg(*fused_cloud, output_cloud);
        // 메시지에 헤더 추가 (예: 프레임 ID 및 타임스탬프 설정)
        output_cloud.header = input_header;

        // 퍼블리시
        publisher_fused_cloud_.publish(output_cloud);
    }

    std::vector<typename pcl::PointCloud<pcl::PointXYZ>::Ptr> clusters;
    std::vector<Box> curr_boxes_;


    // Iterate through each filtered cloud
    for (size_t i = 0; i < combined_filtered_clouds.size(); i++){

        const auto& cloud = combined_filtered_clouds[i];
        if (cloud.empty()) {
            // std::cout << "Skipping empty cloud." << std::endl;
            continue; // 다음 클라우드로 넘어감
        }

        std::vector<typename pcl::PointCloud<pcl::PointXYZ>::Ptr> clusters;
        typename pcl::PointCloud<pcl::PointXYZ>::Ptr closest_cluster; // 가장 큰 클러스터를 저장할 포인터
        size_t max_points = 0; // 가장 많은 포인트 수를 저장할 변수

        // Create a KdTree for the current cloud
        typename pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
        tree->setInputCloud(cloud.makeShared());
        std::vector<pcl::PointIndices> cluster_indices;
        pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
        // ec.setClusterTolerance(0.2); // Set your cluster tolerance here
        // ec.setMinClusterSize(10);      // Minimum cluster size
        // ec.setMaxClusterSize(500);     // Maximum cluster size
        ec.setClusterTolerance(cluster_tolerance); // Set your cluster tolerance here
        ec.setMinClusterSize(cluster_min_size);      // Minimum cluster size
        ec.setMaxClusterSize(cluster_max_size);     // Maximum cluster size
        ec.setSearchMethod(tree);
        ec.setInputCloud(cloud.makeShared());
        ec.extract(cluster_indices);



        int min_cluster_index = -1;
        float min_distance = std::numeric_limits<float>::max(); // Variable to store the minimum distance to the origin
        for (size_t  j = 0; j < cluster_indices.size(); ++j) {
            const auto& indices = cluster_indices[j].indices;
            // Compute the average distance from the origin (0,0,0) to the points in the cluster
            float sum_x =0;
            float sum_y =0;
            float sum_z =0;
            for (const auto& index : indices) {
                const auto& point = cloud.points[index];
                sum_x += point.x;
                sum_y += point.y;
                sum_z += point.z;
            }
            float mean_x = sum_x/indices.size();
            float mean_y = sum_y/indices.size();
            float mean_z = sum_z/indices.size();
            float dis = std::sqrt(mean_x * mean_x + mean_y * mean_y + mean_z * mean_z);
            if(min_distance > dis){
                min_cluster_index = j;
                min_distance = dis;
            } 
        }

        if (min_cluster_index >= 0) {
            const auto& closest_indices = cluster_indices[min_cluster_index];
            typename pcl::PointCloud<pcl::PointXYZ>::Ptr closest_cluster(new pcl::PointCloud<pcl::PointXYZ>);

            // 가장 큰 클러스터의 인덱스를 사용하여 포인트 클라우드 생성
            for (const auto& index : closest_indices.indices) {
                closest_cluster->points.push_back(cloud.points[index]);
            }
            if(pub_fused_clustered_cloud)  *fused_clustered_cloud += *closest_cluster;

            Box bbox = axisAlignedBoundingBox(closest_cluster, i);
            curr_boxes_.emplace_back(bbox);
        }
    }

    if(pub_fused_clustered_cloud){

        sensor_msgs::PointCloud2 output_cloud;
        // PCL 포인트 클라우드를 ROS 메시지로 변환
        pcl::toROSMsg(*fused_clustered_cloud, output_cloud);
        // 메시지에 헤더 추가 (예: 프레임 ID 및 타임스탬프 설정)
        output_cloud.header = input_header;

        // 퍼블리시
        publisher_fused_clustered_cloud_.publish(output_cloud);
    }

    // Construct Bounding Boxes from the clusters
    auto bbox_header = in_cloud_msg->header;
    autoware_msgs::DetectedObjectArray autoware_objects;
    autoware_objects.header = bbox_header;

    // Transform boxes from lidar frame to base_link frame, and convert to jsk and
    // autoware msg formats

    for (auto &box : curr_boxes_) {
        geometry_msgs::Pose pose, pose_transformed;
        pose.position.x = box.position(0);
        pose.position.y = box.position(1);
        pose.position.z = box.position(2);
        pose.orientation.w = box.quaternion.w();
        pose.orientation.x = box.quaternion.x();
        pose.orientation.y = box.quaternion.y();
        pose.orientation.z = box.quaternion.z();
        autoware_objects.objects.emplace_back(
            transformAutowareObject(box, bbox_header, pose));
    }

    pub_autoware_objects.publish(std::move(autoware_objects));

    visualization_msgs::MarkerArray marker_array;
    int marker_id = 0;

    for (const auto& box : curr_boxes_) {
        visualization_msgs::Marker marker;
        marker.header = bbox_header;
        marker.ns = "obstacle_markers";
        marker.id = marker_id++;
        marker.type = visualization_msgs::Marker::CUBE;
        marker.action = visualization_msgs::Marker::ADD;

        marker.pose.position.x = box.position(0);
        marker.pose.position.y = box.position(1);
        marker.pose.position.z = box.position(2);
        marker.pose.orientation.w = box.quaternion.w();
        marker.pose.orientation.x = box.quaternion.x();
        marker.pose.orientation.y = box.quaternion.y();
        marker.pose.orientation.z = box.quaternion.z();

        marker.scale.x = box.dimension(0);
        marker.scale.y = box.dimension(1);
        marker.scale.z = box.dimension(2);

        marker.color.a = 1.0;  // Set alpha
        marker.color.r = 0.0;
        marker.color.g = 0.0;  
        marker.color.b = 1.0;
        marker.lifetime = ros::Duration(0.1);  // Marker lifetime
        marker_array.markers.push_back(marker);
    }

    pub_marker_array.publish(marker_array);

    // Update previous bounding boxes
    curr_boxes_.clear();

    double finish = ros::Time::now().toSec();
    std::cout << (finish - start)*1000 << "ms"<<std::endl;

    polygons_2d_l_.clear();
    polygons_2d_r_.clear();
    polygons_2d_b_.clear();
    polygons_2d_f_.clear();
}

void ROSPixelCloudFusionApp::SegmentCallback_l(const visualization_msgs::MarkerArray::ConstPtr &in_marker_msg)
{
    if(!camera_info_ok_l_) return;

    std::vector<std::vector<cv::Point2f>> polygons_2d_l__;
    polygons_2d_l__.clear();  
    std::vector<cv::Point2f> current_polygon;
    float current_index = -1;

    for (const auto& marker : in_marker_msg->markers)
    {
        float point_x = marker.pose.position.x;
        float point_y = marker.pose.position.y;
        float point_z = marker.pose.position.z; 

        if (point_z != current_index)
        {
            if (!current_polygon.empty())
            {
                AdjustPolygonSize(current_polygon,  min_width, min_height, scale_w, scale_h);
                polygons_2d_l__.push_back(current_polygon);  
                current_polygon.clear();
            }
            current_index = point_z;
        }

        current_polygon.push_back(camera_model_l.rectifyPoint(cv::Point2f(point_x, point_y)));
        // current_polygon.push_back(cv::Point2f(point_x, point_y));
    }

    if (!current_polygon.empty())
    {
        AdjustPolygonSize(current_polygon,  min_width, min_height, scale_w, scale_h);
        polygons_2d_l__.push_back(current_polygon);  
    }
    polygons_2d_l = polygons_2d_l__;
}

void ROSPixelCloudFusionApp::SegmentCallback_r(const visualization_msgs::MarkerArray::ConstPtr &in_marker_msg)
{
    if(!camera_info_ok_r_) return;

    std::vector<std::vector<cv::Point2f>> polygons_2d_r__;
    polygons_2d_r__.clear();  
    std::vector<cv::Point2f> current_polygon;
    float current_index = -1;

    for (const auto& marker : in_marker_msg->markers)
    {
        float point_x = marker.pose.position.x;
        float point_y = marker.pose.position.y;
        float point_z = marker.pose.position.z;

        if (point_z != current_index)
        {
            if (!current_polygon.empty())
            {
                AdjustPolygonSize(current_polygon,  min_width, min_height, scale_w, scale_h);
                polygons_2d_r__.push_back(current_polygon); 
                current_polygon.clear();
            }
            current_index = point_z;
        }

        current_polygon.push_back(camera_model_r.rectifyPoint(cv::Point2f(point_x, point_y)));
        // current_polygon.push_back(cv::Point2f(point_x, point_y));

    }

    if (!current_polygon.empty())
    {
        AdjustPolygonSize(current_polygon,  min_width, min_height, scale_w, scale_h);
        polygons_2d_r__.push_back(current_polygon); 
    }
    polygons_2d_r = polygons_2d_r__;
}

void ROSPixelCloudFusionApp::SegmentCallback_b(const visualization_msgs::MarkerArray::ConstPtr &in_marker_msg)
{
    if(!camera_info_ok_b_) return;
    std::vector<std::vector<cv::Point2f>> polygons_2d_b__;
    polygons_2d_b__.clear();
    std::vector<cv::Point2f> current_polygon;
    float current_index = -1;

    for (const auto& marker : in_marker_msg->markers)
    {
        float point_x = marker.pose.position.x;
        float point_y = marker.pose.position.y;
        float point_z = marker.pose.position.z;

        if (point_z != current_index)
        {
            if (!current_polygon.empty())
            {
                AdjustPolygonSize(current_polygon,  min_width, min_height, scale_w, scale_h);
                polygons_2d_b__.push_back(current_polygon);
                current_polygon.clear();
            }
            current_index = point_z;
        }

        current_polygon.push_back(camera_model_b.rectifyPoint(cv::Point2f(point_x, point_y)));
        // current_polygon.push_back(cv::Point2f(point_x, point_y));
    }

    if (!current_polygon.empty())
    {
        AdjustPolygonSize(current_polygon,  min_width, min_height, scale_w, scale_h);
        polygons_2d_b__.push_back(current_polygon);
    }
    polygons_2d_b = polygons_2d_b__;
}

void ROSPixelCloudFusionApp::SegmentCallback_f(const visualization_msgs::MarkerArray::ConstPtr &in_marker_msg)
{
    if(!camera_info_ok_f_) return;
    std::vector<std::vector<cv::Point2f>> polygons_2d_f__;
    polygons_2d_f__.clear();
    std::vector<cv::Point2f> current_polygon;
    float current_index = -1;

    for (const auto& marker : in_marker_msg->markers)
    {
        float point_x = marker.pose.position.x;
        float point_y = marker.pose.position.y;
        float point_z = marker.pose.position.z;

        if (point_z != current_index)
        {
            if (!current_polygon.empty())
            {
                AdjustPolygonSize(current_polygon,  min_width, min_height, scale_w, scale_h);
                polygons_2d_f__.push_back(current_polygon);
                current_polygon.clear();
            }
            current_index = point_z;
        }

        // current_polygon.push_back(cv::Point2f(point_x, point_y));
        current_polygon.push_back(camera_model_f.rectifyPoint(cv::Point2f(point_x, point_y)));
        // current_polygon.push_back(cv::Point2f(point_x, point_y));
    }

    if (!current_polygon.empty())
    {
        AdjustPolygonSize(current_polygon,  min_width, min_height, scale_w, scale_h);
        polygons_2d_f__.push_back(current_polygon);
    }
    polygons_2d_f = polygons_2d_f__;
}

void ROSPixelCloudFusionApp::IntrinsicsCallback_l(const sensor_msgs::CameraInfo &in_message)
{
    camera_model_l.fromCameraInfo(in_message);

    image_size_l_.height = in_message.height;
    image_size_l_.width = in_message.width;
    image_frame_id_l_ = in_message.header.frame_id;

    camera_intrinsics_l_ = cv::Mat(3, 3, CV_64F);
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            camera_intrinsics_l_.at<double>(row, col) = in_message.K[row * 3 + col];
        }
    }

    distortion_coefficients_l_ = cv::Mat(1, 5, CV_64F);
    for (int col = 0; col < 5; col++)
    {
        distortion_coefficients_l_.at<double>(col) = in_message.D[col];
    }

    fx_l_ = static_cast<float>(in_message.P[0]);
    fy_l_ = static_cast<float>(in_message.P[5]);
    cx_l_ = static_cast<float>(in_message.P[2]);
    cy_l_ = static_cast<float>(in_message.P[6]);

    intrinsics_subscriber_l_.shutdown();
    camera_info_ok_l_ = true;
    ROS_INFO("[%s] Left CameraIntrinsics obtained.", __APP_NAME__);
}

void ROSPixelCloudFusionApp::IntrinsicsCallback_r(const sensor_msgs::CameraInfo &in_message)
{
    camera_model_r.fromCameraInfo(in_message);

    image_size_r_.height = in_message.height;
    image_size_r_.width = in_message.width;
    image_frame_id_r_ = in_message.header.frame_id;

    camera_intrinsics_r_ = cv::Mat(3, 3, CV_64F);
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            camera_intrinsics_r_.at<double>(row, col) = in_message.K[row * 3 + col];
        }
    }

    distortion_coefficients_r_ = cv::Mat(1, 5, CV_64F);
    for (int col = 0; col < 5; col++)
    {
        distortion_coefficients_r_.at<double>(col) = in_message.D[col];
    }

    fx_r_ = static_cast<float>(in_message.P[0]);
    fy_r_ = static_cast<float>(in_message.P[5]);
    cx_r_ = static_cast<float>(in_message.P[2]);
    cy_r_ = static_cast<float>(in_message.P[6]);

    intrinsics_subscriber_r_.shutdown();
    camera_info_ok_r_ = true;
    ROS_INFO("[%s] Right CameraIntrinsics obtained.", __APP_NAME__);
}

void ROSPixelCloudFusionApp::IntrinsicsCallback_b(const sensor_msgs::CameraInfo &in_message)
{
    camera_model_b.fromCameraInfo(in_message);
    image_size_b_.height = in_message.height;
    image_size_b_.width = in_message.width;
    // std::cout <<"image_size_b_.height" << std::endl;

    // std::cout <<image_size_b_.height << std::endl;
    // std::cout <<image_size_b_.width << std::endl;
    image_frame_id_b_ = in_message.header.frame_id;
    std::cout << image_frame_id_b_ << std::endl;

    camera_intrinsics_b_ = cv::Mat(3, 3, CV_64F);
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            camera_intrinsics_b_.at<double>(row, col) = in_message.K[row * 3 + col];
        }
    }

    distortion_coefficients_b_ = cv::Mat(1, 5, CV_64F);
    for (int col = 0; col < 5; col++)
    {
        distortion_coefficients_b_.at<double>(col) = in_message.D[col];
    }

    fx_b_ = static_cast<float>(in_message.P[0]);
    fy_b_ = static_cast<float>(in_message.P[5]);
    cx_b_ = static_cast<float>(in_message.P[2]);
    cy_b_ = static_cast<float>(in_message.P[6]);

    intrinsics_subscriber_b_.shutdown();
    camera_info_ok_b_ = true;
    ROS_INFO("[%s] Back CameraIntrinsics obtained.", __APP_NAME__);
}

void ROSPixelCloudFusionApp::IntrinsicsCallback_f(const sensor_msgs::CameraInfo &in_message)
{
    camera_model_f.fromCameraInfo(in_message);

    image_size_f_.height = in_message.height;
    image_size_f_.width = in_message.width;
    image_frame_id_f_ = in_message.header.frame_id;

    camera_intrinsics_f_ = cv::Mat(3, 3, CV_64F);
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            camera_intrinsics_f_.at<double>(row, col) = in_message.K[row * 3 + col];
        }
    }

    distortion_coefficients_f_ = cv::Mat(1, 5, CV_64F);
    for (int col = 0; col < 5; col++)
    {
        distortion_coefficients_f_.at<double>(col) = in_message.D[col];
    }

    fx_f_ = static_cast<float>(in_message.P[0]);
    fy_f_ = static_cast<float>(in_message.P[5]);
    cx_f_ = static_cast<float>(in_message.P[2]);
    cy_f_ = static_cast<float>(in_message.P[6]);

    intrinsics_subscriber_f_.shutdown();
    camera_info_ok_f_ = true;
    ROS_INFO("[%s] Front CameraIntrinsics obtained.", __APP_NAME__);
}

tf::StampedTransform 
ROSPixelCloudFusionApp::FindTransform(const std::string &in_target_frame, const std::string &in_source_frame)
{
    tf::StampedTransform transform;
    
    try
    {
        // Lookup the transform between the source and target frame
        transform_listener_->lookupTransform(in_target_frame, in_source_frame, ros::Time(0), transform);
        
        // Check if the target frame corresponds to the left, right, back, or front camera
        if (in_target_frame == image_frame_id_l_)
        {
            camera_lidar_tf_l_ = transform;           // Store transform for the left camera
            camera_lidar_tf_ok_l_ = true;             // Mark left transform as available
            ROS_INFO("[%s] Left Camera-Lidar TF obtained", __APP_NAME__);
        }
        else if (in_target_frame == image_frame_id_r_)
        {
            camera_lidar_tf_r_ = transform;           // Store transform for the right camera
            camera_lidar_tf_ok_r_ = true;             // Mark right transform as available
            ROS_INFO("[%s] Right Camera-Lidar TF obtained", __APP_NAME__);
        }
        else if (in_target_frame == image_frame_id_b_)
        {
            camera_lidar_tf_b_ = transform;           // Store transform for the back camera
            camera_lidar_tf_ok_b_ = true;             // Mark back transform as available
            ROS_INFO("[%s] Back Camera-Lidar TF obtained", __APP_NAME__);
        }
        else if (in_target_frame == image_frame_id_f_)
        {
            camera_lidar_tf_f_ = transform;           // Store transform for the front camera
            camera_lidar_tf_ok_f_ = true;             // Mark front transform as available
            ROS_INFO("[%s] Front Camera-Lidar TF obtained", __APP_NAME__);
        }
    }
    catch (tf::TransformException ex)
    {
        ROS_ERROR("[%s] %s", __APP_NAME__, ex.what());
    }

    return transform;
}
void ROSPixelCloudFusionApp::image_callback(const sensor_msgs::CompressedImage::ConstPtr& image_msg){
    try {
        // CompressedImage 메시지를 cv::Mat으로 변환
        cv::Mat image = cv::imdecode(cv::Mat(image_msg->data), cv::IMREAD_COLOR);
        image_msg_ = image_msg;
        // 이미지 크기 출력 (너비와 높이)
        // if (!image.empty()) {
        //     std::cout << "Compressed Image Width: " << image.cols << ", Height: " << image.rows << std::endl;
            
        //     // 이미지 출력
        //     cv::imshow("Compressed Image", image);
        //     cv::waitKey(1); // 필요에 따라 키 입력 대기 시간을 설정
        // }
    } catch (const cv::Exception& e) {
        ROS_ERROR("Could not convert compressed image: %s", e.what());
    }

}

void ROSPixelCloudFusionApp::yolo_callback(const sensor_msgs::Image::ConstPtr& image_msg){
    try {
        // sensor_msgs::Image 메시지를 cv::Mat으로 변환
        cv_bridge::CvImagePtr cv_ptr;
        cv_ptr = cv_bridge::toCvCopy(image_msg, sensor_msgs::image_encodings::BGR8);

        // 이미지 크기 출력 (너비와 높이)
        // if (cv_ptr->image.rows > 0 && cv_ptr->image.cols > 0) {
        //     std::cout << "YOLO Image Width: " << cv_ptr->image.cols << ", Height: " << cv_ptr->image.rows << std::endl;
            
        //     // 이미지 출력
        //     cv::imshow("YOLO Image", cv_ptr->image);
        //     cv::waitKey(1); // 필요에 따라 키 입력 대기 시간을 설정
        // }
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("Could not convert YOLO image: %s", e.what());
    }
}

void ROSPixelCloudFusionApp::InitializeROSIo(ros::NodeHandle &in_private_handle)
{
    // get params
    std::string points_src, camera_info_src_l, camera_info_src_r, camera_info_src_b, camera_info_src_f, point_filtered_topic, fused_clustered_topic;
    std::string mask_src_l, mask_src_r, mask_src_b, mask_src_f, fused_topic, jsk_bboxes_topic, autoware_objects_topic, marker_topic;
    std::string name_space_str = ros::this_node::getNamespace();
    std::string image_topic, yolo_topic;

    ROS_INFO("[%s] This node requires: Registered TF(Lidar-Camera), CameraInfo, Image, and PointCloud.", __APP_NAME__);
    in_private_handle.param<std::string>("points_src", points_src, "/points_raw");

    in_private_handle.param<std::string>("image_topic", image_topic, "/camera/front_l/camera/image_raw/compressed");
    in_private_handle.param<std::string>("yolo_topic", yolo_topic, "/detection/yolo_l_image");

    in_private_handle.param<std::string>("camera_info_src_l", camera_info_src_l, "/camera_info");
    in_private_handle.param<std::string>("camera_info_src_r", camera_info_src_r, "/camera_info");
    in_private_handle.param<std::string>("camera_info_src_b", camera_info_src_b, "/camera_info");
    in_private_handle.param<std::string>("camera_info_src_f", camera_info_src_f, "/camera_info");

    in_private_handle.param<std::string>("mask_src_l", mask_src_l, "/detection/yolo_l_result");
    in_private_handle.param<std::string>("mask_src_r", mask_src_r, "/detection/yolo_r_result");
    in_private_handle.param<std::string>("mask_src_b", mask_src_b, "/detection/yolo_b_result");
    in_private_handle.param<std::string>("mask_src_f", mask_src_f, "/detection/yolo_f_result");  // Front YOLO mask

    in_private_handle.param<std::string>("fused_topic", fused_topic, "/detection/point_fused");
    in_private_handle.param<std::string>("fused_clustered_topic", fused_clustered_topic, "/detection/point_fused_clustered");
    in_private_handle.param<std::string>("point_filtered_topic", point_filtered_topic, "/detection/point_filterd");
    in_private_handle.param<std::string>("jsk_bboxes_topic", jsk_bboxes_topic, "/detection/side/lidar_detector/jsk_bboxes");
    in_private_handle.param<std::string>("autoware_objects_topic", autoware_objects_topic, "/detection/side/detected_object_array");
    in_private_handle.param<std::string>("marker_topic", marker_topic, "/detection/marker");

    in_private_handle.param<double>("intensity_threshold", intensity_threshold, 35.0);

    in_private_handle.param<bool>("pub_filtered_cloud", pub_filtered_cloud, false);
    in_private_handle.param<bool>("pub_fused_cloud", pub_fused_cloud, false);
    in_private_handle.param<bool>("pub_fused_clustered_cloud", pub_fused_clustered_cloud, false);
    in_private_handle.param<bool>("use_voxel_filter", use_voxel_filter, true);
    in_private_handle.param<bool>("use_ground_filter", use_ground_filter, true);
    in_private_handle.param<float>("voxel_size", voxel_size, 0.15);
    in_private_handle.param<int>("num_iterations", num_iterations, 50);
    in_private_handle.param<float>("distance_threshold", distance_threshold, 0.15);
    in_private_handle.param<float>("voxel_size", voxel_size, 0.15);

    in_private_handle.param<double>("cluster_tolerance", cluster_tolerance, 0.2);
    in_private_handle.param<int>("cluster_min_size", cluster_min_size, 50);
    in_private_handle.param<int>("cluster_max_size", cluster_max_size, 20000);


    in_private_handle.param<bool>("use_polygon_resize", use_polygon_resize, false);

    in_private_handle.param<float>("min_width", min_width, 50);
    in_private_handle.param<float>("min_height", min_height, 50);
    in_private_handle.param<float>("scale_w", scale_w, 0.9);
    in_private_handle.param<float>("scale_h", scale_h, 0.9);

    // Subscribe to camera intrinsics
    intrinsics_subscriber_l_ = in_private_handle.subscribe(camera_info_src_l, 1, &ROSPixelCloudFusionApp::IntrinsicsCallback_l, this);
    intrinsics_subscriber_r_ = in_private_handle.subscribe(camera_info_src_r, 1, &ROSPixelCloudFusionApp::IntrinsicsCallback_r, this);
    intrinsics_subscriber_b_ = in_private_handle.subscribe(camera_info_src_b, 1, &ROSPixelCloudFusionApp::IntrinsicsCallback_b, this);  // Back camera intrinsics subscriber
    intrinsics_subscriber_f_ = in_private_handle.subscribe(camera_info_src_f, 1, &ROSPixelCloudFusionApp::IntrinsicsCallback_f, this);  // Front camera intrinsics subscriber

    ROS_INFO("[%s] Subscribing to... %s", __APP_NAME__, points_src.c_str());
    cloud_subscriber_ = in_private_handle.subscribe(points_src, 1, &ROSPixelCloudFusionApp::CloudCallback, this);

    // Subscribe to YOLO masks
    mask_subscriber_l_ = in_private_handle.subscribe(mask_src_l, 1, &ROSPixelCloudFusionApp::SegmentCallback_l, this);
    mask_subscriber_r_ = in_private_handle.subscribe(mask_src_r, 1, &ROSPixelCloudFusionApp::SegmentCallback_r, this);
    mask_subscriber_b_ = in_private_handle.subscribe(mask_src_b, 1, &ROSPixelCloudFusionApp::SegmentCallback_b, this);  // Back YOLO mask subscriber
    mask_subscriber_f_ = in_private_handle.subscribe(mask_src_f, 1, &ROSPixelCloudFusionApp::SegmentCallback_f, this);  // Front YOLO mask subscriber

    image_subscriber_ = in_private_handle.subscribe(image_topic, 1, &ROSPixelCloudFusionApp::image_callback, this);  // Front YOLO mask subscriber
    yolo_subscriber_ = in_private_handle.subscribe(yolo_topic, 1, &ROSPixelCloudFusionApp::yolo_callback, this);  // Front YOLO mask subscriber

    publisher_filtered_cloud_ = node_handle_.advertise<sensor_msgs::PointCloud2>(point_filtered_topic, 1);
    publisher_fused_cloud_ = node_handle_.advertise<sensor_msgs::PointCloud2>(fused_topic, 1);
    publisher_fused_clustered_cloud_ = node_handle_.advertise<sensor_msgs::PointCloud2>(fused_clustered_topic, 1);
    pub_jsk_bboxes = node_handle_.advertise<jsk_recognition_msgs::BoundingBoxArray>(jsk_bboxes_topic, 1);
    pub_autoware_objects = node_handle_.advertise<autoware_msgs::DetectedObjectArray>(autoware_objects_topic, 1);
    pub_marker_array = node_handle_.advertise<visualization_msgs::MarkerArray>(marker_topic, 1);

    ROS_INFO("[%s] Publishing fused pointcloud in %s", __APP_NAME__, fused_topic.c_str());
}

void ROSPixelCloudFusionApp::Run()
{
    ros::NodeHandle private_node_handle("~");
    tf::TransformListener transform_listener;
    transform_listener_ = &transform_listener;

    InitializeROSIo(private_node_handle);

    ROS_INFO("[%s] Ready. Waiting for data...", __APP_NAME__);
    ros::spin();
    ROS_INFO("[%s] END", __APP_NAME__);
}

ROSPixelCloudFusionApp::ROSPixelCloudFusionApp()
{
    // Initialize flags for left, right, back, and front cameras
    camera_lidar_tf_ok_l_ = false;
    camera_lidar_tf_ok_r_ = false;
    camera_lidar_tf_ok_b_ = false;  // Back camera transform flag
    camera_lidar_tf_ok_f_ = false;  // Front camera transform flag
    camera_info_ok_l_ = false;
    camera_info_ok_r_ = false;
    camera_info_ok_b_ = false;  // Back camera info flag
    camera_info_ok_f_ = false;  // Front camera info flag

    // No processing at initialization
    processing_ = false;

    // Initialize image frame IDs for left, right, back, and front cameras to empty strings
    image_frame_id_l_ = "";
    image_frame_id_r_ = "";
    image_frame_id_b_ = "";  // Back camera frame ID
    image_frame_id_f_ = "";  // Front camera frame ID
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, __APP_NAME__);
 
  ROSPixelCloudFusionApp app;
 
  app.Run();
 
  return 0;
}