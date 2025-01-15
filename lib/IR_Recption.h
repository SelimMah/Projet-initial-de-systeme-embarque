
#include <avr/io.h> 
#include <util/delay.h>
#include <util/crc16.h>
#include <util/crc16.h>
#include "Debug.h"

uint8_t lireData()
{
    while (PIND & (1 << PD3)){} // RAISING
    uint16_t compteur = 0;
    while (!(PIND & (1 << PD3))){
        compteur++;
        _delay_us(50);
    } // FALLING
    if (compteur <= 15){
        return 0;
    }else if (compteur <= 35){
        return 1;
    }else   {
        return 2;
    }
}

void recupererDonnee(uint8_t tab[])
{
    while (lireData() != 2){}
    for (uint8_t i = 12; i > 0; i--){
        tab[i - 1] = lireData();
    }
}

void afficherDonnee(uint8_t tab[]){
    for (uint8_t i = 0; i < 12; i++){
        DEBUG_VALUE(tab[i]);
    }
    DEBUG_MESSAGE("\n");
}

uint8_t valeurDonnee(uint8_t tab[]){
    uint8_t result = 0;
    for (uint8_t i = 0; i < 7; i++) {
        result |= tab[i] << i;
    }
    return result;
}

uint8_t crcDonnee(uint8_t tab[]){
    uint8_t result = 0;
    for (uint8_t i = 0; i < 5; i++) {
        result |= tab[i+7] << i;
    }
    return result;
}

bool verifierDonnee(uint8_t Donnee, uint8_t crcDonnee){
    return (_crc16_update(0xFFFF, Donnee) & (0x1F)) == crcDonnee;
}

bool ReceiveDrawing(uint8_t* AB_Branchs, uint8_t* EF_Branchs, uint8_t* AB_Lengths, uint8_t* EF_Lengths)
{
    uint8_t tab[12];
    uint8_t donnee = 0;
    uint8_t crc = 0;
    uint8_t Donnees[18];
    
    bool donneesValides = true;

    for(uint8_t i = 0; i < 18; i++)
    {
        recupererDonnee(tab);
        donnee = valeurDonnee(tab);
        crc = crcDonnee(tab);
        donneesValides &= verifierDonnee(donnee, crc);
        Donnees[i] = donnee;
    }

    for (uint8_t i = 0; i < 4; ++i)
    {
        AB_Branchs[i] = Donnees[i];
    }
    
    for (uint8_t i = 4; i < 8; ++i)
    {
        EF_Branchs[i-4] = Donnees[i];
    }

    for (uint8_t i = 8; i < 13; ++i)
    {
        AB_Lengths[i-8] = Donnees[i];
    }

    for (uint8_t i = 13; i < 18; ++i)
    {
        EF_Lengths[i-13] = Donnees[i];
    }

    return donneesValides;
}

