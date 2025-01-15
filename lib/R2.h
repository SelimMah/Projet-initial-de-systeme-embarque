/*
 * Nom: R2.h
 * Auteurs: Selim-Mahjoub-2193614,
 *          Mohamed-Afandi-2291005,
 *          Bryan Alexandre Tavares-2291297
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Classe R2 de la Librairie
 */

#ifndef R2_H
#define R2_H

#include "LineFollower.h"
#include "IR_Transmission.h"
#include "Draw.h"
#include "Sing.h"

enum class R2State
{
    Parcour,
    Waiting,
    SendIR,
    SendRS232
};

class R2
{
public:
    R2(){};
    void LED5Hz232();
    void stopLED();

    void parcourRoutine();
    void waitingRoutine();
    void sendIR_Routine();
    void sendRS232Routine();

    LineFollower lineFollower;
    Drawer drawer;
    IRTransmitter IRTransmission = IRTransmitter();
    LED waitingLed = LED(PortSelection::PORT_D, 5, 7);
    Sing sing = Sing(PinSing::T2D8);

    R2State state = R2State::Parcour;
};

#endif