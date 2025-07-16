#ifndef _VCC_MAIN_H
#define _VCC_MAIN_H

// Define which chip will be used
#define STM32F401xC

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"

// GPIOB pins
#define BUTTON_PIN  (6)

// GPIOA pins
#define SEGMENT_A   (6)
#define SEGMENT_B   (5)
#define SEGMENT_C   (3)
#define SEGMENT_D   (2)
#define SEGMENT_E   (1)
#define SEGMENT_F   (7)
#define SEGMENT_G   (8)
#define SEGMENT_DP  (4)

#endif
