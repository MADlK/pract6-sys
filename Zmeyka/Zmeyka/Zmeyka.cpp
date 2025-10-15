// Zmeyka.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>
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
const int shirina = 3;
const int visota = 2;


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
    Uzel* curr = new Uzel(x, y);
    while (curr != nullptr)
    {
        if (curr->x == x && curr->y == y) return true;
        curr = curr->sled;
    }
    return false;
}

void Map_reset()
{
    system("cls");
    for (int i = 0; i < shirina + 2; i++) 
    {
        cout << "#";
    }
    
    for (int y = 0; y < visota + 2; y++) 
    {
        for (int x = 0; x < shirina + 2; x++)
        {
          
            if (x == 0)
                cout << "#";

            bool printed = false;
            if (golova->x == x && golova->y == y)
            {
                cout << "O";
                printed = true;
            }

        }
        cout << "\n";
    }
    for (int i = 0; i < shirina + 2; i++)
    {
        cout << "#";
    }
}


int main()
{
    setlocale(0, "rus");
    
    while (control!=' ')
    {
        Map_reset();
    }
    

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
