cmake_minimum_required(VERSION 3.30)
project(sem_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(sem_1 main.cpp
        utils/args_parser.cpp
        utils/args_parser.h
        entities/Entity.h
        entities/line.cpp
        entities/line.h
        entities/rect.cpp
        entities/rect.h
        entities/circle.cpp
        entities/circle.h
        canvas/canvas.cpp
        canvas/canvas.h
        parser/parser.cpp
        parser/parser.h
        commands/command.h
        commands/entity_commands.cpp
        commands/entity_commands.h
        commands/transform_commands.cpp
        commands/transform_commands.h)
