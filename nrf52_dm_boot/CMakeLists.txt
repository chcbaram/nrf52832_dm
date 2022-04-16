cmake_minimum_required(VERSION 3.12)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools")
include(toolchain)


set(PRJ_NAME nrf52_dm_boot)


project(${PRJ_NAME}
  LANGUAGES ASM C
)


set(EXECUTABLE ${PRJ_NAME}.elf)


file(GLOB SRC_FILES CONFIGURE_DEPENDS
  src/bsp/*.c
  src/hw/*.c
  src/hw/driver/*.c
)

file(GLOB_RECURSE SRC_FILES_RECURSE CONFIGURE_DEPENDS
  src/ap/*.cpp
  src/ap/*.c
  src/common/*.c    
  
  src/lib/nrfx-2.8.0/drivers/src/*.c
)

add_executable(${EXECUTABLE} 
  src/main.c
  src/bsp/startup/startup_nrf52832.S
  src/lib/nrfx-2.8.0/mdk/system_nrf52.c

  ${SRC_FILES}
  ${SRC_FILES_RECURSE}
)



target_include_directories(${EXECUTABLE} PRIVATE 
  src  
  src/ap
  src/bsp
  src/common 
  src/common/core
  src/common/hw/include 
  src/hw
  src/lib

  src/bsp/cmsis/Include  

  src/lib/nrfx-2.8.0
  src/lib/nrfx-2.8.0/hal
  src/lib/nrfx-2.8.0/mdk
  src/lib/nrfx-2.8.0/drivers/include
)

target_compile_definitions(${EXECUTABLE} PRIVATE
  -DNRF52832_XXAA
  -DNRF52
  )

target_compile_options(${EXECUTABLE} PRIVATE
  -mcpu=cortex-m4
  -mthumb
  -mfpu=fpv4-sp-d16 
  -mfloat-abi=hard

  -fdata-sections
  -ffunction-sections
  --specs=nano.specs

  -Wall

  -O0
  -g3
  )

target_link_options(${EXECUTABLE} PRIVATE
  -T../src/bsp/ldscript/NRF52832_FLASH.ld
  -mcpu=cortex-m4
  -mthumb
  -mfpu=fpv4-sp-d16 
  -mfloat-abi=hard
  -specs=nano.specs
  --specs=nosys.specs

  -lc
  -lm
  -lstdc++
  -lsupc++

  -Wl,-Map=${PRJ_NAME}.map,--cref
  -Wl,--gc-sections
  -Xlinker -print-memory-usage -Xlinker
  )

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
  COMMAND ${CMAKE_SIZE_UTIL} --format=berkeley --totals "$<TARGET_FILE:${EXECUTABLE}>"
  COMMENT "Invoking: Cross ARM GNU Print Size")

add_custom_command(TARGET ${EXECUTABLE} 
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin
    COMMENT "Invoking: Make Binary"
    )

