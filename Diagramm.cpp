#include "Diagramm.h"
#include "Tree.h"

Diagramm::Diagramm(Scanner* scanner, Tree* tree)
{
	this->scanner = scanner;
	this->tree = tree;
}

int Diagramm::LookForward(int pos)
{
	TypeLex lex;
	int saved_pointer = scanner->getPointer();
	int next_type;
	for (int i = 0; i < pos; i++)
		next_type = scanner->Scan(lex);
	scanner->putPointer(saved_pointer);
	return next_type;
}

int Diagramm::Scan(TypeLex lex)
{
	return scanner->Scan(lex);
}

void Diagramm::Tclass()
{
	inClass = true;
	TypeLex lex;
	int type;

	type = Scan(lex);

	if (type != typeClass)
		scanner->PrintError("Waiting class", lex);

	Tree* classNode = NULL;
	type_data typeData = tree->GetDataType(type);
	type = Scan(lex);

	if (type != typeID)
		scanner->PrintError("Waiting ID", lex);
	if (tree->IsDoublicateId(tree, lex))
		tree->PrintError("Reassignment", lex);

	Node* newNode = new Node();
	newNode->id = lex;
	newNode->objectType = OBJ_CLASS;
	newNode->dataType = typeData;
	if (classNode != NULL) newNode->pointer = classNode;
	tree->SetLeft(newNode);
	tree = tree->GetLeft();
	tree->SetRight(NULL);
	Tree* tmpTree = tree;
	tree = tree->GetRight();

	type = Scan(lex);

	if (type != typeLeftBrace)
		scanner->PrintError("Waiting symbol {", lex);

	type = LookForward(1);

	while (type != typeRightBrace) {
		classDesc();
		type = LookForward(1);
	}

	type = Scan(lex);

	if (type != typeRightBrace)
		scanner->PrintError("Waiting symbol }", lex);
	tree = tmpTree;
	inClass = false;
	type = Scan(lex);
	if (type != typeSemicolon)
		scanner->PrintError("Expected ; got", lex);
}

void Diagramm::classDesc()
{
	TypeLex lex;
	int type;
	type = LookForward(3);
	if (LookForward(1) == typeID && LookForward(2) == typeLeftBracket && LookForward(3) == typeRightBracket && LookForward(4) == typeLeftBrace)
		Function();
	if (type == typeLeftBracket) {
		Function();
	}
	else Data();
}

void Diagramm::Program()
{
	TypeLex lex;
	int type;
	type = LookForward(1);
	while (type == typeInt || type == typeDouble || type == typeClass)
	{
		Description();
		type = LookForward(1);
	}
	if (type != typeEnd)
	{
		type = Scan(lex);
		scanner->PrintError("ожидался конец, ", lex);
	}
}

void Diagramm::Description()
{
	TypeLex lex;
	int type = LookForward(1);
	int simbol = LookForward(3);
	if ((type == typeInt || type == typeDouble) && simbol != typeLeftBracket)
	{
		Data();
		return;
	}
	if (type == typeClass) {
		Tclass();
		return;
	}
	if ((type == typeInt || type == typeDouble) && simbol == typeLeftBracket)
	{
		Function();
		return;
	}
	type = Scan(lex);
	if (type == typeEnd) {
		type = Scan(lex);
		return;

	}
	scanner->PrintError("ожидался тип (int, short, long, float), ", lex);
}

void Diagramm::List()
{
	TypeLex lex;
	int type, pointer;
	int typeData = LookForward(1);
	//Scan(lex);
	Variable(typeData);
	type = LookForward(1);
	while (type == typeComma)
	{
		type = Scan(lex);
		Variable(typeData);
		type = LookForward(1);
	}
}

void Diagramm::Data()
{
	TypeLex lex;
	int type_;
	type_ = LookForward(3);
	if (type_ == typeLeftBracket) {
		Function();
		return;
	}
	Type();
	List();
	type_ = Scan(lex);
	if (type_ != typeSemicolon)
	{
		scanner->PrintError("ожидалась ;, ", lex);
	}
}

void Diagramm::Function()
{
	TypeLex lex;
	int type = Scan(lex);
	if (type != typeInt &&  type != typeDouble)
	{
		scanner->PrintError("ожидался тип (int, short, long, float), ", lex);
	}
	Tree* classNode = (inClass) ? tree->FindUp(lex) : nullptr;
	type = Scan(lex);

	if (type != typeID && type != typeMain)
	{
		scanner->PrintError("ожидался идентификатор, ", lex);
	}
	if (tree->IsDoublicateId(tree, lex)) {
		scanner->PrintError("Переопределение", lex);
	}

	// Создаём новый узел для функции
	Node* newNode = new Node();
	newNode->id = lex;  // Назначаем идентификатор
	newNode->objectType = OBJ_FUNC;
	newNode->dataType = tree->GetDataType(type);
	newNode->pointer = classNode;

	// Вставляем узел в дерево
	tree->SetLeft(newNode);
	tree = tree->GetLeft(); // Переход к новому узлу
	tree->SetRight(NULL);

	Tree* tmpTree = tree; // Сохраняем текущий указатель дерева
	tree = tree->GetRight(); // Переход к правому поддереву

	type = Scan(lex);
	if (type != typeLeftBracket)
	{
		scanner->PrintError("ожидалась (, ", lex);
	}

	type = Scan(lex);
	if (type != typeRightBracket)
	{
		scanner->PrintError("ожидалась ), ", lex);
	}

	type = Scan(lex);
	if (type != typeLeftBrace)
	{
		scanner->PrintError("ожидалась {, ", lex);
	}

	OperatorsAndDescriptions();

	// Возвращаемся к предыдущему узлу
	tree = tmpTree;

	type = Scan(lex);
	if (type != typeRightBrace)
	{
		scanner->PrintError("ожилалась }, ", lex);
	}
}

void Diagramm::Type()
{
	TypeLex lex;
	int type;
	type = Scan(lex);
	if (type != typeInt &&  type != typeDouble)
	{
		scanner->PrintError("ожидался тип (int, short, long, float), ", lex);
	}
}

void Diagramm::Variable(int typeData)
{
	TypeLex lex;
	Node* newNode = new Node();
	int type = LookForward(1);// вериабл под вопросом

	/*if (typeData != typeInt && typeData != typeDouble)
	{
		scanner->PrintError("ожидался тип (int, short, long, float), ", lex);
	}*/
	if (typeData == constInt)
		newNode->dataType = TYPE_INTEGER;
	else if (typeData == constDouble)
		newNode->dataType = TYPE_DOUBLE;
	else
		newNode->dataType = TYPE_UNKNOWN;

	if (type == typeInt || type == typeDouble)
	{
		Scan(lex);
		newNode->objectType = OBJ_VAR;
		newNode->dataType = tree->GetDataType(type);
	}
	/*else
		if (type == typeID) {
			Scan(lex);
			newNode->pointer = tree->FindUp(lex);
			newNode->objectType = OBJ_CLASS_OBJ;
		}*/

	type = LookForward(1);
	Tree* varNode = NULL;

	if (type != typeID)
	{
		type = Scan(lex);
		scanner->PrintError("ожидался идентификатор, ", lex);
	}
	else if (LookForward(2) == typePoint) {
		MemberAccess();
	}
	int pointer = scanner->getPointer();
	type = Scan(lex);

	if (tree->IsDoublicateId(tree, lex)) {
		tree->PrintError("Переопределение", lex);
	}

	newNode->id = lex;  // Устанавливаем идентификатор

	newNode->dataType = tree->GetDataType(type);

	type = LookForward(1);
	if (type == typeEval) {
		newNode->flagInit = 1;
	}
	else
	{
		newNode->flagInit = 0;
	}

	// Добавляем узел в левое поддерево
	tree->SetLeft(newNode);

	// Переход к левому дочернему узлу для дальнейших операций
	tree = tree->GetLeft();

	scanner->putPointer(pointer);

	type = LookForward(2);
	if (type == typeEval)
	{
		Assignment();
		return;
	}
	type = Scan(lex);
}

void Diagramm::Assignment()
{
	TypeLex lex;
	int type = Scan(lex);

	if (type != typeID)
	{
		scanner->PrintError("ожидался идентификатор, ", lex);
	}
	Tree* node = tree->FindUp(lex);
	if (node == NULL) {
		scanner->PrintError("Семантическая ошибка. ID не найден", lex);
	}
	node->SetInit();

	// Получаем тип переменной узла
	type_data varType = node->GetSelfDataType();
	type = LookForward(1);
	if (LookForward(1) == typePoint) {
		MemberAccess();
	}
	type = Scan(lex);
	if (type != typeEval)
	{
		scanner->PrintError("ожидалось =, ", lex);
	}	
		Expression();
}

void Diagramm::Expression()
{
	TypeLex lex;
	int type;

	Comparison();
	type = LookForward(1);
	while (type == typeEq || type == typeUnEq)
	{
		type = Scan(lex);
		Comparison();
		type = LookForward(1);
	}
}

void Diagramm::CompositeOperator()
{
	TypeLex lex;
	Tree* varNode = NULL;
	int type = Scan(lex);
	type_data typeData = tree->GetDataType(type);

	if (type != typeLeftBrace)
	{
		scanner->PrintError("ожидалась {, ", lex);
	}

	Node* newNode = new Node();
	newNode->id = lex;
	newNode->objectType = OBJ_FUNC;
	newNode->dataType = typeData;
	if (varNode != NULL) newNode->pointer = varNode;
	tree->SetLeft(newNode);
	tree = tree->GetLeft();
	tree->SetRight(NULL);
	Tree* tmpTree = tree;
	tree = tree->GetRight();

	OperatorsAndDescriptions();

	type = Scan(lex);
	if (type != typeRightBrace)
	{
		scanner->PrintError("ожидалась }, ", lex);
	}
	tree = tmpTree;
}

void Diagramm::OperatorsAndDescriptions()
{
	TypeLex lex;
	int type;
	int loops();
	type = LookForward(1);
	while (type != typeRightBrace) {
		if ((type == typeInt || type == typeDouble || (type == typeID && LookForward(2) != typeEval && LookForward(2) != typePoint)) && LookForward(3) != typeLeftBracket) {
			Data();
		}
		else Operator();
		if (type == typeReturn) {
			return;
		}
		type = LookForward(1);
		
	}
}

void Diagramm::MemberAccess() {
	TypeLex lex;
	int type;

	type = Scan(lex);
	if (type != typeID) {
		scanner->PrintError("Expected identifier", lex);
	}

	
	Tree* objectNode = tree->FindUp(lex);
	if (objectNode == NULL) {
		scanner->PrintError("Object not found", lex);
		return;
	}

	
	if (objectNode->GetSelfObjectType() == OBJ_CLASS_OBJ) {
		
		type = LookForward(1);
		if (type != typePoint) {
			return;
		}

		Scan(lex); 

		type = LookForward(1); 
		if (type != typeID) {
			scanner->PrintError("Expected identifier after '.'", lex);
			return; 
		}

		
		Tree* methodNode = objectNode->GetNode();
		if (methodNode == nullptr) {
			scanner->PrintError("Method not found", lex);
			return;
		}
		else
			if (LookForward(2) == typeLeftBracket)
				FunctionCall(methodNode);
	}

	
	type = LookForward(1);
	if (type == typeID)
	{
		Tree* methodNode = objectNode->GetNode();
		if (methodNode == nullptr) {
			scanner->PrintError("identifier not found in class", lex);
			return;
		}
		else {
			Scan(lex);
			Tree* idNode = methodNode->FindRightLeft(lex);
			if (idNode == NULL) {
				scanner->PrintError("identifier not found in class", lex);
				return; 
			}
			if (idNode->IsSelfInit() == 0) {
				scanner->PrintError("Semant Error. Variable is not initialized", lex);
				return; 
			}
			type = LookForward(1);
		}
	}
	if (type == typeEval) {
		Assignment();
	}
	else {
		Expression();
	}
}

void Diagramm::Operator()
{
	TypeLex lex;
	int type = LookForward(1);

	if (type == typeReturn)
	{
		ReturnStatement();
		return;
	}

	if (type == typeSemicolon)
	{
		type = Scan(lex);
		return;
	}

	if (type == typeLeftBrace)
	{
		CompositeOperator();
		return;
	}

	if (type == typeFor) 
	{
		Cycle();
		return;
	}

	int type2 = LookForward(2);
	if (type == typeID && type2 == typeLeftBracket)
	{
		FunctionCall();
		return;
	}

	if (type == typeID && type2 == typeEval)
	{
		Assignment();
		type = Scan(lex);
		if (type != typeSemicolon)
			scanner->PrintError("ожидалась ;, ", lex);
		return;
	}

	if (type == typeID)
	{
		Expression();
		return;
	}

	type = Scan(lex);
	scanner->PrintError("ожидался оператор, ", lex);
}

void Diagramm::ReturnStatement()
{
	TypeLex lex;
	int type = Scan(lex);

	if (type != typeReturn)
	{
		scanner->PrintError("ожидалось return, ", lex);
	}

	Expression();

	type = Scan(lex);
	if (type != typeSemicolon)
	{
		scanner->PrintError("ожидалась ; после return <выражение>, ", lex);
	}
}

void Diagramm::Cycle()
{
	TypeLex lex;
	int type = Scan(lex);

	if (type != typeFor)
	{
		scanner->PrintError("ожидалось for, ", lex);
	}

	type = Scan(lex);
	if (type != typeLeftBracket)
	{
		scanner->PrintError("ожидалась (, ", lex);
	}

	Assignment();

	type = Scan(lex);
	if (type != typeSemicolon)
	{
		scanner->PrintError("ожидалась ;, ", lex);
	}

	Comparison();

	type = Scan(lex);
	if (type != typeSemicolon)
	{
		scanner->PrintError("ожидалась ;, ", lex);
	}
	Assignment();

	type = Scan(lex);
	if (type != typeRightBracket)
	{
		scanner->PrintError("ожидалась ), ", lex);
	}

	Operator();
}

void Diagramm::FunctionCall()
{
	TypeLex lex;
	int type = Scan(lex);

	if (type != typeID)
	{
		scanner->PrintError("ожидался идентификатор, ", lex);
	}

	// Ищем узел, называющийся объектом
	Tree* objectNode = tree->FindUp(lex);
	// Получаем указатель на функцию из функции с тем же именем в родительском узле
	Tree* methodNode = objectNode->FindFunction(lex); // Функция для поиска по имени функции в родительском узле на findUp
	if (methodNode == NULL) {
		scanner->PrintError("Method not found", lex);
		return; 
	}

	
	if (methodNode->GetSelfObjectType() != OBJ_FUNC) {
		scanner->PrintError("Not a method", lex);
	}

	if (LookForward(1) == typePoint) {
		MemberAccess();
		return;
	}
	type = Scan(lex);
	if (type != typeLeftBracket)
	{
		scanner->PrintError("ожидалась (, ", lex);
	}

	type = Scan(lex);
	if (type != typeRightBracket)
	{
		scanner->PrintError("ожидалась ), ", lex);
	}

	/*type = Scan(lex);
	if (type != typeSemicolon)
	{
		scanner->PrintError("ожидалась ;, ", lex);
	}*/
}
void Diagramm::FunctionCall(Tree* tree) {
	TypeLex lex;
	int type;

	type = Scan(lex);

	if (type != typeID) {
		scanner->PrintError("Expected identifier got", lex);
	}
	
	Tree* objectNode = tree->FindRightLeft(lex);
	
	Tree* methodNode = objectNode->FindMethod(lex); 
	if (methodNode == NULL) {
		scanner->PrintError("Method not found", lex);
		return; 
	}

	
	if (methodNode->GetSelfObjectType() != OBJ_FUNC) {
		scanner->PrintError("Not a method", lex);
	}

	if (LookForward(1) == typePoint) {
		MemberAccess();
		return;
	}

	type = Scan(lex);
	if (type != typeLeftBracket) {
		scanner->PrintError("Expected ( got", lex);
	}

	type = Scan(lex);
	if (type != typeRightBracket) {
		scanner->PrintError("Expected ) got", lex);
	}
}

void Diagramm::Comparison() 
{
	TypeLex lex;
	Summand(); // ЗДесь был ПОБИТОВЫЙ СДВИГ ВМЕСТО СЛАГАЕМОГО
	int type = LookForward(1);
	while (type == typeLess || type == typeLessOrEq || type == typeMore || type == typeMoreOrEq)
	{
		type = Scan(lex);
		Summand(); // ЗДесь был ПОБИТОВЫЙ СДВИГ ВМЕСТО СЛАГАЕМОГО
		Tree* node = tree->FindUp(lex);
		//if (node == nullptr) {
		//	scaner->PrintError("Семантическая ошибка. Переменная не инициализирована", lex);
		//}
		type = LookForward(1);
	}
}


void Diagramm::Summand()
{
	TypeLex lex;
	int type;
	Multiplier();
	type = LookForward(1);
	while (type == typePlus || type == typeMinus)
	{
		type = Scan(lex);
		Multiplier();
		type = LookForward(1);
	}
}

void Diagramm::Multiplier()
{
	TypeLex lex;
	int type;
	UnaryOperation();
	type = LookForward(1);
	while (type == typeMul || type == typeDiv || type == typeMod)
	{
		type = Scan(lex);
		Tree* node = tree->FindUp(lex);
		UnaryOperation();
		type = LookForward(1);
	}
}

void Diagramm::UnaryOperation()
{
	TypeLex lex;
	int type = LookForward(1);

	if (type == typePlus || type == typeMinus)
	{
		type = Scan(lex);
		ElementaryExpression();
	}
	else
	{
		ElementaryExpression();
	}
}


void Diagramm::ElementaryExpression()
{
	TypeLex lex;
	int type = LookForward(1);
	if ( type == constInt || type == constDouble) {
		type = Scan(lex);
		return;
	}
	if (type == typeID)
	{
		type = Scan(lex); 
		Tree* node = tree->FindUp(lex);
		if (node == nullptr) {
			scanner->PrintError("Semant Error. Variable not found", lex);
			//semanticTree->PrintError("Variable is not initialized", lex);
		}
		if (node->GetSelfObjectType() == OBJ_CLASS_OBJ) {
			scanner->PrintError("Semant Error. Cannot use class object", lex);
			//semanticTree->PrintError("Variable is not initialized", lex);
		}
		if (node->IsSelfInit() == 0) {
			scanner->PrintError("Semant Error. Variable is not initialized", lex);
			//semanticTree->PrintError("Variable is not initialized", lex);
		}
		
		if (LookForward(1) == typePoint) {
			MemberAccess();
			return;
		}

		if (LookForward(1) == typeLeftBracket) {
			FunctionCall();
			return;
		}
		if (type == typePoint) {
			type = Scan(lex);
			return;
		}


		return;
	}

	type = Scan(lex);
	scanner->PrintError("ожидалось выражение, ", lex);
}