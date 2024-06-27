# Laboratorio 5 - IE-0624

## Detector de máscara facial con kit de Tiny Machine Learning - Arduino Nano 33 BLE Lite

Esta guía proporciona los pasos necesarios para compilar, cargar, y utilizar un detector
de máscara facial implementado con el kit de Tiny Machine Learning de Arduino. 

## Requisitos

- Kit de Tiny Machine Learning de Arduino
- Arduino IDE (2.0.1) y soporte Arduino Mbed OS Nano boards (3.4.1)
- Arduino - CLI
- Bibliotecas Arduino_TensorFlowLite y Arduino:LSM9DSI
- minicom
- git

## Uso
### Compilación

<details><summary><b>Mostrar instrucciones</b></summary>

1. Clona el repoistorio:
    ```bash
    git clone https://github.com/dotjae/ie0624.git
    ```

2. Navega al directorio `nano_ble33_sense_camera`:
    ```bash
    cd ie0624/labo5/nano_ble33_sense_camera
    ```

3. Compila el código:
    ```bash
    arduino-cli compile --fqbn arduino:mbed_nano:nano33ble ./nano_ble33_sense_camera.ino --output-dir .
    ```

</details>

### Subir el código 

<details><summary><b>Mostrar instrucciones</b></summary>

1. Conecte el Arduino Nano BLE 33 Lite y la cámara OV7675 al shield proporcionado por el kit de Tiny Machine Learning.

2. Conecte la tarjeta Arduino Nano BLE 33 Lite la PC por medio del cable USB Mini-B.

3. Utilice el siguiente comando para subir el código al microcontrolador. Asegurese de que utilice el puerto serial correcto para cargar el firmware. Puede revisar donde está conectado su microcontrolador con el comando `ls /dev`.
    ```bash
    arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:mbed_nano:nano33ble --input-file nano_ble33_sense_camera.ino.hex
    ```
</details>

### Acceso a la consola

<details><summary><b>Mostrar instrucciones</b></summary>

1. Accede a la interfaz gráfica de la configuración de la consola.
    ```bash
    sudo minicom -s
    ```

2. Escoja `Configuración de puerto serie` y asegurese que tenga la siguiente configuración. `/dev/port` corresponde al puerto serial en donde está conectado el microcontrolador.
```
    +-----------------------------------------------------------------------+
    | A - Dispositivo Serie      : /dev/port                                |
    | B - Localización del Fichero de Bloqueo : /var/lock                   |
    | C - Programa de Acceso           :                                    |
    | D - Programa de Salida             :                                  |
    | E - Bps/Paridad/Bits             : 115200 8N1                         |
    | F - Control de Flujo por Hardware: Sí                                 |
    | G - Control de Flujo por Software: No                                 |
    | H -     RS485 Enable      : No                                        |
    | I -   RS485 Rts On Send   : No                                        |
    | J -  RS485 Rts After Send : No                                        |
    | K -  RS485 Rx During Tx   : No                                        |
    | L -  RS485 Terminate Bus  : No                                        |
    | M - RS485 Delay Rts Before: 0                                         |
    | N - RS485 Delay Rts After : 0                                         |
    |                                                                       |
    |    ¿Qué configuración alterar?                                        |
    +-----------------------------------------------------------------------+
```

3. Regrese a la pantalla principal de `minicom` y seleccione `Salir` para acceder a la terminal serial. En esta interfaz se muestran los resultados de la inferencia del modelo, para los casos en que se detecta una cara con máscara, una cara sin máscara, o no se detecta una cara. 

</details>

### Clasificación de máscara facial
<details><summary><b>Mostrar instrucciones</b></summary>

1. Apunte la cámara OV7675 hacia una cara o cualquier otro objeto.

2. Espere a que se realice la inferencia. Cuando la inferencia sea realizada, se prenderá el LED RGB en la placa Arduino 33 BLE Lite. Se tendrán 3 casos dependiendo del color del LED que se encienda:

<center>

| Color del LED RGB   | Detección      |
|:-------------------:|:--------------:|
| Rojo                | Sin máscarilla |
| Verde               | Con mascarilla |
| Azul                | No hay cara    |

</center>

</details>

