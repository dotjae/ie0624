# Proyecto de microcontroladores

## microPong con STM32F429I-DISCOVERY

Esta guía proporciona los pasos necesarios para compilar y cargar una adaptación del juego Pong al microcontrolador STM32429I-DISCOVERY

## Esquemático

Para poder usar los controles del juego, debe construir el siguiente esquemático:

<center>
![Alt text](./esquematico.jpg)
</center>

En la siguiente tabla, se muestran los controles para ambos jugadores:

<center>
| Pin                 | Control                  |
|:-------------------:|:------------------------:|
| PA0                 | Arriba J1/Selección Menu |
| PA1                 | Abajo J2                 |
| PA5                 | Arriba J2                |
| PA7                 | Abajo J2                 |
</center>

## Requisitos

- STM32F429I-DISCOVERY
- ST-Link
- Toolchain de GCC ARM (gcc-arm-none-eabi)
- git
- make

## Uso
### Compilación

<details><summary><b>Mostrar instrucciones</b></summary>

1. Clona el repoistorio:
    ```bash
    git clone https://github.com/dotjae/ie0624.git
    ```

2. Navege al directorio `ie0624`
    ```bash
    cd ie0624
    ```

3. Inicializa el submódulo de [libopencm3](https://github.com/libopencm3/libopencm3)
    ```bash
    git submodule init
    git submodule update
    ```

4. Navega al directorio `libopencm3`:
    ```bash
    cd libopencm3
    ```

5. Construye la librería:
    ```bash
    make
    ```

6. Navega al directorio `src`:
    ```bash
    cd ../src
    ```

7. Compila el código:
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

---
