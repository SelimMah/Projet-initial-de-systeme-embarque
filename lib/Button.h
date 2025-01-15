/*
 * Nom: Button.h
 * Auteurs: Selim-Mahjoub-2193614, 
 *          Mohamed-Afandi-2291005, 
 *          Bryan Alexandre Tavares-2291297 
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Implémentation de la classe Button de la Librairie
 */

#ifndef Button_H
#define Button_H

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

enum class Edge {LOW, ANY, FALLING, RISING };

class Button
{
 public:
    
    //Constructeurs--------------------------------------------------
    
    Button(bool enable = false, Edge edge = Edge::RISING);

    //Methodes--------------------------------------------------
    
    static void configureButtonInterrupt (Edge edge);
    
    static bool buttonPressed();
    static bool debounceButton();

};

#endif
