/*
 * Nom: Driver.cpp
 * Auteurs: Selim-Mahjoub-2193614,
 *          Mohamed-Afandi-2291005,
 *          Bryan Alexandre Tavares-2291297
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Implémentation de la classe Driver de la Librairie
 */

#include "Driver.h"

// Constructeurs----------------------------------------------------------------

Driver::Driver()
{
    rightMotor_ = Motor(PortDirection::PORT_B, 6, PinPWM::T0B4);
    leftMotor_ = Motor(PortDirection::PORT_B, 3, PinPWM::T0B5);
}

// Constructeur de la classe Driver
// Paramètres :
//   - moteurGauche : Instance du moteur gauche
//   - moteurDroit : Instance du moteur droit
Driver::Driver(Motor moteurGauche, Motor moteurDroit) : leftMotor_(moteurGauche),
                                                          rightMotor_(moteurDroit)
{
}

// Methodes----------------------------------------------------------------

void Driver::setRightCorrection(uint8_t newCorerection)
{
    rightCorrection = newCorerection;
}

void Driver::setLefCorrection(uint8_t newCorerection)
{
    leftCorrection = newCorerection;
}

// Méthode pour arrêter les moteurs
void Driver::stop()
{
    leftMotor_.stop();
    rightMotor_.stop();
}

// Méthode pour avancer
// Paramètre :
//   - percent : Pourcentage de vitesse de déplacement
void Driver::goForward(uint8_t percent)
{
    leftMotor_.forward(percent + rightCorrection);
    rightMotor_.forward(percent + leftCorrection);
}

// Méthode pour reculer
// Paramètre :
//   - percent : Pourcentage de vitesse de déplacement
void Driver::goBackward(uint8_t percent)
{
    leftMotor_.backward(percent + rightCorrection);
    rightMotor_.backward(percent + leftCorrection);
}

// Méthode pour tourner à droite
// Paramètre :
//   - degre : Degré de rotation
void Driver::turnRightStationary(uint8_t degre)
{
    uint16_t DelayMS = 13;

    leftMotor_.forward(50);
    rightMotor_.backward(50);
    for (uint8_t i = 0; i < degre; ++i)
    {
        _delay_ms(DelayMS);
    }
    leftMotor_.stop();
    rightMotor_.stop();
}

// Méthode pour tourner à gauche
// Paramètre :
//   - degre : Degré de rotation
void Driver::turnLeftStationary(uint8_t degre)
{
    uint16_t DelayMS = 13;

    rightMotor_.forward(50);
    leftMotor_.backward(50);
    for (uint8_t i = 0; i < degre; ++i)
    {
        _delay_ms(DelayMS);
    }
    rightMotor_.stop();
    leftMotor_.stop();
}

// Méthode pour tourner à droite
// Paramètres :
//   - percentRight : Pourcentage de vitesse du moteur droit
//   - percentLeft : Pourcentage de vitesse du moteur gauche
void Driver::turnRightStationary(uint8_t percentRight, uint8_t percentLeft)
{
    leftMotor_.forward(percentLeft);
    rightMotor_.backward(percentRight);
}

// Méthode pour tourner à gauche
// Paramètres :
//   - percentRight : Pourcentage de vitesse du moteur droit
//   - percentLeft : Pourcentage de vitesse du moteur gauche
void Driver::turnLeftStationary(uint8_t percentRight, uint8_t percentLeft)
{
    rightMotor_.forward(percentRight);
    leftMotor_.backward(percentLeft);
}

// Méthode pour effectuer un virage
// Paramètres :
//   - percentRight : Pourcentage de vitesse du moteur droit
//   - percentLeft : Pourcentage de vitesse du moteur gauche
void Driver::turnForward(uint8_t percentRight, uint8_t percentLeft)
{
    rightMotor_.forward(percentRight);
    leftMotor_.forward(percentLeft);
}

void Driver::turnBackward(uint8_t percentRight, uint8_t percentLeft)
{
    rightMotor_.backward(percentRight);
    leftMotor_.backward(percentLeft);
}

void custumDelay(uint8_t delay)
{
    for (uint8_t i = 0; i < delay; i++)
    {
        _delay_ms(1);
    }
}

void Driver::impulse(ImpluseDirection direction, uint8_t delay)
{
    switch (direction)
    {
    case ImpluseDirection::Forward:
        goForward(100);
        custumDelay(delay);
        break;
    case ImpluseDirection::Backward:
        goBackward(100);
        custumDelay(delay);
        break;
    case ImpluseDirection::RightStationary:
        turnRightStationary(100, 100);
        custumDelay(delay);
        break;
    case ImpluseDirection::LeftStationary:
        turnLeftStationary(100, 100);
        custumDelay(delay);
        break;
    case ImpluseDirection::RightCurve:
        turnForward(100, 80);
        custumDelay(delay);
        stop();
        break;
    case ImpluseDirection::LeftCurve:
        turnForward(80, 100);
        custumDelay(delay);
        break;
    case ImpluseDirection::RightBackwardCurve:
        turnBackward(100, 80);
        custumDelay(delay);
        break;
    case ImpluseDirection::LeftBackwardCurve:
        turnBackward(80, 100);
        custumDelay(delay);
        break;
    default:
        break;
    }
}

// Méthode pour effectuer un mouvement de "twerk"
void Driver::twerk()
{
    uint16_t Delay10MS = 13;

    rightMotor_.forward();
    leftMotor_.backward();
    for (uint8_t i = 0; i < 25; ++i)
    {
        _delay_ms(Delay10MS);
    }
    leftMotor_.forward();
    rightMotor_.backward();
    for (uint8_t i = 0; i < 25; ++i)
    {
        _delay_ms(Delay10MS);
    }
}

// Méthode pour effectuer un mouvement de "taunt"
void Driver::taunt()
{
    rightMotor_.forward();
    leftMotor_.forward();

    _delay_ms(200);

    leftMotor_.backward();
    rightMotor_.backward();

    _delay_ms(200);

    leftMotor_.stop();
    rightMotor_.stop();
}