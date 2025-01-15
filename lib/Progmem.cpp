/*
 * Nom: Progmem.cpp
 * Auteurs: Selim-Mahjoub-2193614,
 *          Mohamed-Afandi-2291005,
 *          Bryan Alexandre Tavares-2291297
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Implémentation de la classe Progmem de la Librairie
 */

#include "Progmem.h"

// Méthode pour lire une instruction et un opérande à partir de la mémoire
// Paramètres :
//   - instruction : Pointeur vers l'instruction à lire
//   - operand : Pointeur vers l'opérande à lire
void Progmem::readInstructionOperand(uint8_t *instruction, uint8_t *operand)
{
    memory.lecture(progCounter++, instruction);
    _delay_ms(10);

    memory.lecture(progCounter++, operand);
    _delay_ms(10);
}

// Méthode pour attendre un certain temps en millisecondes
// Paramètre :
//   - operand : Le temps d'attente en nombre de boucles
void Progmem::waitRoutine(uint8_t operand)
{
    for (uint8_t i = 0; i < operand; i++)
    {
        _delay_ms(25);
    }
}

// Méthode pour allumer une LED en fonction de l'opérande
// Paramètre :
//   - operand : L'opérande indiquant quelle LED allumer
void Progmem::ledOnRoutine(uint8_t operand)
{
    if (operand == 1)
    {
        robot.led.green();
    }
    else if (operand == 2)
    {
        robot.led.red();
    }
}

// Méthode pour éteindre la LED
void Progmem::ledOffRoutine()
{
    robot.led.off();
}

// Méthode pour jouer une note musicale en fonction de l'opérande
// Paramètre :
//   - operand : L'opérande indiquant quelle note jouer
void Progmem::singOnRoutine(uint8_t operand)
{
    robot.sing.noteSing(operand);
}

// Méthode pour arrêter de jouer la note musicale
void Progmem::singOffRoutine()
{
    robot.sing.stopSing();
}

// Méthode pour arrêter les moteurs du robot
void Progmem::MotorOffRoutine()
{
    robot.driver.stop();
}

// Méthode pour avancer en fonction de l'opérande
// Paramètre :
//   - operand : L'opérande indiquant la vitesse d'avancement
void Progmem::ForwardRoutine(uint8_t operand)
{
    double operandFloat = static_cast<double>(operand);
    double percent = (operandFloat / 255.0) * 100.0;
    robot.driver.goForward(percent);
}

// Méthode pour reculer en fonction de l'opérande
// Paramètre :
//   - operand : L'opérande indiquant la vitesse de recul
void Progmem::BackwardRoutine(uint8_t operand)
{
    double operandFloat = static_cast<double>(operand);
    double percent = (operandFloat / 255.0) * 100.0;
    robot.driver.goBackward(percent);
}

// Méthode pour effectuer un virage à droite
void Progmem::RightTurnRoutine()
{
    robot.driver.turnRightStationary(90);
}

// Méthode pour effectuer un virage à gauche
void Progmem::LeftTurnRoutine()
{;
    robot.driver.turnLeftStationary(90);
}

// Méthode pour commencer une boucle en fonction de l'opérande
// Paramètre :
//   - operand : L'opérande indiquant le nombre de répétitions de la boucle
void Progmem::BeginLoopRoutine(uint8_t operand)
{
    loopAdress = progCounter;
    loopCounter = operand;
}

// Méthode pour terminer une boucle
void Progmem::EndLoopRoutine()
{
    if (loopCounter > 0)
    {
        progCounter = loopAdress;
        loopCounter--;
    }
}

// Méthode pour terminer le programme en arrêtant les moteurs, la musique et la LED
void Progmem::End()
{
    robot.driver.stop();
    robot.sing.stopSing() ;
    robot.led.off();
}
