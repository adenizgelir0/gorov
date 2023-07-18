#pragma once

#include "Num.h"
#include <string>
#include <unordered_map>
#include <vector>


enum ExprType {NUM,VAR,OP};
enum OpType {ADD,SUB,DIV,MULT,FLOOR,CEIL,ABS,SQRT,LOG,SIN,COS};

class Expr
{
	struct ExprU
	{
		char var;
		Num num;
		OpType op;
	};

	public:
	ExprType type;
	ExprU expr;
	Expr *left;
	Expr *right;

	Expr(char);
	Expr(Num);
	Expr(OpType,Expr*,Expr*);
	Expr(OpType,Expr*);
	~Expr();
	Num exec(Num *map);
};

std::ostream& operator<<(std::ostream&, const Expr&);
Expr* random_expr(int);
Expr* clone_expr(Expr*);
void cross_expr(Expr*, Expr*);
void part_expr(Expr*,const std::vector<Expr *>&);
void mutate_expr(Expr*);
