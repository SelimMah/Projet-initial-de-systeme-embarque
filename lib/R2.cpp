

#include "R2.h"

void R2::LED5Hz232()
{
    PORTD |= (1 << PD6) | (1 << PD4);
    DDRD |= (1 << PD4) | (1 << PD6);

    TCCR1A |= (1 << COM1B0);
    TCCR1B |= (1 << WGM12 | 1 << CS12);
    TCCR1C = 0;

    OCR1A = 3125;
}

void R2::stopLED()
{
    DDRD &= ~(1 << PD4) & ~(1 << PD2);

    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1C = 0;

    OCR1A = 0;
}

void R2::parcourRoutine()
{
    DDRD = 0xFF; // Timer
    DDRC = 0xFF; // Memoire Externe / boutton
    DDRB = 0xFF; // Moteurs
    DDRA = 0x00; // Capteurs de lignes

    lineFollower.setSpeed(39);
    lineFollower.robot.driver.impulse(ImpluseDirection::Forward, 40);

    while (!lineFollower.endLineFollowing)
    {
        lineFollower.LineFollowerRoutine();
    }
    state = R2State::Waiting;
}

void R2::waitingRoutine()
{
    DDRD = 0xFF & ~(1 << PD2); // Bouton
    DDRC = 0x00;               // Bouton Externe
    DDRB = 0x00;               // Moteurs
    DDRA = 0x00;

    TCCR1A = 0; // Remise a zero du Timer 1
    TCCR1B = 0; // Remise a zero du Timer 1

    waitingLed.red();

    while (state == R2State::Waiting)
    {
        if (!(PINC & (1 << 7)))
        {
            state = R2State::SendRS232;
            break;
        }

        else if (PIND & (1 << 2))
        {
            state = R2State::SendIR;
            break;
        }
    }
}

void R2::sendIR_Routine()
{
    DDRD = 0xFF & ~(1 << PD2); // Bouton
    DDRC = 0x00;               // Bouton Externe
    DDRB = 0x00;               // Moteurs
    DDRA = 0x00;

    waitingLed.off();

    const uint16_t frequency = 800;
    const uint8_t stopDelay = 50;

    for (uint8_t i = 0; i < 3; i++)
    {
        sing.frequencySing(frequency);
        _delay_ms(stopDelay);
        sing.stopSing();
        _delay_ms(stopDelay);
    }
    DDRD = 0xFF & ~(1 << PD7); // Bouton

    IRTransmission.init();
    IRTransmission.sendDrawing(lineFollower.AB_Branchs, lineFollower.EF_Branchs, lineFollower.AB_Lengths_uint8, lineFollower.EF_Lengths_uint8);

    state = R2State::Waiting;
}

void R2::sendRS232Routine()
{
    LED5Hz232();
    waitingLed.green();

    drawer.reset();
    drawer.drawerOfArray(lineFollower.AB_Lengths_uint8, lineFollower.AB_Branchs, lineFollower.EF_Lengths_uint8, lineFollower.EF_Branchs);
    drawer.readMem();

    stopLED();

    state = R2State::Waiting;
}
