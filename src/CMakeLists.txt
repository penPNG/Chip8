add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.cpp "chip8.h" "chip8.cpp" "keyboard.h" "keyboard.cpp" "cpu.h" "cpu.cpp" "memory.h" "memory.cpp" "bytes.h" "screen.h" )
target_link_libraries(${PROJECT_NAME} PRIVATE vendor)