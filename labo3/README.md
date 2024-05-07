# Laboratorio 3 - IE-0624

## Simulador de Incubadora de Huevos Automática con Arduino UNO

Este directorio contiene el código fuente necesario para correr la simulación de la incubadora de huevos automática diseñada utilizando el microcontrolador ArduinoUNO, simulado en el simulador SimulIDE.

La incubadora simulada funciona de la siguiente manera:

* El usuario, por medio de un potenciómetro, podrá ajustar la temperatura deseada dentro de la incubadora. Esta temperatura debe encontrarse en el rango de 30 a 42 grados Celsius. Se cuenta con 3 luces LED las cuales indican si la temperatura se encuentra abajo, dentro o arriba del rango permitido.
* Por medio de una función llamada ```simPlanta()```, el Adruino se encargará de obtener y simular el calor requerido para realizar los cambios necesarios a la temperatura de la incubadora.
* Por medio de un controlador PID (Proporcional, Integrativo, Derivativo), el Arduino UNO se encargará de ajustar la temperatura actual a la ingreseada por el usuario de acuerdo al resultado de la simulación de la planta y la temperatura deseada.
* Finalmente, el Arduino se encarga de enviar los datos de Setpoint (temperatura deseada), Salida del PID y Salida de la Planta a través del puerto serial UART el cual se conecta a una computadora personal en la cual un script de Python se encarga de almacenar y graficar los datos enviados por el microcontrolador. Detalles del uso de esta funcionalidad se delinearán más adelante.

## Instalación

Asegúrese de tener instalado el simulador SimulIDE (LINK) y el entorno de desarrollo ArduinoIDE (LINK), o bien algún compilador de Arduino a hexadecimal. Los detalles de esta instalación asumen el uso de un sistema operativo de la familia Linux.

Una vez instalado todo, descargue este repositorio por medio del comando en terminal

 ```git clone https://github.com/dotjae/ie0624``` 
 
 y diríjase al directorio **labo3** con el comando ```cd labo3```. 

Corra el simulador SimulIDE y cargue el archivo **incubadora.simu**. Luego, cargue el archivo **incubadora.ino.hex** y carguelo a la placa ArduinoUNO del simulador.

Corra la simulación y ajuste la temperatura al ajustar el potenciómetro que está al lado del microcontrolador. Los valores de la temperatura ingresada, temperatura actual, y potencia generada por el controlador se pueden apreciar en la pantalla LCD que se observa al lado de la placa. Para utilizarla es necesario bajar el switch con la etiqueta _LCDEN_.

### CSV y Gráficas

El script de Python ubicado en este directorio llamado ```serial_communication.py``` se encarga de almacenar los datos de Setpoint (temperatura deseada), Salida del PID y Salida de la Planta en un archivo CSV con un nombre ingresado por el usuario. De igual manera grafica en tiempo real los datos enviados por el microcontrolador y los guarda en un archivo PNG con un nombre definido por el usuario al terminar el proceso del script.

Para poder comunicarse con el puerto serial de la computadora por medio del simulador, es necesario simular un puerto serial de entrada y uno de salida. Para realizar esto utilice el comando:

```socat -d -d pty,raw,echo=0 pty,raw,echo=0```

Preste mucha atención a la ubicación de uno de los puertos creados (por ejemplo: ```'/dev/pts/7'```). Ahora diríjase al simulador y abra el puerto serial del Arduino haciendo click derecho en él y seleccionando la opción "Open Serial Port". Una vez que el puerto serial UART1 se abra, diríjase a sus propiedades y en el Nombre coloque la dirección de el puerto de salida creado. Para habilitar la comunicación serial es necesario activar el switch con la etiqueta _PC_ y asegurarse que el puerto UART se encuentre abierto (presionar Open en el puerto).


En su terminal, mientras la simulación esté corriendo y el switch de PC esté activado, corra el comando: 

```python3 serial_communication.py --ser $PORT_PATH --csv $CSV_FILE --plt $PLOT_FILE``` 

En donde **$PORT_PATH** es la ubicación del puerto creado que no utilizó para el Arduino (por ejemplo: ```dev/pts/6```), **$CSV_FILE** es el nombre del archivo CSV con los datos obtenidos en la simulación; y **$PLOT_FILE** es el nombre del archivo PNG en donde desea guardar la gráfica creada.

Luego de terminar la ejecución, una imagen con tres subgráficos de los datos del Setpoint, Salida del PID y Salida de la Planta en el tiempo, y con el nombre ingresado por el usuario, se almacenará en un directorio llamado ```plots```. De igual forma el archivo CSV con los datos obtenidos se encontrará en un directorio llamado ```csv_files```.

Para terminar el proceso utilice ```Ctrl+C```.
