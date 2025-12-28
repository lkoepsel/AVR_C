# env.make required for *make*

There is a specific change which needs to be made, to ensure the *env.make* file is appropriate for your computer and Uno setup.

## 1. Update the SERIAL to the proper DEVICE
### 1. In your CLI
Enter the two commands below to open the nano editor, in the *AVR_C* folder
```bash
cd AVR_C
cp env.def env.make
```

You will now be in the AVR_C folder and will need to edit the env.make file. The git version is a default version, we copied it for the make program to use it. We want to ensure we're connecting to the correct **DEVICE**.
### 2. **Obtain Uno device address**

```bash
# Connect an Arduino Uno via USB cable and run:
tio -l  # lowercase l as in leo
```
Under **Device** will be something like:
*/dev/ttyUSB0* or */dev/ttyACM0*. 

Copy this string, we'll refer to it as **DEVICE**.

### 3. **Confirm or change the **DEVICE** address**

``` bash
nano env.make
```

**In nano, do the following:**
1. Use your arrow keys to move down to line 39
2. You use left/right arrow keys to edit the line
3. The line will look like this: 
    `SERIAL = /dev/ttyACM0`
4. Either confirm SERIAL equals DEVICE found above

**OR**

5. overwrite it, with DEVICE
6. You will probably* end up with one of two variations below:

    * SERIAL = /dev/ttyACM0

    * SERIAL = /dev/ttyUSB0

*Ctrl-S to save, Ctrl-X to exit*

\* *There can be a third version, however, I rarely see it.*

