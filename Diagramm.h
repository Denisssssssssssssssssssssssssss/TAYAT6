#pragma once

#include "Scanner.h"
#include "Tree.h"

class Diagramm
{
private:
	Scanner* scanner;
	Tree* tree;
	bool inClass = false;
	void Description();						// ��������
	void Data();							// ������
	void Function();						// �������
	void Type();							// ���
	void List();							// ������
	void Variable();						// ����������
	void Assignment();						// ������������
	void Expression();						// ���������
	void CompositeOperator();				// ��������� ��������
	void OperatorsAndDescriptions();		// ��������� � ��������
	void MemberAccess();					//������ � ������ ������
	void Operator();						// ��������
	void FunctionCall();					// ����� �������
	void FunctionCall(Tree* tree);					// ����� �������
	void Comparison();						// ���������
	void Summand();							// ���������
	void Multiplier();						// ���������
	void UnaryOperation();					// ������� ��������
	void ElementaryExpression();			// ������������ ���������
	void Cycle();							// ����
	void ReturnStatement();					// �������� �������� (return)
	int LookForward(int pointer);
	int Scan(TypeLex lex);
	void Tclass();
	void classDesc();

public:
	Diagramm(Scanner* scaner, Tree* tree);
	void Program();							// ���������
};