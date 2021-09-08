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
// Header File rule.h

#define MAXRULES 150  // Maximum number of rules per rulebase for fuzzy_control


/* Class Rule - contains one rule of inference - can make inferences based on
 rules of 1, 2 or 3 predecessors and 1 sucessor. To define a rule, are necessary
 the fuzzy sets of predecessors and of the sucessor! Ex: 

 if Tempsense is Xlarge and Levelsense is Large then HeatKnob is Alot

 needs the following definition of rule:

 rule.definerule(SenseTemp.getcat("Xlarge"),SenseLevel.getcat("Large"), 
                   HeatKnob.getcat("Alot"));
*/


class rule
{
private:
	trapezoid_category *inputcat1, *inputcat2, *inputcat3;
	trapezoid_category *outputcat;

public:
	rule();
	void definerule(trapezoid_category *input1,trapezoid_category *output);
	void definerule(trapezoid_category *input1,trapezoid_category *input2,trapezoid_category *output);
	void definerule(trapezoid_category *input1,trapezoid_category *input2,trapezoid_category *input3,
                     	  trapezoid_category *output);
	float evaluaterule(float &inputval1);
	float evaluaterule(float &inputval1,float &inputval2);
	float evaluaterule(float &inputval1,float &inputval2,float &inputval3);
				trapezoid_category *getoutputcategory();
	void clearinputcategoryactivations();
	void clearoutputcategoryactivations();
	void save_m(FILE *file);
	void save(FILE *file);
	void load(FILE *file);
	~rule();
};
