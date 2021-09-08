// Project FLIE-Fuzzy Logic Inference Engine - Joao Alberto Fabro - out/1996
// Class Methods File fuzzy_control.cpp - Implementation of class fuzzy_control

#include "flie.h"
/* definevars  - Tres metodos para definir as variaveis linguisticas de entrada
                 e saida que controlam o comportamento do sistema */


int fuzzy_control::definevars(linguisticvariable &input1,linguisticvariable &output)
{
numinputvars = 1;        
lingvarinput1 = input1;
lingvaroutput = output;
return(1);
}

int fuzzy_control::definevars(linguisticvariable &input1,linguisticvariable &input2,linguisticvariable &output)
{
numinputvars = 2;
lingvarinput1 = input1;
lingvarinput2 = input2;
lingvaroutput = output;
return(1);
}

int fuzzy_control::definevars(linguisticvariable &input1,linguisticvariable &input2,
                              linguisticvariable &input3,linguisticvariable &output)
{
numinputvars = 3;
lingvarinput1 = input1;
lingvarinput2 = input2;
lingvarinput3 = input3;
lingvaroutput = output;
return(1);
}

//-------------------------------------------------------------

// insert_rule - Three methods to insert fuzzy rules in the control algorithm
int fuzzy_control::insert_rule(const char *setofinplingvar1, const char *setofoutlingvar)
{
	if(numrules<MAXRULES)
	{
         rulebase[numrules] = new rule;
         rulebase[numrules]->definerule(&lingvarinput1.getcat(setofinplingvar1),
                                        &lingvaroutput.getcat(setofoutlingvar));
         numrules++;
         return(0);
	}
	else
         return(1);
}

int fuzzy_control::insert_rule(const char *setofinplingvar1,const char *setofinplingvar2,
                            const char *setofoutlingvar)
{
	if(numrules<MAXRULES)
	{
         rulebase[numrules] = new rule;
         rulebase[numrules]->definerule(&lingvarinput1.getcat(setofinplingvar1),
                                        &lingvarinput2.getcat(setofinplingvar2),
                                        &lingvaroutput.getcat(setofoutlingvar));
         numrules++;
         return(0);
	}
	else
         return(1);
}

int fuzzy_control::insert_rule(const char *setofinplingvar1,const char *setofinplingvar2,
                            const char *setofinplingvar3,const char *setofoutlingvar)
{
	if(numrules<MAXRULES)
	{
         rulebase[numrules] = new rule;
         rulebase[numrules]->definerule(&lingvarinput1.getcat(setofinplingvar1),
                                	&lingvarinput2.getcat(setofinplingvar2),
                                        &lingvarinput3.getcat(setofinplingvar3),
                                        &lingvaroutput.getcat(setofoutlingvar));
         numrules++;
         return(0);
	}
	else
         return(1);
}

// insert_rule(rule&) - polimorphic method to insert rules already created!
int fuzzy_control::insert_rule(rule& ruletoinsert)
{
	if(numrules<MAXRULES)
	{
           	rulebase[numrules] = new rule;
                *rulebase[numrules] = ruletoinsert;
                numrules++;
		return(0);
	}
	else
		return(1);

}


//-------------------------------------------------------------

// make_inference - Three methods to dispatch the inference mecanism!

float fuzzy_control::make_inference(float inputval1)
{
for(int i=0;i<numrules;i++)
   {
    rulebase[i]->clearinputcategoryactivations();
    rulebase[i]->clearoutputcategoryactivations();
   }
  for(int i=0;i<numrules;i++)
   {
     activationofrule[i]=rulebase[i]->evaluaterule(inputval1);
#ifdef DEBUG
     cout << "Activ of Rule " << i << "= ";
     cout << activationofrule[i] << "\n";
#endif
   }

 return(defuzzify());
}

float fuzzy_control::make_inference(float inputval1,float inputval2)
{
for(int i=0;i<numrules;i++)
   {
    rulebase[i]->clearinputcategoryactivations();
    rulebase[i]->clearoutputcategoryactivations();
   }

  for(int i=0;i<numrules;i++)
   {
     activationofrule[i]=rulebase[i]->evaluaterule(inputval1, inputval2);
#ifdef DEBUG
     cout << "Activation of Rule " << i << "= ";
     cout << activationofrule[i] << "\n";
#endif
   }

 return(defuzzify());

}

float fuzzy_control::make_inference(float inputval1,float inputval2,float inputval3)
{
for(int i=0;i<numrules;i++)
   {
    rulebase[i]->clearinputcategoryactivations();
    rulebase[i]->clearoutputcategoryactivations();
   }

for(int i=0;i<numrules;i++)
   {
     activationofrule[i]=rulebase[i]->evaluaterule(inputval1, inputval2, inputval3);
#ifdef DEBUG
     cout << "Activ of Rule " << i << "= ";
     cout << activationofrule[i] << "\n";
#endif
   } 
 return(defuzzify());
}

//-------------------------------------------------------------

// defuzzify - method that choose among the three different methods of 
//             defuzzification - the default is MAXIMUM, to
//	       set a new method, use the constructor or set_defuzz with the
//	       predefined constants : MAXIMUM, AVERAGEOFMAX and CENTEROFAREA
float fuzzy_control::defuzzify()
{
float defuzzout=0.0;

 if(kindofdefuzzification== MAXIMUM)
 {
  defuzzout=defuzzifyMAX();
 }
else if(kindofdefuzzification== AVERAGEOFMAX)
 {
 defuzzout = defuzzifyMOM();
 }
else if(kindofdefuzzification== CENTEROFAREA)
 {
 defuzzout = defuzzifyCOA(); 
 } 
 return(defuzzout);
}


// defuzzifyMAX - defuzzification by the MAXIMUM
float fuzzy_control::defuzzifyMAX()
{
trapezoid_category *outcat;
float x=0.0;
float biggest=0.0;
float defuzzout;
 
  for(int i=0;i<numrules;i++)
   {
     if((x=activationofrule[i])>biggest)
      {
        biggest = x;
        outcat = rulebase[i]->getoutputcategory();
        defuzzout = outcat->getmidval(); 
#ifdef DEBUG
        cout << "\nRule " << i << "\tActivation " << x <<"\tDefuzzMax " << defuzzout <<"\tCategory " << outcat->getname()<<"\n";
#endif
      }
   }
 return(defuzzout);  
}

// defuzzifyMOM - defuzzification by the AVERAGEOFMAX method
float fuzzy_control::defuzzifyMOM()
{
trapezoid_category *outcat;
float x=0.0;
float defuzzout;
float sumativations=0.0;
int countrulesfiring=0;
int numcats;
     
   for(int i=0;i<numrules;i++)
    {
     if((x=activationofrule[i])>0.0)
      {
	countrulesfiring++;
  	outcat = rulebase[i]->getoutputcategory();
        outcat->setoutput(x);
#ifdef DEBUG
        cout << "Rule: " << i << "\tActivation: " << x << "\t" << outcat->getname()<< "\t" <<outcat->getoutput()<<"\n";
#endif

      }
    }

  defuzzout=0.0; 
  numcats=lingvaroutput.getnumofcategories();
  for(int i=0;i<numcats; i++)
  {
   outcat=&lingvaroutput.getcat(i);
   defuzzout+=outcat->getoutput()*outcat->getmidval();
   sumativations += outcat->getoutput();
#ifdef DEBUG
   cout << "Output: " << outcat->getoutput() << "\tMidval: " <<  outcat->getmidval();
   cout << "\tCategory: " << outcat->getname() << "\tDefuzzMOM: " << defuzzout << "\t Sumativ: " << sumativations << "\n";
#endif

  }
 if(sumativations!=0.0)
   defuzzout = defuzzout/sumativations;  	
 else
   defuzzout = 0.0;

 return(defuzzout);
}

// defuzzifyCOA - defuzzification by the CENTEROFAREA method
float fuzzy_control::defuzzifyCOA()
{
trapezoid_category *outcat;
float x=0.0;
float defuzzout;

 for(int i=0;i<numrules;i++)
   {
     if((x=activationofrule[i])>0.0)
      {
        outcat = rulebase[i]->getoutputcategory();
        outcat->setoutput(x);
      }
   }

#ifdef DEBUG
  for(int i=0;i<numrules;i++)
   {
     if((x=activationofrule[i])>0.0)
      {
        outcat = rulebase[i]->getoutputcategory();
        cout << "\nRule " << i << "\tActivation " << x << "\tCategory " << outcat->getname()<<"\n";
      }
   }
#endif

 outcat = &lingvaroutput.getcat(0);
 float init=outcat->getlowval();
 outcat = &lingvaroutput.getcat(((lingvaroutput.getnumofcategories())-1));
 float final=outcat->gethighval();
 float step=(final-init)/(100);

 #ifdef DEBUG
        cout << "\nBegin: " << init << "\tEnd: " << final <<"\tStep: " << step <<"\n";
#endif

float localsum;
float globalsum=0;
float valuessum=0.0;
float aux=0.0;
float aux1=0.0;
  
 for(float i=init;i<=final;i+=step)
 {
   localsum=0.0;
   for(int j=0;j<lingvaroutput.getnumofcategories();j++)
   {
    outcat=&lingvaroutput.getcat(j);
    aux=outcat->getoutput(); 
    aux1=outcat->getshare(i);
    if(aux!=0.0) 
       localsum+=tnorm(aux1,aux);//MUST be min??? 07/11/96 Hans
#ifdef DEBUG
        cout << "\nI= " << i << "\tJ=" << j << "\tAux=Activ: " << aux <<"\tGetshare(i)=" << aux1 << "\tSum " << localsum <<"\tCat " << outcat->getname();
#endif       
   }
#ifdef DEBUG
   cout << "\n";   
#endif
   globalsum+=localsum*i;
   valuessum+=localsum;
#ifdef DEBUG
        cout << "\nLocalsum: " << localsum <<"\tValuesum " << valuessum;
#endif
 }
 if(valuessum!=0.0)
  defuzzout = globalsum/valuessum;
 else
  defuzzout = 0.0;

 return(defuzzout);
}


void fuzzy_control::save_m(const char *name, float error)
{
  FILE *fileFC;

  char fileName[30];

  strcpy(fileName, name);
  strcat(fileName, ".fis");
  if ( (fileFC = fopen ( fileName, "w" )) == NULL )
    {
      cout << "Error in file creation:" << fileName << "\n";
      exit(1);
    }
fprintf(fileFC,"[System]\nName='%s'\rType='mamdani'\rVersion=2.0\r", name);
fprintf(fileFC,"NumInputs=%d\rNumOutputs=1\rNumRules=%d\r", numinputvars, numrules);
fprintf(fileFC,"AndMethod='min'\rOrMethod='max'\rImpMethod='min'\rAggMethod='max'\r");
if(kindofdefuzzification == 3)
        fprintf ( fileFC, "DefuzzMethod='centroid'\r");
else
if(kindofdefuzzification == 2)
        fprintf ( fileFC, "DefuzzMethod='mom'\r");
else
if(kindofdefuzzification == 1)
        fprintf ( fileFC, "DefuzzMethod='bisector'\r");

  if (numinputvars>0)
    lingvarinput1.save_m( fileFC, "Input1" );

  if (numinputvars>1)
    lingvarinput2.save_m( fileFC, "Input2" );
  if (numinputvars>2)
    lingvarinput3.save_m( fileFC, "Input3" );

  lingvaroutput.save_m( fileFC , "Output1" );

  fprintf ( fileFC, "\r\r[Rules]\r");

  for(int i=0;i<numrules;i++)
  {
     rulebase[i]->save_m( fileFC);
  }
  
  fclose (fileFC);
}


void fuzzy_control::save(const char *name, float error)
{
  FILE *fileFC;

  char fileName[30];

  strcpy(fileName, name);
  strcat(fileName, ".fc");
  if ( (fileFC = fopen ( fileName, "w" )) == NULL )
    {
      cout << "Error in file creation:" << fileName << "\n";
      exit(1);
    }
  fprintf ( fileFC, "%d\n", kindofdefuzzification );
  fprintf ( fileFC, "%d\n", numinputvars );

  if (numinputvars>0)
    lingvarinput1.save( fileFC );
  if (numinputvars>1)
    lingvarinput2.save( fileFC );
  if (numinputvars>2)
    lingvarinput3.save( fileFC );

  lingvaroutput.save( fileFC );

  fprintf ( fileFC, "%d\n",  numrules);

  for(int i=0;i<numrules;i++)
  {
     rulebase[i]->save( fileFC);
  }

  fprintf ( fileFC, "Error with this controller = %f\n", error );

  fclose (fileFC);
}

void fuzzy_control::load(const char *name)
{
  FILE *fileFC;
  char line[30];
  char fileName[30];
  int i, j;


  if (numrules > 0)
  {
     for(i=0;i<numrules;i++)
       free(rulebase[i]);
     numrules = 0;
  }

  strcpy(fileName, name);
  strcat(fileName, ".fc");
  if ( (fileFC = fopen ( fileName, "r" )) == NULL )
    {
      cout << "Error in file opening:" << fileName << "\n";
      exit(1);
    }

  fgets ( line, 30, fileFC); line[strlen(line)-1] = '\0';
  kindofdefuzzification = atoi(line);

  fgets ( line, 30, fileFC); line[strlen(line)-1] = '\0';
  numinputvars = atoi(line);


  if (numinputvars>0)
    lingvarinput1.load( fileFC );
  if (numinputvars>1)
    lingvarinput2.load( fileFC );
  if (numinputvars>2)
    lingvarinput3.load( fileFC );

  lingvaroutput.load( fileFC );

  fgets ( line, 30, fileFC); line[strlen(line)-1] = '\0';
  j = atoi(line);//numrules!!

/*  for(int i=0;i<numrules;i++)
  {
     rulebase[i] = new rule;
     rulebase[i]->load( fileFC);
  }
*/
  for(i=0;i<j;i++)
    loadrulebase(fileFC);

  fclose (fileFC);
}

void fuzzy_control::loadrulebase(FILE *file)
{
char cat1[30], cat2[30], cat3[30], cat4[30];
  fgets (cat1, 30, file); cat1[strlen(cat1)-1] = '\0';
  fgets (cat2, 30, file); cat2[strlen(cat2)-1] = '\0';
  fgets (cat3, 30, file); cat3[strlen(cat3)-1] = '\0';
  fgets (cat4, 30, file); cat4[strlen(cat4)-1] = '\0';
  if(!strcmp(cat3, "NULL"))
  {
     if(!strcmp(cat2, "NULL"))
       insert_rule(cat1, cat4);
     else
       insert_rule(cat1, cat2, cat4);
  }
  else
    insert_rule(cat1, cat2, cat3, cat4);
}
