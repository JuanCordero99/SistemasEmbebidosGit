#include<Servo.h>

const int dirPin = 9;
const int stepPin = 8;

int ledV = 0;
int ledR = 1;
 
unsigned long pasosvuelta;
float grados;
unsigned long rpms;
unsigned long pasos;
unsigned long retardo;
String mensaje = "";

float grados1, grados2, grados3;

Servo servo, servo2, servo3 ;


//-----------------SETUP------------------------------ 
void setup() {
   pinMode(ledV, OUTPUT);
   pinMode(ledR, OUTPUT);    
   pinMode(dirPin, OUTPUT);   //coloco el Pin de Dirección como salida
   pinMode(stepPin, OUTPUT);  //coloco el Pin de Step como salida
   Serial.begin(9600);      //inicio la comunicación serial a 115200 baud
   pasosporvuelta();          //llamo a la función para definir los pasos por vuelta
   servo.attach(3);
   servo2.attach(4);
   servo3.attach(5);
}

//-----------------LOOP------------------------------ 
void loop() {

  

  //Servo1
  
  Serial.print("Dime los grados del servo 1: ");
  while (Serial.available() == 0 ) {} //queda esperando hasta recibir un mensaje
  mensaje = Serial.readString();
  grados1 = mensaje.toInt();      //convierte en mensaje recibido en un entero
  if (grados1 == 0) {             //si no es un número envía ERROR y vuelve a llamar a la función
    Serial.print("ERROR\n");
  }
  else {                              //si es un número nos envia un mensaje de OK
    Serial.print(grados1);
    Serial.print(" OK\n");
  }

  servo.write(grados1);

  delay(500);

  //Servo2
  
  Serial.print("Dime los grados del servo 2: ");
  while (Serial.available() == 0 ) {} //queda esperando hasta recibir un mensaje
  mensaje = Serial.readString();
  grados2 = mensaje.toInt();      //convierte en mensaje recibido en un entero
  if (grados2 == 0) {             //si no es un número envía ERROR y vuelve a llamar a la función
    Serial.print("ERROR\n");
  }
  else {                              //si es un número nos envia un mensaje de OK
    Serial.print(grados2);
    Serial.print(" OK\n");
  }

  servo2.write(grados2);

  delay(500);

  //Servo3
  
  Serial.print("Dime los grados del servo 3: ");
  while (Serial.available() == 0 ) {} //queda esperando hasta recibir un mensaje
  mensaje = Serial.readString();
  grados3 = mensaje.toInt();      //convierte en mensaje recibido en un entero
  if (grados3 == 0) {             //si no es un número envía ERROR y vuelve a llamar a la función
    Serial.print("ERROR\n");
  }
  else {                              //si es un número nos envia un mensaje de OK
    Serial.print(grados3);
    Serial.print(" OK\n");
  }

  servo3.write(grados3);

  delay(500);

  
  digitalWrite(ledR, HIGH);
  sentido();    //llamo a la función para definir el sentido de giro.
  giro();       //llamo a la función para definir los grados que debe girar el motor.
  velocidad();  //llamo a la función para definir la velocidad de giro en RPM.
   
  pasos = (grados/360)*pasosvuelta;       //calculo la cantidad de pasos que tengo que enviar. 
  Serial.print(pasos);
  Serial.print(" pasos a ");
  retardo = 30000000/(rpms*pasosvuelta);  //calculo el retardo según las RPM indicadas.
  Serial.print(retardo);
  Serial.print(" uSeg\n");
  Serial.println("---------------------------------------");

  for (int x = 0; x < pasos; x++) {      //envio los pasos calculados con el retardo calculado
    servo.write (0);
    digitalWrite(ledV, HIGH);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(retardo);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(retardo);
    servo.write (90);
    digitalWrite(ledV, LOW);
    digitalWrite(ledR, LOW);
  }
}

//-----------------FUNCIONES-------------------------- 
void pasosporvuelta() {          
  Serial.print("¿Pasos por vuelta? (pasos del motor * micropasos) ");
  while (Serial.available() == 0 ) {} //queda esperando hasta recibir un mensaje
  mensaje = Serial.readString();
  pasosvuelta = mensaje.toInt();      //convierte en mensaje recibido en un entero
  if (pasosvuelta == 0) {             //si no es un número envía ERROR y vuelve a llamar a la función
    Serial.print("ERROR\n");
    pasosporvuelta();
  }
  else {                              //si es un número nos envia un mensaje de OK
    Serial.print(pasosvuelta);
    Serial.print(" OK\n");
  }
}

void sentido() {
  Serial.print("¿Sentido de giro? (0 horario / 1 antihorario) ");
  while (Serial.available() == 0 ) {}
  mensaje = Serial.readString();
  if (mensaje == "0\n") {
    Serial.print("horario OK\n");
    digitalWrite(dirPin, HIGH);
  }
  else if (mensaje == "1\n") {
    Serial.print("antihorario OK\n");
    digitalWrite(dirPin, LOW);       
  }
  else {
    Serial.print("ERROR\n");
    sentido();     
  }
}

void giro() {
  Serial.print("¿Grados? ");
  while (Serial.available() == 0 ) {}
  mensaje = Serial.readString();
  grados = mensaje.toFloat();
  if (pasosvuelta == 0) {
    Serial.print("ERROR\n");
    giro();
  }
  else {
    Serial.print(grados);
    Serial.print(" OK\n");
  }
}

void velocidad() {
  Serial.print("¿Velocidad de giro? (RPM) ");
  while (Serial.available() == 0 ) {}
  mensaje = Serial.readString();
  rpms = mensaje.toInt();
  if (rpms == 0) {
    Serial.print("ERROR\n");
    velocidad();
  }
  else {
    Serial.print(rpms);
    Serial.print(" OK\n");
    
  }
}
