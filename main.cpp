#include <LiquidCrystal.h> // For LCD
const int Switch=53;
int switchState;
const int joyButton=52;
const int xAxis=46;
#define yAxis A10
int yPre=506;
int lastButton=HIGH;
int analogState=1;
int joyState; //Joystick click save
int joyClick; //# of times Joystick Clicked
int down=1;
int yDirect; //Y direction
int miles=0; //Mileage
int Fuel=100; //Gas
int mph=0;


LiquidCrystal lcd(6,7,5,4,3,2); 

void setup() 
{
pinMode(Switch,INPUT_PULLUP);
pinMode(joyButton,INPUT_PULLUP);
lcd.begin(16,2);
Serial.begin(9600);
}
  void Startup()
  {
  switchState=digitalRead(Switch);
  if(switchState==LOW)
  {
  lcd.setCursor(4,0);
  lcd.print("W");
  delay(500);
  lcd.setCursor(5,0);
  lcd.print("E");
  delay(500);
  lcd.setCursor(6,0);
  lcd.print("L");
  delay(500);
  lcd.setCursor(7,0);
  lcd.print("C");
  delay(500);
  lcd.setCursor(8,0);
  lcd.print("O");
  delay(500);
  lcd.setCursor(9,0);
  lcd.print("M");
  delay(500);
  lcd.setCursor(10,0);
  lcd.print("E");
  delay(500);
  lcd.setCursor(11,0);
  lcd.print("!");
  delay(500);
  lcd.clear();
  delay(400);
  lcd.setCursor(4,0);
  lcd.print("WELCOME!");
  delay(600);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("WELCOME!");
  lcd.setCursor(4,0);
  lcd.print(" ");
  delay(600);
  lcd.setCursor(5,0);
  lcd.print(" ");
  delay(600); 
  lcd.setCursor(6,0);
  lcd.print(" ");
  delay(600);
  lcd.setCursor(7,0);
  lcd.print(" ");
  delay(600);
  lcd.setCursor(8,0);
  lcd.print(" ");
  delay(600);
  lcd.setCursor(9,0);
  lcd.print(" ");
  delay(600);
  lcd.setCursor(10,0);
  lcd.print(" ");
  delay(600);
  lcd.setCursor(11,0);
  lcd.print(" ");
  delay(600);
  lcd.clear();
  
  }
  }  
  void Debounce()
  {
    
    int last;
    int debounce=500;
    int current=millis();
    if((millis()-last)>=debounce)
    {
    last=current;
    joyState=digitalRead(joyButton);
    }
  }

  void Descroll()
  {
    int last2;
    int descroll=350;
    int current2=millis();
    if((millis()-last2)>=descroll)
    {
    last2=current2;
    yDirect=analogRead(yAxis);
    }
  }
  void driveMenu()
  {
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print(">Drive");
    lcd.setCursor(2,1);
    lcd.print("Mileage");
    Debounce();
    if(joyState==LOW)
    {
      while(joyClick!=1)
      {
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("MPH:");
      lcd.setCursor(6,0);
      lcd.print(mph);
      Debounce();
      if(joyState==LOW)
        {
          joyClick=1;
        }
      }
      joyClick=0;
    
    }
  }
   
  
  
  
  void mileageMenu()
  {
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Drive");
    lcd.setCursor(1,1);
    lcd.print(">Mileage");
     Debounce();
     if(joyState==LOW)
      {
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("Mileage:");
      lcd.setCursor(10,0);
      lcd.print(miles);
      joyClick++;
      Debounce();
      //if(joyState==LOW)
      
      }
      
    
  }

  void TimeMenu()
  {
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print(">Time");
    lcd.setCursor(2,1);
    lcd.print("Regulatory");
    /*while(joyClick!=2)
     {
      joyState=digitalRead(joyButton);
      if(joyState==LOW)
      {
        joyClick++;
      }
     }
     joyClick=0;
     */
  }
  
 void RegMenu()
 {
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Time");
  lcd.setCursor(1,1);
  lcd.print(">Regulatory");
  Debounce();
  if(joyState==LOW)
  {
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Author:");
    lcd.setCursor(3,1);
    lcd.print("Darryl B");
    joyClick++;
  }
  joyState=digitalRead(joyButton);
  if(joyState==LOW)
  {
    joyClick++;
  }
 
 }


void loop() 
{
  switchState=digitalRead(Switch);
  if(switchState==LOW)
  Startup();
  
  while(switchState==LOW)
  {
   
    switchState=digitalRead(Switch);
    Descroll();    
    if(yDirect>1010)   //Scroll Down
    {
      down++;
      if(down==5)
      down=1;
    }
    if(yDirect<200) //Scroll Up
    {
      down--;
      if(down==0)
      down=1;
    }
/*Serial.print("Y-axis:");
Serial.print(analogRead(yAxis));
Serial.print("\n");
*/
Serial.print("Down:");
Serial.print(down);
Serial.print("\n");
    switch(down)
    {
      case 1:
      driveMenu();
      break;
      case 2:
      mileageMenu();
      break;
      case 3:
      TimeMenu();
      break;
      case 4:
      RegMenu();
      break;
      
    }
    
  }
  
  
  
}

