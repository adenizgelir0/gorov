#include "Expr.h"
#include "Num.h"
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include <vector>

Expr::Expr(char var)
{
	type = VAR;
	expr.var = var;
	left = NULL;
	right = NULL;
}

Expr::Expr(Num N)
{
	type = NUM;
	expr.num = N;
	left = NULL;
	right = NULL;
}

Expr::Expr(OpType op, Expr *leftexpr, Expr *rightexpr)
{
	type = OP;
	expr.op = op;
	left = leftexpr;
	right = rightexpr;
}


Expr::Expr(OpType op, Expr *leftexpr)
{
	type = OP;
	expr.op = op;
	left = leftexpr;
	right = NULL;
}

Expr::~Expr()
{
	if(left != NULL)
		delete left;
	if(right != NULL)
		delete right;
}

Num Expr::exec(Num *map)
{
	if(type == OP)
	{
		switch(expr.op)
		{
			case ADD:
				return left->exec(map) + right->exec(map);
			case SUB:
				return left->exec(map) - right->exec(map);
			case DIV:
				return left->exec(map) / right->exec(map);
			case MULT:
				return left->exec(map) * right->exec(map);
			case FLOOR:
				return floor(left->exec(map));
			case CEIL:
				return floor(left->exec(map));
			case LOG:
				return log(left->exec(map));
			case SIN:
				return sin(left->exec(map));
			case COS:
				return cos(left->exec(map));
			case ABS:
				return abs(left->exec(map));
			case SQRT:
				return sqrt(left->exec(map));
		}
	}
	else if(type == VAR)
		return map[expr.var];
	return expr.num;
}

std::ostream& operator<<(std::ostream &os, const Expr &E)
{
	if(E.type == OP)
	{
		switch(E.expr.op)
		{
			case ADD:
				os << "(" << *(E.left) << "+" << *(E.right) << ")";
				break;
			case SUB:
				os << "(" << *(E.left) << "-" << *(E.right) << ")";
				break;
			case MULT:
				os << "(" << *(E.left) << "*" << *(E.right) << ")";
				break;
			case DIV:
				os << "(" << *(E.left) << "/" << *(E.right) << ")";
				break;
			case FLOOR:
				os << "floor(" << *(E.left) << ")";
				break;
			case CEIL:
				os << "ceil(" << *(E.left) << ")";
				break;
			case ABS:
				os << "|" << *(E.left) << "|";
				break;
			case SQRT:
				os << "sqrt(" << *(E.left) << ")";
				break;
			case LOG:
				os << "log(" << *(E.left) << ")";
				break;
			case SIN:
				os << "sin(" << *(E.left) << ")";
				break;
			case COS:
				os << "cos(" << *(E.left) << ")";
				break;
		}
	}
	else if(E.type == VAR)
		os <<  E.expr.var;
	else
		os << E.expr.num;
	return os;
}

Expr* random_expr(int n) 
{
	if(n==0)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::discrete_distribution<> d({7,1,1,1,1,1,1,1,1,1,1,1});
		int res = d(gen);
		if(res==0)
			return new Expr('n');
		if(res == 10)
			return new Expr('p');
		if(res == 11)
			return new Expr('e');
		return new Expr(Num(res));
	}
	else
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::discrete_distribution<> d({3,3,3,3,1,1,1,1,1,1,1,1});
		int res = d(gen);
		if(res==11)
			return random_expr(0);
		switch(res)
		{
			case ADD:
			case SUB:
			case DIV:
			case MULT:
				return new Expr(static_cast<OpType>(res),
						random_expr(n-1),random_expr(n-1));
			case FLOOR:
			case CEIL:
			case ABS:
			case SQRT:
			case LOG:
			case SIN:
			case COS:
				return new Expr(static_cast<OpType>(res),random_expr(n-1));
		}
	}
}

Expr *clone_expr(Expr *E)
{
	if(E == NULL)
		return NULL;
	if(E->type == NUM)
		return new Expr(E->expr.num);
	if(E->type == VAR)
		return new Expr(E->expr.var);
	return new Expr(E->expr.op,clone_expr(E->left),
			clone_expr(E->right));
}

void part_expr(Expr *E,std::vector<Expr *> &V)
{
	if(E == NULL)return;
	V.push_back(E);
	part_expr(E->right,V);
	part_expr(E->left,V);
}
/*
void cross_expr(Expr *A, Expr *B)
{
	std::vector<Expr *> A_parts;
	std::vector<Expr *> B_parts;
	part_expr(A,A_parts);
	part_expr(B,B_parts);
	std::srand(std::time(nullptr));
	Expr *A_chosen,*B_chosen;
	while(true)
	{
		A_chosen = A_parts[std::rand() % A_parts.size()];
		if(A_chosen->type == OP) break;
	}
	while(true)
	{
		B_chosen = B_parts[std::rand() % B_parts.size()];
		if(B_chosen->type == OP) break;
	}
	if(A_chosen->right != NULL)
	{
		Expr *tmp = A_chosen->right;
		A_chosen->right = B_chosen->left;
		B_chosen->left = tmp;
		return;
	}
	if(B_chosen->right != NULL)
	{
		Expr *tmp = B_chosen->right;
		B_chosen->right = A_chosen->left;
		A_chosen->left = tmp;
		return;
	}
	Expr *tmp = B_chosen->left;
	B_chosen->left = A_chosen->left;
	A_chosen->left = tmp;

}*/
void cross_expr(Expr *A, Expr *B)
{
	if(A->type != OP ||  B->type != OP)return;
	
	if(A->right != NULL)
	{
		Expr *tmp = A->right;
		A->right = B->left;
		B->left = tmp;
		return;
	}
	if(B->right != NULL)
	{
		Expr *tmp = B->right;
		B->right = A->left;
		A->left = tmp;
		return;
	}
	Expr *tmp = B->left;
	B->left = A->left;
	A->left = tmp;
}
void mutate_expr(Expr *E)
{
	std::vector<Expr *> E_parts;
	part_expr(E,E_parts);
	Expr *E_chosen;
	while(true)
	{
		E_chosen = E_parts[std::rand() % E_parts.size()];
		if(E_chosen->type == OP) break;
	}
	if(std::rand()%2 && E_chosen->right != NULL)
	{
		delete E_chosen->right;
		E_chosen->right = random_expr((std::rand()%2)+1);
		return;
	}
	delete E_chosen->left;
	E_chosen->left = random_expr((std::rand()%2)+1);
}
