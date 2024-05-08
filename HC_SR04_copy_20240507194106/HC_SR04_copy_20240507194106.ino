const int trigPin = 9;  
const int echoPin = 10;
float duration, distance;
int counter = 0;
float sum = 0.0;

// I am Lars
void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);  // trigPin is our output
	pinMode(echoPin, INPUT);  // echoPin is our input
	Serial.begin(9600);  
  Serial.println("The code started working.");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);  // Sets the output to OFF
	delayMicroseconds(2);  // After 2 micro seconds, sends out a puls for 10 microseconds
	digitalWrite(trigPin, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPin, LOW); // Sets the output to OFF again.
  duration = pulseIn(echoPin, HIGH); // Receives the output that was sent and measures the time it took
  distance = (duration*.0343)/2; // Calculates the distance to the object from the duration
  Serial.print("Distance: ");  
	Serial.println(distance);  
	delay(100);
  counter++;
  sum = sum + distance;
  // if(counter>5){
  //   //Serial.print("Average Distance: ");
  //   exit(0);
  // }

}
