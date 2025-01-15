/*
 * Nom: LED.h
 * Auteurs: Selim-Mahjoub-2193614, 
 *          Mohamed-Afandi-2291005, 
 *          Bryan Alexandre Tavares-2291297 
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Classe LED de la Librairie 
 */

#ifndef LED_H
#define LED_H

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

enum PortSelection { PORT_A, PORT_B, PORT_C, PORT_D };

class LED 
{
public:

    //Constructeurs--------------------------------------------------
    
    LED();
    LED(PortSelection port, uint8_t brochePlus, uint8_t brocheMoins);

    //Methodes--------------------------------------------------
    
    void off() const;
    void red(uint16_t delay_MS = 0) const;
    void green(uint16_t delay_MS = 0) const;
    void ambre(uint16_t delay_MS) const;

    void customDelay(uint16_t delay_MS) const;

private:
    PortSelection port_;
    uint8_t pinPlus_;
    uint8_t pinMoins_;

    volatile uint8_t* PORTx;
};


#endif