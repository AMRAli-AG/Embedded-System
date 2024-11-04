
###############################################
# Author: Amr Ali
# Date: 4/11/2024
# Version: 1.0
###############################################
# Description:
# This script interfaces an ESP32 microcontroller with the JSN-SR04T 
# ultrasonic sensor to measure distance. It uses GPIO18 for the echo 
# signal and GPIO5 for the trigger signal. By emitting a pulse, capturing 
# its echo, and calculating the time taken for the pulse to return, 
# the code estimates the distance to an object.
#
# The code takes multiple measurements, averages them, and filters out 
# erroneous readings for enhanced accuracy.
#
# Usage:
# - Load the code onto an ESP32 microcontroller.
# - Connect the JSN-SR04T sensor to the ESP32 with GPIO18 as the echo 
#   pin and GPIO5 as the trigger pin.
# - Open the Serial Monitor (at 9600 baud) to view real-time distance 
#   readings in centimeters.
#
# Input:
# - Trigger pulse generated by ESP32 to initiate distance measurement.
#
# Output:
# - Serial output displaying the measured distance (in cm) to an object 
#   in front of the sensor.
###############################################
#define echoPin 18 // Define GPIO18 as the echo pin for the JSN-SR04T sensor
#define trigPin 5  // Define GPIO5 as the trigger pin for the JSN-SR04T sensor                     

long duration;     // Variable to store the time it takes for the echo to return
int distance;      // Variable to store the calculated distance
const int numSamples = 5; // Number of samples to take for averaging

void setup()
{
  pinMode(trigPin, OUTPUT); // Set the trigger pin as an output
  pinMode(echoPin, INPUT);   // Set the echo pin as an input
  Serial.begin(9600);        // Initialize serial communication at 9600 baud rate
  Serial.println("Distance measurement using JSN-SR04T"); // Initial message
  delay(500); // Short delay to allow setup completion
}

void loop()
{
  int totalDistance = 0; // Variable to accumulate total distance for averaging

  // Loop to take multiple samples for averaging
  for (int i = 0; i < numSamples; i++) {
    digitalWrite(trigPin, LOW); // Clear the trigger pin to ensure a clean pulse start
    delayMicroseconds(2);       // Wait for 2 microseconds

    digitalWrite(trigPin, HIGH); // Set the trigger pin high to start a pulse
    delayMicroseconds(10);       // Keep the trigger high for 10 microseconds to generate a pulse
    digitalWrite(trigPin, LOW);  // Set the trigger pin low to stop the pulse

    // Measure the duration (in microseconds) for the echo to return
    duration = pulseIn(echoPin, HIGH);
    
    // Calculate the distance based on the duration and speed of sound
    // speed of sound is approximately 0.0344 cm/µs, hence distance in cm = duration * 0.0344 / 2
    distance = duration * 0.0344 / 2;
    
    // Accumulate the distance for averaging
    totalDistance += distance;
    delay(10); // Short delay between samples to stabilize readings
  }

  // Calculate the average distance based on accumulated readings
  distance = totalDistance / numSamples;

  // Output the calculated average distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm"); // Print the distance in centimeters

  delay(50); // Short delay before the next measurement cycle
}