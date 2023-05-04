 /*Project VulCon
 added gyro 
 
 */
 
 
 #include "Wire.h"
 #include <MPU6050_light.h>
 MPU6050 mpu(Wire);
 const int buzzr = 9;
 int tilt;
 const int LED1 = 2;
 const int LED2 = 3;



 unsigned long timer = 0;
 void setup() {
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

   pinMode(LED1, OUTPUT);
   pinMode(LED2, OUTPUT);
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

    // Headlights 

    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    delay(50);


 }



