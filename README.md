<h1 align="center">Physical Computing Project 2024 - IT KMITL</h1>
<h3 align="center">AutoFishCare :fish::bubbles:</h3>

## บทคัดย่อ
&emsp;โครงงานนี้เป็นการใช้ Microcontroller ในการสร้างโปรแกรมควบคุมระบบต่าง ๆ ที่ใช้ในการดูแลตู้ปลา เนื่องจากปลาต้องการการดูแลอย่างสม่ำเสมอ จึงต้องการทำให้สะดวกต่อการดูแลของผู้เลี้ยงและป้องกันเวลาที่ไม่ว่างให้อาหารปลาหรือลืมให้อาหารปลา ประกอบด้วย ระบบให้อาหารอัตโนมัติ ระบบตรวจสอบปริมาณอาหาร ระบบวัดอุณหภูมิของน้ำพร้อมแจ้งสถานะ โดยทั้งสามระบบนี้สามารถตรวจสอบข้อมูลและตั้งค่าได้ทาง website ซึ่งอาศัยการอ่านค่าที่ได้รับจาก Ultrasonic Sensor และ Temperature Sensor ร่วมกับ Servo

## ฟังก์ชันหลัก
* ระบบให้อาหารอัตโนมัติ
* ระบบตรวจสอบปริมาณอาหาร
* ระบบวัดอุณหภูมิน้ำพร้อมแจ้งสถานะ

## Library ที่ใช้งาน
```c++
#include <OneWire.h>
#include <Servo.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
```

## Website

## Project Demo Video
[![Project Demo Video](https://img.youtube.com/vi/JoBmouosOzM/0.jpg)](https://youtu.be/JoBmouosOzM)

## Poster
![Poster](/poster.png)
## Contributers
* นายปณวัฒน์ ธรรมเจริญ 66070113
* นายสรวิชญ์ กาญจนสันติศักดิ์ 66070199
* นางสาวสรศมน มีภาษี 66070200
* นางสาวอิสรีย์ แม้นถาวรสิริ 66070323
