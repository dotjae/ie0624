import argparse
import serial
import time

def read_from_serial(port, baudrate):
    ser = serial.Serial(port, baudrate, timeout=1)
    total_bytes = 0
    start_time = time.time()
    
    try:
        while True:
            if ser.in_waiting > 0:
                data = ser.read(ser.in_waiting)
                total_bytes += len(data)
                elapsed_time = time.time() - start_time
                if elapsed_time > 0:
                    print(f"Throughput: {total_bytes / elapsed_time / 1024:.2f} KB/s", end="\r")
    except KeyboardInterrupt:
        print("\nExiting...")
    finally:
        ser.close()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Read data from a specified serial port.')
    parser.add_argument('port', type=str, help='Serial port identifier (e.g., /dev/ttyACM0)')
    parser.add_argument('--baud', type=int, default=115200, help='Baud rate (default: 115200)')
    
    args = parser.parse_args()
    
    serial_port = args.port
    baud_rate = args.baud

    read_from_serial(serial_port, baud_rate)
