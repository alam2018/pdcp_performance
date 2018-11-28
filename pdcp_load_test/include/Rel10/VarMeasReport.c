/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "fixed_grammar.asn"
 * 	`asn1c -gen-PER`
 */

#include "VarMeasReport.h"

static asn_TYPE_member_t asn_MBR_VarMeasReport_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct VarMeasReport, measId),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasId,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"measId"
		},
	{ ATF_POINTER, 1, offsetof(struct VarMeasReport, cellsTriggeredList),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CellsTriggeredList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cellsTriggeredList"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct VarMeasReport, numberOfReportsSent),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"numberOfReportsSent"
		},
};
static int asn_MAP_VarMeasReport_oms_1[] = { 1 };
static ber_tlv_tag_t asn_DEF_VarMeasReport_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_VarMeasReport_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* measId at 4378 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* cellsTriggeredList at 4379 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* numberOfReportsSent at 4381 */
};
static asn_SEQUENCE_specifics_t asn_SPC_VarMeasReport_specs_1 = {
	sizeof(struct VarMeasReport),
	offsetof(struct VarMeasReport, _asn_ctx),
	asn_MAP_VarMeasReport_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_VarMeasReport_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_VarMeasReport = {
	"VarMeasReport",
	"VarMeasReport",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	SEQUENCE_decode_uper,
	SEQUENCE_encode_uper,
	SEQUENCE_decode_aper,
	SEQUENCE_encode_aper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_VarMeasReport_tags_1,
	sizeof(asn_DEF_VarMeasReport_tags_1)
		/sizeof(asn_DEF_VarMeasReport_tags_1[0]), /* 1 */
	asn_DEF_VarMeasReport_tags_1,	/* Same as above */
	sizeof(asn_DEF_VarMeasReport_tags_1)
		/sizeof(asn_DEF_VarMeasReport_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_VarMeasReport_1,
	3,	/* Elements count */
	&asn_SPC_VarMeasReport_specs_1	/* Additional specs */
};

