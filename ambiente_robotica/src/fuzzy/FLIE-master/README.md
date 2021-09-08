# FLIE - Fuzzy Logic Inference Engine
####################################################################################
Copyright 2018 Joao Fabro

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
####################################################################################

FLIE - Fuzzy Logic Inference Engine

FLIE was developed by Joao Alberto Fabro, Associate Professor at UTFPR-Federal University of Technology - Parana - Brazil

FLIE is a simple library that implements fuzzy concepts (Fuzzy Sets) in form of triangular or trapezoidal Fuzzy Sets(or Categories).

Several of these "Categories/Fuzzy Sets" can then be agregated in "Linguistic Variables".

Linguistic Variables can then be used to define "Rules" associating "Fuzzy Sets" with each other.

The following source codes compose the Library:
 - fuzfier.h and fuzzfier.cpp (source code for class "fuzzy_set"(also called fuzzyset or trapezoid_category), that are classes that represent fuzzy concepts - near, far, large, small...)
 - lingvar.h and lingvar.cpp (source code for class "linguisticvariable", that aggregates 2 or more fuzzy_sets in one coherent "concept", such as "Distance")
 - rule.h and rule.cpp (source code for class "rule": each "rule" relates one (or two or three) input fuzzy_set's with one output fuzzy set. For example, "if Distance is Near then Action_in_the_Break is Hard" -> rule.definerule( "Far","Hard");
 - fuzzy_control.h and fuzzy_control.cpp (source code for a Mamdani type fuzzy logic controller - aggregates linguistic variables, rules and a defuzzyfication method in order to perform fuzzy inference)
 - flie.h and flie.cpp (example code that creates a PD Fuzzy controller)

These "Rules" can then be aggregated into a "Fuzzy Controller". The code for the "simplest" fuzzy control system is depicted bellow:

/* Simple Example of use (save this excerpt and compile it together with the library) - the easyest way is to just save this 
code with the name "flie.cpp" */


// Joao Alberto Fabro, fabro@utfpr.edu.br, 05/2018
// Version 1.0 - 05/2018
// 08/2018 - MIT License Disclaimer

#include "flie.h"

fuzzy_control fc;

fuzzy_set fs_near,fs_far, fs_soft, fs_hard;

linguisticvariable Distance, BreakControl;

rule infrule[2];

int main()
{

 fs_near.setname("Near");
 fs_near.setrange(0,50);
 fs_near.setval(0,0,10,20);

 fs_far.setname("Far");
 fs_far.setrange(0,50);
 fs_far.setval(0,10,20,50);

 fs_soft.setname("Soft");
 fs_soft.setrange(0,100);
 fs_soft.setval(0,0,75);

 fs_hard.setname("Hard");
 fs_hard.setrange(0,100);
 fs_hard.setval(0,75,100);

 Distace.setname("Distance");
 Distance.includecategory(&fs_near);
 Distance.includecategory(&fs_far);

 BreakControl.setname("Break");
 BreakControl.includecategory(&fs_soft);
 BreakControl.includecategory(&fs_hard);

 fc.definevars(Distance, BreakControl);

 fc.set_defuzz(CENTROID);

 // If Distance IS Near THEN BreakControl IS Hard
 fc.insert_rule("Near","Hard");

 // If Distance IS Far THEN BreakControl IS Soft
 fc.insert_rule("Far","Soft");

 // Variables for Input and Output
 float dist = 50.0;
 float breakPercentage;

 breakPercentage = fc.make_inference(dist);

 printf("for Distance %3.2f meters the defuzyfied Output for BreakControl is %3.2f \% \n",dist, breakPercentage);

 return(0);
}

