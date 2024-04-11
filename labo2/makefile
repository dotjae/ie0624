attiny:
	avr-gcc -mmcu=attiny4313 -DF_CPU=1000000 -Os -o labo2.elf labo2.c
	avr-objcopy -O ihex -R .eeprom labo2.elf labo2.hex

clean: 
	rm *.elf