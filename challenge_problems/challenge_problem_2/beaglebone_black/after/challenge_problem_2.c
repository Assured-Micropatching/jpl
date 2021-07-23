/*
---------------------------------------------------------------------------------------------------------------------
reference: https://bootlin.com/pub/mirror/devmem2.c
Samuel Sarkisian | Mentor: Lini Mestar
JPL | jpl.nasa.gov
---------------------------------------------------------------------------------------------------------------------
*/
#define BEAGLEBONE_BLACK
#ifdef BEAGLEBONE_BLACK

	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <string.h>
	#include <errno.h>
	#include <termios.h>
	#include <sys/types.h>
	#include <sys/mman.h>
	#include <signal.h>
	#include <fcntl.h>
	#include <ctype.h>
	#include <time.h>
	  
	#define FATAL do { fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", \
	  __LINE__, __FILE__, errno, strerror(errno)); exit(1); } while(0)
	 
	#define MAP_SIZE 4096UL
	#define MAP_MASK (MAP_SIZE - 1)
	
	#define start_physicaladdress  0x402F0400
	#define end_physicaladdress  0x402FFFFF
	
	int main(int argc, char **argv) {
            time_t begin,end;
            time(&begin);
            double difference_time;
			time(&end);
            difference_time = difftime(end, begin);
            printf("Execution time for the whole program is = %f\n", difference_time);

		return 0;
	}
#endif

