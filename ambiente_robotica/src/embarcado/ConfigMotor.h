int resolucao = 8;
int frequencia = 5000; 
int pwmD = 1;
int pwmE = 0;

int mdA = 22;
int mdB = 23;

int meA = 18;
int meB = 19;

void configuraMotores() {
  ledcSetup(pwmD, frequencia, resolucao);
  ledcAttachPin(mdA, pwmD);
  pinMode(mdB, OUTPUT);

  ledcSetup(pwmE, frequencia, resolucao);
  ledcAttachPin(meA, pwmE);
  pinMode(meB, OUTPUT);
}

void mdF(int vel) {
  Serial.print("mdF = ");
  Serial.println(vel);

  digitalWrite(mdB, false);
  ledcWrite(pwmD, vel);
}

void mdT(int vel) {
  Serial.print("mdT = ");
  Serial.println(vel);
  
  digitalWrite(mdB, true);
  ledcWrite(pwmD, vel);
}


void meF(int vel) {
  digitalWrite(meB, false);
  ledcWrite(pwmE, vel);
}

void meT(int vel) {
  digitalWrite(meB, true);
  ledcWrite(pwmE, vel);
}
