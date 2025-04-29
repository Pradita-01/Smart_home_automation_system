#define TEMP_SENSOR_PIN A2
#define LED 8      
#define ledpin2 6
#define ledpin3 5
#define BUTTON 2            
#define MOTOR_PIN 9 
#define LDR_PIN A3  
#define RELAY_PIN 2  

#define LDR_THRESHOLD 500 
#define TEMP_THRESHOLD 10   

bool motorState = false; 

void setup() {
  Serial.begin(9600);       
  pinMode(LED, OUTPUT);   
  pinMode(ledpin2 , OUTPUT);
  pinMode(ledpin3 , OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(MOTOR_PIN, OUTPUT); 
  pinMode(RELAY_PIN, OUTPUT); 
  pinMode(LDR_PIN, INPUT); 
}

void loop() {
  
  int sensorValue = analogRead(TEMP_SENSOR_PIN);
  float voltage = sensorValue * (5.0 / 1023.0);  
  float temperature = (voltage - 0.5) * 100.0; 
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");


  if (temperature > TEMP_THRESHOLD) {
    digitalWrite(ledpin2 , HIGH);
    digitalWrite(ledpin3 , HIGH);
  } else {
    digitalWrite(ledpin2 , LOW);
    digitalWrite(ledpin3, LOW);
  }


  if (temperature > TEMP_THRESHOLD) {
    int motorSpeed = map(temperature, TEMP_THRESHOLD, 30, 10, 255); 
    motorSpeed = constrain(motorSpeed, 10, 255);  
    analogWrite(MOTOR_PIN, motorSpeed); 
  } else {
    analogWrite(MOTOR_PIN, 0); 
  }


  int lightLevel = analogRead(LDR_PIN);

  if (lightLevel < LDR_THRESHOLD) { 
    digitalWrite(RELAY_PIN, HIGH);  
    Serial.println("Bulb is ON");
  } else { 
    digitalWrite(RELAY_PIN, LOW);   
    Serial.println("Bulb is OFF");
  }

  delay(1000);
}
