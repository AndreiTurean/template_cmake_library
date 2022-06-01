cmake_minimum_required(VERSION 3.16.0)
message("Template library in CMake created by Andrei Turean")
#   there is no need to set the cmp policy 0048 in newer versions of cmake
#   cmake_policy(SET CMP048)

#######################################################
# setting RPATH                                       #
#######################################################

set(CMAKE_INSTALL_RPATH ${ORIGIN})

#######################################################
# output artifacts redirect                           #
#######################################################

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# for a bigger project maybe you want to set for each target where the build output directory
# will be built. Instead of setting the cache variable in the top level CMake file you can instead
# set it with for each target as follows:

#set_target_properties( ${PROJECT_NAME}
#    PROPERTIES
#    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
#)

# for a small project like this one you don't need to bother with setting per target since
# there are only two targets, the library and the unit test.

#######################################################
# misc                                                #
#######################################################

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_DEBUG_POSTFIX "_debug")

# Set the build type if not set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
endif()

#######################################################
# project definition                                  #
#######################################################
#   setting the project name, version and language
project(my_lib VERSION 0.1.0)

#   add a normal library and control how it is build using the BUILD_SHARED_LIB flag from the command
#   line interface
#   https://cmake.org/cmake/help/latest/variable/BUILD_SHARED_LIBS.html

add_library(${PROJECT_NAME}
source/source.cxx
)

#   add the include directory to our target as PUBLIC
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>  # <prefix>/include/
)

#######################################################
# setting target compile feature/options              #
#######################################################
# https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)


target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX> # setting the W4 warning level for MSVC compilers
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror> # setting the Wall for other compilers
)

if(RASPBIAN)
  # Not actually needed, just there for convenience
  target_compile_definitions(${PROJECT_NAME} PUBLIC -D__RASPBIAN__)
endif()

#######################################################
# defining visibility control                         #
#######################################################

#   setting the visibility as as hidden for GCC compiler
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

#   create the visibility header
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

#######################################################
# package versioning                                  #
#######################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
SOVERSION 0
VERSION 0.1.0)

include(CMakePackageConfigHelpers)

configure_package_config_file(${PROJECT_NAME}.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.cmake
  INSTALL_DESTINATION ${LIB_INSTALL_DIR}/${PROJECT_NAME}/cmake)

write_basic_package_version_file(
  ${PROJECT_NAME}ConfigVersion.cmake
  VERSION 0.1.0
  COMPATIBILITY SameMajorVersion
)

#######################################################
# install step                                        #
#######################################################
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT RUNTIME
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT RUNTIME
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT DEVELOPMENT
)

install(FILES
 include/source.hpp
 ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_export.h DESTINATION include ${INCLUDE_INSTALL_DIR}
)


#######################################################
# test step                                           #
#######################################################

include(GoogleTest)
enable_testing()

add_executable(${PROJECT_NAME}_test
test/main.cxx)

# packages are getted using the vcpkg package manager
find_package(GTest REQUIRED)
target_link_libraries(${PROJECT_NAME}_test PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

gtest_add_tests(TARGET ${PROJECT_NAME}_test)

target_link_libraries(${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME})

#######################################################
# cpack                                               #
#######################################################
include(CPack)