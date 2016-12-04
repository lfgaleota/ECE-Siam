# - Find DUI includes and library
#
# This module defines
#  DUI_INCLUDE_DIRS
#  DUI_LIBRARIES, the libraries to link against to use DUI.
#  DUI_LIBRARY_DIRS, the location of the libraries
#  DUI_FOUND, If false, do not try to use DUI
#
# Copyright © 2016 Horgeon
# Based on a CMake script by Matt Williams
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

IF (DUI_LIBRARIES AND DUI_INCLUDE_DIRS)
	SET(DUI_FIND_QUIETLY TRUE)
ENDIF (DUI_LIBRARIES AND DUI_INCLUDE_DIRS)

SET(DUI_INCLUDE_SEARCH_DIRS
    "${INCLUDE_SEARCH_DIRS}"
    "${CMAKE_INCLUDE_PATH}"
    "/usr/include"
    "/usr/local/include"
    "/usr/include/allegro"
    "/usr/local/include/allegro"
    CACHE STRING ""
    )

SET(DUI_LIBRARY_SEARCH_DIRS
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

IF (NOT DUI_FIND_QUIETLY)
	MESSAGE(STATUS "Looking for DUI")
ENDIF (NOT DUI_FIND_QUIETLY)
FIND_PATH(DUI_INCLUDE_DIRS dui.h ${DUI_INCLUDE_SEARCH_DIRS})
MESSAGE(STATUS "DUI_INCLUDE_DIRS: " ${DUI_INCLUDE_DIRS})

FIND_LIBRARY(DUI_LIBRARY dui)
SET(DUI_LIBRARIES ${DUI_LIBRARY})

#Do some preparation

SET(DUI_INCLUDE_DIRS ${DUI_INCLUDE_DIRS})
SET(DUI_LIBRARIES ${DUI_LIBRARIES})
SET(DUI_LIBRARY_DIRS ${DUI_LIBRARY_DIRS})

MARK_AS_ADVANCED(DUI_INCLUDE_DIRS DUI_LIBRARIES DUI_LIBRARY_DIRS)

IF (DUI_INCLUDE_DIRS AND DUI_LIBRARIES)
	SET(DUI_FOUND TRUE)
ENDIF (DUI_INCLUDE_DIRS AND DUI_LIBRARIES)

IF (DUI_FOUND)
	IF (NOT DUI_FIND_QUIETLY)
		MESSAGE(STATUS "  libraries : ${DUI_LIBRARIES} from ${DUI_LIBRARY_DIRS}")
		MESSAGE(STATUS "  includes  : ${DUI_INCLUDE_DIRS}")
	ENDIF (NOT DUI_FIND_QUIETLY)
ELSE (DUI_FOUND)
	MESSAGE(STATUS "dui not found!")
	IF (DUI_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find DUI. Make sure you have the DUI development headers are installed. Otherwise, try setting LIBRARY_SEARCH_DIRS and INCLUDE_SEARCH_DIRS to the place DUI was installed with -DLIBRARY_SEARCH_DIRS=<path/to/lib> -DINCLUDE_SEARCH_DIRS=<path/to/include>")
	ENDIF (DUI_FIND_REQUIRED)
ENDIF (DUI_FOUND)