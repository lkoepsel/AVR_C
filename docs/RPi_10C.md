# Building a Raspberry Pi C development platform for CSIS10C

## Introduction

These are the steps to create a *complete and up-to-date* Standard C development platform on a Raspberry Pi for the CSIS10C class. The steps accomplish the following:

1. Updates the OS and adds all prerequisites
1. Installs Debian Bookworm versions of avr-binutils, avr-gcc, avr-libc and avrdude
1. Adds [tio 3.5](https://github.com/tio/tio?tab=readme-ov-file), a *CLI-based* serial monitor 
. Adds the[ AVR_C](https://github.com/lkoepsel/AVR_C/tree/main) library and uses it to test the above
1. Install VS Code configuration files for C/C++ and creates default build tasks *AVR_C*
1. Adds a [hello service](https://github.com/lkoepsel/hello), for identifying the *RPi* in large networks

It requires connecting to the *RPi* via the command line (*Windows/Terminal*, *macOS/Terminal or Warp*). The best way to perform these steps, are to have this page open along side the CLI and simply copy and paste. 

**Note: Not all commands can be copy and pasted directly, these will be noted.**

**And for *step 2. CHOOSE OS...*, go to the bottom of the list, *Use custom* and navigate to the file you downloaded above.** Then continue with the instructions, below.

## Use Raspberry Pi Imager to start:
**On your PC** use *Pi Imager* to install a Raspberry Pi OS image on to an SD Card. The selections are:
1. CHOOSE DEVICE -> Raspberry Pi 4
1. CHOOSE OS -> Raspberry Pi OS (other) -> Raspberry Pi OS Lite (64-bit)
1. CHOOSE STORAGE -> **ENSURE THIS IS YOUR SD CARD!**
#### Edit Custom Settings
1. **General** tab: (set per your location)
    * *Set hostname*: to be unique to you if you are in an environment with multiple installations
    * *Set username...*: its best to have it be the same username on your PC and **remember the password you assign**
    * make sure the wi-fi is the same SSD as your PC
    * set locale to your time zone and keyboard layout as desired (in US, set to "*us*")
1. **SERVICES** Select "Allow public-key...", click *RUN SSH-KEYGEN* if required
1. **OPTIONS** Select all

Click *SAVE* then *Yes*, *Yes*.

**CONFIRM you are writing to the SD Card** then authenticate to allow Pi Imager to write to the SD Card.

Once Pi Imager has completed, remove the card and place in your RPi. Plug-in power and wait... :)

## Connect
The *RPi* will take at least 3 minutes for inital boot, then you may attempt to login. Replace *hostname* with the name you assigned in the step above. Connect using **one of the two commands** below:
```bash
# if your username on your PC is exactly the same as the username you used in Pi Imager
ssh hostname.local
# if the usernames are different, use the username you used in Pi Imager, below
ssh username@hostname.local
```

## 1. Update to latest software and add dependencies
```bash
# update OS
sudo apt update && sudo apt full-upgrade -y

# install AVR Suite along with dev programs
sudo apt install gcc-avr binutils-avr gdb-avr avr-libc avrdude make git meson
```

## 2. Update tio to latest
The CLI serial monitor program *tio* is quite handy and has been upgraded significantly in the last year. The new version is at least 3.5 and will be installed.
```bash
mkdir avr-build
cd ~/avr-build
wget https://github.com/tio/tio/releases/download/v3.5/tio-3.5.tar.xz
tar -xvf tio-3.5.tar.xz
cd tio-3.5/
sudo apt install -y libglib2.0-dev liblua5.2-dev
meson setup build
meson compile -C build
sudo meson install -C build
cd
# remove build directory, its quite large, might take a few minutes
rm -rf avr-build/
nano .tioconfig
```

```bash
[default]
baudrate = 250000
databits = 8
parity = none
stopbits = 1
local-echo = true
color = 11

[acm]
device = /dev/ttyACM0
color = 12

[usb]
device = /dev/ttyUSB0
color = 15

[usb-devices]
pattern = ^usb([0-9]*)
device = /dev/ttyUSB%m1
color = 14
```
*Ctrl-S* (save) *Ctrl-X*(exit)

## 5. Add AVR_C and test
* Add [AVR_C/docs/env.make](https://github.com/lkoepsel/AVR_C/blob/main/docs/env_make.md)
```bash
# clone AVR_C and test compile/link/load
cd
git clone https://github.com/lkoepsel/AVR_C.git
cd AVR_C
nano env.make
# copy/paste from from link above
# be sure to assign the correct serial port!
cd examples/blink
make flash
```

## 7. Setup VS Code

**If not already installed, you will want to install the following extensions on the Raspberry Pi:**
* Name: **C/C++** Description: C/C++ IntelliSense, debugging, and code browsing.
* Name: **C/C++ Themes** Description: UI Themes for C/C++ extension.
* Name: **Remote - SSH** Description: Open any folder on a remote machine using SSH and take advantage of VS Code's full feature set.
* Name: **Remote - SSH: Editing Configuration Files** Description: Edit SSH configuration files
* Name: **Remote Explorer** Description: View remote machines for SSH and Tunnels.

Perform these steps in VS Code on your host system:

### 7.1 Connect via Remote SSH
1. *CMD-Shift-P -> "C/C++" -> Remote SSH*
2. Enter the hostname (and credentials, if required) that you use in the CLI
3. VS Code will download the SSH Server and other extensions required

Ensure you do not have any files open in VS Code for the next two steps.
### 7.2 C/C++ Configuration Installation
**If you are on Windows, use Ctrl, instead of CMD.**

1. *CMD-Shift-P -> "C/C++" -> C/C++: Edit Configurations (JSON))*
2. Copy the content below then in *VS Code CMD-a* to select all of the existing *c_cpp_properties.json* file
3. *CMD-v* to paste and *CMD-s* to save. 

## c_cpp_properties.json
```json
{
    "configurations": [
        {
            "name": "AVR",
            "includePath": [
                "/usr/local/avr/avr/",
                "/usr/local/avr/include/**",
                "${workspaceFolder}/**"
            ],
            "defines": [  ],
            "compilerPath": "/usr/local/avr/bin/avr-gcc", 
            "compilerArgs": [ ],
            "cStandard": "c99",
            "cppStandard": "c++98",
            "intelliSenseMode": "${default}"
        }
    ],
    "version": 4
}
```

## 7.3 Default Task Installation
**If you are on Windows, use Ctrl, instead of CMD.**

1. *CMD-Shift-P -> "task" -> Tasks: Configure Default Build Task _> Create...from template -> Others Example...* 
2. Copy the content below then in *VS Code CMD-A* to select all of the existing *tasks.json* file
3. *CMD-v* to paste and *CMD-s* to save. 

## tasks.json
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "make",
            "detail": "Run make",
            "type": "shell",
            "command": "/usr/bin/make ${input:makeTarget}",
            "options": {
                "cwd": "${fileDirname}"
            },
            "presentation": {
                "reveal": "always",
                "panel": "dedicated"
              },        
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ],
    "inputs": [
        {
            "type": "pickString",
            "id": "makeTarget",
            "description": "Select a make target",
            "options": [
                {   
                    "value": "flash",
                    "label": "compile and upload code (upload)"
                },
                {   
                    "value": "compile",
                    "label": "only compile code (verify)"
                },
                {   
                    "value": "clean",
                    "label": "remove non-source files"
                },
                {   
                    "value": "complete",
                    "label": "complete re-compile with verbose upload"
                },
                {   
                    "value": "verbose",
                    "label": "verbose upload to debug serial connection"
                },
                {   
                    "value": "env",
                    "label": "print env variables being used"
                },
                {   
                    "value": "help",
                    "label": "print make commands"
                }
            ],
            "default": " flash"
        }
    ]
}
```
## ******** pibuildv3.img includes above steps ********

**Note: The *hello service* step below requires Python and the Python flask library to be installed on your PC. If you don't require an automatic notification by the *RPi* when it starts up, you may skip the step. Its typically required in large networks (colleges and universities), where its more difficult to ascertain the IP address or to use *Bonjour*.**

## 8. Add hello service
You may clone [hello](https://github.com/lkoepsel/hello) on your PC (host system) or simply download *hello_server.py* in the repository for this capability. This Python *flask* application will report its IP address then wait for a connection by the *RPi*. Use IP address for step 8.2 below. To run the server program locally:

### On host system (your PC)
On your host system, in your CLI , open another tab (*File -> New Tab*).
```bash
# on host system in a different window
cd hello
python -m hello_server
# to quit, press Ctrl-C
```

### Remaining steps on *RPi* tab in your CLI
### 8.1. Add hello.py
```bash
# open a file named hello.py
sudo nano /usr/bin/hello.py
```

```python
import logging
import requests
import socket
import os
import sys


hadtomount = False

if not os.path.exists('/boot/firmware'):
    hadtomount = True
    os.system("sudo mount /dev/mmcblk0p1 /boot/firmware")

# set logging to DEBUG, if not showing up
logging.basicConfig(filename='/boot/firmware/hello.log', encoding='utf-8',
                    format='%(asctime)s %(filename)s:%(levelname)s: %(message)s',
                    level=logging.DEBUG)

IP_file = "hello_ip.txt"  # Replace with your desired file name

# List of directories to search
dirs_to_check = ["/boot", "/boot/firmware"]

# Search for the file in the listed directories
for dir_path in dirs_to_check:
    file_path = os.path.join(dir_path, IP_file)
    if os.path.isfile(file_path):
        try:
            with open(file_path, "r") as f:
                ip = f.read().rstrip("\n")
                logging.debug("IP address found in %s", file_path)
            break  # Exit the loop if the file is found and opened successfully
        except IOError:
            logging.error("Error opening file: %s", file_path)
            sys.exit(0)
else:
    logging.error("%s not found in %s ", IP_file, dirs_to_check)
    sys.exit(0)

if hadtomount:
    os.system("sudo umount /boot/firmware")

host_name = socket.gethostname()
logging.debug("Host name: %s  ", host_name)

url = 'http://' + ip
text = f"Hello from {host_name}"
logging.debug(url)

data = {'text': text}

try:
    response = requests.post(url, data=data)

except requests.exceptions.RequestException as e:
    logging.error(e)
    sys.exit(1)

logging.debug(response.status_code)
logging.debug(response.text)
```
*Ctrl-S* (save) *Ctrl-X*(exit)
### 8.2. Add *hello_ip.txt*
This step identifies your PC by IP address to the Raspberry Pi:

1. Run `python -m hello_server` from [*hello*](https://github.com/lkoepsel/hello) folder on your PC, this will report the IP address of your PC.
1. Open a the file to contain the IP address.

```bash
sudo nano /boot/firmware/hello_ip.txt
```

Enter the only the numeric IP address of your PC WITHOUT a return at the end of the line. The file *hello_ip.txt* will need to look like:

```bash
192.168.1.124
```
*Ctrl-S* (save) *Ctrl-X* (exit)

**Note:** By storing the IP address in a file at */boot/firmware*, you may access the file on a macOS or Windows system. The *boot/firmware* folder shows up as a readable folder on either system called *bootfs*. This enables you to change the IP address on your PC then re-insert the SD Card into the *RPi* to ping you at a new address. 

There is also a file on *boot/firmware* called *hello.log*, which you can open with a text editor. It will contain the log entries for the *hello.service*. Use these entries if you are having difficulty getting a ping from the *RPi.* 

### 8.3. Setup systemd for hello.service
```bash
sudo nano /lib/systemd/system/hello.service
```
```service
[Unit]
Description=Ping a known server (hello_ip.txt) with hostname and IP address
After=network-online.target
Wants=network-online.target

[Service]
Type=simple
ExecStart=/usr/bin/python /usr/bin/hello.py
Restart=on-failure
RestartSec=1
StartLimitInterval=0
StartLimitBurst=5

[Install]
WantedBy=multi-user.target
```
*Ctrl-S* (save) *Ctrl-X* (exit)

#### Test the Service
Run the following commands to create service and test it. (**Go to the hello tab and confirm the hello message appears**):
```bash
sudo chmod 644 /lib/systemd/system/hello.service
sudo systemctl daemon-reload
# start and check service
sudo systemctl start hello.service
sudo systemctl status hello.service
# press q to quit status
```

#### Enable the Service
If you see the IP address, then enable the service. If you don't, confirm you are on the same network and have the correct IP address. Your *RPi* will reboot after this step. **This step to enable the service must be executed in order for the service to work.**
```bash
# if hello.service is running well, then enable to run on boot
sudo systemctl enable hello.service
# reboot and test
sudo reboot now
# on host system, run hello_server.py
```
In *hello* tab of your CLI, watch for the *RPi* to ping the server. When it does, login to the *RPi* with a `ssh username@hostname.local` or `ssh hostname.local` and continue with the steps below.


## Notes:
### CLI Utilities
* `nmtui` - Text User Interface for controlling NetworkManager

### Enable Both Password and Publickey SSH Authentication 
```bash
sudo nano /etc/ssh/sshd_config
# ensure both of these lines are not commented
PasswordAuthentication yes
PubkeyAuthentication yes
# exit nano
sudo reboot now
```

### Update Firmware
[Update Raspberry Pi Bootloader](https://bret.dk/update-raspberry-pi-bootloader/)

```bash
# check current version
rpi-eeprom-update

# Make sure system is up to date
sudo apt update
sudo apt full-upgrade

# Update the Firmware
sudo rpi-eeprom-update -a

# reboot per instructions
sudo reboot now

# check version again
rpi-eeprom-update
```
### Toggle the power led
```bash
# turn off 
echo 0 | sudo tee /sys/class/leds/PWR/brightness
# turn on
sudo echo 1 | tee /sys/class/leds/PWR/brightness
```

### Saving, shrinking and sending an image
```bash
# remove SD Card or USB drive containing RPi image and place in Linux PC
# determine physical device
lsblk
# find specific drive "sdc", "sdd" which is the right size of RPi drive, use as input
sudo dd if=/dev/sdc of=./pi10C.img bs=1M status=progress
# shrink the size of the image to save space
sudo pishrink.sh -avz pi10C.img
# Easy way to send a file, requires magic-wormhole to be installed on receiving system
wormhole send pi10C.img.gz
```

### Linux Serial Permissions
If the *RPi* appears to be having permissions issues with opening the *SNAP* or *XPLAIN* USB port, add a *UDEV* rule to allow it.

#### Testing
Typically, the error is from *avrdude* where is states it has insufficient permissions to access the port. To test, use *avrdude* with and without, `sudo`.
```bash
# This does not work
avrdude -p m328p -P usb  -c snap_isp -t
# This does work
sudo avrdude -p m328p -P usb  -c snap_isp -t
```
Type `q` to quit, if either command works and connects to the Uno. If `sudo` is required, implement the solution below.

#### Solution

```bash
# for Microchip SNAP and XPLAINED MINI 328PB
sudo nano /etc/udev/rules.d/50-myusb.rules
```
Below are two lines, the first is for the SNAP and the second for the XPLAIN
```bash
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2180", GROUP="plugdev", MODE="0660", TAG+="uaccess"
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2145", GROUP="plugdev", MODE="0660", TAG+="uaccess"
```
*Ctrl-S* (save) *Ctrl-X* (exit), then **reboot**:
```bash
sudo reboot now
```

#### More Details on Serial Permissions
1. Run dmesg to determine idVendor and idProduct of the USB interfaces (in this case there are two.)
2. Use sudo and your favorite editor to create a file: "/etc/udev/rules.d/50-myusb.rules"
3. Using the idVendor and idProduct numbers, create two lines in the file using this format (replacing the numbers shown with your numbers):

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2e8a", ATTRS{idProduct}=="0004", GROUP="plugdev", MODE="0660", TAG+="uaccess"

4. Save and close the file then restart your system.

#### Examples for other devices
```bash
# use dmesg to determine idVendor and idProduct
# be sure to use the right USB devices (such as usb 1-1 and usb 1-2 below)
dmesg
# ...
[62603.487834] usb 1-1: New USB device found, idVendor=0403, idProduct=6001, bcdDevice= 6.00
...
[62603.492032] usb 1-1: FTDI USB Serial Device converter now attached to ttyUSB0
...
[62607.143187] usb 1-2: New USB device found, idVendor=2e8a, idProduct=0004, bcdDevice= 1.00
...
[62607.145394] cdc_acm 1-2:1.0: ttyACM0: USB ACM device
# Bookworm with Microchip SNAP
[    2.521599] usb 1-1.4: New USB device found, idVendor=03eb, idProduct=2180, bcdDevice= 1.00

sudo nano /etc/udev/rules.d/50-myusb.rules
SUBSYSTEMS=="usb", ATTRS{idVendor}=="0403", ATTRS{idProduct}=="6001", GROUP="plugdev", MODE="0660", TAG+="uaccess"
SUBSYSTEMS=="usb", ATTRS{idVendor}=="2e8a", ATTRS{idProduct}=="0004", GROUP="plugdev", MODE="0660", TAG+="uaccess"
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2180", GROUP="plugdev", MODE="0660", TAG+="uaccess"

# save the file then reboot your system
```
### Update OS
```bash
sudo apt update && sudo apt full-upgrade-y
```

### In case of no change, and you know its not true
Sometimes, you attempt to update and it implies nothing to update. 
```bash
sudo rm -r /var/lib/apt/lists/*
sudo apt clean
sudo apt update && sudo apt full-upgrade-y
```

### Raspberry Pi Connect Lite 
*from installation via raspi-config*

For Raspberry Pi OS Lite, enable user lingering for your user:
```bash
loginctl enable-linger
```
This allows users who are not logged in to run long-running services.

Raspberry Pi Connect will automatically start when you next log in or you can start it now by running:

```bash
systemctl --user start rpi-connect
```
[More information](https://rptl.io/rpi-connect)

### Disk testing

### hdparm
```bash
sudo hdparm -t /dev/nvme0n1

/dev/nvme0n1:
 Timing buffered disk reads: 2502 MB in  3.00 seconds = 833.95 MB/sec
```

#### fio tests
[Linux fio disk testing](https://dotlayer.com/how-to-use-fio-to-measure-disk-performance-in-linux/)

Let’s start by running the following command. This command will write a total 4GB file [4 jobs x 512 MB = 2GB] running 2 processes at a time:
```bash
# write testing 2 jobs
sudo fio --name=randwrite --ioengine=libaio --iodepth=1 --rw=randwrite --bs=4k --direct=0 --size=512M --numjobs=2 --runtime=240 --group_reporting

# read testing 4 jobs
sudo fio --name=randread --ioengine=libaio --iodepth=16 --rw=randread --bs=4k --direct=0 --size=512M --numjobs=4 --runtime=240 --group_reporting
```

### Fix a known hosts issue
When attempting to login to a new Raspberry Pi, sometimes the host system won't because the *REMOTE HOST IDENTIFICATION HAS CHANGED* has changed. To fix:
```bash
nano ~/.ssh/known_hosts
# shift ctrl-K every line which contains the name of the old Pi
# ctrl-s to save
# ctrl-x to exit
```

### Determine exact model
```bash
cat /proc/cpuinfo
processor   : 0
BogoMIPS    : 38.40
Features    : fp asimd evtstrm crc32 cpuid
CPU implementer : 0x41
CPU architecture: 8
CPU variant : 0x0
CPU part    : 0xd03
CPU revision    : 4

...

Revision    : a22082
Serial      : 000000009f0ea51b
Model       : Raspberry Pi 3 Model B Rev 1.2
```

### Add USB Boot to Model 3B (not 3B+)
```bash
sudo nano /boot/firmware/config.txt
[All]
program_usb_boot_mode=1
# Ctrl-s Ctrl-x
sudo reboot now
# to confirm
vcgencmd otp_dump | grep 17:
17:3020000a
```

