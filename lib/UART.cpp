/*
 * Nom: UART.cpp
 * Auteurs: Selim-Mahjoub-2193614,
 *          Mohamed-Afandi-2291005,
 *          Bryan Alexandre Tavares-2291297
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Classe UART de la Librairie
 */

#include "UART.h"

// Constructeur par défaut de la classe UART
UART::UART() {}

// Méthode pour initialiser l'UART avec les paramètres de configuration prédéfinis
void UART::initialiseUART()
{
	UBRR0H = 0;
	UBRR0L = 0xCF;

	UCSR0A = (1 << UDRE0);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Méthode pour envoyer des données sur l'UART
// Paramètre :
//   - data : Les données à envoyer
void UART::send(uint8_t data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data; 
}

// Méthode pour recevoir des données de l'UART
// Retourne :
//   - Les données reçues
uint8_t UART::receive()
{
    while (!(UCSR0A & (1<<RXC0)));
    return UDR0;
}