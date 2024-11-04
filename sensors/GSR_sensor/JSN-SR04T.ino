#define echoPin 18 // attach pin GPIO18 to pin Echo of JSN-SR04
#define trigPin 5  // attach pin GPIO5 ESP32 to pin Trig of JSN-SR04                     

long duration;
int distance;
const int numSamples = 5; // Number of samples for averaging

void setup()
{
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);  
  Serial.begin(9600);
  Serial.println("Distance measurement using JSN-SR04T");
  delay(500);
}

void loop()
{
  int totalDistance = 0;

  // Take multiple samples
  for (int i = 0; i < numSamples; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2); 

    digitalWrite(trigPin, HIGH); // turn on the Trigger to generate pulse
    delayMicroseconds(10); // keep the trigger "ON" for 10 us to generate pulse
    digitalWrite(trigPin, LOW); // Turn off the pulse trigger to stop pulse

    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.0344 / 2;
    totalDistance += distance;
    delay(10); // Small delay between samples
  }

  // Calculate the average distance
  distance = totalDistance / numSamples;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(500); // Control how frequently measurements are taken
}
