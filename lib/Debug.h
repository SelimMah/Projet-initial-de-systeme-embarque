
/*
 * Nom: debug.h
 * Auteurs: Selim-Mahjoub-2193614, 
 *          Mohamed-Afandi-2291005, 
 *          Bryan Alexandre Tavares-2291297 
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Classe debug de la Librairie 
 */

#define F_CPU 8000000

#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>

#include "string.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "UART.h"

void initDebug();
void printMessage(const char* debugMessage);
void printINT(uint16_t value); 
void printINT(uint8_t value);
void uint16ToCharArray(uint16_t value, char *buffer, size_t bufferSize);
void printValue(uint16_t value);

#ifdef DEBUG
#define DEBUG_INIT() initDebug();
#define DEBUG_MESSAGE(debugMessage) printMessage(debugMessage);
#define DEBUG_INT(value) printINT(value);
#define DEBUG_VALUE(value) printValue(value); 

#else
#define DEBUG_INIT() {};
#define DEBUG_MESSAGE(debugMessage) {};
#define DEBUG_INT(value) {};
#define DEBUG_VALUE(value) {};  

#endif
