#include "Transformed.h"

double DeticionExample(string &example, int sizeExample)
{
    FixRepeatSign(example, sizeExample); //фиксит ошибки, удаляет повторяющиеся знаки, для дальнейшего разброса по отдельным переменным 
    string signs; //знаки между числами
    const int sizeNumeric = 128;
    string numericStr[sizeNumeric]; //введенные пользователем числа в виде строки
    double numeric[sizeNumeric]; //введенные пользователем числа

    ExampleToVariable(example, numericStr, signs, sizeExample, sizeNumeric); //Разносим введенные данные по переменным (числа, игнорируя буквы)

    for (int i = 0; i < sizeNumeric; i++)
    {
        FixRepeatAct(numericStr[i], sizeNumeric); //фиксит ошибки ввода пользователя
    }
        //удаляет повторяющиеся действия, sin, cos и т.п., оставляя последнее введенное действие(sin, Pi...)
    
    ActToDouble(numericStr, sizeNumeric); //преобразовываем числа пи sin и т.п. в обычные числа
    StrArToDouble(numericStr, numeric, sizeNumeric); //Преобразовываем введенные string в массив чисел double
     
    return DeticionManyNumeric(signs, numeric, signs.length()); //находим решение и возвращаем его
} 

void FixRepeatAct(string &numerStr, int sizeNumber) //принимает сслыку на одну строку и удаляет из неё лишние действия
{
    int FindMass[128]; //массив всех позиций найденых действий(sin и т.п.)
    FindMass[0] = numerStr.find("sin");
    FindMass[1] = numerStr.find("cos");
    FindMass[2] = numerStr.find("tan");
    FindMass[3] = numerStr.find("log");
    FindMass[4] = numerStr.find("e");
    FindMass[5] = numerStr.find("Pi");
    FindMass[6] = numerStr.find("ln");
    FindMass[7] = numerStr.find("sqrt");
    FindMass[8] = numerStr.find("fact");
    numerStr = LastCharsString(numerStr, sizeNumber-max(FindMass, 128)); //удаляем все символы находящиеся перед последним действием 
} 
int max(int *numeric, int sizeNumeric)
{
    int maximum = numeric[0]; //сначала записываем первое число как самое большое
    for (int i = 1; i < sizeNumeric; i++) //перебираем все числа принятого массива
    {
        if(maximum < numeric[i]) //если текущее число больше, чем старое макс. число
        {
            maximum = numeric[i]; //сделать максимальным текущее число
        }
    }
    return maximum;
}

void FixRepeatSign(string &str, int sizeStr)
{
    bool keyDot = true; //можно ли ставить точку
    //для того что бы нельзя было установить в одном числе несколько точек

    for (int i = 0; i < sizeStr; i++) //перебираем все строки массива
    {
        if (str[i] == '.' and keyDot == false) //если встретилась точка, но ставить её нельзя
        {
            str.erase(i, 1); //удаляем её
        }
        else if (str[i] == '.' and keyDot == true) //если встретилась точка и её можно ставить
        {
            keyDot = false; //запрещаем ее ставить
        }
        if (str[i] == '+' or str[i] == '-' or str[i] == '/' or str[i] == '*'\
                or str[i] == 'x') //если символ равн ариф. действию
        {
            //разрешаем ввод точки
            keyDot = true; //встретили знак, а значит следующее число в котором еще не было точки
            if (sizeStr > i+1) //это не конец строки
            {
                if (str[i+1] == '+' or str[i+1] == '-' or str[i+1] == '/'\
                        or str[i+1] == '*' or str[i+1] == 'x') //если следующий символ тоже ариф. действие
                {
                    str.erase(i, 1); //удаляем повторяющийся знак ариф. дейсивия
                }
            }
        }
    }
}

void ExampleToVariable(string example, string *numericStr, string &sign, int sizeExample, int sizeNumeric)
{
    int numberVariable = 0; //номер числа заносимого в переменную
    for (int i = 0; i < sizeExample; i++) //перебираем все введенное пользователем
    {
        if (example[i] == '0' or example[i] == '1' or example[i] == '2' or example[i] == '3' or example[i] == '4'\
                or example[i] == '5' or example[i] == '6' or example[i] == '7' or example[i] == '8'\
                or example[i] == '9' or example[i] == '.') //если цифра
        {
            numericStr[numberVariable] += example[i]; //заносим ее в переменную хранящую числа
        }
        else if (WordABC(example[i])) //если это буква английского алфавита
        {
            numericStr[numberVariable] += example[i]; //заносим ее в переменную хранящую числа
        }
        else if(example[i] == '+' or example[i] == '-' or example[i] == '*' or example[i] == 'x' or example[i] == '/') //если знак
        {
            numberVariable++; //переходим к следующему числу
            sign += example[i]; //заносим знак в переменную хранящую знаки
        }
    }
} 

double DeticionManyNumeric(string signs, double *numeric, int sizeSigns)
{
    double answer = 0;
    for(int i = 0; i < sizeSigns; ++i) //перебираем все сохраненные знаки(алгебраические действия над переменными)
    {
        if (i == 0) //если это первый элемент
        {
            answer = DeticionTwoNumeric(numeric[0], numeric[1], signs[0]); //сохраняем в ответ результат действия над первыми двумя переменными
        }
        else
        {
            answer = DeticionTwoNumeric(answer, numeric[i+1], signs[i]); //делаем действия над прошлым результатом
        }
    }
    return answer;
}

double DeticionTwoNumeric(double num1, double num2, char sign)
{
    if (sign == '+')
    {
        return num1 + num2;
    }
    else if (sign == '-')
    {
        return num1 - num2;
    }
    else if (sign == '/')
    {
        return num1 / num2;
    }
    else if (sign == '*' or sign == 'x')
    {
        return num1 * num2;
    }
    return 0;
}

void StrArToDouble(string *ArrayStr, double *ArrayDouble, int sizeArrayStr)
{
    for (int i = 0; i < sizeArrayStr; i++) //перебираем все элементы массива переменных
    {
        if (ArrayStr[i].size() > 0) //если элемент больше нуля
        {
            ArrayDouble[i] = atof(ArrayStr[i].c_str()); //Сохраняем в массив double преобразованные переменные
        }
    }   
}

bool WordABC(char word) //возвращает правду, если это буква англ. алфавита
{
   string abc = "qwertyuiopasdfghjklzxcvbnm"; //алфавит английский малый
   string ABC = "QWERTYUIOPASDFGHJKLZXCVBNM"; //алфавит английский большой
   for (int i = 0; i < abc.size(); i++) 
   {
       if(word == abc[i] or word == ABC[i]) //если это буква англ. алфавита
       {
           return true; //возвращаем правду
       }
   }
   return false; //если это не буква англ. алфавита, то возвращаем ложь
}

void ActToDouble(string *numericStr, int sizeNumericStr) //преобразовывает слова, действия(Pi, sin, cos и т.п.) в числа
{
    for (int i = 0; i < sizeNumericStr; i++) //перебираем все числа(строки)
    {
        //if (numericStr[i].find("Pi") != string::npos);
        if ((numericStr[i])[0] == 'P') //если первая буква P, а значит число Пи
        {
            numericStr[i] = "3.14159265"; //присваиваем ему число Пи в виде строки
        }
        else if ((numericStr[i])[0] == 'e') //если это число e
        {
            numericStr[i] = "2.71828182"; //присваем ему число e в виде строки
        }
        else if ((numericStr[i])[0] == 's' and (numericStr[i])[1] == 'q') //если это sqrt - корень 
        {
            //берем цифры из переменной вида sqrt23423 с помощью функции LastCharsString, то есть все символы кроме первых букв
            //преобразовываем в число double с помощью atof
            //находим корень
            //преобразовываем назад в строку
            numericStr[i] = to_string(sqrt( atof(LastCharsString(numericStr[i], numericStr[i].size()-4).c_str() )));
        }
        else if ((numericStr[i])[0] == 's' and (numericStr[i])[1] == 'i') //если это sin - синус 
        {
            //берем цифры из переменной вида sqrt23423 с помощью функции LastCharsString, то есть все символы кроме первых букв
            //преобразовываем в число double с помощью atof
            //находим синус 
            //преобразовываем назад в строку
            numericStr[i] = to_string(sin( atof(LastCharsString(numericStr[i], numericStr[i].size()-3).c_str() )));
        }
        else if ((numericStr[i])[0] == 'c' and (numericStr[i])[1] == 'o') //если это cos - косинус 
        {
            //берем цифры из переменной вида sqrt23423 с помощью функции LastCharsString, то есть все символы кроме первых букв
            //преобразовываем в число double с помощью atof
            //находим косинус 
            //преобразовываем назад в строку
            numericStr[i] = to_string(cos( atof(LastCharsString(numericStr[i], numericStr[i].size()-3).c_str() )));
        }
        else if ((numericStr[i])[0] == 't' and (numericStr[i])[1] == 'a') //если это tan - тангенс
        {
            numericStr[i] = to_string(tan( atof(LastCharsString(numericStr[i], numericStr[i].size()-3).c_str() )));
        }
        else if ((numericStr[i])[0] == 'f' and (numericStr[i])[1] == 'a') //если это fact - факториал
        {
            numericStr[i] = to_string(fact( atof(LastCharsString(numericStr[i], numericStr[i].size()-4).c_str() )));
        }
        else if ((numericStr[i])[0] == 'l' and (numericStr[i])[1] == 'n') //если это ln - логарифм
        {
            numericStr[i] = to_string(log( atof(LastCharsString(numericStr[i], numericStr[i].size()-2).c_str() )));
        }
        else if ((numericStr[i])[0] == 'l' and (numericStr[i])[1] == 'o') //если это log - логарифм с основанием 10
        {
            numericStr[i] = to_string(log10( atof(LastCharsString(numericStr[i], numericStr[i].size()-3).c_str() )));
        }

    }
}

string LastCharsString(string input, int numeric) //возвращает последние n символов строки
{
    if (input.length() <= numeric) //если строка меньше чем требуемая для обрезки
    {
        return input; //возвращем в неизменном виде
    }
    else
    {
        string cropped = ""; //обрезанная строка
        for (int i = (input.size() - numeric); i < input.size(); i++) //перебираем последние n символов
        {
            cropped += input[i]; //добавляем последние n символов в массив
        }
        return cropped; //возвращаем строку с последними n символами исходной строки
    }
}

double fact(double n)
{    
    if(n < 0) // если ввел отрицательное число
        return 0; // возвращаем ноль
    if (n == 0) // если ввел ноль,
        return 1; // возвращаем факториал от нуля до 1
    else // Во всех остальных случаях
        return n * fact(n - 1); // делаем рекурсию 
}
