#include <Wire.h>
#include <Particle.h>

// This #include statement was automatically added by the Particle IDE.
#include <SparkFun_Qwiic_Humidity_AHT20.h>
AHT20 humiditySensor;
// This #include statement was automatically added by the Particle IDE.

#include <PowerShield.h>
PowerShield batteryMonitor;


//Time interval to recheck environmental parameters
#define ENVIR_CHECK_INTERVAL 2000

float temperature;
float humidity;
float fTemp;
double battery = 0;
int status;
unsigned long lastenvircheck = 0; //Tracks last time the environmental parameters were checked.


void setup()
{
  batteryMonitor.begin();
    // This sets up the fuel gauge
    batteryMonitor.quickStart();
    Particle.publishVitals(3000);
    delay(1000);
   
Particle.publish("Qwiic Humidity AHT20 examples");
  Wire.begin(); //Join I2C bus

  //Check if the AHT20 will acknowledge
  if (humiditySensor.begin() == false)
  {
   // Serial.println("AHT20 not detected. Please check wiring. Freezing.");
    Particle.publish("AHT20 not detected. Please check wiring. Freezing.");
    while (1);
  }
  //Serial.println("AHT20 acknowledged.");
  Particle.publish("AHT20 acknowledged.");
  
   // Subscribe to the integration response event
  Particle.subscribe("hook-response/Enviro_Firebase", myHandler, MY_DEVICES);
  //Used for outputting most current data to control humidifier
  Particle.subscribe("hook-response/SwitchControl_Firebase", myHandler, MY_DEVICES);
  envparam();
  delay(2000);
  battread();
  delay(2000);
}
 



void myHandler(const char *event, const char *data) {
  // Handle the integration response
}


void loop() {
delay(2000);
envparam();
battread();
pub();
delay(60000);    


/*   
     if (lastenvircheck + ENVIR_CHECK_INTERVAL < millis()) {
   lastenvircheck = millis(); 
   envparam();
     }
     else {
  pub(); 
}
*/
}

//Read Temp and humidity
void envparam() {
    //If a new measurement is available
  if (humiditySensor.available() == true)
  {
    //Get the new temperature and humidity value
    temperature = round(humiditySensor.getTemperature());
    humidity = round(humiditySensor.getHumidity());
    
    //Convert temperature from C to F
    fTemp=temperature * 9 / 5 + 32;
    
    Particle.publish("temp F", String(round(fTemp)));
  
    Particle.publish("Humidity", String(humidity));
 
  }    
}

//Check state of charge of the battery
void battread(){

uint32_t stateOfCharge = batteryMonitor.getSoC();
battery = stateOfCharge;  
    
}

//Adjusts for daylight savings time
bool IsDST(int dayOfMonth, int month, int dayOfWeek)
{
	if (month < 3 || month > 11) {
		return false;
	}
	if (month > 3 && month < 11) {
		return true;
	}
	int previousSunday = dayOfMonth - (dayOfWeek - 1);
	if (month == 3) {
		return previousSunday >= 8;
	}
	return previousSunday <= 0;
}  

void pub() {
//Result of battery charge
//Particle.publish("result", String(cHumid));

//Result for temperature
//Particle.publish("Temp", String(f));
  
//Result for humidity
//Particle.publish("Humidity", String(h));  


//Track the time of day and only published to be on or off depending on this.
bool daylightSavings = IsDST(Time.day(), Time.month(), Time.weekday());
	Time.zone(daylightSavings? -5 : -6);    

if (Time.hour() > 16 && Time.hour() < 24 || Time.hour() < 6 && Time.hour() > 0) { //Time between 5pm or 5am
    if(humidity<=60){
        status = 1; //on
    }
    else if (humidity>60){
        status = 0; //off
    }
    
}
else {
    status = 0; //off
}

 // Get some data
 char buf[256];
	snprintf(buf, sizeof(buf), "{\"Humidity\":%.2f,\"Temperature\":%.2f,\"Battery\":%.3f,\"Status\":%d}", humidity, fTemp, battery, status);
	
	Serial.printlnf("publishing %s", buf);  
  // Trigger the integration
  Particle.publish("Enviro_Firebase", buf, PUBLIC);
  //Publish most current value to allow for switch to read data with groovy
 Particle.publish("SwitchControl_Firebase", buf, PRIVATE);
  
  
  // Wait 60 seconds
  //delay(60000);
  
//Check to see if humidity exceeds 60%
/*
if(humidity <=60){
    Particle.publish("Humidity1", "on");
    }
else {
    Particle.publish("Humidity1", "off");
    }
*/

delay(10s);
SystemSleepConfiguration config;
config.mode(SystemSleepMode::HIBERNATE)
      .gpio(WKP, RISING)
      .duration(600s); //10 minutes
SystemSleepResult result = System.sleep(config);

//Particle.publish("readings", String::format("{\"Hum(\%)\": %4.2f, \"Temp(°F)\": %4.2f, \"DP(°F)\": %4.2f, \"HI(°F)\": %4.2f}", h, f, dp, hi));
//sprintf(pubstring,"{\"Hum(%)\": %4.2f, \"Temp(°F)\": %4.2f, \"DP(°F)\": %4.2f, \"HI(°F)\": %4.2f}",h, f, dp, hi);

	//delay(10000);
}
