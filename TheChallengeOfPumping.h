#pragma once
#include <iostream>
#include "windows.h"
void interface_buttons(int& a, int& b, int& c, int& d, int& p) {//� - ��������. � - ����. � - �������. � - �������. p - ���� ��������
    bool click = false;
    char plus_point_to_a_specific_stat;
    while (click == true) {
        if (GetAsyncKeyState('e')) //���������� �� ������ � ������������  
        {
            click = true;
        }
        else if (GetAsyncKeyState('r')) //��� ������� �� r ������������ 
        {
            click = false;
        }
        if (click == true) {
            std::cout << "enter 'h' to give a health point\n";
            std::cout << "enter 'j' to give a strong point\n";
            std::cout << "enter 'k' to give a charisma point\n";
            std::cout << "enter 'l' to give a healing point\n";
            std::cout << "press 'q' to exit\n";
            std::cin >> plus_point_to_a_specific_stat;
            if (plus_point_to_a_specific_stat == 'q') {//����� ��� ����� q 
                break;
            }
            if (plus_point_to_a_specific_stat == 'h') {//�������� ��� ����� ��� ����� ��� ����� 
                if (p > 0) {
                    std::cout << "+ 25 to health";
                    a += 25;
                    p--;
                }
                else {
                    std::cout << "Not enough points";
                }
            }
            if (plus_point_to_a_specific_stat == 'j') {
                if (p > 0) {
                    std::cout << "+ 15 to strength";
                    b += 15;
                    p--;
                }
                else {
                    std::cout << "Not enough points";
                }
            }
            if (plus_point_to_a_specific_stat == 'k') {
                if (p > 0) {
                    std::cout << "+ 15 to charisma";
                    c += 15;
                    p--;
                }
                else {
                    std::cout << "Not enough points";
                }
            }
            if (plus_point_to_a_specific_stat == 'l') {
                if (p > 0) {
                    std::cout << "+ 15 to treatment";
                    d += 15;
                    p--;
                }
                else {
                    std::cout << "Not enough points";
                }
            }
        }
    }
}