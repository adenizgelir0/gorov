#include "Num.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

Num::Num(int val)
{
	type = INT;
	num.intnum = val;
}

Num::Num(double val)
{
	type = DOUBLE;
	num.dubnum = val;
}
Num::Num()
{
	type = INT;
	num.intnum = 0;
}


Num operator+(const Num &A, const Num &B) 
{
    if(A.type == DOUBLE)
    {
        if(B.type == DOUBLE)
            return Num(A.num.dubnum + B.num.dubnum);
        return Num(A.num.dubnum + B.num.intnum);
    }   
    else
    {   
        if(B.type == DOUBLE)
            return Num(A.num.intnum + B.num.dubnum);
        return Num(A.num.intnum + B.num.intnum);
    }   
}

Num operator-(const Num &A, const Num &B) 
{
    if(A.type == DOUBLE)
    {   
        if(B.type == DOUBLE)
            return Num(A.num.dubnum - B.num.dubnum);
        return Num(A.num.dubnum - B.num.intnum);
    }   
    else
    {   
        if(B.type == DOUBLE)
            return Num(A.num.intnum - B.num.dubnum);
        return Num(A.num.intnum - B.num.intnum);
    }   
}

Num operator*(const Num &A, const Num &B) 
{
    if(A.type == DOUBLE)
    {   
        if(B.type == DOUBLE)
            return Num(A.num.dubnum * B.num.dubnum);
        return Num(A.num.dubnum * B.num.intnum);
    }   
    else
    {   
        if(B.type == DOUBLE)
            return Num(A.num.intnum * B.num.dubnum);
        return Num(A.num.intnum * B.num.intnum);
    }   
}

Num operator/(const Num &A, const Num &B) 
{
	if((B.type == DOUBLE && abs(B.num.dubnum)<1e-9)
			|| (B.type == INT && B.num.intnum == 0))
		return Num(0);
    if(A.type == DOUBLE)
    {	
        if(B.type == DOUBLE)
            return Num(A.num.dubnum / B.num.dubnum);
        return Num(A.num.dubnum / B.num.intnum);
    }   
    else
    {   
        if(B.type == DOUBLE)
            return Num(A.num.intnum / B.num.dubnum);
        return Num(static_cast<double>(A.num.intnum) / B.num.intnum);
    }   
}

Num operator==(const Num &A, const Num &B)
{
	if(A.type != B.type)
		return false;
	if(A.type == DOUBLE)
		return abs(A.num.dubnum - B.num.dubnum) < 1e-9;
	return A.num.intnum == B.num.intnum;
}

Num operator!=(const Num &A, const Num &B)
{
	if(A.type != B.type)
		return true;
	if(A.type == DOUBLE)
		return abs(A.num.dubnum - B.num.dubnum) > 1e-9;
	return A.num.intnum != B.num.intnum;
}

Num floor(const Num &N)
{
	if(N.type == INT)
		return Num(N.num.intnum);
	return Num(static_cast<int>(floor(N.num.dubnum)));
}

Num ceil(const Num &N)
{
	if(N.type == INT)
		return Num(N.num.intnum);
	return Num(static_cast<int>(floor(N.num.dubnum)));
}

Num abs(const Num &N)
{
	if(N.type == INT)
		return Num(abs(N.num.intnum));
	return Num(abs(N.num.dubnum));
}

Num sqrt(const Num &N)
{
	if(N.type == INT)
		return Num(sqrt(abs(N.num.intnum)));
	return Num(sqrt(abs(N.num.dubnum)));
}
Num log(const Num &N)
{
	if(N.type == INT)
	{
		if(N.num.intnum == 0)
			return Num(0.0);
		return Num(log(abs(N.num.intnum)));
	}
	if(abs(N.num.dubnum) < 1e-9)
		return Num(0.0);
	return Num(log(abs(N.num.dubnum)));
}

Num sin(const Num &N)
{
	if(N.type == INT)
		return Num(sin(N.num.intnum));
	return Num(sin(N.num.dubnum));
}

Num cos(const Num &N)
{
	if(N.type == INT)
		return Num(cos(N.num.intnum));
	return Num(cos(N.num.dubnum));
}


std::ostream& operator<<(std::ostream &os, const Num &N) 
{
    if(N.type == DOUBLE)
		os << N.num.dubnum;
	else
		os << N.num.intnum;
	return os;
}
