/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <math.h>
#include <project.h>
#include "ANC.h"
int wave_table[WAVESIZE]; 
//int16_t cap_array[NUM_SAMPS_TO_CAPTURE];

int main()
{
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    int i;  
    for(i=0;i<WAVESIZE;++i)
    {
        wave_table[i]=(int)(sin(2.0*3.1416*i/WAVESIZE)*4095); 
    }
    isr_Start();
    VDAC8_1_hs_Start();
    ADC_SAR_Start();
    VDAC8_2_ls_Start();
    
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */

    
}

/* [] END OF FILE */
