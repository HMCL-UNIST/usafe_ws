;; Auto-generated. Do not edit!


(when (boundp 'autorally_msgs::neuralNetModel)
  (if (not (find-package "AUTORALLY_MSGS"))
    (make-package "AUTORALLY_MSGS"))
  (shadow 'neuralNetModel (find-package "AUTORALLY_MSGS")))
(unless (find-package "AUTORALLY_MSGS::NEURALNETMODEL")
  (make-package "AUTORALLY_MSGS::NEURALNETMODEL"))

(in-package "ROS")
;;//! \htmlinclude neuralNetModel.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass autorally_msgs::neuralNetModel
  :super ros::object
  :slots (_header _network _numLayers _structure ))

(defmethod autorally_msgs::neuralNetModel
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:network __network) (let (r) (dotimes (i 0) (push (instance autorally_msgs::neuralNetLayer :init) r)) r))
    ((:numLayers __numLayers) 0)
    ((:structure __structure) (make-array 0 :initial-element 0 :element-type :integer))
    )
   (send-super :init)
   (setq _header __header)
   (setq _network __network)
   (setq _numLayers (round __numLayers))
   (setq _structure __structure)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:network
   (&rest __network)
   (if (keywordp (car __network))
       (send* _network __network)
     (progn
       (if __network (setq _network (car __network)))
       _network)))
  (:numLayers
   (&optional __numLayers)
   (if __numLayers (setq _numLayers __numLayers)) _numLayers)
  (:structure
   (&optional __structure)
   (if __structure (setq _structure __structure)) _structure)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; autorally_msgs/neuralNetLayer[] _network
    (apply #'+ (send-all _network :serialization-length)) 4
    ;; int32 _numLayers
    4
    ;; int32[] _structure
    (* 4    (length _structure)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; autorally_msgs/neuralNetLayer[] _network
     (write-long (length _network) s)
     (dolist (elem _network)
       (send elem :serialize s)
       )
     ;; int32 _numLayers
       (write-long _numLayers s)
     ;; int32[] _structure
     (write-long (length _structure) s)
     (dotimes (i (length _structure))
       (write-long (elt _structure i) s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; autorally_msgs/neuralNetLayer[] _network
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _network (let (r) (dotimes (i n) (push (instance autorally_msgs::neuralNetLayer :init) r)) r))
     (dolist (elem- _network)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; int32 _numLayers
     (setq _numLayers (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32[] _structure
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _structure (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _structure i) (sys::peek buf ptr- :integer)) (incf ptr- 4)
     ))
   ;;
   self)
  )

(setf (get autorally_msgs::neuralNetModel :md5sum-) "3c8c8380b1c9bb122f00005291fff0d0")
(setf (get autorally_msgs::neuralNetModel :datatype-) "autorally_msgs/neuralNetModel")
(setf (get autorally_msgs::neuralNetModel :definition-)
      "Header header

neuralNetLayer[] network
int32 numLayers
int32[] structure
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: autorally_msgs/neuralNetLayer
string name
float32[] weight
float32[] bias
")



(provide :autorally_msgs/neuralNetModel "3c8c8380b1c9bb122f00005291fff0d0")


