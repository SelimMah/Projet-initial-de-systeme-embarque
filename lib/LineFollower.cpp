

#include "LineFollower.h"

volatile bool timerExpired = false;

bool getsensor(Sensor sensor)
{
    switch (sensor)
    {
    case Sensor::s1:
        return (PINA & (1 << 6));
        break;

    case Sensor::s2:
        return (PINA & (1 << 5));
        break;

    case Sensor::s3:
        return (PINA & (1 << 4));
        break;

    case Sensor::s4:
        return (PINA & (1 << 3));
        break;

    case Sensor::s5:
        return (PINA & (1 << 2));
        break;

    default:
        return 0;
        break;
    }
}

bool getAllSensorOn()
{
    return (getsensor(s1) && getsensor(s2) && getsensor(s3) && getsensor(s4) && getsensor(s5));
}

bool getAllSensorOff()
{
    return (!getsensor(s1) && !getsensor(s2) && !getsensor(s3) && !getsensor(s4) && !getsensor(s5));
}

void convertToUint8(const uint16_t* input, uint8_t* output) 
{
    for (uint8_t i = 0; i < 4; ++i) {
        output[i] = static_cast<uint8_t>(input[i] & 0xFF); // Prend le premier octet
    }
}

//------------------------------------------------------------------------------------------

void LineFollower::setSpeed(uint8_t newSpeed)
{
    speed = newSpeed;
}

// Méthode pour la routine avec tous les capteurs activés
// Paramètres : Aucun
void LineFollower::allSensorOnRoutine()
{
    robot.driver.goForward(speed);
    _delay_ms(100);

    if (lastBifurcation)
    {
        lastDirecton = left;
    }
    else
    {
        lastBifurcation = right;
    }
}

// Méthode pour la routine avec tous les capteurs désactivés
// Paramètres : Aucun
void LineFollower::allSensorOffRoutine()
{
    // Déclaration des délais et durées d'impulsion
    const uint16_t delayAfterCorner = 450;
    const uint16_t delayStop = 500;
    const uint8_t impulseDelay = 20;

    // Mouvement en avant
    robot.driver.impulse(ImpluseDirection::RightStationary, impulseDelay);
    robot.driver.goForward(speed);
    _delay_ms(delayAfterCorner);

    // Détection de la dernière direction et ajustement du virage en conséquence
    if (lastDirecton == right)
    {
        robot.driver.impulse(ImpluseDirection::RightStationary, impulseDelay);
        while (!(getsensor(s3) || getsensor(s4) || getsensor(s2)))
        {
            robot.driver.turnRightStationary(speed - 3, speed - 5); // Correction
            lastDirecton = right;
        }
    }
    else
    {
        robot.driver.impulse(ImpluseDirection::LeftStationary, impulseDelay);
        while (!(getsensor(s3) || getsensor(s4) || getsensor(s2)))
        {
            robot.driver.turnLeftStationary(speed - 5, speed - 5); // Correction
            lastDirecton = left;
        }
    }

    // Arrêt du mouvement du robot
    robot.driver.stop();
    _delay_ms(delayStop);

    robot.driver.impulse(ImpluseDirection::Forward, impulseDelay);
}

// Méthode pour entrer dans une branche à droite
// Paramètres : Aucun
bool LineFollower::enterRightBranchingRoutine()
{
    // Déclaration des délais et durées d'impulsion
    const uint16_t delayRotation = 1000;
    const uint16_t timeRotation = 1700;
    const uint16_t delayStop = 400;
    const uint8_t impulseDelay = 32;

    timer.enableInterrupt(true);
    timer.startTimer(timeRotation);
    sei();

    robot.driver.impulse(ImpluseDirection::RightStationary, impulseDelay);
    robot.driver.turnRightStationary(speed, speed);
    _delay_ms(delayRotation);

    while (!timerExpired)
    {
        // DEBUG_MESSAGE("Je suis bloque \n");
        robot.driver.turnRightStationary(speed - 2, speed - 2);
        if ((getsensor(s3)) || getsensor(s4) || getsensor(s2))
        {
            robot.driver.stop();
            _delay_ms(delayStop);
            
            return true;
        }
    }

    timer.stopTimer();
    timer.enableInterrupt(false);
    cli();
    timerExpired = false;

    robot.driver.stop();
    _delay_ms(delayStop);

    return false;
}

// Méthode pour entrer dans une branche à gauche
// Paramètres : Aucun
void LineFollower::enterLeftBranchingRoutine()
{
    // Déclaration des délais et durées d'impulsion
    const uint16_t timeRotation = 300;
    const uint16_t delayStop = 400;
    const uint8_t impulseDelay = 40;

    robot.driver.stop();
    _delay_ms(delayStop);

    // Marche arrierre pour se positioner sur l'embranchement
    robot.driver.impulse(ImpluseDirection::LeftStationary, impulseDelay);

    while (!getAllSensorOff())
    {
        robot.driver.turnLeftStationary(speed - 10, speed + 5);
    }

    while (getAllSensorOff())
    {
        robot.led.red();

        robot.driver.turnLeftStationary(speed - 10, speed + 5);
        lastBifurcation = left;
    }

    robot.driver.stop();
    _delay_ms(delayStop);
}

// Méthode pour explorer une branche
// Paramètres : Aucun
void LineFollower::exploreBranchingRoutine()
{
    // Déclaration des délais et durées d'impulsion
    const uint16_t delayStop = 400;
    const uint8_t impulseDelay = 20;
    const uint8_t forwardDelay = 700;

    // Commencer à explorer l'embranchement
    robot.driver.impulse(ImpluseDirection::Forward, impulseDelay);
    robot.driver.goForward(speed);
    _delay_ms(forwardDelay);

    // Routine de suivi de ligne jusqu'a finir l'embranchement
    while (!getAllSensorOff())
    {
        robot.led.green();
        forwardLineFollwingRoutine();
        robot.led.red();
    }

    robot.driver.stop();
    _delay_ms(delayStop);
}

// Méthode pour finaliser une exploration de branche
// Paramètres :
//   - delayMS : Délai en millisecondes pour l'exécution de la routine de marche arrière
void LineFollower::endLongBranchingRoutine(uint16_t delayMS)
{
    // Déclaration des délais et durées d'impulsion
    const uint8_t impulseDelay = 20;
    const uint16_t delayStop = 400;
    const uint16_t delayComeBackStop = 600;

    // DEBUG_MESSAGE("Duree ; ");
    // DEBUG_VALUE(delayMS);

    // Marche arriere pour se repositionner
    BackwardLineRoutine(delayMS);

    robot.driver.stop();
    _delay_ms(delayStop);

    // Revenir sur le circuit principal en tournant à gauche
    robot.driver.impulse(ImpluseDirection::LeftStationary, impulseDelay);
    robot.driver.turnLeftStationary(speed, speed);
    _delay_ms(delayComeBackStop);

    while (getAllSensorOff())
    {
        robot.driver.turnLeftStationary(speed - 2, speed - 2);
        lastDirecton = left;
    }

    robot.driver.stop();
    _delay_ms(delayStop);

    robot.driver.impulse(ImpluseDirection::Forward, impulseDelay);
}

void LineFollower::endSmallBranchingRoutine()
{
    const uint8_t impulseDelay = 20;
    const uint16_t delayStop = 500;

    robot.driver.impulse(ImpluseDirection::LeftStationary, impulseDelay);

    while (!(getsensor(s3) || getsensor(s4) || getsensor(s2) || getsensor(s1) || getsensor(s5)))
    {
        robot.driver.turnLeftStationary(speed - 2, speed - 2);
        lastDirecton = left;
    }

    robot.driver.stop();
    _delay_ms(delayStop);

    robot.led.off();
}

void LineFollower::longBranchingRoutine()
{
    const uint8_t FCPU = 8000;
    const float cycleMsConvertion = 0.125;
    const uint16_t timeBackwardCorrection = 650;
    uint16_t branchingLength = 0;

    timer.enableInterrupt(true);
    timer.startChronos();
    sei();

    // Commencer l'exploration
    exploreBranchingRoutine();

    // Sauvegarder la longeur de l'embranchement
    branchingLength = timer.getTimerClock();
    uint16_t duree = (branchingLength * 1024) / FCPU;

    updateBranchList(determineBranchType(branchingLength));

    timer.stopTimer();
    timer.enableInterrupt(false);
    cli();
    timerExpired = false;

    // finir l'embranchement
    endLongBranchingRoutine((duree + timeBackwardCorrection));
}

uint8_t LineFollower::determineBranchType(uint16_t branchingLength)
{
    uint16_t averageLongBranch = 12000; //12500
    if (branchingLength >= averageLongBranch)
    {
        return longBranch;
    }
    return midBranch;
}

void LineFollower::updateBranchList(uint8_t branchType)
{
    if ((nCorner == 3) || (nCorner == 1))
    {
        Branchs[nBranch] = branchType;
    }
}

void LineFollower::updateLengthsList(uint16_t length)
{
    const float cycleMsConvertion = 0.125;
    const uint8_t speedValueInch = 3;
    const uint8_t speedValueMS = 950;

    length = (((length * cycleMsConvertion) * speedValueInch) / speedValueMS);

    if ((nCorner == 3) || (nCorner == 1))
    {
        Lengths[nBranch] = length;
        sumLengths += length;
    }
}

// Méthode pour la routine de virage à droite
// Paramètres : Aucun
void LineFollower::branchingRightRoutine()
{
    // Déclaration des délais et durées d'impulsion
    const uint8_t impulseDelay = 20;
    const uint16_t delayAfterBranching = 350 ;
    const uint8_t motorCorrection = 1;
    const uint16_t delayStop = 500;

    uint16_t mainLength = 0;

    // Mouvement pour depasser le virage
    robot.driver.turnForward(speed + motorCorrection, speed);
    _delay_ms(delayStop);

    // Vérification si il s'agit d'un corner ou d'un embranchement
    if (getAllSensorOff())
    {
        robot.led.green();

        mainLength = timer.getTimerClock();
        timer.stopTimer();
        timer.enableInterrupt(false);
        cli();
        timerExpired = false;
        updateLengthsList(mainLength);

        if (++nCorner == 3)
        {
            AB_nBranch = nBranch;
            nBranch = 0;

            Branchs = EF_Branchs;
            Lengths = EF_Lengths;
            AB_sumLengths = sumLengths;
            sumLengths = 0;
        }
        if (nCorner == 4)
        {
            EF_nBranch = nBranch;
            EF_sumLengths = sumLengths;
        }

        lastDirecton = 0;
        allSensorOffRoutine();

        timer.enableInterrupt(true);
        timer.startChronos();
        sei();

        robot.led.off();
    }
    else
    {
        robot.led.red();

        mainLength = timer.getTimerClock();
        timer.stopTimer();
        timer.enableInterrupt(false);
        cli();
        timerExpired = false;
        updateLengthsList(mainLength);

        robot.driver.goForward(speed);
        _delay_ms(delayAfterBranching);

        // Routine de suivi de ligne en avant après l'embranchement
        forwardLineFollwingRoutine(delayAfterBranching);

        robot.driver.stop();
        _delay_ms(delayStop);

        // Marche arrierre pour se positioner sur l'embranchement
        bool longBranch = enterRightBranchingRoutine();

        // Commencer le calcule de la longeur
        if (longBranch)
        {
            longBranchingRoutine();
            robot.led.off();
        }

        else
        {
            updateBranchList(Branch::smallranch);
            endSmallBranchingRoutine();
        }

        timer.enableInterrupt(true);
        timer.startChronos();
        sei();

        nBranch++;
    }
}

// Méthode pour la routine de virage à gauche
// Paramètres : Aucun
void LineFollower::branchingLeftRoutine()
{
    // Déclaration des délais et durées d'impulsion
    const uint16_t timerAfterBranching = 900;
    const uint16_t timeRotation = 700;
    const uint16_t delayStop = 400;
    const uint16_t delayAfterDetection = 750;
    const uint8_t motorCorrection = 1;

    // Mouvement pour depasser le virage
    robot.driver.turnForward(speed, speed + motorCorrection);
    _delay_ms(delayAfterDetection);

    robot.led.green();

    // Routine de suivi de ligne en avant après l'embranchement
    forwardLineFollwingRoutine(timerAfterBranching);

    // Marche arrierre pour se positioner sur l'embranchement
    enterLeftBranchingRoutine();

    // Routine de suivi de ligne jusqu'a finir l'embranchement
    while (!getAllSensorOff())
    {
        forwardLineFollwingRoutine();
    }

    // Arrêt du mouvement du robot
    robot.driver.stop();
    _delay_ms(delayStop);

    for (uint8_t i = 0; i < 5; i++)
    {
        AB_Lengths[i] = ((AB_Lengths[i] * 100) / AB_sumLengths);
        EF_Lengths[i] = ((EF_Lengths[i] * 100) / EF_sumLengths);
    }

    convertToUint8(AB_Lengths, AB_Lengths_uint8);
    convertToUint8(EF_Lengths, EF_Lengths_uint8);

    endLineFollowing = true;
    
}

// Méthode pour effectuer un petit ajustement vers la droite
// Paramètres : Aucun
void LineFollower::smallAdjustRightRoutine()
{
    robot.driver.turnForward(smallAdjustSpeedTwo, smallAdjustSpeedOne);
}

// Méthode pour effectuer un petit ajustement vers la gauche
// Paramètres : Aucun
void LineFollower::smallAdjustLeftRoutine()
{
    robot.driver.turnForward(smallAdjustSpeedOne, smallAdjustSpeedTwo);
}

// Méthode pour effectuer un grand ajustement vers la droite
// Paramètres : Aucun
void LineFollower::largeAdjustRightRoutine()
{
    robot.driver.turnForward(largeAdjustSpeedTwo, largeAdjustSpeedOne);
    lastDirecton = right;
}

// Méthode pour effectuer un grand ajustement vers la gauche
// Paramètres : Aucun
void LineFollower::largeAdjustLeftRoutine()
{
    robot.driver.turnForward(largeAdjustSpeedOne, largeAdjustSpeedTwo);
    lastDirecton = left;
}

// Méthode pour avancer
// Paramètres : Aucun
void LineFollower::forwardRoutine()
{
    robot.driver.goForward(speed);
}

// Méthode pour la routine de suivi de ligne en avant
// Paramètres :
//   - ignoreS5 : Indique si le capteur s5 doit être ignoré (par défaut: false)
void LineFollower::forwardLineFollwingRoutine(bool ignoreS5)
{
    if (getsensor(s4)) // si s4 actif est actif
    {
        smallAdjustRightRoutine();
    }
    else if (getsensor(s2)) // si s2 actif est actif
    {
        smallAdjustLeftRoutine();
    }
    else if (getsensor(s3)) // si s3 actif est actif
    {
        forwardRoutine();
    }

    else if (getsensor(s5) && !getsensor(s1)) // si s5 actif et pas s1
    {
        largeAdjustRightRoutine();
    }

    else if (getsensor(s1) && !getsensor(s5)) // si s1 actif et pas s5
    {
        largeAdjustLeftRoutine();
    }
}

// Méthode pour la routine de suivi de ligne en avant avec un délai spécifié
// Paramètres :
//   - delayMS : Délai en millisecondes pour l'exécution de la routine
void LineFollower::forwardLineFollwingRoutine(uint16_t delayMS)
{
    // Initialisation d'une instance de la classe Timer a
    timer.enableInterrupt(true);
    timer.startTimer(delayMS);
    sei();

    // Boucle pour suivre la ligne tant que le timer n'a pas expiré
    while (!timerExpired)
    {
        forwardLineFollwingRoutine(true);
    }

    // Arrêt du timer
    timer.stopTimer();
    timer.enableInterrupt(false);
    timerExpired = false;
}

// Méthode pour exécuter une routine de marche arrière sur la ligne pendant un délai spécifié
// Paramètres :
//   - delayMS : Délai en millisecondes pour l'exécution de la routine de marche arrière
void LineFollower::BackwardLineRoutine(uint16_t delayMS)
{
    // Déclaration du délai pour les impulsions
    const uint8_t impulseDelay = 20;

    robot.driver.impulse(ImpluseDirection::Backward, impulseDelay);
    for (uint16_t i = 0; i < delayMS; i++)
    {
        robot.driver.goBackward(speed);
        _delay_ms(1);
    }
}

void LineFollower::LineFollowerRoutine()
{
    if (getsensor(s3) && getsensor(s5)) // si s3 actif et s5 actif
    {
        // DEBUG_MESSAGE("Biffurcation a droite 35\n");
        branchingRightRoutine();
    }

    else if (getsensor(s3) && getsensor(s1)) // si s3 actif et s1 actif
    {
        // DEBUG_MESSAGE("Biffurcation a gauche \n");
        branchingLeftRoutine();
    }

    else if (getsensor(s4) || getAllSensorOn()) // si s4 actif
    {
        // DEBUG_MESSAGE("Un peu Doite broche 4\n");
        smallAdjustRightRoutine();
    }

    else if (getsensor(s2)) // si s2 actif
    {
        // DEBUG_MESSAGE("Un peu Gauche broche 6\n");
        smallAdjustLeftRoutine();
    }

    else if (getsensor(s5) && !getsensor(s1)) // si s5 actif et pas s1
    {
        // DEBUG_MESSAGE("Doite broche 3\n");
        largeAdjustRightRoutine();
    }

    else if (getsensor(s1) && !getsensor(s5)) // si s1 actif et pas s5
    {
        // DEBUG_MESSAGE("Gauche broche 7\n");
        largeAdjustLeftRoutine();
    }

    else if (getsensor(s3)) // si s3 actif
    {
        // DEBUG_MESSAGE("Devant\n");
        forwardRoutine();
    }

    else if (getAllSensorOff())
    { // si aucun
        allSensorOffRoutine();
    }
}


ISR(TIMER1_COMPA_vect)
{
    timerExpired = true;
}