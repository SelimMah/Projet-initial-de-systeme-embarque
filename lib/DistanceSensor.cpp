/*
 * Nom: Button.cpp
 * Auteurs: Selim-Mahjoub-2193614, 
 *          Mohamed-Afandi-2291005, 
 *          Bryan Alexandre Tavares-2291297 
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Implémentation de la classe Button de la Librairie
*/
#include "DistanceSensor.h"



uint8_t DistanceSensor::lireData()
{
    while (PIND & (1 << PD3)){} // RAISING
    uint16_t compteur = 0;
    while (!(PIND & (1 << PD3)))
    {
        compteur++;
        _delay_us(50);
    } // FALLING

    if (compteur <= 15)
    {
        return 0;
    }
    
    else if (compteur <= 35)
    {
        return 1;
    }

    else   
    {
        return 2;
    }
}

void DistanceSensor::recupererDonnee(uint8_t tab[])
{
    while (lireData() != 2){}
    for (uint8_t i = 12; i > 0; i--)
    {
        tab[i - 1] = lireData();
    }
}

void DistanceSensor::afficherDonnee(uint8_t tab[])
{
    for (uint8_t i = 0; i < 12; i++)
    {
        DEBUG_VALUE(tab[i]);
    }
    DEBUG_MESSAGE("\n");
}

uint8_t DistanceSensor::valeurDonnee(uint8_t tab[])
{
    uint8_t result = 0;
    for (uint8_t i = 0; i < 7; i++) 
    {
        result |= tab[i] << i;
    }
    return result;
}

uint8_t DistanceSensor::crcDonnee(uint8_t tab[])
{
    uint8_t result = 0;
    for (uint8_t i = 0; i < 5; i++) 
    {
        result |= tab[i+7] << i;
    }
    return result;
}

bool DistanceSensor::verifierDonnee(uint8_t Donnee, uint8_t crcDonnee)
{
    return (_crc16_update(0xFFFF, Donnee) & (0x1F)) == crcDonnee;
}

bool DistanceSensor::ReceiveDrawing(uint8_t* AB_Branchs, uint8_t* EF_Branchs, uint8_t* AB_Lengths, uint8_t* EF_Lengths)
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


DistanceSensor::DistanceSensor(Robot &robot, can &distance) : robot(robot),
                                                             distance(distance) {}

//------------------------------------------------------------------------------------------

// Méthode pour diriger le Robot 1 vers le point rouge (le milieu de la boite)
// Paramètres :
// - detectionSurface: Indique la valeur que le capteur de distance détecte
// - state: Une variable de type Cage nous permettant de faire le changement d'état.
void DistanceSensor::mouvementWall(uint16_t &detectionSurface, Cage &state)
{
    uint8_t const wallFar = 51;
    uint8_t const perfectDistance = 48;
    uint8_t const wallClose = 100;

    if (detectionSurface < perfectDistance)
    {
        robot.driver.goForward(forwardSpeed);
        _delay_ms(400);
    }

    else if (detectionSurface > wallClose || (detectionSurface < wallClose && detectionSurface > wallFar))
    {
        robot.driver.turnBackward(backwardSpeedRight, backwardSpeedLeft);
        _delay_ms(400);
    }

    else if ((detectionSurface > perfectDistance) && (detectionSurface < wallFar))
    {
        robot.driver.stop();
        _delay_ms(1500);
        state = Cage::SWEEPING;
    }
}

// Méthode pour tourner le Robot 1 jusqu'à ce qu'il trouve la porte
// Paramètres :
// - detectionSurface: Indique la valeur que le capteur de distance détecte.
void DistanceSensor::findDoor(uint16_t &detectionSurface, uint8_t &tempDeBalayage)
{
    uint16_t tempDeBalayage2  = 0;
    uint8_t const extremum1   = 15;
    uint8_t const extremum2   = 0;
    uint8_t const ajustement  = 40;

    while (detectionSurface > extremum1 || detectionSurface < extremum2)
    {
        _delay_ms(400);
        robot.driver.turnRightStationary(leftMotorSpeed + ajustement + 5, rightMotorSpeed + ajustement);
        _delay_ms(120);
        robot.driver.stop();
        _delay_ms(400);
        detectionSurface = (distance.lecture(0) >> 2);
        tempDeBalayage2++;
    }
    robot.driver.stop();
}

// Méthode pour jouer une note lorsque le bouton est pressé
// Paramètres :
// - note: La note à jouer
void DistanceSensor::musicBouton(uint8_t note)
{
    Button button(false, Edge::ANY);
    if (button.debounceButton())
    {
        for (int i = 0; i < 3; ++i)
        {
            robot.sing.noteSing(note);
            _delay_ms(50);
            robot.sing.stopSing();
            _delay_ms(50);
        }
    }
}

// Initialise les paramètres du timer ISR pour la fréquence
void DistanceSensor::initTimerISR()
{
    DDRD |= 1 << PD5 | 1 << PD4;
    PORTD &= ~(1 << PD4);

    TCCR1A |= (1 << COM1A0);
    TCCR1B |= (1 << WGM12 | 1 << CS10 | 1 << CS12);
    TCCR1C = 0;
    TCCR1B &= ~(1 << CS11);

    OCR1A = 1563;
}

// Génère la fréquence
void DistanceSensor::genererFrequence()
{
    TCCR1A |= (1 << COM1A0);
}

// Arrête la génération de fréquence
void DistanceSensor::arreterFrequence()
{
    TCCR1A &= ~(1 << COM1A0);
}


// Méthode pour dessiner la trajectoire du robot
// Paramètres :
// - AB_Lengths: Tableau de la voie supérieure
// - AB_Branchs: Tableau de la piste supérieure
// - EF_Lengths: Tableau de la voie inférieure
// - EF_Branchs: Tableau de la piste inférieure
// - drawer: Objet Drawer pour dessiner
// - distanceSensor: Objet DistanceSensor pour l'accès aux méthodes
// - state: Une variable de type Cage pour le changement d'état.
void DistanceSensor::drawing(uint8_t AB_Lengths[4], uint8_t AB_Branchs[4], uint8_t EF_Lengths[5], uint8_t EF_Branchs[5], Drawer drawer, DistanceSensor distanceSensor, uint16_t &moyennePosition, uint8_t &tempDeBalayage)
{
    uint8_t const percent             = 100;
    uint8_t const sweepingTime        = 20;
    uint8_t const robotRightBottom    = 13;
    uint8_t const robotReverseBottom  = 4;
    uint8_t const robotRightTop       = 14;
    uint8_t const robotReverseTop     = 2;

    distanceSensor.initTimerISR();
    distanceSensor.genererFrequence();
   
    robot.led.green();
    
    drawer.reset();
    drawer.drawerOfArray(AB_Lengths, AB_Branchs, EF_Lengths, EF_Branchs);

    if (moyennePosition < percent && tempDeBalayage < sweepingTime)
    {
        drawer.drawRobot(robotRightBottom);
    }

    else if (moyennePosition > percent && tempDeBalayage > sweepingTime)
    {
        drawer.drawRobotInverse(robotReverseBottom);
    }

    else if (moyennePosition < percent && tempDeBalayage > sweepingTime)
    {
        drawer.drawRobotInverse(robotRightTop);
    }

    else if (moyennePosition > percent && tempDeBalayage < sweepingTime)
    {
        drawer.drawRobot(robotReverseTop);
    }
    drawer.readMem();
    drawer.Signature();

    distanceSensor.arreterFrequence();
}

// Méthode pour parcourir le Robot 1 dans la cage
// Paramètres :
// - detectionSurface: Indique la valeur que le capteur de distance détecte
// - button: Objet Button pour l'interaction avec le bouton
// - distanceSensor: Objet DistanceSensor pour l'accès aux méthodes
// - drawer: Objet Drawer pour dessiner
// - state: Une variable de type Cage pour le changement d'état.
// - isPositionFind: Indicateur pour trouver la position
// - moyennePosition: Moyenne de la position
// - tempDeBalayage: Temporisation de balayage
void DistanceSensor::parcoursR1(uint16_t detectionSurface, Button button, DistanceSensor distanceSensor, Drawer drawer, Cage &state, uint8_t &isPositionFind, uint16_t &moyennePosition, uint8_t &tempDeBalayage)
{
    uint8_t const extremum1 = 15;
    uint8_t const extremum2 = 0;
    uint8_t const percent = 100;
    uint8_t const sweepingTime = 20;
    uint8_t isPositionFind2 = 0;

    bool donneesValides = true;

    while (isPositionFind2 <= 5)
    {
        detectionSurface = (distanceSensor.distance.lecture(0) >> 2);
        moyennePosition += detectionSurface;
        isPositionFind2++;
    }
    moyennePosition = ((moyennePosition / 5) * 100) / 48;

    while (true)
    {
        switch (state)
        {
        case Cage::FIND_DISTANCE:
            detectionSurface = (distanceSensor.distance.lecture(0) >> 2);
            distanceSensor.mouvementWall(detectionSurface, state);
            break;

        case Cage::SWEEPING:
            detectionSurface = (distanceSensor.distance.lecture(0) >> 2);
            distanceSensor.findDoor(detectionSurface, tempDeBalayage);
            state = Cage::WAITING;
            break;

        case Cage::WAITING:
            robot.driver.stop();
            while (true)
            {
                robot.led.red();
                distanceSensor.musicBouton(80);
                detectionSurface = (distanceSensor.distance.lecture(0) >> 2);

                if (detectionSurface > 50)
                {
                    state = Cage::RECEPTIONIR;
                    break;
                }
            }
            break;

        case Cage::RECEPTIONIR:
            robot.led.off();
            donneesValides = distanceSensor.ReceiveDrawing(AB_Branchs, EF_Branchs, AB_Lengths, EF_Lengths);

            if(donneesValides)
            {
                for (uint8_t i = 0; i < 4; ++i)
                {
                    DEBUG_VALUE(AB_Branchs[i]);
                }

                for (uint8_t i = 0; i < 4; ++i)
                {
                    DEBUG_VALUE(EF_Branchs[i]);
                }

                for (uint8_t i = 0; i < 5; ++i)
                {
                    DEBUG_VALUE(AB_Lengths[i]);
                }

                for (uint8_t i = 0; i < 5; ++i)
                {
                    DEBUG_VALUE(EF_Lengths[i]);
                }

                state = Cage::RS_232;
            }

            else
            {
                state = Cage::WAITING;
            }
            break;

        case Cage::RS_232:
            while (true)
            {
                robot.led.green();

                if (button.debounceButton())
                {
                    distanceSensor.drawing(AB_Lengths, AB_Branchs, EF_Lengths, EF_Branchs, drawer, distanceSensor, moyennePosition, tempDeBalayage);
                    state = Cage::RS_232;
                    break;
                }
            }
        }
    }
}