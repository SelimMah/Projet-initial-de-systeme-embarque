/*
 * Nom: Button.h
 * Auteurs: Selim-Mahjoub-2193614, 
 *          Mohamed-Afandi-2291005, 
 *          Bryan Alexandre Tavares-2291297 
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Implémentation de la classe Button de la Librairie
*/
#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/crc16.h>
// Inclusion des bibliothèques nécessaires

#include "Button.h"
#include "Debug.h"
#include "can.h"
#include "Robot.h"
#include "Draw.h"

//-----------------------------------------------------------------------

enum class Cage
{
    FIND_DISTANCE,
    SWEEPING,
    WAITING,
    RECEPTIONIR,
    RS_232
};

class DistanceSensor
{
public:
    // Constructeurs ----------------------------------------------------

    DistanceSensor(Robot &robot, can &distance);

    // Methodes ---------------------------------------------------------

    void mouvementWall(uint16_t &detectionSurface, Cage &state);
    void findDoor(uint16_t &detectionSurface, uint8_t &tempDeBalayage);

    void musicBouton(uint8_t note);

    void drawing(uint8_t AB_Branchs[4], uint8_t EF_Branchs[4], uint8_t AB_Lengths[5], uint8_t EF_Lengths[5], Drawer drawer, DistanceSensor distanceSensor, uint16_t &moyennePosition, uint8_t &tempDeBalayage);

    void initTimerISR();
    void genererFrequence();
    void arreterFrequence();

    void parcoursR1(uint16_t detectionSurface, Button button, DistanceSensor distanceSensor, Drawer drawer, Cage &state, uint8_t &isPositionFind, uint16_t &moyennePosition, uint8_t &tempDeBalayage);

    uint8_t lireData();
    void recupererDonnee(uint8_t tab[]);
    void afficherDonnee(uint8_t tab[]);
    uint8_t valeurDonnee(uint8_t tab[]);
    uint8_t crcDonnee(uint8_t tab[]);
    bool verifierDonnee(uint8_t Donnee, uint8_t crcDonnee);
    bool ReceiveDrawing(uint8_t* AB_Branchs, uint8_t* EF_Branchs, uint8_t* AB_Lengths, uint8_t* EF_Lengths);

    Memoire24CXXX memory;

    Cage state;
    Robot robot;
    can distance;
    Motor rightMotor = Motor(PortDirection::PORT_B, 6, PinPWM::T0B4);
    Motor leftMotor  = Motor(PortDirection::PORT_B, 3, PinPWM::T0B5);
    Driver driver    = Driver(leftMotor, rightMotor);

    uint8_t const leftMotorSpeed      = 50;
    uint8_t const rightMotorSpeed     = 53;
    uint8_t const forwardSpeed        = 48;
    uint8_t const backwardSpeedRight  = 60;
    uint8_t const backwardSpeedLeft   = 52;
    uint8_t tempsdebalayage           = 0;

    uint8_t AB_Branchs[4] = {0, 0, 0, 0};
    uint8_t EF_Branchs[4] = {0, 0, 0, 0};
    uint8_t AB_Lengths[5] = {0, 0, 0, 0, 0};
    uint8_t EF_Lengths[5] = {0, 0, 0, 0, 0};
};

#endif