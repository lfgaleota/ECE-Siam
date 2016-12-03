# - Find FBLEND includes and library
#
# This module defines
#  FBLEND_INCLUDE_DIRS
#  FBLEND_LIBRARIES, the libraries to link against to use FBLEND.
#  FBLEND_LIBRARY_DIRS, the location of the libraries
#  FBLEND_FOUND, If false, do not try to use FBLEND
#
# Copyright © 2016 Horgeon
# Based on a CMake script by Matt Williams
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

IF (FBLEND_LIBRARIES AND FBLEND_INCLUDE_DIRS)
	SET(FBLEND_FIND_QUIETLY TRUE)
ENDIF (FBLEND_LIBRARIES AND FBLEND_INCLUDE_DIRS)

SET(FBLEND_INCLUDE_SEARCH_DIRS
    "${INCLUDE_SEARCH_DIRS}"
    "${CMAKE_INCLUDE_PATH}"
    "/usr/include"
    "/usr/local/include"
    "/usr/include/allegro"
    "/usr/local/include/allegro"
    CACHE STRING ""
    )

SET(FBLEND_LIBRARY_SEARCH_DIRS
    "${LIBRARY_SEARCH_DIRS}"
    "${CMAKE_LIBRARY_PATH}"
    "/usr/lib"
    "/usr/lib64"
    "/usr/local/lib"
    "/usr/local/lib64"
    "/opt/lib"
    "/opt/lib64"
    CACHE STRING ""
    )

IF (NOT FBLEND_FIND_QUIETLY)
	MESSAGE(STATUS "Looking for FBlend")
ENDIF (NOT FBLEND_FIND_QUIETLY)
FIND_PATH(FBLEND_INCLUDE_DIRS fblend.h ${FBLEND_INCLUDE_SEARCH_DIRS})
MESSAGE(STATUS "FBLEND_INCLUDE_DIRS: " ${FBLEND_INCLUDE_DIRS})

FIND_LIBRARY(FBLEND_LIBRARY fblend)
SET(FBLEND_LIBRARIES ${FBLEND_LIBRARY})

#Do some preparation

SET(FBLEND_INCLUDE_DIRS ${FBLEND_INCLUDE_DIRS})
SET(FBLEND_LIBRARIES ${FBLEND_LIBRARIES})
SET(FBLEND_LIBRARY_DIRS ${FBLEND_LIBRARY_DIRS})

MARK_AS_ADVANCED(FBLEND_INCLUDE_DIRS FBLEND_LIBRARIES FBLEND_LIBRARY_DIRS)

IF (FBLEND_INCLUDE_DIRS AND FBLEND_LIBRARIES)
	SET(FBLEND_FOUND TRUE)
ENDIF (FBLEND_INCLUDE_DIRS AND FBLEND_LIBRARIES)

IF (FBLEND_FOUND)
	IF (NOT FBLEND_FIND_QUIETLY)
		MESSAGE(STATUS "  libraries : ${FBLEND_LIBRARIES} from ${FBLEND_LIBRARY_DIRS}")
		MESSAGE(STATUS "  includes  : ${FBLEND_INCLUDE_DIRS}")
	ENDIF (NOT FBLEND_FIND_QUIETLY)
ELSE (FBLEND_FOUND)
	MESSAGE(STATUS "fblend not found!")
	IF (FBLEND_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find FBLend. Make sure you have the FBLend development headers are installed. Otherwise, try setting LIBRARY_SEARCH_DIRS and INCLUDE_SEARCH_DIRS to the place FBLend was installed with -DLIBRARY_SEARCH_DIRS=<path/to/lib> -DINCLUDE_SEARCH_DIRS=<path/to/include>")
	ENDIF (FBLEND_FIND_REQUIRED)
ENDIF (FBLEND_FOUND)