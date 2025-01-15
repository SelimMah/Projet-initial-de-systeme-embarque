/*
 * Nom: Sing.h
 * Auteurs: Selim-Mahjoub-2193614, 
 *          Mohamed-Afandi-2291005, 
 *          Bryan Alexandre Tavares-2291297 
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Classe Sing de la Librairie 
 */

#ifndef SING_H
#define SING_H

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

#include <math.h>

enum class PinSing {T0B5, T0B4, T2D7, T2D8};

class Sing 
{
public:  
    Sing(PinSing pinSing = PinSing::T2D8);

    void frequencySing(double frequency);
    void stopSing();
    void noteSing(uint8_t note);
    
private:
    volatile uint8_t * OCRxA;
    volatile uint8_t * PORTx;
};

#endif