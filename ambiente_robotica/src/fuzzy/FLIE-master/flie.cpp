// Project FLIE-Fuzzy Logic Inference Engine - Joao Alberto Fabro - out/1996
// File flie.cc
// Main program - example of setting and using FLIE to create Fuzzy Logic Controllers

#include <iostream>
using namespace std;

#define DOS
#include "flie.h"

/*Deve-se definir um sistema de controle que ira conter as regras.*/
fuzzy_control fc;

/*No programa principal e necessario instanciar as variaveis para conter
todos os conjuntos fuzzy e tambem defini-los.*/

//trapezoid_category cat[21];
fuzzy_set cat[21];


/*Deve-se definir as variaveis linguisticas que irao conter os conjuntos fuzzy*/

linguisticvariable Error, DeltaError, Control;

/*Deve-se definir as regras de inferencia que irao reger o comportamento do
sistema de controle. Eh necessario instancia-los.*/

rule infrule[49];

int main()
{

/* Define-se os conjuntos fuzzy para a variavel linguistica Error*/

cat[0].setname("NB");
cat[0].setrange(-200,0);
cat[0].setval(-200,-200, -30,-10);

cat[1].setname("NS");
cat[1].setrange(-100,0);
cat[1].setval(-30,-10,-5);

cat[2].setname("NVS");
cat[2].setrange(-100,0);
cat[2].setval(-10,-5,-0);

cat[3].setname("QZ");
cat[3].setrange(-100,+100);
cat[3].setval(-5,0,5);

cat[4].setname("PVS");
cat[4].setrange(0,+100);
cat[4].setval(0,5,10);

cat[5].setname("PS");
cat[5].setrange(0,+100);
cat[5].setval(5,10,30);

cat[6].setname("PB");
cat[6].setrange(0,+200);
cat[6].setval(10, 30, 200, 200);


/*Define-se a Variavel linguistica Error*/

Error.setname("Error");

Error.includecategory(&cat[0]);

Error.includecategory(&cat[1]);

Error.includecategory(&cat[2]);

Error.includecategory(&cat[3]);

Error.includecategory(&cat[4]);

Error.includecategory(&cat[5]);

Error.includecategory(&cat[6]);


/*Define-se os conjuntos fuzzy para a variavel linguistica DeltaError*/

cat[7].setname("NB");
cat[7].setrange(-20,0);
cat[7].setval(-20,-20,-2);

cat[8].setname("NS");
cat[8].setrange(-20,0);
cat[8].setval(-20,-2,0);

cat[9].setname("NVS");
cat[9].setrange(-10,0);
cat[9].setval(-2,-0.5,0);

cat[10].setname("QZ");
cat[10].setrange(-10,+10);;
cat[10].setval(-0.5,0,0.5);

cat[11].setname("PVS");
cat[11].setrange(0,+10);
cat[11].setval(0,0.5,2);

cat[12].setname("PS");
cat[12].setrange(0,+20);
cat[12].setval(0,2,20);

cat[13].setname("PB");
cat[13].setrange(0,+20);
cat[13].setval(2,20,20);




/*Define-se a variavel linguistica DeltaError*/

DeltaError.setname("DeltaError");

DeltaError.includecategory(&cat[7]);

DeltaError.includecategory(&cat[8]);

DeltaError.includecategory(&cat[9]);

DeltaError.includecategory(&cat[10]);

DeltaError.includecategory(&cat[11]);

DeltaError.includecategory(&cat[12]);

DeltaError.includecategory(&cat[13]);




/*Define-se os conjuntos fuzzy para a variavel linguistica Control*/

cat[14].setname("NB");
cat[14].setrange(-100,0);
cat[14].setval(-100,-100,-90,-20);

cat[15].setname("NS");
cat[15].setrange(-100,0);
cat[15].setval(-90,-20,-10);

cat[16].setname("NVS");
cat[16].setrange(-100,0);
cat[16].setval(-20,-10,0);

cat[17].setname("QZ");
cat[17].setrange(-10,+10);
cat[17].setval(-10,0,10);

cat[18].setname("PVS");
cat[18].setrange(0,+100);
cat[18].setval(0,10,20);

cat[19].setname("PS");
cat[19].setrange(0,+100);
cat[19].setval(10,20,90);

cat[20].setname("PB");
cat[20].setrange(0,+100);
cat[20].setval(20,90,100,100);


/*Define-se a variavel linguistica Control*/

Control.setname("Control");

Control.includecategory(&cat[14]);

Control.includecategory(&cat[15]);

Control.includecategory(&cat[16]);

Control.includecategory(&cat[17]);

Control.includecategory(&cat[18]);

Control.includecategory(&cat[19]);

Control.includecategory(&cat[20]);




/*Define-se o metodo defuzzificacao: MAXIMUM, AVERAGEOFMAX, or CENTEROFAREA/CENTROID     */

fc.set_defuzz(CENTROID);


/* Define-se o fuzzy_control pelas entradas fuzzy( Error, DeltaError)
e saidas (Control) )*/

fc.definevars(Error, DeltaError, Control);



/*Deve-se incluir cada regra fuzzy no fuzzy_control*/

// If Error IS Negative Big and DeltaError IS Negative Big THEN Control IS Positive Big
fc.insert_rule("NB","NB","PB");

// If Error IS Negative Big and DeltaError IS Negative Small THEN Control IS Positive Big
fc.insert_rule("NB","NS","PB");


// If Error IS Negative Big and DeltaError IS Negative Very Small THEN Control IS Positive Big
fc.insert_rule("NB","NVS","PB");


// If Error IS Negative Big and DeltaError IS Quasi Zero THEN Control IS Positive Big
fc.insert_rule("NB","QZ","PB");

// If Error IS Negative Big and DeltaError IS Positive Very Small THEN Control IS Positive Small
fc.insert_rule("NB","PVS","PS");

// If Error IS Negative Big and DeltaError IS Positive Small THEN Control IS Positive Small
fc.insert_rule("NB","PS","PVS");

// If Error IS Negative Big and DeltaError IS Positive Big THEN Control IS Quasi Zero
fc.insert_rule("NB","PB","QZ");



// If Error IS Negative Small and DeltaError IS Negative Big THEN Control IS Positive Big
fc.insert_rule("NS","NB","PB");

// If Error IS Negative Small and DeltaError IS Negative Small THEN Control IS Positive Big
fc.insert_rule("NS","NS","PB");

// If Error IS Negative Small and DeltaError IS Negative Very Small THEN Control IS Positive Big
fc.insert_rule("NS","NVS","PB");

// If Error IS Negative Small and DeltaError IS Quasi Zero THEN Control IS Positive Small
fc.insert_rule("NS","QZ","PS");

// If Error IS Negative Small and DeltaError IS Positive Very Small THEN Control IS Positive Very Small
fc.insert_rule("NS","PVS","PVS");

// If Error IS Negative Small and DeltaError IS Positive Small THEN Control IS Quasi Zero
fc.insert_rule("NS","PS","QZ");

// If Error IS Negative Small and DeltaError IS Positive Big THEN Control IS Negative Very Small
fc.insert_rule("NS","PB","NVS");



// If Error IS Negative Very Small and DeltaError IS Negative Big THEN Control IS Positive Big
fc.insert_rule("NVS","NB","PB");

// If Error IS Negative Very Small and DeltaError IS Negative Small THEN Control IS Positive Big
fc.insert_rule("NVS","NS","PB");

// If Error IS Negative Very Small and DeltaError IS Negative Very Small THEN Control IS Positive Small
fc.insert_rule("NVS","NVS","PS");

// If Error IS Negative Very Small and DeltaError IS Quasi Zero THEN Control IS Positive Very Small
fc.insert_rule("NVS","QZ","PVS");

// If Error IS Negative Very Small and DeltaError IS Positive Very Small THEN Control IS Quasi Zero
fc.insert_rule("NVS","PVS","QZ");

// If Error IS Negative Very Small and DeltaError IS Positive Small THEN Control IS Negative Very Small
fc.insert_rule("NVS","PS","NVS");

// If Error IS Negative Very Small and DeltaError IS Positive Big THEN Control IS Negative Small
fc.insert_rule("NVS","PB","NS");




// If Error IS  Quasi Zero and DeltaError IS Negative Big THEN Control IS Positive Big
fc.insert_rule("QZ","NB","PB");

// If Error IS Quasi Zero and DeltaError IS Negative Small THEN Control IS Positive Small
fc.insert_rule("QZ","NS","PS");

// If Error IS Quasi Zero and DeltaError IS Negative Very Small THEN Control IS Positive Very Small
fc.insert_rule("QZ","NVS","PVS");

// If Error IS Quasi Zero and DeltaError IS Quasi Zero THEN Control IS Quasi Zero
fc.insert_rule("QZ","QZ","QZ");

// If Error IS Quasi Zero and DeltaError IS Positive Very Small THEN Control IS Negative Very Small
fc.insert_rule("QZ","PVS","NVS");

// If Error IS Quasi Zero and DeltaError IS Positive Small THEN Control IS Negative Small
fc.insert_rule("QZ","PS","NS");

// If Error IS Quasi Zero and DeltaError IS Positive Big THEN Control IS Negative Big
fc.insert_rule("QZ","PB","NB");



// If Error IS Positive Very Small and DeltaError IS Negative Big THEN Control IS Positive Small
fc.insert_rule("PVS","NB","PS");

// If Error IS Positive Very Small and DeltaError IS Negative Small THEN Control IS Positive Very Small
fc.insert_rule("PVS","NS","PVS");

// If Error IS Positive Very Small and DeltaError IS Negative Very Small THEN Control IS Quasi Zero
fc.insert_rule("PVS","NVS","QZ");

// If Error IS Positive Very Small and DeltaError IS Quasi Zero THEN Control IS Negative Very Small
fc.insert_rule("PVS","QZ","NVS");

// If Error IS Positive Very Small and DeltaError IS Positive Very Small THEN Control IS Negative Small
fc.insert_rule("PVS","PVS","NS");

// If Error IS Positive Very Small and DeltaError IS Positive Small THEN Control IS Negative Big
fc.insert_rule("PVS","PS","NB");

// If Error IS Positive Very Small and DeltaError IS Positive Big THEN Control IS Negative Big
fc.insert_rule("PVS","PB","NB");



// If Error IS Positive Small and DeltaError IS Negative Big THEN Control IS Positive Very Small
fc.insert_rule("PS","NB","PVS");

// If Error IS Positive Small and DeltaError IS Negative Small THEN Control IS Quasi Zero
fc.insert_rule("PS","NS","QZ");

// If Error IS Positive Small and DeltaError IS Negative Very Small THEN Control IS Negative Very Small
fc.insert_rule("PS","NVS","NVS");

// If Error IS Positive Small and DeltaError IS Quasi Zero THEN Control IS Negative Small
fc.insert_rule("PS","QZ","NS");

// If Error IS Positive Small and DeltaError IS Positive Very Small THEN Control IS Negative Big
fc.insert_rule("PS","PVS","NB");

// If Error IS Positive Small and DeltaError IS Positive Small THEN Control IS Negative Big
fc.insert_rule("PS","PS","NB");

// If Error IS Positive Small and DeltaError IS Positive Big THEN Control IS Negative Big
fc.insert_rule("PS","PB","NB");



// If Error IS  Positive Big and DeltaError IS Negative Big THEN Control IS Quasi Zero
fc.insert_rule("PB","NB","QZ");

// If Error IS Positive Big and DeltaError IS Negative Small THEN Control IS Negative Very Small
fc.insert_rule("PB","NS","NVS");

// If Error IS Positive Big and DeltaError IS Negative Very Small THEN Control IS Negative Small
fc.insert_rule("PB","NVS","NS");

// If Error IS Positive Big and DeltaError IS Quasi Zero THEN Control IS Negative Big
fc.insert_rule("PB","QZ","NB");

// If Error IS Positive Big and DeltaError IS Positive Very Small THEN Control IS Negative Big
fc.insert_rule("PB","PVS","NB");

// If Error IS Positive Big and DeltaError IS Positive Small THEN Control IS Negative Big
fc.insert_rule("PB","PS","NB");

// If Error IS Positive Big and DeltaError IS Positive Big THEN Control IS Negative Big
fc.insert_rule("PB","PB","NB");

/*Pode-se salvar todo o sistema de controle em um arquivo texto (.fc) que pode posteriormente
ser lido pela chamada ao metodo  "load() de alguma variavel do tipo "fuzzy_control fc": 
fc.load("nomearquivo_sem_extensao"). */

fc.save("controleteste", 0);

/*Pode-se tambem salvar todo o sistema de controle em um arquivo texto (.fis) compativel com 
o formato de arquivo fuzzy do MATLAB. O metodo "load_m() ainda precisa ser implementado (TODO) 
fc.load_m("nomearquivo_sem_extensao"). */

fc.save_m("controleteste", 0);


/*Deve-se definir variaveis que irao conter as entradas e saidas(defuzificadas)
do sistema submetidas ao controle.*/

// Define-se a leitura dos sensores do seu sistema
float ErrorInput = -100.0;
float DeltaErrorInput = 0.0;

// Define-se a saida(defuzificada) do seu sistema
float ControlOutput;

ControlOutput = fc.make_inference(ErrorInput, DeltaErrorInput);

printf("Saida do Sistema de Inferencia quando as entradas sao %3.2f e %3.2f: %3.2f\n",ErrorInput, DeltaErrorInput, ControlOutput);

printf("Se quiser ver exemplos de inferencias para multiplos valores de entrada, aperte <ENTER>\n");
getchar();
for(float k=-90.0;k<90.0;k=k+10.0)
    {
    for(float l=-10.0;l<10.0;l=l+2.0)
        {
        ControlOutput = fc.make_inference(k, l);
        printf("Entradas= %3.2f e %3.2f -> Saida = %3.2f\n",k, l, ControlOutput);
        }
    getchar();
    }



return(0);
}

