//# FLIE - Fuzzy Logic Inference Engine
/*####################################################################################
Copyright 2018 Joao Fabro

Permission is hereby granted, free of charge, to any person obtaining a copy of this 
software and associated documentation files (the "Software"), to deal in the Software 
without restriction, including without limitation the rights to use, copy, modify, merge, 
publish, distribute, sublicense, and/or sell copies of the Software, and to permit 
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or 
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE 
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
DEALINGS IN THE SOFTWARE.
###################################################################################*/
	
// fuzzfier.h
// program to fuzzify data

#ifndef _CATEGORY_CLASSES
#define _CATEGORY_CLASSES
#include <iostream>
using namespace std;

#define NOTSET 0.000131415

class category
{
private:
	char name[30];
	float lowval,highval,midval;
	float output;

public:
	category(){};
	void setname(const char *);
	char * getname();	
	void setval(float, float, float);
	float getlowval();
	float getmidval();
	float gethighval();

	float getshare(const float&);
	void setoutput(const float&);
	void clearoutput();
	float getoutput();
	friend ostream& operator<<(ostream& fluxo, category tc);

	~category(){};
};

class trapezoid_category
{
private:

	char name[30];
	int number;
	float lowval,highval,midvallow, midvalhigh;
	float output;
	float rangelow, rangehigh;

public:
	trapezoid_category();		
	trapezoid_category(int);
	void setname(const char *);
	char * getname();
	void setnumber(int t) {number = t;};
	int getnumber() {return(number);};
	void setrange(float, float);
	float getrangelow(){return(rangelow);};
	float getrangehigh(){return(rangehigh);};
	void setrandomval();
	void setrighttrapezoidrandomval();
	void setlefttrapezoidrandomval();
	void setval(float , float, float, float);
	void setval(float, float, float);
	void move_lowval();
	void change_lowval(){};
	float getlowval(){return lowval;};
	float getmidvallow(){return midvallow;};
	void move_midvallow();
	void change_midvallow(){};
	float getmidval(); // Returns average between midvallow and midvalhigh
	float getmidvalhigh(){return midvalhigh;};
	void move_midvalhigh();
	void change_midvalhigh(){};
	float gethighval(){return highval;};
	void move_highval();
	void change_highval(){};

	float getshare(const float&);
	void setoutput(const float&);
	void clearoutput();
	float getoutput();
   	trapezoid_category(const trapezoid_category &tc);
   	trapezoid_category &operator=(const trapezoid_category &tc);
   	bool operator==(const trapezoid_category &tc) const;
   	bool operator!=(const trapezoid_category &tc) const;
   	friend ostream& operator<<(ostream& fluxo, trapezoid_category tc);

	void save_m(FILE *file, int number);
	void save(FILE *file);
	void load(FILE *file);

	~trapezoid_category(){};
};

typedef trapezoid_category fuzzy_set;
typedef trapezoid_category fuzzyset;

int randnum(int);


#endif
