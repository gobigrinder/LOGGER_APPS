#include <OneWire.h>
#include <DallasTemperature.h>

#define PROBES_PER_RELAY 2
#define NUM_PROBES 12
#define NUM_RELAYS 6

OneWire gp1(26);
DallasTemperature dt1(&gp1);

OneWire gp2(27);
DallasTemperature dt2(&gp2);

OneWire gp3(28);
DallasTemperature dt3(&gp3);

OneWire gp4(29);
DallasTemperature dt4(&gp4);

OneWire gp5(30);
DallasTemperature dt5(&gp5);

OneWire gp6(31);
DallasTemperature dt6(&gp6);

DallasTemperature sensors[6] = { dt1, dt2, dt3, dt4, dt5, dt6 };
int relays[6] = { 38, 39, 40, 41, 42, 43 };

void setup() {
  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  Serial.begin(9600);

  for (int i = 0; i < 6; i++) {
    pinMode(relays[i], OUTPUT);
    digitalWrite(relays[i], HIGH);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  int pIndex = 0;
  String temps = "";
  
  for (int i = 0; i < 6; ++i) {
    // start relay
    digitalWrite(relays[i], LOW);
    delay(1000);

    // ===============
    sensors[i].begin();
    delay(1000);
    sensors[i].requestTemperatures();
    delay(1000);

    for (int p = 0; p < 2; p++) {
      double t = sensors[i].getTempCByIndex(p);
      temps += String(t, 1);
      
      if (pIndex != 11) {
        temps += ",";
      }

      ++pIndex;
    }
    delay(500);
    // Shutdown relay
    digitalWrite(relays[i], HIGH);
  }

  Serial.println(temps);

  delay(5000);
}
