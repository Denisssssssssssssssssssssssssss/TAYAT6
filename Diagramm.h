#pragma once

#include "Scanner.h"
#include "Tree.h"

class Diagramm
{
private:
	Scanner* scanner;
	Tree* tree;
	bool inClass = false;
	void Description();						// Описание
	void Data();							// Данные
	void Function();						// Функция
	void Type();							// Тип
	void List();							// Список
	void Variable();						// Переменная
	void Assignment();						// Присваивание
	void Expression();						// Выражение
	void CompositeOperator();				// Составной оператор
	void OperatorsAndDescriptions();		// Операторы и описания
	void MemberAccess();					//Доступ к данным класса
	void Operator();						// Оператор
	void FunctionCall();					// Вызов функции
	void FunctionCall(Tree* tree);					// Вызов функции
	void Comparison();						// Сравнение
	void Summand();							// Слагаемое
	void Multiplier();						// Множитель
	void UnaryOperation();					// Унарная операция
	void ElementaryExpression();			// Элементарное выражение
	void Cycle();							// Цикл
	void ReturnStatement();					// Оператор возврата (return)
	int LookForward(int pointer);
	int Scan(TypeLex lex);
	void Tclass();
	void classDesc();

public:
	Diagramm(Scanner* scaner, Tree* tree);
	void Program();							// Программа
};