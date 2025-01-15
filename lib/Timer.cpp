/*
 * Nom: Timer.cpp
 * Auteurs: Selim-Mahjoub-2193614, 
 *          Mohamed-Afandi-2291005, 
 *          Bryan Alexandre Tavares-2291297,
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Implémentation de la classe Timer de la Librairie 
 */

#include "Timer.h"

// Constructeur de la classe Timer
// Paramètres :
//   timerNumber : numéro du timer (TimerNumber)
//   clockDiv : diviseur de l'horloge (uint16_t)
Timer::Timer(TimerNumber timerNumber, uint16_t clockDiv) :
    timerNumber_(timerNumber),
    timerStarted_(false),
    interruptEnabled_(false),
    clockDivisor_(clockDiv),
    clockFrequency_(F_CPU / clockDiv)
{
    switch (timerNumber) 
    {
        case TimerNumber::Timer_0:
            TCCRxA = &TCCR0A;
            TCCRxB = &TCCR0B;
            TCNTx = &TCNT0;
            OCRxA = &OCR0A;
            TIMSKx = &TIMSK0;
            break;

        case TimerNumber::Timer_1:
            TCCRxA = &TCCR1A;
            TCCRxB = &TCCR1B;
            TIMSKx = &TIMSK1;
            break;

        case TimerNumber::Timer_2:
            TCCRxA = &TCCR2A;
            TCCRxB = &TCCR2B;
            TCNTx = &TCNT2;
            OCRxA = &OCR2A;
            TIMSKx = &TIMSK2;
            break;

        default:
            break;
    }
    setClockDivisor(clockDiv);
}

// Démarre le timer avec une durée spécifiée
// Paramètres :
//   duration : durée du timer en nombre de cycles (uint32_t)
void Timer::startTimer(uint32_t durationMS) 
{
    setClockDivisor(clockDivisor_) ;
    *TCCRxA |= (1 << COM1A1) | (1 << COM1A0); // OCxA mis sur "compare match", output = high level Essai de l'annuler quand tu compte 

    unsigned long int duration = (clockFrequency_ * durationMS) / 1000;
    if (timerNumber_ == TimerNumber::Timer_1) 
    {
        TCCR1C = 0; // Pas de force output compare
        TCNT1 = 0; // Initialiser le compteur à 0 pour Timer 1  
        OCR1A = duration; // Définir la valeur de comparaison pour Timer 1
    } 
    else 
    {
        *TCNTx = 0; // Initialiser le compteur à 0 pour les autres compteurs de timer
        *OCRxA = duration; // Définir la valeur de comparaison pour les autres compteurs de timer
    }

    // Activer l'interruption pour compare A
    timerStarted_ = true;
}

void Timer::startChronos() 
{
    setClockDivisor(clockDivisor_) ;
    *TCCRxA &= ~(1 << COM1A1) & ~(1 << COM1A0); // OCxA mis sur "compare match", output = high level Essai de l'annuler quand tu compte 

    if (timerNumber_ == TimerNumber::Timer_1) 
    {
        TCCR1C = 0; // Pas de force output compare
        TCNT1 = 0; // Initialiser le compteur à 0 pour Timer 1  
    } 
    else 
    {
        *TCNTx = 0; // Initialiser le compteur à 0 pour les autres compteurs de timer
    }

    // Activer l'interruption pour compare A
    timerStarted_ = true;
}

// Arrête le timer en cours
void Timer::stopTimer() 
{
    *TCCRxB &= ~((1 << CS10) | (1 << CS11) | (1 << CS12)); // No clock source, timer/counter stopped 
    *TCCRxA &= ~((1 << COM1A1) | (1 << COM1A0)); // Normal port operation, OCxA disconnected
    
    if (timerNumber_ == TimerNumber::Timer_1) 
    {
        OCR1A = 0;
        TCNT1 = 0;
        TCCR1C = 0;

    } 
    else 
    {
        *TCNTx = 0;
        *OCRxA = 0;  
    }
    
    *TIMSKx |= (1 << OCIE1A);
    timerStarted_ = false;
}

// Active ou désactive l'interruption pour le compare A
// Paramètres :
//   enable : true pour activer l'interruption, false pour la désactiver (bool)
void Timer::enableInterrupt(bool enable) 
{
    interruptEnabled_ = enable;
    if (enable) 
    {
        *TIMSKx |= (1 << OCIE0A); // Activer l'interruption pour compare A
    } 
    else 
    {
        *TIMSKx &= ~(1 << OCIE0A); // Désactiver l'interruption pour compare A
    }
}

// Configure le diviseur de l'horloge pour le timer
// Paramètres :
//   divisor : diviseur de l'horloge (uint16_t)
void Timer::setClockDivisor(uint16_t divisor) 
{
    switch (divisor) 
    {
        case 1:
            *TCCRxB |= (1 << CS10); // Division d'horloge par 1
            *TCCRxB &= ~((1 << CS11) | (1 << CS12));
            break;

        case 8:
            *TCCRxB |= (1 << CS11); // Division d'horloge par 8
            *TCCRxB &= ~((1 << CS10) | (1 << CS12));
            break;

        case 64:
            *TCCRxB |= (1 << CS10) | (1 << CS11); // Division d'horloge par 64
            *TCCRxB &= ~(1 << CS12);
            break;

        case 256:
            *TCCRxB |= (1 << CS12); // Division d'horloge par 256
            *TCCRxB &= ~((1 << CS10) | (1 << CS11));
            break;

        default: // Par défaut, la division d'horloge est de 1024
            *TCCRxB |= (1 << CS10) | (1 << CS12);
            *TCCRxB &= ~((1 << CS11) );
            break;  
    }
}
