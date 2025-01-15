
#include "IR_Transmission.h"


IRTransmitter::IRTransmitter() {
}

void IRTransmitter::init()
{
    DDRD |= (1 << PD5) | (1 << PD4);
    PORTD &= ~(1 << PD4);
    TCCR1A |= (1 << COM1A0);
    TCCR1B |= (1 << WGM12) | (1 << CS10);
    TCCR1C = 0;
    OCR1A = 104;
}

void IRTransmitter::sendDrawing(uint8_t AB_Branchs[4], uint8_t EF_Branchs[4], uint8_t AB_Lengths[5], uint8_t EF_Lengths[5]) 
{
    for (uint8_t i = 0; i < 4; i++) {
        generateSequence(AB_Branchs[i]);
    }
    for (uint8_t i = 0; i < 4; i++) {
        generateSequence(EF_Branchs[i]);
    }
    for (uint8_t i = 0; i < 5; i++) {
        generateSequence(AB_Lengths[i]);
    }
    for (uint8_t i = 0; i < 5; i++) {
        generateSequence(EF_Lengths[i]);
    }
}

void IRTransmitter::generateStart() 
{
    generateFrequency();
    _delay_us(2400);
    stopFrequency();
    _delay_us(600);
}

void IRTransmitter::generateBit(uint8_t val) 
{
    generateFrequency();
    switch (val) {
        case 1:
            _delay_us(1200);
            break;
        case 0:
            _delay_us(600);
            break;
        default:
            break;
    }
    stopFrequency();
    _delay_us(600);
}

void IRTransmitter::generateSequence(uint8_t val) 
{
    generateStart();
    uint8_t crc = _crc16_update(0xFFFF, val & 0x7F);
    for (uint8_t i = 0; i < 5; i++) {
        generateBit((crc >> (4 - i)) & 0x01);
    }
    for (uint8_t i = 0; i < 7; i++) {
        generateBit((val >> (6 - i)) & 0x01);
    }
}

void IRTransmitter::generateFrequency() 
{
    TCCR1A |= (1 << COM1A0);
}

void IRTransmitter::stopFrequency() {
    TCCR1A &= ~(1 << COM1A0);
}
