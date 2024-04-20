#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

#define DuzinaLozinke 5
#define ZvucnikPin 12 // Promijenjen pin za zvučnik

Servo myservo;
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

int pozicija = 0;

char Podaci[DuzinaLozinke];
char GlavnaLozinka[DuzinaLozinke] = "0409";
byte brojPodataka = 0, brojGlavne = 0;

bool LozinkaJeIspravna;
bool vrata = false;
char pritisnutoDugme;

const byte REDOVI = 4;
const byte KOLONI = 4;
char tastature[REDOVI][KOLONI] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pinoviRedova[REDOVI] = {0, 1, 2, 3};
byte pinoviKolona[KOLONI] = {4, 5, 6, 7};

Keypad customKeypad( makeKeymap(tastature), pinoviRedova, pinoviKolona, REDOVI, KOLONI);

// Tonovi alarma
int melody[] = {
  262, 196, 196, 220, 196, 0, 247, 262
};
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup()
{
  myservo.attach(9, 2000, 2400);
  ZatvoriServo();
  lcd.begin(16, 2);
  lcd.print("Zasticena Vrata");
  ucitavanje("Ucitavanje");
  lcd.clear();
}

void loop()
{
  if (vrata == true)
  {
    pritisnutoDugme = customKeypad.getKey();
    if (pritisnutoDugme == '#')
    {
      lcd.clear();
      ZatvoriServo();
      lcd.print("Vrata su zatvorena");
      delay(3000);
      vrata = false;
    }
  }
  else
    Otvori();

}

void ucitavanje (char msg[]) {
  lcd.setCursor(0, 1);
  lcd.print(msg);

  for (int i = 0; i < 9; i++) {
    delay(1000);
    lcd.print(".");
  }
}

void ocistiPodatke()
{
  while (brojPodataka != 0)
  { 
    Podaci[brojPodataka--] = 0;
  }
  return;
}

void ZatvoriServo()
{
  for (pozicija = 90; pozicija >= 0; pozicija -= 10) { 
    myservo.write(pozicija);
  }
}

void OtvoriServo()
{
  for (pozicija = 0; pozicija <= 90; pozicija += 10) {
    myservo.write(pozicija);  
  }
}

void Otvori()
{
  lcd.setCursor(0, 0);
  lcd.print("Unesite sifru :");
  
  pritisnutoDugme = customKeypad.getKey();
  if (pritisnutoDugme)
  {
    Podaci[brojPodataka] = pritisnutoDugme;
    lcd.setCursor(brojPodataka, 1);
    lcd.print(Podaci[brojPodataka]);
    brojPodataka++;
  }

  if (brojPodataka == DuzinaLozinke - 1)
  {
    if (!strcmp(Podaci, GlavnaLozinka))
    {
      lcd.clear();
      OtvoriServo();
      lcd.print(" Otvoreno ");
      vrata = true;
      delay(2000);
      ucitavanje("Cekanje");
      lcd.clear();
      lcd.print(" Zatvaranje vrata ");
      delay(1000);
      ZatvoriServo();
      vrata = false;      
    }
    else
    {
      lcd.clear();
      lcd.print(" GRESKA ");
      reproducirajAlarm(); // Poziv funkcije za reprodukciju alarma
      vrata = false;
    }
    delay(1000);
    lcd.clear();
    ocistiPodatke();
  }
}

// Funkcija za reprodukciju alarma
void reproducirajAlarm() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(ZvucnikPin, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(ZvucnikPin);
  }
}
