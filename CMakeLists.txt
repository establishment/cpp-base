cmake_minimum_required(VERSION 2.8.4)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cppbase)

set(SOURCE_DIR                "cppbase/")
set(INCLUDE_DIR               "cppbase/")

set(CMAKE_CXX_STANDARD 14)
add_definitions(-D${PROJECT_NAME}uselib)

set(LIB_PATH                                   "${CMAKE_CURRENT_SOURCE_DIR}/build/lib")
set(BIN_PATH                                   "${CMAKE_CURRENT_SOURCE_DIR}/build/bin")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_PATH})

# library
include_directories(${INCLUDE_DIR})
add_library(${PROJECT_NAME} 
    "${SOURCE_DIR}/Debug.cpp"
    "${SOURCE_DIR}/Logger.cpp"
    "${SOURCE_DIR}/OS.cpp"
    "${SOURCE_DIR}/RandGenFast.cpp"
    "${SOURCE_DIR}/Random.cpp"
    "${SOURCE_DIR}/StringUtils.cpp"
    "${SOURCE_DIR}/Time.cpp"
)

target_link_libraries(${PROJECT_NAME} autojson)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

# INTERFACE + LIBRARY
set(INCLUDE_INSTALL_DIR       "include/${PROJECT_NAME}")
set(SOURCE_INSTALL_DIR        "${INCLUDE_INSTALL_DIR}/${PROJECT_NAME}/${PROJECT_NAME}_src")

install(
    DIRECTORY ${INCLUDE_DIR}
    DESTINATION ${INCLUDE_INSTALL_DIR}
)

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION lib
)
