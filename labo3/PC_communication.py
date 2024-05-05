import serial
import csv
import matplotlib.pyplot as plt

# Connect to Arduino serial port
ser = serial.Serial('/dev/pts/7', 115200)  

# Create CSV file for storing data
csv_file = open('temperature_data.csv', 'w', newline='')
csv_writer = csv.writer(csv_file)
csv_writer.writerow(['Setpoint', 'PID Output', 'Plant Output'])

# Initialize lists for storing data
setpoint_data = []
pid_output_data = []
plant_output_data = []
time_data = []

# Create subplots
fig, axs = plt.subplots(3, 1, figsize=(10,8), sharex=True)
fig.suptitle('Temperatura Control')


# Read and store data from Arduino
try:
    while True:
        line = ser.readline().decode().strip()
        if line:
            data = line.split(',')
            if len(data) == 3:
                setpoint = float(data[0])
                pid_output = float(data[1])
                plant_output = float(data[2])
                
                # Append data to lists
                setpoint_data.append(setpoint)
                pid_output_data.append(pid_output)
                plant_output_data.append(plant_output)
                time_data.append(len(plant_output_data))

                # Update subplots
                axs[0].clear()
                axs[0].plot(time_data, plant_output_data, label='Plant Output')
                axs[0].set_ylabel('Plant Output')
                axs[0].legend()
                
                axs[1].clear()
                axs[1].plot(time_data, pid_output_data, label='PID Output')
                axs[1].set_ylabel('PID Output')
                axs[1].legend()
                
                axs[2].clear()
                axs[2].plot(time_data, setpoint_data, label='Setpoint')
                axs[2].set_ylabel('Setpoint')
                axs[2].set_xlabel('Time')
                axs[2].legend()

                # Adjust plot limits
                axs[0].set_xlim(0, len(plant_output_data))
                axs[0].set_ylim(min(plant_output_data), max(plant_output_data))
                axs[1].set_ylim(min(pid_output_data), max(pid_output_data))
                axs[2].set_ylim(min(setpoint_data), max(setpoint_data))
                
                # Draw the plot
                plt.tight_layout()
                plt.draw()
                plt.pause(0.01)
                
            
                # Write data to CSV file
                csv_writer.writerow(data)
                
                # Print received data
                print(f"Setpoint: {setpoint}, PID Output: {pid_output}, Plant Output: {plant_output}")


except KeyboardInterrupt:
    print("Interrupted")
    ser.close()
    csv_file.close()
    plt.close()
