#pragma once
#include <iostream>


enum NumType {INT,DOUBLE};

class Num
{
	union NumU
	{
		int intnum;
		double dubnum;
	};

	public:

	NumType type;
	NumU num;
	
	Num(int val);
	Num(double val);
	Num();


	//Num operator * (const Num&);
	//Num operator / (const Num&);
};

Num operator*(const Num&, const Num&);
Num operator/(const Num&, const Num&);
Num operator+(const Num&, const Num&);
Num operator-(const Num&, const Num&);
Num operator==(const Num&, const Num&);
Num operator!=(const Num&, const Num&);
std::ostream& operator<<(std::ostream&, const Num&);
Num floor(const Num&);
Num ceil(const Num&);
Num abs(const Num&);
Num sqrt(const Num&);
Num log(const Num&);
Num sin(const Num&);
Num cos(const Num&);
