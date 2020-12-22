/*
Игра "Быки и коровы".
*/

#include <iostream>
#include "bulls_and_cows.h"

int main()
{
    setlocale(LC_ALL, "Rus");
    // Запускаем игру
    BullsAndCows game;
    game.start_game();
}