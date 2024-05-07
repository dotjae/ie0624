from optparse import OptionParser
import serial
import csv
import os
import matplotlib.pyplot as plt

# Fancy arguments
parser = OptionParser()
parser.add_option("--ser", dest="serial_port")
parser.add_option("--csv", dest="csv_file")
parser.add_option("--plt", dest="plot_name")

(options, args) = parser.parse_args()

# Variables out of fancy arguments
port = options.serial_port
output_file = options.csv_file
plot = options.plot_name

# Connect to Arduino serial port
ser = serial.Serial(f'{port}', 115200)

if not os.path.exists('csv_files'):
    # Create the directory
    os.makedirs('csv_files')
    
if not os.path.exists('plots'):
    # Create the directory
    os.makedirs('plots')

# Create CSV file for storing data
csv_file = open(f'csv_files/{output_file}.csv', 'w', newline='')
csv_writer = csv.writer(csv_file)
csv_writer.writerow(['Setpoint', 'PID Output', 'Plant Output'])

# Initialize lists for storing data
setpoint_data = []
pid_output_data = []
plant_output_data = []
time_data = []

# Create subplots
fig, axs = plt.subplots(3, 1, figsize=(10,8), sharex=True)
fig.suptitle('Control de Temperatura para la Incubadora de Huevos')

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
                plt.pause(0.00000000001)
                
            
                # Write data to CSV file
                csv_writer.writerow(data)
                
                # Print received data
                print(f"Setpoint: {setpoint}, PID Output: {pid_output}, Plant Output: {plant_output}")


except KeyboardInterrupt:
    print("Interrupted")
    ser.close()
    csv_file.close()
    plt.savefig(f'plots/{plot}.png')
    plt.close()
