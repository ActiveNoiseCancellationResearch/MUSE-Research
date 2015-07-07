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
#include <stdio.h>
int wave_table[WAVESIZE]; 
int16_t cap_array[NUM_SAMPS_TO_CAPTURE];
int n=0;

int main()
{
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    int i;  
    uint8 my_string[16];
    int16_t the_val;
    int string_length;
    int length;
    for(i=0;i<WAVESIZE;++i)
    {
        wave_table[i]=(int)(sin(2.0*3.1416*i/WAVESIZE)*4095); 
    }
    isr_Start();
    VDAC8_1_hs_Start();
    ADC_SAR_Start();
    VDAC8_2_ls_Start();
    UART_1_Start();
    
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    while (n<NUM_SAMPS_TO_CAPTURE)
    {
        
    }
    for(i=0;i<NUM_SAMPS_TO_CAPTURE;++i)
        {
            the_val = cap_array[i];
            sprintf((char*) my_string ,"%d\n",the_val&0xFFFF);
            length = strlen((char*)my_string);
            UART_1_PutArray(my_string,length); 
        }
    while(1){}
}
/* [] END OF FILE */
