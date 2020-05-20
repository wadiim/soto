# FindCheck
# --------
#
# Find Check include dir and libraries
#
# This module reads hint about search locations from variable:
#
#  CHECK_INSTALL_DIR   - Preferred installation prefix
#
# This script creates the following variables:
#
#  CHECK_FOUND         - Boolean that indicates if the package was found
#  CHECK_INCLUDE_DIRS  - Path to the Check include directory
#  CHECK_LIBRARIES     - Package library

# Look for Check include dir
find_path(CHECK_INCLUDE_DIRS
	NAMES check.h
        HINTS $ENV{CHECK_INSTALL_DIR} ${CHECK_INSTALL_DIR}
        PATHS /usr/local /usr /opt/local
        PATH_SUFFIXES include
)

# Look for Check libraries
find_library(CHECK_LIBRARIES
	NAMES check
        HINTS $ENV{CHECK_INSTALL_DIR} ${CHECK_INSTALL_DIR}
        PATHS /usr/local /usr /opt/local
        PATH_SUFFIXES lib
)

# Set CHECK_FOUND honoring the QUIET and REQUIRED arguments
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
	Check
	DEFAULT_MSG
	CHECK_LIBRARIES CHECK_INCLUDE_DIRS
)
