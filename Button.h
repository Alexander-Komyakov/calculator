#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <cstring>

using namespace sf;
using namespace std;

class Button
{
public:
    int x, y, width, height; //Координаты кнопки
    string name; //текст кнопки
    int shiftTextX, shiftTextY; //сдвиг текста относительно кнопки 
    Font font; //шрифт текста кнопки
    Text text; //sfml текст
    RectangleShape button; //прямоульник
    Button(string Iname, int Ix, int Iy, int Iwidth=180, int Iheight=80, int IsizeFont=63); //конструктор
    bool AimButton(int Mausex, int Mausey); //попадают ли принятые координаты на текущую клавишу
    string getName();
    void setName(string Iname);
    void setShiftTextXY(int IshiftTextX, int IshiftTextY); //вносим сдвиг текста и применяем его
};


