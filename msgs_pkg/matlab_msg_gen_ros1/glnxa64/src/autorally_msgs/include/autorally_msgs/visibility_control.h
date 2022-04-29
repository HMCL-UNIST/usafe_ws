#ifndef AUTORALLY_MSGS__VISIBILITY_CONTROL_H_
#define AUTORALLY_MSGS__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define AUTORALLY_MSGS_EXPORT __attribute__ ((dllexport))
    #define AUTORALLY_MSGS_IMPORT __attribute__ ((dllimport))
  #else
    #define AUTORALLY_MSGS_EXPORT __declspec(dllexport)
    #define AUTORALLY_MSGS_IMPORT __declspec(dllimport)
  #endif
  #ifdef AUTORALLY_MSGS_BUILDING_LIBRARY
    #define AUTORALLY_MSGS_PUBLIC AUTORALLY_MSGS_EXPORT
  #else
    #define AUTORALLY_MSGS_PUBLIC AUTORALLY_MSGS_IMPORT
  #endif
  #define AUTORALLY_MSGS_PUBLIC_TYPE AUTORALLY_MSGS_PUBLIC
  #define AUTORALLY_MSGS_LOCAL
#else
  #define AUTORALLY_MSGS_EXPORT __attribute__ ((visibility("default")))
  #define AUTORALLY_MSGS_IMPORT
  #if __GNUC__ >= 4
    #define AUTORALLY_MSGS_PUBLIC __attribute__ ((visibility("default")))
    #define AUTORALLY_MSGS_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define AUTORALLY_MSGS_PUBLIC
    #define AUTORALLY_MSGS_LOCAL
  #endif
  #define AUTORALLY_MSGS_PUBLIC_TYPE
#endif
#endif  // AUTORALLY_MSGS__VISIBILITY_CONTROL_H_
// Generated 28-Apr-2022 23:48:57
// Copyright 2019-2020 The MathWorks, Inc.
