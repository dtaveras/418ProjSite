#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

void setup(void) 
{
  uint32_t currentFrequency;
    
  Serial.begin(115200);
  
  //Serial.println("Measuring voltage and current with INA219 ...");
  ina219.begin();
  //Serial.println("starting ..");
}

double prvtime = 0;
void loop(void) 
{
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;

  float now = millis();
  
  float t = 1/(abs(now - prvtime)/1000.0);
  //Serial.println(t);
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  int debug = 0;
  
  if(debug == 0){
      Serial.print(current_mA);Serial.print(",");
  }
  else{
    //Debug Information
    Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
    Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
    Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
    Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
    Serial.println("");
  }
  prvtime = now;
  delay(30);  
}
