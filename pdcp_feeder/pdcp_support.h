/*
 * pdcp_support.h
 *
 *  Created on: Oct 8, 2017
 *      Author: idefix
 */

#ifndef PDCP_SUPPORT_H_
#define PDCP_SUPPORT_H_

boolean_t pdcp_init_seq_numbers(pdcp_t* pdcp_entity);

void pdcp_layer_init(void);

rlc_op_status_t rlc_status_return (rlc_op_status_t val);

rlc_op_status_t rlc_status_resut(const protocol_ctxt_t* const ctxt_pP,
        const srb_flag_t   srb_flagP,
        const MBMS_flag_t  MBMS_flagP,
        const rb_id_t      rb_idP,
        const mui_t        muiP,
        confirm_t    confirmP,
        sdu_size_t   sdu_sizeP,
        mem_block_t *sdu_pP);

#endif /* PDCP_SUPPORT_H_ */
