import paho.mqtt.client as mqtt
import json
import time
import serial
import sys

PORT = sys.argv[1]

# Broker details
broker = "iot.eie.ucr.ac.cr"
port = 1883
topic = "v1/devices/me/telemetry"
topicreq = "v1/devices/me/attributes/request/1/"
username = "urtcz88waqo9wjzbknpa"
password = ""

# Callback when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    client.subscribe(topicreq)

# Callback when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(f"Received message on {msg.topic}: {str(msg.payload)}")

# Create an MQTT client instance
client = mqtt.Client()

# Set username and password
client.username_pw_set(username, password)

# Assign event callbacks
client.on_connect = on_connect
client.on_message = on_message

# Connect to the broker
client.connect(broker, port, 60)

# Start the loop
client.loop_start()

# Connect to STM serial port
ser = serial.Serial(f'{PORT}', 115200)

# Dictionary to send data to ThingsBoard
data_dict = {'temp': 0, 'x':0, 'y':0, 'z':0, 'bat':0}

try:
    while True:
        if ser.in_waiting > 0:
            try:
                data = ser.readline().decode('utf-8')
            except UnicodeDecodeError:
                continue
            
            # Array of each received element
            dsplit = data.split()
            
            # Check array's length
            if (len(dsplit)) != 5:
                continue

            # Element variables
            x = dsplit[0]
            y = dsplit[1]
            z = dsplit[2]
            temp = dsplit[3]
            batt = dsplit[4]

            # Assign elements to dictionary
            data_dict['x'] = float(x)
            data_dict['y'] = float(y)
            data_dict['z'] = float(z)
            data_dict['temp'] = int(temp)
            data_dict['bat'] = int(batt)        
           
            # Publish the telemetry data
            client.publish(topic, json.dumps(data_dict))
            print(f"Sent telemetry data: {data_dict}")

            # Wait a small period before sending the next data
            time.sleep(0.5)
        
except KeyboardInterrupt:
    print("\nExiting program.")
finally:
    ser.close()
    print("Serial port closed.")

# Stop the loop and disconnect
client.loop_stop()
client.disconnect()


