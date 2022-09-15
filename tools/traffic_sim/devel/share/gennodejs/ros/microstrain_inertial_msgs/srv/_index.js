
"use strict";

let SetMagAdaptiveVals = require('./SetMagAdaptiveVals.js')
let SetDynamicsMode = require('./SetDynamicsMode.js')
let GetMagDipAdaptiveVals = require('./GetMagDipAdaptiveVals.js')
let GetAccelBiasModel = require('./GetAccelBiasModel.js')
let GetAccelAdaptiveVals = require('./GetAccelAdaptiveVals.js')
let SetSensor2VehicleOffset = require('./SetSensor2VehicleOffset.js')
let SetHeadingSource = require('./SetHeadingSource.js')
let SetEstimationControlFlags = require('./SetEstimationControlFlags.js')
let GetHeadingSource = require('./GetHeadingSource.js')
let GetEstimationControlFlags = require('./GetEstimationControlFlags.js')
let GetGyroBiasModel = require('./GetGyroBiasModel.js')
let GetTareOrientation = require('./GetTareOrientation.js')
let SetAccelBias = require('./SetAccelBias.js')
let SetMagDipAdaptiveVals = require('./SetMagDipAdaptiveVals.js')
let GetGyroBias = require('./GetGyroBias.js')
let GetConingScullingComp = require('./GetConingScullingComp.js')
let GetSensor2VehicleOffset = require('./GetSensor2VehicleOffset.js')
let SetConingScullingComp = require('./SetConingScullingComp.js')
let GetComplementaryFilter = require('./GetComplementaryFilter.js')
let GetGravityAdaptiveVals = require('./GetGravityAdaptiveVals.js')
let GetRelativePositionReference = require('./GetRelativePositionReference.js')
let GetZeroAngleUpdateThreshold = require('./GetZeroAngleUpdateThreshold.js')
let GetZeroVelocityUpdateThreshold = require('./GetZeroVelocityUpdateThreshold.js')
let SetAccelBiasModel = require('./SetAccelBiasModel.js')
let GetMagAdaptiveVals = require('./GetMagAdaptiveVals.js')
let GetGyroNoise = require('./GetGyroNoise.js')
let SetAccelNoise = require('./SetAccelNoise.js')
let SetMagNoise = require('./SetMagNoise.js')
let SetComplementaryFilter = require('./SetComplementaryFilter.js')
let InitFilterEuler = require('./InitFilterEuler.js')
let SetReferencePosition = require('./SetReferencePosition.js')
let GetAccelNoise = require('./GetAccelNoise.js')
let GetSensor2VehicleRotation = require('./GetSensor2VehicleRotation.js')
let GetSensor2VehicleTransformation = require('./GetSensor2VehicleTransformation.js')
let InitFilterHeading = require('./InitFilterHeading.js')
let SetGyroNoise = require('./SetGyroNoise.js')
let GetReferencePosition = require('./GetReferencePosition.js')
let DeviceSettings = require('./DeviceSettings.js')
let SetGyroBiasModel = require('./SetGyroBiasModel.js')
let SetAccelAdaptiveVals = require('./SetAccelAdaptiveVals.js')
let SetZeroVelocityUpdateThreshold = require('./SetZeroVelocityUpdateThreshold.js')
let SetHardIronValues = require('./SetHardIronValues.js')
let GetDynamicsMode = require('./GetDynamicsMode.js')
let GetSoftIronMatrix = require('./GetSoftIronMatrix.js')
let GetMagNoise = require('./GetMagNoise.js')
let DeviceReport = require('./DeviceReport.js')
let SetGravityAdaptiveVals = require('./SetGravityAdaptiveVals.js')
let SetSensor2VehicleRotation = require('./SetSensor2VehicleRotation.js')
let SetTareOrientation = require('./SetTareOrientation.js')
let SetSoftIronMatrix = require('./SetSoftIronMatrix.js')
let ExternalHeadingUpdate = require('./ExternalHeadingUpdate.js')
let GetAccelBias = require('./GetAccelBias.js')
let SetZeroAngleUpdateThreshold = require('./SetZeroAngleUpdateThreshold.js')
let SetFilterSpeedLeverArm = require('./SetFilterSpeedLeverArm.js')
let GetHardIronValues = require('./GetHardIronValues.js')
let SetRelativePositionReference = require('./SetRelativePositionReference.js')
let SetGyroBias = require('./SetGyroBias.js')

module.exports = {
  SetMagAdaptiveVals: SetMagAdaptiveVals,
  SetDynamicsMode: SetDynamicsMode,
  GetMagDipAdaptiveVals: GetMagDipAdaptiveVals,
  GetAccelBiasModel: GetAccelBiasModel,
  GetAccelAdaptiveVals: GetAccelAdaptiveVals,
  SetSensor2VehicleOffset: SetSensor2VehicleOffset,
  SetHeadingSource: SetHeadingSource,
  SetEstimationControlFlags: SetEstimationControlFlags,
  GetHeadingSource: GetHeadingSource,
  GetEstimationControlFlags: GetEstimationControlFlags,
  GetGyroBiasModel: GetGyroBiasModel,
  GetTareOrientation: GetTareOrientation,
  SetAccelBias: SetAccelBias,
  SetMagDipAdaptiveVals: SetMagDipAdaptiveVals,
  GetGyroBias: GetGyroBias,
  GetConingScullingComp: GetConingScullingComp,
  GetSensor2VehicleOffset: GetSensor2VehicleOffset,
  SetConingScullingComp: SetConingScullingComp,
  GetComplementaryFilter: GetComplementaryFilter,
  GetGravityAdaptiveVals: GetGravityAdaptiveVals,
  GetRelativePositionReference: GetRelativePositionReference,
  GetZeroAngleUpdateThreshold: GetZeroAngleUpdateThreshold,
  GetZeroVelocityUpdateThreshold: GetZeroVelocityUpdateThreshold,
  SetAccelBiasModel: SetAccelBiasModel,
  GetMagAdaptiveVals: GetMagAdaptiveVals,
  GetGyroNoise: GetGyroNoise,
  SetAccelNoise: SetAccelNoise,
  SetMagNoise: SetMagNoise,
  SetComplementaryFilter: SetComplementaryFilter,
  InitFilterEuler: InitFilterEuler,
  SetReferencePosition: SetReferencePosition,
  GetAccelNoise: GetAccelNoise,
  GetSensor2VehicleRotation: GetSensor2VehicleRotation,
  GetSensor2VehicleTransformation: GetSensor2VehicleTransformation,
  InitFilterHeading: InitFilterHeading,
  SetGyroNoise: SetGyroNoise,
  GetReferencePosition: GetReferencePosition,
  DeviceSettings: DeviceSettings,
  SetGyroBiasModel: SetGyroBiasModel,
  SetAccelAdaptiveVals: SetAccelAdaptiveVals,
  SetZeroVelocityUpdateThreshold: SetZeroVelocityUpdateThreshold,
  SetHardIronValues: SetHardIronValues,
  GetDynamicsMode: GetDynamicsMode,
  GetSoftIronMatrix: GetSoftIronMatrix,
  GetMagNoise: GetMagNoise,
  DeviceReport: DeviceReport,
  SetGravityAdaptiveVals: SetGravityAdaptiveVals,
  SetSensor2VehicleRotation: SetSensor2VehicleRotation,
  SetTareOrientation: SetTareOrientation,
  SetSoftIronMatrix: SetSoftIronMatrix,
  ExternalHeadingUpdate: ExternalHeadingUpdate,
  GetAccelBias: GetAccelBias,
  SetZeroAngleUpdateThreshold: SetZeroAngleUpdateThreshold,
  SetFilterSpeedLeverArm: SetFilterSpeedLeverArm,
  GetHardIronValues: GetHardIronValues,
  SetRelativePositionReference: SetRelativePositionReference,
  SetGyroBias: SetGyroBias,
};
