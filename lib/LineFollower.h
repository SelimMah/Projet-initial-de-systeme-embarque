/*
 * Nom: LineFollower.h
 * Auteurs: Selim-Mahjoub-2193614, 
 *          Mohamed-Afandi-2291005, 
 *          Bryan Alexandre Tavares-2291297 
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Classe LineFollower de la Librairie 
 */

#ifndef LINE_FOLLOWER_H
#define LINE_FOLLOWER_H

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

// #define F_CPU 8000000

#define F_CPU 8000000

// Inclusion des bibliothèques nécessaires
#include <avr/io.h>
#include <util/delay.h>

#include "Debug.h"

#include "LED.h"
#include "Driver.h"
#include "Robot.h"
#include "Timer.h"
#include "can.h"
#include "memoire_24.h"

//--------------------------------------------------------------
enum Sensor
{
    s1,
    s2,
    s3,
    s4,
    s5
};

enum Direction
{
    right = 0,
    left = 1,
};

enum Branch
{
    smallranch = 1,
    midBranch = 2,
    longBranch = 3,
};

class LineFollower
{
public:
    // Constructeurs--------------------------------------------------

    LineFollower(){};

    // Methodes--------------------------------------------------

    void setSpeed(uint8_t newSpeed);

    void allSensorOnRoutine();
    void allSensorOffRoutine();

    bool enterRightBranchingRoutine();
    void enterLeftBranchingRoutine();

    void exploreBranchingRoutine();

    void endLongBranchingRoutine(uint16_t delayMS);
    void endSmallBranchingRoutine();
    void longBranchingRoutine();

    uint8_t determineBranchType(uint16_t branchingLength);
    void updateBranchList(uint8_t branchType);
    void updateLengthsList(uint16_t length);

    void branchingRightRoutine();
    void branchingLeftRoutine();

    void smallAdjustRightRoutine();
    void smallAdjustLeftRoutine();

    void largeAdjustRightRoutine();
    void largeAdjustLeftRoutine();

    void forwardRoutine();

    void forwardLineFollwingRoutine(uint16_t delayMS);
    void forwardLineFollwingRoutine(bool ignoreS5 = false);

    void BackwardLineRoutine(uint16_t delayMS);
    void LineFollowerRoutine();

    Memoire24CXXX memory;
    Robot robot;
    Timer timer = Timer(TimerNumber::Timer_1, 1024);

    uint8_t speed = 45;
    uint8_t smallAdjustSpeedOne = (speed + 5);
    uint8_t smallAdjustSpeedTwo = (speed - 8);

    uint8_t largeAdjustSpeedOne = (speed + 20);
    uint8_t largeAdjustSpeedTwo = (speed - 13);

    bool lastBifurcation = 0;
    bool lastDirecton = 0;

    uint8_t nCorner = 0;

    uint8_t AB_nBranch = 0;
    uint8_t EF_nBranch = 0;
    uint8_t nBranch = AB_nBranch;

    uint8_t AB_Branchs[4] = {0, 0, 0, 0};
    uint8_t EF_Branchs[4] = {0, 0, 0, 0};
    uint8_t *Branchs = AB_Branchs;

    uint16_t AB_Lengths[5] = {0, 0, 0, 0, 0};
    uint16_t EF_Lengths[5] = {0, 0, 0, 0, 0};
    uint16_t *Lengths = AB_Lengths;

    uint8_t AB_Lengths_uint8[5]; 
    uint8_t EF_Lengths_uint8[5];

    uint16_t sumLengths = 0;
    uint16_t AB_sumLengths = 0;
    uint16_t EF_sumLengths = 0;

    bool endLineFollowing = false;
};


#endif