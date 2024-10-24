// Control de Juanito

#include <xmotionV3.h> // Biblioteca XMotion incluida
int RightSensor = A5; // Pin del sensor de oponente derecho
int RightDiagonalSensor = 4; // Pin del sensor de oponente diagonal derecho
int MiddleSensor = 2; // Pin del sensor de oponente central
int LeftDiagonalSensor = 1; // Pin del sensor de oponente diagonal izquierdo
int LeftSensor = 0; // Pin del sensor de oponente izquierdo

int LeftLine = A2; // Pin del sensor de línea izquierdo
int RightLine = A4; // Pin del sensor de línea derecho
int Start = A0; // Pin del botón de inicio

int Led1 = 8;

int LastValue = 0;

void setup() {
  xmotion.StopMotors(100); // Detener motores, en caso de que los pines de salida estén abiertos.
  xmotion.ToggleLeds(100); // Función de parpadeo para hacer parpadear 2 LEDs de usuario con un retardo.
  pinMode(Led1, OUTPUT);
  pinMode(RightSensor, INPUT); // Declaramos las entradas y salidas digitales.
  pinMode(RightDiagonalSensor, INPUT);
  pinMode(MiddleSensor, INPUT);
  pinMode(LeftDiagonalSensor, INPUT);
  pinMode(LeftSensor, INPUT);
  pinMode(Start, INPUT);
  Serial.begin(9600);
}

void loop() {
  while (digitalRead(Start) == 0) // Se espera que se pulse el botón. Cuando se presiona, da un valor de 1.
  { // Esta instrucción if
    if (digitalRead(LeftSensor) == 1 || digitalRead(MiddleSensor) == 1 || digitalRead(RightSensor) == 1 || digitalRead(RightDiagonalSensor) == 1 || digitalRead(LeftDiagonalSensor) == 1)
    {
      digitalWrite(Led1, HIGH);
    } else {
      digitalWrite(Led1, LOW);
    }

    xmotion.UserLed2(100); // Parpadeo del LED de usuario 2 en intervalos de 100 milisegundos.
  }
  xmotion.CounterLeds(1000, 5);
  while (1) {
    if (analogRead(LeftLine) < 800 && analogRead(RightLine) > 800 ) // El sensor de línea izquierdo detecta la línea
    {
      xmotion.Backward(100, 100); // Retroceder al 100% de velocidad, retroceso de 100 ms.
      xmotion.Right0(100, 200); // Giro a la derecha al 100% de velocidad, duración de 200 ms.
    } else if (analogRead(LeftLine) > 800 && analogRead(RightLine) < 800 ) // El sensor de línea derecho detecta la línea
    {
      xmotion.Backward(100, 100); // Retroceder al 100% de velocidad, retroceso de 100 ms.
      xmotion.Left0(100, 200); // Giro a la izquierda al 100% de velocidad, duración de 200 ms.
    } else if (analogRead(LeftLine) < 800 && analogRead(RightLine) < 800 ) // Ambos sensores detectan la línea
    {
      xmotion.Backward(100, 200); // Retroceder al 100% de velocidad, retroceso de 200 ms.
      xmotion.Right0(100, 300); // Giro a la izquierda al 100% de velocidad, duración de 200 ms.
    }

    else if (digitalRead(MiddleSensor) == 1 ) // El sensor central ve al oponente (0 No visto, 1 Visto)
    {
      xmotion.Forward(100, 1); // Ambos motores hacia adelante al 100% de velocidad, 1 milisegundo
      LastValue = 0;
    }
    else if (digitalRead(RightSensor) == 1) // El sensor derecho ve al oponente
    {
      xmotion.Right0(70, 1); // Giro a la derecha al 70% de potencia durante 1 milisegundo
      LastValue = 1;
    }
    else if (digitalRead(LeftSensor) == 1) // El sensor izquierdo ve al oponente
    {
      xmotion.Left0(70, 1); // Giro a la izquierda al 70% de potencia durante 1 milisegundo
      LastValue = 2;
    }
    else if (digitalRead(LeftDiagonalSensor) == 1) // El sensor diagonal izquierdo ve al oponente
    {
      xmotion.ArcTurn(20, 70, 1); // Motor izquierdo al 20% de velocidad, derecho al 70% de velocidad durante 1 ms.
      LastValue = 2;
    }
    else if (digitalRead(RightDiagonalSensor) == 1) // El sensor diagonal derecho ve al oponente
    {
      xmotion.ArcTurn(70, 20, 1); // Motor izquierdo al 70% de velocidad, derecho al 20% de velocidad durante 1 ms.
      LastValue = 1;
    } else if (LastValue == 0) { // El sensor central vio al oponente
      xmotion.Forward(20, 1);
    } else if (LastValue == 1) { // El sensor derecho o diagonal derecho vio al oponente
      xmotion.Right0(30, 1);
    } else if (LastValue == 2) { // El sensor izquierdo o diagonal izquierdo vio al oponente
      xmotion.Left0(30, 1);
    }
  }
}

