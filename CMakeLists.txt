project(POOL)
cmake_minimum_required(VERSION 2.6)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)


SET(CPU_FLAG "-mmcu=msp430g2553 -g")
set (CMAKE_C_FLAGS ${CPU_FLAG})
set (CMAKE_EXE_LINKER_FLAGS ${CPU_FLAG})

# specify the cross compiler
SET(CMAKE_C_COMPILER msp430-gcc)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)


add_subdirectory(src)
