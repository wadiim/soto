cmake_minimum_required(VERSION 3.5)
project(soto LANGUAGES C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(GNUInstallDirs)

add_library(${PROJECT_NAME} STATIC
	${CMAKE_SOURCE_DIR}/src/sort_template.c
	${CMAKE_SOURCE_DIR}/src/sort.c
	${CMAKE_SOURCE_DIR}/src/list_template.c
	${CMAKE_SOURCE_DIR}/src/list.c
	${CMAKE_SOURCE_DIR}/src/utils_template.c
	${CMAKE_SOURCE_DIR}/src/utils.c
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

install(TARGETS ${PROJECT_NAME} EXPORT "${PROJECT_NAME}Config"
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT "${PROJECT_NAME}Config" DESTINATION share/${PROJECT_NAME}/cmake)

export(TARGETS ${PROJECT_NAME} FILE "${PROJECT_NAME}Config.cmake")

if(BUILD_TESTING)
	enable_testing()
	add_subdirectory(test)
endif(BUILD_TESTING)
