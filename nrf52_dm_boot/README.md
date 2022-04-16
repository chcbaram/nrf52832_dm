# nRF52832_DM UART 부트로더
nRF52832_DM 보드에서 UART를 통해서 펌웨어를 업데이트 할 수 있는 부트로더 프로젝트이다. 

## CMake Configure
```
cmake -S . -B build -G "MinGW Makefiles"
```

## CMake Build
```
cmake --build build -j16   
```

## CMake Clean
```
cmake --build build --target clean
```

## STLink 디버깅 설정
- .vscode/launch.json 파일
  ```
  {
    "configurations": [
      {
        "cwd": "${workspaceRoot}",
        "executable": "./build/nrf52_dm_boot.elf",
        "name": "Debug with OpenOCD",
        "request": "launch",
        "type": "cortex-debug",
        "servertype": "openocd",
        "configFiles": [
          "interface/stlink.cfg",
          "target/nrf52.cfg"
        ],
        "searchDir": ["${workspaceRoot}"],
        "runToEntryPoint": "main",
        "showDevDebugOutput": "none",
        
        "windows": {
          "toolchainPath": "D:/tools/gcc-arm-none-eabi-9-2020-q2-update-win32/bin",
          "serverpath": "D:/tools/build_tools/xpack-openocd-0.11.0-1/bin/openocd.exe"
        }
      },
    ]
  }
  ```