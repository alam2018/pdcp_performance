/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "fixed_grammar.asn"
 * 	`asn1c -gen-PER`
 */

#include "BandclassCDMA2000.h"

int
BandclassCDMA2000_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
BandclassCDMA2000_1_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
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
BandclassCDMA2000_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	BandclassCDMA2000_1_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

int
BandclassCDMA2000_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	BandclassCDMA2000_1_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

asn_dec_rval_t
BandclassCDMA2000_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	BandclassCDMA2000_1_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

asn_enc_rval_t
BandclassCDMA2000_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	BandclassCDMA2000_1_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

asn_dec_rval_t
BandclassCDMA2000_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	BandclassCDMA2000_1_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

asn_enc_rval_t
BandclassCDMA2000_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	BandclassCDMA2000_1_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

asn_dec_rval_t
BandclassCDMA2000_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	BandclassCDMA2000_1_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

asn_enc_rval_t
BandclassCDMA2000_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	BandclassCDMA2000_1_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

asn_enc_rval_t
BandclassCDMA2000_encode_aper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	BandclassCDMA2000_1_inherit_TYPE_descriptor(td);
	return td->aper_encoder(td, constraints, structure, per_out);
}

asn_dec_rval_t
BandclassCDMA2000_decode_aper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	BandclassCDMA2000_1_inherit_TYPE_descriptor(td);
	return td->aper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_per_constraints_t asn_PER_type_BandclassCDMA2000_constr_1 GCC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  5,  5,  0,  31 }	/* (0..31,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_INTEGER_enum_map_t asn_MAP_BandclassCDMA2000_value2enum_1[] = {
	{ 0,	3,	"bc0" },
	{ 1,	3,	"bc1" },
	{ 2,	3,	"bc2" },
	{ 3,	3,	"bc3" },
	{ 4,	3,	"bc4" },
	{ 5,	3,	"bc5" },
	{ 6,	3,	"bc6" },
	{ 7,	3,	"bc7" },
	{ 8,	3,	"bc8" },
	{ 9,	3,	"bc9" },
	{ 10,	4,	"bc10" },
	{ 11,	4,	"bc11" },
	{ 12,	4,	"bc12" },
	{ 13,	4,	"bc13" },
	{ 14,	4,	"bc14" },
	{ 15,	4,	"bc15" },
	{ 16,	4,	"bc16" },
	{ 17,	4,	"bc17" },
	{ 18,	7,	"spare14" },
	{ 19,	7,	"spare13" },
	{ 20,	7,	"spare12" },
	{ 21,	7,	"spare11" },
	{ 22,	7,	"spare10" },
	{ 23,	6,	"spare9" },
	{ 24,	6,	"spare8" },
	{ 25,	6,	"spare7" },
	{ 26,	6,	"spare6" },
	{ 27,	6,	"spare5" },
	{ 28,	6,	"spare4" },
	{ 29,	6,	"spare3" },
	{ 30,	6,	"spare2" },
	{ 31,	6,	"spare1" }
	/* This list is extensible */
};
static unsigned int asn_MAP_BandclassCDMA2000_enum2value_1[] = {
	0,	/* bc0(0) */
	1,	/* bc1(1) */
	10,	/* bc10(10) */
	11,	/* bc11(11) */
	12,	/* bc12(12) */
	13,	/* bc13(13) */
	14,	/* bc14(14) */
	15,	/* bc15(15) */
	16,	/* bc16(16) */
	17,	/* bc17(17) */
	2,	/* bc2(2) */
	3,	/* bc3(3) */
	4,	/* bc4(4) */
	5,	/* bc5(5) */
	6,	/* bc6(6) */
	7,	/* bc7(7) */
	8,	/* bc8(8) */
	9,	/* bc9(9) */
	31,	/* spare1(31) */
	22,	/* spare10(22) */
	21,	/* spare11(21) */
	20,	/* spare12(20) */
	19,	/* spare13(19) */
	18,	/* spare14(18) */
	30,	/* spare2(30) */
	29,	/* spare3(29) */
	28,	/* spare4(28) */
	27,	/* spare5(27) */
	26,	/* spare6(26) */
	25,	/* spare7(25) */
	24,	/* spare8(24) */
	23	/* spare9(23) */
	/* This list is extensible */
};
static asn_INTEGER_specifics_t asn_SPC_BandclassCDMA2000_specs_1 = {
	asn_MAP_BandclassCDMA2000_value2enum_1,	/* "tag" => N; sorted by tag */
	asn_MAP_BandclassCDMA2000_enum2value_1,	/* N => "tag"; sorted by N */
	32,	/* Number of elements in the maps */
	33,	/* Extensions before this member */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static ber_tlv_tag_t asn_DEF_BandclassCDMA2000_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
asn_TYPE_descriptor_t asn_DEF_BandclassCDMA2000 = {
	"BandclassCDMA2000",
	"BandclassCDMA2000",
	BandclassCDMA2000_free,
	BandclassCDMA2000_print,
	BandclassCDMA2000_constraint,
	BandclassCDMA2000_decode_ber,
	BandclassCDMA2000_encode_der,
	BandclassCDMA2000_decode_xer,
	BandclassCDMA2000_encode_xer,
	BandclassCDMA2000_decode_uper,
	BandclassCDMA2000_encode_uper,
	BandclassCDMA2000_decode_aper,
	BandclassCDMA2000_encode_aper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_BandclassCDMA2000_tags_1,
	sizeof(asn_DEF_BandclassCDMA2000_tags_1)
		/sizeof(asn_DEF_BandclassCDMA2000_tags_1[0]), /* 1 */
	asn_DEF_BandclassCDMA2000_tags_1,	/* Same as above */
	sizeof(asn_DEF_BandclassCDMA2000_tags_1)
		/sizeof(asn_DEF_BandclassCDMA2000_tags_1[0]), /* 1 */
	&asn_PER_type_BandclassCDMA2000_constr_1,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_BandclassCDMA2000_specs_1	/* Additional specs */
};

