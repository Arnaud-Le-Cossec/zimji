add_library(cpu_core
    cpu.c
    # Add other source files here
)
target_include_directories(cpu_core PRIVATE ${CMAKE_SOURCE_DIR}/inc)