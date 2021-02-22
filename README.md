# Bedroom-Environmental-Parameters
## Humidity and Temperature Monitoring for Control of Humidifier
#### Problem:
The humidifier in my bedroom had no humidistat built in to regulate run time to not raise the humitiy of the room beyond 60 percent relative humidity. 

#### Solution:
Using a Particle Photon, Smart Outlet Switch, and a AHT20 Humidity and Temperature Sensor the humidifier is transformed from a dumb humidifier to a smart one. 

#### Hardware:
  * Particle Photon Board-[Particle Store](https://store.particle.io/collections/wifi/products/photon)
  * Smart Outlet Switch (any with Smartthings integration will do)
  * Adafruit AHT20 - Temperature & Humidity Sensor Breakout Board - STEMMA QT / Qwiic [Adafruit Store](https://www.adafruit.com/product/4566)

#### Software:
  * Particle Web IDE [Particle Build](https://build.particle.io/build)
  * Firebase [Sign Up for Firebase](https://firebase.google.com/)
  * SmartThings [SmartThings Groovy IDE](https://graph.api.smartthings.com/)
  
  ###### OPTIONAL SOFTWARE
   * Microsoft Visual Studio [Visual Studio Download](https://visualstudio.microsoft.com/)

#### Code:
  * Fork from the Particle Web IDE Library [SparkFun_Qwiic_Humidity_AHT20_Arduino_Library](https://build.particle.io/libs/SparkFun_Qwiic_Humidity_AHT20_Arduino_Library/1.0.0)
  
#### Repository Contents
  * Custom code utilizing the forked library for the AHT20
  * Groovy code to control smartplug 
    
