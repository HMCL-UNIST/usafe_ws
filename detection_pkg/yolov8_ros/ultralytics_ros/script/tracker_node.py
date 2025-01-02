#!/usr/bin/env python3
# -*- coding: utf-8 -*-
 
# ultralytics_ros
# Copyright (C) 2023-2024  Alpaca-zip
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import cv_bridge
import numpy as np
import roslib.packages
import rospy
from sensor_msgs.msg import Image, CameraInfo, CompressedImage
from ultralytics import YOLO
from vision_msgs.msg import Detection2D, Detection2DArray, ObjectHypothesisWithPose
from visualization_msgs.msg import Marker, MarkerArray
from ultralytics_ros.msg import YoloResult
import cv2
import image_geometry
from cv_bridge import CvBridge


class TrackerNode:
    def __init__(self):
        yolo_model = rospy.get_param("~yolo_model", "yolov8n.pt")
        self.input_topic = rospy.get_param("~input_topic", "image_raw")
        self.result_topic = rospy.get_param("~result_topic", "yolo_result")
        self.result_image_topic = rospy.get_param("~result_image_topic", "yolo_image")
        self.conf_thres = rospy.get_param("~conf_thres", 0.5)
        self.iou_thres = rospy.get_param("~iou_thres", 0.45)
        self.max_det = rospy.get_param("~max_det", 300)
        self.classes = rospy.get_param("~classes", None)
        self.tracker = rospy.get_param("~tracker", "bytetrack.yaml")
        self.device = rospy.get_param("~device", None)
        self.result_conf = rospy.get_param("~result_conf", True)
        self.result_line_width = rospy.get_param("~result_line_width", None)
        self.result_font_size = rospy.get_param("~result_font_size", None)
        self.result_font = rospy.get_param("~result_font", "Arial.ttf")
        self.result_labels = rospy.get_param("~result_labels", True)
        self.result_boxes = rospy.get_param("~result_boxes", True)
        self.result_masks = rospy.get_param("~result_masks", True)
        self.camera_info_topic = rospy.get_param("~camera_info_topic", "/camera/front_60/camera/camera_info")
        self.camera_model = image_geometry.PinholeCameraModel()

        path = roslib.packages.get_pkg_dir("ultralytics_ros")
        self.model = YOLO(f"{path}/models/{yolo_model}")

        self.model.fuse()

        # Camera parameters initialization
        self.camera_matrix = None
        self.dist_coeffs = None
        self.image_size = None
        self.camera_info_received = False  # Check if camera info has been received

        # Subscribe to camera_info to get the calibration data
        self.camera_info_sub = rospy.Subscriber(self.camera_info_topic, CameraInfo, self.camera_info_callback)
        # self.result_image_pub = rospy.Publisher(
        #     self.result_image_topic, Image, queue_size=1
        # )
        # Subscribe to image topic
        self.sub = rospy.Subscriber(
            self.input_topic,
            CompressedImage,
            self.image_callback,
            queue_size=1,
            buff_size=2**24,
        )
        # self.results_pub = rospy.Publisher(self.result_topic, Image, queue_size=1)
        self.results_pub = rospy.Publisher(self.result_topic, MarkerArray, queue_size=1)
        self.bridge = cv_bridge.CvBridge()
        self.use_segmentation = yolo_model.endswith("-seg.pt")
    
    def camera_info_callback(self, camera_info_msg):
        self.camera_model.fromCameraInfo(camera_info_msg)

        """Callback function to receive camera information"""
        if not self.camera_info_received:
            self.camera_matrix = np.array(camera_info_msg.K).reshape(3, 3)
            self.dist_coeffs = np.array(camera_info_msg.D)
            self.image_size = (camera_info_msg.width, camera_info_msg.height)

            rospy.loginfo("Camera matrix:\n{}".format(self.camera_matrix))
            rospy.loginfo("Distortion coefficients:\n{}".format(self.dist_coeffs))

            # Once the camera info is received, unregister the subscriber to stop further callbacks
            self.camera_info_sub.unregister()
            self.camera_info_received = True  # Camera info received
    
    def compressed_to_cv_image(self, compressed_msg):
        """Converts a compressed image message to OpenCV format."""
        self.img_array = np.frombuffer(compressed_msg.data, np.uint8)
        self.cv_image = cv2.imdecode(self.img_array, cv2.IMREAD_COLOR)
        return self.cv_image
    
    def image_callback(self, msg):
        # current_time_start = rospy.Time.now()

        cv_image = self.compressed_to_cv_image(msg)

        results = self.model.predict(cv_image, conf=self.conf_thres)

        if results is not None:
 

            # yolo_detected_object_mask = Image()
            yolo_detected_object_mask = MarkerArray()

            yolo_detected_object_mask = self.create_segmentation_masks_with_markers(results, msg.header)
            # yolo_result_image_msg = Image()
            # yolo_result_image_msg = self.create_result_image(results)
            # yolo_result_image_msg.header = msg.header
            # self.result_image_pub.publish(yolo_result_image_msg)

            self.results_pub.publish(yolo_detected_object_mask)



        # current_time_end = rospy.Time.now()

        # processing_time = (current_time_end - current_time_start).to_sec() * 1000.0
        # rospy.loginfo("Processing time: %.2f ms" % processing_time)

 
    def create_result_image(self, results):
        plotted_image = results[0].plot(
            conf=self.result_conf,
            line_width=self.result_line_width,
            font_size=self.result_font_size,
            font=self.result_font,
            labels=self.result_labels,
            # boxes=self.result_boxes,
            masks=self.result_masks,
        )        
        result_image_msg = self.bridge.cv2_to_imgmsg(plotted_image, encoding="bgr8")
        return result_image_msg
    
    def create_segmentation_masks_with_markers(self, results, header):
        marker_array = MarkerArray()

        polygon_id = 0

        for result in results:
            if hasattr(result, "masks") and result.masks is not None:
                for mask_tensor, cls, bbox in zip(result.masks, result.boxes.cls, result.boxes.xywh):
                    # current_time_start = rospy.Time.now()
                    class_id = int(cls.item())
                    if class_id == 2 or  class_id == 7:  # class_id == 2 -> car, class_id ==7 -> truck
                        # bbox_height = bbox[3].item()
                        # if header.frame_id == "front_l_cam" or header.frame_id == "front_r_cam":
                            # (50,1) (100,0.6) (150,0.4) (200,0.3) (280,0) regression result -> tbd
                        # dynamic_ratio = - 0.0000002589 * pow(bbox_height, 3) + 0.0001393 * pow(bbox_height, 2) - 0.0257264 * bbox_height + 1.9639

                        polygon = mask_tensor.xy[0]
                        # scaled_polygon = self.reduce_polygon_size(polygon, max(0.7, min(1, dynamic_ratio)))
                        
                        # print(max(0.6, min(1, dynamic_ratio)))
                        # Create marker for each point in the polygon
                        # print(scaled_polygon)
                        # print(type(scaled_polygon))
                        # for point in scaled_polygon:
                        for point in polygon:
                            marker = Marker()
                            
                            original_pixel = (point[0], point[1])
                            rectified_pixel = self.camera_model.rectifyPoint(original_pixel)
                            
                            marker.pose.position.x = rectified_pixel[0]
                            marker.pose.position.y = rectified_pixel[1]
                            marker.pose.position.z = polygon_id

                            marker_array.markers.append(marker)

                        polygon_id = polygon_id +1

                    # current_time_end = rospy.Time.now()

                    # processing_time = (current_time_end - current_time_start).to_sec() * 1000.0
                    # rospy.loginfo("Processing time: %.2f ms" % processing_time)
        return marker_array

    def reduce_polygon_size(self, polygon, scale_factor=0.5):
        # Compute the centroid of the polygon
        M = cv2.moments(np.array(polygon))
        if M['m00'] != 0:
            cX = int(M['m10'] / M['m00'])
            cY = int(M['m01'] / M['m00'])
        else:
            cX, cY = np.mean(polygon, axis=0)  # Fallback to the average point
        # print(scale_factor)
        # Scale the polygon
        scaled_polygon = []
        for point in polygon:
            # Move the point relative to the centroid and scale it
            new_point = [(point[0] - cX) * scale_factor + cX, (point[1] - cY) * scale_factor + cY]
            scaled_polygon.append(new_point)
        
        return np.array(scaled_polygon, dtype=np.int32)
    
if __name__ == "__main__":
    rospy.init_node("yolov8_ros")
    node = TrackerNode()
    rospy.spin()
 