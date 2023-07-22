cmake_minimum_required(VERSION 3.15)
project(rioki_sanity
        VERSION 0.4.0
        DESCRIPTION "Sanity"
        LANGUAGES CXX
)

option(ENABLE_UNIT_TESTS "Enable building unit tests." OFF)

set(HEADERS
  sanity/sanity.h
)

# library
add_library(rioki_sanity
  sanity/check.cpp
  sanity/crash_dump.cpp
  sanity/pch.cpp
  sanity/trace.cpp
)
set_target_properties(rioki_sanity PROPERTIES
    CXX_STANDARD 20
    PUBLIC_HEADER "${HEADERS}"
)


# unit tests
if(ENABLE_UNIT_TESTS)
  find_package(GTest CONFIG REQUIRED)
  add_executable(sanity-test
    sanity-test/check_test.cpp
    sanity-test/DebugMonitor.cpp
    sanity-test/main.cpp
    sanity-test/pch.cpp
    sanity-test/trace_test.cpp
  )
  include_directories(.)
  target_compile_features(sanity-test PRIVATE cxx_std_20)
  set_target_properties(sanity PROPERTIES
      CXX_STANDARD 20
  )
  target_link_libraries(sanity-test PRIVATE sanity GTest::gtest)
  add_test(NAME sanity-test
           COMMAND sanity-test
  )
endif()

# install
install(
  TARGETS rioki_sanity
  EXPORT rioki_sanityTargets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  PUBLIC_HEADER DESTINATION include/rioki/sanity
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/rioki_sanityConfigVersion.cmake"
                                 COMPATIBILITY SameMajorVersion)

configure_package_config_file(${PROJECT_SOURCE_DIR}/rioki_sanityConfig.cmake.in
                                rioki_sanityConfig.cmake
                                INSTALL_DESTINATION share/rioki_sanity)

install(FILES
        "${PROJECT_BINARY_DIR}/rioki_sanityConfig.cmake"
        "${PROJECT_BINARY_DIR}/rioki_sanityConfigVersion.cmake"
        DESTINATION share/rioki_sanity
)

install(EXPORT rioki_sanityTargets
        NAMESPACE rioki_sanity::
        DESTINATION share/rioki_sanity
)