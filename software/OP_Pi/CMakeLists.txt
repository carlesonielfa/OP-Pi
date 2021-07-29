cmake_minimum_required(VERSION 3.0.0)
project(OP_Pi VERSION 0.1.0)

add_subdirectory(lib/libsoundio)
#add_subdirectory(OLEDdriver)

include(CTest)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsoundio/
    #${CMAKE_CURRENT_SOURCE_DIR}/OLEDdriver/
    #${CMAKE_CURRENT_SOURCE_DIR}/OLEDdriver/Fonts
    ${CMAKE_CURRENT_SOURCE_DIR}/inputmanager/
    ${CMAKE_CURRENT_SOURCE_DIR}/screenmanager/
)
enable_testing()


set(
    SCREENMANAGER_SOURCES
    screenmanager/screen_manager.cpp
    screenmanager/oled_driver.cpp
)

set(
    INPUTMANAGER_SOURCES
    inputmanager/input_manager_gpio.cpp
    inputmanager/input_manager_keyboard.cpp
)

add_executable(OP_Pi main.cpp synth.cpp instrument.cpp instrument.h daw.h daw.cpp timeline.cpp timeline.h effect.h effect.cpp eq.cpp eq.h reverb.cpp reverb.h ${INPUTMANAGER_SOURCES} ${SCREENMANAGER_SOURCES} )
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
get_directory_property(LIBSOUNDIO_LIBS DIRECTORY lib/libsoundio DEFINITION LIBSOUNDIO_LIBS)
add_compile_definitions(SOUNDIO_STATIC_LIBRARY)
find_library(OLEDDRIVER oleddriver lib)
target_link_libraries(OP_Pi
    libsoundio_static
    ${LIBSOUNDIO_LIBS}
    X11
    wiringPi
    m
)