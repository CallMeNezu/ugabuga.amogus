#include <iostream>
#include "windows.h" 
#include "TheChallengeOfPumping.h"
enum home_screen //создаём переменые для начального экрана
{
    PLAY = 112,
    QUIT = 113,
};
struct stats {//статистика
    char name[20];
    int heal;
    int strong;
    int charisma;
    int healing;
};
int main()
{
    char start;
    do {
        std::cout << "Welcome to our project" << std::endl;
        std::cout << "Play - p" << std::endl;
        std::cout << "quit - q" << std::endl;
        std::cin >> start;
        switch (start) {
        case PLAY: {//при вводе p нчинаеться диолог
            std::cout << "background....\n";
            Sleep(10);
            std::cout << ". ";
            Sleep(10);
            std::cout << ". ";
            Sleep(10);
            std::cout << ". \n";
            Sleep(10);
            std::cout << "Damn, I forgot...\n";
            Sleep(30);
            std::cout << "That's right! You fell into some kind of hole. \n";
            Sleep(20);
            std::cout << "Get out of here.\n";
            Sleep(75);
            std::cout << "The pancakes are getting cold at home.\n";
            break;
        }
        case QUIT: {//при вводе q выход и программа заканчиваеться
            return 0;
        }
        default:
            std::cout << "nope ";
        }
    } while (start != 'q' && start != 'p');

    std::cout << "\nwhat is your name?\n";//справшивают имя
    stats player;
    player.name;
    player.heal = 100;
    player.strong = 50;
    player.charisma = 25;
    player.healing = 25;
    std::cin >> player.name;
    int points = 99;
    std::cout << "check\n";
    interface_buttons(player.heal, player.strong, player.charisma, player.healing, points);//открытие прокачки по кнопке е и закрытие на кнопк r или при вводе q в прокачке 
    std::cout << "check";
}