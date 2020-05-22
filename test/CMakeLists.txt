find_package(Check REQUIRED)

include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)

set(TESTS test_sort test_list)

foreach(TEST ${TESTS})
	add_executable(${TEST} ${TEST}.c)
	include_directories(${CHECK_INCLUDE_DIRS})
	target_link_libraries(${TEST} soto ${CHECK_LIBRARIES})

	add_test(NAME ${TEST} COMMAND ${TEST}
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing
	)
endforeach(TEST ${TESTS})
