/*
 * Nom: UART.h
 * Auteurs: Selim-Mahjoub-2193614,
 *          Mohamed-Afandi-2291005,
 *          Bryan Alexandre Tavares-2291297
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Classe UART de la Librairie
 */

#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <avr/eeprom.h> 

class UART
{
public:
    UART();
    
    void initialiseUART ();
    
    void send(uint8_t data);        
    uint8_t receive();

};

#endif