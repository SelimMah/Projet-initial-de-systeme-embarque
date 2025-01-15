
#include "Debug.h"
#include <util/crc16.h>
#include <avr/io.h>
#include <util/crc16.h>
#include <util/delay.h>


class IRTransmitter {
public:
    IRTransmitter();

    void init();

    void sendDrawing(uint8_t AB_Branchs[4], uint8_t EF_Branchs[4], uint8_t AB_Lengths[5], uint8_t EF_Lengths[5]);

    void generateStart();

    void generateBit(uint8_t val);

    void generateSequence(uint8_t val);

    void generateFrequency();

    void stopFrequency();
};
