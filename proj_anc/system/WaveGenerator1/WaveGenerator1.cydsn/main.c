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
#include <project.h>

int main()
{

    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    isr_Start();
    VDAC8_Start();
    ADC_SAR_Start();
    VDAC8_1_Start();
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        
    }
}

/* [] END OF FILE */
