 void setup() {
  Serial.begin(9600);
  Serial.println("Send Message...");
  // Serial.println("ATD8320317410");
  // Serial.println("AT+CNMI=2,2,0,0,0");
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"+918320317410\"");
  delay(1000);
  Serial.println("Hello Bhavya!");
  Serial.write((char)26);
}

void loop() {
   
}
