/*
   Programm:          LED Laufleuchte mit 8 LED durch Taster Stoppen
   Letzte Änderung:   06.10.2020
   Programmierer:     LC
   Bibliotheken:      OneButton
   Hardware:      Arduino UNO / 8 LED's an Pin 2,3,4,5,6,7,8,9 / Taster an Pin 10
*/

unsigned long intervall = 500;
unsigned long startpunkt;
unsigned long ende;

#include <OneButton.h>

OneButton taster(10, false);
boolean merkerStartStop = false;

byte led[8] = {2, 3, 4, 5, 6, 7, 8, 9};

byte ledZustand[7][8] =
{
  {1, 0, 0, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {1, 0, 0, 0, 0, 0, 0, 1},
};

void setup()
{
  Serial.begin(9600);
  taster.attachClick(Funktion_StartStop);
  {
    for (byte i = 0; i < 8; i++)
    {
      pinMode (led[i], OUTPUT);
    }
  }
}

void loop()
{
  taster.tick();
  delay(10);
  {
    if (merkerStartStop == true)
    {
        for (byte i = 0; i < 7; i++)      //Zeilen
        {
          delay(100);
          for (byte j = 0; j < 8; j++)    //Spalten
          {
            digitalWrite(led[j], ledZustand[i][j]);
          }
          taster.tick();
        }
      }
      else
      {
        for (byte i = 0; i < 8; i++)
        {
          digitalWrite(led[i], LOW);
        }
      }
    }
  }
  void Funktion_StartStop ()
  {
    merkerStartStop = !merkerStartStop;
  }
