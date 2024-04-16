# README.md

Este proyecto consiste en la creación de un simulador de un semáforo electrónico utilizando el microcontrolador ATTiny4313 de Microchip y el simulador SimulIDE.

Se asume que el usuario utiliza el sistema operativo Linux, SimulIDE instalado y que ya cuenta con el compilador *avr* instalado. De no ser el caso, diríjase a las páginas: [SimulIDE: Downloads](https://simulide.com/p/downloads/) y [AVR GCC Compiler](https://www.nongnu.org/avr-libc/) y siga los pasos necesarios para instalar correctamente el simulador y el compilador.

Una vez instalados, diríjase a su directorio de preferencia y clone el presente repositorio con el siguiente comando: ```git clone https://github.com/dotjae/ie0624```.

De no tener el comando *git* instalado, ingrese el comando ```sudo apt-get install git``` en la terminal.

Una vez clonado el repositorio, diríjase a la carpeta ```ie0624/labo2/``` y, en la terminal, utilice los comandos:

```bash
$ make
$ make clean
```

Lo anterior compilará el archivo ```labo2.c``` a un archivo ```labo2.hex```, el cual podrá luego ser cargado al microcontrolador para que este cumpla su función. Los archivos adicionales creados se borrarán debido al comando de 'clean'.

Finalmente, abra el archivo ```labo2.simu``` en el simulador SimulIDE. Presione click derecho sobre el microcontrolador, seleccione la opción *Load Firmware* y seleccione el archivo ```.hex``` recién creado. 

Listo! 

Corra la simulación y presione el botón para observar el semáforo en acción.
