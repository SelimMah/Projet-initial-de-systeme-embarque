/*
 * Nom: R1
 * Auteurs: Selim-Mahjoub-2193614,
 *          Mohamed-Afandi-2291005,
 *          Bryan Alexandre Tavares-2291297
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Implémentation de R1 les branchements sont spécifiés dans le lisermoi.txt
*/

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Inclusion des bibliothèques nécessaires

#include "DistanceSensor.h"

int main()
{
    DDRD = 0xF3;
    DDRC = 0xFF;
    DDRB = 0xFF;
    DDRA = 0x00;

    Cage state = Cage::FIND_DISTANCE;
    Robot robot;
    can distance;
    Drawer drawer;
    Button button(false, Edge::ANY);

    robot.setLed(PortSelection::PORT_D, 5, 6);

    DistanceSensor distanceSensor(robot, distance);

    uint16_t detectionSurface;

    detectionSurface = (distanceSensor.distance.lecture(0) >> 2);

    DEBUG_INIT();

    uint8_t tempDeBalayage   = 0;
    uint8_t isPositionFind   = 0;
    uint16_t moyennePosition = 0;

    distanceSensor.parcoursR1(detectionSurface, button, distanceSensor, drawer, state, isPositionFind, moyennePosition, tempDeBalayage);
}