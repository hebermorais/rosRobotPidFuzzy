#include <tf/tf.h>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose.h"
#include "nav_msgs/Odometry.h"
#include <iostream>
using namespace std;
#include "FLIE-master/flie.h"

bool verificaConflito();
void configuraFuzzy();
float calc_distance_robot_obstacle();
float calc_angle_robot_obstacle();

fuzzy_control fc_velLin;
fuzzy_control fc_velAng;

fuzzy_set categoriasEntradaRiscoColisao[3];
fuzzy_set categoriasEntradaAngulo[3];

fuzzy_set categoriasSaidaLin[2];
fuzzy_set categoriasSaidaAng[3];

linguisticvariable RiscoColisao, Angulo, VelLinear, VelAngular;


geometry_msgs::Pose feedback;
geometry_msgs::Pose feedback_obstacle;


double yaw2;
double PI = 3.141592654;

float calc_distance_robot_obstacle(){
    float distance_obstable = sqrt(pow((feedback_obstacle.position.x-feedback.position.x),2)+pow((feedback_obstacle.position.y-feedback.position.y),2));
    return distance_obstable;
}
 
float calc_angle_robot_obstacle(){
   float errorAngular = atan2(feedback_obstacle.position.y-feedback.position.y, feedback_obstacle.position.x-feedback.position.x);
   double err =  (errorAngular)-(yaw2);
        
    //verifica se o erro esteja dentro do intevalo de -PI à PI
    if (err > PI) {
        err = err - (2 * PI);
    } 
    if (err < -PI) {
        err = err + (2 * PI);
    }    
    return err;
}

	


void subCallback(const geometry_msgs::Pose::ConstPtr& msg){
	feedback.position = msg->position;
  feedback.orientation = msg->orientation;
   tf::Quaternion q(
        msg->orientation.x,
        msg->orientation.y,
        msg->orientation.z,
        msg->orientation.w);
  tf::Matrix3x3 m(q);
  double roll, pitch, yaw;
  m.getRPY(roll, pitch, yaw);
  yaw2 = yaw;
}

void subCallbackObstacle(const geometry_msgs::Pose::ConstPtr& msg){
  feedback_obstacle.position = msg->position;
  feedback_obstacle.orientation = msg->orientation;
}

 
int main(int argc, char **argv){
  ros::init(argc, argv, "pid_stage");
 
  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/robot_01/cmd_vel", 1000);
  ros::Subscriber sub = n.subscribe("/robot_01/pose", 1000, subCallback);
  ros::Subscriber sub2 = n.subscribe("//obstacle_5/pose", 1000, subCallbackObstacle);
  
  ros::Time   last_time, actual_time;
  ros::Rate loop_rate(1000);
   
  configuraFuzzy();

  double erroSumL, lastErrL;
  double erroSumA, lastErrA;
  double linearX = 0;
  double angularZ = 0;

  double kpL = 1;
  double kiL = 0;
  double kdL = 0.5;

  double kpA = 4;
  double kiA = 0;
  double kdA = 1;
  

  while (ros::ok()){
    geometry_msgs::Twist msg;
    float posX, posY;
    float tolerance = 0.01;
    double errorLinear = 99;
    double errorAngular = 0;
    
    cout << "Digite a posicao\nX>>";
    cin >> posX;

    cout << "Digite a posicao\nY>>";
    cin >> posY;


    while (abs(errorLinear) > tolerance && ros::ok()) {

        
        double yaw = 0;
      
        yaw = yaw2;

        actual_time = ros::Time::now();
        last_time = actual_time;
        double timeChange = (actual_time = last_time).toSec();

        //linear PID   
        errorLinear = sqrt(pow((posX-feedback.position.x),2)+pow((posY-feedback.position.y),2));
        erroSumL += (errorLinear * timeChange);
        double dErrL =  (errorLinear - lastErrL) / timeChange;
        linearX = kpL * errorLinear + kiL * erroSumL + kdL * dErrL;

        
        
        errorAngular = atan2(posY-feedback.position.y, posX-feedback.position.x);
        erroSumA += (errorAngular * timeChange);
        double dErrA =  (errorAngular - lastErrA) / timeChange;
        //double err =  (errorAngular - yaw);
        double err =  (errorAngular)-(yaw);
        
        //verifica se o erro esteja dentro do intevalo de -PI à PI
        if (err > PI) {
            err = err - (2 * PI);
        } 
        if (err < -PI) {
            err = err + (2 * PI);
        }    

        angularZ = (kpA * err) + (kiA * erroSumA) + (kdA * dErrA);

    
        float distancia = calc_distance_robot_obstacle();
        float ang = calc_angle_robot_obstacle();

        float dist = 0;
        float linFuzzy = 0;
        float angFuzzy = 0; 
        
        float distMin = 0.05;
        float gatilho = 0.1;
        float gatilhoOffSet = gatilho - distMin;



        if(distancia<gatilho && ang>-1.57 && ang < 1.57){
            ROS_INFO("FUZZY ATIVADO!");
            if(ang < -1.57){
                ang = -1.57;
            }
            if(ang > 1.57){ 
                ang = 1.57;
            }
            distancia = distancia - distMin;
            dist = distancia / gatilhoOffSet;
            linFuzzy = fc_velLin.make_inference(dist,ang);
            angFuzzy = fc_velAng.make_inference(dist,ang);
            linearX = 1.5;
            angularZ = angFuzzy * 10;
        }



        if(linearX < 1.8){
          linearX = 1.8;
        }
        if(linearX > 10){
          linearX = 10;
        }
        msg.linear.x = linearX;
        msg.angular.z = angularZ;
        

        
        
        //ROS_INFO("Pose.: X=%f  Y=%f", feedback.position.x, feedback.position.y);
        //ROS_INFO("Err......= %f Erro Ang......=%f   YAW............= %f", err, errorAngular, yaw);
        ROS_INFO("Distanc.: %f   linFuzzy.: %f  angFuzzy:: %f distF.: %f  ang..: %f", distancia, linFuzzy, angFuzzy, dist, ang);
        ROS_INFO("Linear..: %f  angular: %f", linearX, angularZ);
        ROS_INFO("----------------------");
        
        // erro = posX-feedback.x;
        // msg.linear.x = /Kpos*erro/(60/10);
        // ROS_INFO("TEMPO: %f   X>>%f,Erro>>%f",dt,feedback.x,erro);
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
  	}
    ROS_WARN("...Posicao alcancada...");
    msg.linear.x = 0;
    msg.angular.z = 0; 
    pub.publish(msg);
    ros::spinOnce();
  }
 
  return 0;
}


void configuraFuzzy(){

  /* Define-se os conjuntos fuzzy da variáveis de entrada RISCO DE COLISAO*/
  categoriasEntradaRiscoColisao[0].setname("alto");
  categoriasEntradaRiscoColisao[0].setrange(0,1);
  categoriasEntradaRiscoColisao[0].setval(0, 0, 0.2, 0.5);

  categoriasEntradaRiscoColisao[1].setname("medio");
  categoriasEntradaRiscoColisao[1].setrange(0,1);
  categoriasEntradaRiscoColisao[1].setval(0.3, 0.5, 0.7);

  categoriasEntradaRiscoColisao[2].setname("baixo");
  categoriasEntradaRiscoColisao[2].setrange(0,1);
  categoriasEntradaRiscoColisao[2].setval(0.5, 0.8, 1, 1);
  

  RiscoColisao.setname("RiscoColisao");
  RiscoColisao.includecategory(&categoriasEntradaRiscoColisao[0]);
  RiscoColisao.includecategory(&categoriasEntradaRiscoColisao[1]);
  RiscoColisao.includecategory(&categoriasEntradaRiscoColisao[2]);

  /*Define-se os conjuntos fuzzy da variáveis de entrada ANGULO*/

  categoriasEntradaAngulo[0].setname("l_esquerda");
  categoriasEntradaAngulo[0].setrange(-1.57,1.57);
  categoriasEntradaAngulo[0].setval(-1.57, -1.57, 0);

  categoriasEntradaAngulo[1].setname("proximo");
  categoriasEntradaAngulo[1].setrange(-1.57,1.57);
  categoriasEntradaAngulo[1].setval(-0.5, 0, 0.5);

  categoriasEntradaAngulo[2].setname("l_direita");
  categoriasEntradaAngulo[2].setrange(-1.57,1.57);
  categoriasEntradaAngulo[2].setval(0, 1.57, 1.57);
  

  Angulo.setname("Angulo");
  Angulo.includecategory(&categoriasEntradaAngulo[0]);
  Angulo.includecategory(&categoriasEntradaAngulo[1]);
  Angulo.includecategory(&categoriasEntradaAngulo[2]);


  /* Define-se os conjuntos fuzzy da variável de saída VelLin*/

  categoriasSaidaLin[0].setname("lento");
  categoriasSaidaLin[0].setrange(0, 1);
  categoriasSaidaLin[0].setval(0, 0, 0.2, 0.8);

  categoriasSaidaLin[1].setname("rapido");
  categoriasSaidaLin[1].setrange(0,1);
  categoriasSaidaLin[1].setval(0.2, 0.8, 1, 1);

  VelLinear.setname("VelLin");
  VelLinear.includecategory(&categoriasSaidaLin[0]);
  VelLinear.includecategory(&categoriasSaidaLin[1]);

  /* Define-se os conjuntos fuzzy da variável de saída VelAng*/

  categoriasSaidaAng[0].setname("direita");
  categoriasSaidaAng[0].setrange(-1, 1);
  categoriasSaidaAng[0].setval(-1, -1, -0.8, 0);

  categoriasSaidaAng[1].setname("frente");
  categoriasSaidaAng[1].setrange(-1,1);
  categoriasSaidaAng[1].setval(-0.5, 0, 0.5);

  categoriasSaidaAng[2].setname("esquerda");
  categoriasSaidaAng[2].setrange(-1,1);
  categoriasSaidaAng[2].setval(0, 0.8, 1, 1);

  VelAngular.setname("VelAng");
  VelAngular.includecategory(&categoriasSaidaAng[0]);
  VelAngular.includecategory(&categoriasSaidaAng[1]);
  VelAngular.includecategory(&categoriasSaidaAng[2]);
  

  fc_velLin.definevars(RiscoColisao, Angulo,  VelLinear);

  fc_velLin.insert_rule("alto", "l_esquerda", "lento");
  fc_velLin.insert_rule("medio", "l_esquerda", "rapido");
  fc_velLin.insert_rule("baixo", "l_esquerda", "rapido");

  fc_velLin.insert_rule("alto", "proximo", "lento");
  fc_velLin.insert_rule("medio", "proximo", "lento");
  fc_velLin.insert_rule("baixo", "proximo", "rapido");
  
  fc_velLin.insert_rule("alto", "l_direita", "lento");
  fc_velLin.insert_rule("medio", "l_direita", "rapido");
  fc_velLin.insert_rule("baixo", "l_direita", "rapido");
  
  
  

  fc_velAng.definevars(RiscoColisao, Angulo, VelAngular);


  fc_velAng.insert_rule("alto", "l_esquerda", "frente");
  fc_velAng.insert_rule("medio", "l_esquerda", "frente");
  fc_velAng.insert_rule("baixo", "l_esquerda", "esquerda");

  fc_velAng.insert_rule("alto", "proximo", "direita");
  fc_velAng.insert_rule("medio", "proximo", "direita");
  fc_velAng.insert_rule("baixo", "proximo", "direita");
  
  fc_velAng.insert_rule("alto", "l_direita", "direita");
  fc_velAng.insert_rule("medio", "l_direita", "frente");
  fc_velAng.insert_rule("baixo", "l_direita", "frente");


  fc_velLin.set_defuzz(3);
  fc_velAng.set_defuzz(3);

}