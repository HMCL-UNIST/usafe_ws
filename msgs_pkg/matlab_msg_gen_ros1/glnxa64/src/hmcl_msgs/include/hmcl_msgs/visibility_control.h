#ifndef HMCL_MSGS__VISIBILITY_CONTROL_H_
#define HMCL_MSGS__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define HMCL_MSGS_EXPORT __attribute__ ((dllexport))
    #define HMCL_MSGS_IMPORT __attribute__ ((dllimport))
  #else
    #define HMCL_MSGS_EXPORT __declspec(dllexport)
    #define HMCL_MSGS_IMPORT __declspec(dllimport)
  #endif
  #ifdef HMCL_MSGS_BUILDING_LIBRARY
    #define HMCL_MSGS_PUBLIC HMCL_MSGS_EXPORT
  #else
    #define HMCL_MSGS_PUBLIC HMCL_MSGS_IMPORT
  #endif
  #define HMCL_MSGS_PUBLIC_TYPE HMCL_MSGS_PUBLIC
  #define HMCL_MSGS_LOCAL
#else
  #define HMCL_MSGS_EXPORT __attribute__ ((visibility("default")))
  #define HMCL_MSGS_IMPORT
  #if __GNUC__ >= 4
    #define HMCL_MSGS_PUBLIC __attribute__ ((visibility("default")))
    #define HMCL_MSGS_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define HMCL_MSGS_PUBLIC
    #define HMCL_MSGS_LOCAL
  #endif
  #define HMCL_MSGS_PUBLIC_TYPE
#endif
#endif  // HMCL_MSGS__VISIBILITY_CONTROL_H_
// Generated 28-Apr-2022 23:52:47
// Copyright 2019-2020 The MathWorks, Inc.
