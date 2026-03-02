add_subdirectory(cpu)

add_executable(zimji
    emulator_utility.c
    main.c
    # Add other source files here
)

target_link_libraries(zimji PRIVATE cpu_core)
target_include_directories(zimji PRIVATE ${CMAKE_SOURCE_DIR}/inc)
