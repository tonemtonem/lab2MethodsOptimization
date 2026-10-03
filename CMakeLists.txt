cmake_minimum_required(VERSION 4.2)
project(LabMethodsOptimisation2 C)

set(CMAKE_C_STANDARD 11)

add_executable(LabMethodsOptimisation2 main.c
        numericUtils.h
        numericUtils.c
        SimplexTypes.h
        SimplexTable.h
        SimplexSolver.h
        SimplexTable.c
        AdditionalMethods.h
        AdditionalMethods.c
        SimplexSolver.c
)
