#pragma once

#include "Scanner.h"

enum type_data
{
	TYPE_UNKNOWN = 0,
	TYPE_INTEGER = 1,
	TYPE_DOUBLE = 2,
};

enum type_object
{
	OBJ_VAR = 0,
	OBJ_FUNC = 1,
	OBJ_CLASS = 2,
	OBJ_CLASS_OBJ = 3,
};

class Tree;

struct Node
{
	std::string id;
	type_object objectType;
	type_data dataType;
	int flagInit;
	Tree* pointer; // ”казатель на узел
	void setInit()
	{
		flagInit = 1;
	};
};

class Tree
{
private:
	Node* node;
	Tree* up;
	Tree* left;
	Tree* right;
public:
	Tree();
	Tree(Tree*, Tree*, Tree*, Node*);
	~Tree();
	void PrintError(std::string errorMessage, std::string lexeme);
	void SetLeft(Node*);
	void SetRight(Node*);
	Tree* GetLeft();
	Tree* GetRight();
	type_object GetSelfObjectType();
	type_data GetSelfDataType();
	std::string GetSelfId();
	bool IsSelfInit();
	Tree* FindMethod(const TypeLex& lex);
	Tree* GetNode();
	Tree* FindUp(Tree*, std::string);
	Tree* FindUp(std::string);
	Tree* FindUp(Tree*, std::string, type_object);
	Tree* FindUp(std::string, type_object);
	Tree* FindUp(Tree*, type_object);
	Tree* FindUp(type_object);
	Tree* FindFunction(const TypeLex& lex);
	Tree* FindUpOneLevel(Tree*, std::string);
	Tree* FindRightLeft(Tree* from, std::string id);
	Tree* FindRightLeft(std::string id);
	Tree* FindLeft(Tree* from, std::string id);
	Tree* FindLeft(std::string id);
	void SetInit();
	type_data GetDataType(int);
	type_data GetTypeResult(type_data, type_data, int);
	void Print(int);
	void Print();
	bool IsDoublicateId(Tree*, std::string);
	bool IsAllowChangeId(std::string);
	bool IsMainExists();
	bool CanBeAdded(type_data type1, type_data type2);
	bool CanBeAdded(int type1, int type2);

};