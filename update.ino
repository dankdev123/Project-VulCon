 /*Project VulCon
 added gyro 
 added ldr
 */
 
 
 #include "Wire.h"
 #include <MPU6050_light.h>
 MPU6050 mpu(Wire);
 const int buzzr = 9;
 int tilt;

  int ldr = A0;
  int hdl1 = 7;
  int hdl2 = 6;
  double lux;



 unsigned long timer = 0;
 void setup() {
  
  pinMode(hdl1, OUTPUT);
  pinMode(hdl2, OUTPUT); 
   Serial.begin(9600);
   Wire.begin();
 byte status = mpu.begin();
   Serial.print(F("MPU6050 status: "));
   Serial.println(status);
   while (status != 0) { } 
 Serial.println(F("Calculating offsets, do not move MPU6050"));
   delay(1000);
   mpu.calcOffsets();
   Serial.println("Done!\n");

  
   pinMode(hdl1, OUTPUT);
   pinMode(hdl2, OUTPUT); 
 }
 void loop() {
   tilt = mpu.getAngleY();
   
   mpu.update();
 if ((millis() - timer) > 10) {
     Serial.print("X : ");
     Serial.print(mpu.getAngleX());
     Serial.print("\tY : ");
     Serial.print(mpu.getAngleY());
     Serial.print("\tZ : ");
     Serial.println(mpu.getAngleZ());
     timer = millis();
   }
   if( tilt > 25){
    tone(buzzr, 5);
    delay(100);
    noTone(buzzr);
    delay(100);
  }
    if( tilt < -25){
      tone(buzzr, 5);
      delay(100);
      noTone(buzzr);
      delay(100);
    }

  int data = analogRead(ldr);

  Serial.println("");
  Serial.print("Light Sensor ");
  Serial.print("Value ");
  Serial.print("/t");
  Serial.print(data);

  if (data <= 400) {
  digitalWrite(hdl1, HIGH);
  digitalWrite(hdl2, HIGH);
  } else {
  digitalWrite(hdl1, LOW);
  digitalWrite(hdl2, LOW);
  }

      
 

    


 }
