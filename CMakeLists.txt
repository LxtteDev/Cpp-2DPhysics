cmake_minimum_required(VERSION 3.0.0)
project(Physics VERSION 0.1.0)

include(FetchContent)
set(BUILD_SHARED_LIBS  OFF)
FetchContent_Declare(
 SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

include(CTest)
enable_testing()

file(GLOB source
    "src/**/*.h"
    "src/**/*.cpp"
)

add_executable(Physics src/main.cpp ${source})
# file(COPY ${CMAKE_SOURCE_DIR}/content DESTINATION ${CMAKE_BINARY_DIR}/Debug) # Copy assets

target_link_libraries(Physics sfml-graphics)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
