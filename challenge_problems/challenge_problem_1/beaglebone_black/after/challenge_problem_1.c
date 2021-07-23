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
	  
	#define FATAL do { fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", \
	  __LINE__, __FILE__, errno, strerror(errno)); exit(1); } while(0)
	 
	#define MAP_SIZE 4096UL
	#define MAP_MASK (MAP_SIZE - 1)
	
	#define physical_address 0x402FFFFF

	int main(int argc, char **argv) {

		    int fd;
		    void *map_base, *virt_addr; 
			unsigned long read_result, writeval;
			off_t target;
		
			target = physical_address;
		
			if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
				
			map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);
			if(map_base == (void *) -1) FATAL;
		
			virt_addr = map_base + (target & MAP_MASK);
		
			writeval = target;
			*((unsigned long *) virt_addr) = writeval;
			read_result = *((unsigned long *) virt_addr);
				
			if(read_result != writeval){
				printf("read physical addres 0x%X; write physical address 0x%X \n", read_result, writeval);
			}
			if(munmap(map_base, MAP_SIZE) == -1) FATAL;
				close(fd);	
			
		
	
		return 0;
	}
#endif

