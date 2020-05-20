find_package(Check REQUIRED)

include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)

add_executable(test_sort test_sort.c)
include_directories(${CHECK_INCLUDE_DIRS})
target_link_libraries(test_sort soto ${CHECK_LIBRARIES})

add_test(NAME test_sort COMMAND test_sort
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing
)
