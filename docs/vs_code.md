# VS Code Configuration Files

Perform these steps in VS Code:

## C/C++ Configuration Installation
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
