/*
 * report_write.c
 *
 *  Created on: Mar 20, 2018
 *      Author: idefix
 */


#include <stdio.h>
#include <errno.h>
#include <stdbool.h>

#define SEC_TO_NANO_SECONDS  1000000000

//extern struct timespec send_time, rec_time;
extern double total_time;

FILE *feeder_report;
bool file_present = false;
void report (void) {

	if (file_present == false)
	{
	    feeder_report = fopen ("feeder_report.csv","w+");
	    if (feeder_report == NULL) {
	        printf ("File not created okay, errno = %d\n", errno);
	    }

	    file_present = true;
	}

	fprintf (feeder_report,"Total time (us): %f\n", total_time/1000);

}
