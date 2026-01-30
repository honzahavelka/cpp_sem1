cmake_minimum_required(VERSION 3.10)
project(sem_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# shromáždění všech zdrojových souborů
file(GLOB_RECURSE SOURCES "src/*.cpp")

# definice spustitelného souboru
add_executable(${PROJECT_NAME} ${SOURCES})

# nastavení složky s hlavičkovými soubory
target_include_directories(${PROJECT_NAME} PUBLIC include)

# zapnutí varování
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# nastavení výstupního jména
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "drawing")