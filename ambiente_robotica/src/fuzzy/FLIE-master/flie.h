//# FLIE - Fuzzy Logic Inference Engine
/*####################################################################################
Copyright 2018 Joao Fabro - joaofabro@gmail.com

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

// Project FLIE-Fuzzy Logic Inference Engine - Joao Alberto Fabro - Development Started: out/1996
// Header file flie.h
#include <iostream>
using namespace std;
#include <stdio.h>
#include "fuzzyset.h"
#include "lingvar.h"
#include "rule.h"
#include "fuzzy_control.h"
#include "stdlib.h"
#include "string.h"

#define tnorm(x,y) x<y?x:y //min : macros that define the T-norm
#define snorm(x,y) x<y?y:x //max : and the S-norm used in the fuzzy inference



