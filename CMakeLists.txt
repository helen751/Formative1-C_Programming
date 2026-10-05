cmake_minimum_required(VERSION 3.20)

project(Formative1_C_Programming C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(question1
        question1_water_monitoring/main.c
)

add_executable(question2
        question2_mobile_money/main.c
)

add_executable(question3
        question3_recursive/main.c
)