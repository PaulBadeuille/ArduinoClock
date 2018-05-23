#include <FastLED.h>
#include <DS3231.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>

CRGB leds[256];
Adafruit_BMP085 bmp;
DS3231 clock;
DHT dht(6, DHT11);
RTCDateTime dt;
int r = 135, g = 135, b = 135, fonc = 0, alarmh = 0, alarmm = 0, etatalarm = 0;

#include "gerer_matrice.h"

int *afficheur = new int[256];
int rangee[] = {2, 3, 4, 5};
int colonne[] = {8, 9, 10, 7};
int col_scan;

void setup() {
  clock.begin();
  dht.begin();
  bmp.begin();
  pinMode(11, OUTPUT);
  FastLED.addLeds<WS2811, 13, GRB>(leds, 256).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(64);
  for (int i = 0; i <= 3; i++)
  {
    pinMode(rangee[i], OUTPUT);
    pinMode(colonne[i], INPUT);
    digitalWrite(colonne[i], HIGH);
  }
}

void loop()
{
  for (int i = 0; i <= 3; i++)
  {
    digitalWrite(rangee[0], HIGH);
    digitalWrite(rangee[1], HIGH);
    digitalWrite(rangee[2], HIGH);
    digitalWrite(rangee[3], HIGH);
    digitalWrite(rangee[i], LOW);
    for (int j = 0; j <= 3; j++)
    {
      col_scan = digitalRead(colonne[j]);
      if (col_scan == LOW)
      {
        toucherBouton(i, j);
        delay(300);
      }
    }
  }
  if (fonc == 0) {
    afficherHeure();
  }
  else if (fonc == 1) {
    afficherDate();
  }
  else if (fonc == 2) {
    afficherAlarm();
  }
  else if (fonc == 3) {
    afficherTemperature();
  }
  else {
    afficherHumidite();
  }
  if (alarmm == clock.getDateTime().minute && alarmh == clock.getDateTime().hour && etatalarm == 1) {
    while (etatalarm == 1) {
      alarme(etatalarm);
    }
    fonc = 0;
  }
}

void augmenter(int &r) {
  r = r + 15;
  if (r == 270) {
    r = 0;
  }
}

void diminuer(int &r) {
  r = r - 15;
  if (r == -15) {
    r = 255;
  }
}

void reset(int &r, int &g, int &b) {
  r = 135;
  g = 135;
  b = 135;
}

void changerFonction(int &fonc) {
  fonc++;
  if (fonc == 5)fonc = 0;
}

void toucherBouton(int i, int j)
{
  if (i == 0 && j == 0)augmenter(r);
  if (i == 0 && j == 1)augmenter(g);
  if (i == 0 && j == 2)augmenter(b);
  if (i == 0 && j == 3)changerFonction(fonc);
  if (i == 1 && j == 0)diminuer(r);
  if (i == 1 && j == 1)diminuer(g);
  if (i == 1 && j == 2)diminuer(b);
  if (i == 1 && j == 3)reset(r, g, b);
  if (i == 2 && j == 0 && fonc == 2)augmenterminute(alarmm);
  if (i == 2 && j == 1 && fonc == 2)augmenterheure(alarmh);
  if (i == 2 && j == 2) {}
  if (i == 2 && j == 3) {}
  if (i == 3 && j == 0 && fonc == 2)diminuerminute(alarmm);
  if (i == 3 && j == 1 && fonc == 2)diminuerheure(alarmh);
  if (i == 3 && j == 2)changeretat(etatalarm);
  if (i == 3 && j == 3) {}
}

void afficherHumidite() {
  int h = dht.readHumidity();
  int hum_0 = 0;
  int hum_1 = 0;
  if (h > 89) {
    hum_1 = 9;
    hum_0 = h - 90;
  }
  else if (h > 79) {
    hum_1 = 8;
    hum_0 = h - 80;
  }
  else if (h > 69) {
    hum_1 = 7;
    hum_0 = h - 70;
  }

  else if (h > 59) {
    hum_1 = 6;
    hum_0 = h - 60;
  }

  else if (h > 49) {
    hum_1 = 5;
    hum_0 = h - 50;
  }
  else if (h > 39) {
    hum_1 = 4;
    hum_0 = h - 40;
  }

  else if (h > 29) {
    hum_1 = 3;
    hum_0 = h - 30;
  }

  else if (h > 19) {
    hum_1 = 2;
    hum_0 = h - 20;
  }
  else if (h > 9) {
    hum_1 = 1;
    hum_0 = h - 10;
  }
  else {
    hum_0 = h;
    hum_1 = 0;
  }
  modifierMatrice(hum_1, 0, afficheur);
  modifierMatrice(hum_0, 1, afficheur);
  modifierMatrice(11, 2, afficheur);
  modifierMatrice(11, 3, afficheur);
  double photo = (double)analogRead(A0) / 1000;
  if (photo < 0.20) {
    photo = 0.20;
  }
  afficherMatrice(afficheur, floor(r * photo), floor(g * photo), floor(b * photo), 3, 0);
}

void afficherTemperature() {
  int temperature = bmp.readTemperature();
  int temperature_0 = 0;
  int temperature_1 = 0;
  if (temperature > 39) {
    temperature_1 = 4;
    temperature_0 = temperature - 40;
  }
  else if (temperature > 29) {
    temperature_1 = 3;
    temperature_0 = temperature - 30;
  }
  else if (temperature > 19) {
    temperature_1 = 2;
    temperature_0 = (temperature - 20);
  }
  else if (temperature > 9) {
    temperature_1 = 1;
    temperature_0 = temperature - 10;
  }
  else {
    temperature_1 = 0;
    temperature_0 = temperature;
  }
  modifierMatrice(temperature_1, 0, afficheur);
  modifierMatrice(temperature_0, 1, afficheur);
  modifierMatrice(11, 2, afficheur);
  modifierMatrice(11, 3, afficheur);
  double photo = (double)analogRead(A0) / 1000;
  if (photo < 0.20) {
    photo = 0.20;
  }
  afficherMatrice(afficheur, floor(r * photo), floor(g * photo), floor(b * photo), 2, 0);
}

void afficherDate() {

  dt = clock.getDateTime();

  int jour = dt.day;
  int mois = dt.month;
  int jour_0 = 0;
  int jour_1 = 0;
  int mois_0 = 0;
  int mois_1 = 0;

  if (mois > 9) {
    mois_1 = 1;
    mois_0 = mois - 10;
  }
  else {
    mois_1 = 0;
    mois_0 = mois;
  }

  if (jour > 29) {
    jour_1 = 3;
    jour_0 = jour - 30;
  }
  else if (jour > 19) {
    jour_1 = 2;
    jour_0 = (jour - 20);
  }
  else if (jour > 9) {
    jour_1 = 1;
    jour_0 = jour - 10;
  }
  else {
    jour_1 = 0;
    jour_0 = jour;
  }
  modifierMatrice(jour_1, 0, afficheur);
  modifierMatrice(jour_0, 1, afficheur);
  modifierMatrice(mois_1, 2, afficheur);
  modifierMatrice(mois_0, 3, afficheur);
  double photo = (double)analogRead(A0) / 1000;
  if (photo < 0.20) {
    photo = 0.20;
  }
  afficherMatrice(afficheur, floor(r * photo), floor(g * photo), floor(b * photo), 1, 0);
}

void afficherHeure()
{
  dt = clock.getDateTime();

  int minutes = dt.minute;
  int heures = dt.hour;
  int minute_0 = 0;
  int minute_1 = 0;
  int heure_0 = 0;
  int heure_1 = 0;
  if (minutes > 49) {
    minute_1 = 5;
    minute_0 = minutes - 50;
  }
  else if (minutes > 39) {
    minute_1 = 4;
    minute_0 = minutes - 40;
  }
  else if (minutes > 29) {
    minute_1 = 3;
    minute_0 = minutes - 30;
  }
  else if (minutes > 19) {
    minute_1 = 2;
    minute_0 = (minutes - 20);
  }
  else if (minutes > 9) {
    minute_1 = 1;
    minute_0 = minutes - 10;
  }
  else {
    minute_1 = 0;
    minute_0 = minutes;
  }
  if (heures > 19) {
    heure_1 = 2;
    heure_0 = heures - 20;
  }
  else if (heures > 9) {
    heure_1 = 1;
    heure_0 = heures - 10;
  }
  else {
    heure_1 = 0;
    heure_0 = heures;
  }
  modifierMatrice(heure_1, 0, afficheur);
  modifierMatrice(heure_0, 1, afficheur);
  modifierMatrice(minute_1, 2, afficheur);
  modifierMatrice(minute_0, 3, afficheur);
  double photo = (double)analogRead(A0) / 1000;
  if (photo < 0.20) {
    photo = 0.20;
  }
  afficherMatrice(afficheur, floor(r * photo), floor(g * photo), floor(b * photo), 0, dt.second);
}

void augmenterminute(int& alarmm)
{
  alarmm++;
  if (alarmm == 60)
  {
    alarmm = 0;
  }
}

void augmenterheure(int& alarmh)
{
  alarmh++;
  if (alarmh == 24)
  {
    alarmh = 0;
  }
}


void diminuerminute(int& alarmm)
{
  alarmm--;
  if (alarmm == -1)
  {
    alarmm = 59;
  }
}

void diminuerheure(int& alarmh)
{
  alarmh--;
  if (alarmh == -1)
  {
    alarmh = 23;
  }
}

void changeretat(int &etatalarm) {
  etatalarm++;
  if (etatalarm == 2)
  {
    etatalarm = 0;
  }
}

void afficherAlarm()
{
  int aminute_0 = 0;
  int aminute_1 = 0;
  int aheure_0 = 0;
  int aheure_1 = 0;
  if (alarmm > 49) {
    aminute_1 = 5;
    aminute_0 = alarmm - 50;
  }
  else if (alarmm > 39) {
    aminute_1 = 4;
    aminute_0 = alarmm - 40;
  }
  else if (alarmm > 29) {
    aminute_1 = 3;
    aminute_0 = alarmm - 30;
  }
  else if (alarmm > 19) {
    aminute_1 = 2;
    aminute_0 = (alarmm - 20);
  }
  else if (alarmm > 9) {
    aminute_1 = 1;
    aminute_0 = alarmm - 10;
  }
  else {
    aminute_1 = 0;
    aminute_0 = alarmm;
  }
  if (alarmh > 19) {
    aheure_1 = 2;
    aheure_0 = alarmh - 20;
  }
  else if (alarmh > 9) {
    aheure_1 = 1;
    aheure_0 = alarmh - 10;
  }
  else {
    aheure_1 = 0;
    aheure_0 = alarmh;
  }
  modifierMatrice(aheure_1, 0, afficheur);
  modifierMatrice(aheure_0, 1, afficheur);
  modifierMatrice(aminute_1, 2, afficheur);
  modifierMatrice(aminute_0, 3, afficheur);
  double photo = (double)analogRead(A0) / 1000;
  if (photo < 0.20) {
    photo = 0.20;
  }
  afficherMatrice(afficheur, floor(r * photo), floor(g * photo), floor(b * photo), 4, 0);
}

void alarme(int& etatalarm) {
  afficherHeure();
  digitalWrite(11, HIGH);
  delay(75);
  digitalWrite(11, LOW);
  delay(75);
  if (analogRead(A1) < 950)
  {
    etatalarm = 0;
  }
}
