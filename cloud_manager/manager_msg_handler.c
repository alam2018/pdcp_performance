/*
 * manager_msg_handler.c
 *
 *  Created on: Dec 6, 2018
 *      Author: user
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

#include "manager_msg.h"
#include "types.h"


_tSchedBuffer activeRequests[MAX_NO_SOCKET_CONN];

/*
 * Function forward deceleration
 */

static VOID MsgHandler(UINT32 messageId, INT32 sockFd);
static VOID MsgSend(int sendFD);
void reg_reply_send(CLOUD_MANAGER_REGISTRATION_T mng_reg, INT32 sockFd);
void brodcast_res_usg_report (int db_index);
void get_result();
double allocate_cpu ();


/*!----------------------------------------------------------------------------
*Construction of buffer for sending message
*
------------------------------------------------------------------------------*/
int responseBufferSize;
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


int  delCon(int nSockFd, int Addr)
{
	if (nSockFd<0)
		return -1; // Bad parameter
	activeRequests[nSockFd].sockFD = 0;
//	activeRequests[nSockFd].entity = NULL;
//	activeRequests[nSockFd].usage = false;
	free (activeRequests[nSockFd].pData);
	return 0;
}


int  AddCon(int nSockFd, int Addr)
{
	if (nSockFd<=0)
		return -1; // Bad parameter
//	isNewCon = true;
	int i;
	for (i=0; i<MAX_NO_SOCKET_CONN; i++)
	{
		if(activeRequests[i].sockFD ==0)//entry is free
		{
			activeRequests[i].pData = (UINT8*)malloc(BUFFER_SIZE);
					if (NULL == activeRequests[i].pData)
					{
						printf(("Failed to allocate memory for 'pdcpReceiveBuffer',QUIT\n"));
						printf("PDCP module start failed!!! \n");
						exit(EXIT_FAILURE);
					}

			activeRequests[i].sockFD = nSockFd;
			strcpy(activeRequests[i].entity, "OAI");
			printf ("Connection established with OAI at socket %d\n\n", nSockFd);

			return i;
		}
	}
return -2;
}

int findCon(int nSockFd)
{
	int sockfound=0;
	if (nSockFd<=0)
		return -1; // Bad parameter

	int i;
	for (i=0; i<MAX_NO_SOCKET_CONN; i++)
	{
		if(activeRequests[i].sockFD ==nSockFd)//entry is there
		{
			return i;//if an empty buffer exists for this fd use it
		}

	}
//else make a new one;
return AddCon (nSockFd, sockfound);
}

//Message received from UP. Both Control message and scheduler message is handled here
bool sckClose = false;
EXT_MSG_T ExtRecMsg;
UINT32	sockExtHeaderSize = sizeof(ExtRecMsg.msgId) + sizeof (ExtRecMsg.msgSize);// implicitly calculating header size

extern fd_set fdgroup;
int connIndex, tempTotalCon;

VOID MsgReceive(INT32 connectedSockFd)
{
	INT32 retValue = -1;
	sckClose = false;
	// memorise the start address of the send buffer
	int schedID = findCon(connectedSockFd);
	connIndex = schedID;
	temppdcpReceiveBuffer = activeRequests[schedID].pData;
	memset(activeRequests[schedID].pData,0,BUFFER_SIZE);
	retValue = recv(connectedSockFd,temppdcpReceiveBuffer,sockExtHeaderSize,0); //LRM receives message on templrmReceiverBufer

	if (retValue == SYSCALLFAIL )
	{
		perror("recv");
		printf("recv() returned Error \n");
		retValue = 0;
		return;
	} 	else if (retValue == 0)
	{
		printf("Connection is closed on FD (%u)\n",(unsigned)connectedSockFd);
		close (connectedSockFd);
		FD_CLR(connectedSockFd, &fdgroup);
		delCon(schedID, 0);
	} else
	{

		 // if the Message has some data in the payload
		ExtRecMsg.msgId = ((EXT_MSG_T*)temppdcpReceiveBuffer)->msgId;
		ExtRecMsg.msgSize = ((EXT_MSG_T*)temppdcpReceiveBuffer)->msgSize;
		temppdcpReceiveBuffer += sockExtHeaderSize;


		 if (ExtRecMsg.msgSize)
		 {
			 retValue = recv(connectedSockFd,temppdcpReceiveBuffer, ExtRecMsg.msgSize, 0);
			 if (retValue == SYSCALLFAIL )
			 {
				 perror("recv2");
				 printf("recv() returned Error \n");
			 }
		 }

		 // call message handler here
		 MsgHandler(ExtRecMsg.msgId, connectedSockFd);
	}
}

static VOID MsgHandler(UINT32 messageId, INT32 sockFd)
{
	switch ( messageId )
	{
		case CLOUD_MANAGER_REGISTRATION:
		{
			/*All the resource seeking modules are registered with this function call
			*/
			CLOUD_MANAGER_REGISTRATION_T mng_reg;
			memcpy(&mng_reg,temppdcpReceiveBuffer, ExtRecMsg.msgSize);

			int i;
			mng_reg.reg_resp = -1;
			for (i= 0; i<MAX_NO_SOCKET_CONN; i++)
			{
				if (i == connIndex && activeRequests[i].module_id == 0)
				{
					activeRequests[connIndex].module_id = mng_reg.module_id;
					activeRequests[connIndex].qosIndex = mng_reg.qosIndex;
					mng_reg.reg_resp = 1;
					total_Numberof_Mudule++;
					reg_reply_send(mng_reg, sockFd);
					break;
				}
			}
		}
		break;

		case CLOUD_MANAGER_RESOURCE_HANDLE:
		{
			/*All the resource seeking modules are registered with this function call
			*/
			CLOUD_MANAGER_RESOURCE_HANDLE_T mng_cpu_alloc;
			memcpy(&mng_cpu_alloc,temppdcpReceiveBuffer, ExtRecMsg.msgSize);

			if (activeRequests[connIndex].module_id != mng_cpu_alloc.module_id)
			{
				perror("Database error");
				printf("Synchronization error with cloud manager database and existing running system \n");
				exit(EXIT_FAILURE);
			} else if (mng_cpu_alloc.res_querry_enable == 1)
			{
				activeRequests[connIndex].res_db.currentusage = mng_cpu_alloc.resource_req;
				if (total_Numberof_Mudule > 1)
				{
					brodcast_res_usg_report (connIndex);
					printf ("Current program is designed only for allocation of one microservice. In the system there is %d microservice."
							"Uanble to allocate CPU", total_Numberof_Mudule);
				} else if (total_Numberof_Mudule == 1)
				{
					mng_cpu_alloc.resource_rsp = allocate_cpu();
					mng_cpu_alloc.res_querry_enable = 3;
					MsgInsertFunc (CLOUD_MANAGER_RESOURCE_HANDLE, sizeof (CLOUD_MANAGER_RESOURCE_HANDLE_T), &mng_cpu_alloc, &temppdcpSendBuffer);
					MsgSend (sockFd);
				}

			} else if (mng_cpu_alloc.res_querry_enable == 3)
			{
				activeRequests[connIndex].res_db.currentusage = mng_cpu_alloc.resource_req;
				tempTotalCon --;
				if ((total_Numberof_Mudule == 1 && tempTotalCon == 0) || (total_Numberof_Mudule > 1 && tempTotalCon == 1))
				{

				}
			}


		}
		break;

		 default:
		 {
			 printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
			 printf("Unknown msg received from OAI\n\n\n\n");
			 printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
		 }
		 break;
	}
}

void reg_reply_send(CLOUD_MANAGER_REGISTRATION_T mng_reg, INT32 sockFd)
{
	MsgInsertFunc (CLOUD_MANAGER_REGISTRATION, sizeof (CLOUD_MANAGER_REGISTRATION_T), &mng_reg, &temppdcpSendBuffer);
	MsgSend (sockFd);
}

void brodcast_res_usg_report (int db_index)
{
	CLOUD_MANAGER_RESOURCE_HANDLE_T mng_cpu_alloc;
	int i;
	for (i= 0; i<MAX_NO_SOCKET_CONN; i++)
	{
		if (i != db_index && activeRequests[i].module_id != 0)
		{
			mng_cpu_alloc.module_id = activeRequests[i].module_id;
			mng_cpu_alloc.res_querry_enable = 2;
			MsgInsertFunc (CLOUD_MANAGER_RESOURCE_HANDLE, sizeof (CLOUD_MANAGER_RESOURCE_HANDLE_T), &mng_cpu_alloc, &temppdcpSendBuffer);
			MsgSend (activeRequests[i].sockFD);
		}
	}
	get_result();
}

extern INT32 fdmax;
extern int firstSockFD;
extern fd_set readFds, fdgroup;
void get_result()
{
	bool loop = true;
	struct timeval timeoutN;
	tempTotalCon = total_Numberof_Mudule;
	if (total_Numberof_Mudule > 1)
	{
		while(loop)
		{
			timeoutN.tv_sec  = 0;
			timeoutN.tv_usec = 250;
			readFds = fdgroup;
			INT32 n = select(fdmax+1,&readFds,NULL,NULL,&timeoutN);

			if(n < 0)
			  {
				  perror("select() failed");
				  exit(EXIT_FAILURE);
			  }

			int i_fd = 0;
			for (i_fd = firstSockFD; i_fd <= fdmax; i_fd++)
			{
				if (FD_ISSET(i_fd,&readFds))
					{
						MsgReceive(i_fd);

					}
			}

			if (tempTotalCon == 1)
			{
				loop = false;
			}
		}
	}
}

double allocate_cpu ()
{
	   double i;
	   bool false_in = true;

	   while (false_in)
	   {
		   printf( "Enter percent of CPU allocation :");
		   scanf("%lf", &i);
		   printf( "\nYou entered: %f \n", i);
		   if (i > 0 && i <= 100)
		   {
			   false_in = false;
		   }

	   }

	   double allocated_cpu = (double)((CPU_CAPACITY * i) / 100);

	   return allocated_cpu;
}
