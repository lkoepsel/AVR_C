# VS Code Configuration Files

These files are now tracked by git in the *.vscode* folder. The text below shows as of *Trixie December 2025*.

## C/C++ Configuration Installation
**If you are on Windows, use Ctrl, instead of CMD.**

1. *CMD-Shift-P -> "C/C++" -> C/C++: Edit Configurations (JSON))*
2. Copy the content below then in *VS Code CMD-a* to select all of the existing *c_cpp_properties.json* file
3. *CMD-v* to paste and *CMD-s* to save. 

## Trixie version C (gcc 14.2)
### c_cpp_properties.json
```json
{
    "configurations": [
        {
            "name": "AVR",
            "includePath": [
                "/usr/lib/gcc/avr/14.2.0/include/",
                "/usr/lib/gcc/avr/14.2.0/include-fixed/**",
                "/usr/lib/avr/include",
                "${workspaceFolder}/**"
            ],
            "defines": ["__AVR_ATmega328P__"],
            "compilerPath": "/usr/bin/avr-gcc", 
            "compilerArgs": [ ],
            "cStandard": "c99",
            "cppStandard": "c++98",
            "intelliSenseMode": "${default}"
        }
    ],
    "version": 4
}
```

## Default Task Installation
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
                "reveal": "silent",
                "panel": "shared"
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
                    "value": "size",
                    "label": "print size information of elf file"
                },
                {   
                    "value": "disasm",
                    "label": "create an assembly listing of the file, main.lst"
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

## extensions.json

```json
{
    "recommendations": [
    "ms-vscode-remote.remote-containers",
    "ms-vscode-remote.remote-ssh",
    "ms-vscode-remote.remote-ssh-edit",
    "ms-vscode.cpptools",
    "ms-vscode.cpptools-themes",
    "ms-vscode.remote-explorer"
  ],
  "unwantedRecommendations": [
    "qili.vscode-lc3",
    "yzane.markdown-pdf",
    "marp-team.marp-vscode"
  ]
}
```

## settings.json

```json
{
    "files.associations": {
        "*.make": "makefile",
        "*.S": "avr",
        "xarm.h": "c"
    },
    "workbench.colorCustomizations": {
      "terminal.background": "#1e1e1e",
      "terminal.foreground": "#cccccc",
      "terminal.ansiBlack": "#000000",
      "terminal.ansiRed": "#cd3131",
      "terminal.ansiGreen": "#0dbc79",
      "terminal.ansiYellow": "#e5e510",
      "terminal.ansiBlue": "#2472c8",
      "terminal.ansiMagenta": "#bc3fbc",
      "terminal.ansiCyan": "#11a8cd",
      "terminal.ansiWhite": "#e5e5e5"
    },
    "cSpell.words": [
      "Adafruit",
      "AREF",
      "atmega",
      "Atmel",
      "avrdude",
      "binutils",
      "cppcheck",
      "Datasheet",
      "functionname",
      "getchar",
      "invalidscanf",
      "Libc",
      "makefiles",
      "Mersenne",
      "microcontroller",
      "Microcontrollers",
      "millis",
      "minicom",
      "MPLAB",
      "objdump",
      "oneline",
      "Optiboot",
      "outerpins",
      "Pico",
      "pidev",
      "Pmem",
      "PULLUP",
      "pushbuttons",
      "recompiles",
      "scanf",
      "serialio",
      "studentn",
      "sysclock",
      "tinymt",
      "uart",
      "unolib",
      "usbserial",
      "wrapprint",
      "Wundef",
      "Xplained"
    ],
  "extensions.ignoreRecommendations": true,
  // to disable specific extensions:
  "extensions.disabled": [
    "qili.vscode-lc3",
    "yzane.markdown-pdf",
    "marp-team.marp-vscode",
    "paulober.pico-w-go"
  ],
    "remote.defaultExtensionsIfInstalledLocally": [],
    "workbench.panel.defaultLocation": "right"
}
```