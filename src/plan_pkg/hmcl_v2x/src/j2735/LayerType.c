/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "../asn/J2735_201603DA_copyright_updated 12.2.ASN"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#include "LayerType.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static asn_oer_constraints_t asn_OER_type_LayerType_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
asn_per_constraints_t asn_PER_type_LayerType_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  3,  3,  0,  7 }	/* (0..7,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_LayerType_value2enum_1[] = {
	{ 0,	4,	"none" },
	{ 1,	12,	"mixedContent" },
	{ 2,	14,	"generalMapData" },
	{ 3,	16,	"intersectionData" },
	{ 4,	9,	"curveData" },
	{ 5,	18,	"roadwaySectionData" },
	{ 6,	15,	"parkingAreaData" },
	{ 7,	14,	"sharedLaneData" }
	/* This list is extensible */
};
static const unsigned int asn_MAP_LayerType_enum2value_1[] = {
	4,	/* curveData(4) */
	2,	/* generalMapData(2) */
	3,	/* intersectionData(3) */
	1,	/* mixedContent(1) */
	0,	/* none(0) */
	6,	/* parkingAreaData(6) */
	5,	/* roadwaySectionData(5) */
	7	/* sharedLaneData(7) */
	/* This list is extensible */
};
const asn_INTEGER_specifics_t asn_SPC_LayerType_specs_1 = {
	asn_MAP_LayerType_value2enum_1,	/* "tag" => N; sorted by tag */
	asn_MAP_LayerType_enum2value_1,	/* N => "tag"; sorted by N */
	8,	/* Number of elements in the maps */
	9,	/* Extensions before this member */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_LayerType_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
asn_TYPE_descriptor_t asn_DEF_LayerType = {
	"LayerType",
	"LayerType",
	&asn_OP_NativeEnumerated,
	asn_DEF_LayerType_tags_1,
	sizeof(asn_DEF_LayerType_tags_1)
		/sizeof(asn_DEF_LayerType_tags_1[0]), /* 1 */
	asn_DEF_LayerType_tags_1,	/* Same as above */
	sizeof(asn_DEF_LayerType_tags_1)
		/sizeof(asn_DEF_LayerType_tags_1[0]), /* 1 */
	{ &asn_OER_type_LayerType_constr_1, &asn_PER_type_LayerType_constr_1, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_LayerType_specs_1	/* Additional specs */
};

