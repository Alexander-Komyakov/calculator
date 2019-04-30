#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <cstring>
#include "math.h"


using namespace std;
using namespace sf;

int max(int *numeric, int sizeNumeric); //принимает массив int и его размер, возврщает максимальное число

void FixRepeatAct(string &numerStr, int sizeNumber); //принимает сслыку на одну строку и удаляет из неё лишние действия

void FixRepeatSign(string &st, int sizeSt); //принимает ссылку на строку и удаляет из нее повторяющиеся знаки (-=/+) 

double DeticionTwoNumeric(double num1, double num2, char sign); //Принимает 2 числа и действие, а возвращает их результат

double DeticionManyNumeric(string signs, double *numeric, int sizeSigns); //Принимает n чисел и действий и возвращает ответ

void ExampleToVariable(string example, string *numeric, string &sign, int sizeExample, int sizeNumeric); //принимает строку "2+2-n..." и заносит знаки в массив знаков, числа в массив чисел

void StrArToDouble(string *ArrayStr, double *ArrayDouble, int sizeArrayStr); //преобразовывает массив строк в массив чисел double

double DeticionExample(string &example, int sizeExample); //принимает строку типа 2+2-3.2= и возвращает ответ

bool WordABC(char word); //принимает символ и возвращает правду, если это буква англ. алфавита

void ActToDouble(string *numericStr, const int sizeNumericStr); //преобразовывает слова, действия(Pi, sin, cos и т.п.) в числа

string LastCharsString(string input, int numeric); //возвращает последние n символов строки

double fact(double n); //возвращает факториал
