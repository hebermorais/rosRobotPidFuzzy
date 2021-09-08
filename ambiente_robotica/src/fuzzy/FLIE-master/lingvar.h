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
	
// Project FLIE-Fuzzy Logic Inference Engine - Joao Alberto Fabro - out/1996

// Header File lingvar.h 



#define MAXCATEGORIES 11 // Maximum number of fuzzy sets that define a ling. variable



// Class linguisticvariable - contains all fuzzy sets that define one variable

class linguisticvariable
{
private:
	char name[30];
	int numcategories;
	trapezoid_category *cats[MAXCATEGORIES];

public:
	linguisticvariable();
    linguisticvariable& operator=(const linguisticvariable& l);
    void setname(const char*);
    const char *getname();
    int includecategory(trapezoid_category*);
    int setcatptr(int,trapezoid_category*);
    trapezoid_category& getcat(const char*);
    trapezoid_category& getcat(int);
    trapezoid_category* getcatptr(int);
    int getnumofcategories(){return(numcategories);};
    void clearoutputcategoryactivations();
    void save_m(FILE *file, const char* number);
    void save(FILE *file);
    void load(FILE *file);
};

