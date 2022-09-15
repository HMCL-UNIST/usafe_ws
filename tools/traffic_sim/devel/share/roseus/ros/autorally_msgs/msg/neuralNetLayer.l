;; Auto-generated. Do not edit!


(when (boundp 'autorally_msgs::neuralNetLayer)
  (if (not (find-package "AUTORALLY_MSGS"))
    (make-package "AUTORALLY_MSGS"))
  (shadow 'neuralNetLayer (find-package "AUTORALLY_MSGS")))
(unless (find-package "AUTORALLY_MSGS::NEURALNETLAYER")
  (make-package "AUTORALLY_MSGS::NEURALNETLAYER"))

(in-package "ROS")
;;//! \htmlinclude neuralNetLayer.msg.html


(defclass autorally_msgs::neuralNetLayer
  :super ros::object
  :slots (_name _weight _bias ))

(defmethod autorally_msgs::neuralNetLayer
  (:init
   (&key
    ((:name __name) "")
    ((:weight __weight) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:bias __bias) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _name (string __name))
   (setq _weight __weight)
   (setq _bias __bias)
   self)
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:weight
   (&optional __weight)
   (if __weight (setq _weight __weight)) _weight)
  (:bias
   (&optional __bias)
   (if __bias (setq _bias __bias)) _bias)
  (:serialization-length
   ()
   (+
    ;; string _name
    4 (length _name)
    ;; float32[] _weight
    (* 4    (length _weight)) 4
    ;; float32[] _bias
    (* 4    (length _bias)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _name
       (write-long (length _name) s) (princ _name s)
     ;; float32[] _weight
     (write-long (length _weight) s)
     (dotimes (i (length _weight))
       (sys::poke (elt _weight i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[] _bias
     (write-long (length _bias) s)
     (dotimes (i (length _bias))
       (sys::poke (elt _bias i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float32[] _weight
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _weight (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _weight i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; float32[] _bias
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _bias (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _bias i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;;
   self)
  )

(setf (get autorally_msgs::neuralNetLayer :md5sum-) "5c7ae79f2ee4ffbb5044508aa41abced")
(setf (get autorally_msgs::neuralNetLayer :datatype-) "autorally_msgs/neuralNetLayer")
(setf (get autorally_msgs::neuralNetLayer :definition-)
      "string name
float32[] weight
float32[] bias
")



(provide :autorally_msgs/neuralNetLayer "5c7ae79f2ee4ffbb5044508aa41abced")


