#include <Arduino.h>
#include <M5StickC.h>
#include "sensor/accel.h"
#include "sensor/gyro.h"
#include "sensor/mag.h"
#include <MadgwickAHRS.h>

Madgwick filter;

Sensor *acc = new AccelSensor();
Sensor *gyro = new GyroSensor();
Sensor *mag = new MagSensor();

unsigned long lastUpdate = millis();
float ax,ay,az,gx,gy,gz,mx,my,mz;

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);

  // センサー初期化
  acc->init();
  gyro->init();
  mag->init();

  // 加速度センサーキャリブレーション
  M5.Lcd.println("calibration acc");
  while(!acc->calibrate()) { delay(2); }

  // 角速度センサーキャリブレーション
  M5.Lcd.println("calibration gyro");
  while(!gyro->calibrate()) { delay(2); }
  
  // 地磁気センサーキャリブレーション
  M5.Lcd.println("calibration mag");
  while(!mag->calibrate()) { delay(2); }

  filter.begin(200);
}

void loop() {

  acc->read(&ax, &ay, &az);
  gyro->read(&gx, &gy, &gz);
  mag->read(&mx, &my, &mz);

  // フィルタアップデート
  filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);
  // 磁気センサを使わない場合
  // filter.updateIMU(gx, gy, gz, ax, ay, az);

  M5.Lcd.setCursor(0,40);
  M5.Lcd.printf("roll %6.2f \npitch %6.2f \nyaw %6.2f", filter.getRoll(), filter.getPitch(), filter.getYaw());

  if(millis() - lastUpdate < 5)
    delay(5 - (millis() - lastUpdate));
  lastUpdate = millis();
}