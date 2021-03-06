/*******************************************************************************
* File Name: isr.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <isr.h>

#if !defined(isr__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START isr_intc` */
#include <project.h>
#include "canceller.h"
#include "ANC.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Uncomment one of the following 3 modes:
//
// This mode puts full-scale sine waves out on both DACSs, to HS and LS outputs
//#define MODE_CALIBRATE
//
// Normal operation of the active noise canceller (with sine-wave undesired signal)
#define MODE_CANCELLER
//
// This mode puts out random data onto LS output, captures MIC input, and sends to host via serial port
//#define MODE_CHARACTERIZE

#ifdef MODE_CHARACTERIZE
uint8 cap_array[NUM_SAMPS_TO_CAPTURE];
extern int n;
#endif

#ifndef MODE_CHARACTERIZE
extern int wave_table[WAVESIZE];
#endif

/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE      16
#endif /* CYINT_IRQ_BASE */
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif /* CYINT_VECT_TABLE */

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: isr_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it. This function disables the interrupt, 
*  sets the default interrupt vector, sets the priority from the value in the
*  Design Wide Resources Interrupt Editor, then enables the interrupt to the 
*  interrupt controller.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void isr_Start(void)
{
    /* For all we know the interrupt is active. */
    isr_Disable();

    /* Set the ISR to point to the isr Interrupt. */
    isr_SetVector(&isr_Interrupt);

    /* Set the priority. */
    isr_SetPriority((uint8)isr_INTC_PRIOR_NUMBER);

    /* Enable it. */
    isr_Enable();
}


/*******************************************************************************
* Function Name: isr_StartEx
********************************************************************************
*
* Summary:
*  Sets up the interrupt and enables it. This function disables the interrupt,
*  sets the interrupt vector based on the address passed in, sets the priority 
*  from the value in the Design Wide Resources Interrupt Editor, then enables 
*  the interrupt to the interrupt controller.
*  
*  When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*  used to provide consistent definition across compilers:
*  
*  Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*   Function prototype example:
*   CY_ISR_PROTO(MyISR);
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void isr_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    isr_Disable();

    /* Set the ISR to point to the isr Interrupt. */
    isr_SetVector(address);

    /* Set the priority. */
    isr_SetPriority((uint8)isr_INTC_PRIOR_NUMBER);

    /* Enable it. */
    isr_Enable();
}


/*******************************************************************************
* Function Name: isr_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void isr_Stop(void)
{
    /* Disable this interrupt. */
    isr_Disable();

    /* Set the ISR to point to the passive one. */
    isr_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: isr_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for isr.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(isr_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START isr_Interrupt` */
    
#define DC_EST_NUM_SAMPS_LOG2   (12)
#define DC_EST_NUM_SAMPS        (1 << DC_EST_NUM_SAMPS_LOG2)
    
                           // Discrete time index

    int x=0;
    static int dc_count = 0;
    static int dc_sum = 0;
    
#ifndef MODE_CHARACTERIZE    
    static int wave_idx=0;
#endif

#ifdef MODE_CANCELLER
    int e_;
    int y;
#endif

//    Start_isr_Write(1);
//    Start_isr_Write(0);

#ifndef MODE_CHARACTERIZE
     x = wave_table[wave_idx];

    if (dc_count == DC_EST_NUM_SAMPS)
    {
        // Convert sine wave from Q20.12 to 8-bit offset binary
        VDAC8_2_ls_SetValue((x>>5)+128);
    }

    // Advance to next sample in wave  table
    ++wave_idx;
    if (wave_idx == WAVESIZE) wave_idx=0;
#else
    x = rand();   

    VDAC8_2_ls_SetValue(x & 0xFF);
#endif

#ifdef MODE_CANCELLER       
    //canceller code goes here
    // e_ is 12-bit offset binary, range 0 to 4095
    e_ =  ADC_SAR_GetResult16();          //Set's value to the ADC output (16bit 2's comp value)
        
    y = (canceller_new_sample(x) + (1<<4)) >> 5;   // Get signed value, 7 fractional bits (8 bits total)
    if (y > 127)  y =  127;
    if (y < -128) y = -128;
    
    // Convert value to offset binary
    if (dc_count == DC_EST_NUM_SAMPS)
    {
        VDAC8_1_hs_SetValue(y + 128);              
    }
    else
    {
        dc_sum += e_;
        
        ++dc_count;
        
        if (dc_count == DC_EST_NUM_SAMPS)
        {
            // Normalize to use as DC estimate
            dc_sum = (dc_sum + (1 << (DC_EST_NUM_SAMPS_LOG2-1)))>>DC_EST_NUM_SAMPS_LOG2;
        }
    }

    canceller_coeff_update(e_ - dc_sum);
    //end canceller code  
#else
#ifdef MODE_CALIBRATE
    VDAC8_1_hs_SetValue((x>>5)+128);
#endif
#endif

#ifdef MODE_CHARACTERIZE
    if (n < NUM_SAMPS_TO_CAPTURE)
    {
        cap_array[n] = e_>>4;
        ++n;
    }
    else if (n == NUM_SAMPS_TO_CAPTURE)
    {
        int the_val;
        char my_string[32];
        int length;
        int i;
        
        for(i=0;i<NUM_SAMPS_TO_CAPTURE;++i)
        {
            the_val = cap_array[i];
            sprintf(my_string ,"%d\n", the_val & 0xFFFF);
            length = strlen(my_string);
            UART_1_PutArray( (uint8 *) my_string, length); 
        }
        ++n;
    }
#endif
//    End_isr_Write(1);
//    End_isr_Write(0);
}        

    /* `#END` */



/*******************************************************************************
* Function Name: isr_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling isr_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use isr_StartEx instead.
* 
*   When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*   used to provide consistent definition across compilers:
*
*   Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*
*   Function prototype example:
*     CY_ISR_PROTO(MyISR);
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void isr_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)isr__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: isr_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress isr_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)isr__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: isr_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. 
*
*   Note calling isr_Start or isr_StartEx will 
*   override any effect this API would have had. This API should only be called
*   after isr_Start or isr_StartEx has been called. 
*   To set the initial priority for the component, use the Design-Wide Resources
*   Interrupt Editor.
*
*   Note This API has no effect on Non-maskable interrupt NMI).
*
* Parameters:
*   priority: Priority of the interrupt, 0 being the highest priority
*             PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*             PSoC 4: Priority is from 0 to 3.
*
* Return:
*   None
*
*******************************************************************************/
void isr_SetPriority(uint8 priority)
{
    *isr_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: isr_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt, 0 being the highest priority
*    PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*    PSoC 4: Priority is from 0 to 3.
*
*******************************************************************************/
uint8 isr_GetPriority(void)
{
    uint8 priority;


    priority = *isr_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: isr_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt to the interrupt controller. Do not call this function
*   unless ISR_Start() has been called or the functionality of the ISR_Start() 
*   function, which sets the vector and the priority, has been called.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void isr_Enable(void)
{
    /* Enable the general interrupt. */
    *isr_INTC_SET_EN = isr__INTC_MASK;
}


/*******************************************************************************
* Function Name: isr_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 isr_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*isr_INTC_SET_EN & (uint32)isr__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: isr_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt in the interrupt controller.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void isr_Disable(void)
{
    /* Disable the general interrupt. */
    *isr_INTC_CLR_EN = isr__INTC_MASK;
}


/*******************************************************************************
* Function Name: isr_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
* Side Effects:
*   If interrupts are enabled and the interrupt is set up properly, the ISR is
*   entered (depending on the priority of this interrupt and other pending 
*   interrupts).
*
*******************************************************************************/
void isr_SetPending(void)
{
    *isr_INTC_SET_PD = isr__INTC_MASK;
}


/*******************************************************************************
* Function Name: isr_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt in the interrupt controller.
*
*   Note Some interrupt sources are clear-on-read and require the block 
*   interrupt/status register to be read/cleared with the appropriate block API 
*   (GPIO, UART, and so on). Otherwise the ISR will continue to remain in 
*   pending state even though the interrupt itself is cleared using this API.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void isr_ClearPending(void)
{
    *isr_INTC_CLR_PD = isr__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
