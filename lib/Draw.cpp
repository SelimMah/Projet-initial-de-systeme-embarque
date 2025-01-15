

#include "Draw.h"

// Fonction pour initialiser le module de débogage (UART)
void Drawer::initPrint()
{
    uart.initialiseUART();
}

// Fonction pour imprimer un message de débogage sur l'UART.
// Paramètres :
//   - debugMessage : Un tableau de caractères contenant le message de débogage à imprimer.
//   - size : La taille du message de débogage à imprimer.
void Drawer::printCharacter(const char *character)
{
    while (*character)
    {
        uart.send(*character++);
    }
}

uint16_t Drawer::getCoordinate(uint8_t line, uint8_t column)
{
    return (line - 1) * nColumns + (column - 1);
}

void Drawer::writeCoordinate(uint8_t character, uint8_t line, uint8_t column)
{
    uint16_t address = getCoordinate(line, column);
    memory.ecriture(address, character);
    _delay_ms(2);
}

void Drawer::reset()
{
    for (uint8_t line = 1; line <= nLines; line++)
    {
        for (uint8_t column = 1; column <= nColumns; column++)
        {
            writeCoordinate(0, line, column);
        }
    }
}

void Drawer::doVerticalLine(uint8_t originColumn, uint8_t originLine, uint8_t lVertical)
{
    for (uint8_t i = originLine; i <= originLine + lVertical; i++)
    {
        writeCoordinate(keyVerticalBar, i, originColumn);
    }
}

void Drawer::doVerticalLine(uint8_t originColumn, uint8_t originLine, uint8_t lVertical, uint8_t key)
{
    for (uint8_t i = originLine; i <= originLine + lVertical; i++)
    {
        writeCoordinate(key, i, originColumn);
    }
}

void Drawer::doHorizontalLine(uint8_t originColumn, uint8_t originLine, uint8_t lHorizontal)
{
    for (uint8_t i = originColumn; i <= originColumn + lHorizontal; i++)
    {
        writeCoordinate(keyHorizontalBar, originLine, i);
    }
}

void Drawer::doHorizontalLine(uint8_t originColumn, uint8_t originLine, uint8_t lHorizontal, uint8_t key)
{
    for (uint8_t i = originColumn; i <= originColumn + lHorizontal; i++)
    {
        writeCoordinate(key, originLine, i);
    }
}

void Drawer::doUpperBand(uint8_t originColumn, uint8_t lVertical)
{
    uint8_t length = 0;
    switch (lVertical)
    {
    case 1:
        length = 2;
        break;
    case 2:
        length = 3;
        break;
    case 3:
        length = 5;
        break;
    default:
        break;
    }
    doVerticalLine(originColumn, (originLineCircuit + lVerticalCircuit) - length, length);
    writeCoordinate(keyTI, originLineCircuit + lVerticalCircuit, originColumn);
}

void Drawer::doLowerBand(uint8_t originColumn, uint8_t lVertical)
{
    uint8_t length = 0;
    switch (lVertical)
    {
    case 1:
        length = 2;
        break;
    case 2:
        length = 3;
        break;
    case 3:
        length = 5;
        break;
    default:
        break;
    }
    doVerticalLine(originColumn, originLineCircuit, length);
    writeCoordinate(keyT, originLineCircuit, originColumn);
}

void Drawer::doLeftBand(uint8_t originColumn, uint8_t originLine, uint8_t lHorizontal)
{
    doHorizontalLine(originColumn - lHorizontal, originLine, lHorizontal);
    writeCoordinate(keyTG, originLine, originColumn);
}

void Drawer::doRectangle(uint8_t originColumn, uint8_t originLine, uint8_t lHorizontal, uint8_t lVertical)
{
    doVerticalLine(originColumn, originLine, lVertical);
    doVerticalLine(originColumn + lHorizontal, originLine, lVertical);
    doHorizontalLine(originColumn, originLine, lHorizontal);
    doHorizontalLine(originColumn, originLine + lVertical, lHorizontal);

    writeCoordinate(keyTopLeftCorner, originLine, originColumn);
    writeCoordinate(keyBottomLeftCorner, originLine + lVertical, originColumn);
    writeCoordinate(keyTopRightCorner, originLine, originColumn + lHorizontal);
    writeCoordinate(keyBottomRightCorner, originLine + lVertical, originColumn + lHorizontal);

    doLeftBand(originColumn, originLine + lVertical / 2, 5);
}

void Drawer::doRectangle(uint8_t originColumn, uint8_t originLine, uint8_t lHorizontal, uint8_t lVertical, const uint8_t tab[])
{
    doVerticalLine(originColumn, originLine, lVertical, tab[0]);
    doVerticalLine(originColumn + lHorizontal, originLine, lVertical, tab[0]);
    doHorizontalLine(originColumn, originLine, lHorizontal, tab[1]);
    doHorizontalLine(originColumn, originLine + lVertical, lHorizontal, tab[1]);

    writeCoordinate(tab[2], originLine, originColumn);
    writeCoordinate(tab[4], originLine + lVertical, originColumn);
    writeCoordinate(tab[3], originLine, originColumn + lHorizontal);
    writeCoordinate(tab[5], originLine + lVertical, originColumn + lHorizontal);
}

void Drawer::readMem()
{
    Memoire24CXXX memory = Memoire24CXXX();
    uint8_t stock;
    for (uint16_t address = 0; address < nLines * nColumns; address++)
    {
        memory.lecture(address, &stock);
        _delay_ms(10);
        switch (stock)
        {
        case key::keyNothing:
            printCharacter(Nothing);
            break;
        case key::keyVerticalBar:
            printCharacter(VerticalBar);
            break;
        case key::keyHorizontalBar:
            printCharacter(HorizontalBar);
            break;
        case key::keyTopLeftCorner:
            printCharacter(TopLeftCorner);
            break;
        case key::keyTopRightCorner:
            printCharacter(TopRightCorner);
            break;
        case key::keyBottomLeftCorner:
            printCharacter(BottomLeftCorner);
            break;
        case key::keyBottomRightCorner:
            printCharacter(BottomRightCorner);
            break;
        case key::keyT:
            printCharacter(T);
            break;
        case key::keyTI:
            printCharacter(TI);
            break;
        case key::keyTG:
            printCharacter(TG);
            break;

        // Newly added keys
        case key::keyExternalBorderVerticalBar:
            printCharacter(ExternalBorderVerticalBar);
            break;
        case key::keyExternalBorderHorizontalBar:
            printCharacter(ExternalBorderHorizontalBar);
            break;
        case key::keyExternalBorderTopLeftCorner:
            printCharacter(ExternalBorderTopLeftCorner);
            break;
        case key::keyExternalBorderTopRightCorner:
            printCharacter(ExternalBorderTopRightCorner);
            break;
        case key::keyExternalBorderBottomLeftCorner:
            printCharacter(ExternalBorderBottomLeftCorner);
            break;
        case key::keyExternalBorderBottomRightCorner:
            printCharacter(ExternalBorderBottomRightCorner);
            break;
        case key::keyInternalBorderVerticalBar:
            printCharacter(InternalBorderVerticalBar);
            break;
        case key::keyInternalBorderHorizontalBar:
            printCharacter(InternalBorderHorizontalBar);
            break;
        case key::keyInternalBorderTopLeftCorner:
            printCharacter(InternalBorderTopLeftCorner);
            break;
        case key::keyInternalBorderTopRightCorner:
            printCharacter(InternalBorderTopRightCorner);
            break;
        case key::keyInternalBorderBottomLeftCorner:
            printCharacter(InternalBorderBottomLeftCorner);
            break;
        case key::keyInternalBorderBottomRightCorner:
            printCharacter(InternalBorderBottomRightCorner);
            break;

        case key::keyTopRightCornerRobot:
            printCharacter(TopRightRobot);
            break;
        case key::keyTopLeftCornerRobot:
            printCharacter(TopLeftRobot);
            break;
        case key::keyBottomRightCornerRobot:
            printCharacter(BottomRightRobot);
            break;
        case key::keyBottomLeftCornerRobot:
            printCharacter(BottomLeftRobot);
            break;
        case key::keyArrowRobot:
            printCharacter(ArrowRobot);
            break;
        case key::keyWheelRobot:
            printCharacter(WheelRobot);
            break;
        case key::keyArrowRobotBottom:
            printCharacter(ArrowRobotBottom);
            break;
        default:
            break;
        }

        if ((address + 1) % nColumns == 0)
        {
            printCharacter("\n");
        }
    }
}

void Drawer::drawRobot(uint8_t originLine)
{
    uint8_t originColumn = originColumnBox + (lHorizontalBox / 2) - 2;
    originLine = originLineBox + originLine;

    writeCoordinate(keyTopLeftCornerRobot, originLine, originColumn + 1);
    writeCoordinate(keyExternalBorderHorizontalBar, originLine, originColumn + 2);
    writeCoordinate(keyExternalBorderHorizontalBar, originLine, originColumn + 3);
    writeCoordinate(keyTopRightCornerRobot, originLine, originColumn + 4);

    writeCoordinate(keyExternalBorderVerticalBar, originLine + 1, originColumn + 1);
    writeCoordinate(keyArrowRobot, originLine + 1, originColumn + 2);
    writeCoordinate(keyArrowRobot, originLine + 1, originColumn + 3);
    writeCoordinate(keyExternalBorderVerticalBar, originLine + 1, originColumn + 4);
    writeCoordinate(keyWheelRobot, originLine + 2, originColumn + 1);
    writeCoordinate(keyWheelRobot, originLine + 2, originColumn + 4);

    writeCoordinate(keyBottomLeftCornerRobot, originLine + 3, originColumn + 1);
    writeCoordinate(keyBottomRightCornerRobot, originLine + 3, originColumn + 4);
    writeCoordinate(keyExternalBorderHorizontalBar, originLine + 3, originColumn + 2);
    writeCoordinate(keyExternalBorderHorizontalBar, originLine + 3, originColumn + 3);
}

void Drawer::drawRobotInverse(uint8_t originLine)
{
    uint8_t originColumn = originColumnBox + (lHorizontalBox / 2) - 2;
    originLine = originLineBox + lVerticalBox - originLine;

    writeCoordinate(keyBottomLeftCornerRobot, originLine + 3, originColumn + 1);
    writeCoordinate(keyExternalBorderHorizontalBar, originLine + 3, originColumn + 2);
    writeCoordinate(keyExternalBorderHorizontalBar, originLine + 3, originColumn + 3);
    writeCoordinate(keyBottomRightCornerRobot, originLine + 3, originColumn + 4);

    writeCoordinate(keyExternalBorderVerticalBar, originLine + 2, originColumn + 1);
    writeCoordinate(keyArrowRobotBottom, originLine + 2, originColumn + 2);
    writeCoordinate(keyArrowRobotBottom, originLine + 2, originColumn + 3);
    writeCoordinate(keyExternalBorderVerticalBar, originLine + 2, originColumn + 4);
    writeCoordinate(keyWheelRobot, originLine + 1, originColumn + 1);
    writeCoordinate(keyWheelRobot, originLine + 1, originColumn + 4);

    writeCoordinate(keyTopLeftCornerRobot, originLine, originColumn + 1);
    writeCoordinate(keyTopRightCornerRobot, originLine, originColumn + 4);
    writeCoordinate(keyExternalBorderHorizontalBar, originLine, originColumn + 2);
    writeCoordinate(keyExternalBorderHorizontalBar, originLine, originColumn + 3);
}

void Drawer::drawerOfArray(uint8_t trackArrayUp[5], uint8_t stripeArrayUp[4], uint8_t trackArrayBottom[5], uint8_t stripeArrayBottom[4])
{
    uint8_t nBandH = 0;
    uint8_t nBandB = 0;
    uint8_t vTempH = 0;
    uint8_t vTempB = 0;

    for (uint8_t i = 0; i < 4; i++)
    {
        if (stripeArrayUp[i] != 0)
        {
            nBandH++;
        }
        if (stripeArrayBottom[i] != 0)
        {
            nBandB++;
        }
    }

    doRectangle(1, 1, nColumns - 1, nLines - 1, externalBorder);
    doRectangle(originColumnCircuit, originLineCircuit, lHorizontalCircuit, lVerticalCircuit); // right
    doRectangle(originColumnBox, originLineBox, lHorizontalBox, lVerticalBox, internalBorder); // left
    doVerticalLine(originColumnBox + lHorizontalBox, originLineBox - 1 + lVerticalBox / 2, 3, keyNothing);

    for (uint8_t bandH = 0; bandH < nBandH; bandH++)
    {
        vTempH += (lHorizontalCircuit * trackArrayUp[bandH]) / 100;
        doLowerBand(originColumnCircuit + vTempH, stripeArrayUp[bandH]);
    }
    for (uint8_t bandB = 0; bandB < nBandB; bandB++)
    {
        vTempB += (lHorizontalCircuit * trackArrayBottom[bandB]) / 100;
        doUpperBand((originColumnCircuit + lHorizontalCircuit) - vTempB, stripeArrayBottom[bandB]);
    }

}

void Drawer::Signature()
{
    printCharacter("Produced by: Octane\n");
}
