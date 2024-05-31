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


# Callback when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    client.subscribe(topicreq)

# Callback when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(f"Received message on {msg.topic}: {str(msg.payload)}")

# Create an MQTT client instance
client = mqtt.Client()

# Authenticate
client.username_pw_set(username)

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
data_dict = {'temp': 0, 'x':0, 'y':0, 'z':0, 'bat':0, 'low_bat':"", "deg_alert": ""}
deg_alert = False

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
            x = float(dsplit[0])
            y = float(dsplit[1])
            z = float(dsplit[2])
            temp = int(dsplit[3])
            batt = float(dsplit[4])*100/9
            deg_alert = True if x > 5 or y > 5 or z > 5 else False



            # Assign elements to dictionary
            data_dict['x'] = x
            data_dict['y'] = y
            data_dict['z'] = z
            data_dict['temp'] = temp
            data_dict['bat'] = batt
            data_dict['low_bat'] = "Full Battery" if batt >= 90 else "Low Battery" if batt < 80 else "Medium Battery" 
            data_dict['deg_alert'] = "Danger!" if deg_alert else "All good."           
            
            # Publish the telemetry data
            client.publish(topic, json.dumps(data_dict))
            print(f"Sent telemetry data: {data_dict}")

            # Wait a small period before sending the next data
            time.sleep(0.1)
        
except KeyboardInterrupt:
    print("\nExiting program.")
finally:
    ser.close()
    print("Serial port closed.")

# Stop the loop and disconnect
client.loop_stop()
client.disconnect()


