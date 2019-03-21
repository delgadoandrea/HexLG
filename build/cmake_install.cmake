# Install script for directory: /Users/1zd/HexLG

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/1zd/HexLG/build/lib/libHexLGCommon.0.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/1zd/HexLG/build/lib" TYPE SHARED_LIBRARY FILES "/Users/1zd/HexLG/build/lib/libHexLGCommon.0.so")
  if(EXISTS "$ENV{DESTDIR}/Users/1zd/HexLG/build/lib/libHexLGCommon.0.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/1zd/HexLG/build/lib/libHexLGCommon.0.so")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/usr/local/lib/root"
      "$ENV{DESTDIR}/Users/1zd/HexLG/build/lib/libHexLGCommon.0.so")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/1zd/geant4.10.05-install/lib"
      "$ENV{DESTDIR}/Users/1zd/HexLG/build/lib/libHexLGCommon.0.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" "$ENV{DESTDIR}/Users/1zd/HexLG/build/lib/libHexLGCommon.0.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/1zd/HexLG/build/lib/libHexLGCommon.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/1zd/HexLG/build/lib" TYPE SHARED_LIBRARY FILES "/Users/1zd/HexLG/build/lib/libHexLGCommon.so")
  if(EXISTS "$ENV{DESTDIR}/Users/1zd/HexLG/build/lib/libHexLGCommon.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/1zd/HexLG/build/lib/libHexLGCommon.so")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/usr/local/lib/root"
      "$ENV{DESTDIR}/Users/1zd/HexLG/build/lib/libHexLGCommon.so")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/1zd/geant4.10.05-install/lib"
      "$ENV{DESTDIR}/Users/1zd/HexLG/build/lib/libHexLGCommon.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" "$ENV{DESTDIR}/Users/1zd/HexLG/build/lib/libHexLGCommon.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/1zd/HexLG/build/bin/HexLG")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/1zd/HexLG/build/bin" TYPE EXECUTABLE FILES "/Users/1zd/HexLG/build/bin/HexLG")
  if(EXISTS "$ENV{DESTDIR}/Users/1zd/HexLG/build/bin/HexLG" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/1zd/HexLG/build/bin/HexLG")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/usr/local/lib/root"
      "$ENV{DESTDIR}/Users/1zd/HexLG/build/bin/HexLG")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/1zd/HexLG/build/lib"
      "$ENV{DESTDIR}/Users/1zd/HexLG/build/bin/HexLG")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/1zd/geant4.10.05-install/lib"
      "$ENV{DESTDIR}/Users/1zd/HexLG/build/bin/HexLG")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" "$ENV{DESTDIR}/Users/1zd/HexLG/build/bin/HexLG")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/1zd/HexLG/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
