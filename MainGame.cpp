#define _CRT_SECURE_NO_WARNINGS

using namespace std;
#include "Upgrade.h" // Мишен код: инвентарь / характериситики

#include <iostream>
#include <string.h>
#include <string>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
//----------------------------------------------------------------------------------------------------------------------------------------------------------
enum home_screen
{
    PLAY = 112,
    QUIT = 113,
};

class Player {
public:
    std::string name;
    int MaxHealth = 100;
    int health = 100;
    int strong = 10;
    int charisma = 25;
    int healing = 25;
    


    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }

    bool isAlive() {
        return health > 0;
    }
};

//----------------------------------------------------------------------------------------------------------------------------------------------------------
const int MAX_Y_VIEV = 120; // 237 строки
const int MAX_X_VIEV = 40; // 67 столбы
const int Fields = 3; // 3 * 3
const int MAX_X = MAX_X_VIEV * Fields;
const int MAX_Y = MAX_Y_VIEV * Fields;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

class Enemy {
public:
    std::string name;
    int health;

    Enemy(std::string enemyName) : name(enemyName), health(50) {}

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }

    bool isAlive() {
        return health > 0;
    }
};

void encounte(Player& player, Enemy& enemy) {
    std::cout << "You encountered a " << enemy.name << "!\n";

    while (player.isAlive() && enemy.isAlive()) {
        std::cout << "HP: " << player.MaxHealth<<" / " << player.health << "\n";
        std::cout << enemy.name << "'s health: " << enemy.health << "\n";

        std::cout << "Choose an action:\n1. Attack\n2. Heal\n";
        int action;
        std::cin >> action;

        if (action == 1) {
            int damage = player.strong + rand() % (player.strong/3);
            enemy.takeDamage(damage);

            std::cout << "You attacked " << enemy.name << " for " << damage << " damage!\n";
        }
        else if (action == 2) {
            player.health += player.healing;
            if (player.health > player.MaxHealth) {
                player.health = player.MaxHealth;
            }

            std::cout << "You healed for " << player.healing << " health!\n";
        }

        if (enemy.isAlive()) {
            int enemyDamage = rand() % 15 + 5;
            player.takeDamage(enemyDamage);
            std::cout << enemy.name << " attacked you for " << enemyDamage << " damage!\n";
        }
    }

    if (player.isAlive()) {
        std::cout << "You defeated " << enemy.name << "!\n";
    }
    else {
        std::cout << "You were defeated...\n";
    }
}

void cls()
{
    // Get the Win32 handle representing standard output.
    // This generally only has to be done once, so we make it static.
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = { 0, 0 };

    // std::cout uses a buffer to batch writes to the underlying console.
    // We need to flush that to the console because we're circumventing
    // std::cout entirely; after we clear the console, we don't want
    // stale buffered text to randomly be written out.
    std::cout.flush();

    // Figure out the current width and height of the console window
    if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
        // TODO: Handle failure!
        abort();
    }
    DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

    DWORD written;

    // Flood-fill the console with spaces to clear it
    FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

    // Reset the attributes of every character to the default.
    // This clears all background colour formatting, if any.
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

    // Move the cursor back to the top left for the next sequence of writes
    SetConsoleCursorPosition(hOut, topLeft);
}

// x is the column, y is the row. The origin (0,0) is top-left.
void setCursorPosition(int x, int y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}
void ClearArray(char Arr[][MAX_X_VIEV]) {
    for (int y = 0; y < MAX_Y_VIEV; y++)
    {
        for (int x = 0; x < MAX_X_VIEV; x++)
        {
            Arr[y][x] = ' ';
        }
    }
}

void player_movement(int& posX, int& posY) {
    if (GetKeyState('W') & 0x8000)
    {
        posX--;
    }
    if (GetKeyState('S') & 0x8000)
    {
        posX++;
    }

    if (GetKeyState('A') & 0x8000)
    {
        posY--;
    }
    if (GetKeyState('D') & 0x8000)
    {
        posY++;
    }
}
bool ChangeMap(int& posX, int& posY, int& Viev_X, int& Viev_Y) {
    bool change = false;
    if (posX < 0 && Viev_X > 0) { // вверх //
        posX = MAX_X_VIEV - 1;
        Viev_X -= MAX_X_VIEV;
        change = true;
    }
    else if (posX < 0)
    {
        posX = 0;
    }

    if (posX >= MAX_X_VIEV && Viev_X + MAX_X_VIEV < MAX_X) { // вниз //
        posX = 0;
        Viev_X += MAX_X_VIEV;
        change = true;
    }
    else if (posX >= MAX_X_VIEV)
    {
        posX = MAX_X_VIEV - 1;
    }

    if (posY >= MAX_Y_VIEV - 1 && Viev_Y + MAX_Y_VIEV < MAX_Y) { // направо
        posY = 0;
        Viev_Y += MAX_Y_VIEV;
        change = true;
    }
    else if (posY >= MAX_Y_VIEV - 1)
    {
        posY = MAX_Y_VIEV - 2;
    }

    if (posY < 0 && Viev_Y > 0) { // наЛЕВО
        posY = MAX_Y_VIEV - 2;
        Viev_Y -= MAX_Y_VIEV;
        change = true;
    }
    else if (posY < 0)
    {
        posY = 0;
    }
    return change;
}

bool Encounter() {
    cls();
    SetConsoleTextAttribute(hConsole, 15);
    Sleep(1000);
    cout << "Fight! :D" << endl;
    Sleep(1000);
    cout << "Nah I'd win." << endl;
    Sleep(1000);
    SetConsoleTextAttribute(hConsole, 8);

    return false; // false - died | true - alive
}

void PrintMapSimvol(char Simvol, int y, int x) {
    if (Simvol == '#') {
        SetConsoleTextAttribute(hConsole, 4); // red
        setCursorPosition(y, x);
        std::cout << Simvol;
        SetConsoleTextAttribute(hConsole, 8); // grey
    }
    else if (Simvol == '!') {
        SetConsoleTextAttribute(hConsole, 15); // white
        setCursorPosition(y, x);
        std::cout << Simvol;
        SetConsoleTextAttribute(hConsole, 8);
    }
    else
    {
        SetConsoleTextAttribute(hConsole, 8);
        setCursorPosition(y, x);
        std::cout << Simvol;
    }
}

void Spawn() {
    cout << "Start in ";
    for (int i = 3; i >= 0; i--) {
        setCursorPosition(9, 0);
        cout << i << " ";
        Sleep(1000);
    }
    cls();
}
void Welcome() {
    char start;
    std::cout << "Welcome to our project" << std::endl;
    std::cout << "Play - p" << std::endl;
    std::cout << "quit - q" << std::endl;
    std::cin >> start;

    cls();

    switch (start) {
    case PLAY: {
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
        Sleep(2000);
        break;
    }
    }
}

//**********************************************************************************************************************************
// Начало

int main()
{
    SetConsoleTextAttribute(hConsole, 15);
    //ShowConsoleCursor(false);
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000); // full screan
    setlocale(0, "");
    srand(time(NULL));

//----------------------------------------------------------------------------------------------------------------------------------------------------------
    Welcome();

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Создание Карты
    const int TERR_SIZE = 11;
    const int TERR_MAX_SIZE = 200;
    char terr[TERR_MAX_SIZE] = { '`',',','"','_','.', '-', 'o', '*', '/', ';','#' };
    for (int i = TERR_SIZE; i < TERR_MAX_SIZE; i++) {
        terr[i] = ' ';
    }

//----------------------------------------------------------------------------------------------------------------------------------------------------------

    while (true) { // inf game

        SetConsoleTextAttribute(hConsole, 15);
        ShowConsoleCursor(FALSE);
        
        // нахождение поля видимости (для того чтобы перемещать камеру по карте (отрезок от карты))
        int Viev_X = 0; 
        int Viev_Y = 0;

        char map[MAX_Y][MAX_X]; // полная карта

        for (int y = 0; y < MAX_Y; y++) // заполнение карты символами (которые находятся в массиве terr
        {
            for (int x = 0; x < MAX_X; x++)
            {
                map[y][x] = terr[rand() % TERR_MAX_SIZE];
            }
        }

        for (int x = 0; x < MAX_X; x++) { // границы (решетки #)
            map[0][x] = '#';
            map[MAX_Y - 1][x] = '#';
        }
        for (int y = 0; y < MAX_Y; y++) {
            map[y][0] = '#';
            map[y][MAX_X - 1] = '#';
        }

        map[10][10] = '!'; // типо моб

//----------------------------------------------------------------------------------------------------------------------------------------------------------

        char BattleField[MAX_Y_VIEV][MAX_X_VIEV]; // Текущее поле (отрезок от карты) имеющий размер с константами которые указаны выше
        char prevBattleField[MAX_Y_VIEV][MAX_X_VIEV]; // Предыдущее поле (Необходимо для ускорения изменения карты, оптимизации)

//----------------------------------------------------------------------------------------------------------------------------------------------------------
        for (int y = 0; y < MAX_Y_VIEV; y++) //  Заполение поле отрезком карты 
        {
            for (int x = 0; x < MAX_X_VIEV; x++)
            {
                BattleField[y][x] = map[y][x];
            }
        }

//----------------------------------------------------------------------------------------------------------------------------------------------------------
        cls();

        int P_X = 5; // position of player [X]
        int P_Y = 5; // position of player [Y]

        Player player;


        std::cout << "What is your name?\n";
        std::cin >> player.name;
        int points = 1;

//----------------------------------------------------------------------------------------------------------------------------------
        Sleep(1000); // хз зачем, работает значит не трогай

//**********************************************************************************************************************************
        cls();
        Spawn(); // Отсчет (от 3 до 0)

//----------------------------------------------------------------------------------------------------------------------------------

        while (true) { // Начало игры

            for (int y = 0; y < MAX_Y_VIEV; y++) // Цикл проверяющий текущее поле с предыдущим по каждому символу
            {
                for (int x = 0; x < MAX_X_VIEV; x++)
                {
                    if (BattleField[y][x] == prevBattleField[y][x]) {
                        
                        continue;
                    }
                    PrintMapSimvol(BattleField[y][x], y, x);
                    // если не совпадает то в указаной позиции пишет символ из текущего поля
                }
            }

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Копирование предыдущего поля с текущим
            std::memcpy((char*)prevBattleField, (char const*)BattleField, MAX_X_VIEV * MAX_Y_VIEV);

//----------------------------------------------------------------------------------------------------------------------------------------------------------
            int prevX = P_X; // сохранение позиции игрока до его изменения
            int prevY = P_Y;

            player_movement(P_X, P_Y); // проверяет на движение

//----------------------------------------------------------------------------------------------------------------------------------------------------------
            
            if (map[prevY + Viev_Y][P_X + Viev_X] == '#' || map[prevY + Viev_Y + 1][P_X + Viev_X] == '#') {
                P_X = prevX;
            }
            if ((map[P_Y + Viev_Y][prevX + Viev_X] == '#') || (map[P_Y + Viev_Y + 1][prevX + Viev_X] == '#')) {
                P_Y = prevY;
            }
            if ((map[P_Y + Viev_Y][P_X + Viev_X] == '#') || (map[P_Y + Viev_Y + 1][P_X + Viev_X] == '#')) {
                P_Y = prevY;
                P_X = prevX;
            }
// Если в его позиции будет решетка то вернет в предыдущую позицию

//----------------------------------------------------------------------------------------------------------------------------------------------------------
            
            if (P_X != prevX || P_Y != prevY) { // если после всех изменений позиция изменилось то
                bool result = ChangeMap(P_X, P_Y, Viev_X, Viev_Y); // проверит нужно ли менять локацию

                if (result == true) { // если скажет да то
                    for (int y = Viev_Y; y < Viev_Y + MAX_Y_VIEV; y++)
                    {
                        for (int x = Viev_X; x < Viev_X + MAX_X_VIEV; x++)
                        {
                            BattleField[y - Viev_Y][x - Viev_X] = map[y][x];
                        }
                    }
                    // Меняет поле на кусочек от карты взависимости от позиции его поля видения
                    PrintMapSimvol(BattleField[prevY][prevX], prevY, prevX);
                    PrintMapSimvol(BattleField[prevY + 1][prevX], prevY + 1, prevX);

                    // убрать игрока с предыдущего места и заменить на символы из поля
                }
            }

//----------------------------------------------------------------------------------------------------------------------------------------------------------
            
            setCursorPosition(P_Y, P_X);
            SetConsoleTextAttribute(hConsole, 204); //12 or 204
            std::cout << " ";
            setCursorPosition(P_Y + 1, P_X);
            SetConsoleTextAttribute(hConsole, 204); //12 or 204
            std::cout << " ";

            // рисует игрока на 2-ух клетках

//----------------------------------------------------------------------------------------------------------------------------------------------------------
            Sleep(25);

            SetConsoleTextAttribute(hConsole, 8);


            if (prevX != P_X) {
                PrintMapSimvol(BattleField[prevY][prevX], prevY, prevX);
                PrintMapSimvol(BattleField[prevY + 1][prevX], prevY + 1, prevX);
            }
            else if (prevY > P_Y) {
                PrintMapSimvol(BattleField[prevY + 1][prevX], prevY + 1, prevX);
            }
            else if (prevY < P_Y) {
                PrintMapSimvol(BattleField[prevY][prevX], prevY, prevX);
            }

            if (GetKeyState('C') & 0x8000)
            {

                ClearArray(prevBattleField);

                interface_buttons(player.name, player.MaxHealth, player.health, player.strong, player.charisma, player.healing, points);
                cls();
            }


            if (BattleField[P_Y][P_X] == '!') {
                for (int x = 0; x < MAX_X_VIEV; x++)
                {
                    for (int y = 0; y < MAX_Y_VIEV; y++)
                    {
                        if (BattleField[y][x] == '*') {
                            continue;
                        }
                        PrintMapSimvol('*', y, x);
                    }
                }
                for (int x = MAX_X_VIEV - 1; x >= 0; x--)
                {
                    for (int y = MAX_Y_VIEV - 1; y >= 0; y--)
                    {
                        PrintMapSimvol(' ', y, x);
                    }
                }

                cls();
                std::srand(std::time(0));

                Enemy enemy("Froggit");

                while (player.isAlive()) {
                    encounte(player, enemy);
                    std::cout << "Do you want to continue? (y/n): ";
                    char choice;
                    std::cin >> choice;
                    if (player.isAlive() == false)
                    {
                        break;
                    }
                    if (choice == 'y')
                    {
                        cls();
                        break;
                    }
                }
                ClearArray(prevBattleField);

                if (!player.isAlive())
                {
                    cout << "you died";
                    Sleep(1000);
                    cls();
                    break;
                }
                else
                {
                    map[P_Y + Viev_Y][P_X + Viev_X] = ' ';
                    BattleField[P_Y][P_X] = ' ';
                }
            }
        }
    }

    return 0;
}