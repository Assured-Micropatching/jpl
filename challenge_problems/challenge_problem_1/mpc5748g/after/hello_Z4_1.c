/*****************************************************************************/
/* FILE NAME: hello_Z4_1.c	           COPYRIGHT (c) NXP Semiconductors 2016 */

/*                                                      All Rights Reserved  */
/* PLATFORM: DEVKIT-MPG5748G												 */
/* DESCRIPTION: Main C program for core 0 (e200z4a)                          */
/*				Turns on the the DS4, DS6 and DS8 LEDs. Also outputs FIRC  	 */
/* 				clock scaled to FIRC/10 on port pin PG7 (J3_16)				 */
/*				Core 0 : Turns on DS4										 */
/*				NASA JPL: change the physical address from before to after               */
														 
/*                                                                           */
/*****************************************************************************/
/* REV      AUTHOR      								  DATE        					DESCRIPTION OF CHANGE                   */
/* ---   -----------   									 ----------    					---------------------                   */
/* 1.0	  SM            								29 Jul 2013  					Initial Version                         */
/* 1.1    SM            								12 Feb 2015  					Removed unrequired SIUL ME_PCTL code    */
/* 1.2	  K Shah										23 Feb 2016  					Ported to S32DS	                    	*/
/*   	  Samuel Sarkisian & Mentor: Lini Mestar		13 June 2021  					  						                */

/*****************************************************************************/
#define MPC5748G
#ifdef MPC5748G


#include "derivative.h" /* include peripheral declarations */
#include "project.h"
#include "platform_inits.h" /* Platform Configurations */
#include "clk.h"

#define KEY_VALUE1 0x5AF0ul
#define KEY_VALUE2 0xA50Ful

#define physical_address 0x40001FFF

#define delay_time 500000


extern void xcptn_xmpl(void);

void hw_init(void)
{
#if defined(DEBUG_SECONDARY_CORES)
	uint32_t mctl = MC_ME.MCTL.R;
#if defined(TURN_ON_CPU1)
	/* enable core 1 in all modes */
	MC_ME.CCTL[2].R = 0x00FE;
	/* Set Start address for core 1: Will reset and start */
	MC_ME.CADDR[2].R = 0x11d0000 | 0x1;
#endif
#if defined(TURN_ON_CPU2)
	/* enable core 2 in all modes */
	MC_ME.CCTL[3].R = 0x00FE;
	/* Set Start address for core 2: Will reset and start */
	MC_ME.CADDR[3].R = 0x13a0000 | 0x1;
#endif
	MC_ME.MCTL.R = (mctl & 0xffff0000ul) | KEY_VALUE1;
	MC_ME.MCTL.R =  mctl; /* key value 2 always from MCTL */
#endif /* defined(DEBUG_SECONDARY_CORES) */
}

__attribute__ ((section(".text")))


int main(void)
{

	unsigned long read_result, writeval;
	unsigned target;
	/* Configure and Enable Interrupts */
	xcptn_xmpl ();
	/* Configure wait states, flash master access, etc. */
	memory_config_16mhz();
	/* Pad PA10 (10): OBE=1. On EVB active low DS4 LED */
	SIUL2.MSCR[PA10].B.OBE = 1;
	/* Pad PG7 = CLOCKOUT = FIRC / 10 */
	clock_out_FIRC();

	target = physical_address;
	 writeval = target;
	 *((unsigned long *) target) = writeval;
	 read_result = *((unsigned long *) target);

	 if(read_result != writeval){
	    SIUL2.MSCR[PA7].B.OBE = 1;
	    //while loop for delay
	    int i = 0;
	    while(i <= delay_time){
	    	i++;
	    }
	 }

	 else{
	    SIUL2.MSCR[PA7].B.OBE = 0;
	 }


	//Turn DS4 LED OFF by deactivating it as soon as the process is done
	SIUL2.MSCR[PA10].B.OBE = 0;

	return 0;

}
#endif
