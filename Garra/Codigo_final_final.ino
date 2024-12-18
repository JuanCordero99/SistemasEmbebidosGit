#include <Servo.h>

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

Servo servo, servo2, servo3;

//-----------------SETUP------------------------------
void setup() {
  pinMode(ledV, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(dirPin, OUTPUT);   
  pinMode(stepPin, OUTPUT);  
  Serial.begin(9600);       
  pasosporvuelta();          
  servo.attach(3);
  servo2.attach(4);
  servo3.attach(5);
}

//-----------------LOOP------------------------------
void loop() {
  Serial.println("¿Qué motor quieres controlar?");
  Serial.println("Z. Servo 1");
  Serial.println("Y. Servo 2");
  Serial.println("3. Servo 3");
  Serial.println("X. Motor paso a paso");

  while (Serial.available() == 0) {} 
  mensaje = Serial.readString();
  int opcion = mensaje.toInt();      
  switch (opcion) {
    case 1:
      controlarServo(servo, "Servo 1", 'Z');
      break;
    case 2:
      controlarServo(servo2, "Servo 2", 'Y');
      break;
    case 3:
      controlarServo(servo3, "Servo 3", '3');
      break;
    case 4:
      controlarMotor();
      break;
    default:
      Serial.print("Opción no válida\n");
      break;
  }
}

void controlarServo(Servo s, String nombre, char eje) {
  Serial.print("Dime los grados de ");
  Serial.print(nombre);
  Serial.print(" (Eje ");
  Serial.print(eje);
  Serial.print("): ");

  while (Serial.available() == 0) {} 
  mensaje = Serial.readString();
  grados = mensaje.toFloat(); 
  if (grados == 0) { 
    Serial.print("ERROR\n");
  } else {
    Serial.print(grados);
    Serial.print(" OK\n");
    Serial.print("Moviendo ");
    Serial.print(nombre);
    Serial.print(" (Eje ");
    Serial.print(eje);
    Serial.println(")...");
    s.write(grados);
  }

  delay(500);
  Serial.println("Movimiento completo.\n");
}

void controlarMotor() {
  digitalWrite(ledR, HIGH);
  sentido();
  giro();
  velocidad();

  pasos = (grados / 360) * pasosvuelta;
  Serial.print(pasos);
  Serial.print(" pasos a ");
  retardo = 30000000 / (rpms * pasosvuelta);

  Serial.print(rpms);
  Serial.print(" RPM, ");
  Serial.print(grados);
  Serial.print(" grados, ");
  Serial.print(pasos);
  Serial.print(" pasos, ");
  Serial.print(retardo);
  Serial.print(" microsegundos de retardo\n");

  digitalWrite(ledR, LOW);
  for (int x = 0; x < pasos; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(retardo);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(retardo);
  }
}

void velocidad() {
  Serial.println("¿A qué velocidad quieres que gire el motor? (RPM)");

  while (Serial.available() == 0) {} 
  mensaje = Serial.readString();
  rpms = mensaje.toInt(); 
  if (rpms == 0) {
    Serial.print("ERROR\n");
    velocidad();
  } else {
    Serial.print(rpms);
    Serial.print(" RPM OK\n");
  }
}

//-----------------FUNCIÓN PARA DEFINIR EL SENTIDO DE GIRO--------------
void sentido() {
  Serial.println("¿En qué sentido quieres que gire el motor?");
  Serial.println("1. Horario");
  Serial.println("2. Antihorario");

  while (Serial.available() == 0) {} 
  mensaje = Serial.readString();
  int opcion = mensaje.toInt(); 
  if (opcion == 1) {
    Serial.print("Horario OK\n");
    digitalWrite(dirPin, HIGH);
  } else if (opcion == 2) {
    Serial.print("Antihorario OK\n");
    digitalWrite(dirPin, LOW);
  } else {
    Serial.print("Opción no válida\n");
    sentido();
  }
}

//-----------------FUNCIÓN PARA HACER GIRAR EL MOTOR--------------
void giro() {
  Serial.println("¿Cuántos grados quieres que gire el motor?");

  while (Serial.available() == 0) {} 
  mensaje = Serial.readString();
  grados = mensaje.toFloat(); 
  if (grados == 0) {
    Serial.print("ERROR\n");
    giro();
  } else {
    Serial.print(grados);
    Serial.print(" grados OK\n");
  }
}

//-----------------FUNCIÓN PARA CALCULAR LOS PASOS POR VUELTA--------------
void pasosporvuelta() {
  Serial.println("¿Cuántos pasos tiene el motor por vuelta?");
  while (Serial.available() == 0) {} 
  mensaje = Serial.readString();
  pasosvuelta = mensaje.toInt(); 
  if (pasosvuelta == 0) {
    Serial.print("ERROR\n");
    pasosporvuelta();
  } else {
    Serial.print(pasosvuelta);
    Serial.print(" pasos por vuelta OK\n");
  }
}

//---------------FIN DEL PROGRAMA-----------------
