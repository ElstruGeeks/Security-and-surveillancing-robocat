// Define pins for ultrasonic and buzzer
#define SPEAKER   11
int const trigPin = 9;
int const echoPin = 10;
int const buzzPin = 5;
int smokeA0 = A0;
// Your threshold value
int sensorThres = 400;

void setup()
{
  pinMode(trigPin, OUTPUT); // trig pin will have pulses output
  pinMode(echoPin, INPUT); // echo pin should be input to get pulse width
  pinMode(buzzPin, OUTPUT); // buzz pin is output to control buzzering
  pinMode(SPEAKER,OUTPUT);  // important to set pin as output
  pinMode(smokeA0, INPUT); // set pin to analog A0

  Serial.begin(57600); // Starts the serial communication
}

void loop()
{
  // Duration will be the input pulse width and distance will be the distance to the obstacle in centimeters
  int duration, distance;
  // Output pulse with 1ms width on trigPin
  digitalWrite(trigPin, HIGH); 
  delay(1);
  digitalWrite(trigPin, LOW);
  // Measure the pulse input in echo pin
  duration = pulseIn(echoPin, HIGH);
  // Distance is half the duration devided by 29.1 (from datasheet)
  distance = (duration/2) / 29.1;
  // if distance less than 0.5 meter and more than 0 (0 or less means over range) 
    if (distance <= 50 && distance >= 0) {
       meow2();
  delay(1000);
    }
    // Waiting 60 ms won't hurt any one
    delay(60);
 // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
 //Gas Detection
 int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    tone(SPEAKER, 1000, 200);
  }
  else
    {
    noTone(SPEAKER);
    }
  delay(100);
}

void meow() {  // cat meow (emphasis ow "me")
  uint16_t i;
  playTone(3100,50);        // "m" (short)
  playTone(304,180);        // "eee" (long)
  for(i=990; i<1022; i+=2)  // vary "ooo" down
     playTone(i,8);
  playTone(6100,40);        // "w" (short)
}

void meow2() {  // cat meow (emphasis on "ow")
  uint16_t i;
  playTone(5100,55);
  playTone(394,170);       // "eee" (long)
  delay(30);               // wait a tiny bit
  for(i=330; i<360; i+=2)  // vary "ooo" down
     playTone(i,10);
  playTone(5100,40);       // "w" (short)
}

void mew() {  // cat mew
  uint16_t i;
  playTone(5100,55);       // "m"   (short)
  playTone(394,130);       // "eee" (long)
  playTone(384,35);        // "eee" (up a tiny bit on end)
  playTone(5100,40);       // "w"   (short)
}


// play tone on a piezo speaker: tone shorter values produce higher frequencies
//  which is opposite beep() but avoids some math delay - similar to code by Erin Robotgrrl

void playTone(uint16_t tone1, uint16_t duration) {
  if(tone1 < 50 || tone1 > 15000) return;  // these do not play on a piezo
  for (long i = 0; i < duration * 1000L; i += tone1 * 2) {
     digitalWrite(buzzPin, HIGH);
     delayMicroseconds(tone1);
     digitalWrite(buzzPin, LOW);
     delayMicroseconds(tone1);
  }     
}
