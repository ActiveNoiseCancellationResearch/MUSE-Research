/*******************************************************************************
* File Name: End_isr.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "End_isr.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 End_isr__PORT == 15 && ((End_isr__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: End_isr_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void End_isr_Write(uint8 value) 
{
    uint8 staticBits = (End_isr_DR & (uint8)(~End_isr_MASK));
    End_isr_DR = staticBits | ((uint8)(value << End_isr_SHIFT) & End_isr_MASK);
}


/*******************************************************************************
* Function Name: End_isr_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  End_isr_DM_STRONG     Strong Drive 
*  End_isr_DM_OD_HI      Open Drain, Drives High 
*  End_isr_DM_OD_LO      Open Drain, Drives Low 
*  End_isr_DM_RES_UP     Resistive Pull Up 
*  End_isr_DM_RES_DWN    Resistive Pull Down 
*  End_isr_DM_RES_UPDWN  Resistive Pull Up/Down 
*  End_isr_DM_DIG_HIZ    High Impedance Digital 
*  End_isr_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void End_isr_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(End_isr_0, mode);
}


/*******************************************************************************
* Function Name: End_isr_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro End_isr_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 End_isr_Read(void) 
{
    return (End_isr_PS & End_isr_MASK) >> End_isr_SHIFT;
}


/*******************************************************************************
* Function Name: End_isr_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 End_isr_ReadDataReg(void) 
{
    return (End_isr_DR & End_isr_MASK) >> End_isr_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(End_isr_INTSTAT) 

    /*******************************************************************************
    * Function Name: End_isr_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 End_isr_ClearInterrupt(void) 
    {
        return (End_isr_INTSTAT & End_isr_MASK) >> End_isr_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
