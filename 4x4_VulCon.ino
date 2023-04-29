/* 
Project Vulcon
*/

/*
LOG: 
27.04.23 : headlights
29.04.23 : gyro + buzzer 
*/


#include <Wire.h>

// Values for the Gyro
const int MPU = 0x68;
float AC, AY, AZ;
float GyroX, GyroY, GyroZ;
float AngY, AngX, GyroAngX, GyroAngY, GyroAngZ;
float roll, pitch, yaw;
float ErrorX, ErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
float elpTime, curTime, prevTime
int c = 0;

// Values for buzzer


const int buzzr = 9; 


// Defining Pins for Headlights 
#define light1 12;
#define light2 13;


void setup(){

    // Headlights 
    pinMode(light1, OUTPUT);
    pinMode(light2, OUTPUT);

    //Gyro 
    Serial.begin(19200);
    Wire.begin();
    Wire.beginTransmission(MPU);
    Wire.Write(0x6B);
    Wire.endTransmission(true);
    calculate_IMU_error();
    delay(1000);

    // Buzzer
    pinMode(buzzr, OUTPUT);

    

}

void loop(){
    // Headlights 
     *gpinMode(light1,HIGH); //Always ON
    pinMode(light2,HIGH); 

    //Acceleromter 
    Wire.beginTransmission(MPU);
    Wire.Write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    AC = (Wire.read() << 8 | Wire.read()) / 16384.0;
    AY = (Wire.read() << 8 | Wire.read()) / 16384.0;
    AZ = (Wire.read() << 8 | Wire.read()) / 16384.0;
    AngX = (atan(AY / sqrt(pow(AC, 2) + pow(AZ, 2))) * 180 / PI) - 0.58;
    AngY = (atan(-1 *AC / sqrt(pow(AC, 2) + pow(AZ, 2))) * 180 / PI) + 1.58;

    //Gyro

    prevTime = curTime;
    curTime = millis();
    elpTime = (curTime - prevTime);

    Wire.beginTransmission(MPU);
    Wire.write(Ox43);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    GyroX = (Wire.read() << 8 | Wire.read()) / 131.0;
    GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
    GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;
    GyroX + GyroX + 0.56;
    GyroY + GyroY - 2;
    GyroZ + GyroZ + 0.79;

    GyroAngX = GyroAngX + GyroX * elpTime;
    GyroAngY = GyroAngY + GyroY * elpTime;
    yaw = yaw + GyroZ * elpTime;

    roll = 0.96 * GyroAngX + 0.04 * AngX;
    pitch = 0.96 * GyroAngY + 0.04 * AngY;

    Serial.print(roll);
    Serial.print("/");
    Serial.print(pitch);
    Serial.print("/");
    Serial.print(yaw);

    
    // If operation for tilt

    if (roll = 25 || roll = -25);
    {
        tone(buzzr, 1000);
        delay(1000);
        noTone(buzzr);
        delay(1000);

    }
    

        

}


//function for IMU errors 
void calculate_IMU_error(){
    while (c < 200)
    {
        Wire.beginTransmission(MPU);
        Wire.Write(0x3B);
        Wire.endTransmission(false);
        Wire.requestFrom(MPU, 6, true);
        AC = (Wire.read() << 8 | Wire.read()) / 16384.0;
        AY = (Wire.read() << 8 | Wire.read()) / 16384.0;
        AZ = (Wire.read() << 8 | Wire.read()) / 16384.0;
        AngX = (atan(AY / sqrt(pow(AC, 2) + pow(AZ, 2))) * 180 / PI) - 0.58;
        AngY = (atan(-1 *AC / sqrt(pow(AC, 2) + pow(AZ, 2))) * 180 / PI) + 1.58;
        c++;
    }

    ErrorX = ErrorX / 200;
    ErrorY = ErrorY / 200;
    c = 0;

    while (c < 200)
    {
        Wire.beginTransmission(MPU);
        Wire.write(Ox43);
        Wire.endTransmission(false);
        Wire.requestFrom(MPU, 6, true);
        GyroX = (Wire.read() << 8 | Wire.read());
        GyroY = (Wire.read() << 8 | Wire.read());
        GyroZ = (Wire.read() << 8 | Wire.read());
        GyroErrorX = GyroErrorX + (GyroX / 131.0);
        GyroErrorY = GyroErrorY + (GyroY / 131.0);
        GyroErrorZ = GyroErrorZ + (GyroZ / 131.0);
        c++;
    }
    
    GyroErrorX = GyroErrorX / 200;
    GyroErrorY = GyroErrorY / 200;
    GyroErrorZ = GyroErrorZ / 200;

    Serial.print("ErrorX: ");
    Serial.println(ErrorX);
    Serial.print("ErrorY: ");
    Serial.println(ErrorY);
    Serial.print("GyroX: ");
    Serial.println(GyroErrorX);
    Serial.print("GyroY: ");
    Serial.println(GyroErrorY);
    Serial.print("GyroY: ");
    Serial.println(GyroErrorZ);

}
