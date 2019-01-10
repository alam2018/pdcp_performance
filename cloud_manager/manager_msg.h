/*
 * manaer_msg.h
 *
 *  Created on: Dec 6, 2018
 *      Author: user
 */

#ifndef MANAGER_MSG_H_
#define MANAGER_MSG_H_

#include <stdio.h>
#include "types.h"
//#include "platform_types.h"
//#include "mem_block.h"
#include "stdbool.h"
//#include "pdcp.h"


#define ROHC_COMPRESSION
//#undef ROHC_COMPRESSION
#define IP_HEADER_SIZE 20
#define UDP_HEADER_SIZE 8
#define RTP_HEADER_SIZE 12

#define BUFFER_READ_DELAY_REPORT
#undef BUFFER_READ_DELAY_REPORT

//#define MAXUPSOCKET 5


//#define PAYLOAD_SIZE    1400
#define NUM_TO_MSGDX(n) (n << 16)


#define MAX_NO_SOCKET_CONN 				250
#define BUFFER_SIZE 					10000
#define CPU_CAPACITY					9485.8662


VOID MsgReceive(INT32 connectedSockFd);

UINT8 *pdcpSendBuffer, *temppdcpSendBuffer;
uint8_t *pdcpReceiveBuffer,*temppdcpReceiveBuffer;
int total_Numberof_Mudule;

//Database of connection information for all the connected entities

typedef struct resDB {
	int currentusage;
	int allocatedCPU;
}_tResourceDB;

typedef struct schedSockbufferHdr {
	int     		module_id;
	int 			sockFD;
	int				qosIndex;
	char 			entity[10];					//
	UINT32			msgID;
	bool 			isBufferUsed;
	UINT32 			msgSize;			//Size of pData
	uint8_t 		*pData;				//contains the original buffer
	_tResourceDB	res_db;
}_tSchedBuffer;



//******************************************************************************
// Message Architecture
//******************************************************************************

typedef struct extMsg
{
    UINT32 msgId; //Indicates the messageID
    UINT32 msgSize; //Indicates the size of the message payload
    UINT8  dataPacket[BUFFER_SIZE]; //Contains the actual Payload
} __attribute__((packed)) EXT_MSG_T;


//******************************************************************************
// Name Message Identifiers
//******************************************************************************

#define MSGID_PDCP_INCOMMING              	NUM_TO_MSGDX(1)    // (95536)
#define MSGID_PDCP_OUTGOING               	NUM_TO_MSGDX(2)
#define MSGID_CLOUD_MANAGER					NUM_TO_MSGDX(3)


//******************************************************************************
// Name Message Identifiers
//******************************************************************************

/*
 * Incoming message identifiers
*/

#define PDCP_BASE_MSG_IN_ID             (MSGID_PDCP_INCOMMING)

#define PDCP_RUN_FUNC                (PDCP_BASE_MSG_IN_ID) // (65536)
#define PDCP_DATA_REQ_FUNC			 (PDCP_BASE_MSG_IN_ID + 1)
#define PDCP_DATA_IND				 (PDCP_BASE_MSG_IN_ID + 2)
#define PDCP_REMOVE_UE				 (PDCP_BASE_MSG_IN_ID + 3)
#define RRC_PDCP_CONFIG_REQ	 		 (PDCP_BASE_MSG_IN_ID + 4)
#define PDCP_MODULE_CLEANUP			 (PDCP_BASE_MSG_IN_ID + 5)
#define RLC_STATUS_FOR_PDCP			 (PDCP_BASE_MSG_IN_ID + 6)
#define PDCP_REG_REQ				 (PDCP_BASE_MSG_IN_ID + 7)
#define RRC_PDCP_CONFIG_ASN1_REQ	 (PDCP_BASE_MSG_IN_ID + 8)
#define PDCP_MODULE_INIT_REQ		 (PDCP_BASE_MSG_IN_ID + 9)
#define PDCP_CONFIG_SET_SECURITY_REQ (PDCP_BASE_MSG_IN_ID + 10)
#define PDCP_HASH_COLLEC 			 (PDCP_BASE_MSG_IN_ID + 11)
#define PDCP_GET_SEQ_NUMBER_TEST	 (PDCP_BASE_MSG_IN_ID + 12)




/*
 * Outgoing message identifiers
*/

#define PDCP_BASE_MSG_OUT_ID             (MSGID_PDCP_OUTGOING)

#define RLC_DATA_REQ					 (PDCP_BASE_MSG_OUT_ID)
#define PDCP_REG_RSP					 (PDCP_BASE_MSG_OUT_ID + 1)
#define PDCP_DATA_REQ_RSP				 (PDCP_BASE_MSG_OUT_ID + 2)
#define PDCP_DATA_IND_SEND_RSP			 (PDCP_BASE_MSG_OUT_ID + 3)
#define PDCP_RRC_DATA_IND_RSP			 (PDCP_BASE_MSG_OUT_ID + 4)
#define MAC_ENB_GET_RRC_STATUS_REQ		 (PDCP_BASE_MSG_OUT_ID + 5)
#define MAC_ENB_GET_RRC_STATUS_RSP		 (PDCP_BASE_MSG_OUT_ID + 6)


/*Cloud manager Message definition */
#define CLOUD_MANAGER_BASE_MSG_ID            	(MSGID_CLOUD_MANAGER)
#define CLOUD_MANAGER_REGISTRATION				(CLOUD_MANAGER_BASE_MSG_ID)
#define CLOUD_MANAGER_RESOURCE_HANDLE			(CLOUD_MANAGER_BASE_MSG_ID + 1)


//******************************************************************************
// Cloud Manager Message Structure
//******************************************************************************

typedef struct
{
	int 		module_id;     						/*!< \brief  Virtualized module identifier      */
	int  		reg_resp;      						/*!< \brief  Registration response to the requested module. Send 1 for successful registration else -1 */
	int			qosIndex;							/*!< \brief  Indicate the QoS flow index got from SDAP      */
} __attribute__((packed)) CLOUD_MANAGER_REGISTRATION_T;


typedef struct
{
	int 		module_id;     							/*!< \brief  Virtualized module identifier      */
	int  		resource_req;      						/*!< \brief  Amount of CPU resource request from an module */
	int			resource_rsp;							/*!< \brief  Amount of allocated CPU resource from the cloud manager */
	int			down_BW_req;							/*!< \brief  Downlink Bandwidth request */
	int			down_BW_rsp;							/*!< \brief  Downlink Bandwidth allocation from CM */
	int			up_BW_req;								/*!< \brief  Uplink Bandwidth request */
	int			up_BW_rsp;								/*!< \brief  Uplink Bandwidth allocation from CM */
	int			res_querry_enable;						/*!< \brief  Cloud manager asks to module about current resource usage report. Set 1, when module is asking
														for cpu, 2 when manager is asking modules about there current usage, 3 when modules are replying about managers query  */
} __attribute__((packed)) CLOUD_MANAGER_RESOURCE_HANDLE_T;



#endif /* MANAER_MSG_H_ */
