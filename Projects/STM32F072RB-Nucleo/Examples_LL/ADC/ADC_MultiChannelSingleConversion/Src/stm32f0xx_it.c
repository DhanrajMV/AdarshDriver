/** 
  ******************************************************************************
  * @file    Examples_LL/ADC/ADC_MultiChannelSingleConversion/Src/stm32f0xx_it.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"

/** @addtogroup STM32F0xx_LL_Examples
  * @{
  */

/** @addtogroup ADC_MultiChannelSingleConversion
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}


/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}


/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles external line 4_15 interrupt request.
  * @param  None
  * @retval None
  */
void USER_BUTTON_IRQHANDLER(void)
{
  /* Manage Flags */
  if(LL_EXTI_IsActiveFlag_0_31(USER_BUTTON_EXTI_LINE) != RESET)
  {
    /* Call interruption treatment function */
    UserButton_Callback();
    
    /* Clear EXTI line flag */
    /* Note: Clear flag after callback function to minimize user button       */
    /*       switch debounce parasitics.                                      */
    LL_EXTI_ClearFlag_0_31(USER_BUTTON_EXTI_LINE);
  }
}

/**
  * @brief  This function handles ADC1 interrupt request.
  * @param  None
  * @retval None
  */
void ADC1_COMP_IRQHandler(void)
{
  /* Check whether ADC group regular end of sequence conversions caused       */
  /* the ADC interruption.                                                    */
  if(LL_ADC_IsActiveFlag_EOS(ADC1) != 0)
  {
    /* Clear flag ADC group regular end of sequence conversions */
    LL_ADC_ClearFlag_EOS(ADC1);
    
    /* Call interruption treatment function */
    AdcGrpRegularSequenceConvComplete_Callback();
  }
  
  /* Check whether ADC group regular overrun caused the ADC interruption */
  if(LL_ADC_IsActiveFlag_OVR(ADC1) != 0)
  {
    /* Clear flag ADC group regular overrun */
    LL_ADC_ClearFlag_OVR(ADC1);
    
    /* Call interruption treatment function */
    AdcGrpRegularOverrunError_Callback();
  }
}

/**
  * @brief  This function handles DMA1 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel1_IRQHandler(void)
{
  /* Check whether DMA transfer complete caused the DMA interruption */
  if(LL_DMA_IsActiveFlag_TC1(DMA1) == 1)
  {
    /* Clear DMA transfer complete flag */
    LL_DMA_ClearFlag_TC1(DMA1);
    
    /* Call interruption treatment function */
    AdcDmaTransferComplete_Callback();
  }
  
  /* Check whether DMA transfer error caused the DMA interruption */
  if(LL_DMA_IsActiveFlag_TE1(DMA1) == 1)
  {
    /* Clear flag DMA transfer error */
    LL_DMA_ClearFlag_TE1(DMA1);
    
    /* Call interruption treatment function */
    AdcDmaTransferError_Callback();
  }
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
