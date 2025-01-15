/*
 * Nom: PWM.h
 * Auteurs: Selim-Mahjoub-2193614, 
 *          Mohamed-Afandi-2291005, 
 *          Bryan Alexandre Tavares-2291297 
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Classe PWM de la Librairie 
 */

#ifndef PWM_H
#define PWM_H

#include <avr/io.h>
#include <avr/interrupt.h>

enum class PinPWM { T0B4, T0B5, T1D5, T1D6, T2D7, T2D8 };

class PWM 
{
public:
    
    //Constructeurs--------------------------------------------------
    
    PWM(PinPWM pinPWM, uint8_t percent = 0);

    //Getters--------------------------------------------------
    
    uint8_t getPercent() const { return percent_;};

    //Methodes--------------------------------------------------
    
    void setPercent(uint8_t percent);
    void increase(uint8_t percent);
    void decrease(uint8_t percent);
    void stop();

 private:
    uint8_t percent_;
    PinPWM pinPWM_;
};

#endif