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

int main()
{

    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    int i;    
    isr_Start();
    VDAC8_1_hs_Start();
    ADC_SAR_Start();
    VDAC8_2_ls_Start();
    
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */

    for(i=0;i<WAVESIZE;++i)
    {
        wave_table[i]=(int)(sin(2.0*3.1416*i/20.0)*4096.0); 
    }
}

/* [] END OF FILE */
