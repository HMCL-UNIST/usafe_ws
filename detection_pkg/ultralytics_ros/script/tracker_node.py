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
 
import cv_bridge
import numpy as np
import roslib.packages
import rospy
from sensor_msgs.msg import Image
from sensor_msgs.msg import CompressedImage
from ultralytics import YOLO
from vision_msgs.msg import Detection2D, Detection2DArray, ObjectHypothesisWithPose
from visualization_msgs.msg import Marker, MarkerArray
from ultralytics_ros.msg import YoloResult
from autoware_msgs.msg import DetectedObject, DetectedObjectArray
import cv2
 
 
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
        path = roslib.packages.get_pkg_dir("ultralytics_ros")
        self.model = YOLO(f"{path}/models/{yolo_model}")
        
        self.model.fuse()
        self.sub = rospy.Subscriber(
            self.input_topic,
            # Image,
            CompressedImage,
            self.image_callback,
            queue_size=1,
            buff_size=2**24,
        )
        self.results_pub = rospy.Publisher(self.result_topic, MarkerArray, queue_size=1)
        # self.result_image_pub = rospy.Publisher(
        #     self.result_image_topic, Image, queue_size=1
        # )
        self.bridge = cv_bridge.CvBridge()
        self.use_segmentation = yolo_model.endswith("-seg.pt")
 
    def compressed_to_cv_image(self, compressed_msg):
        self.img_array = np.frombuffer(compressed_msg.data, np.uint8)
        self.cv_image = cv2.imdecode(self.img_array, cv2.IMREAD_COLOR)
        return self.cv_image
    
    def image_callback(self, msg):
        current_time_start = rospy.Time.now()

        # cv_image = self.bridge.imgmsg_to_cv2(raw_image, desired_encoding="bgr8")
        cv_image = self.compressed_to_cv_image(msg)

        results = self.model.predict(cv_image, conf=self.conf_thres)

        height, width, _ = cv_image.shape
        image_shape = (height, width)
 
        if results is not None:
 
            # yolo_detected_object_mask = Image()
            yolo_detected_object_mask = MarkerArray()
            # yolo_result_image_msg = Image()

            yolo_detected_object_mask = self.create_segmentation_masks_with_markers(results, msg.header)
            # yolo_detected_object_mask = self.create_segmentation_masks(results, image_shape)
            # yolo_result_image_msg = self.create_result_image(results)

            # yolo_result_image_msg.header = msg.header

            self.results_pub.publish(yolo_detected_object_mask)
            # self.result_image_pub.publish(yolo_result_image_msg)
        current_time_end = rospy.Time.now()

        processing_time = (current_time_end - current_time_start).to_sec() * 1000.0
        rospy.loginfo("Processing time: %.2f ms" % processing_time)


    def create_detections_array(self, results):

        class_list = ['person', 'bicycle', 'car', 'motorcycle', 'airplane', 'bus', 'train', 'truck', 'boat', 'traffic light', \
                        'fire hydrant', 'stop sign', 'parking meter', 'bench', 'bird', 'cat', 'dog', 'horse', 'sheep', 'cow', \
                        'elephant', 'bear', 'zebra', 'giraffe', 'backpack', 'umbrella', 'handbag', 'tie', 'suitcase', 'frisbee', \
                        'skis', 'snowboard', 'sports ball', 'kite', 'baseball bat', 'baseball glove', 'skateboard', 'surfboard', 'tennis racket',  'bottle', \
                        'wine glass', 'cup', 'fork', 'knife', 'spoon', 'bowl', 'banana', 'apple', 'sandwich', 'orange', \
                        'broccoli', 'carrot', 'hot dog', 'pizza', 'donut', 'cake', 'chair', 'couch', 'potted plant', 'bed', \
                        'dining table', 'toilet', 'tv', 'laptop', 'mouse', 'remote', 'keyboard', 'cell phone', 'microwave', 'oven', \
                        'toaster', 'sink', 'refrigerator', 'book', 'clock', 'vase', 'scissors', 'teddy bear', 'hair drier', 'toothbrush']
        
        detected_object_array = DetectedObjectArray()
        bounding_box = results[0].boxes.xywh
        classes = results[0].boxes.cls
        confidence_score = results[0].boxes.conf
        if results[0].boxes.id is not None:
            track_ids = results[0].boxes.id.int().tolist()
        else :
            track_ids = np.zeros(len(bounding_box))
 
        for bbox, cls, conf, track_id in zip(bounding_box, classes, confidence_score, track_ids):
        # for bbox, cls, conf in zip(bounding_box, classes, confidence_score):
            detected_object = DetectedObject()

            detected_object.x = int(np.round(bbox[0].item()))
            detected_object.y = int(np.round(bbox[1].item()))
            detected_object.width = int(np.round(bbox[2].item()))
            detected_object.height = int(np.round(bbox[3].item()))
            # print(cls)
            detected_object.label = class_list[int(cls.item())%3]
            
            detected_object.id = int(track_id)
            detected_object.score = float(conf)
            detected_object_array.objects.append(detected_object)
        return detected_object_array
 
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

        marker_id = 0  
        polygon_id = 0

        for result in results:
            if hasattr(result, "masks") and result.masks is not None:
                for mask_tensor, cls, bbox in zip(result.masks, result.boxes.cls, result.boxes.xywh):
                    class_id = int(cls.item())
                    if class_id == 2:  # class_id == 2 -> car
                        bbox_height = bbox[3].item()
                        # (50,1) (100,0.6) (150,0.4) (200,0.3) (280,0) regression result
                        # dynamic_ratio = - 0.0000002589 * pow(bbox_height, 3) + 0.0001393 * pow(bbox_height, 2) - 0.0257264 * bbox_height + 1.9639
                        polygon = mask_tensor.xy[0]
                        # scaled_polygon = self.reduce_polygon_size(polygon, max(0, min(1, dynamic_ratio)))

                        # Create marker for each point in the polygon
                        # for point in scaled_polygon:
                        for point in polygon:
                            marker = Marker()

                            marker.pose.position.x = point[0]
                            marker.pose.position.y = point[1]
                            marker.pose.position.z = polygon_id

                            marker_array.markers.append(marker)
                            marker_id += 1

                        polygon_id = polygon_id +1

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
 
