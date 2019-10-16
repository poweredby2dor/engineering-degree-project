#include<LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void(* resetFunc) (void) = 0;

int resetfunction;

// Parametrii reteta
//  Nr_etapa       = timp in secunde

int e1_asteptare   = 40;
int e2_agitare     = 10;
int e_lichid1      = e1_asteptare + e2_agitare;
int e3_omogenizare = 30;
int e4_solid       = 5;
int e5_omogenizare = 45;
int e6_solid       = 5;
int e7_omogenizare = 30;
int e8_lichid2     = 33;
int e9_omogenizare = 20;
int e10_stabil     = 22;
int e11_evac       = 30;
int e12_wait       = 60;

int releu1 = 37; // Pini pentru relee
int releu2 = 36;
int releu3 = 35;
int releu4 = 34;
int releu5 = 33;
int releu6 = 32;
int releu7 = 31;
int releu8 = 30;
int releu9 = 38;
int releu10 = 39;
int releu11 = 40;
int releu12 = 41;
int releu13 = 42;
int releu14 = 43;
int releu15 = 44;
int releu16 = 45;

int start   = 6;        // Buton Start
int automan = 7;        // Buton Auto / man
int avans   = 8;        // Buton Avans etapa
int reset   = 11;       // Buton Reset alarma
int service = 9;        // Buton Service key
int descarc1   = 0;     // Buton Descarcare lichid 1
int descarc2   = 1;     // Buton Descarcare lichid 2
int descarcvas = 2;     // Buton Descarcare amestec
int deschideclapet = 3; // Buton Deschide clapet
int butonmotor = 4;     // Motor mixer
int urgenta = 5;        // Stop urgenta
int compresor = 14;     // Presiune compresor

int svas1 = 12;
int svas2 = 13;
int pozvalva = 10;

int dozare1, dozare2, solid, descarcare, agitare, alarma;
int lipsa1, lipsa2, emergency, pozitie, confirm, pres1;

char manual = 84;
int x, n, j, jmax, a, b, c, d, e, stare, etapa, alter, counter, minute, serv1, serv2, servvalva, servclapet;
float timer, timp;




void setup() //                        --- VOID SETUP ---
{
  pinMode(releu1, OUTPUT); // Definirea pinilor digitali
  pinMode(releu2, OUTPUT);
  pinMode(releu3, OUTPUT);
  pinMode(releu4, OUTPUT);
  pinMode(releu5, OUTPUT);
  pinMode(releu6, OUTPUT);
  pinMode(releu7, OUTPUT);
  pinMode(releu8, OUTPUT);
  pinMode(releu9, OUTPUT);
  pinMode(releu10, OUTPUT);
  pinMode(releu11, OUTPUT);
  pinMode(releu12, OUTPUT);
  pinMode(releu13, OUTPUT);
  pinMode(releu14, OUTPUT);
  pinMode(releu15, OUTPUT);
  pinMode(releu16, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT); // Initializare LED onboard

  // Default relay state

  digitalWrite(releu1, HIGH);  // Sursa 24V executie
  digitalWrite(releu2, HIGH);  // Sursa 12V compresor
  digitalWrite(releu3, HIGH);  // Bec buton start
  digitalWrite(releu4, HIGH);  // Bec buton auto / man
  digitalWrite(releu5, HIGH);  // Bec buton avans
  digitalWrite(releu6, HIGH);  // Bec buton reset
  digitalWrite(releu7, HIGH);  // Bec lipsa lichid 1
  digitalWrite(releu8, HIGH);  // Bec lipsa lichid 2
  digitalWrite(releu9, HIGH);  // Descarcare vas 1
  digitalWrite(releu10, HIGH); // Descarcare vas 2
  digitalWrite(releu11, HIGH); // Actionare clapet
  digitalWrite(releu12, HIGH); // Actionare valva descarcare
  digitalWrite(releu13, HIGH);
  digitalWrite(releu14, HIGH);
  digitalWrite(releu15, HIGH); // Motor agitare
  digitalWrite(releu16, HIGH); // Compresor aer instrumental

  digitalWrite(LED_BUILTIN, HIGH); // Pornire LED Galben

  lcd.begin(20, 4);

  lcd.clear();

  if (analogRead(service) < 500)
  {
    lcd.print("Macheta licenta");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("Cernat Tudor Liviu");
    delay(500);
    lcd.setCursor(0, 2);
    lcd.print("Conducator stintific");
    delay(500);
    lcd.setCursor(0, 3);
    lcd.print("Dr.Ing.Florin Zamfir");
    delay(4000); // 2 secunde

    lcd.clear();
    lcd.print("Sistem automat");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("de amestecare");
    delay(500);
    lcd.setCursor(0, 2);
    lcd.print("a materiilor prime");
    delay(500);
    lcd.setCursor(0, 3);
    lcd.print("lichide cu solide.");

    delay(4000); // 4 secunde
  }
  else
  {
    delay(1000); // 4 secunde
  }

  lcd.clear();
  lcd.print("Pornire surse: ");
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("12Vdc - Compresor");
  digitalWrite(releu2, LOW); // Sursa 12V
  delay(2000);
  lcd.setCursor(0, 2);
  lcd.print("24Vdc - Executie");
  digitalWrite(releu1, LOW); // Sursa 24V
  delay(2000);

  lcd.clear();
  lcd.print("Verificare mod de");
  lcd.setCursor(0, 1);
  lcd.print("lucru : ");

  delay(500);
  if (analogRead(automan) > 500)
  {
    lcd.print("Manual");
  }
  else
  {
    lcd.print("Automat");
  }

  delay(500);
  if (analogRead(service) > 500)
  {
    lcd.setCursor(0, 3);
    lcd.print("Mod mentenanta activ");
  }

  delay(500);
  x = 5;
  while (x > 0)
  {
    lcd.setCursor(19, 0);
    lcd.print(x);
    x = x - 1;
    while ( analogRead(compresor) < 500 )
    {
      digitalWrite(releu16, LOW); // Compresor aer instrumental
      lcd.setCursor(0, 2);
      lcd.print("Aer instrumental: ! ");
    }
  }
  if ( analogRead(compresor) > 500 )
  {
    lcd.setCursor(0, 2);
    digitalWrite(releu16, HIGH); // Compresor aer instrumental
    lcd.print("Aer instrumental: OK");
    delay(1000);
  }

  digitalWrite(LED_BUILTIN, LOW);
  timp = -1;
}

//                                                                                                        VOID LOOP
//  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//

void loop()
{
  lcd.clear();
  digitalWrite(LED_BUILTIN, LOW);

  if (analogRead(service) > 500)
  {
    digitalWrite(LED_BUILTIN, HIGH);

    // sectiune detectie senzori si contacti

    lcd.setCursor(0, 3);

    if (analogRead(svas1) > 500)
    {
      lcd.print("V1");
    }

    if (analogRead(svas2) > 500)
    {
      lcd.print("V2");
    }

    if (analogRead(pozvalva) > 500)
    {
      lcd.print("VD");
    }

    if (analogRead(compresor) > 500)
    {
      lcd.print("CP");
    }

    if (analogRead(start) > 500)
    {
      lcd.print("B2");
    }

    if (analogRead(automan) > 500)
    {
      lcd.print("B3");
    }

    if (analogRead(avans) > 500)
    {
      lcd.print("B4");
    }

    if (analogRead(reset) > 500)
    {
      lcd.print("B5");
      resetfunction++;
    }

    if (analogRead(descarc1) > 500)
    {
      lcd.print("B7");
      if ( etapa > 2 || etapa == 0 )
      {
        digitalWrite(releu9, LOW);  // Descarcare vas 1
        serv1 = 100;
      }
    }

    if (analogRead(descarc2) > 500)
    {
      lcd.print("B8");
      if ( etapa > 2 || etapa == 0 )
      {
        digitalWrite(releu10, LOW); // Descarcare vas 2
        serv2 = 68;
      }
    }
    if (analogRead(descarcvas) > 500)
    {
      lcd.print("B9");
      if ( etapa != 11 )
      {
        digitalWrite(releu12, LOW); // Actionare valva descarcare
        pozitie = 0;
        servvalva = 40;
      }
    }

    if (analogRead(deschideclapet) > 500)
    {
      lcd.print("B10");
      if ( etapa != 4 && etapa != 6 )
      {
        digitalWrite(releu11, LOW); // Actionare clapet
        servclapet = 20;
      }
    }

    if (analogRead(butonmotor) > 500)
    {
      lcd.print("B11");

      if ( timer < 1 && analogRead(butonmotor) > 500 && ( etapa == 0 || etapa == 1 || etapa > 9 ) )
      {
        digitalWrite(releu15, LOW); // Motor agitare
      }
      else
      {
        digitalWrite(releu15, HIGH); // Motor agitare
      }


      if ( etapa >= 2 && etapa < 9 )
      {  }
      else
      {
        digitalWrite(releu15, LOW); // Motor agitare
      }
    }
    else
    {
      if ( etapa >= 2 && etapa <= 9 )
      { }
      else
        digitalWrite(releu15, HIGH); // Motor agitare
    }

    if (analogRead(urgenta) > 500)
    {
      lcd.print("B12");
    }

    if ( serv1 > 0 )
    {
      lcd.print(" ");
      lcd.print(serv1);
    }
    if ( serv2 > 0 )
    {
      lcd.print(" ");
      lcd.print(serv2);
    }
    if ( servvalva > 0 )
    {
      lcd.print(" ");
      lcd.print(servvalva);
    }
    if ( servclapet > 0 )
    {
      lcd.print(" ");
      lcd.print(servclapet);
    }


  } // Sfarsit secventa service

  // Setarea parametrilor

  if (analogRead(automan) > 500)
  {
    manual = 'm';
  }
  else
  {
    manual = 'a';
  }

  //                                                                                        Sectiune Alarme!
  //  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  //
  //

  if ( analogRead(svas1) < 500 )
  {
    lipsa1 = 1;
  }
  if ( analogRead(svas2) < 500 )
  {
    lipsa2 = 1;
  }

  if ( lipsa1 == 1 )
  {
    digitalWrite(releu7, LOW);  // Bec lipsa lichid 1
  }
  else
  {
    digitalWrite(releu7, HIGH);  // Bec lipsa lichid 1
  }

  if ( lipsa2 == 1 )
  {
    digitalWrite(releu8, LOW);  // Bec lipsa lichid 2
  }
  else
  {
    digitalWrite(releu8, HIGH);  // Bec lipsa lichid 2
  }

  if ( analogRead(urgenta) > 500 )
  {
    emergency = 1;
  }
  if ( analogRead(compresor) < 500 )
  {
    if ( pres1 == 0 )
    {
      pres1 = 2;
    }
    if ( pres1 > 1 )
    {
      pres1++;
    }
    if ( pres1 > 120 )
    {
      pres1 = 1;
    }
  }
  else
  {
    pres1 = 0;
  }

  if ( analogRead(pozvalva) < 500 && pozitie == 0 )
  {
    confirm = 1;
  }
  else
  {
    if ( analogRead(pozvalva) > 500 && pozitie == 1 )
    {
      confirm = 1;
    }
  }

  if ( lipsa1 == 1 || lipsa2 == 1 || emergency == 1 || pres1 == 1 || confirm == 0 )
  {
    alarma = 1;
  }
  else
  {
    alarma = 0;
  }

  if ( alarma == 1 )
  {
    if ( lipsa1 == 1 )
    {
      n = 4;
      a = 1;
    }
    if ( lipsa2 == 1 )
    {
      b = n + 1;
      n = n + 4;
    }
    if ( emergency == 1 )
    {
      c = n + 1;
      n = n + 4;
    }
    if ( pres1 == 1 )
    {
      d = n + 1;
      n = n + 4;
    }
    if ( confirm == 0 )
    {
      e = n + 1;
      n = n + 4;
    }



    if ( lipsa1 == 1 && j >= a && j <= a + 3)
    {
      lcd.setCursor(0, 2);
      lcd.print("Lipsa lichid VAS 1");
    }
    if ( lipsa2 == 1 && j >= b && j <= b + 3)
    {
      lcd.setCursor(0, 2);
      lcd.print("Lipsa lichid VAS 2");
    }
    if ( emergency == 1 && j >= c && j <= c + 3)
    {
      lcd.setCursor(0, 2);
      lcd.print("STOP URGENGA APASAT!");
    }
    if ( pres1 == 1 && j >= d && j <= d + 3)
    {
      lcd.setCursor(0, 2);
      lcd.print("Lipsa aer instr. !");
    }
    if ( confirm == 0 && j >= e && j <= e + 3)
    {
      lcd.setCursor(0, 2);
      lcd.print("Eroare valva pneum.!");
    }
  }

  //                                                                                        Anulare alarme cu reset
  //  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  //

  if ( alarma == 1 )
  {
    digitalWrite(releu9, HIGH);  // Descarcare vas 1
    digitalWrite(releu10, HIGH); // Descarcare vas 2
    digitalWrite(releu11, HIGH); // Actionare clapet
    digitalWrite(releu12, HIGH); // Actionare valva descarcare
    digitalWrite(releu15, HIGH); // Motor agitare
    if ( alter < 4 )
    {
      digitalWrite(releu6, LOW);  // Bec buton reset
    }
    else
    {
      digitalWrite(releu6, HIGH);  // Bec buton reset
    }
  }

  if ( analogRead(reset) > 500 )
  {
    if ( analogRead(svas1) > 500 )
    {
      lipsa1 = 0;
    }
    if ( analogRead(svas2) > 500 )
    {
      lipsa2 = 0;
    }
    if ( analogRead(urgenta) < 500 )
    {
      emergency = 0;
    }

    pres1     = 0;
    confirm   = 1;

    if ( lipsa1 == 1 || lipsa2 == 1 || emergency == 1 || pres1 == 1 || confirm == 0 )
    {
      alarma = 1;
    }
    else
    {
      alarma = 0;
      digitalWrite(releu6, HIGH);  // Bec buton reset
    }
  }

  //
  // Etapele retetei
  //
  //                                                                                                      Etapa 0
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  if ( etapa == 0 )
  {
    lcd.setCursor(0, 1);
    counter = 0;
    if ( alarma == 0 )
    {
      lcd.print("Instalatie pregatita");
    }

    if ( manual == 'a' )
    {
      if ( alarma == 0 )
      {
        digitalWrite(releu3, LOW);  // Bec buton start
      }
    }

    if ( (analogRead(start) > 500) && (manual == 'a') && alarma == 0 )
    {
      etapa = 1;
      timp = 0;
      counter = e1_asteptare * 4 + 1;
      digitalWrite(releu3, HIGH);  // Bec buton start
      digitalWrite(releu5, HIGH);  // Bec buton avans
    }
    if ( analogRead(avans) < 500 && x > 0 )
    {
      counter = e1_asteptare * 4;
      timp = 0;
    }
  } // Final ecran principal

  // Pornire ciclu
  //                                                                                                      Etapa 1
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  if ( etapa == 1 && alarma == 0 )
  {
    counter--;
    if ( analogRead(avans) < 500 && x > 0 && manual == 'm' )
    {
      counter = e2_agitare * 4;
    }
    if ( counter == 0 )
    {
      if ( manual == 'a' )
      {
        digitalWrite(releu9, HIGH);  // Descarcare vas 1
        etapa++;
        counter = e2_agitare * 4 + 1;
      }
      else
      {
        digitalWrite(releu9, HIGH);  // Descarcare vas 1
        lcd.setCursor(0, 1);
        lcd.print("Avans la etapa 2 ?");
      }
    }
    else
    {
      digitalWrite(releu9, LOW);  // Descarcare vas 1
      lcd.setCursor(0, 1);
      if ( alter < 4 )
      {
        lcd.print("1. Asteptare agitare");
      }
      else
      {
        lcd.print("1. Dozare lichid #1");
      }
    }
  } // Final etapa 1

  //                                                                                                      Etapa 2
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  if ( etapa == 2 && alarma == 0 )
  {
    counter--;
    if ( analogRead(avans) < 500 && x > 0 && manual == 'm' )
    {
      counter = e3_omogenizare * 4;
    }
    if ( counter == 0 )
    {
      if ( manual == 'a' )
      {
        digitalWrite(releu9, HIGH);  // Descarcare vas 1
        digitalWrite(releu15, HIGH); // Motor agitare
        etapa++;
        counter = e3_omogenizare * 4 + 1;
      }
      else
      {
        digitalWrite(releu9, HIGH);  // Descarcare vas 1
        digitalWrite(releu15, HIGH); // Motor agitare
        lcd.setCursor(0, 1);
        lcd.print("Avans la etapa 3 ?");
      }
    }
    else
    {
      digitalWrite(releu9, LOW);  // Descarcare vas 1
      digitalWrite(releu15, LOW); // Motor agitare
      lcd.setCursor(0, 1);
      if ( alter < 4 )
      {
        lcd.print("2. Agitare amestec");
      }
      else
      {
        lcd.print("2. Dozare lichid #1");
      }
    }
  } // Final etapa 2

  //                                                                                                      Etapa 3
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  if ( etapa == 3 && alarma == 0 )
  {
    counter--;
    if ( analogRead(avans) < 500 && x > 0 && manual == 'm' )
    {
      counter = e4_solid * 4;
    }
    if ( counter == 0 )
    {
      if ( manual == 'a' )
      {
        digitalWrite(releu15, HIGH); // Motor agitare
        etapa++;
        counter = e4_solid * 4 + 1;
      }
      else
      {
        digitalWrite(releu15, HIGH); // Motor agitare
        lcd.setCursor(0, 1);
        lcd.print("Avans la etapa 4 ?");
      }
    }
    else
    {
      digitalWrite(releu15, LOW); // Motor agitare
      lcd.setCursor(0, 1);
      lcd.print("3. Omogenizare");
    }
  } // Final etapa 3

  //                                                                                                      Etapa 4
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  if ( etapa == 4 && alarma == 0 )
  {
    counter--;
    if ( analogRead(avans) < 500 && x > 0 && manual == 'm' )
    {
      counter = e5_omogenizare * 4;
    }
    if ( counter == 0 )
    {
      if ( manual == 'a' )
      {
        digitalWrite(releu15, HIGH); // Motor agitare
        digitalWrite(releu11, HIGH); // Actionare clapet
        etapa++;
        counter = e5_omogenizare * 4 + 1;
      }
      else
      {
        digitalWrite(releu15, HIGH); // Motor agitare
        digitalWrite(releu11, HIGH); // Actionare clapet
        lcd.setCursor(0, 1);
        lcd.print("Avans la etapa 5 ?");
      }
    }
    else
    {
      digitalWrite(releu15, LOW); // Motor agitare
      digitalWrite(releu11, LOW); // Actionare clapet
      lcd.setCursor(0, 1);
      lcd.print("4. Dozare solid");
    }
  } // Final etapa 4

  //                                                                                                      Etapa 5
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  if ( etapa == 5 && alarma == 0 )
  {
    counter--;
    if ( analogRead(avans) < 500 && x > 0 && manual == 'm' )
    {
      counter = e6_solid * 4;
    }
    if ( counter == 0 )
    {
      if ( manual == 'a' )
      {
        digitalWrite(releu15, HIGH); // Motor agitare
        etapa++;
        counter = e6_solid * 4 + 1;
      }
      else
      {
        digitalWrite(releu15, HIGH); // Motor agitare
        lcd.setCursor(0, 1);
        lcd.print("Avans la etapa 6 ?");
      }
    }
    else
    {
      digitalWrite(releu15, LOW); // Motor agitare
      lcd.setCursor(0, 1);
      lcd.print("5. Omogenizare");
    }
  } // Final etapa 5

  //                                                                                                      Etapa 6
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  if ( etapa == 6 && alarma == 0 )
  {
    counter--;
    if ( analogRead(avans) < 500 && x > 0 && manual == 'm' )
    {
      counter = e7_omogenizare * 4;
    }
    if ( counter == 0 )
    {
      if ( manual == 'a' )
      {
        digitalWrite(releu15, HIGH); // Motor agitare
        digitalWrite(releu11, HIGH); // Actionare clapet
        etapa++;
        counter = e7_omogenizare * 4 + 1;
      }
      else
      {
        digitalWrite(releu15, HIGH); // Motor agitare
        digitalWrite(releu11, HIGH); // Actionare clapet
        lcd.setCursor(0, 1);
        lcd.print("Avans la etapa 7 ?");


      }
    }
    else
    {
      digitalWrite(releu15, LOW); // Motor agitare
      digitalWrite(releu11, LOW); // Actionare clapet
      lcd.setCursor(0, 1);
      lcd.print("6. Dozare solid (2)");
    }
  } // Final etapa 6


  //                                                                                                      Etapa 7
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  if ( etapa == 7 && alarma == 0 )
  {
    counter--;
    if ( analogRead(avans) < 500 && x > 0 && manual == 'm' )
    {
      counter = e8_lichid2 * 4;
    }
    if ( counter == 0 )
    {
      if ( manual == 'a' )
      {
        digitalWrite(releu15, HIGH); // Motor agitare
        etapa++;
        counter = e8_lichid2 * 4 + 1;
      }
      else
      {
        digitalWrite(releu15, HIGH); // Motor agitare
        lcd.setCursor(0, 1);
        lcd.print("Avans la etapa 8 ?");
      }
    }
    else
    {
      digitalWrite(releu15, LOW); // Motor agitare
      lcd.setCursor(0, 1);
      lcd.print("7. Omogenizare");
    }
  } // Final etapa 7

  //                                                                                                      Etapa 8
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  if ( etapa == 8 && alarma == 0 )
  {
    counter--;
    if ( analogRead(avans) < 500 && x > 0 && manual == 'm' )
    {
      counter = e9_omogenizare * 4;
    }
    if ( counter == 0 )
    {
      if ( manual == 'a' )
      {
        digitalWrite(releu15, HIGH); // Motor agitare
        digitalWrite(releu10, HIGH); // Descarcare vas 2
        etapa++;
        counter = e9_omogenizare * 4 + 1;
      }
      else
      {
        digitalWrite(releu15, HIGH); // Motor agitare
        digitalWrite(releu10, HIGH); // Descarcare vas 2
        lcd.setCursor(0, 1);
        lcd.print("Avans la etapa 9 ?");
      }
    }
    else
    {
      digitalWrite(releu15, LOW); // Motor agitare
      digitalWrite(releu10, LOW); // Descarcare vas 2
      lcd.setCursor(0, 1);
      lcd.print("8. Dozare lichid #2");
    }
  } // Final etapa 8

  //                                                                                                      Etapa 9
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  if ( etapa == 9 && alarma == 0 )
  {
    counter--;
    if ( analogRead(avans) < 500 && x > 0 && manual == 'm' )
    {
      counter = e10_stabil * 4;
    }
    if ( counter == 0 )
    {
      if ( manual == 'a' )
      {
        digitalWrite(releu15, HIGH); // Motor agitare
        etapa++;
        counter = e10_stabil * 4 + 1;
      }
      else
      {
        digitalWrite(releu15, HIGH); // Motor agitare
        lcd.setCursor(0, 1);
        lcd.print("Avans la etapa 10 ?");


      }
    }
    else
    {
      digitalWrite(releu15, LOW); // Motor agitare
      lcd.setCursor(0, 1);
      lcd.print("9. Omogenizare");
    }
  } // Final etapa 9


  //                                                                                                      Etapa 10
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  if ( etapa == 10 && alarma == 0 )
  {
    counter--;
    if ( analogRead(avans) < 500 && x > 0 && manual == 'm' )
    {
      counter = e11_evac * 4;
    }
    if ( counter == 0 )
    {
      if ( manual == 'a' )
      {
        digitalWrite(releu15, HIGH); // Motor agitare
        digitalWrite(releu9, HIGH);  // Descarcare vas 1
        digitalWrite(releu10, HIGH); // Descarcare vas 2
        digitalWrite(releu11, HIGH); // Actionare clapet
        etapa++;
        counter = e11_evac * 4 + 1;
      }
      else
      {
        digitalWrite(releu15, HIGH); // Motor agitare
        digitalWrite(releu9, HIGH);  // Descarcare vas 1
        digitalWrite(releu10, HIGH); // Descarcare vas 2
        digitalWrite(releu11, HIGH); // Actionare clapet
        lcd.setCursor(0, 1);
        lcd.print("Avans la etapa 11 ?");

      }
    }
    else
    {
      lcd.setCursor(0, 1);
      lcd.print("10. Stabil. amestec");
    }
  } // Final etapa 10

  //                                                                                                      Etapa 11
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  if ( etapa == 11 && alarma == 0 )
  {
    counter--;
    if ( analogRead(avans) < 500 && x > 0 && manual == 'm' )
    {
      counter = e12_wait * 4;
    }
    if ( counter == 0 )
    {
      if ( manual == 'a' )
      {
        digitalWrite(releu12, HIGH); // Actionare valva descarcare
        etapa++;
        counter = e12_wait * 4 + 1;
      }
      else
      {
        digitalWrite(releu12, HIGH); // Actionare valva descarcare
        etapa = 0;
        counter = 0;
      }
    }
    else
    {
      digitalWrite(releu12, LOW); // Actionare valva descarcare
      lcd.setCursor(0, 1);
      lcd.print("11. Evacuare amestec");
    }
  } // Final etapa 11

  //                                                                                                      Etapa 12
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  if ( etapa == 12 && alarma == 0 )
  {
    lcd.setCursor(0, 1);
    lcd.print("12. Timp intre sarje");

    counter--;

    if ( counter == 0 )
    {
      if ( manual == 'a' )
      {
        digitalWrite(releu15, HIGH); // Motor agitare
        digitalWrite(releu9, HIGH);  // Descarcare vas 1
        digitalWrite(releu10, HIGH); // Descarcare vas 2
        digitalWrite(releu11, HIGH); // Actionare clapet
        digitalWrite(releu12, HIGH); // Actionare valva descarcare
        etapa = 1;
        counter = e1_asteptare * 4 + 1;
      }
    }

  } // Final etapa 12



  //  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  //  Indici principali de afisat
  //

  timer = counter / 4;

  lcd.setCursor(0, 0);
  if ( manual == 'm' )
  {
    lcd.print("Mod: Manual");
    digitalWrite(releu3, HIGH);  // Bec buton start

    if (alter < 4)
    {
      digitalWrite(releu4, LOW);  // Bec buton auto / man
    }
    else
    {
      digitalWrite(releu4, HIGH);  // Bec buton auto / man
    }

    if ( alter < 6 && timer < 1 )
    {
      digitalWrite(releu5, LOW);
    }
    else
    {
      digitalWrite(releu5, HIGH);
    }

    if ( analogRead(avans) < 500 && x > 0 && alarma == 0 )
    {
      etapa++;
      if ( etapa == 12 )
      {
        etapa = 0;
      }
      digitalWrite(releu3, HIGH);  // Bec buton start
      digitalWrite(releu5, HIGH);  // Bec buton avans
      digitalWrite(releu9, HIGH);  // Descarcare vas 1
      digitalWrite(releu10, HIGH); // Descarcare vas 2
      digitalWrite(releu11, HIGH); // Actionare clapet
      digitalWrite(releu12, HIGH); // Actionare valva descarcare
      digitalWrite(releu15, HIGH); // Motor agitare
    }

  }
  else
  {
    lcd.print("Mod: AUTO");
    digitalWrite(releu4, HIGH);  // Bec buton auto / man
    digitalWrite(releu5, HIGH);  // Bec buton avans
    if ( etapa == 13 )
    {
      etapa = 1;
    }
  }

  //                                                                                        Compresor !!!
  //  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  //
  //
  if ( analogRead(compresor) > 500 )
  {
    digitalWrite(releu16, HIGH); // Compresor aer instrumental
  }
  else
  {
    digitalWrite(releu16, LOW); // Compresor aer instrumental
  }

  //                                                                                        Diverse
  //  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  //
  //
  if ( alarma == 1 )
  {
    lcd.setCursor(0, 1);
    lcd.print("Rezolvati alarmele !");
  }



  // Temporizare buton

  if (analogRead(avans) > 500)
  {
    x = 20;
  }
  else
  {
    if ( x = 0 )
    {
      x = 1;
    }
    x--;
  }

  // Afisarea pe ecran a timpului ramas din etapa

  lcd.setCursor(15, 0);
  lcd.print("-> ");
  lcd.print(timer, 0);
  if ( timp != -1 )
  {
    if ( timp >= 60 )
    {
      minute++;
      timp = 0;
    }
    timp = timp + 0.25;
    lcd.setCursor(13, 3);
    lcd.print(minute);
    lcd.print("'");
    lcd.print(timp, 0);
    lcd.print("''");
  }

  if ( timp == 240 )
  {
    minute++;
    timp = 0;
  }

  // Contoare

  serv1--;
  if ( serv1 == 0 )
  {
    digitalWrite(releu9, HIGH);  // Descarcare vas 1
    serv1 = -1;
  }
  serv2--;
  if ( serv2 == 0 )
  {
    digitalWrite(releu10, HIGH);  // Descarcare vas 2
    serv2 = -1;
  }
  servvalva--;
  if ( servvalva == 0 )
  {
    digitalWrite(releu12, HIGH); // Actionare valva descarcare
    pozitie = 0;
    servvalva = -1 ;
  }
  servclapet--;
  if ( servclapet == 0 )
  {
    digitalWrite(releu11, HIGH); // Actionare clapet
    servclapet = -1 ;
  }


  if ( counter == 0 )
  {
    counter = 1;
  }

  j++;
  if ( j > n )
  {
    j = 1;
  }
  n = 0;

  alter++;
  if (alter == 8)
  {
    alter = 0;
  }

  if ( resetfunction > 20 )
  {
    lcd.clear();
    delay(1000);
    resetFunc();
  }
  delay(250);
} // final void loop
