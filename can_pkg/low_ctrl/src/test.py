import can

# CAN bus setup (adjust channel and bustype as necessary for your hardware)
can_interface = 'can0'
bus = can.interface.Bus(channel=can_interface, bustype='socketcan', bitrate=500000)

# Message ID for PIT STOP ZONE
message_id = 0x125

def decode_value(data, start_bit, length, factor, offset=0, is_signed=False):
    # Extracting the specific bits from the data
    value = 0
    for i in range(length):
        byte_index = (start_bit + i) // 8
        bit_index = (start_bit + i) % 8
        bit_value = (data[byte_index] >> bit_index) & 1
        value |= bit_value << i
    
    # Apply sign if necessary
    if is_signed and (value & (1 << (length - 1))):
        value -= 1 << length
    
    # Apply factor and offset
    return value * factor + offset

def read_can_message():
    while True:
        message = bus.recv()
        if message.arbitration_id == message_id:
            data = message.data
            # Extract PITZONE_LAT and PITZONE_LONG from the data
            pitzone_lat = decode_value(data, 0, 32, 0.0000001)
            pitzone_long = decode_value(data, 32, 32, 0.0000001)
            print(f"PITZONE_LAT: {pitzone_lat}, PITZONE_LONG: {pitzone_long}")

try:
    read_can_message()
except KeyboardInterrupt:
    print("Program interrupted")
finally:
    bus.shutdown()
