const int leds[] = {4, 5, 6, 7}; 

const int botones[] = {8, 9, 10, 11}; 
// Para 6 niveles, 4 LEDs por nivel
int nivel[6][4]; 

void setup() {
    Serial.begin(9600); 
    for (int i = 0; i < 4; i++) {
        pinMode(leds[i], OUTPUT); 
        pinMode(botones[i], INPUT_PULLUP); 
        digitalWrite(leds[i], LOW); 
    }
    // Semilla aleatoria
    randomSeed(analogRead(A0)); 
    generarNiveles(); 
}

void loop() {
    int res[4];
    for (int i = 0; i < 6; i++) {
        bool nivelSuperado = false;

        // Repite el nivel actual hasta que el usuario lo complete exitosamente
        while (!nivelSuperado) {
            // Pasa el arreglo res a la función level
            level(i, res); 
            nivelSuperado = comprobarRespuesta(i, res); 

            if (nivelSuperado) {
                Serial.println("Nivel superado.");
                for (int x = 0; x < 5; x++) {
                    ledsOn();
                    delay(500);
                    ledsOff();
                    delay(200);
                }
            } else {
                Serial.println("Error en el nivel. Repitiendo nivel...");
                ledRed(); 
                delay(1000); 
            }
        }

        delay(1000);
    }
}

void ledsOff() {
    for (int x = 0; x < 4; x++) {
        digitalWrite(leds[x], LOW);
    }
}

// Función para encender todos los LEDs
void ledsOn() {
    for (int x = 0; x < 4; x++) {
        digitalWrite(leds[x], HIGH);
    }
}

// Función para indicar un error con el LED rojo
void ledRed() {
    for (int x = 0; x < 2; x++) {
        digitalWrite(leds[0], HIGH); 
        delay(500);
        digitalWrite(leds[0], LOW);
        delay(500);
    }
}

bool comprobarRespuesta(int nivelActual, int res[]) {
    for (int j = 0; j < 4; j++) {
        if (res[j] != nivel[nivelActual][j]) {
            return false; 
        }
    }
    return true; 
}

// Generar la secuencia de niveles
void generarNiveles() {
    for (int i = 0; i < 6; i++) { 
        for (int j = 0; j < 4; j++) {
            nivel[i][j] = random(0, 4);
        }

        // Permitir repeticiones limitadas
        for (int j = 1; j < 4; j++) {
            if (nivel[i][j] == nivel[i][j - 1]) { 
                nivel[i][j] = (nivel[i][j] + 1) % 4; 
            }
        }
    }
}

// Función que maneja la lógica de cada nivel
void level(int nivelActual, int res[]) {
    int conteo = 0;

    // Muestra la secuencia de LEDs para el nivel actual
    for (int j = 0; j < 4; j++) {
        digitalWrite(leds[nivel[nivelActual][j]], HIGH);
        delay(500);
        digitalWrite(leds[nivel[nivelActual][j]], LOW);
        delay(200);
    }

    // Indica que se espera una respuesta
    ledsOn();
    delay(300);
    ledsOff();
    delay(300);

    // Respuesta del usuario
    while (conteo < 4) {
        for (int x = 0; x < 4; x++) {
            if (digitalRead(botones[x]) == HIGH) {
                digitalWrite(leds[x], HIGH);
                res[conteo] = x;
                delay(300); 
                digitalWrite(leds[x], LOW);
                conteo++;
            }
        }
    }

    // Apaga todos los LEDs al finalizar la captura
    ledsOff();
}
