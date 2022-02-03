#include "M5StickCPlus.h"
#include "sat3.h"
#include "font.h"


#include <WiFi.h>
#include "time.h"

const char* ssid     = "xxxxx";
const char* password = "xxxxxx";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec =3600;
const int   daylightOffset_sec = 3600;


#define background 0xB635
 
int moove=46;


void setup() {

  Serial.begin(9600);
   WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");

 
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
 
  M5.begin();
  M5.Axp.ScreenBreath(9);
   
 
 M5.Lcd.setRotation(1);
 M5.Lcd.setSwapBytes(true);

 M5.Lcd.fillScreen(TFT_WHITE); 

 M5.Lcd.pushImage(0,0-moove,240,240,sat3);
 M5.Lcd.setTextColor(0x0081,background);
 M5.Lcd.fillRoundRect(48,107-moove,138,48,5,background);

}

String tM="ww";


void loop() {  delay(1000);
  printLocalTime();

}

void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  
  /*Serial.println(&timeinfo);
  Serial.print("Day of week: ");
  Serial.println(&timeinfo, "%A");
  Serial.print("Month: ");
  Serial.println(&timeinfo, "%B");
  Serial.print("Day of Month: ");
  Serial.println(&timeinfo, "%d");
  Serial.print("Year: ");
  Serial.println(&timeinfo, "%Y");
  Serial.print("Hour: ");
  Serial.println(&timeinfo, "%H");
  Serial.print("Hour (12 hour format): ");
  Serial.println(&timeinfo, "%I");
  Serial.print("Minute: ");
  Serial.println(&timeinfo, "%M");
  Serial.print("Second: ");
  Serial.println(&timeinfo, "%S");
  */

  char timeHour[3];
  strftime(timeHour,3, "%H", &timeinfo);
  

  char timeMin[3];
  strftime(timeMin,3, "%M", &timeinfo);
  String m=String(timeMin);

  char timeSec[3];
  strftime(timeSec,3, "%S", &timeinfo);

   char timeWeekDay[3];
  strftime(timeWeekDay,10, "%A", &timeinfo);
   String d=String(timeWeekDay);

   char timeDay[3];
  strftime(timeDay,3, "%d", &timeinfo);


  if(tM!=m){
  M5.Lcd.setFreeFont(&DSEG7_Classic_Bold_30);
  M5.Lcd.drawString(String(timeHour)+":"+String(timeMin),46,126-moove);
  tM=m;
  }

  M5.Lcd.setFreeFont(&DSEG7_Classic_Bold_20);
  M5.Lcd.drawString(String(timeSec),154,136-moove);

 
   M5.Lcd.setFreeFont(&DSEG14_Classic_Bold_18);
 M5.Lcd.drawString(d.substring(0,2),94,96-moove);
 M5.Lcd.drawString(String(timeDay),156,96-moove);
  
  
  
 
}
