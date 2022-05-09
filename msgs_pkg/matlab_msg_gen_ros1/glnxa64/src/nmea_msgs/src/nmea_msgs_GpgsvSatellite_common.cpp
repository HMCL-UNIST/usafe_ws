// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for nmea_msgs/GpgsvSatellite
#include "boost/date_time.hpp"
#include "boost/shared_array.hpp"
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4244)
#pragma warning(disable : 4265)
#pragma warning(disable : 4458)
#pragma warning(disable : 4100)
#pragma warning(disable : 4127)
#pragma warning(disable : 4267)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wredundant-decls"
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#pragma GCC diagnostic ignored "-Wdelete-non-virtual-dtor"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wshadow"
#endif //_MSC_VER
#include "ros/ros.h"
#include "nmea_msgs/GpgsvSatellite.h"
#include "visibility_control.h"
#ifndef FOUNDATION_MATLABDATA_API
#include "MDArray.hpp"
#include "StructArray.hpp"
#include "TypedArrayRef.hpp"
#include "Struct.hpp"
#include "ArrayFactory.hpp"
#include "StructRef.hpp"
#include "Reference.hpp"
#endif
#ifndef FOUNDATION_MATLABDATA_API
typedef matlab::data::Array MDArray_T;
typedef matlab::data::ArrayFactory MDFactory_T;
#else
typedef foundation::matlabdata::Array MDArray_T;
typedef foundation::matlabdata::standalone::ClientArrayFactory MDFactory_T;
#endif
namespace nmea_msgs {
namespace matlabhelper {
namespace GpgsvSatellite {
  //----------------------------------------------------------------------------
  NMEA_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<nmea_msgs::GpgsvSatellite>& msg, const matlab::data::StructArray arr) {
    try {
        //prn
        const matlab::data::TypedArray<uint8_t> prn_arr = arr[0]["prn"];
        msg->prn = prn_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'prn' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'prn' is wrong type; expected a uint8.");
    }
    try {
        //elevation
        const matlab::data::TypedArray<uint8_t> elevation_arr = arr[0]["elevation"];
        msg->elevation = elevation_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'elevation' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'elevation' is wrong type; expected a uint8.");
    }
    try {
        //azimuth
        const matlab::data::TypedArray<uint16_t> azimuth_arr = arr[0]["azimuth"];
        msg->azimuth = azimuth_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'azimuth' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'azimuth' is wrong type; expected a uint16.");
    }
    try {
        //snr
        const matlab::data::TypedArray<int8_t> snr_arr = arr[0]["snr"];
        msg->snr = snr_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'snr' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'snr' is wrong type; expected a int8.");
    }
  }
  //----------------------------------------------------------------------------
  NMEA_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const nmea_msgs::GpgsvSatellite>& msg) {
    auto outArray = factory.createStructArray({1,1},{"prn","elevation","azimuth","snr"});
    // prn
    outArray[0]["prn"] = factory.createScalar(msg->prn);
    // elevation
    outArray[0]["elevation"] = factory.createScalar(msg->elevation);
    // azimuth
    outArray[0]["azimuth"] = factory.createScalar(msg->azimuth);
    // snr
    outArray[0]["snr"] = factory.createScalar(msg->snr);
    return std::move(outArray);
  }
} //namespace GpgsvSatellite
} //namespace matlabhelper
} //namespace nmea_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1