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
// Revision 17/12/2001 - Save and Load Controller, By JAF
// Header File fuzzy_control.h


                	 // Kinds of defuzzification

#define MAXIMUM		1// Value of maximum activation of output set

#define AVERAGEOFMAX 	2// Average of activations of output sets 

#define CENTEROFAREA 	3// Center of area of activated output sets
#define CENTROID        3// Center of area(or CENTROID) of activated output sets

// Class fuzzy_control : receive all rules, executes the inference engine
// and the defuzzification process

class fuzzy_control
{
protected:
   	linguisticvariable lingvarinput1,lingvarinput2,lingvarinput3;
	linguisticvariable lingvaroutput;
	int numinputvars;
	int numrules;
	rule *rulebase[MAXRULES];
	float activationofrule[MAXRULES];
	int kindofdefuzzification;
	float defuzzify();
	float defuzzifyMAX();
	float defuzzifyMOM();
	float defuzzifyCOA();
	void loadrulebase(FILE *file);

public:

	fuzzy_control(){kindofdefuzzification=MAXIMUM;numrules=0;};
	fuzzy_control(int kindofdefuzz){kindofdefuzzification=kindofdefuzz;numrules=0;};
	int getkindofdefuzzification() { return kindofdefuzzification;};
	int getnuminputvars() { return numinputvars;};
	int getnumrules() { return numrules;};
	rule *getrule(int i) { return rulebase[i];};
	void set_defuzz(int kindofdefuzz){kindofdefuzzification=kindofdefuzz;};
	int definevars(linguisticvariable &input1,linguisticvariable &output);
	int definevars(linguisticvariable &input1,linguisticvariable &input2,
	            linguisticvariable &output);
	int definevars(linguisticvariable &input1,linguisticvariable &input2,
	           linguisticvariable &input3,linguisticvariable &output);
	int insert_rule(rule& ruletoinsert);
	int insert_rule(const char *setofinplingvar1,const char *setofoutlingvar);
	int insert_rule(const char *setofinplingvar1,const char *setofinplingvar2,
	             const char *setofoutlingvar);

	int insert_rule(const char *setofinplingvar1,const char *setofinplingvar2,
	            const char *setofinplingvar3,const char *setofoutlingvar);

	float make_inference(float inputval1);
	float make_inference(float inputval1,float inputval2);
	float make_inference(float inputval1,float inputval2,float inputval3);
	float getnumoflingvars() { return numinputvars;};

	linguisticvariable *getlingvarinput1(){return &lingvarinput1;};
	linguisticvariable *getlingvarinput2(){return &lingvarinput2;};
	linguisticvariable *getlingvarinput3(){return &lingvarinput3;};
	linguisticvariable *getlingvaroutput(){return &lingvaroutput;};
	void save_m(const char *name, float error);
	void save(const char *name, float error);
	void load(const char *name);
};

