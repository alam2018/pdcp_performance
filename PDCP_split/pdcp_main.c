/*
 * pdcp_main.c
 *
 *  Created on: Sep 21, 2017
 *      Author: idefix
 */

#define _GNU_SOURCE
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

#include "types.h"
#include "math.h"
#include "list.h"
#include "pdcp.h"
#include "log.h"
#include "pdcp_support.h"

//#include "collec_dec_pdcp.h"
#include "socket_msg.h"

conn_info connInfo[TOTAL_PDCP_INSTANCE];

//******************************************************************************
// Global Declarations
//******************************************************************************

INT32 gConnectSockFd;
INT32 gListenSockFd;
INT32 gNewConnectedListenSockFd;
INT32 sendFD;
fd_set fdgroup;
fd_set readFds;
// This defines the measurement time interval in sec and microsecs.
int measurem_intvall_s  = 0;
int measurem_intvall_us = 2;



// Socket and socket function related variables
struct sockaddr_in socketAddrPDCP;
struct timeval timeout;
//    struct timespec timeout;

INT32 fdmax;
INT32 reuseaddr = TRUE;
INT32 portno_PDCP;


// Message send , receive and handling related variables

INT8 *module;
BOOL loadMeasure = FALSE;
INT32 retValue;
UINT32 sizeOfMsg;
UINT32 responseBufferSize;


//******************************************************************************
// PDCP self test
//******************************************************************************

//#define SELF_TEST_ENABLE 1



//******************************************************************************
// PDCP variables
//******************************************************************************
/*
 * These are the PDCP entities that will be utilised
 * throughout the test
 *
 * For pdcp_data_req() and pdcp_data_ind() these
 * are passed and used
 */
pdcp_t pdcp_array[2];

/*
 * TX list is the one we use to receive PDUs created by pdcp_data_req() and
 * RX list is the one we use to pass these PDUs to pdcp_data_ind(). In test_pdcp_data_req()
 * method every PDU created by pdcp_data_req() are first validated and then added to RX
 * list after it's removed from TX list
 */
list_t test_pdu_tx_list;
list_t test_pdu_rx_list;


void conn_info_array_init ()
{
	int i = 0;
	for (i = 0; i<TOTAL_PDCP_INSTANCE; i++)
	{
		connInfo[i].socID = -99;
		connInfo[i].bearerID = -99;
		connInfo[i].pdcpInsID = -99;
	}
}


//Initialize PDCP data structure
BOOL init_pdcp_entity(pdcp_t *pdcp_entity)
{
  if (pdcp_entity == NULL)
    return FALSE;

  /*
   * Initialize sequence number state variables of relevant PDCP entity
   */
  pdcp_entity->next_pdcp_tx_sn = 0;
  pdcp_entity->next_pdcp_rx_sn = 0;
  pdcp_entity->tx_hfn = 0;
  pdcp_entity->rx_hfn = 0;
//  pdcp_entity->kUPenc[0] = 4;
  /* SN of the last PDCP SDU delivered to upper layers */
  pdcp_entity->last_submitted_pdcp_rx_sn = 4095;
  pdcp_entity->seq_num_size = 12;

  printf("PDCP entity is initialized: Next TX: %d, Next Rx: %d, TX HFN: %d, RX HFN: %d, " \
      "Last Submitted RX: %d, Sequence Number Size: %d\n", pdcp_entity->next_pdcp_tx_sn, \
      pdcp_entity->next_pdcp_rx_sn, pdcp_entity->tx_hfn, pdcp_entity->rx_hfn, \
      pdcp_entity->last_submitted_pdcp_rx_sn, pdcp_entity->seq_num_size);

  return TRUE;
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


//Set specific core to run PDCP
void SetCore(int  Core2Pin)
{
	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(Core2Pin, &set);
	if (sched_setaffinity(0, sizeof(cpu_set_t), &set) < 0)
		perror("Error in sched_setaffinity()");
}

//Terminate the program
void sigint_handler(int sig)
{
    char  c;

    signal(sig, SIG_IGN);
    printf("OUCH, did you hit Ctrl-C?\n"
           "Do you really want to quit? [y/n] ");
    c = getchar();
    if (c == 'y' || c == 'Y')
         exit(0);
    else
         signal(SIGINT, sigint_handler);
    getchar(); // Get new line character
}


int main (INT32 argc, INT8 **argv )
{
	bool chkFirstConn = true;
	int firstSockFD = 0;

	int cpu_core = atoi(argv[2]);
	SetCore(cpu_core);

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
	portno_PDCP = atoi(argv[1]);
	bzero((char *) &socketAddrPDCP, sizeof(socketAddrPDCP));
	socketAddrPDCP.sin_family = AF_INET;
	socketAddrPDCP.sin_addr.s_addr = INADDR_ANY;
	socketAddrPDCP.sin_port = htons(portno_PDCP);

	num = bind(gListenSockFd, (struct sockaddr *) &socketAddrPDCP, sizeof(socketAddrPDCP));
	if (num == SYSCALLFAIL )
	{
		perror("ERROR Binding PDCP'socket");
		close(gListenSockFd);
		printf("PDCP module start failed!!! \n");
		exit (EXIT_FAILURE);
	}

	num = listen(gListenSockFd,MAX_NO_CONN_TO_PDCP);
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


	printf("PDCP module started successfully! \n");
	fflush(stdout);  // Otherwise over ssh we do not see the SUCCESS message

	//Initialization
	  /*
	   * Initialize memory allocator, list_t for test PDUs, and log generator
	   */
#if defined create_report || defined create_uplink_report
prepare_file_for_report ();
#endif

#ifdef BUFFER_READ_DELAY_REPORT
	buffer_read_delay_report ();
#endif

	  conn_info_array_init ();
	  pool_buffer_init();
	  list_init(&test_pdu_tx_list, NULL);
	  list_init(&test_pdu_rx_list, NULL);
	  logInit();
	  pdcp_layer_init ();

	  if (init_pdcp_entity(&pdcp_array[0]) == TRUE && init_pdcp_entity(&pdcp_array[1]) == TRUE)
	    printf(" PDCP entity initialization OK\n");
	  else {
		  printf("[TEST] Cannot initialize PDCP entities!\n");
	    return 1;
	  }

	  /* Initialize PDCP state variables */
	  int index;
	  for (index = 0; index < 2; ++index) {
	    if (pdcp_init_seq_numbers(&pdcp_array[index]) == FALSE) {
	    	printf("[TEST] Cannot initialize sequence numbers of PDCP entity %d!\n", index);
	      exit(1);
	    } else {
	    	printf("[TEST] Sequence number state of PDCP entity %d is initialized\n", index);
	    }
	  }

	  signal(SIGINT, sigint_handler);

#if SELF_TEST_ENABLE
	  pdcp_array[0].rlc_mode = RLC_MODE_AM;
	  pdcp_array[1].rlc_mode = RLC_MODE_AM;
	  main_test();

	  /* Initialize PDCP state variables */
	  for (index = 0; index < 2; ++index) {
	    if (pdcp_init_seq_numbers(&pdcp_array[index]) == FALSE) {
	    	printf("[TEST] Cannot initialize sequence numbers of PDCP entity %d!\n", index);
	      exit(1);
	    } else {
	    	printf("[TEST] Sequence number state of PDCP entity %d is initialized\n", index);
	    }
	  }
#endif


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
