cmake_minimum_required(VERSION 3.5.1)

project(libTE)

option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
	enable_testing()
endif()

set(sources
	threshold_encryption.cpp
)

set(headers
	threshold_encryption.h
)

set(PROJECT_VERSION 0.1.0)

set (THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../)

add_library(te ${sources} ${headers})

include_directories(${CMAKE_BINARY_DIR})
link_directories(${CMAKE_BINARY_DIR})

add_dependencies(te gmp)
target_include_directories(te PRIVATE ${GMP_INCLUDE_DIR})
target_link_libraries(te PRIVATE ${GMPXX_LIBRARY} ${GMP_LIBRARY})

include(deps/ProjectPBC.cmake)

include_directories(${CMAKE_BINARY_DIR}/deps/include ${PBC_INCLUDE_DIR})
link_directories(${CMAKE_BINARY_DIR}/deps/lib)

add_dependencies(te pbc)
target_include_directories(te PRIVATE ${PBC_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${THIRD_PARTY_DIR})
target_link_libraries(te PRIVATE ${PBC_LIBRARY})


if (BUILD_TESTS)
	add_executable(te_unit_test unit_tests_te.cpp)
	target_include_directories(te_unit_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${THIRD_PARTY_DIR})
	target_link_libraries(te_unit_test PRIVATE te ${PBC_LIBRARY} ${GMP_LIBRARY})

	add_test(NAME te_tests COMMAND te_unit_test)

	add_custom_target(all_te_tests
		COMMAND ./te_unit_test
		DEPENDS te_unit_test
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Run all TE tests"
		)
endif()