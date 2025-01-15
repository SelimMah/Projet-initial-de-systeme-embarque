/*
 * Nom: R2
 * Auteurs: Selim-Mahjoub-2193614,
 *          Mohamed-Afandi-2291005,
 *          Bryan Alexandre Tavares-2291297
 *          Brice Tangmouo Manfo-2275762
 * Groupe 04 / Equipe 09394
 * Description: Implémentation de R2 les branchements sont spécifiés dans le lisermoi.txt
*/

#include "R2.h"

int main()
{
    DDRD = 0x00; // Haut-Parleura
    DDRC = 0xFF; // Memoire Externe
    DDRB = 0xFF; // Moteurs
    DDRA = 0x00; // LED + Capteur de lignes

    DEBUG_INIT();

    R2 robot2;
    robot2.state = R2State::Parcour;

    while (1)
    {
        switch (robot2.state)
        {
        case R2State::Parcour:
            robot2.parcourRoutine();
            break;

        case R2State::Waiting:
            robot2.waitingRoutine();
            break;

        case R2State::SendIR:
            robot2.sendIR_Routine();
            break;

        case R2State::SendRS232:
            robot2.sendRS232Routine();
            break;

        default:
            break;
        };
    }
};