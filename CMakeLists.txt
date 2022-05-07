cmake_minimum_required(VERSION 3.21.0)
message("Template library in cmake created by Andrei Turean")
#   there is no need to set the cmp policy 0048 in newer versions of cmake
#   cmake_policy(SET CMP048)

#######################################################
# setting RPATH                                       #
#######################################################

set(CMAKE_INSTALL_RPATH ${ORIGIN})

#######################################################
# project definition                                  #
#######################################################
#   setting the project name, version and language
project(my_lib VERSION 0.1.0)

#   add a normal library and control how it is build using the BUILD_SHARED_LIB flag from the command
#   line interface
add_library(${PROJECT_NAME}
source/source.cxx
)

#   add the include directory to our target as PUBLIC
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>  # <prefix>/include/
)

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

configure_package_config_file(my_lib.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/my_lib.cmake
  INSTALL_DESTINATION ${LIB_INSTALL_DIR}/my_lib/cmake)

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
find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME}_test
test/main.cxx)

gtest_add_tests(TARGET ${PROJECT_NAME}_test
)

target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}_test GTest::gtest GTest::gtest_main)

#######################################################
# cpack                                               #
#######################################################
include(CPack)