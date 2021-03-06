# - Try to find GLOOX
# Find GLOOX headers, libraries and the answer to all questions.
#
#  GLOOX_FOUND               True if gloox got found
#  GLOOX_INCLUDE_DIR        Location of gloox headers 
#  GLOOX_LIBRARIES           List of libaries to use gloox 
#
# Copyright (c) 2009 Nigmatullin Ruslan <euroelessar@gmail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

FIND_PATH( GLOOX_INCLUDE_DIR "gloox/gloox.h" )
FIND_LIBRARY( GLOOX_LIBRARIES gloox )

if( GLOOX_LIBRARIES AND GLOOX_INCLUDE_DIR )
	if(DEFINED WITH_STATIC_GLOOX)
		message( STATUS "Found gloox: ${WITH_STATIC_GLOOX} ${GLOOX_INCLUDE_DIR}")
	else(DEFINED WITH_STATIC_GLOOX)
		message( STATUS "Found gloox: ${GLOOX_LIBRARIES} ${GLOOX_INCLUDE_DIR}" )
	endif(DEFINED WITH_STATIC_GLOOX)
	set( GLOOX_FOUND 1 )
else( GLOOX_LIBRARIES AND GLOOX_INCLUDE_DIR )
	message( FATAL_ERROR "Could NOT find gloox" )
endif( GLOOX_LIBRARIES AND GLOOX_INCLUDE_DIR )
