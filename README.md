# ArduinoClock

An alarm clock based on Arduino with many features like weather, temperature, humidity...

<h2>Tutorial :</h2>

<strong>Components needed :</strong>
  - Arduino Uno R3
  - Clock Module RTC DS3231
  - Temperature Sensor DHT11
  - Pressure Sensor BMP180
  - Photoresistor (and a 10kOhm resistor)
  - Vibrating Sensor (HDX)
  - Buzzer
  - Wiring Jumpers
  - LED Matrix WS2812B
  - 4x4 Button Keypad
  
<strong>Wiring :</strong>
  Please wire all components as explained in the wiring diagram.
  
<strong>Programming :</strong>
  Upload horloge.ino file in Arduino. You will also need these libraries : DHT.h, DS3231.h, FastLed.h and Adafruit_BMP085.h.
  
After these steps, you'll just have to work on the esthetic aspect to lay the clock on a table for example. You can make an enclosure in wood (like pictures) or plastic depending your house decoration. Now just plug-in the Arduino in a 5V source and enjoy !
