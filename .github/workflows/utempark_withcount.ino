#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

Servo myservo;

#define ir_enter 2
#define ir_back  4
#define ir_car1 5
#define ir_car2 6
#define ir_car3 7
#define ir_car4 8
#define ir_car5 9
#define ir_car6 10

int S1 = 0, S2 = 0, S3 = 0, S4 = 0, S5 = 0, S6 = 0;
int prevS1 = 0, prevS2 = 0, prevS3 = 0, prevS4 = 0, prevS5 = 0, prevS6 = 0;
int flag1 = 0, flag2 = 0, flag3 = 0; 
int slot = 6;
unsigned long servoTimer = 0;

void setup() {
  Serial.begin(9600);

  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);
  pinMode(ir_car3, INPUT);
  pinMode(ir_car4, INPUT);
  pinMode(ir_car5, INPUT);
  pinMode(ir_car6, INPUT);

  pinMode(ir_enter, INPUT);
  pinMode(ir_back, INPUT);
  
  myservo.attach(3);
  myservo.write(90);

  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0, 1);
  lcd.print("  UTEM Car parking  ");
  lcd.setCursor(0, 2);
  lcd.print("       System     ");
  delay(2000);
  lcd.clear();   

  Read_Sensor();

  int total = S1 + S2 + S3 + S4 + S5 + S6;
  slot = slot - total; 
}

void loop() {
  Read_Sensor();

  lcd.setCursor(0, 0);
  lcd.print("   Have Slot: "); 
  lcd.print(slot);
  lcd.print("    ");  

  lcd.setCursor(0, 1);
  if(S1 == 1) {
    lcd.print("S1:Fill ");
  } else {
    lcd.print("S1:Empty");
  }

  lcd.setCursor(10, 1);
  if(S2 == 1) {
    lcd.print("S2:Fill ");
  } else {
    lcd.print("S2:Empty");
  }

  lcd.setCursor(0, 2);
  if(S3 == 1) {
    lcd.print("S3:Fill ");
  } else {
    lcd.print("S3:Empty");
  }

  lcd.setCursor(10, 2);
  if(S4 == 1) {
    lcd.print("S4:Fill ");
  } else {
    lcd.print("S4:Empty");
  }

  lcd.setCursor(0, 3);
  if(S5 == 1) {
    lcd.print("S5:Fill ");
  } else {
    lcd.print("S5:Empty");
  }

  lcd.setCursor(10, 3);
  if(S6 == 1) {
    lcd.print("S6:Fill ");
  } else {
    lcd.print("S6:Empty");
  }    

  if(digitalRead(ir_enter) == 0 && flag1 == 0) {
    if(slot > 0) {
      flag1 = 1;
      if(flag2 == 0) {
        myservo.write(180);
        servoTimer = millis();  
        slot = slot - 1; 
      }
    } else {
      lcd.setCursor(0, 0);
      lcd.print(" Sorry Parking Full ");  
      delay(1500);
    }   
  }

  
  if(prevS1 == 1 && S1 == 0) {
    slot = slot + 1;
  }
  if(prevS2 == 1 && S2 == 0) {
    slot = slot + 1;
  }
  if(prevS3 == 1 && S3 == 0) {
    slot = slot + 1;
  }
  if(prevS4 == 1 && S4 == 0) {
    slot = slot + 1;
  }
  if(prevS5 == 1 && S5 == 0) {
    slot = slot + 1;
  }
  if(prevS6 == 1 && S6 == 0) {
    slot = slot + 1;
  }

  
  if(flag1 == 1 && flag2 == 0 && millis() - servoTimer >= 5000) {
    myservo.write(90);
    flag1 = 0;
  }

  
  if(millis() - servoTimer >= 2000 && digitalRead(ir_back) == 0 && flag3 == 0) {
    myservo.write(180);
    delay(1000);  
    myservo.write(90);
    flag3 = 1;
  }

  delay(1);
}

void Read_Sensor() {
  prevS1 = S1;
  prevS2 = S2;
  prevS3 = S3;
  prevS4 = S4;
  prevS5 = S5;
  prevS6 = S6;

  S1 = 0, S2 = 0, S3 = 0, S4 = 0, S5 = 0, S6 = 0;

  if(digitalRead(ir_car1) == 0) {
    S1 = 1;
  }
  if(digitalRead(ir_car2) == 0) {
    S2 = 1;
  }
  if(digitalRead(ir_car3) == 0) {
    S3 = 1;
  }
  if(digitalRead(ir_car4) == 0) {
    S4 = 1;
  }
  if(digitalRead(ir_car5) == 0) {
    S5 = 1;
  }
  if(digitalRead(ir_car6) == 0) {
    S6 = 1;
  }  
}

