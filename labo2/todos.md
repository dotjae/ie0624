# Laboratorio #2: GPIOs, Timers y FSM

## Instrucciones Generales

- [ ] Utilizar git
- [ ] Utilizar capturas de pantalla para demostrar la funcionalidad en el informe (las capturas de pantalla deben mostrar solo la información pertinente al paso correspondiente.)
- [ ] Entregar un archivo comprimido que incluya:
  - [ ] Un directorio llamado `informe` con los archivos necesarios para generar el PDF del informe (.tex, imágenes, código, etc.).
  - [ ] Un directorio llamado `src` con los archivos de código fuente.


## Documentación

- [ ] Documentar los pasos realizados con capturas de pantalla en el informe final.
- [ ] Incluir descripciones de cada paso en el informe final.

## Desarrollo del Proyecto

- [ ] Desarrollar un cruce de semáforos simplificado utilizando leds, botones y el microcontrolador ATtiny4313.
- [ ] Utilizar al menos seis leds (LDPV, LDVD, LDPP, LDPD) para representar los semáforos vehiculares y peatonales.
- [ ] Utilizar el botón B1 y/o B2 para la activación de las luces peatonales.
- [ ] Cumplir con el diagrama de temporización proporcionado en la figura 2 del documento.
- [ ] Asignar funcionalidades específicas a cada led:
  - [ ] LDPV: Paso de vehículos.
  - [ ] LDPP: Paso de peatones.
  - [ ] LDVD: Vehículos detenidos.
  - [ ] LDPD: Peatones detenidos.
- [ ] Permitir la presión del botón B1 o B2 durante el funcionamiento de LDPV.
- [ ] Mantener LDPV encendido hasta que terminen los 10 segundos, incluso si se presiona el botón.
- [ ] Utilizar temporizadores del microcontrolador para la temporización de los leds.
- [ ] Realizar la lectura de los botones y del fin de cuenta del Timer mediante interrupciones (importante).
- [ ] Considerar agregar leds adicionales para representar más adecuadamente los colores de los semáforos (opcional).
