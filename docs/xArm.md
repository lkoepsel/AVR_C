# xArm Commands

This interface is closely modeled after the great work by Chris Courson, [here](https://github.com/ccourson/xArmServoController). His work served as inspiration and guidance in created a similar work, except this one is exclusively **C99 C**.

I also took the approach to use the Lewan-Soul/HiWonder board as a primitive controller and developed the control intelligence in the Uno board. This gives greater programmatic control to the C programmer, however, it does require far more programming work to do so. This is a traditional programming dilemma...*the greater the control the program provides, the greater the work required*.
## Vector Approach
The vector approach is to make the assumption that an array of six joint positions, defines a specific point for the xArm. There also definitions based on this approach:
* *vector0 (V0)* - is considered the base or safe resting position of the xArm. It is determined by experimentation, and is considered the first position from which the xArm will begin to move.
* *vector sequence* - is a series of vectors, starting with *V0*, which define a specific course of action such as picking up a marker and placing it elsewhere.
## Structure
The *AVR_C xArm Commander* program utilizes three files to create an interface, it is similar to many of the files in the *examples* folder.:

* *xArm_Commander* - the main.c program which is the main interface to the xArm API. It drives a command-based interface.
* *xArm.h* - header program for the xArm primitives file, *xArm.c*
* *xArm.c* - xArm primitives file, contains similar (if not the same) routines as those in the *Coursen xArm Arduino src* file.

## Commands
* *move joint position* - move *joint* (1-6) to *position* (1 - 999)
* *pos joint* - return the position of joint
* *add joint position* - the **same as the move** command, except it is added to a *vector* of moves which will be executed sequentially by *exec*. A *vector* can contain up to 6 moves, one for each joint, and is expected to express a point in space by the xArm. At this time, there is only one vector.
* *show* - show list of commands to be executed by *exec*
* *exec* - execute list of commands
* *reset* - reset list of commands to be empty
* *volt* - return the voltage of the battery
* *beep* - cause the arm to beep

## Important Considerations
In the effort to not damage the xArms, please follow the rules:
1. Always perform a *pos* command on a joint, prior to first moving it
1. Move in small increments, test direction before attempting a substantive move

## New Image Process (for class project)
This process will ensure you are in the correct folder, it will fetch/merge the latest code from this repository, then compile/link/upload the new code to the Uno:
```bash
cd
cd xArm/AVR_C
git fetch
git merge
cd examples/xArm_Commander
make flash
tio -b 9600 /dev/ttyUSB0
```

## Communications
This application has been designed to have two communication or serial ports, one uses the UART of the *ATmega328P* and the other is a software serial port which can be on any two of the digital pins. For simplicity, I use pins 2 and 3, right next to the pins 0 and 1, which comprise the Uno (ATmega328) serial port. 
### Adafruit Blue USB Type A to 4 Wire Red/Black/Green/White
* red **power** **NO CONNECTION**
* black **ground**
* white **RX** into USB port
* green **TX** out of the USB port.

### Connections
* **Uno Pin 0** - *UART RX* to 2nd pin from the left on the xArm serial port (*TX*)
* **Uno Pin 1** - *UART TX* to 3rd pin from the left on the xArm serial port (*RX*)
* **Uno Pin 2** - *User designated RX* to a USB to serial cable (*TX*)
* **Uno Pin 3** - *User designated TX* to a USB to serial cable (*RX*)
* **Uno Pin GND** - Connect to GND on UART cable (black wire)
* **Uno Pin GND** - Connect to GND on serial cable (black wire)

### USB to Serial Cables
I've tested both the [Adafruit Blue USB Type A to 4 Wire Red/Black/Green/White](https://www.adafruit.com/product/954) and the [Adafruit FTDI Friend USB Mini](https://www.adafruit.com/product/284) and they both work well.

### User-designated Pins
To use two different pins as the *soft serial port*, change the pin numbers in *soft_serial.h*:

```C
#define SOFT_BAUD 9600
#define BIT_DURATION (1000000 / SOFT_BAUD) // Bit duration in microseconds
#define CR 13

#define SOFT_RX_PIN PIND2 // Define the RX pin
#define SOFT_TX_PIN PIND3 // Define the TX pin
``` 

If running in the command line, I use *tio*, as my serial program. If I'm able to use a *GUI* its always *CoolTerm*.

As shown, you can also change the baud rate, I've had success to *28800* baud.

## Control Example
```bash
tio usb0
[14:08:15.422] tio v3.3
[14:08:15.422] Press ctrl-t q to quit
[14:08:15.429] Connected to /dev/ttyUSB0

xArm Commander: Enter commands to interact w xARM
Command received: pos 1
1 Servo position: 250
Success
Command received: move 1 300
Success
Command received: pos 5
5 Servo position: 704
Success
Command received: move 5 650
Success
Command received: pos 4
4 Servo position: 1022
Success
Command received: move 4 900
Success
Command received: add 4 800
Success
Command received: add 5 600
Success
Command received: pos 3
3 Servo position: 119
Success
Command received: move 3 200
Success
Command received: add 3 300
Success
Command received: move 1 200
Success
Command received: add 1 300
Success
Command received: show
0 move 4 800
1 move 5 600
2 move 3 300
3 move 1 300
Success
Command received: exec
0 move 4 800
1 move 5 600
2 move 3 300
3 move 1 300
Success
Command received: reset
Success
Command received: show
Success

[14:10:44.521] Disconnected
```

## Test Protocol

1. Place xArm in Vector 0 (*V0*), configuration using *move* commands
1. Create a vector using *add* commands, which would replicate *V0*.
1. Use *show* to confirm the vector is correct
1. Cycle the xArm power
1. Use the *exec* command to execute the vector
1. Perform a *pos* commmand on all joints to ensure they are in the correct spot