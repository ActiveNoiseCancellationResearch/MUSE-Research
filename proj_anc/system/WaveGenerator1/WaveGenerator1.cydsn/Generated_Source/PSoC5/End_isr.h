/*******************************************************************************
* File Name: End_isr.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_End_isr_H) /* Pins End_isr_H */
#define CY_PINS_End_isr_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "End_isr_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 End_isr__PORT == 15 && ((End_isr__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    End_isr_Write(uint8 value) ;
void    End_isr_SetDriveMode(uint8 mode) ;
uint8   End_isr_ReadDataReg(void) ;
uint8   End_isr_Read(void) ;
uint8   End_isr_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define End_isr_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define End_isr_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define End_isr_DM_RES_UP          PIN_DM_RES_UP
#define End_isr_DM_RES_DWN         PIN_DM_RES_DWN
#define End_isr_DM_OD_LO           PIN_DM_OD_LO
#define End_isr_DM_OD_HI           PIN_DM_OD_HI
#define End_isr_DM_STRONG          PIN_DM_STRONG
#define End_isr_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define End_isr_MASK               End_isr__MASK
#define End_isr_SHIFT              End_isr__SHIFT
#define End_isr_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define End_isr_PS                     (* (reg8 *) End_isr__PS)
/* Data Register */
#define End_isr_DR                     (* (reg8 *) End_isr__DR)
/* Port Number */
#define End_isr_PRT_NUM                (* (reg8 *) End_isr__PRT) 
/* Connect to Analog Globals */                                                  
#define End_isr_AG                     (* (reg8 *) End_isr__AG)                       
/* Analog MUX bux enable */
#define End_isr_AMUX                   (* (reg8 *) End_isr__AMUX) 
/* Bidirectional Enable */                                                        
#define End_isr_BIE                    (* (reg8 *) End_isr__BIE)
/* Bit-mask for Aliased Register Access */
#define End_isr_BIT_MASK               (* (reg8 *) End_isr__BIT_MASK)
/* Bypass Enable */
#define End_isr_BYP                    (* (reg8 *) End_isr__BYP)
/* Port wide control signals */                                                   
#define End_isr_CTL                    (* (reg8 *) End_isr__CTL)
/* Drive Modes */
#define End_isr_DM0                    (* (reg8 *) End_isr__DM0) 
#define End_isr_DM1                    (* (reg8 *) End_isr__DM1)
#define End_isr_DM2                    (* (reg8 *) End_isr__DM2) 
/* Input Buffer Disable Override */
#define End_isr_INP_DIS                (* (reg8 *) End_isr__INP_DIS)
/* LCD Common or Segment Drive */
#define End_isr_LCD_COM_SEG            (* (reg8 *) End_isr__LCD_COM_SEG)
/* Enable Segment LCD */
#define End_isr_LCD_EN                 (* (reg8 *) End_isr__LCD_EN)
/* Slew Rate Control */
#define End_isr_SLW                    (* (reg8 *) End_isr__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define End_isr_PRTDSI__CAPS_SEL       (* (reg8 *) End_isr__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define End_isr_PRTDSI__DBL_SYNC_IN    (* (reg8 *) End_isr__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define End_isr_PRTDSI__OE_SEL0        (* (reg8 *) End_isr__PRTDSI__OE_SEL0) 
#define End_isr_PRTDSI__OE_SEL1        (* (reg8 *) End_isr__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define End_isr_PRTDSI__OUT_SEL0       (* (reg8 *) End_isr__PRTDSI__OUT_SEL0) 
#define End_isr_PRTDSI__OUT_SEL1       (* (reg8 *) End_isr__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define End_isr_PRTDSI__SYNC_OUT       (* (reg8 *) End_isr__PRTDSI__SYNC_OUT) 


#if defined(End_isr__INTSTAT)  /* Interrupt Registers */

    #define End_isr_INTSTAT                (* (reg8 *) End_isr__INTSTAT)
    #define End_isr_SNAP                   (* (reg8 *) End_isr__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_End_isr_H */


/* [] END OF FILE */
