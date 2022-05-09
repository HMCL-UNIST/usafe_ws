// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for autorally_msgs/neuralNetModel
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
#include "autorally_msgs/neuralNetModel.h"
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
namespace autorally_msgs {
namespace matlabhelper {
namespace neuralNetModel {
  void copy_from_arr_std_msgs_Header(std_msgs::Header& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const autorally_msgs::neuralNetModel::_header_type& val);
  void copy_from_arr_ros_Time(ros::Time& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_ros_Time(MDFactory_T& factory, const std_msgs::Header::_stamp_type& val);
  void copy_from_arr_autorally_msgs_neuralNetLayer_var_arr(autorally_msgs::neuralNetLayer& val, const matlab::data::Struct& arr);
  MDArray_T get_arr_autorally_msgs_neuralNetLayer_var_arr(MDFactory_T& factory, const autorally_msgs::neuralNetModel::_network_type& val);
  //----------------------------------------------------------------------------
  void copy_from_arr_std_msgs_Header(std_msgs::Header& val, const matlab::data::StructArray& arr) {
    // _std_msgs_Header.seq
    try {
        const matlab::data::TypedArray<uint32_t> _headerseq_arr = arr[0]["seq"];
        val.seq = _headerseq_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'seq' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'seq' is wrong type; expected a uint32.");
    }
    // _std_msgs_Header.stamp
    try {
        const matlab::data::StructArray _headerstamp_arr = arr[0]["stamp"];
        copy_from_arr_ros_Time(val.stamp,_headerstamp_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'stamp' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'stamp' is wrong type; expected a struct.");
    }
    // _std_msgs_Header.frame_id
    try {
        const matlab::data::CharArray _headerframe_id_arr = arr[0]["frame_id"];
        val.frame_id = _headerframe_id_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'frame_id' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'frame_id' is wrong type; expected a string.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const autorally_msgs::neuralNetModel::_header_type& val) {
    auto _headeroutArray = factory.createStructArray({1,1},{"seq","stamp","frame_id"});
    // _std_msgs_Header.seq
    _headeroutArray[0]["seq"] = factory.createScalar(val.seq);
    // _std_msgs_Header.stamp
    _headeroutArray[0]["stamp"] = get_arr_ros_Time(factory, val.stamp);
    // _std_msgs_Header.frame_id
    _headeroutArray[0]["frame_id"] = factory.createCharArray(val.frame_id);
    return std::move(_headeroutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_ros_Time(ros::Time& val, const matlab::data::StructArray& arr) {
    // _ros_Time.sec
    try {
        const matlab::data::TypedArray<uint32_t> _header_stampsec_arr = arr[0]["sec"];
        val.sec = _header_stampsec_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'sec' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'sec' is wrong type; expected a uint32.");
    }
    // _ros_Time.nsec
    try {
        const matlab::data::TypedArray<uint32_t> _header_stampnsec_arr = arr[0]["nsec"];
        val.nsec = _header_stampnsec_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'nsec' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'nsec' is wrong type; expected a uint32.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_ros_Time(MDFactory_T& factory, const std_msgs::Header::_stamp_type& val) {
    auto _header_stampoutArray = factory.createStructArray({1,1},{"sec","nsec"});
    // _ros_Time.sec
    _header_stampoutArray[0]["sec"] = factory.createScalar(val.sec);
    // _ros_Time.nsec
    _header_stampoutArray[0]["nsec"] = factory.createScalar(val.nsec);
    return std::move(_header_stampoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_autorally_msgs_neuralNetLayer_var_arr(autorally_msgs::neuralNetLayer& val, const matlab::data::Struct& arr) {
    // _autorally_msgs_neuralNetLayer_var_arr.name
    try {
        const matlab::data::CharArray _networkname_arr = arr["name"];
        val.name = _networkname_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'name' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'name' is wrong type; expected a string.");
    }
    // _autorally_msgs_neuralNetLayer_var_arr.weight
    try {
        const matlab::data::TypedArray<float> _networkweight_arr = arr["weight"];
        size_t nelem = _networkweight_arr.getNumberOfElements();
        	val.weight.resize(nelem);
        	std::copy(_networkweight_arr.begin(), _networkweight_arr.begin()+nelem, val.weight.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'weight' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'weight' is wrong type; expected a single.");
    }
    // _autorally_msgs_neuralNetLayer_var_arr.bias
    try {
        const matlab::data::TypedArray<float> _networkbias_arr = arr["bias"];
        size_t nelem = _networkbias_arr.getNumberOfElements();
        	val.bias.resize(nelem);
        	std::copy(_networkbias_arr.begin(), _networkbias_arr.begin()+nelem, val.bias.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'bias' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'bias' is wrong type; expected a single.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_autorally_msgs_neuralNetLayer_var_arr(MDFactory_T& factory, const autorally_msgs::neuralNetModel::_network_type& val) {
    auto _networkoutArray = factory.createStructArray({1,val.size()},{"name","weight","bias"});
    for (size_t idx = 0; idx < val.size(); ++idx){
    // _autorally_msgs_neuralNetLayer_var_arr.name
    	_networkoutArray[idx]["name"] = factory.createCharArray(val[idx].name);
    // _autorally_msgs_neuralNetLayer_var_arr.weight
    	_networkoutArray[idx]["weight"] = factory.createArray<autorally_msgs::neuralNetLayer::_weight_type::const_iterator, float>({1, val[idx].weight.size()}, val[idx].weight.begin(), val[idx].weight.end());
    // _autorally_msgs_neuralNetLayer_var_arr.bias
    	_networkoutArray[idx]["bias"] = factory.createArray<autorally_msgs::neuralNetLayer::_bias_type::const_iterator, float>({1, val[idx].bias.size()}, val[idx].bias.begin(), val[idx].bias.end());
    }
    return std::move(_networkoutArray);
  }
  //----------------------------------------------------------------------------
  AUTORALLY_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<autorally_msgs::neuralNetModel>& msg, const matlab::data::StructArray arr) {
    try {
        //header
        const matlab::data::StructArray header_arr = arr[0]["header"];
        copy_from_arr_std_msgs_Header(msg->header,header_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'header' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'header' is wrong type; expected a struct.");
    }
    try {
        //network
        const matlab::data::StructArray network_arr = arr[0]["network"];
        for (auto _networkarr : network_arr) {
        	autorally_msgs::neuralNetLayer _val;
        	copy_from_arr_autorally_msgs_neuralNetLayer_var_arr(_val,_networkarr);
        	msg->network.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'network' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'network' is wrong type; expected a struct.");
    }
    try {
        //numLayers
        const matlab::data::TypedArray<int32_t> numLayers_arr = arr[0]["numLayers"];
        msg->numLayers = numLayers_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'numLayers' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'numLayers' is wrong type; expected a int32.");
    }
    try {
        //structure
        const matlab::data::TypedArray<int32_t> structure_arr = arr[0]["structure"];
        size_t nelem = structure_arr.getNumberOfElements();
        	msg->structure.resize(nelem);
        	std::copy(structure_arr.begin(), structure_arr.begin()+nelem, msg->structure.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'structure' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'structure' is wrong type; expected a int32.");
    }
  }
  //----------------------------------------------------------------------------
  AUTORALLY_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const autorally_msgs::neuralNetModel>& msg) {
    auto outArray = factory.createStructArray({1,1},{"header","network","numLayers","structure"});
    // header
    outArray[0]["header"] = get_arr_std_msgs_Header(factory, msg->header);
    // network
    outArray[0]["network"] = get_arr_autorally_msgs_neuralNetLayer_var_arr(factory, msg->network);
    // numLayers
    outArray[0]["numLayers"] = factory.createScalar(msg->numLayers);
    // structure
    outArray[0]["structure"] = factory.createArray<autorally_msgs::neuralNetModel::_structure_type::const_iterator, int32_t>({1, msg->structure.size()}, msg->structure.begin(), msg->structure.end());
    return std::move(outArray);
  }
} //namespace neuralNetModel
} //namespace matlabhelper
} //namespace autorally_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1