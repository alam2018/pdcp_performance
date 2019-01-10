/*
 * manager_main.c
 *
 *  Created on: Dec 4, 2018
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



//******************************************************************************
// Global Declarations
//******************************************************************************

INT32 gConnectSockFd;
INT32 gListenSockFd;
INT32 gNewConnectedListenSockFd;
INT32 sendFD;
fd_set fdgroup;
fd_set readFds;
int firstSockFD;
// This defines the measurement time interval in sec and microsecs.
int measurem_intvall_s  = 0;
int measurem_intvall_us = 2;



// Socket and socket function related variables
struct sockaddr_in socketAddrPDCP;
struct timeval timeout;
//    struct timespec timeout;

INT32 fdmax;
INT32 reuseaddr = TRUE;
INT32 portno_manager;


// Message send , receive and handling related variables

INT8 *module;
BOOL loadMeasure = FALSE;
INT32 retValue;
UINT32 sizeOfMsg;
UINT32 responseBufferSize;


/* Initialization of module database*/
extern _tSchedBuffer activeRequests[MAX_NO_SOCKET_CONN];
void init_module_database()
{
	total_Numberof_Mudule = 0;
	int i;
	for (i= 0; i<MAX_NO_SOCKET_CONN; i++)
	{
		activeRequests[i].isBufferUsed = false;
		activeRequests[i].module_id = 0;
		activeRequests[i].msgID = 0;
		activeRequests[i].msgSize = 0;
		activeRequests[i].qosIndex = 0;
		activeRequests[i].sockFD = 0;
	}
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

int main (INT32 argc, INT8 **argv )
{
	bool chkFirstConn = true;

//	int cpu_core = atoi(argv[2]);
//	SetCore(cpu_core);

	init_module_database();

	//--------------------------------------------------------------
	//create socket for accepting incoming communication
	//--------------------------------------------------------------
	//Create an AF_INET stream socket to receive incoming connections on

	gListenSockFd = socket(AF_INET, SOCK_STREAM, 0);
	if (gListenSockFd < 0)
	   {
		 perror("ERROR opening PDCP socket for OAI");
		 printf("PDCP module start failed!!! \n");
		 exit (EXIT_FAILURE);
	   }

	//Allow socket descriptor to be reusable

	int num = setsockopt(gListenSockFd, SOL_SOCKET,  SO_REUSEADDR, (char *)&reuseaddr, sizeof(reuseaddr));

	if (num < 0)
		{
		  perror("setsockopt() failed");
		  close(gListenSockFd);
		  printf("PDCP module start failed!!! \n");
		  exit(EXIT_FAILURE);
		}

	// Set socket to be non-blocking.  All of the sockets for the incoming connections will also be non-blocking since
	// they will inherit that state from the listening socket.

	sockSetNonBlocking(gListenSockFd);

	// Bind the socket
	portno_manager = atoi(argv[1]);
	bzero((char *) &socketAddrPDCP, sizeof(socketAddrPDCP));
	socketAddrPDCP.sin_family = AF_INET;
	socketAddrPDCP.sin_addr.s_addr = INADDR_ANY;
	socketAddrPDCP.sin_port = htons(portno_manager);

	num = bind(gListenSockFd, (struct sockaddr *) &socketAddrPDCP, sizeof(socketAddrPDCP));
	if (num == SYSCALLFAIL )
	{
		perror("ERROR Binding PDCP'socket");
		close(gListenSockFd);
		printf("PDCP module start failed!!! \n");
		exit (EXIT_FAILURE);
	}

	num = listen(gListenSockFd,MAX_NO_SOCKET_CONN);
	if(num == SYSCALLFAIL)
	 {
		 perror("ERROR on listening socket");
		 close(gListenSockFd);
		 printf("PDCP module start failed!!! \n");
		 exit (EXIT_FAILURE);
	 }



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

	//Initialize the master fd_set

	FD_ZERO(&fdgroup);
	FD_ZERO(&readFds);

	FD_SET(gListenSockFd,&fdgroup);
	FD_SET(gConnectSockFd,&fdgroup);

	fdmax = gListenSockFd;

	temppdcpSendBuffer = pdcpSendBuffer;

	// Set to zero.
	memset(pdcpSendBuffer,0,BUFFER_SIZE);


	printf("Cloud manager started successfully! \n");
	fflush(stdout);  // Otherwise over ssh we do not see the SUCCESS message

	while (TRUE)
	{
		int measurem_intvall_s  = 0;
		int measurem_intvall_us = 2;
		timeout.tv_sec  = measurem_intvall_s;
		timeout.tv_usec = measurem_intvall_us;
		readFds = fdgroup;
		INT32 n = select(fdmax+1,&readFds,NULL,NULL,&timeout);

		if(n < 0)
		  {
			  perror("select() failed");
			  exit(EXIT_FAILURE);
		  }

		// --------------------------------------------------------------
		// NEW TCP CONNECT REQUEST FROM UP, typically from FD=4
		// --------------------------------------------------------------

		 if (FD_ISSET(gListenSockFd,&readFds))
		 {
			 gNewConnectedListenSockFd = accept(gListenSockFd, NULL,NULL);
				 if(gNewConnectedListenSockFd < 0)
					 {
						 perror("ERROR accept");
						 exit(EXIT_FAILURE);
					 } else
					 {
						 if (chkFirstConn)
						 {
							 firstSockFD = gNewConnectedListenSockFd;
							 chkFirstConn = false;
						 }
						 printf ("New connection established at socket %d\n", gNewConnectedListenSockFd);
					 }

					fdmax = gNewConnectedListenSockFd;

					//Set the socket to nonblocking

					sockSetNonBlocking(gNewConnectedListenSockFd);

					FD_SET(gNewConnectedListenSockFd,&fdgroup);
		 }

		int i_fd = 0;
		for (i_fd = firstSockFD; i_fd <= fdmax; i_fd++)
		{
			if (FD_ISSET(i_fd,&readFds))
				{
					MsgReceive(i_fd);

				}
		}


	}

}

