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

### Subir el código y acceso a consola

1. Utiliza el comando `make flash` para subir el código al microcontrolador:
    ```bash
    make flash
    ```

2. Configura la consola con `minicom`:
    ```bash
    sudo minicom -b 115200 -o -D /dev/ttyACM0M -8 -h
    ```

3. Accede a la consola con `minicom`:
    ```bash
    sudo minicom
    ```

4. Para salir de la consola, presiona las teclas `CTRL+Shift+A+X`.

---
