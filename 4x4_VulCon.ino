/*
Project VulCon
*/

#include <Wire.h>
const int MPU = 0x68; 
float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float accAngleX, accAngleY, accAngleZ, gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
float AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
float elapsedTime, currentTime, previousTime;
const int buzzr = 9;


void setup() {
  Serial.begin(19200);
  Wire.begin();                      
  Wire.beginTransmission(MPU);      
  Wire.write(0x6B);                  
  Wire.write(0x00);                  
  Wire.endTransmission(true); 
  
  pinMode(LEDP, OUTPUT);
  pinMode(buzzr, OUTPUT);
  
  
  
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);                  
  Wire.write(0x10);                  
  Wire.endTransmission(true);
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);                   
  Wire.write(0x10);                  
  Wire.endTransmission(true);
  delay(20);

  
}
void loop() {
  
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); 
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); 
  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0;
  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; 
  AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; 

  accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - 0.58; 
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) + 1.58; 
  previousTime = currentTime;        
  currentTime = millis();            
  elapsedTime = (currentTime - previousTime) / 1000; 
  Wire.beginTransmission(MPU);
  Wire.write(0x43); 
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); 
  GyroX = (Wire.read() << 8 | Wire.read()) / 131.0; 
  GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;
  
  GyroX = GyroX + 0.56; 
  GyroY = GyroY - 2; 
  GyroZ = GyroZ + 0.79; 
  
  gyroAngleX = gyroAngleX + GyroX * elapsedTime; 
  gyroAngleY = gyroAngleY + GyroY * elapsedTime;
  gyroAngleZ = gyroAngleZ + GyroZ * elapsedTime;
  yaw =  yaw + GyroZ * elapsedTime;
  
  roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
  pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;
 
  
 
  Serial.print(roll);
  Serial.print("/");
  Serial.print(pitch);
  Serial.print("/");
  Serial.println(yaw);
  Serial.println("/");
  Serial.println(GyroZ);
  delay(100);

  if( roll > 25){
    tone(buzzr, 1000);
    delay(100);
    noTone(buzzr);
    delay(100);
  }
}


