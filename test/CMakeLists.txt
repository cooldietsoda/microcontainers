cmake_minimum_required(VERSION 3.22)
project("MicroContainersTest")

find_package(DamnTest CONFIG REQUIRED)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PRIVATE
        set_test.cpp
)
target_compile_options(${PROJECT_NAME} PRIVATE -fno-exceptions -fno-unwind-tables -fno-rtti)
target_link_libraries(${PROJECT_NAME} PRIVATE MicroContainers ::DamnTest)