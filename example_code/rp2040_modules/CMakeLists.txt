# Set minimum CMake version
cmake_minimum_required(VERSION 3.17)

# Include the subsidiary .cmake file to get the SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set the name and version of the project
project(rp2040_module VERSION 0.0.1)

# Set the board to Raspberry Pi Picos
set(PICO_BOARD pico)

# Set top source code folder
set(SOURCE_FOLDER "src")

# Set build type (options: 'Debug', 'Release', 'MinSizeRel', 'RelWithDebInfo')
set(default_build_type "Release")

# Set CMAKE_BUILD_TYPE
set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build, options are: 'Debug', 'Release', 'MinSizeRel', 'RelWithDebInfo'." FORCE)

# Initialize the SDK
pico_sdk_init()

# Add an executable target for the project
add_executable(${PROJECT_NAME})

# Get all the pio files, when the glob value changes, cmake will run again and update the files
file(GLOB_RECURSE pio_src CONFIGURE_DEPENDS "${SOURCE_FOLDER}/*.pio")

# Convert List to String
STRING(REPLACE ";" "\n" PIO_SRC_STR_OUT "${pio_src}")

# Print the pio source file list
message(STATUS "PIO code source files: \n${PIO_SRC_STR_OUT}")

# If there are any PIO source files, include them to the build.
if (NOT pio_src STREQUAL "")
	foreach(PIO_SRC_ELEM ${pio_src})
		pico_generate_pio_header(${PROJECT_NAME} ${PIO_SRC_ELEM})
	endforeach()
endif()

# Get all C and C++ files, when the glob value changes, cmake will run again and update the files
file(GLOB_RECURSE app_src CONFIGURE_DEPENDS "${SOURCE_FOLDER}/*.c" "${SOURCE_FOLDER}/*.cpp" )

# Convert List to String
STRING(REPLACE ";" "\n" APP_SRC_STR "${app_src}")

# Print the C and C++ source file list
message(STATUS "C and C++ source files: \n${APP_SRC_STR}")

# Add C and C++ source files to the build
target_sources(${PROJECT_NAME} PRIVATE ${app_src})

# Link the Project to extra libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
  pico_stdlib
  hardware_pio
  hardware_adc
  hardware_i2c
  hardware_timer
  hardware_pwm
)

# Including header files directly from project directory
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Export binaries like hex, bin, and uf2 files.
pico_add_extra_outputs(${PROJECT_NAME})

# Enable or Disable UART
pico_enable_stdio_uart(${PROJECT_NAME} 1)

# Enable or Disable USB CDC
pico_enable_stdio_usb(${PROJECT_NAME} 1)

# Disable DTR check for USB CDC connection
add_definitions(-DPICO_STDIO_USB_CONNECTION_WITHOUT_DTR=1)

 
add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_SOURCE_DIR}/wait.sh
  COMMENT "Copiing uf2 to rpi."
)

