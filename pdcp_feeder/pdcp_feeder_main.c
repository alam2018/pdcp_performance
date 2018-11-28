/*
 * pdcp_feeder_main.c
 *
 *  Created on: Nov 13, 2017
 *      Author: idefix
 */


/*
 * pdcp_gw_main.c
 *
 *  Created on: Oct 9, 2017
 *      Author: idefix
 */


#include <stdint.h>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "sys/socket.h"
#include "sys/ioctl.h"
#include "sys/types.h"
#include "netinet/in.h"
#include "net/if.h"
#include "unistd.h"
#include "arpa/inet.h"
#include <netdb.h>
#include <sys/select.h>
#include <fcntl.h>//non blocking function
#include <sys/time.h>
#include "errno.h"
#include <time.h>
#include <netinet/tcp.h>
#include <stdbool.h>
#include <sched.h>
#include "signal.h"
#include <pthread.h>

#include "types.h"
#include "math.h"
#include "list.h"
#include "pdcp.h"
#include "log.h"
//#include "pdcp_support.h"

//#include "collec_dec_pdcp.h"
#include "socket_msg.h"
#include "platform_types.h"
#include "mem_block.h"
#include "stdbool.h"
#include "pdcp_msg_handler.h"
#include "rohc_proc.h"


//#include "config.h" /* for HAVE_*_H definitions */

#if HAVE_WINSOCK2_H == 1
#  include <winsock2.h> /* for htons() on Windows */
#endif
#if HAVE_ARPA_INET_H == 1
#  include <arpa/inet.h> /* for htons() on Linux */
#endif

/* includes required to use the compression part of the ROHC library */
#include <rohc/rohc.h>
#include <rohc/rohc_comp.h>


#ifdef ROHC_COMPRESSION
	/* the buffer that will contain the IPv4 packet to compress */
	uint8_t ip_buffer[ROHC_BUFFER_SIZE];
	struct rohc_buf ip_packet = rohc_buf_init_empty(ip_buffer, ROHC_BUFFER_SIZE);
	int rohc_data_size;
	int total_pkt_size;
#endif

//******************************************************************************
// Global Declarations
//******************************************************************************

INT32 gConnectSockFd, gConnectSockFdUplink;
INT32 gListenSockFd;
INT32 gNewConnectedListenSockFd;
INT32 sendFD;
fd_set fdgroup;
fd_set readFds;
// This defines the measurement time interval in sec and microsecs.
int measurem_intvall_s  = 0;
int measurem_intvall_us = 200;



// Socket and socket function related variables
struct sockaddr_in socketAddrPDCP, socketAddrPDCPUplink;
struct timeval timeout;
//    struct timespec timeout;

INT32 fdmax;
INT32 reuseaddr = TRUE;
INT32 portno_PDCP, portno_PDCPUplink;


// Message send , receive and handling related variables

INT8 *module;
//BOOL loadMeasure = FALSE;
INT32 retValue;
UINT32 sizeOfMsg;
UINT32 responseBufferSize;
bool file_param;


bool result_get;
bool hash_result;

#define SEC_TO_NANO_SECONDS  1000000000
struct timespec send_time, rec_time;
double total_time;

sdu_size_t test_packet_size;

extern bool pdcpFeederAsSDAP;

//#define WRITE_REPORT


EXT_MSG_T ExtRecMsg;
UINT32	sockExtHeaderSize = sizeof(ExtRecMsg.msgId) + sizeof (ExtRecMsg.msgSize);// implicitly calculating header size


//Message defination
PDCP_DATA_REQ_RSP_T 		pdcpDataReqRspMsg;
PDCP_DATA_IND_SEND_RSP_T	pdcpDataIndSendRsp;
RLC_DATA_REQ_T				rlcDataReqRsp;
PDCP_RRC_DATA_IND_RSP_T		pdcpRRCDataIndRsp;
MAC_ENB_GET_RRC_STATUS_REQ_T macENBRRCStatusReq;
PDCP_HASH_COLLEC_T 			pdcp_hash_msg;
PDCP_DATA_REQ_FUNC_T				pdcpDataReqMsg;


int msg_send (int msgNO);

VOID MsgReceive(INT32 connectedSockFd);
static VOID MsgSend(int sendFD);
static VOID MsgInsertFunc (
                              UINT32 MsgId ,
                              UINT32 MsgSize,
                              VOID* MsgData,
                              UINT8 **buffer
		             );
static VOID MsgHandler(UINT32 messageId, INT32 sockFd);
static VOID sockSetNonBlocking(INT32 sockFD);


extern unsigned char* pdcp_test_pdu_buffer;
extern unsigned char pdcp_test_pdu_buffer_size;
extern int create_packet(struct rohc_buf *const packet);


boolean_t get_result(int sockFD)
{
	int loop = 1;
	result_get = false;
	while(loop)
	{
		sleep(1);
		timeout.tv_sec  = 1;
		timeout.tv_usec = measurem_intvall_us;
		readFds = fdgroup;
		INT32 n = select(sockFD+1,&readFds,NULL,NULL,&timeout);

		if(n < 0)
		  {
			  perror("select() failed");
			  exit(EXIT_FAILURE);
		  }
		if (FD_ISSET(sockFD,&readFds))
		{
			MsgReceive (sockFD);

			if (ExtRecMsg.msgId == PDCP_DATA_REQ_FUNC)
			{
#ifdef WRITE_REPORT
	clock_gettime(CLOCK_MONOTONIC, &rec_time);
#endif
				loop = -1;
				memcpy (&pdcpDataReqMsg, temppdcpReceiveBuffer, ExtRecMsg.msgSize);
//				pdcpDataReqMsg.pdcp_pdu = ((PDCP_DATA_REQ_FUNC_T*)temppdcpReceiveBuffer)->pdcp_pdu;
				return true;
				result_get = false;
			}
		}
	}

	return -1;
}

//void *receiveMessage(void *sock_desc)
void receiveMessage()
{
	// ---------------------------------------------------------------------------
    // Create Socket for BBSC communication
	// ---------------------------------------------------------------------------

    gConnectSockFd = socket(AF_INET, SOCK_STREAM, 0);

    if (gConnectSockFd < 0)
	{
	  perror("ERROR opening PDCP'socket");
	  printf("OAI module start failed!!! \n");
	  exit (EXIT_FAILURE);
	}

	fflush(stdout);

	// Feeder try to connect to PDCP
	int val = connect(gConnectSockFd,(struct sockaddr *) &socketAddrPDCP,sizeof(socketAddrPDCP));
	if ( val == SYSCALLFAIL)
	{
		perror("connect");
		printf("Check if PDCP is available for connection \n");
		printf("OAI module start failed!!! \n");
		exit(EXIT_FAILURE);
	} else
		printf ("Successful connection from OAI to PDCP established\n");

	//Allow socket descriptor to be reusable and non blocking
	val = setsockopt(gConnectSockFd, SOL_SOCKET,  SO_REUSEADDR,	(char *)&reuseaddr, sizeof(reuseaddr));

	if (val < 0)
		{
		  perror("setsockopt() failed");
		  close(gConnectSockFd);
		  printf("OAI module start failed!!! \n");
		  exit(EXIT_FAILURE);
		}

	sockSetNonBlocking(gConnectSockFd);

	//Initialize the master fd_set

//	FD_ZERO(&fdgroup);
//	FD_ZERO(&readFds);
//
//	FD_SET(gListenSockFd,&fdgroup);
//	FD_SET(gConnectSockFd,&fdgroup);
//
//	fdmax = gListenSockFd;

	if (isUplink == 1)
	{

	    gConnectSockFdUplink = socket(AF_INET, SOCK_STREAM, 0);

	    if (gConnectSockFdUplink < 0)
		{
		  perror("ERROR opening PDCP'socket");
		  printf("Uplink PDCP module start failed!!! \n");
		  exit (EXIT_FAILURE);
		}

		fflush(stdout);

		// OAI try to connect to PDCP
		int valUplink = connect(gConnectSockFdUplink,(struct sockaddr *) &socketAddrPDCPUplink,sizeof(socketAddrPDCPUplink));
		if ( valUplink == SYSCALLFAIL)
		{
			perror("connect");
			printf("Check if Uplink PDCP is available for connection \n");
			printf("Uplink PDCP module start failed!!! \n");
			exit(EXIT_FAILURE);
		} else
			printf ("Successful connection from OAI to PDCP established\n");

		//Allow socket descriptor to be reusable and non blocking
		valUplink = setsockopt(gConnectSockFdUplink, SOL_SOCKET,  SO_REUSEADDR,	(char *)&reuseaddr, sizeof(reuseaddr));

		if (valUplink < 0)
			{
			  perror("setsockopt() failed");
			  close(gConnectSockFdUplink);
			  printf("OAI module start failed!!! \n");
			  exit(EXIT_FAILURE);
			}

		sockSetNonBlocking(gConnectSockFdUplink);

	}


	//Initialize the master fd_set

	FD_ZERO(&fdgroup);
	FD_ZERO(&readFds);

	FD_SET(gConnectSockFd,&fdgroup);
	FD_SET(gListenSockFd,&fdgroup);
	FD_SET(gConnectSockFdUplink,&fdgroup);

	fdmax = gListenSockFd;

	// Allocate memory to the send  buffer
	pdcpSendBuffer =  (UINT8*) (malloc(BUFFER_SIZE));
	if (NULL == pdcpSendBuffer)
		{
			printf("PDCP module start failed!!! \n");
			exit(EXIT_FAILURE);
		}

	// Allocate memory to the receive buffer
	pdcpReceiveBuffer = (UINT8*) (malloc(BUFFER_SIZE));
	if (NULL == pdcpReceiveBuffer)
		{
			printf("PDCP module start failed!!! \n");
			exit(EXIT_FAILURE);
		}

	temppdcpSendBuffer = pdcpSendBuffer;

	// Set to zero.
	memset(pdcpSendBuffer,0,BUFFER_SIZE);	// Allocate memory to the send  buffer

	test_main();

}


//Function to set the sockets to nonBlocking

static VOID sockSetNonBlocking(INT32 sockFD)
{
	INT32 sockNonBlockopts;

	sockNonBlockopts = fcntl(sockFD,F_GETFL);

	if (0 > sockNonBlockopts)
		{
			perror("fcntl(F_GETFL)");
			printf("PDCP module start failed!!! \n");
			exit(EXIT_FAILURE);
		}

	sockNonBlockopts = (sockNonBlockopts | O_NONBLOCK);
	if (0 > fcntl(sockFD,F_SETFL,sockNonBlockopts))
		{
			perror("fcntl(F_SETFL)");
			printf("PDCP module start failed!!! \n");
			exit(EXIT_FAILURE);
		}

	int one = 4;
	unsigned int len = sizeof(one);
	int resOpt = getsockopt(sockFD, SOL_TCP, TCP_NODELAY, (void*)&one, &len);

	one =1;

	resOpt = setsockopt(sockFD, SOL_TCP, TCP_NODELAY, &one, sizeof(one));
	resOpt = getsockopt(sockFD, SOL_TCP, TCP_CORK, (void*)&one, &len);
	resOpt = getsockopt(sockFD, SOL_TCP, TCP_NODELAY, (void*)&one, &len);
	return;
}



//Initializing all the parameters for PDCP connection
void set_txt_inp (int countLine, char *val)
{
	switch (countLine)
	{
	case 1:
		printf("PDCP connection parameter reading started\n\n");
		break;

	case 2:
		socketAddrPDCP.sin_addr.s_addr = inet_addr(val);
		printf ("PDCP IP: %s", val);
		break;

	case 3:
		portno_PDCP = atoi(val);
		socketAddrPDCP.sin_port = htons(portno_PDCP);
		printf ("PDCP Port: %s", val);
		break;

	case 4:
		isUplink = atoi(val);
		printf ("PDCP direction: %s", val);
		break;

	case 5:
		socketAddrPDCPUplink.sin_addr.s_addr = inet_addr(val);
		printf ("UPlink PDCP IP: %s", val);
		break;

	case 6:
		portno_PDCPUplink = atoi(val);
		socketAddrPDCPUplink.sin_port = htons(portno_PDCPUplink);
		printf ("Uplink PDCP Port: %s", val);
		break;
	 default:
	 {
		 printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
		 printf("Unknown msg received from PDCP\n\n\n\n");
		 printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	 }
	 break;
	}
}


int main( INT32 argc, INT8 **argv)

{
	//Setup the test packet size for PDCP
	test_packet_size = atoi(argv[1]);
	printf ("Test packet size set %d byte\n\n", test_packet_size);
    // Initialize or filling up the socket structure of PDCP
	bzero((char *) &socketAddrPDCP, sizeof(socketAddrPDCP));
	socketAddrPDCP.sin_family = AF_INET;

	bzero((char *) &socketAddrPDCPUplink, sizeof(socketAddrPDCPUplink));
	socketAddrPDCPUplink.sin_family = AF_INET;

	FILE* lrmConfFile = 0;
	lrmConfFile = fopen("OAI_sock_file.conf","r");

	int lineCount = 0;
	if (lrmConfFile == 0)
	{
		printf("Configuration file not found!!! \n");
		printf("PDCP module connection failed!!! \n\n");
		exit (EXIT_FAILURE);
	} else
	{
		printf("Configuration file found. Now analyzing the inputs \n");
		char line[80];
		while(fgets(line, sizeof(line),lrmConfFile)!=NULL)///something in the file
		{
			if (line[0] == 'S')
			{
				file_param = true;
			}

			if (file_param == true)
			{
				lineCount++;
				set_txt_inp (lineCount, &line[0]);
			}
		}
	}

//	pthread_t receive_thread;
//	pthread_create(&receive_thread, NULL, receiveMessage, NULL);
//	pthread_join(receive_thread, NULL);
	receiveMessage();
	return 0;
}

static VOID MsgSend(int sendFD)
{
	INT32  retValue = 0;

	int sizeOfMsg = responseBufferSize;
	retValue = send(sendFD,pdcpSendBuffer,sizeOfMsg,0);
	printf("Sent msg on Fd (%d) \n\n",sendFD );


	if (SYSCALLFAIL == retValue)
	{
	  perror("send failed");
	}

	// reset the sendBuffer flag
	temppdcpSendBuffer = pdcpSendBuffer;
	// Set to zero.
	responseBufferSize = 0;
	memset(pdcpSendBuffer,0,BUFFER_SIZE);
	return ;

}



/*!----------------------------------------------------------------------------
*Construction of buffer for sending message
*
------------------------------------------------------------------------------*/
static VOID MsgInsertFunc (
                              UINT32 MsgId ,
                              UINT32 MsgSize,
                              VOID* MsgData,
                              UINT8 **buffer
		             )
{
    EXT_MSG_T lrmExtMsg;

    lrmExtMsg.msgId = MsgId;
    lrmExtMsg.msgSize = MsgSize; //Indicates the size of the message payload
    // Set/re-set the external structure
    memset(lrmExtMsg.dataPacket,0, BUFFER_SIZE);//SRK

    memcpy(lrmExtMsg.dataPacket,MsgData,lrmExtMsg.msgSize);
    memset(*buffer,0,BUFFER_SIZE);

    memcpy(*buffer,&lrmExtMsg.msgId, sizeof(lrmExtMsg.msgId));
    *buffer += sizeof(lrmExtMsg.msgId);

    memcpy(*buffer,&lrmExtMsg.msgSize, sizeof(lrmExtMsg.msgSize));
    *buffer += sizeof(lrmExtMsg.msgSize);

    memcpy(*buffer, lrmExtMsg.dataPacket, lrmExtMsg.msgSize);
    *buffer += lrmExtMsg.msgSize;

    responseBufferSize = (sizeof(lrmExtMsg.msgId))+ (sizeof(lrmExtMsg.msgSize))+ (lrmExtMsg.msgSize);

    return ;
}


VOID MsgReceive(INT32 connectedSockFd)
{
	INT32 retValue = -1;
//	sckClose = false;
	// memorise the start address of the send buffer
//	int schedID = findCon(connectedSockFd);
//	temppdcpReceiveBuffer = activeRequests[schedID].pData;

	// reset the receive Buffer flag
	temppdcpReceiveBuffer = pdcpReceiveBuffer;
	memset(temppdcpReceiveBuffer,0,BUFFER_SIZE);
	retValue = recv(connectedSockFd,temppdcpReceiveBuffer,sockExtHeaderSize,0); //LRM receives message on templrmReceiverBufer

	if (retValue == SYSCALLFAIL )
	{
		perror("recv");
		printf("recv() returned Error \n");
		retValue = 0;
		return;
	} else
	{

		 // if the Message has some data in the payload
		ExtRecMsg.msgId = ((EXT_MSG_T*)temppdcpReceiveBuffer)->msgId;
		ExtRecMsg.msgSize = ((EXT_MSG_T*)temppdcpReceiveBuffer)->msgSize;
		temppdcpReceiveBuffer += sockExtHeaderSize;


		 if (ExtRecMsg.msgSize)
		 {
			 retValue = recv(connectedSockFd,temppdcpReceiveBuffer, ExtRecMsg.msgSize, 0);
			 result_get = true;
			 if (retValue == SYSCALLFAIL )
			 {
				 perror("recv2");
				 printf("recv() returned Error \n");
			 }
		 }

		 // call message handler here
//		 MsgHandler(ExtRecMsg.msgId, connectedSockFd);
	}
}


boolean_t pdcp_data_req_send(
  const protocol_ctxt_t* const  ctxt_pP,
  const srb_flag_t     srb_flagP,
  const rb_id_t        rb_idP,
  const mui_t          muiP,
  const confirm_t      confirmP,
  const sdu_size_t     sdu_buffer_sizeP,
  unsigned char *const sdu_buffer_pP,
  const pdcp_transmission_mode_t modeP
)
{
	PDCP_DATA_REQ_FUNC_T pdcpDataReqFuncMsg;

	pdcpDataReqFuncMsg.ctxt_pP				= *ctxt_pP;
	pdcpDataReqFuncMsg.srb_flagP			= srb_flagP;
	pdcpDataReqFuncMsg.rb_id				= rb_idP;
	pdcpDataReqFuncMsg.muiP					= muiP;
	pdcpDataReqFuncMsg.confirmP				= confirmP;
	pdcpDataReqFuncMsg.sdu_buffer_size		= sdu_buffer_sizeP;

#ifdef ROHC_COMPRESSION


	rohc_data_size = create_packet(&ip_packet); //This length contains the size of IP header and fake payload
	total_pkt_size = rohc_data_size + 2 * sizeof (uint64_t) + 3 * sizeof (size_t);


	/* create a fake IP packet for the purpose of this example program */
	printf("\nbuild a fake IP/UDP/RTP packet\n");

	pdcpDataReqFuncMsg.rohc_packet.len = ip_packet.len; //This length contains the size of IP header and fake payload
	pdcpDataReqFuncMsg.rohc_packet.time.sec = ip_packet.time.sec;
	pdcpDataReqFuncMsg.rohc_packet.time.nsec = ip_packet.time.nsec;
	pdcpDataReqFuncMsg.rohc_packet.max_len = ip_packet.max_len;
	pdcpDataReqFuncMsg.rohc_packet.offset = ip_packet.offset;
//	memcpy (pdcpDataReqFuncMsg.rohc_packet.data, ip_packet.data, rohc_data_size);
	memcpy (pdcpDataReqFuncMsg.rohc_packet.ipData, ip_packet.data, ip_packet.len);
	memcpy (pdcpDataReqFuncMsg.rohc_packet.dataBuffer, sdu_buffer_pP, pdcpDataReqFuncMsg.sdu_buffer_size);
#else
	memcpy (&pdcpDataReqFuncMsg.buffer, sdu_buffer_pP, (sdu_buffer_sizeP * sizeof (unsigned char)));
#endif

//	strcpy (pdcpDataReqFuncMsg.buffer, *sdu_buffer_pP);
	pdcpDataReqFuncMsg.mode					= modeP;

	int mem_block_alam_size =  sizeof (unsigned char ) + (SDU_BUFFER_SIZE + MAX_PDCP_HEADER_SIZE + MAX_PDCP_TAILER_SIZE) * sizeof (unsigned char );
	int msgSize = sizeof (protocol_ctxt_t) + sizeof (srb_flag_t) + sizeof (rb_id_t) + sizeof (mui_t) +
			sizeof (confirm_t) + sizeof (sdu_size_t) + pdcpDataReqFuncMsg.sdu_buffer_size +
			sizeof (pdcp_transmission_mode_t) + sizeof (uint16_t) + mem_block_alam_size + sizeof (boolean_t);

	int tstSize = sizeof (PDCP_DATA_REQ_FUNC_T);

	//responseBufferSize = sizeof (UINT32) + sizeof (UINT32) + msgSize;
	responseBufferSize = sizeof (UINT32) + sizeof (UINT32) + tstSize;
#ifdef BUFFER_READ_DELAY_REPORT
	clock_gettime(CLOCK_MONOTONIC, &pdcpDataReqFuncMsg.packet_send);
#endif

	MsgInsertFunc (PDCP_DATA_REQ_FUNC, sizeof (PDCP_DATA_REQ_FUNC_T), &pdcpDataReqFuncMsg, &temppdcpSendBuffer);

#ifdef WRITE_REPORT
	clock_gettime(CLOCK_MONOTONIC, &send_time);
#endif
	MsgSend (gConnectSockFd);

	printf("Size of the data part of the packet sent to PDCP %d\n", pdcpDataReqFuncMsg.sdu_buffer_size);
	boolean_t pdcp_result = true;
	//For uplink test, uncomment the following lines
	printf("Waiting for status reply from PDCP........\n");
	pdcp_result= get_result(gConnectSockFd);
	printf("Got the status reply from PDCP. Continuing the program\n");


#ifdef WRITE_REPORT
	total_time = (double)(rec_time.tv_sec - send_time.tv_sec)*SEC_TO_NANO_SECONDS + (double)(rec_time.tv_nsec - send_time.tv_nsec);

	report();
//	fprintf (feeder_report,"Total time needed by PDCP (us) %f",  total_time/1000);
#endif
	return pdcp_result;
}


/*boolean_t
pdcp_data_ind_send(
  const protocol_ctxt_t* const ctxt_pP,
  const srb_flag_t   srb_flagP,
  const MBMS_flag_t  MBMS_flagP,
  const rb_id_t      rb_idP,
  const sdu_size_t   sdu_buffer_sizeP,
  mem_block_t* const sdu_buffer_pP
)
{
	PDCP_DATA_IND_T pdcpDataIndRsp;
	pdcpDataIndRsp.ctxt_pP					= *ctxt_pP;
	pdcpDataIndRsp.srb_flagP				= srb_flagP;
	pdcpDataIndRsp.MBMS_flagP				= MBMS_flagP;
	pdcpDataIndRsp.rb_id					= rb_idP;
	pdcpDataIndRsp.sdu_buffer_size			= sdu_buffer_sizeP;
	memcpy (&pdcpDataIndRsp.sdu_buffer, sdu_buffer_pP, sizeof (mem_block_t));

	MsgInsertFunc (PDCP_DATA_IND, sizeof(PDCP_DATA_IND_T), &pdcpDataIndRsp, &temppdcpSendBuffer);
	MsgSend (gConnectSockFd);

	printf("Waiting for status reply from PDCP........");
	boolean_t pdcp_result= get_result(gConnectSockFd);
	printf("Got the status reply from PDCP. Continuing the program");
	return pdcp_result;
}*/


void
pdcp_run_send (
		module_id_t module_id,
		eNB_flag_t  enb_flag,
//		instance_t  instance,
		rnti_t      rnti,
		frame_t     frame,
		sub_frame_t subframe,
		eNB_index_t eNB_index
)
{
	PDCP_RUN_FUNC_T pdcpRunSendRsp;
	pdcpRunSendRsp.module_id = module_id;
	pdcpRunSendRsp.enb_flag = enb_flag;
//	pdcpRunSendRsp.instance = instance;
	pdcpRunSendRsp.rnti = rnti;
	pdcpRunSendRsp.frame = frame;
	pdcpRunSendRsp.subframe = subframe;
	pdcpRunSendRsp.eNB_index = eNB_index;

	MsgInsertFunc (PDCP_RUN_FUNC, sizeof(PDCP_RUN_FUNC_T), &pdcpRunSendRsp, &temppdcpSendBuffer);
	MsgSend (gConnectSockFd);

}


boolean_t
pdcp_remove_UE_send(
  const protocol_ctxt_t* const  ctxt_pP
)
{
	PDCP_REMOVE_UE_T pdcpRemUERsp;
	memcpy (&pdcpRemUERsp.ctxt_pP, ctxt_pP, sizeof (protocol_ctxt_t));

	MsgInsertFunc (PDCP_REMOVE_UE, sizeof(PDCP_REMOVE_UE_T), &pdcpRemUERsp, &temppdcpSendBuffer);
	MsgSend (gConnectSockFd);

	return 1;
}

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
  ,PMCH_InfoList_r9_t*  pmch_InfoList_r9_pP
#endif
)
{
	RRC_PDCP_CONFIG_ASN1_REQ_T rrcPdcpConfigAsn1Rsp;

	memcpy (&rrcPdcpConfigAsn1Rsp.ctxt_pP, ctxt_pP, sizeof (protocol_ctxt_t));
	memcpy (&rrcPdcpConfigAsn1Rsp.srb2add_list_pP, srb2add_list_pP, sizeof (SRB_ToAddModList_t));
	memcpy (&rrcPdcpConfigAsn1Rsp.drb2add_list_pP, drb2add_list_pP, sizeof (DRB_ToAddModList_t));
	memcpy (&rrcPdcpConfigAsn1Rsp.drb2release_list_pP, drb2release_list_pP, sizeof (DRB_ToReleaseList_t));
	memcpy (&rrcPdcpConfigAsn1Rsp.security_modeP, &security_modeP, sizeof (uint8_t));
	memcpy (&rrcPdcpConfigAsn1Rsp.kRRCenc_pP, kRRCenc_pP, sizeof (uint8_t));
	memcpy (&rrcPdcpConfigAsn1Rsp.kRRCint_pP, kRRCint_pP, sizeof (uint8_t));
	memcpy (&rrcPdcpConfigAsn1Rsp.kUPenc_pP, kUPenc_pP, sizeof (uint8_t));

	MsgInsertFunc (RRC_PDCP_CONFIG_ASN1_REQ, sizeof(RRC_PDCP_CONFIG_ASN1_REQ_T), &rrcPdcpConfigAsn1Rsp, &temppdcpSendBuffer);
	MsgSend (gConnectSockFd);

	return 1;
}

void
rrc_pdcp_config_req_send (
  const protocol_ctxt_t* const  ctxt_pP,
  const srb_flag_t srb_flagP,
  const uint32_t actionP,
  const rb_id_t rb_idP,
  const uint8_t security_modeP)
{
	RRC_PDCP_CONFIG_REQ_T rrcPdcpConfigRsp;

	memcpy (&rrcPdcpConfigRsp.ctxt_pP, ctxt_pP, sizeof (protocol_ctxt_t));
	rrcPdcpConfigRsp.srb_flagP = srb_flagP;
	rrcPdcpConfigRsp.actionP = actionP;
	rrcPdcpConfigRsp.rb_idP = rb_idP;
	memcpy (&rrcPdcpConfigRsp.security_modeP, &security_modeP, sizeof (uint8_t));

	MsgInsertFunc (RRC_PDCP_CONFIG_REQ, sizeof(RRC_PDCP_CONFIG_REQ_T), &rrcPdcpConfigRsp, &temppdcpSendBuffer);
	MsgSend (gConnectSockFd);
}

int pdcp_module_init_send (void)
{
	PDCP_MODULE_INIT_REQ_T msg;
	MsgInsertFunc (PDCP_MODULE_INIT_REQ, sizeof(PDCP_MODULE_INIT_REQ_T), &msg, &temppdcpSendBuffer);
	MsgSend (gConnectSockFd);

	return 0;
}


void pdcp_module_cleanup_send (void)
{
	PDCP_MODULE_CLEANUP_T pdcpCleanupMsg;
	MsgInsertFunc (PDCP_MODULE_CLEANUP, sizeof(PDCP_MODULE_CLEANUP_T), &pdcpCleanupMsg, &temppdcpSendBuffer);
	MsgSend (gConnectSockFd);
}

void
pdcp_config_set_security_send(
  const protocol_ctxt_t* const  ctxt_pP,
  pdcp_t         * const pdcp_pP,
  const rb_id_t         rb_idP,
  const uint16_t        lc_idP,
  const uint8_t         security_modeP,
  uint8_t        * const kRRCenc,
  uint8_t        * const kRRCint,
  uint8_t        * const  kUPenc)
{
	PDCP_CONFIG_SET_SECURITY_REQ_T pdcpConfigSetSecurityReqMsg;
	memcpy (&pdcpConfigSetSecurityReqMsg.ctxt_pP, ctxt_pP, sizeof (protocol_ctxt_t));
	memcpy (&pdcpConfigSetSecurityReqMsg.pdcp_pP, pdcp_pP, sizeof (pdcp_t));
	pdcpConfigSetSecurityReqMsg.rb_idP = rb_idP;
	pdcpConfigSetSecurityReqMsg.lc_idP = lc_idP;
	memcpy (&pdcpConfigSetSecurityReqMsg.security_modeP, &security_modeP, sizeof (security_modeP));
	memcpy (&pdcpConfigSetSecurityReqMsg.kRRCenc, &kRRCenc, sizeof (kRRCenc));
	memcpy (&pdcpConfigSetSecurityReqMsg.kRRCint, &kRRCint, sizeof (kRRCint));
	memcpy (&pdcpConfigSetSecurityReqMsg.kUPenc, &kUPenc, sizeof (kUPenc));

	MsgInsertFunc (PDCP_CONFIG_SET_SECURITY_REQ, sizeof(PDCP_CONFIG_SET_SECURITY_REQ_T), &pdcpConfigSetSecurityReqMsg, &temppdcpSendBuffer);
	MsgSend (gConnectSockFd);

}

void get_pdcp_coll_p()
{
	MsgInsertFunc (PDCP_HASH_COLLEC, sizeof(PDCP_HASH_COLLEC_T), &pdcp_hash_msg, &temppdcpSendBuffer);
	MsgSend (gConnectSockFd);

	hash_result = false;
	int loop = -1;
	while (loop)
	{
		if (FD_ISSET(gConnectSockFd,&readFds))
		{
			MsgReceive (gConnectSockFd);

			if (hash_result == true)
			{
				loop = 1;
				memcpy (pdcp_coll_p_new, &pdcp_hash_msg.pdcp_coll_p, sizeof (pdcp_hash_msg.pdcp_coll_p));
				break;

			}
		}
	}

}

bool feeder_msg_created = false;



int msg_send (int msgNO)
{
	switch (msgNO)
	{
		case 1:
		{
			module_id_t first = 'H';
			eNB_index_t last = 'E';
			pdcp_run_send (first, true, 10, 20, 30, last);
		}
		break;

		case 2:
		{
			protocol_ctxt_t cp;
			cp.module_id = 'H';
			cp.enb_flag = true;
			cp.module_id = 10;

			srb_flag_t     srb_flagP = false;
			rb_id_t        rb_idP = 5;
			mui_t          muiP = 30;
			confirm_t      confirmP = 40;
			sdu_size_t     sdu_buffer_size_new =test_packet_size;
			const unsigned char sdu_buffer_new[sdu_buffer_size_new];
//			const unsigned char sdu_buffer_pP[sdu_buffer_sizeP];// = {'H', 'E', 'L', 'L', 'O'};
//			unsigned char *buffer = "HELLO";
//			strcpy (sdu_buffer_pP, buffer);

			int i;
//			if (feeder_msg_created == false)
			{
/*				for (i = 0; i<sdu_buffer_size_new; i++)
				{
//					sdu_buffer_new[i] = (unsigned char) i;
					sprintf(sdu_buffer_new[i], "%x", i);
				}*/
				unsigned char *buffer = "NOTE 4: If the keys CK, IK resulting from an EPS AKA run were stored in the fields already available on "
						"the USIM for storing keys CK and IK this could lead to overwriting keys resulting from an earlier run of UMTS AKA. This "
						"would lead to problems when EPS security context and UMTS security context were held simultaneously (as is the case "
						"when security context is stored e.g. for the purposes of Idle Mode Signaling Reduction). Therefore, plastic roaming"
						" where a UICC is inserted into another ME will necessitate an EPS AKA authentication run if the USIM does not support "
						"EMM parameters storage. "
						"UE shall respond with User authentication response message including RES in case of successful AUTN verification and "
						"successful AMF verification as described above. In this case the ME shall compute KASME from CK, IK, and serving "
						"network's identity (SN id) using the KDF as specified in clause A.2. SN id binding implicitly authenticates the serving "
						"network's identity when the derived keys from KASME are successfully used.";
//				strcpy (sdu_buffer_new, buffer);

				memcpy (&sdu_buffer_new, buffer, sdu_buffer_size_new);
				feeder_msg_created = true;
			}
			pdcp_transmission_mode_t modeP = PDCP_TRANSMISSION_MODE_DATA;
//			pdcp_transmission_mode_t modeP = PDCP_TRANSMISSION_MODE_TRANSPARENT;
			return pdcp_data_req_send (&cp, srb_flagP, rb_idP, muiP, confirmP, sdu_buffer_size_new, &sdu_buffer_new, modeP);
		}
		break;

		case 3:
		{
			//Msg send to PDCP for uplink simulation. PDCP feeder acts as RLC
//		    pdcpDataReqMsg.ctxt_pP.enb_flag = 0;

			PDCP_DATA_IND_T pdcpUplinkMsg;

			memcpy (&pdcpUplinkMsg.ctxt_pP, &pdcpDataReqMsg.ctxt_pP, sizeof (protocol_ctxt_t));
			pdcpUplinkMsg.confirmP = pdcpDataReqMsg.confirmP;
			pdcpUplinkMsg.mode = pdcpDataReqMsg.mode;
			pdcpUplinkMsg.muiP = pdcpDataReqMsg.muiP;
			pdcpUplinkMsg.pdcp_pdu_size = pdcpDataReqMsg.pdcp_pdu_size;
			pdcpUplinkMsg.srb_flagP = pdcpDataReqMsg.srb_flagP;
			pdcpUplinkMsg.rb_id = pdcpDataReqMsg.rb_id;
			pdcpUplinkMsg.sdu_buffer_size = pdcpDataReqMsg.sdu_buffer_size;

#ifdef ROHC_COMPRESSION
			pdcpUplinkMsg.rohc_packet.len = pdcpDataReqMsg.rohc_packet.len;
			pdcpUplinkMsg.rohc_packet.offset = pdcpDataReqMsg.rohc_packet.offset;
			pdcpUplinkMsg.rohc_packet.max_len = pdcpDataReqMsg.rohc_packet.max_len;
			memcpy (pdcpUplinkMsg.rohc_packet.ipData, pdcpDataReqMsg.rohc_packet.ipData, ROHC_BUFFER_SIZE);
	memcpy (pdcpUplinkMsg.rohc_packet.dataBuffer, pdcpDataReqMsg.rohc_packet.dataBuffer, pdcpDataReqMsg.sdu_buffer_size);
#else
	memcpy (&pdcpUplinkMsg.buffer, pdcpDataReqMsg.buffer, pdcpDataReqMsg.sdu_buffer_size);
#endif

			MsgInsertFunc (PDCP_DATA_IND, sizeof (PDCP_DATA_IND_T), &pdcpUplinkMsg, &temppdcpSendBuffer);

//		    MsgInsertFunc (PDCP_DATA_REQ_FUNC, sizeof (PDCP_DATA_REQ_FUNC_T), &pdcpDataReqMsg, &temppdcpSendBuffer);
		    MsgSend (gConnectSockFdUplink);
		}
		break;

		case 4:
		{
			PDCP_GET_SEQ_NUMBER_TEST_T pdcpGetSeqNo;
			pdcpGetSeqNo.bufferSize = pdcp_test_pdu_buffer_size;
			memcpy (&pdcpGetSeqNo.pdu_buffer, pdcp_test_pdu_buffer, pdcp_test_pdu_buffer_size);

			int msgSize = 2 * sizeof (int) + pdcp_test_pdu_buffer_size;

			MsgInsertFunc (PDCP_GET_SEQ_NUMBER_TEST, msgSize, &pdcpGetSeqNo, &temppdcpSendBuffer);
			MsgSend (gConnectSockFd);

			hash_result = false;
			int loop = 1;
			while (loop)
			{
				timeout.tv_sec  = 1;
				timeout.tv_usec = measurem_intvall_us;
				readFds = fdgroup;
				INT32 n = select(gConnectSockFd+1,&readFds,NULL,NULL,&timeout);

				if(n < 0)
				  {
					  perror("select() failed");
					  exit(EXIT_FAILURE);
				  }

				if (FD_ISSET(gConnectSockFd,&readFds))
				{
					MsgReceive (gConnectSockFd);

					if (ExtRecMsg.msgId == PDCP_GET_SEQ_NUMBER_TEST)
					{
						loop = -1;
						memcpy (&pdcpGetSeqNo, temppdcpReceiveBuffer, ExtRecMsg.msgSize);
						return pdcpGetSeqNo.return_result;

					}
				}
			}
		}
	}
}

