# README.md

Este proyecto consiste en la creación de un simulador de dado electrónico usando el microcontrolador PIC12F683 de Microchip, utilizando el simulador SimulIDE.

Se asume que el usuario utiliza el sistema operativo Linux, SimulIDE instalado y que ya cuenta con el compilador *sdcc* instalado. De no ser el caso, diríjase a las páginas: [SimulIDE: Downloads](https://simulide.com/p/downloads/) y [SDCC Manual](https://sdcc.sourceforge.net/doc/sdccman.pdf) y siga los pasos necesarios para instalar correctamente el simulador y el compilador.

Una vez instalados, diríjase a su directorio de preferencia y clone el presente repositorio con el siguiente comando: ```git clone https://github.com/dotjae/ie0624```.

De no tener el comando *git* instalado, ingrese el comando ```sudo apt-get install git``` en la terminal.

Una vez clonado el repositorio, diríjase a la carpeta ```ie0624/labo1/``` y, en la terminal, utilice los comandos:

```bash
$ make
$ make clean
```

Lo anterior compilará el archivo ```labo1.c``` a un archivo ```labo1.hex```, el cual podrá luego ser cargado al microcontrolador para que este cumpla su función. Los archivos adicionales creados se borrarán debido al comando de 'clean'.

Finalmente, abra el archivo ```labo1.simu``` en el simulador SimulIDE. Presione click derecho sobre el microcontrolador, seleccione la opción *Load Firmware* y seleccione el archivo ```.hex``` recién creado. 

Listo! 

Corra la simulación y presione el botón para observar el dado en acción.
