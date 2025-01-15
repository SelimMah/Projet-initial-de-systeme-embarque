/*
 * Nom: Debug.cpp
 * Auteurs: Selim-Mahjoub-2193614, 
 *          Mohamed-Afandi-2291005, 
 *          Bryan Alexandre Tavares-2291297 
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Classe Debug de la Librairie 
 */


#include "Debug.h"

// Fonction pour initialiser le module de débogage (UART)
void initDebug()
{
    UART uart = UART();
    uart.initialiseUART();
}

// Fonction pour imprimer un message de débogage sur l'UART.
// Paramètres :
//   - debugMessage : Un tableau de caractères contenant le message de débogage à imprimer.
//   - size : La taille du message de débogage à imprimer.
void printMessage(const char* debugMessage)
{
    UART uart = UART();
    
    while (*debugMessage) 
    {
        uart.send(*debugMessage++);
    }
}

// Fonction pour convertir un entier non signé 16 bits en une chaîne de caractères
// Paramètres :
//   - value : L'entier non signé 16 bits à convertir.
//   - buffer : Le tableau de caractères où stocker la chaîne résultante.
//   - bufferSize : La taille du tableau de caractères buffer.
void uint16ToCharArray(uint16_t value, char *buffer, size_t bufferSize) 
{
    if (bufferSize >= 20) 
    {
        snprintf(buffer, 20, "%d\n", value);
    }
}

// Fonction pour imprimer un entier non signé 8 bits sur l'UART.
// Paramètre :
//   - value : L'entier non signé 8 bits à imprimer.
void printINT(uint8_t value)
{
    UART uart = UART();
    uart.send(value);
}

// Fonction pour imprimer une valeur initiale sur l'UART.
// Paramètres :
//   - value : La valeur initiale à imprimer.
void printINT(uint16_t value)
{
    UART uart = UART();
    
    uint16_t temp = value;
    uart.send(static_cast<uint8_t>(value >> 8));
    uart.send(static_cast<uint8_t>(temp));
}

// Fonction pour imprimer une valeur sous forme de chaîne de caractères sur l'UART.
// Paramètre :
//   - value : La valeur à imprimer sous forme de chaîne de caractères.
void printValue(uint16_t value)
{
    char myBuffer[20];
    uint16ToCharArray(value, myBuffer, sizeof(myBuffer));
    printMessage(myBuffer);
}
