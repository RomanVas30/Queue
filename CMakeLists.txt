cmake_minimum_required(VERSION 3.3)

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.19.123.tar.gz"
    SHA1 "57d07480686f82ddc916a5980b4f2a18e5954c2b"
)

project(Queue)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" OFF)
option(BUILD_EXAMPLES "Build Examples" OFF)

set(${PROJECT_NAME}_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sources/queue.cpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(${PROJECT_NAME}  ${${PROJECT_NAME}_SOURCES})

if(BUILD_EXAMPLES)
    file(GLOB EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp")
    foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
        get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)
        set(EXAMPLE_TARGET_NAME example_${EXAMPLE_NAME})
        add_executable(${EXAMPLE_TARGET_NAME} ${EXAMPLE_SOURCE})
        target_link_libraries(${EXAMPLE_TARGET_NAME} ${PROJECT_NAME})
        set_target_properties(${EXAMPLE_TARGET_NAME} PROPERTIES OUTPUT_NAME ${EXAMPLE_NAME})
        install(TARGETS ${EXAMPLE_TARGET_NAME}
                RUNTIME DESTINATION bin
                )
    endforeach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
endif()
