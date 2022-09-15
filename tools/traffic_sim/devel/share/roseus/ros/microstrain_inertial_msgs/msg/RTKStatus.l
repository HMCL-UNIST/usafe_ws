;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::RTKStatus)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'RTKStatus (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))

(in-package "ROS")
;;//! \htmlinclude RTKStatus.msg.html


(intern "*MODEM_STATE_OFF*" (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(shadow '*MODEM_STATE_OFF* (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(defconstant microstrain_inertial_msgs::RTKStatus::*MODEM_STATE_OFF* 0)
(intern "*MODEM_STATE_NO_NETWORK*" (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(shadow '*MODEM_STATE_NO_NETWORK* (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(defconstant microstrain_inertial_msgs::RTKStatus::*MODEM_STATE_NO_NETWORK* 1)
(intern "*MODEM_STATE_NETWORK_CONNECTED*" (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(shadow '*MODEM_STATE_NETWORK_CONNECTED* (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(defconstant microstrain_inertial_msgs::RTKStatus::*MODEM_STATE_NETWORK_CONNECTED* 2)
(intern "*MODEM_STATE_CONFIGURING_DATA_CONTEXT*" (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(shadow '*MODEM_STATE_CONFIGURING_DATA_CONTEXT* (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(defconstant microstrain_inertial_msgs::RTKStatus::*MODEM_STATE_CONFIGURING_DATA_CONTEXT* 3)
(intern "*MODEM_STATE_ACTIVATING_DATA_CONTEXT*" (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(shadow '*MODEM_STATE_ACTIVATING_DATA_CONTEXT* (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(defconstant microstrain_inertial_msgs::RTKStatus::*MODEM_STATE_ACTIVATING_DATA_CONTEXT* 4)
(intern "*MODEM_STATE_CONFIGURING_SOCKET*" (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(shadow '*MODEM_STATE_CONFIGURING_SOCKET* (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(defconstant microstrain_inertial_msgs::RTKStatus::*MODEM_STATE_CONFIGURING_SOCKET* 5)
(intern "*MODEM_STATE_WAITING_ON_SERVER_HANDSHAKE*" (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(shadow '*MODEM_STATE_WAITING_ON_SERVER_HANDSHAKE* (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(defconstant microstrain_inertial_msgs::RTKStatus::*MODEM_STATE_WAITING_ON_SERVER_HANDSHAKE* 6)
(intern "*MODEM_STATE_CONNECTED_AND_IDLE*" (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(shadow '*MODEM_STATE_CONNECTED_AND_IDLE* (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(defconstant microstrain_inertial_msgs::RTKStatus::*MODEM_STATE_CONNECTED_AND_IDLE* 7)
(intern "*MODEM_STATE_CONNECTED_AND_STREAMING*" (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(shadow '*MODEM_STATE_CONNECTED_AND_STREAMING* (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(defconstant microstrain_inertial_msgs::RTKStatus::*MODEM_STATE_CONNECTED_AND_STREAMING* 8)
(intern "*CONNECTION_TYPE_NO_CONNECTION*" (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(shadow '*CONNECTION_TYPE_NO_CONNECTION* (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(defconstant microstrain_inertial_msgs::RTKStatus::*CONNECTION_TYPE_NO_CONNECTION* 0)
(intern "*CONNECTION_TYPE_CONNECTION_2G*" (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(shadow '*CONNECTION_TYPE_CONNECTION_2G* (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(defconstant microstrain_inertial_msgs::RTKStatus::*CONNECTION_TYPE_CONNECTION_2G* 2)
(intern "*CONNECTION_TYPE_CONNECTION_3G*" (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(shadow '*CONNECTION_TYPE_CONNECTION_3G* (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(defconstant microstrain_inertial_msgs::RTKStatus::*CONNECTION_TYPE_CONNECTION_3G* 3)
(intern "*CONNECTION_TYPE_CONNECTION_4G*" (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(shadow '*CONNECTION_TYPE_CONNECTION_4G* (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(defconstant microstrain_inertial_msgs::RTKStatus::*CONNECTION_TYPE_CONNECTION_4G* 4)
(intern "*CONNECTION_TYPE_CONNECTION_5G*" (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(shadow '*CONNECTION_TYPE_CONNECTION_5G* (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUS"))
(defconstant microstrain_inertial_msgs::RTKStatus::*CONNECTION_TYPE_CONNECTION_5G* 5)
(defclass microstrain_inertial_msgs::RTKStatus
  :super ros::object
  :slots (_gps_tow _gps_week _epoch_status _dongle_version _dongle_modem_state _dongle_connection_type _dongle_rssi _dongle_signal_quality _dongle_tower_change_indicator _dongle_nmea_timeout _dongle_server_timeout _dongle_rtcm_timeout _dongle_out_of_range _dongle_corrections_unavailable _gps_correction_latency _glonass_correction_latency _galileo_correction_latency _beidou_correction_latency _raw_status_flags ))

(defmethod microstrain_inertial_msgs::RTKStatus
  (:init
   (&key
    ((:gps_tow __gps_tow) 0.0)
    ((:gps_week __gps_week) 0)
    ((:epoch_status __epoch_status) 0)
    ((:dongle_version __dongle_version) 0)
    ((:dongle_modem_state __dongle_modem_state) 0)
    ((:dongle_connection_type __dongle_connection_type) 0)
    ((:dongle_rssi __dongle_rssi) 0)
    ((:dongle_signal_quality __dongle_signal_quality) 0)
    ((:dongle_tower_change_indicator __dongle_tower_change_indicator) 0)
    ((:dongle_nmea_timeout __dongle_nmea_timeout) nil)
    ((:dongle_server_timeout __dongle_server_timeout) nil)
    ((:dongle_rtcm_timeout __dongle_rtcm_timeout) nil)
    ((:dongle_out_of_range __dongle_out_of_range) nil)
    ((:dongle_corrections_unavailable __dongle_corrections_unavailable) nil)
    ((:gps_correction_latency __gps_correction_latency) 0.0)
    ((:glonass_correction_latency __glonass_correction_latency) 0.0)
    ((:galileo_correction_latency __galileo_correction_latency) 0.0)
    ((:beidou_correction_latency __beidou_correction_latency) 0.0)
    ((:raw_status_flags __raw_status_flags) 0)
    )
   (send-super :init)
   (setq _gps_tow (float __gps_tow))
   (setq _gps_week (round __gps_week))
   (setq _epoch_status (round __epoch_status))
   (setq _dongle_version (round __dongle_version))
   (setq _dongle_modem_state (round __dongle_modem_state))
   (setq _dongle_connection_type (round __dongle_connection_type))
   (setq _dongle_rssi (round __dongle_rssi))
   (setq _dongle_signal_quality (round __dongle_signal_quality))
   (setq _dongle_tower_change_indicator (round __dongle_tower_change_indicator))
   (setq _dongle_nmea_timeout __dongle_nmea_timeout)
   (setq _dongle_server_timeout __dongle_server_timeout)
   (setq _dongle_rtcm_timeout __dongle_rtcm_timeout)
   (setq _dongle_out_of_range __dongle_out_of_range)
   (setq _dongle_corrections_unavailable __dongle_corrections_unavailable)
   (setq _gps_correction_latency (float __gps_correction_latency))
   (setq _glonass_correction_latency (float __glonass_correction_latency))
   (setq _galileo_correction_latency (float __galileo_correction_latency))
   (setq _beidou_correction_latency (float __beidou_correction_latency))
   (setq _raw_status_flags (round __raw_status_flags))
   self)
  (:gps_tow
   (&optional __gps_tow)
   (if __gps_tow (setq _gps_tow __gps_tow)) _gps_tow)
  (:gps_week
   (&optional __gps_week)
   (if __gps_week (setq _gps_week __gps_week)) _gps_week)
  (:epoch_status
   (&optional __epoch_status)
   (if __epoch_status (setq _epoch_status __epoch_status)) _epoch_status)
  (:dongle_version
   (&optional __dongle_version)
   (if __dongle_version (setq _dongle_version __dongle_version)) _dongle_version)
  (:dongle_modem_state
   (&optional __dongle_modem_state)
   (if __dongle_modem_state (setq _dongle_modem_state __dongle_modem_state)) _dongle_modem_state)
  (:dongle_connection_type
   (&optional __dongle_connection_type)
   (if __dongle_connection_type (setq _dongle_connection_type __dongle_connection_type)) _dongle_connection_type)
  (:dongle_rssi
   (&optional __dongle_rssi)
   (if __dongle_rssi (setq _dongle_rssi __dongle_rssi)) _dongle_rssi)
  (:dongle_signal_quality
   (&optional __dongle_signal_quality)
   (if __dongle_signal_quality (setq _dongle_signal_quality __dongle_signal_quality)) _dongle_signal_quality)
  (:dongle_tower_change_indicator
   (&optional __dongle_tower_change_indicator)
   (if __dongle_tower_change_indicator (setq _dongle_tower_change_indicator __dongle_tower_change_indicator)) _dongle_tower_change_indicator)
  (:dongle_nmea_timeout
   (&optional __dongle_nmea_timeout)
   (if __dongle_nmea_timeout (setq _dongle_nmea_timeout __dongle_nmea_timeout)) _dongle_nmea_timeout)
  (:dongle_server_timeout
   (&optional __dongle_server_timeout)
   (if __dongle_server_timeout (setq _dongle_server_timeout __dongle_server_timeout)) _dongle_server_timeout)
  (:dongle_rtcm_timeout
   (&optional __dongle_rtcm_timeout)
   (if __dongle_rtcm_timeout (setq _dongle_rtcm_timeout __dongle_rtcm_timeout)) _dongle_rtcm_timeout)
  (:dongle_out_of_range
   (&optional __dongle_out_of_range)
   (if __dongle_out_of_range (setq _dongle_out_of_range __dongle_out_of_range)) _dongle_out_of_range)
  (:dongle_corrections_unavailable
   (&optional __dongle_corrections_unavailable)
   (if __dongle_corrections_unavailable (setq _dongle_corrections_unavailable __dongle_corrections_unavailable)) _dongle_corrections_unavailable)
  (:gps_correction_latency
   (&optional __gps_correction_latency)
   (if __gps_correction_latency (setq _gps_correction_latency __gps_correction_latency)) _gps_correction_latency)
  (:glonass_correction_latency
   (&optional __glonass_correction_latency)
   (if __glonass_correction_latency (setq _glonass_correction_latency __glonass_correction_latency)) _glonass_correction_latency)
  (:galileo_correction_latency
   (&optional __galileo_correction_latency)
   (if __galileo_correction_latency (setq _galileo_correction_latency __galileo_correction_latency)) _galileo_correction_latency)
  (:beidou_correction_latency
   (&optional __beidou_correction_latency)
   (if __beidou_correction_latency (setq _beidou_correction_latency __beidou_correction_latency)) _beidou_correction_latency)
  (:raw_status_flags
   (&optional __raw_status_flags)
   (if __raw_status_flags (setq _raw_status_flags __raw_status_flags)) _raw_status_flags)
  (:serialization-length
   ()
   (+
    ;; float64 _gps_tow
    8
    ;; uint16 _gps_week
    2
    ;; uint16 _epoch_status
    2
    ;; uint8 _dongle_version
    1
    ;; uint8 _dongle_modem_state
    1
    ;; uint8 _dongle_connection_type
    1
    ;; int8 _dongle_rssi
    1
    ;; uint8 _dongle_signal_quality
    1
    ;; uint8 _dongle_tower_change_indicator
    1
    ;; bool _dongle_nmea_timeout
    1
    ;; bool _dongle_server_timeout
    1
    ;; bool _dongle_rtcm_timeout
    1
    ;; bool _dongle_out_of_range
    1
    ;; bool _dongle_corrections_unavailable
    1
    ;; float32 _gps_correction_latency
    4
    ;; float32 _glonass_correction_latency
    4
    ;; float32 _galileo_correction_latency
    4
    ;; float32 _beidou_correction_latency
    4
    ;; uint32 _raw_status_flags
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _gps_tow
       (sys::poke _gps_tow (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; uint16 _gps_week
       (write-word _gps_week s)
     ;; uint16 _epoch_status
       (write-word _epoch_status s)
     ;; uint8 _dongle_version
       (write-byte _dongle_version s)
     ;; uint8 _dongle_modem_state
       (write-byte _dongle_modem_state s)
     ;; uint8 _dongle_connection_type
       (write-byte _dongle_connection_type s)
     ;; int8 _dongle_rssi
       (write-byte _dongle_rssi s)
     ;; uint8 _dongle_signal_quality
       (write-byte _dongle_signal_quality s)
     ;; uint8 _dongle_tower_change_indicator
       (write-byte _dongle_tower_change_indicator s)
     ;; bool _dongle_nmea_timeout
       (if _dongle_nmea_timeout (write-byte -1 s) (write-byte 0 s))
     ;; bool _dongle_server_timeout
       (if _dongle_server_timeout (write-byte -1 s) (write-byte 0 s))
     ;; bool _dongle_rtcm_timeout
       (if _dongle_rtcm_timeout (write-byte -1 s) (write-byte 0 s))
     ;; bool _dongle_out_of_range
       (if _dongle_out_of_range (write-byte -1 s) (write-byte 0 s))
     ;; bool _dongle_corrections_unavailable
       (if _dongle_corrections_unavailable (write-byte -1 s) (write-byte 0 s))
     ;; float32 _gps_correction_latency
       (sys::poke _gps_correction_latency (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _glonass_correction_latency
       (sys::poke _glonass_correction_latency (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _galileo_correction_latency
       (sys::poke _galileo_correction_latency (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _beidou_correction_latency
       (sys::poke _beidou_correction_latency (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint32 _raw_status_flags
       (write-long _raw_status_flags s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _gps_tow
     (setq _gps_tow (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; uint16 _gps_week
     (setq _gps_week (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _epoch_status
     (setq _epoch_status (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint8 _dongle_version
     (setq _dongle_version (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _dongle_modem_state
     (setq _dongle_modem_state (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _dongle_connection_type
     (setq _dongle_connection_type (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; int8 _dongle_rssi
     (setq _dongle_rssi (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _dongle_rssi 127) (setq _dongle_rssi (- _dongle_rssi 256)))
   ;; uint8 _dongle_signal_quality
     (setq _dongle_signal_quality (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _dongle_tower_change_indicator
     (setq _dongle_tower_change_indicator (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; bool _dongle_nmea_timeout
     (setq _dongle_nmea_timeout (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _dongle_server_timeout
     (setq _dongle_server_timeout (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _dongle_rtcm_timeout
     (setq _dongle_rtcm_timeout (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _dongle_out_of_range
     (setq _dongle_out_of_range (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _dongle_corrections_unavailable
     (setq _dongle_corrections_unavailable (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float32 _gps_correction_latency
     (setq _gps_correction_latency (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _glonass_correction_latency
     (setq _glonass_correction_latency (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _galileo_correction_latency
     (setq _galileo_correction_latency (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _beidou_correction_latency
     (setq _beidou_correction_latency (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint32 _raw_status_flags
     (setq _raw_status_flags (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get microstrain_inertial_msgs::RTKStatus :md5sum-) "da5543a2118eca78b75d2cf97686be1d")
(setf (get microstrain_inertial_msgs::RTKStatus :datatype-) "microstrain_inertial_msgs/RTKStatus")
(setf (get microstrain_inertial_msgs::RTKStatus :definition-)
      "# Possible values for dongle_modem_state
uint8   MODEM_STATE_OFF = 0
uint8   MODEM_STATE_NO_NETWORK = 1
uint8   MODEM_STATE_NETWORK_CONNECTED = 2
uint8   MODEM_STATE_CONFIGURING_DATA_CONTEXT = 3
uint8   MODEM_STATE_ACTIVATING_DATA_CONTEXT = 4
uint8   MODEM_STATE_CONFIGURING_SOCKET = 5
uint8   MODEM_STATE_WAITING_ON_SERVER_HANDSHAKE = 6
uint8   MODEM_STATE_CONNECTED_AND_IDLE = 7
uint8   MODEM_STATE_CONNECTED_AND_STREAMING = 8

# Possible values for dongle_connection_type
uint8   CONNECTION_TYPE_NO_CONNECTION = 0
uint8   CONNECTION_TYPE_CONNECTION_2G = 2
uint8   CONNECTION_TYPE_CONNECTION_3G = 3
uint8   CONNECTION_TYPE_CONNECTION_4G = 4
uint8   CONNECTION_TYPE_CONNECTION_5G = 5

float64 gps_tow
uint16  gps_week
uint16  epoch_status

uint8   dongle_version
uint8   dongle_modem_state      # Use in conjunction with MODEM_STATE_* values
uint8   dongle_connection_type  # Use in conjunction with CONNECTION_TYPE_* values
int8    dongle_rssi             # RSSI values are negative
uint8   dongle_signal_quality
uint8   dongle_tower_change_indicator
bool    dongle_nmea_timeout
bool    dongle_server_timeout
bool    dongle_rtcm_timeout
bool    dongle_out_of_range
bool    dongle_corrections_unavailable

float32 gps_correction_latency
float32 glonass_correction_latency
float32 galileo_correction_latency
float32 beidou_correction_latency


uint32  raw_status_flags        # Raw status flags value
")



(provide :microstrain_inertial_msgs/RTKStatus "da5543a2118eca78b75d2cf97686be1d")


