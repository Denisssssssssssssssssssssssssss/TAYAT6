#pragma once
#ifndef __LEXEME
#define __LEXEME

#include <string>
using namespace std;

#define MAX_TEXT 10000 // Максимальный размер текста
#define MAX_LEX 100    // Максимальная длина лексемы
#define MAX_NUM 25    // Максимальная длина лексемы
#define MAX_FLT 35    // Максимальная длина лексемы
#define MAX_KEYW 13    // Максимальное количество ключевых слов

typedef char TypeMod[MAX_TEXT];  // Тип для хранения текста (модуля)
typedef char TypeLex[MAX_LEX];   // Тип для хранения лексем

#define typeID 1          // Идентификатор

// Коды типов данных 
#define typeInt 10 
#define typeDouble 11 
#define typeFor 12
#define typeClass 13
#define typeReturn 14 
#define typeMain 15

// Коды для констант
#define constInt 20      // Целочисленная константа
#define constDouble 21   // Вещественная константа

// Коды для специальных символов
#define typePoint 30     // Точка
#define typeComma 31     // Запятая
#define typeSemicolon 32 // Точка с запятой
#define typeLeftBracket 33  // Левый круглый скобка
#define typeRightBracket 34 // Правый круглый скобка
#define typeLeftBrace 35    // Левый фигурный скобка
#define typeRightBrace 36   // Правый фигурный скобка

// Коды операторов
#define typeEval 40       // Оператор равенства
#define typeUnEq 41      // Оператор неравенства
#define typeEq 42        // Оператор равенства
#define typeMore 43      // Оператор больше
#define typeMoreOrEq 44  // Оператор больше или равно
#define typeLess 45      // Оператор меньше
#define typeLessOrEq 46  // Оператор меньше или равно
#define typeMul 47       // Оператор умножения
#define typeDiv 48       // Оператор деления
#define typeMod 49       // Оператор остатка от деления
#define typePlus 50      // Оператор сложения
#define typeMinus 51     // Оператор вычитания


// Коды для специальных состояний
#define typeEnd 100      // Конец файла
#define typeError 404    // Ошибка при разборе

inline string GetTypeName(int typeCode) {
    switch (typeCode) {
    case typeInt: return "typeInt";
    case typeDouble: return "typeDouble";
    case typeReturn: return "typeReturn";
    case typeClass: return "typeClass";
    case typeMain: return "typeMain";
    case typeID: return "typeID";
    case typeFor: return "typefor";
    case constInt: return "constInt";
    case constDouble: return "constDouble";
    case typePoint: return "typePoint";
    case typeComma: return "typeComma";
    case typeSemicolon: return "typeSemicolon";
    case typeLeftBracket: return "typeLeftBracket";
    case typeRightBracket: return "typeRightBracket";
    case typeLeftBrace: return "typeLeftBrace";
    case typeRightBrace: return "typeRightBrace";
    case typeEval: return "typeEval";
    case typeUnEq: return "typeUnEq";
    case typeEq: return "typeEq";
    case typeLessOrEq: return "typeLessOrEq";
    case typeLess: return "typeLess";
    case typeMoreOrEq: return "typeMoreOrEq";
    case typeMore: return "typeMore";
    case typeMinus: return "typeMinus";
    case typePlus: return "typePlus";
    case typeMod: return "typeMod";
    case typeDiv: return "typeDiv";
    case typeMul: return "typeMul";
    case typeEnd: return "typeEnd";
    case typeError: return "typeError";
    default: return "Unknown Type Code";
    }
}

#endif