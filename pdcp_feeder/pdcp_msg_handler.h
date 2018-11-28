/*
 * pdcp_msg_handler.h
 *
 *  Created on: Oct 10, 2017
 *      Author: idefix
 */

#ifndef PDCP_MSG_HANDLER_H_
#define PDCP_MSG_HANDLER_H_

#include <stdio.h>
#include "types.h"
#include "platform_types.h"
#include "mem_block.h"
#include "stdbool.h"
#include "SRB-ToAddModList.h"
#include "DRB-ToAddModList.h"
#include "DRB-ToReleaseList.h"
#include "PMCH-InfoList-r9.h"
#include "pdcp.h"

boolean_t pdcp_data_req_send(
  const protocol_ctxt_t* const  ctxt_pP,
  const srb_flag_t     srb_flagP,
  const rb_id_t        rb_idP,
  const mui_t          muiP,
  const confirm_t      confirmP,
  const sdu_size_t     sdu_buffer_sizeP,
  unsigned char *const sdu_buffer_pP,
  const pdcp_transmission_mode_t modeP
);

boolean_t
pdcp_data_ind_send(
  const protocol_ctxt_t* const ctxt_pP,
  const srb_flag_t   srb_flagP,
  const MBMS_flag_t  MBMS_flagP,
  const rb_id_t      rb_idP,
  const sdu_size_t   sdu_buffer_sizeP,
  mem_block_t* const sdu_buffer_pP
);

void
pdcp_run_send (
		module_id_t module_id,
		eNB_flag_t  enb_flag,
//		instance_t  instance,
		rnti_t      rnti,
		frame_t     frame,
		sub_frame_t subframe,
		eNB_index_t eNB_index
);


boolean_t
pdcp_remove_UE_send(
  const protocol_ctxt_t* const  ctxt_pP
);

boolean_t
rrc_pdcp_config_asn1_req_send (
  const protocol_ctxt_t* const  ctxt_pP,
  SRB_ToAddModList_t  *const srb2add_list_pP,
  DRB_ToAddModList_t  *const drb2add_list_pP,
  DRB_ToReleaseList_t *const drb2release_list_pP,
  const uint8_t                   security_modeP,
  uint8_t                  *const kRRCenc_pP,
  uint8_t                  *const kRRCint_pP,
  uint8_t                  *const kUPenc_pP
#ifdef Rel10
  ,PMCH_InfoList_r9_t*  const pmch_InfoList_r9_pP
#endif
);

void
rrc_pdcp_config_req_send (
  const protocol_ctxt_t* const  ctxt_pP,
  const srb_flag_t srb_flagP,
  const uint32_t actionP,
  const rb_id_t rb_idP,
  const uint8_t security_modeP);

int
pdcp_module_init_send (
  void
);

void pdcp_module_cleanup_send (void);


rlc_op_status_t rlc_data_req     (const protocol_ctxt_t* const ctxt_pP,
                                  const srb_flag_t   srb_flagP,
                                  const MBMS_flag_t  MBMS_flagP,
                                  const rb_id_t      rb_idP,
                                  const mui_t        muiP,
                                  confirm_t    confirmP,
                                  sdu_size_t   sdu_sizeP,
                                  mem_block_t *sdu_pP);

void
pdcp_rrc_data_ind(
  const protocol_ctxt_t* const ctxt_pP,
  const rb_id_t                srb_idP,
  const sdu_size_t             sdu_sizeP,
  uint8_t              * const buffer_pP
);

int mac_eNB_get_rrc_status(const module_id_t   module_idP, const rnti_t  rntiP);

void
pdcp_config_set_security_send(
  const protocol_ctxt_t* const  ctxt_pP,
  pdcp_t         * const pdcp_pP,
  const rb_id_t         rb_idP,
  const uint16_t        lc_idP,
  const uint8_t         security_modeP,
  uint8_t        * const kRRCenc,
  uint8_t        * const kRRCint,
  uint8_t        * const  kUPenc);


hash_table_t  *pdcp_coll_p_new;
void   get_pdcp_coll_p();


void connect_main ();
#endif /* PDCP_MSG_HANDLER_H_ */
