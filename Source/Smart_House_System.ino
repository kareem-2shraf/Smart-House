#define ser_pin 9
#define ser2_pin 11
#define ser3_pin 10
#define buzzpin 12
#define ir1Pin A2
#define ir2Pin A3
#define ir3Pin 13
#define lm35 A0
#define ldr A1
#define fan 8
#define led1 7
#define led2 6
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 
const int rows=2;
const int cols=2;
char keys[rows][cols]={
   {'7','8'},
   {'*','0'}  
};
byte rowpins[rows]= {5,4};
byte colspins[cols]={3,2};
Keypad keypad = Keypad( makeKeymap(keys), rowpins, colspins, rows, cols );
Servo myServo;
Servo gateServo;
Servo garageServo;
char stored_pass[]={"780"};
const int number=sizeof(stored_pass)-1;
char pass[number];
int i=0,count=0,size=0,pos=0,ldr_reading,ir1State,ir3State,ir2State,button=13,button_reading,k=0;
int flag1=0,flag2=0,*flag1_ptr=&flag1,*flag2_ptr=&flag2;
float lm35_reading;

void setup()
{
  lcd.init();            
  lcd.backlight();       
  lcd.setCursor(0, 0);   
  myServo.attach(ser_pin);
  myServo.write(90);
  gateServo.attach(ser2_pin);  
  gateServo.write(90);
  pinMode(buzzpin,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(fan,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  delay(100);
  Serial.begin(9600);
  garageServo.attach(ser3_pin);
  garageServo.write(90);
}

void loop() 
{
  ir1State=digitalRead(ir1Pin);
  ir2State=digitalRead(ir2Pin);
  ir3State=digitalRead(ir3Pin);
  if (flag1==0&&flag2==0)
  in_door();
  else if(flag1==1&&flag2==0)
  {
   if (ir2State==0&&ir1State==1)
    {
      delay(15); 
      gateServo.write(0);                                    
    }
    delay(3000);
    
      gateServo.write(90);           
      delay(15);                      
    *flag1_ptr=0;  
    }
  if(k==0)
  {  
  lcd.print("Enter the pass");
  lcd.setCursor(0,1);  
  k++;
  }
  check_pass();
  if(Serial.available())
  garage();
  }
  else if (flag1==1&&flag2==1)
  {
  temp_ldr();
  if (Serial.available())
  garage();
  }
}
void check_pass(void)
{
  
  char key=keypad.getKey();
  if(key>0 && key!='*')
  {
    lcd.print('*');
    pass[i]=key;
    i++;    
   }
  else if(key=='*')
  {
    for(int j=0 ;j<number ;j++)
    {
      if(pass[j]==stored_pass[j])
      {
        count++;
      } 
      else 
       break;
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
  delay(15);  
  myServo.write(180);                                   
  delay(3000);
  
  myServo.write(90);                                   
  i=0;
  count=0;
  lcd.clear();
  lcd.setCursor(0,0);
  *flag2_ptr=1;
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
    *flag2_ptr=0;
}
void in_door(void)
{
if(ir1State==0&&ir2State==1)
{
    delay(15);
    gateServo.write(180);              
                             
    delay(3000);
    gateServo.write(90);                                  
}
lcd.print("welcome home");
delay(5000);
lcd.clear();
lcd.setCursor(0,0);
*flag1_ptr=1;
}
}

void temp_ldr(void)
{
ir3State = digitalRead(ir3Pin);
lm35_reading=(analogRead(lm35)*5*1000/(1023*10));
ldr_reading =map(analogRead(ldr),0,1023,0,255);
button_reading=digitalRead(button);
analogWrite(led1,ldr_reading);
analogWrite(led2,ldr_reading);
ir2State = digitalRead(ir2Pin);
lcd.print("TEMP : ");
lcd.print(lm35_reading);
lcd.setCursor(0,1);
lcd.print("LIGHTING : ");
lcd.print(ldr_reading/255);
lcd.setCursor(0,0);
if(lm35_reading>25&&lm35_reading<35)
{
digitalWrite(fan,1); 
digitalWrite(buzzpin,0);
}
else if (lm35_reading>=35&&button_reading==1)
{
digitalWrite(fan,1);
digitalWrite(buzzpin,1);
}
else
{
 digitalWrite(fan,0);
 digitalWrite(buzzpin,0);
}
if(ir3State ==0)
{
lcd.clear();
lcd.setCursor(0,0);
delay(15);
myServo.write(180));                                     
lcd.print("good bye");
delay(3000); 
myServo.write(90);                                   
lcd.clear();
lcd.setCursor(0,0);
*flag2_ptr=0;
}
}
void garage(void)
  {
    String command = Serial.readStringUntil("\n");
    command.trim();
    if(command == "open")
    {
      delay(15); 
      garageServo.write(0);              
                             
      }
      Serial.println("Garage openned");
    }
    else if (command == "close")
    {
      delay(15); 
      garageServo.write(0);                                   
      Serial.println("Garage closed");
    }
    else
    {
      Serial.println("Invalid command, Enter 'open' or 'close'.");
    }
  }
