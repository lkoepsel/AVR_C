# xArm Commands

This interface is closely modeled after the great work by Chris Courson, [here](https://github.com/ccourson/xArmServoController). His work served as inspiration and guidance in created a similar work, except this one is exclusively **C99 C**.

I also took the approach to use the Lewan-Soul/HiWonder board as a primitive controller and developed the control intelligence in the Uno board. This gives greater programmatic control to the C programmer, however, it does require far more programming work to do so. This is a traditional programming dilemma...*the greater the control the program provides, the greater the work required*.

## Structure
The *AVR_C xArm Commander* program utilizes three files to create an interface, it is similar to many of the files in the *examples* folder.:

* *xArm_Commander* - the main.c program which is the main interface to the xArm API. It drives a command-based interface.
* *xArm.h* - header program for the xArm primitives file, *xArm.c*
* *xArm.c* - xArm primitives file, contains similar (if not the same) routines as those in the *Coursen xArm Arduino src* file.

## Commands
* *move joint position* - move *joint* (1-6) to *position* (1 - 999)
* *pos joint* - return the position of joint
* *add joint position* - the same as the move command, except it is added to a list of moves which will be executed sequentially by *exec*
* show - show the list of commands to be executed by *exec*
* exec - execute the list of commands
* reset - reset the list of commands to be empty
* volt - return the voltage of the battery
* beep - cause the arm to beep

## Communications

