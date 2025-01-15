/*
 * Nom: Motor.h
 * Auteurs: Selim-Mahjoub-2193614, 
 *          Mohamed-Afandi-2291005, 
 *          Bryan Alexandre Tavares-2291297 
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Classe Motor de la Librairie 
 */
#ifndef MOTOR_H
#define MOTOR_H

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <PWM.h>

enum class PortDirection {PORT_B, PORT_D};

class Motor
{    
public:

    //Constructeurs--------------------------------------------------
    
    Motor(PortDirection port, uint8_t brocheDirection, PinPWM pinPWM);
    
    //Getters--------------------------------------------------
    
    void forward(uint8_t percent = 100);
    void backward(uint8_t percent = 100);
    void stop();

private:
    PortDirection port_;
    uint8_t pinDirection_;
    PWM pinPWM_;
};

#endif 