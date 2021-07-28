cmake_minimum_required(VERSION 3.0.0)
project(OP_Pi VERSION 0.1.0)

add_subdirectory(lib/libsoundio)

include(CTest)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsoundio/
    ${CMAKE_CURRENT_SOURCE_DIR}/oled/
    ${CMAKE_CURRENT_SOURCE_DIR}/inputmanager/
    ${CMAKE_CURRENT_SOURCE_DIR}/screenmanager/
)
enable_testing()

set(
    OLEDDRIVER_SOURCES
    oled/DEV_Config.cpp
    oled/OLED_Driver.cpp
    oled/OLED_GFX.cpp
    oled/fonts/ASCII_Font.cpp
    oled/fonts/font8.cpp
    oled/fonts/font12.cpp
    oled/fonts/font16.cpp
    oled/fonts/font20.cpp
    oled/fonts/font24.cpp
)

set(
    SCREENMANAGER_SOURCES
    screenmanager/screen_manager.cpp
)

set(
    INPUTMANAGER_SOURCES
    inputmanager/input_manager_gpio.cpp
    inputmanager/input_manager_keyboard.cpp
)

add_executable(OP_Pi main.cpp synth.cpp instrument.cpp instrument.h daw.h daw.cpp timeline.cpp timeline.h effect.h effect.cpp eq.cpp eq.h reverb.cpp reverb.h ${OLEDDRIVER_SOURCES} ${INPUTMANAGER_SOURCES} ${SCREENMANAGER_SOURCES}
)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
get_directory_property(LIBSOUNDIO_LIBS DIRECTORY lib/libsoundio DEFINITION LIBSOUNDIO_LIBS)
add_compile_definitions(SOUNDIO_STATIC_LIBRARY)
target_link_libraries(OP_Pi
    libsoundio_static
    ${LIBSOUNDIO_LIBS}
    X11
    wiringPi
)