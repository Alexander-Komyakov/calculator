#include "Button.h"

Button::Button(string Iname, int Ix, int Iy, int Iwidth, int Iheight, int IsizeFont) //Параметры по умолчанию указываются только в определении
{ 
    shiftTextX = 12; shiftTextY = 0;
    name = Iname; x = Ix; y = Iy; width = Iwidth; height = Iheight; //сохраняем принятые значения
    button.setSize(Vector2f(width, height)); //размер прямоугольника
    button.setPosition(x, y); //позиция прямоугольника

    font.loadFromFile("InputMonoCompressed-Bold.ttf"); //шрифт

    text.setFont(font); //Задаем тексту ранее созданный шрифт
    text.setCharacterSize(IsizeFont); //Определяем размер текста
    text.setFillColor(Color::Blue); //Цвет текста
    text.setPosition(x+shiftTextX, y+shiftTextY); //Позиция текста
    text.setString(name); //Выводимая строка

    button.setOutlineThickness(8); //Рамка по бокам прямугольника
    button.setOutlineColor(Color(250, 150, 100)); //цвет рамки прямоугольника
}

bool Button::AimButton(int Mausex, int Mausey)
{
    if((Mausex >= x and Mausex <= x + width) and (Mausey >= y and Mausey <= y + height)) //если принятые координаты попадают на кноку
    {
        return true;
    }
    return false;
}

string Button::getName()
{
    return name;
}

void Button::setName(string Iname)
{
    name = Iname; //сохраняем введенную строку
    text.setString(name); //Меняем строку
}

void Button::setShiftTextXY(int IshiftTextX, int IshiftTextY)
{
    shiftTextX = IshiftTextX;
    shiftTextY = IshiftTextY;
    text.setPosition(x+shiftTextX, y+shiftTextY); //меняем позицию текста на новую
}
