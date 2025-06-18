cmake_minimum_required(VERSION 3.30)
project(expresscpp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

# Vcpkg toolchain
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# Dependencies
find_package(Crow CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Source files (SANS les headers)
set(SOURCES
        src/app.cpp
        src/request.cpp
        src/response.cpp
        src/router.cpp
)

add_library(expresscpp ${SOURCES})

target_include_directories(expresscpp
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/include
)

target_link_libraries(expresscpp
        PUBLIC
        Crow::Crow
        nlohmann_json::nlohmann_json
)

# Installation
install(TARGETS expresscpp
        EXPORT expresscppTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(DIRECTORY include/expresscpp DESTINATION include)

# Export pour pouvoir trouver la lib en mode développement
export(TARGETS expresscpp
        FILE "${CMAKE_CURRENT_BINARY_DIR}/expresscppTargets.cmake"
)

# Tests
add_subdirectory(tests)