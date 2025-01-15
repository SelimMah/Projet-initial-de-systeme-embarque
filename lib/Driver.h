/*
 * Nom: Driver.h
 * Auteurs: Selim-Mahjoub-2193614,
 *          Mohamed-Afandi-2291005,
 *          Bryan Alexandre Tavares-2291297
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Classe Driver de la Librairie
 */

#ifndef DRIVER_H
#define DRIVER_H

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <Motor.h>

enum class ImpluseDirection
{
    Forward,
    Backward,
    RightStationary,
    LeftStationary,
    RightCurve,
    LeftCurve,
    RightBackwardCurve,
    LeftBackwardCurve
};

class Driver
{
public:
    // Constructeurs--------------------------------------------------
    Driver();
    Driver(Motor leftMotor, Motor rightMotor);

    // Methodes--------------------------------------------------

    void setRightCorrection(uint8_t newCorerection);
    void setLefCorrection(uint8_t newCorerection);
    
    void stop();
    void goForward(uint8_t percent = 100);
    void goBackward(uint8_t percent = 100);

    void turnRightStationary(uint8_t degre = 90);
    void turnLeftStationary(uint8_t degre = 90);

    void turnRightStationary(uint8_t percentRight, uint8_t percentLeft);
    void turnLeftStationary(uint8_t percentRight, uint8_t percentLeft);

    void turnForward(uint8_t percentRight, uint8_t percentLeft);
    void turnBackward(uint8_t percentRight, uint8_t percentLeft);
    void impulse(ImpluseDirection direction, uint8_t delay = 15);

    void twerk();
    void taunt();

private:
    Motor rightMotor_ = Motor(PortDirection::PORT_B, 6, PinPWM::T0B4);
    Motor leftMotor_ = Motor(PortDirection::PORT_B, 3, PinPWM::T0B5);

    uint8_t rightCorrection = 0;
    uint8_t leftCorrection = 0;
};

#endif