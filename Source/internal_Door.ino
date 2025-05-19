#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>
#define ser_pin 12
#define buzzpin 10
LiquidCrystal_I2C lcd(0x27, 16, 2); 
//keypad
const int rows=4;
const int cols=4;
char keys[rows][cols]={
   {'1','2','3','A'},
   {'4','5','6','B'},
   {'7','8','9','C'},
   {'*','0','#','D'}  
};
byte rowpins[rows]= {9,8,7,6};
byte colspins[rows]={5,4,3,2};
Keypad keypad = Keypad( makeKeymap(keys), rowpins, colspins, rows, cols );
//pass
char stored_pass[]={"123AB"};
const int number=sizeof(stored_pass)-1;
char pass[number];
int i=0,count=0,size=0;
//servo
Servo myServo;
void setup()
{
  lcd.init();            
  lcd.backlight();       
  lcd.setCursor(0, 0);   
  lcd.print("ENTER THE PASS:"); 
  lcd.setCursor(0,1);
  myServo.write(0);       
  delay(100);
  myServo.attach(ser_pin);
  pinMode(buzzpin,OUTPUT);
}

void loop() 
{
  check_pass();
}
void check_pass(void)
{
  char key=keypad.getKey();
  if(key>0 && key!='D')
  {
    lcd.print('*');
    pass[i]=key;
    i++;    
   }
  else if(key=='D')
  {
    for(int j=0 ;j<number ;j++)
    {
      if(pass[j]==stored_pass[j])
      {
        count++;
      } 
    }
    if(count==number && i==number)
    {
      correctpass();
    }
    else
    {
      wrongpass();
    }
  }    
} 
void correctpass(void)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("correct pass");
  myServo.write(90);
  delay(5000);
  myServo.write(0);
  i=0;
  count=0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ENTER PASS");
  lcd.setCursor(0,1);
}
void wrongpass(void)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("wrong pass ");
  digitalWrite(buzzpin, HIGH);
  delay(2000);
  digitalWrite(buzzpin, LOW);
  i=0;
  count=0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ENTER PASS AGAIN");
  lcd.setCursor(0,1);
}