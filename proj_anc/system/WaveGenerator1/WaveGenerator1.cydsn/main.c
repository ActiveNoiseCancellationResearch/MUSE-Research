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
#include <stdio.h>
#include "ANC.h"
#include "hs_model.h"
#include "hs_model_coeffs.h"
#include "canceller.h"

int wave_table[WAVESIZE];       // Q20.12 format (signed two's complement, 12 fractional bits)s
int n=0;

int main()
{
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    int i;  
//    uint8 my_string[16];
//    int16_t the_val;
//    int string_length;
//    int length;
    for(i=0;i<WAVESIZE;++i)
    {
        wave_table[i]=(int)(sin(2.0*3.1416*i/WAVESIZE)*4095); 
    }
    
    // The hs_model_coeffs array must be defined in hs_model_coeffs.h !!!
    hs_model_new( hs_model_coeffs );
    canceller_new();
    
    VDAC8_1_hs_Start();
    ADC_SAR_Start();
    VDAC8_2_ls_Start();
    UART_1_Start();
    isr_Start();
    
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    while (n<NUM_SAMPS_TO_CAPTURE)
    {
        
    }
    
    while(1){}
}
/* [] END OF FILE */