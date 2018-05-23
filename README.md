# ArduinoClock

An alarm clock based on Arduino with many features like weather, temperature, humidity... This alarm clock has been realized for a school project. You can find more details of this project (in French) in the file Compte_Rendu.pdf.<br />
Un réveil basé sur Arduino avec différentes fonctions : météo, température, humidité... Ce réveil a été réalisé dans le cadre d'un projet d'école. Vous trouverez plus d'informations sur ce projet dans le fichier Compte_Rendu.pdf.

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
  Please wire all components as explained in the wiring diagram (Wiring_Diagram.png).
  
<strong>Programming :</strong>
  Upload horloge.ino file in Arduino. You will also need these libraries : DHT, DS3231, FastLed, Adafruit_BMP085 and Adafruit_Sensor (available in libraries folder).
  
After these steps, you'll just have to work on the esthetic aspect to lay the clock on a table for example. You can make an enclosure in wood (like pictures) or plastic depending your house decoration. You can also add a paper sheet in front of the LED panel in order to spread the light. Now just plug-in the Arduino in a 5V source and enjoy (see buttons.png to know how to use buttons) !

<hr />

<h2>Tutoriel :</h2>
<strong>Composants requis :</strong>

  - Arduino Uno R3
  - Module horloge RTC DS3231
  - Capteur de température DHT11
  - Capteur de pression BMP180
  - Photorésistance (et une résistance de 10kOhm)
  - Capteur de vibration (HDX)
  - Buzzer
  - Câbles
  - Matrice LED WS2812B
  - Matrice de bouton 4x4
  
<strong>Câblage :</strong>
  Le câblage se fait comme expliqué sur le schéma de câblage (Wiring_Diagram.png).
  
<strong>Programmation :</strong>
  Téléverser le fichier horloge.ino dans l'Arduino. Vous aurez également besoin de ces librairies : DHT, DS3231, FastLed, Adafruit_BMP085 et Adafruit_Sensor (disponibles dans le dossier libraries).
  
Après ces étapes, vous avez juste à peaufiner l'aspect esthétique pour rendre l'horloge présentable. Vous pouvez faire un boitier en bois (comme sur les photos) ou en plastique en fonction de la décoration de votre pièce. Vous pouvez également ajouter une feuille de papier devant la matrice de LED pour diffuser la lumière. Pour finir, vous avez juste à brancher l'Arduino sur une source 5V et profitez (voir buttons.png pour l'utilisation des boutons) !
