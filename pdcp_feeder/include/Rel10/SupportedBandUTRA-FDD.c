/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "fixed_grammar.asn"
 * 	`asn1c -gen-PER`
 */

#include "SupportedBandUTRA-FDD.h"

int
SupportedBandUTRA_FDD_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
SupportedBandUTRA_FDD_1_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
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

void
SupportedBandUTRA_FDD_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	SupportedBandUTRA_FDD_1_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

int
SupportedBandUTRA_FDD_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	SupportedBandUTRA_FDD_1_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

asn_dec_rval_t
SupportedBandUTRA_FDD_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	SupportedBandUTRA_FDD_1_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

asn_enc_rval_t
SupportedBandUTRA_FDD_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	SupportedBandUTRA_FDD_1_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

asn_dec_rval_t
SupportedBandUTRA_FDD_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	SupportedBandUTRA_FDD_1_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

asn_enc_rval_t
SupportedBandUTRA_FDD_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	SupportedBandUTRA_FDD_1_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

asn_dec_rval_t
SupportedBandUTRA_FDD_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	SupportedBandUTRA_FDD_1_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

asn_enc_rval_t
SupportedBandUTRA_FDD_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	SupportedBandUTRA_FDD_1_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

asn_enc_rval_t
SupportedBandUTRA_FDD_encode_aper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	SupportedBandUTRA_FDD_1_inherit_TYPE_descriptor(td);
	return td->aper_encoder(td, constraints, structure, per_out);
}

asn_dec_rval_t
SupportedBandUTRA_FDD_decode_aper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	SupportedBandUTRA_FDD_1_inherit_TYPE_descriptor(td);
	return td->aper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_per_constraints_t asn_PER_type_SupportedBandUTRA_FDD_constr_1 GCC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  4,  4,  0,  15 }	/* (0..15,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_INTEGER_enum_map_t asn_MAP_SupportedBandUTRA_FDD_value2enum_1[] = {
	{ 0,	5,	"bandI" },
	{ 1,	6,	"bandII" },
	{ 2,	7,	"bandIII" },
	{ 3,	6,	"bandIV" },
	{ 4,	5,	"bandV" },
	{ 5,	6,	"bandVI" },
	{ 6,	7,	"bandVII" },
	{ 7,	8,	"bandVIII" },
	{ 8,	6,	"bandIX" },
	{ 9,	5,	"bandX" },
	{ 10,	6,	"bandXI" },
	{ 11,	7,	"bandXII" },
	{ 12,	8,	"bandXIII" },
	{ 13,	7,	"bandXIV" },
	{ 14,	6,	"bandXV" },
	{ 15,	7,	"bandXVI" },
	{ 16,	12,	"bandXVII-8a0" },
	{ 17,	13,	"bandXVIII-8a0" },
	{ 18,	11,	"bandXIX-8a0" },
	{ 19,	10,	"bandXX-8a0" },
	{ 20,	11,	"bandXXI-8a0" },
	{ 21,	12,	"bandXXII-8a0" },
	{ 22,	13,	"bandXXIII-8a0" },
	{ 23,	12,	"bandXXIV-8a0" },
	{ 24,	11,	"bandXXV-8a0" },
	{ 25,	12,	"bandXXVI-8a0" },
	{ 26,	13,	"bandXXVII-8a0" },
	{ 27,	14,	"bandXXVIII-8a0" },
	{ 28,	12,	"bandXXIX-8a0" },
	{ 29,	11,	"bandXXX-8a0" },
	{ 30,	12,	"bandXXXI-8a0" },
	{ 31,	13,	"bandXXXII-8a0" }
	/* This list is extensible */
};
static unsigned int asn_MAP_SupportedBandUTRA_FDD_enum2value_1[] = {
	0,	/* bandI(0) */
	1,	/* bandII(1) */
	2,	/* bandIII(2) */
	3,	/* bandIV(3) */
	8,	/* bandIX(8) */
	4,	/* bandV(4) */
	5,	/* bandVI(5) */
	6,	/* bandVII(6) */
	7,	/* bandVIII(7) */
	9,	/* bandX(9) */
	10,	/* bandXI(10) */
	11,	/* bandXII(11) */
	12,	/* bandXIII(12) */
	13,	/* bandXIV(13) */
	18,	/* bandXIX-8a0(18) */
	14,	/* bandXV(14) */
	15,	/* bandXVI(15) */
	16,	/* bandXVII-8a0(16) */
	17,	/* bandXVIII-8a0(17) */
	19,	/* bandXX-8a0(19) */
	20,	/* bandXXI-8a0(20) */
	21,	/* bandXXII-8a0(21) */
	22,	/* bandXXIII-8a0(22) */
	23,	/* bandXXIV-8a0(23) */
	28,	/* bandXXIX-8a0(28) */
	24,	/* bandXXV-8a0(24) */
	25,	/* bandXXVI-8a0(25) */
	26,	/* bandXXVII-8a0(26) */
	27,	/* bandXXVIII-8a0(27) */
	29,	/* bandXXX-8a0(29) */
	30,	/* bandXXXI-8a0(30) */
	31	/* bandXXXII-8a0(31) */
	/* This list is extensible */
};
static asn_INTEGER_specifics_t asn_SPC_SupportedBandUTRA_FDD_specs_1 = {
	asn_MAP_SupportedBandUTRA_FDD_value2enum_1,	/* "tag" => N; sorted by tag */
	asn_MAP_SupportedBandUTRA_FDD_enum2value_1,	/* N => "tag"; sorted by N */
	32,	/* Number of elements in the maps */
	17,	/* Extensions before this member */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static ber_tlv_tag_t asn_DEF_SupportedBandUTRA_FDD_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
asn_TYPE_descriptor_t asn_DEF_SupportedBandUTRA_FDD = {
	"SupportedBandUTRA-FDD",
	"SupportedBandUTRA-FDD",
	SupportedBandUTRA_FDD_free,
	SupportedBandUTRA_FDD_print,
	SupportedBandUTRA_FDD_constraint,
	SupportedBandUTRA_FDD_decode_ber,
	SupportedBandUTRA_FDD_encode_der,
	SupportedBandUTRA_FDD_decode_xer,
	SupportedBandUTRA_FDD_encode_xer,
	SupportedBandUTRA_FDD_decode_uper,
	SupportedBandUTRA_FDD_encode_uper,
	SupportedBandUTRA_FDD_decode_aper,
	SupportedBandUTRA_FDD_encode_aper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_SupportedBandUTRA_FDD_tags_1,
	sizeof(asn_DEF_SupportedBandUTRA_FDD_tags_1)
		/sizeof(asn_DEF_SupportedBandUTRA_FDD_tags_1[0]), /* 1 */
	asn_DEF_SupportedBandUTRA_FDD_tags_1,	/* Same as above */
	sizeof(asn_DEF_SupportedBandUTRA_FDD_tags_1)
		/sizeof(asn_DEF_SupportedBandUTRA_FDD_tags_1[0]), /* 1 */
	&asn_PER_type_SupportedBandUTRA_FDD_constr_1,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_SupportedBandUTRA_FDD_specs_1	/* Additional specs */
};

