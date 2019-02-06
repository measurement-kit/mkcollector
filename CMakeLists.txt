cmake_minimum_required(VERSION 3.1.0)
project(mkcollector LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")
include(MkUtils)

# Download dependencies
# ---------------------

MkDownloadCatchorgCatch2()
MkDownloadMeasurementKitMkCurl()
MkDownloadMeasurementKitMkMock()
MkDownloadNlohmannJson()
MkDownloadCaBundle()

if("${MSVC}")
  MkDownloadMeasurementKitPrebuiltWindowsCurl()
  list(APPEND CMAKE_INCLUDE_PATH "${MK_WINDOWS_CURL_INCLUDE_PATH}")
  list(APPEND CMAKE_LIBRARY_PATH "${MK_WINDOWS_CURL_LIBRARY_PATH}")
  add_definitions(${MK_WINDOWS_CURL_DEFINITIONS})
  list(APPEND MKCOLLECTOR_LIBS ${MK_WINDOWS_CURL_EXTRA_LINK_LIBS})
endif()

# Checks
# ------

find_package(CURL REQUIRED)

# Compiler flags
# --------------

MkSetCompilerFlags()

# Library and binary
# ------------------

set(MKCOLLECTOR_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
    ${CURL_INCLUDE_DIRS} ${CMAKE_REQUIRED_INCLUDES})

add_library(mkcollector mkcollector.cpp)
list (APPEND MKCOLLECTOR_LIBS ${CURL_LIBRARIES})
if("${WIN32}" OR "${MINGW}")
  list(APPEND MKCOLLECTOR_LIBS "ws2_32")
  if ("${MINGW}")
      list(APPEND MKCOLLECTOR_LIBS -static-libgcc -static-libstdc++)
  endif()
endif()
list(APPEND MKCOLLECTOR_LIBS Threads::Threads)

# Testing
# -------

set(BUILD_TESTING "ON" CACHE BOOL "Whether to build tests")
if(${BUILD_TESTING})
  add_executable(integration-tests integration-tests.cpp)
  target_include_directories(integration-tests PUBLIC ${MKCOLLECTOR_INCLUDES})
  target_link_libraries(integration-tests "${MKCOLLECTOR_LIBS}" mkcollector)
  add_executable(tests tests.cpp)
  target_include_directories(tests PUBLIC ${MKCOLLECTOR_INCLUDES})
  target_link_libraries(tests "${MKCOLLECTOR_LIBS}")
  enable_testing()
  add_test(NAME integration_tests COMMAND integration-tests)
  add_test(NAME mocked_tests COMMAND tests)
endif()
