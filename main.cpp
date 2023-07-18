#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include "Num.h"
#include "Expr.h"
const int N=100000;
struct Res
{
	double cost;
	int length;
	Expr *expr;

	Res(double c, int l, Expr *E): cost(c), length(l), expr(E){}
};

bool operator<(const Res &A, const Res &B)
{
	if(std::abs(A.cost-B.cost)<1e-5)
		return (A.length < B.length);
	return (A.cost < B.cost);
}
std::ostream& operator<<(std::ostream &os, const Res &R)
{
	os << *(R.expr) << " " << R.cost << " " << R.length;
	return os;
}


int main()
{
	std::ifstream file;
	file.open("test");
	std::vector<double> test_data;
	double tmp;
	while(file >> tmp) test_data.push_back(tmp);

	std::vector<Res> V; 
	int n=N;
	Num map[256];
	map['p'] = Num(atan(1)*4);
	map['e'] = Num(exp(1));
	while(n--)
	{
		Expr *E = random_expr((std::rand()%3)+1);
		double cost = 0;
		for(int i=0; i<test_data.size(); i++)
		{
			map['n'] = Num(i+1);
			Num result = E->exec(map);
			if(result.type == DOUBLE)
				cost += std::abs(result.num.dubnum - test_data[i]);
			else
				cost += std::abs(result.num.intnum - test_data[i]);

		}
		std::stringstream s;
		s << *E;
		int length = s.str().length();
		V.push_back(Res(cost,length,E));
	}
	int gen=0;
	while(true)
	{
		std::sort(V.begin(),V.end());
		n=N-20;
		while(n--)
		{
			delete V[V.size()-1].expr;
			V.pop_back();
		}
		std::cout << "GEN " << gen << " ====================\n";
		std::cout << V[0] << "\n" << V[1] << "\n";
		while(V.size() < N)
		{

			Expr *E1 = clone_expr(V[rand()%20].expr);
			Expr *E2 = clone_expr(V[rand()%20].expr);
			cross_expr(E1,E2);
			if(rand()%100 == 0)
				mutate_expr(E1);
			if(rand()%100 == 0)
				mutate_expr(E2);
			double cost=0;
			for(int i=0; i<test_data.size(); i++)
			{
				map['n'] = Num(i+1);
				Num result = E1->exec(map);
				if(result.type == DOUBLE)
					cost += std::abs(result.num.dubnum - test_data[i]);
				else
					cost += std::abs(result.num.intnum - test_data[i]);

			}
			std::stringstream s;
			s << *E1;
			int length = s.str().length();
			V.push_back(Res(cost,length,E1));

			cost=0;
			for(int i=0; i<test_data.size(); i++)
			{
				map['n'] = Num(i+1);
				Num result = E2->exec(map);
				if(result.type == DOUBLE)
					cost += std::abs(result.num.dubnum - test_data[i]);
				else
					cost += std::abs(result.num.intnum - test_data[i]);

			}
			s.str("");
			s << *E2;
			length = s.str().length();
			V.push_back(Res(cost,length,E2));

			for(int i=0; i<10; i++)
			{
				Expr *B1 = V[i].expr;
				Expr *B2 = V[i+10].expr;
				cross_expr(B1,B2);
				double cost1=0;
				double cost2=0;
				for(int j=0; j<test_data.size(); j++)
				{
					map['n'] = Num(j+1);
					Num result1 = B1->exec(map);
					Num result2 = B2->exec(map);
					if(result1.type == DOUBLE)
						cost1 += std::abs(result1.num.dubnum - test_data[j]);
					else
						cost1 += std::abs(result1.num.intnum - test_data[j]);

					if(result2.type == DOUBLE)
						cost2 += std::abs(result2.num.dubnum - test_data[j]);
					else
						cost2 += std::abs(result2.num.intnum - test_data[j]);
				}
				std::stringstream s1;
				s1 << *B1;
				int length1 = s1.str().length();
				V[i] = Res(cost1,length1,B1);
				std::stringstream s2;
				s2 << *B2;
				int length2 = s2.str().length();
				V[i+10] = Res(cost2,length2,B2);
			}
		}
		gen++;

	}
}
