/*
 * Nom: LED.cpp
 * Auteurs: Selim-Mahjoub-2193614,
 *          Mohamed-Afandi-2291005,
 *          Bryan Alexandre Tavares-2291297
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Définition des méthodes de la classe LED
 */

#include "LED.h"

// Constructeurs -------------------------------------------------------------

// Constructeur par défaut
LED::LED()
{
    port_ = PortSelection::PORT_A;
    pinPlus_ = 0;
    pinMoins_ = 1;
};

// Constructeur avec paramètres
// Paramètres :
//   port : sélection du port (PortSelection)
//   brochePlus : numéro de la broche positive (uint8_t)
//   brocheMoins : numéro de la broche négative (uint8_t)
LED::LED(PortSelection port, uint8_t brochePlus, uint8_t brocheMoins)
{
    switch (port)
    {
    case PortSelection::PORT_A:
        PORTx = &PORTA; 
        break;

    case PortSelection::PORT_B:
        PORTx = &PORTB;
        break;

    case PortSelection::PORT_C:
        PORTx = &PORTC;
        break;

    case PortSelection::PORT_D:
        PORTx = &PORTD;
        break;

    default:
        break;
    }

    port_ = port;
    pinPlus_ = brochePlus - 1;
    pinMoins_ = brocheMoins - 1;
};

// Méthodes -------------------------------------------------------------

// Fonction de délai personnalisée
// Paramètres :
//   delay_MS : durée du délai en millisecondes (uint16_t)
void LED::customDelay(uint16_t delay_MS) const
{
    for (uint16_t i = 0; i < delay_MS; i++)
    {
        _delay_ms(1);
    }
};

// Éteint la LED
void LED::off() const
{
    *PORTx &= ~((1 << pinPlus_) | (1 << pinMoins_));
};

// Allume la LED en rouge
// Paramètres :
//   delay_MS : durée pendant laquelle la LED reste allumée en millisecondes (uint16_t)
void LED::red(uint16_t delay_MS) const
{
    *PORTx |= (1 << pinPlus_);
    *PORTx &= ~(1 << pinMoins_);

    if (delay_MS != 0)
    {
        customDelay(delay_MS);
        off();
    }
};

// Allume la LED en vert
// Paramètres :
//   delay_MS : durée pendant laquelle la LED reste allumée en millisecondes (uint16_t)
void LED::green(uint16_t delay_MS) const
{
    *PORTx |= (1 << pinMoins_);
    *PORTx &= ~(1 << pinPlus_);
 
    if (delay_MS != 0)
    {
        customDelay(delay_MS);
        off();
    }
};

// Allume la LED en ambre (rouge et vert alternés)
// Paramètres :
//   delay_MS : durée pendant laquelle la LED reste allumée en millisecondes (uint16_t)
void LED::ambre(uint16_t delay_MS) const
{
    uint8_t delay_red = 1;
    uint8_t delay_green = 4;
    uint16_t cycle = delay_MS / (delay_red + delay_green);

    for (uint16_t i = 0; i < cycle; ++i)
    {
        red();
        _delay_ms(delay_red);
        green();
        _delay_ms(delay_green);
    }
    off();
};


