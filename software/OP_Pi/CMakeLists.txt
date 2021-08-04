cmake_minimum_required(VERSION 3.0.0)
project(OP_Pi VERSION 0.1.0)

add_subdirectory(lib/libsoundio)
add_subdirectory(lib/lcdgfx)
add_subdirectory(lib/libsndfile)

include(CTest)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsoundio/
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsndfile/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/lcdgfx/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/inputmanager/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/screenmanager/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)
enable_testing()

set(
    DAW_SOURCES
    src/synth.cpp
    src/instrument.cpp
    src/daw.cpp
    src/daw.h
    src/timeline.cpp
    src/effect.cpp
    src/eq.cpp
    src/reverb.cpp
)
set(
    SCREENMANAGER_SOURCES
    src/screenmanager/screen_manager.cpp
)

set(
    INPUTMANAGER_SOURCES
    src/inputmanager/input_manager_gpio.cpp
    src/inputmanager/input_manager_keyboard.cpp
)

add_executable(OP_Pi main.cpp  ${DAW_SOURCES} ${INPUTMANAGER_SOURCES} ${SCREENMANAGER_SOURCES} )
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
    lcdgfx
    sndfile
)