;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::Status)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'Status (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::STATUS")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::STATUS"))

(in-package "ROS")
;;//! \htmlinclude Status.msg.html


(defclass microstrain_inertial_msgs::Status
  :super ros::object
  :slots (_device_model _status_selector _status_flags _system_state _system_timer_ms _gps_power_on _num_gps_pps_triggers _last_gps_pps_trigger_ms _imu_stream_enabled _gps_stream_enabled _filter_stream_enabled _imu_dropped_packets _gps_dropped_packets _filter_dropped_packets _com1_port_bytes_written _com1_port_bytes_read _com1_port_write_overruns _com1_port_read_overruns _imu_parser_errors _imu_message_count _imu_last_message_ms _gps_parser_errors _gps_message_count _gps_last_message_ms ))

(defmethod microstrain_inertial_msgs::Status
  (:init
   (&key
    ((:device_model __device_model) 0)
    ((:status_selector __status_selector) 0)
    ((:status_flags __status_flags) 0)
    ((:system_state __system_state) 0)
    ((:system_timer_ms __system_timer_ms) 0)
    ((:gps_power_on __gps_power_on) 0)
    ((:num_gps_pps_triggers __num_gps_pps_triggers) 0)
    ((:last_gps_pps_trigger_ms __last_gps_pps_trigger_ms) 0)
    ((:imu_stream_enabled __imu_stream_enabled) 0)
    ((:gps_stream_enabled __gps_stream_enabled) 0)
    ((:filter_stream_enabled __filter_stream_enabled) 0)
    ((:imu_dropped_packets __imu_dropped_packets) 0)
    ((:gps_dropped_packets __gps_dropped_packets) 0)
    ((:filter_dropped_packets __filter_dropped_packets) 0)
    ((:com1_port_bytes_written __com1_port_bytes_written) 0)
    ((:com1_port_bytes_read __com1_port_bytes_read) 0)
    ((:com1_port_write_overruns __com1_port_write_overruns) 0)
    ((:com1_port_read_overruns __com1_port_read_overruns) 0)
    ((:imu_parser_errors __imu_parser_errors) 0)
    ((:imu_message_count __imu_message_count) 0)
    ((:imu_last_message_ms __imu_last_message_ms) 0)
    ((:gps_parser_errors __gps_parser_errors) 0)
    ((:gps_message_count __gps_message_count) 0)
    ((:gps_last_message_ms __gps_last_message_ms) 0)
    )
   (send-super :init)
   (setq _device_model (round __device_model))
   (setq _status_selector (round __status_selector))
   (setq _status_flags (round __status_flags))
   (setq _system_state (round __system_state))
   (setq _system_timer_ms (round __system_timer_ms))
   (setq _gps_power_on (round __gps_power_on))
   (setq _num_gps_pps_triggers (round __num_gps_pps_triggers))
   (setq _last_gps_pps_trigger_ms (round __last_gps_pps_trigger_ms))
   (setq _imu_stream_enabled (round __imu_stream_enabled))
   (setq _gps_stream_enabled (round __gps_stream_enabled))
   (setq _filter_stream_enabled (round __filter_stream_enabled))
   (setq _imu_dropped_packets (round __imu_dropped_packets))
   (setq _gps_dropped_packets (round __gps_dropped_packets))
   (setq _filter_dropped_packets (round __filter_dropped_packets))
   (setq _com1_port_bytes_written (round __com1_port_bytes_written))
   (setq _com1_port_bytes_read (round __com1_port_bytes_read))
   (setq _com1_port_write_overruns (round __com1_port_write_overruns))
   (setq _com1_port_read_overruns (round __com1_port_read_overruns))
   (setq _imu_parser_errors (round __imu_parser_errors))
   (setq _imu_message_count (round __imu_message_count))
   (setq _imu_last_message_ms (round __imu_last_message_ms))
   (setq _gps_parser_errors (round __gps_parser_errors))
   (setq _gps_message_count (round __gps_message_count))
   (setq _gps_last_message_ms (round __gps_last_message_ms))
   self)
  (:device_model
   (&optional __device_model)
   (if __device_model (setq _device_model __device_model)) _device_model)
  (:status_selector
   (&optional __status_selector)
   (if __status_selector (setq _status_selector __status_selector)) _status_selector)
  (:status_flags
   (&optional __status_flags)
   (if __status_flags (setq _status_flags __status_flags)) _status_flags)
  (:system_state
   (&optional __system_state)
   (if __system_state (setq _system_state __system_state)) _system_state)
  (:system_timer_ms
   (&optional __system_timer_ms)
   (if __system_timer_ms (setq _system_timer_ms __system_timer_ms)) _system_timer_ms)
  (:gps_power_on
   (&optional __gps_power_on)
   (if __gps_power_on (setq _gps_power_on __gps_power_on)) _gps_power_on)
  (:num_gps_pps_triggers
   (&optional __num_gps_pps_triggers)
   (if __num_gps_pps_triggers (setq _num_gps_pps_triggers __num_gps_pps_triggers)) _num_gps_pps_triggers)
  (:last_gps_pps_trigger_ms
   (&optional __last_gps_pps_trigger_ms)
   (if __last_gps_pps_trigger_ms (setq _last_gps_pps_trigger_ms __last_gps_pps_trigger_ms)) _last_gps_pps_trigger_ms)
  (:imu_stream_enabled
   (&optional __imu_stream_enabled)
   (if __imu_stream_enabled (setq _imu_stream_enabled __imu_stream_enabled)) _imu_stream_enabled)
  (:gps_stream_enabled
   (&optional __gps_stream_enabled)
   (if __gps_stream_enabled (setq _gps_stream_enabled __gps_stream_enabled)) _gps_stream_enabled)
  (:filter_stream_enabled
   (&optional __filter_stream_enabled)
   (if __filter_stream_enabled (setq _filter_stream_enabled __filter_stream_enabled)) _filter_stream_enabled)
  (:imu_dropped_packets
   (&optional __imu_dropped_packets)
   (if __imu_dropped_packets (setq _imu_dropped_packets __imu_dropped_packets)) _imu_dropped_packets)
  (:gps_dropped_packets
   (&optional __gps_dropped_packets)
   (if __gps_dropped_packets (setq _gps_dropped_packets __gps_dropped_packets)) _gps_dropped_packets)
  (:filter_dropped_packets
   (&optional __filter_dropped_packets)
   (if __filter_dropped_packets (setq _filter_dropped_packets __filter_dropped_packets)) _filter_dropped_packets)
  (:com1_port_bytes_written
   (&optional __com1_port_bytes_written)
   (if __com1_port_bytes_written (setq _com1_port_bytes_written __com1_port_bytes_written)) _com1_port_bytes_written)
  (:com1_port_bytes_read
   (&optional __com1_port_bytes_read)
   (if __com1_port_bytes_read (setq _com1_port_bytes_read __com1_port_bytes_read)) _com1_port_bytes_read)
  (:com1_port_write_overruns
   (&optional __com1_port_write_overruns)
   (if __com1_port_write_overruns (setq _com1_port_write_overruns __com1_port_write_overruns)) _com1_port_write_overruns)
  (:com1_port_read_overruns
   (&optional __com1_port_read_overruns)
   (if __com1_port_read_overruns (setq _com1_port_read_overruns __com1_port_read_overruns)) _com1_port_read_overruns)
  (:imu_parser_errors
   (&optional __imu_parser_errors)
   (if __imu_parser_errors (setq _imu_parser_errors __imu_parser_errors)) _imu_parser_errors)
  (:imu_message_count
   (&optional __imu_message_count)
   (if __imu_message_count (setq _imu_message_count __imu_message_count)) _imu_message_count)
  (:imu_last_message_ms
   (&optional __imu_last_message_ms)
   (if __imu_last_message_ms (setq _imu_last_message_ms __imu_last_message_ms)) _imu_last_message_ms)
  (:gps_parser_errors
   (&optional __gps_parser_errors)
   (if __gps_parser_errors (setq _gps_parser_errors __gps_parser_errors)) _gps_parser_errors)
  (:gps_message_count
   (&optional __gps_message_count)
   (if __gps_message_count (setq _gps_message_count __gps_message_count)) _gps_message_count)
  (:gps_last_message_ms
   (&optional __gps_last_message_ms)
   (if __gps_last_message_ms (setq _gps_last_message_ms __gps_last_message_ms)) _gps_last_message_ms)
  (:serialization-length
   ()
   (+
    ;; uint16 _device_model
    2
    ;; uint8 _status_selector
    1
    ;; uint32 _status_flags
    4
    ;; uint16 _system_state
    2
    ;; uint32 _system_timer_ms
    4
    ;; uint8 _gps_power_on
    1
    ;; uint32 _num_gps_pps_triggers
    4
    ;; uint32 _last_gps_pps_trigger_ms
    4
    ;; uint8 _imu_stream_enabled
    1
    ;; uint8 _gps_stream_enabled
    1
    ;; uint8 _filter_stream_enabled
    1
    ;; uint32 _imu_dropped_packets
    4
    ;; uint32 _gps_dropped_packets
    4
    ;; uint32 _filter_dropped_packets
    4
    ;; uint32 _com1_port_bytes_written
    4
    ;; uint32 _com1_port_bytes_read
    4
    ;; uint32 _com1_port_write_overruns
    4
    ;; uint32 _com1_port_read_overruns
    4
    ;; uint32 _imu_parser_errors
    4
    ;; uint32 _imu_message_count
    4
    ;; uint32 _imu_last_message_ms
    4
    ;; uint32 _gps_parser_errors
    4
    ;; uint32 _gps_message_count
    4
    ;; uint32 _gps_last_message_ms
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint16 _device_model
       (write-word _device_model s)
     ;; uint8 _status_selector
       (write-byte _status_selector s)
     ;; uint32 _status_flags
       (write-long _status_flags s)
     ;; uint16 _system_state
       (write-word _system_state s)
     ;; uint32 _system_timer_ms
       (write-long _system_timer_ms s)
     ;; uint8 _gps_power_on
       (write-byte _gps_power_on s)
     ;; uint32 _num_gps_pps_triggers
       (write-long _num_gps_pps_triggers s)
     ;; uint32 _last_gps_pps_trigger_ms
       (write-long _last_gps_pps_trigger_ms s)
     ;; uint8 _imu_stream_enabled
       (write-byte _imu_stream_enabled s)
     ;; uint8 _gps_stream_enabled
       (write-byte _gps_stream_enabled s)
     ;; uint8 _filter_stream_enabled
       (write-byte _filter_stream_enabled s)
     ;; uint32 _imu_dropped_packets
       (write-long _imu_dropped_packets s)
     ;; uint32 _gps_dropped_packets
       (write-long _gps_dropped_packets s)
     ;; uint32 _filter_dropped_packets
       (write-long _filter_dropped_packets s)
     ;; uint32 _com1_port_bytes_written
       (write-long _com1_port_bytes_written s)
     ;; uint32 _com1_port_bytes_read
       (write-long _com1_port_bytes_read s)
     ;; uint32 _com1_port_write_overruns
       (write-long _com1_port_write_overruns s)
     ;; uint32 _com1_port_read_overruns
       (write-long _com1_port_read_overruns s)
     ;; uint32 _imu_parser_errors
       (write-long _imu_parser_errors s)
     ;; uint32 _imu_message_count
       (write-long _imu_message_count s)
     ;; uint32 _imu_last_message_ms
       (write-long _imu_last_message_ms s)
     ;; uint32 _gps_parser_errors
       (write-long _gps_parser_errors s)
     ;; uint32 _gps_message_count
       (write-long _gps_message_count s)
     ;; uint32 _gps_last_message_ms
       (write-long _gps_last_message_ms s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint16 _device_model
     (setq _device_model (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint8 _status_selector
     (setq _status_selector (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint32 _status_flags
     (setq _status_flags (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint16 _system_state
     (setq _system_state (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint32 _system_timer_ms
     (setq _system_timer_ms (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint8 _gps_power_on
     (setq _gps_power_on (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint32 _num_gps_pps_triggers
     (setq _num_gps_pps_triggers (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _last_gps_pps_trigger_ms
     (setq _last_gps_pps_trigger_ms (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint8 _imu_stream_enabled
     (setq _imu_stream_enabled (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _gps_stream_enabled
     (setq _gps_stream_enabled (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _filter_stream_enabled
     (setq _filter_stream_enabled (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint32 _imu_dropped_packets
     (setq _imu_dropped_packets (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _gps_dropped_packets
     (setq _gps_dropped_packets (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _filter_dropped_packets
     (setq _filter_dropped_packets (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _com1_port_bytes_written
     (setq _com1_port_bytes_written (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _com1_port_bytes_read
     (setq _com1_port_bytes_read (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _com1_port_write_overruns
     (setq _com1_port_write_overruns (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _com1_port_read_overruns
     (setq _com1_port_read_overruns (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _imu_parser_errors
     (setq _imu_parser_errors (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _imu_message_count
     (setq _imu_message_count (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _imu_last_message_ms
     (setq _imu_last_message_ms (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _gps_parser_errors
     (setq _gps_parser_errors (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _gps_message_count
     (setq _gps_message_count (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _gps_last_message_ms
     (setq _gps_last_message_ms (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get microstrain_inertial_msgs::Status :md5sum-) "b19b8bec6f96c609664c27dbc51ddf60")
(setf (get microstrain_inertial_msgs::Status :datatype-) "microstrain_inertial_msgs/Status")
(setf (get microstrain_inertial_msgs::Status :definition-)
      "uint16 device_model
uint8  status_selector

uint32 status_flags

uint16 system_state
uint32 system_timer_ms

uint8 gps_power_on

uint32 num_gps_pps_triggers
uint32 last_gps_pps_trigger_ms

uint8 imu_stream_enabled
uint8 gps_stream_enabled
uint8 filter_stream_enabled

uint32 imu_dropped_packets
uint32 gps_dropped_packets
uint32 filter_dropped_packets

uint32 com1_port_bytes_written
uint32 com1_port_bytes_read
uint32 com1_port_write_overruns
uint32 com1_port_read_overruns

uint32 imu_parser_errors
uint32 imu_message_count
uint32 imu_last_message_ms

uint32 gps_parser_errors
uint32 gps_message_count
uint32 gps_last_message_ms

")



(provide :microstrain_inertial_msgs/Status "b19b8bec6f96c609664c27dbc51ddf60")


