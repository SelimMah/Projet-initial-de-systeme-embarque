/*
 * Nom: Robot.cpp
 * Auteurs: Selim-Mahjoub-2193614,
 *          Mohamed-Afandi-2291005,
 *          Bryan Alexandre Tavares-2291297
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Implémentation de la classe Robot de la Librairie
 */

#include "Robot.h"

// Constructeur par défaut de la classe Robot
Robot::Robot() 
{
}

// Méthode pour définir la LED du robot
// Paramètres :
//   - port : Sélection du port où est connectée la LED
//   - brochePlus : Numéro de broche pour la LED positive
//   - brocheMoins : Numéro de broche pour la LED négative
void Robot::setLed(PortSelection port, uint8_t brochePlus, uint8_t brocheMoins)
{
    led = LED(port, brochePlus, brocheMoins);
}

// Méthode pour définir le module de son (Sing) du robot
// Paramètre :
//   - pinSing : Sélection de la broche pour le module de son
void Robot::setSing(PinSing pinSing)
{
    sing = Sing(pinSing);
}
