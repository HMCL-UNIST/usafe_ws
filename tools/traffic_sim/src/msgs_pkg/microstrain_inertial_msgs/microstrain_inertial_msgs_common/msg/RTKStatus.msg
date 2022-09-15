# Possible values for dongle_modem_state
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