/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "fixed_grammar.asn"
 * 	`asn1c -gen-PER`
 */

#include "RRCConnectionSetupComplete-r8-IEs.h"

static int
memb_selectedPLMN_Identity_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 1 && value <= 6)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_memb_selectedPLMN_Identity_constr_2 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 3,  3,  1,  6 }	/* (1..6) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_RRCConnectionSetupComplete_r8_IEs_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct RRCConnectionSetupComplete_r8_IEs, selectedPLMN_Identity),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_selectedPLMN_Identity_constraint_1,
		&asn_PER_memb_selectedPLMN_Identity_constr_2,
		0,
		"selectedPLMN-Identity"
		},
	{ ATF_POINTER, 1, offsetof(struct RRCConnectionSetupComplete_r8_IEs, registeredMME),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RegisteredMME,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"registeredMME"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RRCConnectionSetupComplete_r8_IEs, dedicatedInfoNAS),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DedicatedInfoNAS,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dedicatedInfoNAS"
		},
	{ ATF_POINTER, 1, offsetof(struct RRCConnectionSetupComplete_r8_IEs, nonCriticalExtension),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RRCConnectionSetupComplete_v8a0_IEs,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"nonCriticalExtension"
		},
};
static int asn_MAP_RRCConnectionSetupComplete_r8_IEs_oms_1[] = { 1, 3 };
static ber_tlv_tag_t asn_DEF_RRCConnectionSetupComplete_r8_IEs_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_RRCConnectionSetupComplete_r8_IEs_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* selectedPLMN-Identity at 1048 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* registeredMME at 1049 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* dedicatedInfoNAS at 1050 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* nonCriticalExtension at 1051 */
};
static asn_SEQUENCE_specifics_t asn_SPC_RRCConnectionSetupComplete_r8_IEs_specs_1 = {
	sizeof(struct RRCConnectionSetupComplete_r8_IEs),
	offsetof(struct RRCConnectionSetupComplete_r8_IEs, _asn_ctx),
	asn_MAP_RRCConnectionSetupComplete_r8_IEs_tag2el_1,
	4,	/* Count of tags in the map */
	asn_MAP_RRCConnectionSetupComplete_r8_IEs_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_RRCConnectionSetupComplete_r8_IEs = {
	"RRCConnectionSetupComplete-r8-IEs",
	"RRCConnectionSetupComplete-r8-IEs",
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
	asn_DEF_RRCConnectionSetupComplete_r8_IEs_tags_1,
	sizeof(asn_DEF_RRCConnectionSetupComplete_r8_IEs_tags_1)
		/sizeof(asn_DEF_RRCConnectionSetupComplete_r8_IEs_tags_1[0]), /* 1 */
	asn_DEF_RRCConnectionSetupComplete_r8_IEs_tags_1,	/* Same as above */
	sizeof(asn_DEF_RRCConnectionSetupComplete_r8_IEs_tags_1)
		/sizeof(asn_DEF_RRCConnectionSetupComplete_r8_IEs_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_RRCConnectionSetupComplete_r8_IEs_1,
	4,	/* Elements count */
	&asn_SPC_RRCConnectionSetupComplete_r8_IEs_specs_1	/* Additional specs */
};

