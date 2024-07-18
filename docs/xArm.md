# xArm Commander

This document describes how to use the *examples/xArm_Commander*, a serial, robototic command interpreter for the [*Lewan-Soul/HiWonder xArm Robotic Arms*](https://www.amazon.com/LewanSoul-xArm-1S-Programming-Educational/dp/B0CHY63V9P?th=1). It provides the ability to enter commands for the xArm, via a serial port, then have the xArm perform movements, based on the commands.

This interface is closely modeled after the great work by Chris Courson, [here](https://github.com/ccourson/xArmServoController). His work served as inspiration and guidance in created a similar work, except this one is exclusively **C99 C**. *Thank you, Chris.*

I also took the approach to use the *Lewan-Soul/HiWonder Bus Servo Controller Communication Board* as a primitive API and developed the control intelligence in the Uno board. This gives greater programmatic control to the C programmer, however, it does require far more programming work to do so. This is a traditional programming dilemma...*the greater the control the program provides, the greater the work required*.
## Installation
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

You can also perform a *git log* to confirm the log message at the top of the log trail is the same as the message on the github repository.

## Vector Approach
The vector approach is to make the assumption that an array of six joint (or servo) positions, define a specific point for the xArm. Here are definitions based on this approach:
* *vector* - a set of specific positions for each servo, with the xARm, there are six servos.
* *vector0 (v0)* - is considered the base or safe resting position of the xArm. It is determined by experimentation, and is considered the first position from which the xArm will begin to move.
* *vector sequence* - is a series of vectors, starting with *V0*, which define a specific course of action such as picking up a marker and placing it elsewhere.
* *vn: prompt* - indicates which vector your are modifying. All of the vector commands, *add, show, exec, reset*, will work on the *n* indicated vector. For example, at startup, the prompt is *v0:*, which indicates all changes will be applied to the base vector or vector 0.
* *vect n* is the set vector command. This will set the vector to the *nth* vector and all changes will be made to it, until a new *vect n* command.
* *vecs* is the display vector command. This will display all of the vectors, aligned by joint, on your terminal.
* *perf* performs all of the vectors in order (0-9). At present it has a 1 second delay between vectors until it has been fully tested.

There was a programming choice I needed to make, which was whether or not, to allow joint movement to be re-ordered. By this, I mean, within a vector, can *joint 3* move prior to *joint 1*or *joint 5* move prior to *joint 2*? For example, this becomes important when attempting to open the pincher (*joint 1*) after rotating to a new position (*joint 6*).

For this iteration, I decided that joint movement would need to go in sequential order. Which means, *joint 1* will **always** move first, then *joint 2*, *3* and so on. If a higher number joint needs to move prior to its lower number counterpart, then have the lower numbered joint *skip* by leaving it's position as a 0. You may also enter *skip n* to specifically set the joint to be skipped. 

In summary, think in terms of vectors and not specific joint movements per vector. Each vector will perform a specific action, and in the case of higher numbered joints, they might need to have a vector specific to their action.

## Commands
* **move** *joint position - move *joint* (1-6) to *position* (1 - 999)
* **pos** *joint* - return the position of *joint* (1-6)
* **vect** *n* - set the active vector, (0-9)
* **add** *joint position* - the **same as the move** command, except it is added to a *vector* of moves which will be executed sequentially by *exec*. A *vector* can contain up to 6 moves, one for each *joint*, and is expected to express a point in space by the xArm. At this time, there five vectors, *v0* - *v4*.
* **show** - show active vector joint move list to be executed by *exec*
* **vecs** - show complete matrix of moves, each joint is a line and each column is a vector
* **perf** - perform all 10 vectors (0-9) with a one second delay between each vector move.
* **exec** - execute active vector joint moves
* **reset** - reset active vector joint moves to be empty
* **all** - show all positions of servos
* **save** - save to EEPROM all 10 vectors, verified on save
* **load** - load from EEPROM all 10 vectors, verified on load
* **skip** - set the position of a joint to 0, in essence, skipping it on moves
* **volt** - return the voltage of the battery
* **beep** - cause the arm to beep

**Command entry doesn't allow for backspace or any editing commands.** It is recommended that once you realize you've made a mistake, you either add a series of letters which will make the command illegal or hit enter if the command isn't fully-formed. 

# Important Considerations
In the effort to not damage the xArms, please follow the rules:
1. Always perform a *pos* command on a joint, prior to moving it. This will ensure you know the position of the joint.
2. Move in small increments, test the direction, before attempting a substantive move. For example, if the position is *320*, move to position *300*, to confirm the direction is what you expect, prior to moving *100* or more steps.

## Test Protocol
1. Place xArm in Vector 0 (*V0*), configuration using *move* commands
1. Create a vector using *add* commands, which would replicate *V0*.
1. Use *show* to confirm the vector is correct
1. Cycle the xArm power
1. Use the *exec* command to execute the vector
1. Perform an *all* commmand to show all joints are in the correct spot

## Program Structure
The *AVR_C xArm Commander* program utilizes three files to create an interface, it is similar to many of the files in the *examples* folder.:

* *xArm_Commander* - the main.c program which is the main interface to the xArm API. It drives a command-based interface.
* *xArm.h* - header program for the xArm primitives file, *xArm.c*
* *xArm.c* - xArm primitives file, contains similar (if not the same) routines as those in the *Coursen xArm Arduino src* file.

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
## Debugging Steps
Here are a few steps to ensure you are successful with connecting to the Uno and xArm.
1. Confirm you have the latest code, by performing a *git log*. The top-most message needs to be the same message as at the top of the *AVR_C* repository.
2. Confirm that each *TX* line is connected to an *RX* line. For example, confirm that the xArm *TX*, the third pin from the left on the xArm serial connector is connected to the *Uno pin 0*. Do this for both serial connections, 4 lines in all.
3. Confirm that the baud rate in the env.make file is set to *9600UL* and **not** *250000UL*. To check, enter *make env* in the *CLI*, this will print out all of the env.make variables.
4. Make sure the xArm is turned off, while uploading code to the Uno, as the Uno and xArm share the USB port.
## Control Example
```bash

```
