#include "yolo_lidar_fusion/utils.h"

// transformAutowareObject 함수 정의
autoware_msgs::DetectedObject transformAutowareObject(
    const Box &box, const std_msgs::Header &header,
    const geometry_msgs::Pose &pose_transformed) {
  autoware_msgs::DetectedObject autoware_object;
  autoware_object.header = header;
  autoware_object.id = box.id;
  autoware_object.label = "unknown";
  autoware_object.score = 1.0f;
  autoware_object.pose = pose_transformed;
  autoware_object.pose_reliable = true;
  autoware_object.dimensions.x = box.dimension(0);
  autoware_object.dimensions.y = box.dimension(1);
  autoware_object.dimensions.z = box.dimension(2);
  autoware_object.valid = true;

  return autoware_object;
}

// segmentGround 함수 정의
void segmentGround(const boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ>>& input_cloud,
                   boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ>>& ground_cloud,
                   boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ>>& non_ground_cloud,
                   int max_iterations, float distance_threshold, bool optimize_coefficients) {
    pcl::SACSegmentation<pcl::PointXYZ> sac_seg;
    sac_seg.setOptimizeCoefficients(optimize_coefficients);
    sac_seg.setModelType(pcl::SACMODEL_PLANE);
    sac_seg.setMethodType(pcl::SAC_RANSAC);
    sac_seg.setMaxIterations(max_iterations);
    sac_seg.setDistanceThreshold(distance_threshold);

    pcl::PointIndices::Ptr ground_indices(new pcl::PointIndices);
    pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);

    sac_seg.setInputCloud(input_cloud);
    sac_seg.segment(*ground_indices, *coefficients);

    // Ground와 비 Ground 포인트 클라우드를 분리
    pcl::ExtractIndices<pcl::PointXYZ> extract;
    extract.setInputCloud(input_cloud);
    extract.setIndices(ground_indices);
    extract.setNegative(false);
    extract.filter(*ground_cloud);

    extract.setNegative(true);
    extract.filter(*non_ground_cloud);
}

Eigen::Matrix4f transformTFToEigenMatrix(const tf::StampedTransform& tf_transform)
{
    // Eigen의 Affine3d 행렬 선언 (회전 및 변환 모두 포함)
    Eigen::Affine3d affine_transform;

    // tf::StampedTransform의 회전(quaternion) 및 변환(translation) 추출
    tf::Vector3 tf_translation = tf_transform.getOrigin();
    tf::Quaternion tf_rotation = tf_transform.getRotation();

    // Eigen의 Translation3d로 변환
    Eigen::Translation3d translation(tf_translation.x(), tf_translation.y(), tf_translation.z());

    // Eigen의 Quaternion으로 회전 변환
    Eigen::Quaterniond rotation(tf_rotation.w(), tf_rotation.x(), tf_rotation.y(), tf_rotation.z());

    // 변환과 회전을 합쳐서 Affine3d로 생성
    affine_transform = translation * rotation;

    // Affine3d를 4x4 행렬인 Matrix4f로 변환
    Eigen::Matrix4f eigen_matrix = affine_transform.matrix().cast<float>();

    return eigen_matrix;  // Matrix4f 반환
}

bool IsPointInPolygon(const std::vector<cv::Point2f>& polygon, float x, float y) {
    int n = polygon.size();
    bool inside = false;

    for (int i = 0, j = n - 1; i < n; j = i++) {
        if ((polygon[i].y > y) != (polygon[j].y > y) &&
            (x < (polygon[j].x - polygon[i].x) * (y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x)) {
            inside = !inside;
        }
    }

    return inside;
}

Box axisAlignedBoundingBox(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cluster, int id)
{
    // 클러스터의 최소 및 최대 포인트를 찾습니다.
    pcl::PointXYZ min_pt, max_pt;
    pcl::getMinMax3D(*cluster, min_pt, max_pt);

    const Eigen::Vector3f position((max_pt.x + min_pt.x) / 2, 
                                    (max_pt.y + min_pt.y) / 2, 
                                    (max_pt.z + min_pt.z) / 2);
    const Eigen::Vector3f dimension((max_pt.x - min_pt.x), 
                                     (max_pt.y - min_pt.y), 
                                     (max_pt.z - min_pt.z));

    return Box(id, position, dimension);
}

Box axisAlignedBoundingBox(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cluster, int id, const float x_roi_threshold)
{
    // 클러스터의 최소 및 최대 포인트를 찾습니다.
    pcl::PointXYZ min_pt, max_pt;
    pcl::getMinMax3D(*cluster, min_pt, max_pt);

    float center_x = (max_pt.x + min_pt.x) / 2;
    float center_y = (max_pt.y + min_pt.y) / 2;
    float center_z = (max_pt.z + min_pt.z) / 2;

    if (std::abs(center_x) < x_roi_threshold){
        if (center_y >= 0){
            center_y = min_pt.y + 0.91;  // avante cn width = 1820mm
        }

        else center_y = max_pt.y - 0.91;
    }

    const Eigen::Vector3f position(center_x, 
                                   center_y, 
                                   center_z);

    const Eigen::Vector3f dimension((max_pt.x - min_pt.x), 
                                     (max_pt.y - min_pt.y), 
                                     (max_pt.z - min_pt.z));

    return Box(id, position, dimension);
}

void applyCropBoxFilter(const boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ>>& input_cloud,
                        boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ>>& output_cloud,
                        const Eigen::Vector4f& min_pt, const Eigen::Vector4f& max_pt, bool set_negative) {
    // CropBox 필터 선언
    pcl::CropBox<pcl::PointXYZ> crop_box;
    crop_box.setInputCloud(input_cloud);

    // CropBox의 최소 및 최대 점 설정
    crop_box.setMin(min_pt);
    crop_box.setMax(max_pt);

    // 필터링: true로 설정하면 박스 안의 포인트를 제외하고, false로 설정하면 박스 안의 포인트만 남긴다.
    crop_box.setNegative(set_negative);

    // 필터 적용
    crop_box.filter(*output_cloud);
}

void applyVoxelGridFilter(const boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ>>& input_cloud,
                          boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ>>& output_cloud, 
                          float voxel_size) {
    // VoxelGrid 필터 선언
    pcl::VoxelGrid<pcl::PointXYZ> voxel_filter;
    voxel_filter.setInputCloud(input_cloud); // 원래 포인트 클라우드 입력

    // 리프 크기 설정 (voxel_size로 설정)
    voxel_filter.setLeafSize(voxel_size, voxel_size, voxel_size);

    // 필터 적용
    voxel_filter.filter(*output_cloud);
}


void DrawPolygon(cv::Mat& image, const std::vector<cv::Point2f>& polygon, const cv::Scalar& color, int thickness = 2) {
    std::vector<cv::Point> polygon_int;
    for (const auto& pt : polygon) {
        polygon_int.push_back(cv::Point(static_cast<int>(pt.x), static_cast<int>(pt.y)));
    }

    const cv::Point* pts = polygon_int.data();
    int npts = static_cast<int>(polygon_int.size());

    // 다각형 그리기
    cv::polylines(image, &pts, &npts, 1, true, color, thickness);
}
void AdjustPolygonSize(std::vector<cv::Point2f>& polygon, float min_width, float min_height, float scale_x_manual, float scale_y_manual) {
    // 다각형의 최소/최대 x, y 값을 구함
    float min_x = std::numeric_limits<float>::max();
    float max_x = std::numeric_limits<float>::lowest();
    float min_y = std::numeric_limits<float>::max();
    float max_y = std::numeric_limits<float>::lowest();


    // cv::Mat image = cv::Mat::zeros(3000, 3000, CV_8UC3);
    // // cv::Mat image2 = cv::Mat::zeros(2000, 2000, CV_8UC3);
    // DrawPolygon(image, polygon, cv::Scalar(0, 0, 255), 2);
    // // cv::imshow("Polygon Visualization", image);


    for (const auto& point : polygon) {
        if (point.x < min_x) min_x = point.x;
        if (point.x > max_x) max_x = point.x;
        if (point.y < min_y) min_y = point.y;
        if (point.y > max_y) max_y = point.y;
    }

    // 다각형의 중심 계산
    float center_x = (min_x + max_x) / 2.0f;
    float center_y = (min_y + max_y) / 2.0f;

    // 현재 다각형의 너비와 높이 계산
    float width = max_x - min_x;
    float height = max_y - min_y;
    // 다각형이 최소 width와 height보다 작은 경우, 비율을 계산
    float scale_x = (width < min_width) ? min_width / width : scale_x_manual + (1 - scale_x_manual)*min_width/width;
    float scale_y = (height < min_height) ? min_height / height : scale_y_manual + (1 - scale_y_manual)*min_height/height;;
    // if(scale_x < 0.8) std::cout << "scale_x"<< std::endl;

    // 다각형의 각 포인트를 중심을 기준으로 스케일링
    for (auto& point : polygon) {

        point.x = center_x + (point.x - center_x) * scale_x;
        // std::cout << center_x<< std::endl;
        // std::cout << center_y<< std::endl;
        // std::cout << scale_y<< std::endl;
        // std::cout << point.y<< std::endl;
        point.y = center_y + (point.y - center_y) * scale_y;
        // std::cout << point.y<< std::endl;
    }


    // // 조정된 다각형 그리기 (초록색)
    // DrawPolygon(image, polygon, cv::Scalar(0, 255, 0), 2);

    // // 결과 이미지 표시
    // cv::imshow("Polygon Visualization2", image);
    // cv::waitKey(10);
}

void projectLidarToImage(const sensor_msgs::CompressedImage::ConstPtr& image_msg, pcl::PointCloud<pcl::PointXYZI>::Ptr& cloud, const Eigen::Matrix4f& transform,\
 const image_geometry::PinholeCameraModel cm, const float fx_l_, const float fy_l_, const float cx_l_, const float cy_l_, const std::vector<std::vector<cv::Point2f>>polygons)
{
    try {
        // Convert ROS compressed image message to OpenCV image
        cv::Mat image = cv::imdecode(cv::Mat(image_msg->data), cv::IMREAD_COLOR);

        // 이미지 크기 출력 (너비와 높이)
        if (!image.empty()) {
            // std::cout << "Compressed Image Width: " << image.cols << ", Height: " << image.rows << std::endl;

                // Rectify the image (보정된 이미지로 변환)
                cv::Mat rectified_image;
                cm.rectifyImage(image, rectified_image);

            // Loop through each point in the point cloud
            std::cout << "Compressed Image Width: " << cloud->points.size() << std::endl;

            for (const auto& point : cloud->points) {
                // Transform the point cloud using the calibration transform matrix
                Eigen::Vector4f point_h(point.x, point.y, point.z, 1.0);
                Eigen::Vector4f transformed_point = transform * point_h;

                // Project the transformed point onto the image
                float u = static_cast<float>(fx_l_ * transformed_point.x() / transformed_point.z() + cx_l_);
                float v = static_cast<float>(fy_l_ * transformed_point.y() / transformed_point.z() + cy_l_);
                cv::Point2f projected_point(u, v);

                if (projected_point.x >= 0 && projected_point.x < rectified_image.cols && projected_point.y >= 0 && projected_point.y < rectified_image.rows && transformed_point.z() > 0) {
                // if (u >= 0 && u < image.cols && v >= 0 && v < image.rows && transformed_point.z() > 0) {
                    // Intensity-based coloring: Map intensity to a color (e.g., blue to red gradient)
                    float intensity = point.intensity;
                    float max_intensity = 2300;
                    // Normalize intensity to a 0-1 range
                    float normalized_intensity = intensity / max_intensity;

                    // Calculate color: blue for high intensity, green for medium, red for low intensity
                    int blue = static_cast<int>(255 * normalized_intensity);       // Blue increases with intensity
                    int green = static_cast<int>(255 * (1.0f - std::abs(normalized_intensity - 0.5f) * 2)); // Green peaks at mid-intensity
                    int red = static_cast<int>(255 * (1.0f - normalized_intensity)); // Red decreases with intensity

                    int intensity_color = std::min(255, static_cast<int>(255 * (intensity / max_intensity)));

                    cv::circle(rectified_image, cv::Point(projected_point.x, projected_point.y), 5, cv::Scalar(blue, green, red), -1); // Intensity in blue channel
                    // cv::circle(image, cv::Point(u, v), 3, cv::Scalar(0, 0, intensity_color), -1); // Intensity in blue channel
                }
            }

            for (const auto& polygon : polygons) {
                // std::vector<cv::Point2f> polygon_ = polygon;
                // AdjustPolygonSize(polygon_,  min_width, min_height, scale_w, scale_h);
                DrawPolygon(rectified_image, polygon, cv::Scalar(0, 255, 0), 2);
            }
            // Display the image with projected points
            cv::imshow("Lidar Projected on Image", rectified_image);
            cv::waitKey(10); // 필요에 따라 키 입력 대기 시간을 설정
        }
    } catch (const cv::Exception& e) {
        ROS_ERROR("Error projecting Lidar to image: %s", e.what());
    }
}