cmake_minimum_required(VERSION 3.0.0)
project(OP_Pi VERSION 0.1.0)

add_subdirectory(lib/libsoundio)

include(CTest)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsoundio/
)
enable_testing()

add_executable(OP_Pi main.cpp synth.cpp input_manager.cpp instrument.cpp screen_manager.cpp daw.h daw.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
get_directory_property(LIBSOUNDIO_LIBS DIRECTORY lib/libsoundio DEFINITION LIBSOUNDIO_LIBS)
add_compile_definitions(SOUNDIO_STATIC_LIBRARY)
target_link_libraries(OP_Pi
    libsoundio_static
    ${LIBSOUNDIO_LIBS}
    X11
)
