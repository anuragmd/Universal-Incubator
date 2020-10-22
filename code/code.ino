// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

#define DHTPIN A5
// Digital pin connected to the DHT sensor 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)
#define b1 8
#define b2 9
#define b3 10
#define b4 11
#define BULB 13
#define MOTOR 12
#define FAN 2

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;


void setup() {
  Serial.begin(9600);
  display.begin();
  display.setContrast(50);
  pinMode(BULB,OUTPUT);
  pinMode(FAN,OUTPUT);
  pinMode(MOTOR,OUTPUT);  
  
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

float h,t;
int i=0;int c;
int flag=0;int hours;
String nam[6]={"Chicken","Turkey","  Duck"," Goose"," Quail"," Pigeon"};
float temp=37.7;
int start_time;
int hum[6]={85,84,85,86,86,85};
int rot[6]={18,25,25,25,21,15};
int day[6]={21,28,28,34,28,17};
int days;

void loop() {
  
///////MAIN MENU///////
if(flag==0)
{
  digitalWrite(BULB,LOW);
  digitalWrite(MOTOR,LOW);
  digitalWrite(FAN,LOW);
  while(digitalRead(b3)!=1)
  {
    display.clearDisplay();
    display.setTextSize(1); 
    display.println("  Choose Egg"); 
    display.println(" ");
    display.setTextSize(2);
    display.print(nam[i]);
    display.setTextSize(1);
    display.setCursor(0,37);
    display.print("prev      next");
    //display.drawRect(0,13,84,20,BLACK);
    display.display();
    delay(1000);
      if(digitalRead(b1)==1)
      {
        if(i>=1)
         i--;
      }
      if(digitalRead(b2)==1)
      {
        if(i<5)
         i++;
      }
      if(digitalRead(b4)==1)
      {
        display.setTextSize(1);
        display.clearDisplay();        
        digitalWrite(MOTOR,HIGH);
        display.println("MOTOR ON");
        display.display(); 
        delay(5000);
        display.clearDisplay(); 
        digitalWrite(MOTOR,LOW);
        display.println("MOTOR OFF");
        display.display();
        delay(1000);

        display.clearDisplay();        
        digitalWrite(FAN,HIGH);
        display.println("FAN ON");
        display.display(); 
        delay(1000);
        display.clearDisplay(); 
        digitalWrite(FAN,LOW);
        display.println("FAN OFF");
        display.display();                
        delay(1000);
        
        display.clearDisplay();        
        digitalWrite(BULB,HIGH);
        display.println("BULB ON");
        display.display(); 
        delay(1000);
        display.clearDisplay(); 
        digitalWrite(BULB,LOW);
        display.println("BULB OFF");
        display.display();
        delay(1000);
      }
  }
  flag=1;
  start_time=millis();
}  

  hours=(millis()-start_time)/3600000;
  days=hours/24;
   
  delay(delayMS);
  sensors_event_t event;
  
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    t=event.temperature;    
  }
  
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    h=event.relative_humidity;
  }

///////////////////////////////////////////  
  ////screen1/////
  display.clearDisplay();
  display.setTextSize(1); 

  display.print("Type :");
  display.println(nam[i]);

  display.println("CURRENT");
   
  display.print("Hum   :");  //display humidity
  display.print(h);
  display.println("%");
  
  display.print("Temp  :");  //display temperature
  display.print(t);
  display.println("C");

  display.print("Total Days:"); //display time remaining
  display.println(day[i]);

  display.display();

  delay(2000);
  ////screen2/////
  display.clearDisplay();
  display.setTextSize(1); 

  display.print("Type :"); 
  display.println(nam[i]);

  display.println("TARGET");
   
  display.print("Hum   :");  //display humidity
  display.print(hum[i]);
  display.println("%");
  
  display.print("Temp  :");  //display temperature
  display.print(temp);
  display.println("C");

  display.print("Days left:"); //display time remaining
  display.println(day[i]-days);
  
  display.display();

  delay(500);  
//////////////ADJUSTING///////////////////

    if(t>temp)                   //adjust temp
     {
      digitalWrite(BULB,LOW);  
     }
    else
     {
      digitalWrite(BULB,HIGH); 
     }

    if(h<hum[i])                 //adjust humidity(fan speed);
    {
      digitalWrite(FAN,HIGH);  
    }
    else
    {
      digitalWrite(FAN,LOW);
    }
    if(days>rot[i])               //adjust rotation
    {
      digitalWrite(MOTOR,LOW);
    }
    else
    {
      if(hours!=c)
      {
        digitalWrite(MOTOR,HIGH);
        delay(30);
      }
      int c=hours;
    }
////////RESET/////////////////////////////  

  if(digitalRead(b4)==1)
  {
    flag=0;
  }
//////////////////////////////////////////
  
}
