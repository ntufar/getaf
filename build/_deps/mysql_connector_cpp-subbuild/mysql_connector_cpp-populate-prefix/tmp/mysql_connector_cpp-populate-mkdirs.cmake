# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/projects/getaf/build/_deps/mysql_connector_cpp-src")
  file(MAKE_DIRECTORY "C:/projects/getaf/build/_deps/mysql_connector_cpp-src")
endif()
file(MAKE_DIRECTORY
  "C:/projects/getaf/build/_deps/mysql_connector_cpp-build"
  "C:/projects/getaf/build/_deps/mysql_connector_cpp-subbuild/mysql_connector_cpp-populate-prefix"
  "C:/projects/getaf/build/_deps/mysql_connector_cpp-subbuild/mysql_connector_cpp-populate-prefix/tmp"
  "C:/projects/getaf/build/_deps/mysql_connector_cpp-subbuild/mysql_connector_cpp-populate-prefix/src/mysql_connector_cpp-populate-stamp"
  "C:/projects/getaf/build/_deps/mysql_connector_cpp-subbuild/mysql_connector_cpp-populate-prefix/src"
  "C:/projects/getaf/build/_deps/mysql_connector_cpp-subbuild/mysql_connector_cpp-populate-prefix/src/mysql_connector_cpp-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/projects/getaf/build/_deps/mysql_connector_cpp-subbuild/mysql_connector_cpp-populate-prefix/src/mysql_connector_cpp-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/projects/getaf/build/_deps/mysql_connector_cpp-subbuild/mysql_connector_cpp-populate-prefix/src/mysql_connector_cpp-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
