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
    serial_port = '/dev/ttyACM12'  # Replace with your actual serial port
    baud_rate = 115200  # This value is actually ignored for USB CDC but is required to open the port

    read_from_serial(serial_port, baud_rate)

