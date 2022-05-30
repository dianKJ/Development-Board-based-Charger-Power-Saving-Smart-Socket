#include "EmonLib.h"
EnergyMonitor emon1;
long mili;
double sampleI;
double offsetI;
double filteredI;
char str[90];
double I;
double sum = 0 ;


void setup()
{
  Serial.begin(9600);

  emon1.current(1, 111.1);
  offsetI = ADC_COUNTS;

  mili = millis();
  pinMode(A0, INPUT);
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  //  delay(5000);
}

void loop()
{


  for (int i = 0; i < 1000; i++) {
    sampleI = analogRead(A0);

    offsetI = (offsetI + (sampleI - offsetI) / 1024);//filter low pass digital
    filteredI = sampleI - offsetI;
//    if (filteredI < 0)filteredI == 0;
    I = filteredI * filteredI;
    sum += I;   // ovf
  }
  double O = sqrt(I / 1000);

  if (O > 10000) {
    O = 10000;
  }
  else if (O < 0) O = O * (-1);

  Serial.print(sum);
  Serial.print("   ");
  Serial.println(O);

  //  sprintf(str, "%d", O );
  //  Serial.println(str);


  //  if (O <= 1) {
  //
  //    digitalWrite(5, LOW);
  //  } else if (O > 1)digitalWrite(5, HIGH);



}
