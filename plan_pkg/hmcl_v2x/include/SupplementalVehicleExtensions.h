/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "../asn/J2735_201603DA_copyright_updated 12.2.ASN"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_SupplementalVehicleExtensions_H_
#define	_SupplementalVehicleExtensions_H_


#include <asn_application.h>

/* Including external dependencies */
#include "BasicVehicleClass.h"
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct VehicleClassification;
struct VehicleData;
struct WeatherReport;
struct WeatherProbe;
struct ObstacleDetection;
struct DisabledVehicle;
struct SpeedProfile;
struct RTCMPackage;
struct RegionalExtension;

/* SupplementalVehicleExtensions */
typedef struct SupplementalVehicleExtensions {
	BasicVehicleClass_t	*classification	/* OPTIONAL */;
	struct VehicleClassification	*classDetails	/* OPTIONAL */;
	struct VehicleData	*vehicleData	/* OPTIONAL */;
	struct WeatherReport	*weatherReport	/* OPTIONAL */;
	struct WeatherProbe	*weatherProbe	/* OPTIONAL */;
	struct ObstacleDetection	*obstacle	/* OPTIONAL */;
	struct DisabledVehicle	*status	/* OPTIONAL */;
	struct SpeedProfile	*speedProfile	/* OPTIONAL */;
	struct RTCMPackage	*theRTCM	/* OPTIONAL */;
	struct SupplementalVehicleExtensions__regional {
		A_SEQUENCE_OF(struct RegionalExtension) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *regional;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SupplementalVehicleExtensions_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SupplementalVehicleExtensions;
extern asn_SEQUENCE_specifics_t asn_SPC_SupplementalVehicleExtensions_specs_1;
extern asn_TYPE_member_t asn_MBR_SupplementalVehicleExtensions_1[10];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "VehicleClassification.h"
#include "VehicleData.h"
#include "WeatherReport.h"
#include "WeatherProbe.h"
#include "ObstacleDetection.h"
#include "DisabledVehicle.h"
#include "SpeedProfile.h"
#include "RTCMPackage.h"
#include "RegionalExtension.h"

#endif	/* _SupplementalVehicleExtensions_H_ */
#include <asn_internal.h>
