/******************************************************************************/
/*                                                                            */
/* Isidore Lauzier - 9 juillet 2005                                           */
/*                                                                            */
/* Cet exemple d'utilisation d'une memoire eeprom i2c est une modification du */
/* programme de Joerg Wunsch twitest.c fourni avec Winavr. Il est compatible  */
/* aux eeprom 24C128, 24C256 et 24c512. Ce programme a ete simplifie afin     */
/* d'illustrer la programmation du bus TWI et des memoires I2C.               */
/*                                                                            */
/* NOTE IMPORTANTE: Le protocule I2C utilise les broches C0 et C1 sur un      */
/*                  microcontroleur Atmel ATMega244pa.                        */
/*                                                                            */
/* Modifications mineures:                                                    */
/*   - Pour refaire l'indentation - ete 2007 - Jerome Collin                  */
/*   - Pour preciser les broches utilisees - novembre 2008 - Jerome Collin    */
/*   - ajouts de commentaires - septembre 2017 - Jerome Collin                */
/*   - Correction de certains commentaires - septembre 2022 - Jérôme Collin   */
/*                                                                            */
/******************************************************************************/

#ifndef MEMOIRE_24_H
#define MEMOIRE_24_H

# define F_CPU 8000000UL

#include <avr/io.h>
#include <util/twi.h>

class Memoire24CXXX
{
public:

   Memoire24CXXX(); // le constructeur appelle init() decrit plus bas
   ~Memoire24CXXX();

   // procedure d'initialisation appelee par le constructeur
   // Donc, ne pas le refaire a moins de changements en cours
   // d’utilisation.
   void init();
   
   // la procedure init() initialize a zero le "memory bank". 
   // appeler cette methode uniquement si l'adresse doit changer
   static uint8_t choisir_banc(const uint8_t banc);
   
   // deux variantes pour la lecture, celle-ci et la suivante
   // une donnee a la fois
   uint8_t lecture(const uint16_t adresse, uint8_t *donnee);
   // bloc de donnees : longueur doit etre de 127 et moins
   uint8_t lecture(const uint16_t adresse, uint8_t *donnee,
                   const uint8_t longueur);

   // deux variantes pour la l'ecriture egalement:
   // une donnee a la fois
   uint8_t ecriture(const uint16_t adresse, const uint8_t donnee);
   // bloc de donnees : longueur doit etre de 127 et moins
   uint8_t ecriture(const uint16_t adresse, uint8_t *donnee,
                    const uint8_t longueur);

private:
   // pour l'ecriture
   uint8_t ecrire_page(const uint16_t adresse, uint8_t *donnee,
                       const uint8_t longueur);

private:
   // donnees membres
   static uint8_t m_adresse_peripherique;
   const uint8_t PAGE_SIZE;
};

#endif /* MEMOIRE_24_H */
