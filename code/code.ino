#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Blynk.h>
// Replace with your network credentials
char auth[] = "FbCNOvxCexLcOhBfHMu7HHMwF_vef67J";
char ssid[] = "Neeku enduku";
char pass[] = "kkoo8071";

int count=0;
char card_no[12];

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
BlynkTimer timer;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  mlx.begin();
  timer.setInterval(5000L, sendTemp); // Send temperature data to Blynk every 1 second
}

void loop() {
  if(Serial.available())
   {
      count = 0;
      while(Serial.available() && count < 12)
      {
         card_no[count] = Serial.read();
         count++;
         delay(5);
      }
      Serial.print("RFID value: ");
      Serial.print(card_no);
      Blynk.run();
      timer.run();
   }
}

void sendTemp() {
  float tempC = mlx.readObjectTempC();
  tempC=mlx.readObjectTempC();
  delay(2000);// Send temperature data to Virtual Pin V1 in Blynk
  Serial.println(tempC);
  Blynk.virtualWrite(V4, tempC);
  Blynk.virtualWrite(V5, card_no);
  if(tempC > 30){
    Blynk.logEvent("temp_exceed", "from " +String(card_no));
    //Blynk.notify("Alert!", card_no );
  }
}
