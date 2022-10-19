/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "../asn/J2735_201603DA_copyright_updated 12.2.ASN"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_TrailerHistoryPointList_H_
#define	_TrailerHistoryPointList_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct TrailerHistoryPoint;

/* TrailerHistoryPointList */
typedef struct TrailerHistoryPointList {
	A_SEQUENCE_OF(struct TrailerHistoryPoint) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TrailerHistoryPointList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TrailerHistoryPointList;
extern asn_SET_OF_specifics_t asn_SPC_TrailerHistoryPointList_specs_1;
extern asn_TYPE_member_t asn_MBR_TrailerHistoryPointList_1[1];
extern asn_per_constraints_t asn_PER_type_TrailerHistoryPointList_constr_1;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "TrailerHistoryPoint.h"

#endif	/* _TrailerHistoryPointList_H_ */
#include <asn_internal.h>
