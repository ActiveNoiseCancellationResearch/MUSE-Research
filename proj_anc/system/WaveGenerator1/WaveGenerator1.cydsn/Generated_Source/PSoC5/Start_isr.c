/*******************************************************************************
* File Name: Start_isr.c  
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
#include "Start_isr.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Start_isr__PORT == 15 && ((Start_isr__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Start_isr_Write
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
void Start_isr_Write(uint8 value) 
{
    uint8 staticBits = (Start_isr_DR & (uint8)(~Start_isr_MASK));
    Start_isr_DR = staticBits | ((uint8)(value << Start_isr_SHIFT) & Start_isr_MASK);
}


/*******************************************************************************
* Function Name: Start_isr_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Start_isr_DM_STRONG     Strong Drive 
*  Start_isr_DM_OD_HI      Open Drain, Drives High 
*  Start_isr_DM_OD_LO      Open Drain, Drives Low 
*  Start_isr_DM_RES_UP     Resistive Pull Up 
*  Start_isr_DM_RES_DWN    Resistive Pull Down 
*  Start_isr_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Start_isr_DM_DIG_HIZ    High Impedance Digital 
*  Start_isr_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Start_isr_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Start_isr_0, mode);
}


/*******************************************************************************
* Function Name: Start_isr_Read
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
*  Macro Start_isr_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Start_isr_Read(void) 
{
    return (Start_isr_PS & Start_isr_MASK) >> Start_isr_SHIFT;
}


/*******************************************************************************
* Function Name: Start_isr_ReadDataReg
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
uint8 Start_isr_ReadDataReg(void) 
{
    return (Start_isr_DR & Start_isr_MASK) >> Start_isr_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Start_isr_INTSTAT) 

    /*******************************************************************************
    * Function Name: Start_isr_ClearInterrupt
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
    uint8 Start_isr_ClearInterrupt(void) 
    {
        return (Start_isr_INTSTAT & Start_isr_MASK) >> Start_isr_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
