/*
 * Nom: Button.cpp
 * Auteurs: Selim-Mahjoub-2193614, 
 *          Mohamed-Afandi-2291005, 
 *          Bryan Alexandre Tavares-2291297 
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Implémentation de la classe Button de la Librairie
 */

#include "Button.h"

// Constructeur de la classe Button
// Paramètres :
//   - enable : Un booléen indiquant si le bouton est activé ou non.
//   - edge : Le type de bord (front montant ou descendant) pour la configuration de l'interruption du bouton.
Button::Button(bool enable, Edge edge)
{
    if (enable) {configureButtonInterrupt(edge);};
}

// Initialise l'interruption du bouton
// Paramètre :
//   edge : type de front déclencheur de l'interruption (Edge)
void Button::configureButtonInterrupt(Edge edge) 
{
    cli ();
    
    EIMSK |= (1 << INT0);
    EICRA &= ~0x03; 
    
    switch (edge)
    {
    case Edge::LOW : 
        EICRA |= 0x01;
        break;
    
    case Edge::ANY :
        EICRA |= 0x01;
        break;
    
    case Edge::FALLING :
        EICRA |= 0x02;
        break;

    case Edge::RISING :    
    default:
        EICRA |= 0x03;
        break;
    }

    sei ();
}

// Vérifie si le bouton est pressé
// Retourne true si le bouton est pressé, sinon false
bool Button::buttonPressed() 
{
    return (PIND & (1 << 2));
}

// Gère le rebond du bouton
// Retourne true si le bouton est pressé après le rebond, sinon false
bool Button::debounceButton() 
{
    uint8_t delayDebounce = 20;
    if (buttonPressed()) 
    {
        _delay_ms(delayDebounce);
        if (buttonPressed()) 
        {
            return true;
        }
    }
    return false;
}