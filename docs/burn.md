# Burn the Optiboot bootloader onto a board

## Using Atmel-ICE
```
# 0. Connect the Atmel-ICE to the Uno. ICSP cable, cable pin 1 opposite in top row to Uno pin 1, USB to Atmel-ICE, USB to Uno
# 1. Test the connection
avrdude -p m328p -P usb  -c atmelice_isp -t
part
quit
# 2. Set fuses and lock bits to enable re-loading of boot loader
avrdude -p atmega328p  -c atmelice_isp -P usb -e -U lock:w:0x3f:m -U efuse:w:0x05:m -U hfuse:w:0xDE:m -U lfuse:w:0xFF:m
# 3. Copy hex file to desktop
cp /Users/lkoepsel/Documents/optiboot/optiboot/bootloaders/optiboot/optiboot_atmega328.hex ~/Desktop/
# 4. Burn Arduino bootloader & set lock bits to lockbootloader section
avrdude -p atmega328p  -c atmelice_isp -P usb -U flash:w:./optiboot_atmega328.hex -U lock:w:0x0f:m
```

## Using SNAP

```
# 0. Connect the SNAP to the Uno. ICSP cable, cable pin 1 to top row to Uno pin 1, USB to SNAP, USB to Uno
# 1. Test the connection
avrdude -p m328p -P usb  -c snap_isp -t
part
quit
# 2. Set fuses and lock bits to enable re-loading of boot loader
avrdude -p atmega328p  -c snap_isp -P usb -e -U lock:w:0x3f:m -U efuse:w:0x05:m -U hfuse:w:0xDE:m -U lfuse:w:0xFF:m
# 3. Copy hex file to desktop
cp /Users/lkoepsel/Documents/optiboot/optiboot/bootloaders/optiboot/optiboot_atmega328.hex ~/Desktop/
# 4a. Burn Arduino bootloader & set lock bits to lockbootloader section
avrdude -p atmega328p  -c snap_isp -P usb -U flash:w:./optiboot_atmega328.hex -U lock:w:0x0f:m
# 4b. Burn FlashForth & set lock bits to lockbootloader section
avrdude -p atmega328p  -c snap_isp -P usb -U flash:w:./328-16MHz-38400.hex -U lock:w:0x0f:m
```

