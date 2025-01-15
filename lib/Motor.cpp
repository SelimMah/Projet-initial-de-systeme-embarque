/*
 * Nom: LED.cpp
 * Auteurs: Selim-Mahjoub-2193614,
 *          Mohamed-Afandi-2291005,
 *          Bryan Alexandre Tavares-2291297
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Deffinition des methodes de la classe LED
 */

#include "Motor.h"

//Constructeurs----------------------------------------------------------------

// Constructeur de la classe Motor
// Paramètres :
//   - port : Le port sur lequel est connecté le moteur
//   - brocheDirection : Le numéro de broche pour le contrôle de la direction
//   - pinPWM : L'objet PinPWM associé pour le contrôle de la vitesse
Motor::Motor(PortDirection port, uint8_t brocheDirection, PinPWM pinPWM) :
    pinDirection_(brocheDirection - 1),
    pinPWM_(pinPWM)
 {
        port_ = port;
 }


//Methodes----------------------------------------------------------------

// Méthode pour faire avancer le moteur avec une certaine vitesse en pourcentage
// Paramètre :
//   - percent : Pourcentage de vitesse à laquelle le moteur doit avancer
void Motor::forward(uint8_t percent)
{
    switch (port_)
    {
    case PortDirection::PORT_B:
        PORTB &= ~(1 << pinDirection_);
        break;

    case PortDirection::PORT_D:
        PORTD &= ~(1 << pinDirection_);
        break;

    default:
        break;
    }
    
    pinPWM_.setPercent(percent);
}

// Méthode pour faire reculer le moteur avec une certaine vitesse en pourcentage
// Paramètre :
//   - percent : Pourcentage de vitesse à laquelle le moteur doit reculer
void Motor::backward(uint8_t percent)
{
    switch (port_)
    {
    case PortDirection::PORT_B:
        PORTB |= 1 << pinDirection_;
        break;

    case PortDirection::PORT_D:
        PORTD |= 1 << pinDirection_;
        break;

    default:
        break;
    }

    pinPWM_.setPercent(percent);
}

// Méthode pour arrêter le moteur
void Motor::stop()
{
    pinPWM_.setPercent(0);
}
