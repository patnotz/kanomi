cmake_minimum_required(VERSION 2.8)

#
# External dependencies and paths
#
find_package(Boost 1.46.0 REQUIRED)
include_directories (
    .
    ${Boost_INCLUDE_DIRS}
    ${Trilinos_INCLUDE_DIRS}
    ${Trilinos_TPL_INCLUDE_DIRS}
)

link_directories (
    ${Trilinos_LIBRARY_DIRS} 
    ${Trilinos_TPL_LIBRARY_DIRS} 
)

#
# The kanomi library
#
SET ( SOURCES
    Kanomi_Stencils.cpp
)

SET ( HEADERS
    Kanomi_Manager.hpp
    Kanomi_ScalarField.hpp
    Kanomi_Stencils.hpp
    Kanomi_TypeInfo.hpp
)

add_library(kanomiLib ${SOURCES} ${HEADERS})

SET ( kanomi_LIBRARIES
    kanomiLib
)

#
# The kanomi executable
#
add_executable ( kanomi Kanomi_main.cpp)

target_link_libraries ( kanomi 
    ${kanomi_LIBRARIES} 
    ${Boost_LIBRARIES}
	${Trilinos_LIBRARIES}
	${Trilinos_TPL_LIBRARIES}
) 
