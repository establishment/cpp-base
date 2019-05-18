cmake_minimum_required(VERSION 2.8.4)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cppbase)

set(SOURCE_DIR                "src/")
set(INCLUDE_DIR               "src/")

set(CMAKE_CXX_STANDARD 14)

# library
include_directories(${INCLUDE_DIR})
add_library(${PROJECT_NAME} 
    "${SOURCE_DIR}/cppbase/Debug.cpp"
    "${SOURCE_DIR}/cppbase/Logger.cpp"
    "${SOURCE_DIR}/cppbase/OS.cpp"
    "${SOURCE_DIR}/cppbase/RandGenFast.cpp"
    "${SOURCE_DIR}/cppbase/Random.cpp"
    "${SOURCE_DIR}/cppbase/StringUtils.cpp"
    "${SOURCE_DIR}/cppbase/Time.cpp"
)
target_compile_definitions(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}uselib)
target_link_libraries(${PROJECT_NAME} PUBLIC autojson)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

# INTERFACE + LIBRARY
set(INCLUDE_INSTALL_DIR       "include/")
set(SOURCE_INSTALL_DIR        "${INCLUDE_INSTALL_DIR}/${PROJECT_NAME}_src")

install(
    DIRECTORY ${INCLUDE_DIR}
    DESTINATION ${INCLUDE_INSTALL_DIR}
)

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION lib
)
