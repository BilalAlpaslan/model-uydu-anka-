#include <helper_3dmath.h>
#include <MPU6050.h>
#include <MPU6050_6Axis_MotionApps20.h>
#include <MPU6050_9Axis_MotionApps41.h>


#include <Wire.h>
 
MPU6050 mpu6050(Wire);
 
long zaman1 = 0;
 
void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}
 
void loop() {
  mpu6050.update();
 
  if(millis() - zaman1 > 1000){ //EĞER ŞU ANKİ ZAMAN-zaman1  1000 DEN BÜYÜKSE 
    
    Serial.println("=======================================================");
    Serial.print("temp : ");Serial.println(mpu6050.getTemp());              //SICAKLIK VERİSİ
    Serial.print("accX : ");Serial.print(mpu6050.getAccX());                //X EKSENİNDE İVME
    Serial.print("\taccY : ");Serial.print(mpu6050.getAccY());              //Y EKSENİNDE İVME 
    Serial.print("\taccZ : ");Serial.println(mpu6050.getAccZ());            //Z EKSENİNDE İVME 
  
    Serial.print("gyroX : ");Serial.print(mpu6050.getGyroX());
    Serial.print("\tgyroY : ");Serial.print(mpu6050.getGyroY());
    Serial.print("\tgyroZ : ");Serial.println(mpu6050.getGyroZ());
  
    Serial.print("accAngleX : ");Serial.print(mpu6050.getAccAngleX());
    Serial.print("\taccAngleY : ");Serial.println(mpu6050.getAccAngleY());
  
    Serial.print("gyroAngleX : ");Serial.print(mpu6050.getGyroAngleX());      // JİROSKOP X EKSENİ
    Serial.print("\tgyroAngleY : ");Serial.print(mpu6050.getGyroAngleY());    // JİROSKOP Y EKSENİ 
    Serial.print("\tgyroAngleZ : ");Serial.println(mpu6050.getGyroAngleZ());  // JİROSKOP Z EKSENİ 
    
    Serial.print("angleX : ");Serial.print(mpu6050.getAngleX());
    Serial.print("\tangleY : ");Serial.print(mpu6050.getAngleY());
    Serial.print("\tangleZ : ");Serial.println(mpu6050.getAngleZ());
    Serial.println("=======================================================\n");
    zaman1 = millis();
    
  }
 
}
