cmake_minimum_required(VERSION 3.10)
project(HashedVebTreeMap VERSION 0.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR}/dependencies)
find_package(GTest CONFIG REQUIRED)

add_subdirectory(HashedVEBTreeMap)

add_executable(Exec src/main.cpp)
target_link_libraries(Exec HashedVEBTree)
target_include_directories(Exec PUBLIC
        "${PROJECT_BINARY_DIR}"
        )

option(ENABLE_TESTING "Add Tests To Build" OFF)
if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(Tests)
endif()

