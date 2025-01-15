/*
 * Nom: PWM.cpp
 * Auteurs: Selim-Mahjoub-2193614,
 *          Mohamed-Afandi-2291005,
 *          Bryan Alexandre Tavares-2291297
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Implémentation de la classe PWM de la Librairie
 */

#include "PWM.h"

// Constructeurs----------------------------------------------------------------

// Constructeur de la classe PWM
// Paramètres :
//   - pinPWM : L'identifiant de la broche PWM
//   - percent : Pourcentage initial de la largeur d'impulsion
PWM::PWM(PinPWM pinPWM, uint8_t percent) : 
    percent_(percent),
    pinPWM_(pinPWM)

{
    switch (pinPWM_)
    {
    case PinPWM::T0B4:
        // Configuration pour la broche T0B4
        TCNT0 = 0;
        OCR0A = (percent_ * 255) / 100;
        TCCR0A |= (1 << COM0A1 | 1 << WGM00);
        TCCR0B |= (1 << CS00);
        break;

    case PinPWM::T0B5:
        // Configuration pour la broche T0B5
        TCNT0 = 0;
        OCR0B = (percent_ * 255) / 100;
        TCCR0A |= (1 << COM0B1 | 1 << WGM00);
        TCCR0B |= (1 << CS00);
        break;

    case PinPWM::T1D6:
        // Configuration pour la broche T1D5
        TCNT1 = 0;
        OCR1A = (percent_ * 255) / 100;
        TCCR1A |= (1 << COM1A1 | 1 << WGM10);
        TCCR1B |= (1 << CS10);
        break;

    case PinPWM::T1D5:
        // Configuration pour la broche T1D6
        TCNT1 = 0;
        OCR1B = (percent_ * 255) / 100;
        TCCR1A |= (1 << COM1B1 | 1 << WGM10);
        TCCR1B |= (1 << CS10);
        break;

    case PinPWM::T2D8:
        // Configuration pour la broche T2D7
        TCNT2 = 0;
        OCR2A = (percent_ * 255) / 100;
        TCCR2A |= (1 << COM2A1 | 1 << WGM20);
        TCCR2B |= (1 << CS20);
        break;

    case PinPWM::T2D7:
        // Configuration pour la broche T2D8
        TCNT2 = 0;
        OCR2B = (percent_ * 255) / 100;
        TCCR2A |= (1 << COM2B1 | 1 << WGM20);
        TCCR2B |= (1 << CS20);
        break;
    
    default:
        break;
    }
}

//Methodes----------------------------------------------------------------

// Méthode pour définir le pourcentage de la largeur d'impulsion
// Paramètre :
//   - percent : Pourcentage de la largeur d'impulsion
void PWM::setPercent(uint8_t percent)
{
    percent_ = percent;

    switch (pinPWM_)
    {
    case PinPWM::T0B4:
        OCR0A = (percent * 255) / 100;
        break;

    case PinPWM::T0B5:
        OCR0B = (percent * 255) / 100;
        break;

    case PinPWM::T1D6:
        OCR1A = (percent * 255) / 100;
        break;

    case PinPWM::T1D5:
        OCR1B = (percent * 255) / 100;
        break;

    case PinPWM::T2D8:
        OCR2A = (percent * 255) / 100;
        break;

    case PinPWM::T2D7:
        OCR2B = (percent * 255) / 100;
        break;

    default:
        break;
    }
}

// Méthode pour diminuer le pourcentage de la largeur d'impulsion
// Paramètre :
//   - percent : Pourcentage à diminuer
void PWM::decrease(uint8_t percent)
{
    if (percent_ < percent) { percent_ = 0;}
    else {percent_ -= percent;}

    setPercent(percent_);
}

// Méthode pour augmenter le pourcentage de la largeur d'impulsion
// Paramètre :
//   - percent : Pourcentage à augmenter
void PWM::increase(uint8_t percent)
{
    uint8_t difference = (255 - percent_);
    
    if (difference < percent) {percent_ = 255;}
    else { percent_ += percent;}

    setPercent(percent_);
}
// Méthode pour arrêter le PWM en mettant la largeur d'impulsion à 0
void PWM::stop() {setPercent(0);}