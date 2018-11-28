/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "fixed_grammar.asn"
 * 	`asn1c -gen-PER`
 */

#include "UplinkPowerControlDedicatedSCell-r10.h"

static int
deltaMCS_Enabled_r10_3_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	/* Replace with underlying type checker */
	td->check_constraints = asn_DEF_NativeEnumerated.check_constraints;
	return td->check_constraints(td, sptr, ctfailcb, app_key);
}

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static void
deltaMCS_Enabled_r10_3_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
	td->free_struct    = asn_DEF_NativeEnumerated.free_struct;
	td->print_struct   = asn_DEF_NativeEnumerated.print_struct;
	td->check_constraints = asn_DEF_NativeEnumerated.check_constraints;
	td->ber_decoder    = asn_DEF_NativeEnumerated.ber_decoder;
	td->der_encoder    = asn_DEF_NativeEnumerated.der_encoder;
	td->xer_decoder    = asn_DEF_NativeEnumerated.xer_decoder;
	td->xer_encoder    = asn_DEF_NativeEnumerated.xer_encoder;
	td->uper_decoder   = asn_DEF_NativeEnumerated.uper_decoder;
	td->uper_encoder   = asn_DEF_NativeEnumerated.uper_encoder;
	td->aper_decoder   = asn_DEF_NativeEnumerated.aper_decoder;
	td->aper_encoder   = asn_DEF_NativeEnumerated.aper_encoder;
	if(!td->per_constraints)
		td->per_constraints = asn_DEF_NativeEnumerated.per_constraints;
	td->elements       = asn_DEF_NativeEnumerated.elements;
	td->elements_count = asn_DEF_NativeEnumerated.elements_count;
     /* td->specifics      = asn_DEF_NativeEnumerated.specifics;	// Defined explicitly */
}

static void
deltaMCS_Enabled_r10_3_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	deltaMCS_Enabled_r10_3_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
deltaMCS_Enabled_r10_3_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	deltaMCS_Enabled_r10_3_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
deltaMCS_Enabled_r10_3_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	deltaMCS_Enabled_r10_3_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
deltaMCS_Enabled_r10_3_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	deltaMCS_Enabled_r10_3_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
deltaMCS_Enabled_r10_3_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	deltaMCS_Enabled_r10_3_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
deltaMCS_Enabled_r10_3_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	deltaMCS_Enabled_r10_3_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
deltaMCS_Enabled_r10_3_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	deltaMCS_Enabled_r10_3_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
deltaMCS_Enabled_r10_3_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	deltaMCS_Enabled_r10_3_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static asn_enc_rval_t
deltaMCS_Enabled_r10_3_encode_aper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	deltaMCS_Enabled_r10_3_inherit_TYPE_descriptor(td);
	return td->aper_encoder(td, constraints, structure, per_out);
}

static asn_dec_rval_t
deltaMCS_Enabled_r10_3_decode_aper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	deltaMCS_Enabled_r10_3_inherit_TYPE_descriptor(td);
	return td->aper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static int
pathlossReferenceLinking_r10_10_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	/* Replace with underlying type checker */
	td->check_constraints = asn_DEF_NativeEnumerated.check_constraints;
	return td->check_constraints(td, sptr, ctfailcb, app_key);
}

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static void
pathlossReferenceLinking_r10_10_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
	td->free_struct    = asn_DEF_NativeEnumerated.free_struct;
	td->print_struct   = asn_DEF_NativeEnumerated.print_struct;
	td->check_constraints = asn_DEF_NativeEnumerated.check_constraints;
	td->ber_decoder    = asn_DEF_NativeEnumerated.ber_decoder;
	td->der_encoder    = asn_DEF_NativeEnumerated.der_encoder;
	td->xer_decoder    = asn_DEF_NativeEnumerated.xer_decoder;
	td->xer_encoder    = asn_DEF_NativeEnumerated.xer_encoder;
	td->uper_decoder   = asn_DEF_NativeEnumerated.uper_decoder;
	td->uper_encoder   = asn_DEF_NativeEnumerated.uper_encoder;
	td->aper_decoder   = asn_DEF_NativeEnumerated.aper_decoder;
	td->aper_encoder   = asn_DEF_NativeEnumerated.aper_encoder;
	if(!td->per_constraints)
		td->per_constraints = asn_DEF_NativeEnumerated.per_constraints;
	td->elements       = asn_DEF_NativeEnumerated.elements;
	td->elements_count = asn_DEF_NativeEnumerated.elements_count;
     /* td->specifics      = asn_DEF_NativeEnumerated.specifics;	// Defined explicitly */
}

static void
pathlossReferenceLinking_r10_10_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	pathlossReferenceLinking_r10_10_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
pathlossReferenceLinking_r10_10_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	pathlossReferenceLinking_r10_10_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
pathlossReferenceLinking_r10_10_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	pathlossReferenceLinking_r10_10_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
pathlossReferenceLinking_r10_10_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	pathlossReferenceLinking_r10_10_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
pathlossReferenceLinking_r10_10_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	pathlossReferenceLinking_r10_10_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
pathlossReferenceLinking_r10_10_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	pathlossReferenceLinking_r10_10_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
pathlossReferenceLinking_r10_10_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	pathlossReferenceLinking_r10_10_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
pathlossReferenceLinking_r10_10_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	pathlossReferenceLinking_r10_10_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static asn_enc_rval_t
pathlossReferenceLinking_r10_10_encode_aper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	pathlossReferenceLinking_r10_10_inherit_TYPE_descriptor(td);
	return td->aper_encoder(td, constraints, structure, per_out);
}

static asn_dec_rval_t
pathlossReferenceLinking_r10_10_decode_aper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	pathlossReferenceLinking_r10_10_inherit_TYPE_descriptor(td);
	return td->aper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static int
memb_p0_UE_PUSCH_r10_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= -8 && value <= 7)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_pSRS_Offset_r10_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 15)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_pSRS_OffsetAp_r10_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 15)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_type_deltaMCS_Enabled_r10_constr_3 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_pathlossReferenceLinking_r10_constr_10 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_p0_UE_PUSCH_r10_constr_2 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 4,  4, -8,  7 }	/* (-8..7) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_pSRS_Offset_r10_constr_7 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 4,  4,  0,  15 }	/* (0..15) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_pSRS_OffsetAp_r10_constr_8 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 4,  4,  0,  15 }	/* (0..15) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_INTEGER_enum_map_t asn_MAP_deltaMCS_Enabled_r10_value2enum_3[] = {
	{ 0,	3,	"en0" },
	{ 1,	3,	"en1" }
};
static unsigned int asn_MAP_deltaMCS_Enabled_r10_enum2value_3[] = {
	0,	/* en0(0) */
	1	/* en1(1) */
};
static asn_INTEGER_specifics_t asn_SPC_deltaMCS_Enabled_r10_specs_3 = {
	asn_MAP_deltaMCS_Enabled_r10_value2enum_3,	/* "tag" => N; sorted by tag */
	asn_MAP_deltaMCS_Enabled_r10_enum2value_3,	/* N => "tag"; sorted by N */
	2,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static ber_tlv_tag_t asn_DEF_deltaMCS_Enabled_r10_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_deltaMCS_Enabled_r10_3 = {
	"deltaMCS-Enabled-r10",
	"deltaMCS-Enabled-r10",
	deltaMCS_Enabled_r10_3_free,
	deltaMCS_Enabled_r10_3_print,
	deltaMCS_Enabled_r10_3_constraint,
	deltaMCS_Enabled_r10_3_decode_ber,
	deltaMCS_Enabled_r10_3_encode_der,
	deltaMCS_Enabled_r10_3_decode_xer,
	deltaMCS_Enabled_r10_3_encode_xer,
	deltaMCS_Enabled_r10_3_decode_uper,
	deltaMCS_Enabled_r10_3_encode_uper,
	deltaMCS_Enabled_r10_3_decode_aper,
	deltaMCS_Enabled_r10_3_encode_aper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_deltaMCS_Enabled_r10_tags_3,
	sizeof(asn_DEF_deltaMCS_Enabled_r10_tags_3)
		/sizeof(asn_DEF_deltaMCS_Enabled_r10_tags_3[0]) - 1, /* 1 */
	asn_DEF_deltaMCS_Enabled_r10_tags_3,	/* Same as above */
	sizeof(asn_DEF_deltaMCS_Enabled_r10_tags_3)
		/sizeof(asn_DEF_deltaMCS_Enabled_r10_tags_3[0]), /* 2 */
	&asn_PER_type_deltaMCS_Enabled_r10_constr_3,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_deltaMCS_Enabled_r10_specs_3	/* Additional specs */
};

static int asn_DFL_9_set_4(int set_value, void **sptr) {
	FilterCoefficient_t *st = *sptr;
	
	if(!st) {
		if(!set_value) return -1;	/* Not a default value */
		st = (*sptr = CALLOC(1, sizeof(*st)));
		if(!st) return -1;
	}
	
	if(set_value) {
		/* Install default value 4 */
		*st = 4;
		return 0;
	} else {
		/* Test default value 4 */
		return (*st == 4);
	}
}
static asn_INTEGER_enum_map_t asn_MAP_pathlossReferenceLinking_r10_value2enum_10[] = {
	{ 0,	5,	"pCell" },
	{ 1,	5,	"sCell" }
};
static unsigned int asn_MAP_pathlossReferenceLinking_r10_enum2value_10[] = {
	0,	/* pCell(0) */
	1	/* sCell(1) */
};
static asn_INTEGER_specifics_t asn_SPC_pathlossReferenceLinking_r10_specs_10 = {
	asn_MAP_pathlossReferenceLinking_r10_value2enum_10,	/* "tag" => N; sorted by tag */
	asn_MAP_pathlossReferenceLinking_r10_enum2value_10,	/* N => "tag"; sorted by N */
	2,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static ber_tlv_tag_t asn_DEF_pathlossReferenceLinking_r10_tags_10[] = {
	(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_pathlossReferenceLinking_r10_10 = {
	"pathlossReferenceLinking-r10",
	"pathlossReferenceLinking-r10",
	pathlossReferenceLinking_r10_10_free,
	pathlossReferenceLinking_r10_10_print,
	pathlossReferenceLinking_r10_10_constraint,
	pathlossReferenceLinking_r10_10_decode_ber,
	pathlossReferenceLinking_r10_10_encode_der,
	pathlossReferenceLinking_r10_10_decode_xer,
	pathlossReferenceLinking_r10_10_encode_xer,
	pathlossReferenceLinking_r10_10_decode_uper,
	pathlossReferenceLinking_r10_10_encode_uper,
	pathlossReferenceLinking_r10_10_decode_aper,
	pathlossReferenceLinking_r10_10_encode_aper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_pathlossReferenceLinking_r10_tags_10,
	sizeof(asn_DEF_pathlossReferenceLinking_r10_tags_10)
		/sizeof(asn_DEF_pathlossReferenceLinking_r10_tags_10[0]) - 1, /* 1 */
	asn_DEF_pathlossReferenceLinking_r10_tags_10,	/* Same as above */
	sizeof(asn_DEF_pathlossReferenceLinking_r10_tags_10)
		/sizeof(asn_DEF_pathlossReferenceLinking_r10_tags_10[0]), /* 2 */
	&asn_PER_type_pathlossReferenceLinking_r10_constr_10,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_pathlossReferenceLinking_r10_specs_10	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_UplinkPowerControlDedicatedSCell_r10_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UplinkPowerControlDedicatedSCell_r10, p0_UE_PUSCH_r10),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_p0_UE_PUSCH_r10_constraint_1,
		&asn_PER_memb_p0_UE_PUSCH_r10_constr_2,
		0,
		"p0-UE-PUSCH-r10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UplinkPowerControlDedicatedSCell_r10, deltaMCS_Enabled_r10),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_deltaMCS_Enabled_r10_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"deltaMCS-Enabled-r10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UplinkPowerControlDedicatedSCell_r10, accumulationEnabled_r10),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"accumulationEnabled-r10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UplinkPowerControlDedicatedSCell_r10, pSRS_Offset_r10),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_pSRS_Offset_r10_constraint_1,
		&asn_PER_memb_pSRS_Offset_r10_constr_7,
		0,
		"pSRS-Offset-r10"
		},
	{ ATF_POINTER, 2, offsetof(struct UplinkPowerControlDedicatedSCell_r10, pSRS_OffsetAp_r10),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_pSRS_OffsetAp_r10_constraint_1,
		&asn_PER_memb_pSRS_OffsetAp_r10_constr_8,
		0,
		"pSRS-OffsetAp-r10"
		},
	{ ATF_POINTER, 1, offsetof(struct UplinkPowerControlDedicatedSCell_r10, filterCoefficient_r10),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_FilterCoefficient,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		asn_DFL_9_set_4,	/* DEFAULT 4 */
		"filterCoefficient-r10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UplinkPowerControlDedicatedSCell_r10, pathlossReferenceLinking_r10),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_pathlossReferenceLinking_r10_10,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"pathlossReferenceLinking-r10"
		},
};
static int asn_MAP_UplinkPowerControlDedicatedSCell_r10_oms_1[] = { 4, 5 };
static ber_tlv_tag_t asn_DEF_UplinkPowerControlDedicatedSCell_r10_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_UplinkPowerControlDedicatedSCell_r10_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* p0-UE-PUSCH-r10 at 2844 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* deltaMCS-Enabled-r10 at 2845 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* accumulationEnabled-r10 at 2846 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* pSRS-Offset-r10 at 2847 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* pSRS-OffsetAp-r10 at 2848 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* filterCoefficient-r10 at 2849 */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 } /* pathlossReferenceLinking-r10 at 2850 */
};
static asn_SEQUENCE_specifics_t asn_SPC_UplinkPowerControlDedicatedSCell_r10_specs_1 = {
	sizeof(struct UplinkPowerControlDedicatedSCell_r10),
	offsetof(struct UplinkPowerControlDedicatedSCell_r10, _asn_ctx),
	asn_MAP_UplinkPowerControlDedicatedSCell_r10_tag2el_1,
	7,	/* Count of tags in the map */
	asn_MAP_UplinkPowerControlDedicatedSCell_r10_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_UplinkPowerControlDedicatedSCell_r10 = {
	"UplinkPowerControlDedicatedSCell-r10",
	"UplinkPowerControlDedicatedSCell-r10",
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
	asn_DEF_UplinkPowerControlDedicatedSCell_r10_tags_1,
	sizeof(asn_DEF_UplinkPowerControlDedicatedSCell_r10_tags_1)
		/sizeof(asn_DEF_UplinkPowerControlDedicatedSCell_r10_tags_1[0]), /* 1 */
	asn_DEF_UplinkPowerControlDedicatedSCell_r10_tags_1,	/* Same as above */
	sizeof(asn_DEF_UplinkPowerControlDedicatedSCell_r10_tags_1)
		/sizeof(asn_DEF_UplinkPowerControlDedicatedSCell_r10_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_UplinkPowerControlDedicatedSCell_r10_1,
	7,	/* Elements count */
	&asn_SPC_UplinkPowerControlDedicatedSCell_r10_specs_1	/* Additional specs */
};

