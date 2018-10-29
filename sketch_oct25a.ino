#define USE_ARDUINO_INTERRUPTS true
#include <LiquidCrystal.h> //library for LCD
#include <TinyGPS.h> //Library for GPS module
#include <SoftwareSerial.h> //SOfwtare serial library
const int rs = 2, en = 3, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
const float lat = 22.600796, lon = 72.820256; 
int PulseSensorPin = 0, LED = 13;
float Signal, myBPM, Threshold = 220;
TinyGPS gps; //object of tinygps
SoftwareSerial gpsSerial(6,7);  //gpsSerial(rx,tx)
LiquidCrystal lcd(rs,en,d4,d5,d6,d7); 

void setup() {
  Serial.begin(9600);   
  gpsSerial.begin(9600);
  lcd.begin(16,2);
  LCD_init();  //calling lcd_init() function
  pinMode(LED,OUTPUT); //setting led as output pin
}

void loop() {
  Signal = analogRead(PulseSensorPin); //reading data from analogsensorpin
  Serial.println(Signal); //printing on serial monitor
  myBPM = (1/Signal) * 60 *1000; 
  if(myBPM > Threshold){
     digitalWrite(LED,HIGH);
     LCD_print();
     lcd.print("BPM: ");
     lcd.setCursor(5,0);
     lcd.print(myBPM);
     delay(1000);
     lcd.clear();
     lcd.print("BPM is high");
     delay(1000);
     lcd.clear();
     lcd.print("Sending message");
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"+918320317410\"");
  delay(1000);
  Serial.println(myBPM);
  delay(1000);
  Serial.write((char)26);
  delay(5000);
     lcd.clear();
    // lcd.print("Calling...");
    // calling();
    // lcd.clear();
    // lcd.print("Call ended!");
    // delay(1000);
    // lcd.clear();
     fetchgps();
     lcd.print("Sending lat");
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"+918320317410\"");
  delay(1000);
  Serial.println(lat);
  delay(1000);
  Serial.write((char)26);
  delay(5000);
  lcd.clear();
  lcd.print("Sending lon");
    Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"+918320317410\"");
  delay(1000);
  Serial.println(lon);
  delay(1000);
  Serial.write((char)26);
  delay(5000);
  lcd.clear();
     String latitude = String(lat,6); 
     String longitude = String(lon,6); 
    delay(1000);       
  }else {
     digitalWrite(LED,LOW);
     LCD_print();
     lcd.print("BPM: ");
     lcd.setCursor(5,0);
     lcd.print(myBPM);
     delay(1000);
     lcd.clear();
  }
delay(100);
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

void calling()
{
 /* Serial.println("ATD8320317410;"); //calling alert   
  delay(8000);
  Serial.println("ATH");  //disconnecting call */
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"+918320317410\"");
  delay(1000);
  Serial.println(myBPM);
  delay(1000);
  Serial.write((char)26);
  delay(5000);
}
void LCD_print(){
     lcd.print("BPM: ");
     lcd.setCursor(5,0);
     lcd.print(myBPM);
     delay(1000);
     lcd.clear();
}
void fetchgps(){
     lcd.print("Fetching GPS");
     for(int i=12;i<16;i++)
     {
      lcd.setCursor(i,0);
      lcd.print(".");
      delay(500);
     }
     delay(1000);
     lcd.clear();
     gps.f_get_position(&lat, &lon);
     lcd.setCursor(1,0); 
     lcd.print("LAT:"); 
     lcd.setCursor(5,0); 
     lcd.print(lat); 
     lcd.setCursor(1,1); 
     lcd.print("LON:"); 
     lcd.setCursor(5,1); 
     lcd.print(lon);
     delay(5000);
     lcd.clear();
}
