/*
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * Matthew Khouzam et Jerome Collin
 * 2005-2006
 *
 * Code qui n'est sous aucune license.
 *
 */

#include "can.h"

// constructeur: initialisation du convertisseur
can::can()
{
   // ADC mux : reference analogique externe
   //           ajuste a droite
   ADMUX  = ( 0 << REFS1 ) | ( 0 << REFS0 ) | ( 0 << ADLAR ) | ( 0 << MUX4 ) |
            ( 0 << MUX3 ) | ( 0 << MUX2 ) | ( 0 << MUX1) | ( 0 << MUX0 ) ;

   // ADC Status and Control Register A : 
   //  Active le convertisseur mais sans demarrer de conversion pour l'instant.
   //  Pas de declanchement automatique et aucune interruption suivant
   //  la fin d'une convertion. Division de l'horloge par 64 (il faudra
   //  donc 13 cycles du convertisseur * 64 pour terminer une conversion
   //  soit 832 cycles d'horloge soit 104 micro-secondes
   ADCSRA = ( 1 << ADEN ) | ( 0 << ADSC )  | ( 0 << ADATE ) | ( 0 << ADIF ) |
            ( 0 << ADIE ) | ( 1 << ADPS2 ) | ( 1 << ADPS1 ) | ( 0 << ADPS0 ) ;
}

// Destructeur:  Arreter le convertisseur pour sauver sur la consommation.
can::~can()
{
   // rendre le convertisseur inactif.
   ADCSRA = 0 << ADEN ;
}

// Faire une conversion et aller retourner le resultat sur 16 bits
// dont seulement les 10 de poids faibles sont significatifs.
uint16_t
can::lecture( uint8_t pos)
{
   uint16_t adcVal;

   // Garder les bits de ADMUX intacts, sauf les bit permettant 
   // la selection de l'entree
   ADMUX  &=  ~(( 1 << MUX4 ) | ( 1 << MUX3 ) | 
                ( 1 << MUX2 ) | ( 1 << MUX1)  | ( 1 << MUX0 ));

   // selectionner l'entree voulue
   ADMUX |= ((pos & 0x07) << MUX0) ;

   // demarrer la conversion
   ADCSRA |= ( 1 << ADSC );

   // Attendre la fin de la conversion soit 13 cycles du convertisseur.
   while( ! (ADCSRA & ( 1 << ADIF ) ) );

   // important: remettre le bit d'indication de fin de cycle a zero 
   // pour la prochaine conversion ce qui se fait en l'ajustant a un.
   ADCSRA |= (1 << ADIF);

   // Aller chercher le resultat sur 16 bits.
   adcVal =   ADCL ;
   adcVal +=  ADCH << 8;

   // resultat sur 16 bits
   return adcVal;
}

