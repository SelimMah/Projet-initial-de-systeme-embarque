/*
 * Nom: Progmem.h
 * Auteurs: Selim-Mahjoub-2193614, 
 *          Mohamed-Afandi-2291005, 
 *          Bryan Alexandre Tavares-2291297 
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Classe Progmem de la Librairie 
 */

#ifndef PROGMEM_H
#define PROGMEM_H

#define F_CPU 8000000

#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>
#include "string.h"
#include <stdlib.h>

#include "LED.h"
#include "Sing.h"
#include "Debug.h"
#include "can.h"
#include "memoire_24.h"
#include "Robot.h"

class Progmem
{
public:
    //Constructeurs--------------------------------------------------

    Progmem() {};
    
    //Methodes--------------------------------------------------

    void readInstructionOperand(uint8_t* instruction, uint8_t* operand);

    void waitRoutine(uint8_t operand);
    void ledOnRoutine(uint8_t operand);
    void ledOffRoutine();
    void singOnRoutine(uint8_t operand);
    void singOffRoutine();
    void MotorOffRoutine();
    void ForwardRoutine(uint8_t operand);
    void BackwardRoutine(uint8_t operand);
    void RightTurnRoutine();
    void LeftTurnRoutine();
    void BeginLoopRoutine(uint8_t operand);
    void EndLoopRoutine();
    void End();
    
    //Attribues--------------------------------------------------

    Memoire24CXXX memory;
    Robot robot;
    uint16_t progCounter = 0x00;
    bool isActive = false;
    uint16_t loopAdress;
    uint8_t loopCounter;
};

#endif