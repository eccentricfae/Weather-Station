cmake_minimum_required(VERSION 3.13)

# TODO Check if current directory is the same where the CMakeLists.txt is

set(PICO_BOARD pico_w)

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/pico_sdk_import.cmake")
    # If pico_sdk_import.cmake exists in working directory -> include it
    include(pico_sdk_import.cmake)
else()
    # Else -> pull it from the SDK directory
    include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
endif()

project(WEATHER-STATION C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

pico_sdk_init()

# Generates html_data.c (raw html for uC)
execute_process(COMMAND
    python ${CMAKE_CURRENT_LIST_DIR}/src/helpers/makefsdata.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

add_executable(
    ${PROJECT_NAME}

    src/main.c
    src/server/cgi.c
    src/server/ssi.c
    src/hardware/hardware.c
    src/helpers/helpers.c
)

target_include_directories(
    ${PROJECT_NAME}

    PUBLIC   
    src/
    src/server/
    src/hardware/
    src/helpers/
    src/wifi_config/
)

target_link_libraries(
    ${PROJECT_NAME} 

    PUBLIC
    pico_stdlib 
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_http                             
)

# Enable USB output for trivial USB-PC debugging
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# Need to generate UF2 file for upload to RP2040
pico_add_extra_outputs(${PROJECT_NAME})