cmake_minimum_required(VERSION 2.8)

# Error check up front
IF (NOT DEFINED KANOMI_TRILINOS_DIR)
  MESSAGE(FATAL_ERROR "\nKANOMI Error: cmake must define KANOMI_TRILINOS_DIR:
  (-D CJ_TRILINOS_DIR:FILEPATH=<trilinos_install_prefix>)!")
ENDIF()

# Get Trilinos as one entity
FIND_PACKAGE(Trilinos PATHS ${KANOMI_TRILINOS_DIR}/lib/cmake/Trilinos)

IF(NOT Trilinos_FOUND)
  MESSAGE(FATAL_ERROR "Could not find Trilinos!")
ENDIF()

MESSAGE("\nFound Trilinos!  Here are the details: ")
MESSAGE("   Trilinos_DIR = ${Trilinos_DIR}")
MESSAGE("   Trilinos_VERSION = ${Trilinos_VERSION}")
MESSAGE("   Trilinos_PACKAGE_LIST = ${Trilinos_PACKAGE_LIST}")
MESSAGE("   Trilinos_LIBRARIES = ${Trilinos_LIBRARIES}")
MESSAGE("   Trilinos_INCLUDE_DIRS = ${Trilinos_INCLUDE_DIRS}")
MESSAGE("   Trilinos_LIBRARY_DIRS = ${Trilinos_LIBRARY_DIRS}")
MESSAGE("   Trilinos_TPL_LIST = ${Trilinos_TPL_LIST}")
MESSAGE("   Trilinos_TPL_INCLUDE_DIRS = ${Trilinos_TPL_INCLUDE_DIRS}")
MESSAGE("   Trilinos_TPL_LIBRARIES = ${Trilinos_TPL_LIBRARIES}")
MESSAGE("   Trilinos_TPL_LIBRARY_DIRS = ${Trilinos_TPL_LIBRARY_DIRS}")
MESSAGE("   Trilinos_BUILD_SHARED_LIBS = ${Trilinos_BUILD_SHARED_LIBS}")
MESSAGE("End of Trilinos details\n")

SET(CMAKE_CXX_COMPILER ${Trilinos_CXX_COMPILER} )
SET(CMAKE_C_COMPILER ${Trilinos_C_COMPILER} )

add_definitions("-g -O2")

# End of setup and error checking
#  NOTE: PROJECT command checks for compilers, so this statement
#        is moved AFTER setting CMAKE_CXX_COMPILER opton

PROJECT(Kanomi)

# MPI check -- defaults to TRUE
MESSAGE("-- Checking if MPI is enabled in Trilinos:")
LIST(FIND Trilinos_TPL_LIST MPI MPI_List_ID)
IF (MPI_List_ID GREATER -1)
  MESSAGE("-- Checking if MPI is enabled in Trilinos: MPI ENABLED")
  SET(KANOMI_MPI TRUE)
  ADD_DEFINITIONS(-DKANOMI_MPI)
ELSE()
  MESSAGE("-- Checking if MPI is enabled in Trilinos: MPI NOT ENABLED")
  SET(KANOMI_MPI FALSE)
ENDIF()


################################################################################
# GTest - http://code.google.com/p/googletest/
################################################################################
add_subdirectory(gtest-1.6.0)
enable_testing(true)

add_subdirectory(src)

