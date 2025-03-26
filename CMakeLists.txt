cmake_minimum_required(VERSION 3.30)
project(miniguys)

# Set some global configs
set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(LIB_NAME lib_${PROJECT_NAME})
set(TEST_NAME test_${PROJECT_NAME})

# Find packages with VCPKG
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# Setup static files
file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/miniguys/shaders DESTINATION ${PROJECT_BINARY_DIR})

# Main library
add_library(
    ${LIB_NAME} STATIC

    miniguys/saske.c
)

target_compile_features(${LIB_NAME} PRIVATE c_std_17)
target_link_libraries(${LIB_NAME} PUBLIC glad::glad glfw)

# Executable
add_executable(
    ${PROJECT_NAME}

    miniguys/main.c
)

target_compile_features(${PROJECT_NAME} PRIVATE c_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_NAME})

# Test executable
add_executable(
    ${TEST_NAME}

    miniguys/test.c
    miniguys/saske.test.c
)

target_compile_features(${TEST_NAME} PRIVATE c_std_17)
target_link_libraries(${TEST_NAME} PRIVATE ${LIB_NAME})
