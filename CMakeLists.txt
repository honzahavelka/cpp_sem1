cmake_minimum_required(VERSION 3.10)
project(sem_1)

# Moderní C++ standard (požadavek ze zadání)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 1. Shromáždění všech zdrojových souborů (včetně vnořených složek)
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 2. Definice spustitelného souboru
add_executable(${PROJECT_NAME} ${SOURCES})

# 3. Nastavení složky s hlavičkovými soubory
# Používáme PUBLIC, aby o nich věděly i případné další části projektu
target_include_directories(${PROJECT_NAME} PUBLIC include)

# 4. Zapnutí varování (aby tě statická analýza MSVC i GCC měla ráda)
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# 5. Volitelné: Nastavení výstupního jména (pokud se má jmenovat jinak než projekt)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "drawing")