// Zmeyka.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
using namespace std;







struct Uzel
{
    int x;
    int y;
    Uzel* sled;
    
    Uzel(int X, int Y)
    {
        x = X;
        y = Y;
        sled = nullptr;
        
    }
};

char control = 'w';
Uzel* golova = nullptr;
Uzel* hvost = nullptr;
int eda_x ;
int eda_y ;
bool igra = true;
const int shirina = 30;
const int visota = 20;
int score = 0;
int speed = 100;


void InitSnake()
{
    int midx = shirina / 2;
    int midy = visota / 2;
    golova = new Uzel(midx, midy);
    hvost = golova;
    eda_x = rand() % shirina;
    eda_y = rand() % visota;
}

void Addhead(int x, int y)
{
    Uzel* newH = new Uzel(x, y);
    newH->sled = golova;
    golova = newH;
}

void RemoveTail()
{
    if (!golova || !golova->sled)
        return;
    Uzel* curr = golova;
    while (curr->sled != hvost)
        curr = curr->sled;
    delete hvost;
    hvost = curr;
    hvost->sled = nullptr;
}

bool Stolknoveniye(int x, int y)
{
    Uzel* curr = golova;
    while (curr != nullptr)
    {
       
            if (curr->x == x && curr->y == y)
            return true;
        curr = curr->sled;
    }
    return false;
}

void Map_reset()
{
    system("cls");

    // Верхняя граница
    for (int i = 0; i < shirina + 2; i++)
        cout << "#";
    cout << "\n";

    for (int y = 0; y < visota; y++)
    {
        cout << "#";
        for (int x = 0; x < shirina; x++)
        {
            bool printed = false;

            // голова
            if (golova->x == x && golova->y == y)
            {
                cout << "O";
                printed = true;
            }
            // тело
            else
            {
                Uzel* curr = golova->sled;
                while (curr)
                {
                    if (curr->x == x && curr->y == y)
                    {
                        cout << "o";
                        printed = true;
                        break;
                    }
                    curr = curr->sled;
                }
            }

            // еда
            if (x == eda_x && y == eda_y)
            {
                cout << "@";
                printed = true;
            }

            if (!printed)
                cout << " ";
        }
        cout << "#\n";
    }

    // Нижняя граница
    for (int i = 0; i < shirina + 2; i++)
        cout << "#";
    cout << "\nScore: " << score << "  (WASD — движение, Q — выход)\n";
}
void Move()
{
    
    int newX = golova->x;
    int newY = golova->y;

    if (_kbhit())
    {
        char c = tolower(_getch());
        if ((c == 'w' ) && control != 's') control = 'w';
        else if ((c == 's')&& control != 'w'   ) control = 's';
        else if ((c == 'a' )&& control != 'd') control = 'a';
        else if ((c == 'd' ) && control != 'a' ) control = 'd';
        else if (c == 'q' ) igra = false;
    }

    switch (control)
    {
    case 'w': newY--; break;
    case 's': newY++; break;
    case 'a': newX--; break;
    case 'd': newX++; break;
    }

    // столкновение со стенами
    if (newX < 0 || newX >= shirina || newY < 0 || newY >= visota)
    {
        igra = false;
        return;
    }

    // столкновение с собой
    if (Stolknoveniye(newX, newY))
    {
        igra = false;
        return;
    }

    // добавляем голову
    Addhead(newX, newY);

    // еда
    if (newX == eda_x && newY == eda_y)
    {
        score += 1;
        eda_x = rand() % shirina;
        eda_y = rand() % visota;
        if (speed > 40) speed -= 2;
    }
    else
    {
        RemoveTail();
    }
}




void CheckRecord(int score)
{
    string recordName;
    int recordScore = 0;

    // --- Чтение текущего рекорда ---
    ifstream infile("rec.txt");
    if (infile.is_open())
    {
        infile >> recordName >> recordScore; 
        infile.close();
    }

    // --- Сравнение с текущим счётом ---
    if (score > recordScore)
    {
        cout << "Новый рекорд! Ваш счёт: " << score << "\n";
        cout << "Введите имя: ";
        string name;
        cin >> name;

        ofstream outfile("rec.txt", ios::trunc); // перезаписываем файл
        if (outfile.is_open())
        {
            outfile << name << " " << score << endl;
            outfile.close();
        }

        cout << "Рекорд сохранён!\n";
    }
    else
    {
        cout << "Рекорд: " << recordName << " " << recordScore << endl;
    }
}
int main()
{
    setlocale(0, "rus");
    srand(GetTickCount());
    InitSnake();

    while (igra)
    {
        Map_reset();
        Move();
        Sleep(speed);
    }

    system("cls");
    cout << "YOU LOSE!\nCчёт: " << score << "\n";
    CheckRecord(score);
    _getch();

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.












