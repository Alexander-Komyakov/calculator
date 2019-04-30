#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <cstring>
#include "Button.h"
#include "Transformed.h"

using namespace std;
using namespace sf;


int main()
{
    RenderWindow window(VideoMode(840, 607), "Calculator"); //создаем окно
    //изменение размера окна
    window.setSize(Vector2u(440, 380));
    View view;//объявили sfml объект "вид", который и является камерой
    view.reset(FloatRect(0, 0, 1260, 607)); //изменение камеры

    vector <Button> Buttons; //храним все кнопки в массиве
    Buttons.reserve(24); //выделяем 12 мест в массиве
    
    //Цифры 1-9
    Button but1("1", 15, 115); //создаем кнопку
    Buttons.push_back(but1); //заносим созданную кнопку в массив
    Button but2("2", 225, 115);
    Buttons.push_back(but2);
    Button but3("3", 435, 115);
    Buttons.push_back(but3);
    
    Button but4("4", 15, 215);
    Buttons.push_back(but4);
    Button but5("5", 225, 215);
    Buttons.push_back(but5);
    Button but6("6", 435, 215);
    Buttons.push_back(but6);

    Button but7("7", 15, 315);
    Buttons.push_back(but7);
    Button but8("8", 225, 315);
    Buttons.push_back(but8);
    Button but9("9", 435, 315);
    Buttons.push_back(but9);
    
    //Нуль, запятая, удаление одного символа 
    Button butZ(".", 15, 415);
    Buttons.push_back(butZ);
    Button but0("0", 225, 415);
    Buttons.push_back(but0);
    Button butDel("Del", 435, 415);
    Buttons.push_back(butDel);    

    //Действия: деление, умножение, разница, сумма
    Button butD("/", 645, 115);
    Buttons.push_back(butD);
    Button butP("*", 645, 215);
    Buttons.push_back(butP);
    Button butM("-", 645, 315);
    Buttons.push_back(butM);  
    Button butS("+", 645, 415);
    Buttons.push_back(butS); 

    //Очистка, поле выводa примера и ответа
    Button butDisplay("Input", 15, 15, 600);
    Buttons.push_back(butDisplay);

    Button butClear("Clear", 645, 15);
    Buttons.push_back(butClear);
    Buttons[17].setShiftTextXY(6, 0); //сдвигаем текст в кнопке левее

    Button butDisplayAnswer("Answer", 15, 515, 1230); //810
    Buttons.push_back(butDisplayAnswer);

    Button butLog("log", 855, 15); //корень
    Buttons.push_back(butLog);
    Button butSin("sin", 855, 115); //синус
    Buttons.push_back(butSin);
    Button butCos("cos", 855, 215); //косинус 
    Buttons.push_back(butCos);
    Button butTan("tan", 855, 315); //тангенс 
    Buttons.push_back(butTan);
    Button butSqrt("sqrt", 855, 415, 390); //логарифм
    Buttons.push_back(butSqrt);
    Button butFact("fact", 1065, 315); //факториал
    Buttons.push_back(butFact);
    Button butPi("Pi", 1065, 15); //число Пи
    Buttons.push_back(butPi);
    Button butE("e", 1065, 115); //число е
    Buttons.push_back(butE);   
    Button butLn("ln", 1065, 215); //Десятисчный логарифм
    Buttons.push_back(butLn); 

    double otwet = 0; //ответ на введенный пример

    string input; //введенная пользователем строка
    while (window.isOpen()) //пока открыто окно
    {
        Event event; //создаем событие и обновляем его

    	Vector2i MausePixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f MausePos = window.mapPixelToCoords(MausePixelPos);//переводим их в игровые (уходим от коорд окна)
       

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) //если вызван выход
                window.close(); //закрываем окно
            //управление графическое
            for (auto i = Buttons.begin(); i != Buttons.end(); i++) //перебираем все кнопки
            {
                if(i->AimButton(MausePos.x, MausePos.y)) //если курсор попадает на кнопку
                { 
                    i->button.setFillColor(Color::Cyan); //красим кнопку
                    if(event.type == event.MouseButtonReleased and event.mouseButton.button == Mouse::Left) //если отпущена ЛКМ
                    {
                        if(i->getName() == "Clear") //если нажата клавиша очистить
                        {
                            input = ""; //обнуляем вывод
                        }
                        else if(i->getName() == "Del") //если нажата кнопка Del
                        {
                            if (input.size() > 0) //размер строки больше нуля
                            {
                                input.pop_back(); //удаляем последний символ
                            }
                        }
                        else if(i == Buttons.begin()+18) //если нажата клавиша вывода ответа
                        {
                            Clipboard::setString(to_string(DeticionExample(input, input.size() ) )); //копируем в буфер обмена ответ
                        }
                        else
                        {
                            input += i->getName(); //добавляем в строку ввода нажатую клавишу
                        }
                    }
                }
                else
                {
                    i->button.setFillColor(Color::White); //ставим стандартный цвект
                }
            }
            //управление кнопками
            if (event.type == Event::KeyReleased) //если клавиша отпущена
	        {
		        if (event.key.code == Keyboard::C) //клавиша С
		        {
                    input = ""; //очищаем введенную пользователем строку
		        }


		        if (event.key.code == Keyboard::Num0 or event.key.code == Keyboard::Numpad0) //клавиша 0
		        {
                    input += '0'; //добавляем в конец строки введенную букву
		        }
                else if (event.key.code == Keyboard::Num1 or event.key.code == Keyboard::Numpad1) //клавиша 1
		        {
                    input += '1'; //добавляем в конец строки введенную букву
		        }
                else if (event.key.code == Keyboard::Num2 or event.key.code == Keyboard::Numpad2) //клавиша 2
		        {
                    input += '2'; //добавляем в конец строки введенную букву
		        }
                else if (event.key.code == Keyboard::Num3 or event.key.code == Keyboard::Numpad3) //клавиша 3
		        {
                    input += '3'; //добавляем в конец строки введенную букву
		        }
		        else if (event.key.code == Keyboard::Num4 or event.key.code == Keyboard::Numpad4) //клавиша 4
		        {
                    input += '4'; //добавляем в конец строки введенную букву
		        }
                else if (event.key.code == Keyboard::Num5 or event.key.code == Keyboard::Numpad5) //клавиша 5
		        {
                    input += '5'; //добавляем в конец строки введенную букву
		        }
                else if (event.key.code == Keyboard::Num6 or event.key.code == Keyboard::Numpad6) //клавиша 6
		        {
                    input += '6'; //добавляем в конец строки введенную букву
		        }
                else if (event.key.code == Keyboard::Num7 or event.key.code == Keyboard::Numpad7) //клавиша 7
		        {
                    input += '7'; //добавляем в конец строки введенную букву
		        }
                else if (event.key.code == Keyboard::Num8 or event.key.code == Keyboard::Numpad8) //клавиша 8
		        {
                    input += '8'; //добавляем в конец строки введенную букву
		        }
                else if (event.key.code == Keyboard::Num9 or event.key.code == Keyboard::Numpad9) //клавиша 9
		        {
                    input += '9'; //добавляем в конец строки введенную букву
		        }
                

                else if (event.key.code == Keyboard::BackSpace) //клавиша BackSpace
		        {
                    if (input.size() > 0) //если размер строки больше нуля
                    {
                        input.pop_back(); //удаляем последний символ
                    }
		        }
                else if (event.key.code == Keyboard::Period) //клавиша '.'
		        {
                    input += '.'; //добавляем введенный символ в строку
		        }
                else if (event.key.code == Keyboard::Add) //клавиша '+'
		        {
                    input += '+'; //добавляем введенный символ в строку
		        }
                else if (event.key.code == Keyboard::Subtract) //клавиша '-'
		        {
                    input += '-'; //добавляем введенный символ в строку
		        }
                else if (event.key.code == Keyboard::Divide) //клавиша '/'
		        {
                    input += '/'; //добавляем введенный символ в строку
                } 
                else if (event.key.code == Keyboard::Multiply) //клавиша '*'
                {
                    input += '*'; //добавляем введенный символ в строку
                }
	        }
        }
        //получение ответа на введенный пример
        double otwet = DeticionExample(input, input.size());

        Buttons[16].setName(LastCharsString(input, 27)); //Выводим пользователю последние 27 нажатых клавишь
        Buttons[18].setName(LastCharsString(to_string(otwet), 57)); //Выводим пользователю ответ 
        //Изменяем размер ответа, ввода и шрифта в зависимости от кол-ва символов
        if(to_string(otwet).size() > 35) //если ответ слишком длинный (не вмещается в окно)
        {
            Buttons[18].text.setCharacterSize(40); //уменьшаем размер текста
            Buttons[18].setShiftTextXY(12, 12); //сдвигаем в центр кнопки текст
        }
        else
        {
            Buttons[18].setShiftTextXY(12, 0); //возвращаем на место текст
            Buttons[18].text.setCharacterSize(63); //меняем на исходный размер
        }
        if(input.size() > 17) //если ввод слишком длинный(не вмещается в окно)
        {
            Buttons[16].text.setCharacterSize(40); //уменьшаем размер текста
            Buttons[16].setShiftTextXY(8, 14); //сдвигаем в центр кнопки текст
        }
        else
        {
            Buttons[16].setShiftTextXY(12, 0); //возвращаем на место текст
            Buttons[16].text.setCharacterSize(63); //меняем на исходный размер
        }

        window.clear(); //очищаем экран
        for (auto i = Buttons.begin(); i != Buttons.end(); i++) //отрисовываем кнопки
        {
            window.draw(i->button);
            window.draw(i->text);
        }
        window.setView(view);
        window.display(); 
    }

    return 0;
}

