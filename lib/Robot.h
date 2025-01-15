/*
 * Nom: Robot.h
 * Auteurs: Selim-Mahjoub-2193614, 
 *          Mohamed-Afandi-2291005, 
 *          Bryan Alexandre Tavares-2291297 
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Classe Robot de la Librairie 
 */

#ifndef ROBOT_H
#define ROBOT_H

#define F_CPU 8000000

#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>
#include "string.h"
#include <stdlib.h>

#include "Driver.h"
#include "LED.h"
#include "Sing.h"

class Robot
{
public:
    //Constructeurs--------------------------------------------------

    Robot();

    //Methodes--------------------------------------------------

    void setLed(PortSelection port, uint8_t brochePlus, uint8_t brocheMoins);
    void setSing(PinSing pinSing = PinSing::T2D8);

    //Attribues--------------------------------------------------

    LED led = LED(PortSelection::PORT_A, 1, 2);   // Le controle de la LED
    Driver driver;
    Sing sing = Sing(PinSing::T2D7);  // Le SingTimer pour jouer les sonorites
};

#endif 