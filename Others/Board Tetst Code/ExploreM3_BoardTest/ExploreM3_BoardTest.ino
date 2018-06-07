
#include "RTC.h"

RTC my_rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};



char option;
int max = 41, i, j;

void gpio_Test();
void adc_test();
void rtc_test();


int key()
{
  if (digitalRead(41)== 1)
    return 1;
  else
  {
    while (digitalRead(41) == 0);
    return 0;
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(41, INPUT);
  while (key());
  Serial.println(' ');
  Serial.println(' ');
  Serial.println("------------------------------------");
  Serial.println(F("Testing Explore Arduino"));
  Serial.println(F("Press-->1 for GPIO Test"));
  Serial.println(F("Press-->2 for Serial Test"));
  Serial.println(F("Press-->3 for ADC Test"));
  Serial.println(F("Press-->4 for RTC Test"));
  Serial.println(F("Select One of the above options"));
  Serial.println("------------------------------------");
  Serial.println(' ');
  option = '1';
}

void loop()
{
  switch (option)
  {
    case '1': gpio_Test(); break;
    case '2': serial_test(); break;
    case '3': adc_test(); break;
    case '4': rtc_test(); break;

  }
  option++;
  if (option > '5')
  option = '1';
}

void gpio_Test()
{
  for (i = 0; i < max; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }

  int keyPress = key();
  while (keyPress)
  {

    for (i = 0; ((i < max) && keyPress); i++)
    {
      keyPress = key();
      digitalWrite(i, LOW);
      delay(100);
      digitalWrite(i, HIGH);
      delay(100);
    }
  }
}


void serial_test()
{
  Serial.println(F("DO the serial connection M3-Tx pins 1,3,5,7 to Cp2102 Rx pins"));
  Serial.println(F("Make connections and hit 'k' to test "));

  Serial0.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);

  while (key())
  {
    Serial0.println("Serial port Zero");
    Serial1.println("Serial port One");
    Serial2.println("Serial port Two");
    Serial3.println("Serial port Three");
  }
}




void adc_test()
{
  int sensorValue;

  Serial.println(F("Connect Temp Sensor to A0, POT->A1 and LDR->A2"));

  while (key())
  {
    sensorValue = analogRead(A0);
    Serial.print("Temp Sensor = " );
    Serial.print(sensorValue);

    sensorValue = analogRead(A1);
    Serial.print("  POT = " );
    Serial.print(sensorValue);

    sensorValue = analogRead(A2);
    Serial.print("  LDR = " );
    Serial.println(sensorValue);
    delay(500);
  }
}


void rtc_test()
{
  my_rtc.begin();

  if (! my_rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    my_rtc.adjust(DateTime((__DATE__), (__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // my_rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  while (key())
  {

    DateTime now = my_rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");

    // calculate a date which is 7 days and 30 seconds into the future
    DateTime future (now + TimeSpan(7, 12, 30, 6));

    Serial.print(" now + 7d + 30s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();

    Serial.println();
    delay(1000);

  }
}


