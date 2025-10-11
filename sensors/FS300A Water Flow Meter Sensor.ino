volatile int count1 = 0;
volatile int count2 = 0;

const int sensor1 = 2;  // Sensor 1 signal
const int sensor2 = 3;  // Sensor 2 signal

float flow1 = 0;
float flow2 = 0;
float total1 = 0;
float total2 = 0;

void ISR1() { count1++; }
void ISR2() { count2++; }

void setup() {
  Serial.begin(9600);
  pinMode(sensor1, INPUT_PULLUP);
  pinMode(sensor2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(sensor1), ISR1, RISING);
  attachInterrupt(digitalPinToInterrupt(sensor2), ISR2, RISING);

  Serial.println("Water Flow Sensors Started");
}

void loop() {
  count1 = 0;
  count2 = 0;
  interrupts();
  delay(1000);   // measure for 1 second
  noInterrupts();

  // Convert pulses to L/min (approx 5.5 pulses per L/min)
  flow1 = count1 / 5.5;
  flow2 = count2 / 5.5;

  // Add total volume (in liters)
  total1 += flow1 / 60.0;
  total2 += flow2 / 60.0;

  Serial.print("Sensor 1: ");
  Serial.print(flow1);
  Serial.print(" L/min | Total: ");
  Serial.print(total1);
  Serial.println(" L");

  Serial.print("Sensor 2: ");
  Serial.print(flow2);
  Serial.print(" L/min | Total: ");
  Serial.print(total2);
  Serial.println(" L");

  Serial.println("----------------------");
}
