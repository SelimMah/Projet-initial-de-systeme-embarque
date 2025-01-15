

#include "Sing.h"

// Constructeur de la classe Sing
// Initialise les paramètres en fonction de la broche passée en paramètre.
// Paramètre :
//   - pinSing : L'instance de la broche utilisée pour Sing.
Sing::Sing(PinSing pinSing)
{
    switch (pinSing)
    {
    case PinSing::T0B4:
        OCRxA = &OCR0A;
        PORTx = &PORTB;
        
        TCNT0 = 0;
        TCCR0A |= (1 << COM0A0) | (1 << WGM01);
        TCCR0B |= (1 << CS02);   
        break;
    
    case PinSing::T0B5:
        OCRxA = &OCR0A;
        PORTx = &PORTB;
        
        TCNT0 = 0;
        TCCR0A |= (1 << COM0B0) | (1 << WGM01);
        TCCR0B |= (1 << CS02);  
        break;

    case PinSing::T2D7:
        OCRxA = &OCR2A;
        PORTx = &PORTD;
        
        TCNT2 = 0;
        TCCR2A |= (1 << COM2B0) | (1 << WGM21);
        TCCR2B |= (1 << CS22) | (1 << CS21);        
        break;

    case PinSing::T2D8:
        OCRxA = &OCR2A;
        PORTx = &PORTD;
        
        TCNT2 = 0;
        TCCR2A |= (1 << COM2A0) | (1 << WGM21);
        TCCR2B |= (1 << CS22) | (1 << CS21);      
        break;

    default:
        break;
    }
}

// Méthode pour ajuster la fréquence du son Sing
// Paramètre :
//   - frequency : La fréquence à laquelle régler le son Sing.
void Sing::frequencySing(double frequency)
    {
        *OCRxA = static_cast<uint8_t>((F_CPU / (2 * 256 * frequency)) - 1);
    }


// Fonction pour arrêter le son Sing
void Sing::stopSing()
{
    *OCRxA = 0 ;
}

// Méthode pour jouer une note musicale avec le son Sing
// Paramètre :
//   - note : La note musicale à jouer.
void Sing::noteSing(uint8_t note) 
{
  if ((note <= 81) && (note >= 45))
  {
    double noteDouble = static_cast<double>(note);
    double frequencyRefference = 440.0;        
    double frequency = frequencyRefference * pow((double) 2.0, ((double)(noteDouble - 69) / (double)12.0));

    frequencySing(frequency);
  }
}
