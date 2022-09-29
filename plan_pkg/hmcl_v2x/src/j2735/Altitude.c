/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "AddGrpC"
 * 	found in "../asn/J2735_201603DA_copyright_updated 12.2.ASN"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#include "Altitude.h"

asn_TYPE_member_t asn_MBR_Altitude_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct Altitude, value),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AltitudeValue,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"value"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct Altitude, confidence),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AltitudeConfidence,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"confidence"
		},
};
static const ber_tlv_tag_t asn_DEF_Altitude_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_Altitude_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* value */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* confidence */
};
asn_SEQUENCE_specifics_t asn_SPC_Altitude_specs_1 = {
	sizeof(struct Altitude),
	offsetof(struct Altitude, _asn_ctx),
	asn_MAP_Altitude_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_Altitude = {
	"Altitude",
	"Altitude",
	&asn_OP_SEQUENCE,
	asn_DEF_Altitude_tags_1,
	sizeof(asn_DEF_Altitude_tags_1)
		/sizeof(asn_DEF_Altitude_tags_1[0]), /* 1 */
	asn_DEF_Altitude_tags_1,	/* Same as above */
	sizeof(asn_DEF_Altitude_tags_1)
		/sizeof(asn_DEF_Altitude_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_Altitude_1,
	2,	/* Elements count */
	&asn_SPC_Altitude_specs_1	/* Additional specs */
};

