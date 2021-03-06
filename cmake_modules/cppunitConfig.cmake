# - Find cppunit
# Find the native cppunit includes and library
#
#  CPPUNIT_INCLUDE_DIR - where to find cppunit/Test.h, etc.
#  CPPUNIT_LIBRARIES   - List of libraries when using cppunit.
#  CPPUNIT_FOUND       - True if cppunit found.


IF (CPPUNIT_INCLUDE_DIR)
  # Already in cache, be silent
  SET(CPPUNIT_FIND_QUIETLY TRUE)
ENDIF (CPPUNIT_INCLUDE_DIR)

FIND_PATH(CPPUNIT_INCLUDE_DIR cppunit/Test.h)

SET(CPPUNIT_NAMES cppunit)
FIND_LIBRARY(CPPUNIT_LIBRARY NAMES ${CPPUNIT_NAMES} )

# handle the QUIETLY and REQUIRED arguments and set CPPUNIT_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CppUnit DEFAULT_MSG CPPUNIT_LIBRARY CPPUNIT_INCLUDE_DIR)

IF(CPPUNIT_FOUND)
  SET( CPPUNIT_LIBRARIES ${CPPUNIT_LIBRARY} )
ELSE(CPPUNIT_FOUND)
  SET( CPPUNIT_LIBRARIES )
ENDIF(CPPUNIT_FOUND)

MARK_AS_ADVANCED( CPPUNIT_LIBRARY CPPUNIT_INCLUDE_DIR )
