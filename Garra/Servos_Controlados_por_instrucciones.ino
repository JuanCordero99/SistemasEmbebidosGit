#include<Servo.h>

String mensaje;
float grados1, grados2, grados3;

Servo servo, servo2, servo3 ;

void setup() {

  Serial.begin(9600);
  servo.attach(3);
  servo2.attach(4);
  servo3.attach(5);

}

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

  delay(1500);

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

  delay(1500);

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

  delay(1500);

}
