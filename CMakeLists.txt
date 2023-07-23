cmake_minimum_required(VERSION 3.15)
project(sanity
        VERSION 0.4.0
        DESCRIPTION "Sanity"
        LANGUAGES CXX
)

option(ENABLE_UNIT_TESTS "Enable building unit tests." OFF)

set(HEADERS
  sanity/sanity.h
)

# Headers that exist, but should not be installed.
# This only exists to satisfy the CMake check script.
set(PRIV_HEADERS
  sanity/pch.h
)

# library
add_library(sanity
  sanity/check.cpp
  sanity/crash_dump.cpp
  sanity/pch.cpp
  sanity/trace.cpp
)
set_target_properties(sanity PROPERTIES
    CXX_STANDARD 20
    PUBLIC_HEADER "${HEADERS}"
)
IF (WIN32)
target_link_libraries(sanity Dbghelp.lib)
ENDIF()


# unit tests
if(ENABLE_UNIT_TESTS)
  enable_testing()
  find_package(GTest CONFIG REQUIRED)
  add_executable(sanity-test
    sanity-test/check_test.cpp
    sanity-test/DebugMonitor.cpp
    sanity-test/main.cpp
    sanity-test/pch.cpp
    sanity-test/trace_test.cpp
  )
  include_directories(.)
  set_target_properties(sanity-test PROPERTIES
      CXX_STANDARD 20
  )
  target_link_libraries(sanity-test PRIVATE sanity GTest::gtest)
  add_test(NAME sanity-test
           COMMAND sanity-test
  )
endif()

# install
install(
  TARGETS sanity
  EXPORT sanityTargets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  PUBLIC_HEADER DESTINATION include/rioki/sanity
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/sanityConfigVersion.cmake"
                                 COMPATIBILITY SameMajorVersion)

configure_package_config_file(${PROJECT_SOURCE_DIR}/sanityConfig.cmake.in
                                sanityConfig.cmake
                                INSTALL_DESTINATION share/sanity)

install(FILES
        "${PROJECT_BINARY_DIR}/sanityConfig.cmake"
        "${PROJECT_BINARY_DIR}/sanityConfigVersion.cmake"
        DESTINATION share/sanity
)

install(EXPORT sanityTargets
        NAMESPACE sanity::
        DESTINATION share/sanity
)