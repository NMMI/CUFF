/*******************************************************************************
* File Name: MOTOR_1A.c  
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
#include "MOTOR_1A.h"


/*******************************************************************************
* Function Name: MOTOR_1A_Write
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
void MOTOR_1A_Write(uint8 value) 
{
    uint8 staticBits = (MOTOR_1A_DR & (uint8)(~MOTOR_1A_MASK));
    MOTOR_1A_DR = staticBits | ((uint8)(value << MOTOR_1A_SHIFT) & MOTOR_1A_MASK);
}


/*******************************************************************************
* Function Name: MOTOR_1A_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  MOTOR_1A_DM_STRONG     Strong Drive 
*  MOTOR_1A_DM_OD_HI      Open Drain, Drives High 
*  MOTOR_1A_DM_OD_LO      Open Drain, Drives Low 
*  MOTOR_1A_DM_RES_UP     Resistive Pull Up 
*  MOTOR_1A_DM_RES_DWN    Resistive Pull Down 
*  MOTOR_1A_DM_RES_UPDWN  Resistive Pull Up/Down 
*  MOTOR_1A_DM_DIG_HIZ    High Impedance Digital 
*  MOTOR_1A_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void MOTOR_1A_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(MOTOR_1A_0, mode);
}


/*******************************************************************************
* Function Name: MOTOR_1A_Read
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
*  Macro MOTOR_1A_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 MOTOR_1A_Read(void) 
{
    return (MOTOR_1A_PS & MOTOR_1A_MASK) >> MOTOR_1A_SHIFT;
}


/*******************************************************************************
* Function Name: MOTOR_1A_ReadDataReg
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
uint8 MOTOR_1A_ReadDataReg(void) 
{
    return (MOTOR_1A_DR & MOTOR_1A_MASK) >> MOTOR_1A_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(MOTOR_1A_INTSTAT) 

    /*******************************************************************************
    * Function Name: MOTOR_1A_ClearInterrupt
    ********************************************************************************
    *
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
    uint8 MOTOR_1A_ClearInterrupt(void) 
    {
        return (MOTOR_1A_INTSTAT & MOTOR_1A_MASK) >> MOTOR_1A_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
