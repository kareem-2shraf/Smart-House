#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>

Adafruit_LiquidCrystal lcd(0); 

// Servo def
Servo gateServo;

// Sensor def
#define irPin 2
//bool carDetected = false;

void setup() {
  // LCD
  lcd.begin(16, 2);    
  lcd.setBacklight(1); 

  lcd.setCursor(0, 0);
  lcd.print("Smart Gate Ready");

  // IR Sensor
  pinMode(irPin, INPUT);

  // Servo
  gateServo.attach(9); 
  gateServo.write(0);

  lcd.setCursor(0, 0);
  lcd.print("Smart Gate Ready");
}

void loop() {
  int irState = digitalRead(irPin);

  if (irState == LOW) 
  {  
    //if (!carDetected) {
     // carDetected = true;
      // open
      gateServo.write(90); // open the gate angle
      // display
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Car Detected");
      lcd.setCursor(0, 1);
      lcd.print("Gate: OPEN");
    // }
  } 
  else 
  {
    //if (carDetected) {
      //carDetected = false;
      // to close the gate
      gateServo.write(0);

      // update the data on screen
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("No Car Nearby");
      lcd.setCursor(0, 1);
      lcd.print("Gate: CLOSED");
   // }
  }

  delay(200); // to make it stable
}

