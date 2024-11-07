#pragma once
#include <iostream>
#include "windows.h"


void interface_buttons(string name, int& MaxHealth, int& a, int& b, int& c, int& d, int& p) {//а - здоровье. б - сила. с - харизма. д - лечение. p - очки прокачки
    while (true) {
        system("CLS");

        char plus_point_to_a_specific_stat = ' ';
        std::cout << "enter 'h' to give a health point\n";
        std::cout << "enter 'j' to give a strong point\n";
        std::cout << "enter 'k' to give a charisma point\n";
        std::cout << "enter 'l' to give a healing point\n";
        std::cout << "press 'q' to exit\n";

        std::cout << "\n - * - * - "<< endl<<endl;

        std::cout << "Name: " << name << endl;
        std::cout << "Health: " << MaxHealth << " / " << a << endl;
        std::cout << "Strength: " << b << endl;
        std::cout << "Charism: " << c << endl;
        std::cout << "Heal: " << d << endl<<endl;

        std::cout << "Your Points: " << p << endl;
        std::cin >> plus_point_to_a_specific_stat;

        if (plus_point_to_a_specific_stat == 'q') {
            break;
        }
        if (plus_point_to_a_specific_stat == 'h') {
            if (p > 0) {
                std::cout << "+ 25 to health";
                MaxHealth += 25;
                a += 25;
                p--;
            }
            else {
                std::cout << "Not enough points";
            }
        }
        else if (plus_point_to_a_specific_stat == 'j') {
            if (p > 0) {
                std::cout << "+ 15 to strength";
                b += 15;
                p--;
            }
            else {
                std::cout << "Not enough points";
            }
        }
        else if (plus_point_to_a_specific_stat == 'k') {
            if (p > 0) {
                std::cout << "+ 15 to charisma";
                c += 15;
                p--;
            }
            else {
                std::cout << "Not enough points";
            }
        }
        else if (plus_point_to_a_specific_stat == 'l') {
            if (p > 0) {
                std::cout << "+ 15 to treatment";
                d += 15;
                p--;
            }
            else {
                std::cout << "Not enough points";
            }
        }
        else {
            continue;
        }
        Sleep(2000);
    }
}