/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "fixed_grammar.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_LoggingDuration_r10_H_
#define	_LoggingDuration_r10_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum LoggingDuration_r10 {
	LoggingDuration_r10_min10	= 0,
	LoggingDuration_r10_min20	= 1,
	LoggingDuration_r10_min40	= 2,
	LoggingDuration_r10_min60	= 3,
	LoggingDuration_r10_min90	= 4,
	LoggingDuration_r10_min120	= 5,
	LoggingDuration_r10_spare2	= 6,
	LoggingDuration_r10_spare1	= 7
} e_LoggingDuration_r10;

/* LoggingDuration-r10 */
typedef long	 LoggingDuration_r10_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_LoggingDuration_r10;
asn_struct_free_f LoggingDuration_r10_free;
asn_struct_print_f LoggingDuration_r10_print;
asn_constr_check_f LoggingDuration_r10_constraint;
ber_type_decoder_f LoggingDuration_r10_decode_ber;
der_type_encoder_f LoggingDuration_r10_encode_der;
xer_type_decoder_f LoggingDuration_r10_decode_xer;
xer_type_encoder_f LoggingDuration_r10_encode_xer;
per_type_decoder_f LoggingDuration_r10_decode_uper;
per_type_encoder_f LoggingDuration_r10_encode_uper;
per_type_decoder_f LoggingDuration_r10_decode_aper;
per_type_encoder_f LoggingDuration_r10_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _LoggingDuration_r10_H_ */
#include <asn_internal.h>
