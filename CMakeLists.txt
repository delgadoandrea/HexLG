
#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(HexLG)

###############
# Random tweaks
###############

# force using absolute paths to linked libraries
# fixes a problem where hdf5 libraries were shortened to relative -lhdf5
# without full link path being specified (resulting in link errors)
cmake_policy(SET CMP0060 NEW)

#For Mac OS X Use @rpath on OS X
if(APPLE)
  if(POLICY CMP0042)
      CMAKE_POLICY(SET CMP0042 NEW)
   endif()
endif()

set(CMAKE_BUILD_TYPE release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")


##############
# Output paths
##############

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")


########
# Locate sources and headers for this project
# need PrimaryGeneratorAction and DetectorConstructionBase first for static initialization order
file(GLOB sources
#        ${PROJECT_SOURCE_DIR}/src/HexLGDetectorConstructionBase.cc
#        ${PROJECT_SOURCE_DIR}/src/HexLGPrimaryGeneratorAction.cc
        ${PROJECT_SOURCE_DIR}/src/*.cc
        ${PROJECT_SOURCE_DIR}/src/*/*.cc )
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh ${PROJECT_SOURCE_DIR}/include/*/*.hh)

# macro to find all subdirectories of include/ containing headers
MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list ${PROJECT_SOURCE_DIR}/include/*/*.hh)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

HEADER_DIRECTORIES(mylist)
INCLUDE_DIRECTORIES(${mylist} ${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
option(WITH_GEANT4_UIVIS "Build with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()
include(${Geant4_USE_FILE})
Message("Geant4_USE_FILE = ${Geant4_USE_FILE}")

###############
# ROOT and dictionaries
###############

find_package(ROOT REQUIRED COMPONENTS Core MathCore MathMore RIO Tree)
include_directories(${ROOT_INCLUDE_DIRS})
#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
message("ROOT_USE_FILE: ${ROOT_USE_FILE}")
include("${ROOT_USE_FILE}")

#ROOT_GENERATE_DICTIONARY(AD1Common_Dict "include/Event.hh" LINKDEF "include/EventLinkDef.h" OPTIONS "")
ROOT_GENERATE_DICTIONARY(HexLGCommon_Dict OPTIONS "")
list(APPEND sources "HexLGCommon_Dict.cxx")

######
# HDF5
######

find_package(HDF5 REQUIRED COMPONENTS C HL)
message("Including HDF5 paths '${HDF5_INCLUDE_DIRS}' and libraries '${HDF5_LIBRARIES}' in '${HDF5_LIBRARY_DIRS}'")
include_directories(${HDF5_INCLUDE_DIRS})

###############
# Everything glommed together as library
###############
add_library(HexLGCommon SHARED ${sources} ${headers})
SET(SB_G4_LIBRARY_PROPERTIES
    ${SB_G4_LIBRARY_PROPERTIES}
    VERSION "0"
    SOVERSION "0"
    SUFFIX ".so"
)
set_target_properties(HexLGCommon PROPERTIES ${SB_G4_LIBRARY_PROPERTIES})
install(TARGETS HexLGCommon DESTINATION ${LIBRARY_OUTPUT_PATH})
link_directories(${LIBRARY_OUTPUT_PATH})

# need this on *some* systems:
target_link_libraries(HexLGCommon ${ROOT_LIBRARIES} MathMore ${Geant4_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_HL_LIBRARIES})


#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
#file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
#file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
#add_executable(AD1 AD1Main.cc ${sources} ${headers})
add_executable(HexLG HexLG.cc)
#target_link_libraries(AD1 ${Geant4_LIBRARIES})
target_link_libraries(HexLG ${ROOT_LIBRARIES} MathMore ${Geant4_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_HL_LIBRARIES} HexLGCommon)

if(PROFILE_RUN)
    add_definitions(-DPROFILE_RUN)
endif()

add_custom_command(TARGET HexLG POST_BUILD
    COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/*HexLGCommon_Dict_rdict.pcm ${LIBRARY_OUTPUT_PATH}
)

install(TARGETS HexLG DESTINATION ${EXECUTABLE_OUTPUT_PATH})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
#set(EXAMPLEB1_SCRIPTS
#  AD1Main.in
#  AD1Main.out
#  init_vis.mac
#  run1.mac
#  run2.mac
#  vis.mac
#  )

#foreach(_script ${EXAMPLEB1_SCRIPTS})
#  configure_file(
#    ${PROJECT_SOURCE_DIR}/${_script}
#    ${PROJECT_BINARY_DIR}/${_script}
#    COPYONLY
#    )
#endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
#add_custom_target(AD1 DEPENDS AD1)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
#install(TARGETS AD1 DESTINATION bin)

