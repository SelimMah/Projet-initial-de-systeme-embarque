/*
 * Nom: Timer.h
 * Auteurs: Selim-Mahjoub-2193614, 
 *          Mohamed-Afandi-2291005, 
 *          Bryan Alexandre Tavares-2291297,
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Implémentation de la classe Timer de la Librairie 
 */

#ifndef Timer_H
#define Timer_H

#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>

enum class TimerNumber {Timer_0, Timer_1, Timer_2};

class Timer 
{
public:
    //Constructeurs--------------------------------------------------

    Timer(TimerNumber timerNumber = TimerNumber::Timer_1, uint16_t clockDiv = 1024);

    //Methodes--------------------------------------------------

    void startTimer(uint32_t durationMS = 9000);
    void startChronos();
    void stopTimer();
    void setClockDivisor(uint16_t divisor);
    void enableInterrupt(bool enable);

    //Getteur--------------------------------------------------
    
    const bool getTimerStarted_() { return timerStarted_; }
    const bool getInterruptEnabled() { return interruptEnabled_; }
    const uint16_t getClockDivisor() { return clockDivisor_; }
    const uint16_t getTimerClock() { return TCNT1; }

private:
    
    TimerNumber timerNumber_;
    bool timerStarted_;
    bool interruptEnabled_;
    uint16_t clockDivisor_;
    uint32_t clockFrequency_;

    // Registres -----------------------------------------------------
    volatile uint8_t * TCCRxA;
    volatile uint8_t * TCCRxB;
    volatile uint8_t * TCNTx;
    volatile uint8_t * TIMSKx;
    volatile uint8_t * OCRxA;
};

#endif
