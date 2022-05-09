#ifndef CAN_MSGS__VISIBILITY_CONTROL_H_
#define CAN_MSGS__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define CAN_MSGS_EXPORT __attribute__ ((dllexport))
    #define CAN_MSGS_IMPORT __attribute__ ((dllimport))
  #else
    #define CAN_MSGS_EXPORT __declspec(dllexport)
    #define CAN_MSGS_IMPORT __declspec(dllimport)
  #endif
  #ifdef CAN_MSGS_BUILDING_LIBRARY
    #define CAN_MSGS_PUBLIC CAN_MSGS_EXPORT
  #else
    #define CAN_MSGS_PUBLIC CAN_MSGS_IMPORT
  #endif
  #define CAN_MSGS_PUBLIC_TYPE CAN_MSGS_PUBLIC
  #define CAN_MSGS_LOCAL
#else
  #define CAN_MSGS_EXPORT __attribute__ ((visibility("default")))
  #define CAN_MSGS_IMPORT
  #if __GNUC__ >= 4
    #define CAN_MSGS_PUBLIC __attribute__ ((visibility("default")))
    #define CAN_MSGS_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define CAN_MSGS_PUBLIC
    #define CAN_MSGS_LOCAL
  #endif
  #define CAN_MSGS_PUBLIC_TYPE
#endif
#endif  // CAN_MSGS__VISIBILITY_CONTROL_H_
// Generated 28-Apr-2022 23:52:43
// Copyright 2019-2020 The MathWorks, Inc.
