#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "qpOASES_e" for configuration "Release"
set_property(TARGET qpOASES_e APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(qpOASES_e PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "m"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libqpOASES_e.so.3.1"
  IMPORTED_SONAME_RELEASE "libqpOASES_e.so.3.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS qpOASES_e )
list(APPEND _IMPORT_CHECK_FILES_FOR_qpOASES_e "${_IMPORT_PREFIX}/lib/libqpOASES_e.so.3.1" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
