cmake_minimum_required(VERSION 2.8)

# Auto-version generation
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Kanomi_autoversion.hpp
    COMMAND ${PROJECT_SOURCE_DIR}/create-version-header.sh ${PROJECT_SOURCE_DIR}/version-gen.sh ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS 
    COMMENT "Generating auto-version header file from Git..."
    ALL
)

#
# External dependencies and paths
#
find_package(Boost 1.46.0 REQUIRED)
include_directories (
    .
    ${Boost_INCLUDE_DIRS}
    ${Trilinos_INCLUDE_DIRS}
    ${Trilinos_TPL_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR} # for Kanomi_version.hpp
)

link_directories (
    ${Trilinos_LIBRARY_DIRS} 
    ${Trilinos_TPL_LIBRARY_DIRS} 
)

#
# The kanomi library
#
SET ( SOURCES
    Kanomi_Demangle.cpp
    Kanomi_Stencils.cpp
    Kanomi_version.cpp
)

SET ( HEADERS
    ${CMAKE_CURRENT_BINARY_DIR}/Kanomi_autoversion.hpp
    Kanomi_BasisFunction.hpp
    Kanomi_Build.hpp
    Kanomi_ConstantScalar.hpp
    Kanomi_Demangle.hpp
    Kanomi_EnergyResidual.hpp
    Kanomi_EQ.hpp
    Kanomi_EQ_Energy.hpp
    Kanomi_Factory.hpp
    Kanomi_Factory_ThermalConductivity.hpp
    Kanomi_FieldNames.hpp
    Kanomi_GradScalarField.hpp
    Kanomi_Manager.hpp
    Kanomi_mpl.hpp
    Kanomi_Named.hpp
    Kanomi_OutputGraphviz.hpp
    Kanomi_provider.hpp
    Kanomi_ScalarField.hpp
    Kanomi_ScalarPolynomial.hpp
    Kanomi_Stencils.hpp
    Kanomi_TypeInfo.hpp
    Kanomi_version.hpp
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
