cmake_minimum_required(VERSION 3.28)

# Generate compile_commands.json for clangd
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    Mousir
    VERSION 1.0.0.0
    LANGUAGES CXX
)

# cache variables for installation destinations
include(GNUInstallDirs)

add_library(MousirFacilities INTERFACE)

set_target_properties(MousirFacilities PROPERTIES
    OUTPUT_NAME MousirFacilities
    EXPORT_NAME Facilities
)

target_include_directories(MousirFacilities INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Test
if(CMAKE_SOURCE_DIR STREQUAL Mousir_SOURCE_DIR OR TEST_Mousir)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TestMousir
    ${CMAKE_CURRENT_LIST_DIR}/tests/tests.cpp
)

target_include_directories(TestMousir
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}
)


find_package(Conceptrodon REQUIRED CONFIG)
target_link_libraries(TestMousir PRIVATE Conceptrodon::Facilities)

endif()


install(
    TARGETS MousirFacilities
    EXPORT Mousir
)

install(
    DIRECTORY Mousir
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT Mousir
    FILE Mousir.cmake
    NAMESPACE Mousir::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Mousir
)

# include the package config helpers and generate the file below
include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/MousirConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Mousir
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/MousirConfig.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Mousir
)