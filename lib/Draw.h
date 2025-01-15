
#ifndef DRAW_H
#define DRAW_H

#define F_CPU 8000000

// Including necessary libraries
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
#include "memoire_24.h"

constexpr char Nothing[] = " ";
constexpr char VerticalBar[] = "\u2551";
constexpr char HorizontalBar[] = "\u2550";
constexpr char TopLeftCorner[] = "\u2554";
constexpr char TopRightCorner[] = "\u2557";
constexpr char BottomLeftCorner[] = "\u255A";
constexpr char BottomRightCorner[] = "\u255D";
constexpr char T[] = "\u2566";
constexpr char TI[] = "\u2569";
constexpr char TG[] = "\u2563";

constexpr char ExternalBorderVerticalBar[] = "\u2502";
constexpr char ExternalBorderHorizontalBar[] = "\u2500";
constexpr char ExternalBorderTopLeftCorner[] = "\u250C";
constexpr char ExternalBorderTopRightCorner[] = "\u2510";
constexpr char ExternalBorderBottomLeftCorner[] = "\u2514";
constexpr char ExternalBorderBottomRightCorner[] = "\u2518";

constexpr char InternalBorderVerticalBar[] = "\u2503";
constexpr char InternalBorderHorizontalBar[] = "\u2501";
constexpr char InternalBorderTopLeftCorner[] = "\u250F";
constexpr char InternalBorderTopRightCorner[] = "\u2513";
constexpr char InternalBorderBottomLeftCorner[] = "\u2517";
constexpr char InternalBorderBottomRightCorner[] = "\u251B";

constexpr char TopLeftRobot[] = "\u256D";
constexpr char TopRightRobot[] = "\u256E";
constexpr char BottomRightRobot[] = "\u256F";
constexpr char BottomLeftRobot[] = "\u2570";
constexpr char WheelRobot[] = "\u2593";
constexpr char ArrowRobot[] = "\u25B2";
constexpr char ArrowRobotBottom[] = "\u25BC";

// Array for the group of the external border
constexpr uint8_t externalBorder[] = {
    9, 10, 11, 12, 13, 14};

// Array for the group of the internal border
constexpr uint8_t internalBorder[] = {
    15, 16, 17, 18, 19, 20};

enum key
{
    keyNothing = 0,
    keyVerticalBar = 1,
    keyHorizontalBar = 2,
    keyTopLeftCorner = 3,
    keyTopRightCorner = 4,
    keyBottomLeftCorner = 5,
    keyBottomRightCorner = 6,
    keyT = 7,
    keyTI = 8,
    keyTG = 21,

    keyExternalBorderVerticalBar = 9,
    keyExternalBorderHorizontalBar = 10,
    keyExternalBorderTopLeftCorner = 11,
    keyExternalBorderTopRightCorner = 12,
    keyExternalBorderBottomLeftCorner = 13,
    keyExternalBorderBottomRightCorner = 14,

    keyInternalBorderVerticalBar = 15,
    keyInternalBorderHorizontalBar = 16,
    keyInternalBorderTopLeftCorner = 17,
    keyInternalBorderTopRightCorner = 18,
    keyInternalBorderBottomLeftCorner = 19,
    keyInternalBorderBottomRightCorner = 20,

    keyWheelRobot = 22,
    keyTopRightCornerRobot = 23,
    keyTopLeftCornerRobot = 24,
    keyBottomRightCornerRobot = 25,
    keyBottomLeftCornerRobot = 26,
    keyArrowRobot = 27,
    keyArrowRobotBottom = 28
};

class Drawer
{
public:
    Drawer() { uart.initialiseUART(); };

    void initPrint();
    void printCharacter(const char *character);

    uint16_t getCoordinate(uint8_t line, uint8_t column);
    void writeCoordinate(uint8_t character, uint8_t line, uint8_t column);

    void reset();

    void doVerticalLine(uint8_t originColumn, uint8_t originLine, uint8_t lVertical);
    void doVerticalLine(uint8_t originColumn, uint8_t originLine, uint8_t lVertical, uint8_t key);

    void doHorizontalLine(uint8_t originColumn, uint8_t originLine, uint8_t lHorizontal);
    void doHorizontalLine(uint8_t originColumn, uint8_t originLine, uint8_t lHorizontal, uint8_t key);

    void doUpperBand(uint8_t originColumn, uint8_t lVertical);
    void doLowerBand(uint8_t originColumn, uint8_t lVertical);
    void doLeftBand(uint8_t originColumn, uint8_t originLine, uint8_t lHorizontal);

    void doRectangle(uint8_t originColumn, uint8_t originLine, uint8_t lHorizontal, uint8_t lVertical);
    void doRectangle(uint8_t originColumn, uint8_t originLine, uint8_t lHorizontal, uint8_t lVertical, const uint8_t tab[]);

    void drawRobot(uint8_t originLine);
    void drawRobotInverse(uint8_t originLine);

    void readMem();
    void drawerOfArray(uint8_t trackArrayUp[4], uint8_t stripeArrayUp[3], uint8_t trackArrayBottom[4], uint8_t stripeArrayBottom[3]);
    void Signature();

    const uint8_t nColumns = 100;
    const uint8_t nLines = 26;
    const uint8_t originLineCircuit = 1 + nLines / 4;
    const uint8_t originColumnCircuit = nColumns / 2;
    const uint8_t lVerticalCircuit = nLines / 2;
    const uint8_t lHorizontalCircuit = (nColumns * 4) / 10;

    const uint8_t originLineBox = 1 + nLines / 6;
    const uint8_t originColumnBox = nColumns / 10;
    const uint8_t lVerticalBox = (nLines * 4) / 6;
    const uint8_t lHorizontalBox = 1 + (nColumns * 2) / 10;

    const uint8_t nLineH = 4;
    const uint8_t nLineB = 12;

    UART uart = UART();
    Memoire24CXXX memory = Memoire24CXXX();
};


#endif