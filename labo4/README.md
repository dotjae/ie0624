# Laboratorio 4 - IE-0624

## Monitor de pendientes con STM32F429I-DISCOVERY

Esta guía proporciona los pasos necesarios para compilar, cargar y acceder a la consola de un monitor de pendientes implementado en la placa STM32F429I-DISCOVERY.

## Requisitos

- STM32F429I-DISCOVERY
- ST-Link
- Toolchain de GCC ARM (gcc-arm-none-eabi)
- minicom 
- git
- make

## Uso
### Compilación

<details><summary><b>Mostrar instrucciones</b></summary>

1. Clona el repoistorio:
    ```bash
    git clone https://github.com/dotjae/ie0624.git
    ```

2. Inicializa el submódulo de [libopencm3](https://github.com/libopencm3/libopencm3)
    ```bash
    git submodule init
    git submodule update
    ```

3. Navega al directorio `libopencm3`:
    ```bash
    cd libopencm3
    ```

4. Construye la librería:
    ```bash
    make
    ```

5. Navega al directorio `src`:
    ```bash
    cd ../src
    ```

6. Compila el código:
    ```bash
    make
    ```

</details>

### Subir el código 

<details><summary><b>Mostrar instrucciones</b></summary>

1. Conecte la tarjeta STM32F429I-DISCOVERY a la PC por medio del cable USB Mini-B.

2. Utiliza el comando `make flash` para subir el código al microcontrolador:
    ```bash
    make flash
    ```
</details>

### Acceso a la consola

<details><summary><b>Mostrar instrucciones</b></summary>

1. Accede a la interfaz gráfica de la configuración de la consola.
    ```bash
    sudo minicom -s
    ```

2. Escoja `Configuración de puerto serie` y asegurese que tenga la siguiente configuración. `/dev/port` corresponde al puerto serial en donde está conectado el microcontrolador, puedes revisar a cual puerto está conectado tu microcontrolador con el comando `ls /dev`.
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

3. Accede a la consola con `minicom`:
    ```bash
    sudo minicom
    ```

</details>

---
