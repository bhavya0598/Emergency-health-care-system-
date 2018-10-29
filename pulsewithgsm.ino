#define USE_ARDUINO_INTERRUPTS true
#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 8, d5 = 9, d6 = 10, d7 = 11; 
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);       
const int LED13 = 13;   
float Signal;                
int Threshold = 200;           
float myBPM;
void setup() {
  //pinMode(LED13,OUTPUT); 
    lcd.begin(16,2);
    LCD_init();        
   Serial.begin(9600);         
   pinMode(LED13,OUTPUT);
}
void loop() {
  Signal = analogRead(A0); 
  myBPM = (1/Signal)*60*1000;
  //Serial.println(Signal);           
   if(Signal>Threshold){                        
     digitalWrite(LED13,HIGH);
        delay(200);
        LCD_print();
        // Serial.println("Calling... ");
        Serial.println("Send Message...");
        delay(10);
        // Serial.println("ATD8320317410;");
        // Serial.println("AT+CNMI=2,2,0,0,0");
        Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"+918320317410\"");
  delay(1000);
  Serial.println(myBPM);
  delay(1000);
        Serial.write((char)26);
   } else {
     digitalWrite(LED13,LOW);               
   Serial.println(myBPM);
   }
delay(10000);
}

void LCD_init()
{
  lcd.begin(16, 2);
  lcd.print("Emergency Health");
  lcd.setCursor(0,1);
  lcd.print("Care System.....");
  delay(5000);
  lcd.clear();
}
void LCD_print(){
     lcd.print("BPM: ");
     lcd.setCursor(5,0);
     lcd.print(myBPM);
     delay(1000);
     lcd.clear();
}
