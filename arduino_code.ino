#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include <WiFiS3.h>
#include <WiFiClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define ONE_WIRE_BUS 2 //กำหนดว่าขาของเซนเซอร์ 18B20 ต่อกับขา 2

const char* ssid = "YuuuuuY";      // Your SSID
const char* password = "0814822764";  // Your Password

const int trigPin = 10;
const int echoPin = 11;
long duration;
int distanceCm, distanceInch;
int temp = 0, distance = 0;
bool isOpen = false;
String currentTime;
String timeValue = "00:00";

String setvaluesHTML(double temp_, int food){
  String tempStatus,emo;
    if (temp_ < 24) {
      emo = "❄️ o(╥﹏╥)o ❄️";
      tempStatus = "Water temperature too cool. ❄️!!!";
    } else if (temp_ > 28) {
        emo = "🔥 o(╥﹏╥)o 🔥";
        tempStatus = "Water temperature too hot. 🔥!!!";
    } else {
        emo = "🎉 (≧▽≦) 🎉";
        tempStatus = "Water temperature is good. :D";
    }
    String foodStatus;
      if (food < 30) {
          foodStatus = "The food level is low. Please refill.";
      } else {
          foodStatus = "The food level was good :D";
      }
  String html = "";
  html += "        opacity: 0.8;\n";
  html += "        margin-top: 1.5%;\n";
  html += "        margin-left: auto;\n";
  html += "        margin-right: 5%;\n";
  html += "        right: 0;\n";
  html += "        box-shadow: 2px 4px 8px 2px rgb(255, 255, 255);\n";
  html += "    }\n";
  html += "    .food p{\n";
  html += "        font-size: 3vh;\n";
  html += "        text-align: center;\n";
  html += "        color: rgb(54, 130, 206);\n";
  html += "    }\n";
  html += "    .food .amount{\n";
  html += "        font-size: 7vh;\n";
  html += "        text-align: center;\n";
  html += "        color: rgb(54, 130, 206);\n";
  html += "    }\n";
  html += "</style>\n";
  html += "</head>\n";
  html += "<body>\n";
  html += "    <div class=\"auto\">\n";
  html += "        <div class=\"text\"><label for=\"text\">Auto-Fishcare</label></div>\n";
  html += "    </div>\n";
  html += "    <div class=\"tem\"><p>Temperature-Now</p><p class=\"tempo\">"+String(temp_)+"°C</p></div>\n";
  html += "    <div class=\"emoji\"><div class=\"sta\"><p>Status</p></div><div class=\"emo\"><p>"+emo+"</p></div></div>\n";
  html += "    <div class=\"noti\"><div class=\"not\"><label for=\"text\">Notification</label></div><div class=\"sentnoti\"><p>"+tempStatus+"</p></div><div class=\"sentnoti\"><p>"+foodStatus+"</p></div></div>\n";
  html += "    <div class=\"timer\"><div class=\"feeder\"><p>Set timer/Feeder</p></div><div class=\"box\"><form action=\"/submit\" method=\"POST\"><div><p>Set time</p></div><div class=\"input-box\"><input type=\"time\" id=\"timeInput\" name=\"timeInput\" required></div><div class=\"but2\"><button type=\"submit\">Submit</button></div></form></div><form action=\"/feed\" method=\"POST\"><div class=\"but\"><button>Feed now</button></div></form></div>\n";
  html += "    <div class=\"food\"><p>Amount of food</p><p class=\"amount\">"+String(food)+" %</p></div>\n";
  html += "</body>\n";
  html += "</html>";
  return html;
}
String generateHTML() {
  String html = "<!DOCTYPE html>\n";
  html += "<html lang=\"en\">\n";
  html += "<head>\n";
  html += "    <meta charset=\"UTF-8\">\n";
  html += "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
  html += "    <title>pc</title>\n";
  html += "<style>\n";
  html += "    *{\n";
  html += "        margin: 0;\n";
  html += "        padding: 0;\n";
  html += "        box-sizing: border-box;\n";
  html += "        font-family: \"Itim\", cursive;\n";
  html += "        font-weight: 400;\n";
  html += "        font-style: normal;\n";
  html += "    }\n";
  html += "    body{\n";
  html += "        background: rgb(2,0,36);\n";
  html += "        background: radial-gradient(circle, rgba(2,0,36,1) 0%, rgb(255, 243, 222) 0%, rgb(118, 191, 231) 100%);\n";
  html += "    }\n";
  html += "    .auto{\n";
  html += "        position: relative;\n";
  html += "        width: 100%;\n";
  html += "        height: 200px;\n";
  html += "        padding: 25px;\n";
  html += "        margin-left: auto;\n";
  html += "        margin-right: auto;\n";
  html += "        border-radius: 35px;\n";
  html += "        background-color: aliceblue;\n";
  html += "        margin-top: 3%;\n";
  html += "        justify-content: center;\n";
  html += "        max-width: 90%;\n";
  html += "        box-shadow: 2px 4px 8px 2px rgba(255, 255, 255, 0.64), 0 6px 20px 0 rgba(255, 255, 255, 0.346);\n";
  html += "    }\n";
  html += "    .text{\n";
  html += "        font-size: 15vh;\n";
  html += "        text-align: center;\n";
  html += "        color: rgb(54, 130, 206);\n";
  html += "    }\n";
  html += "    .not{\n";
  html += "        font-size: 4vh;\n";
  html += "        text-align: center;\n";
  html += "        color: rgb(54, 130, 206);\n";
  html += "    }\n";
  html += "    .tem{\n";
  html += "        position: relative;\n";
  html += "        width: 100%;\n";
  html += "        height: 230px;\n";
  html += "        padding: 25px;\n";
  html += "        margin-left: 5%;\n";
  html += "        border-radius: 35px;\n";
  html += "        background-color: #ffffff;\n";
  html += "        margin-top: 2%;\n";
  html += "        max-width: 20%;\n";
  html += "        opacity: 0.8;\n";
  html += "        box-shadow: 2px 4px 8px 2px rgb(255, 255, 255);\n";
  html += "    }\n";
  html += "    .tem p{\n";
  html += "        font-size: 3vh;\n";
  html += "        text-align: center;\n";
  html += "        color: rgb(54, 130, 206);\n";
  html += "    }\n";
  html += "    .tem .tempo{\n";
  html += "        font-size: 9vh;\n";
  html += "        text-align: center;\n";
  html += "        color: rgb(54, 130, 206);\n";
  html += "        margin-top: 20px;\n";
  html += "    }\n";
  html += "    .emoji{\n";
  html += "        position: relative;\n";
  html += "        width: 100%;\n";
  html += "        height: 230px;\n";
  html += "        padding: 25px;\n";
  html += "        margin-top: -20px;\n";
  html += "        margin-left: 5%;\n";
  html += "        border-radius: 35px;\n";
  html += "        background-color: #ffffff;\n";
  html += "        margin-top: 2%;\n";
  html += "        max-width: 20%;\n";
  html += "        opacity: 0.8;\n";
  html += "        align-items: center;\n";
  html += "        box-shadow: 2px 4px 8px 2px rgb(255, 255, 255);\n";
  html += "    }\n";
  html += "    .emoji .emo{\n";
  html += "        font-size: 4vh;\n";
  html += "        margin-top: 15%;\n";
  html += "        text-align: center;\n";
  html += "        justify-items: center;\n";
  html += "        color: rgb(54, 130, 206);\n";
  html += "    }\n";
  html += "    .emoji .sta{\n";
  html += "        font-size: 3vh;\n";
  html += "        text-align: center;\n";
  html += "        justify-items: center;\n";
  html += "        color: rgb(54, 130, 206);\n";
  html += "    }\n";
  html += "    .noti{\n";
  html += "        position: relative;\n";
  html += "        width: 30%;\n";
  html += "        height: 300px;\n";
  html += "        padding: 25px;\n";
  html += "        border-radius: 35px;\n";
  html += "        background-color: #ffffff;\n";
  html += "        opacity: 0.8;\n";
  html += "        margin-top: -490px;\n";
  html += "        margin-left: auto;\n";
  html += "        margin-right: 5%;\n";
  html += "        right: 0;\n";
  html += "        overflow: scroll;\n";
  html += "        overflow-y: auto;\n";
  html += "        overflow-x: auto;\n";
  html += "        box-shadow: 2px 4px 8px 2px rgb(255, 255, 255);\n";
  html += "    }\n";
  html += "    .sentnoti{\n";
  html += "        position: relative;\n";
  html += "        margin-top: 5%;\n";
  html += "        width: 90%;\n";
  html += "        height: 70px;\n";
  html += "        padding: 25px;\n";
  html += "        border-radius: 25px;\n";
  html += "        background-color: #9fd2f4;\n";
  html += "        align-items: center;\n";
  html += "        margin-left: auto;\n";
  html += "        margin-right: auto;\n";
  html += "    }\n";
  html += "    .timer{\n";
  html += "        position: absolute;\n";
  html += "        width: 35%;\n";
  html += "        height: 490px;\n";
  html += "        padding: 25px;\n";
  html += "        border-radius: 35px;\n";
  html += "        background-color: #ffffff;\n";
  html += "        opacity: 0.8;\n";
  html += "        margin-top: -300px;\n";
  html += "        left: 27.5%;\n";
  html += "        box-shadow: 2px 4px 8px 2px rgb(255, 255, 255);\n";
  html += "    }\n";
  html += "    .feeder{\n";
  html += "        font-size: 4vh;\n";
  html += "        color: rgb(54, 130, 206);\n";
  html += "        margin-left: 4%;\n";
  html += "    }\n";
  html += "    .box{\n";
  html += "        position: relative;\n";
  html += "        margin-top: 3%;\n";
  html += "        width: 90%;\n";
  html += "        height: 250px;\n";
  html += "        padding: 25px;\n";
  html += "        border-radius: 25px;\n";
  html += "        background-color: #9fd2f4;\n";
  html += "        align-items: center;\n";
  html += "        margin-left: auto;\n";
  html += "        margin-right: auto;\n";
  html += "    }\n";
  html += "    .but{\n";
  html += "        display: flex;\n";
  html += "        justify-content: center;\n";
  html += "        align-items: center;\n";
  html += "        margin-top: 10px;\n";
  html += "    }\n";
  html += "    .but button{\n";
  html += "        height: 6.5vh;\n";
  html += "        width: 60%;\n";
  html += "        color: #ffffff;\n";
  html += "        font-size: 3vh;\n";
  html += "        font-weight: 400;\n";
  html += "        margin-top: 30px;\n";
  html += "        border: none;\n";
  html += "        border-radius: 2vh;\n";
  html += "        background-color: #ecb5df;\n";
  html += "        cursor: pointer;\n";
  html += "        transition: all 0.2s ease;\n";
  html += "    }\n";
  html += "    .but button:hover{\n";
  html += "        background-color: #b3d5fa;\n";
  html += "    }\n";
  html += "    .input-box input{\n";
  html += "        position: relative;\n";
  html += "        height: 6vh;\n";
  html += "        width: 80%;\n";
  html += "        outline: none;\n";
  html += "        font-size: 2vh;\n";
  html += "        color: #5ab7f5;\n";
  html += "        margin-top: 20px;\n";
  html += "        margin-left: 32px;\n";
  html += "        border: none;\n";
  html += "        border-radius: 7px;\n";
  html += "        padding: 0 15px;\n";
  html += "    }\n";
  html += "    .box p{\n";
  html += "        font-size: 3vh;\n";
  html += "        text-align: center;\n";
  html += "        color: rgb(54, 130, 206);\n";
  html += "    }\n";
  html += "    .but2{\n";
  html += "        display: flex;\n";
  html += "        justify-content: center;\n";
  html += "        align-items: center;\n";
  html += "        margin-top: 10px;\n";
  html += "    }\n";
  html += "    .but2 button{\n";
  html += "        height: 5vh;\n";
  html += "        width: 40%;\n";
  html += "        color: #ffffff;\n";
  html += "        font-size: 2vh;\n";
  html += "        font-weight: 400;\n";
  html += "        margin-top: 30px;\n";
  html += "        border: none;\n";
  html += "        border-radius: 1vh;\n";
  html += "        background-color: #6fbcff;\n";
  html += "        cursor: pointer;\n";
  html += "        transition: all 0.2s ease;\n";
  html += "    }\n";
  html += "    .but2 button:hover{\n";
  html += "        background-color: #f7d8fc;\n";
  html += "    }\n";
  html += "    .food{\n";
  html += "        position: absolute;\n";
  html += "        width: 30%;\n";
  html += "        height: 165px;\n";
  html += "        padding: 25px;\n";
  html += "        border-radius: 35px;\n";
  html += "        background-color: #ffffff;\n";
  return html;
}
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Servo myServo;
WiFiServer server(80);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 25200, 60000);

void setup(){
  Serial.begin(9600); // Initialize serial communication at 9600 bits per second
  sensors.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(9);  // Attach the servo to pin = 9

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  server.begin(); // Start the server
}

int getTemp() {
  sensors.requestTemperatures(); //สั่งอ่านค่าอุณหภูมิ
  return sensors.getTempCByIndex(0); // แสดงค่าอุณหภูมิ
}

int getDistance() {
  // clear trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
    
  // Read the echoPin, return the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm and inches
  distanceCm = duration * 0.034 / 2;
  distanceInch = duration * 0.0133 / 2;
  distanceCm = -6.25 * distanceCm + 100;

  return distanceCm;
}

void openServo() {
  myServo.write(70);
}

void closeServo() {
  myServo.write(100);
}

void runWebServer(double temp, double distance) {
  Serial.println(WiFi.localIP());
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client) {
    Serial.println("New Client Connected.");
    String request = client.readStringUntil('\r'); // Read the request
    Serial.println(request);
    client.flush();
    String requestBody = "";
        while (client.available()) {
            requestBody += client.readString(); // อ่านข้อมูลที่เหลือจาก client
        }
    Serial.println("Request Body:");
    Serial.println(requestBody);
    if (request.indexOf("POST /submit") >= 0) {
        timeValue = getPostParameter(requestBody, "timeInput");
        Serial.println("Received time: " + timeValue);
    } else if (request.indexOf("POST /feed") >= 0){
      if (true){
        openServo();
        delay(700);
        closeServo();
      }
        Serial.println("feed");
    }
    // Send a response to the client
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    // Serial.println(generateHTML(40, 10));
    client.print(generateHTML());
    client.print(setvaluesHTML(temp, distance));

    delay(1);
    client.stop(); // Close the connection
    Serial.println("Client Disconnected.");
  }
}

String getPostParameter(String request, String parameter) {
    int startIndex = request.indexOf(parameter + "=");
    if (startIndex == -1) return "";

    startIndex += parameter.length() + 1; // ข้ามชื่อ parameter และ "="

    int endIndex = request.indexOf("&", startIndex);
    if (endIndex == -1) endIndex = request.length(); // หากไม่มี "&" ให้ใช้ถึงท้าย
    String timeString = request.substring(startIndex, endIndex);
    timeString.replace("%3A", ":");
    return timeString; // คืนค่าที่ได้
}

bool checkTime() {
  timeClient.update();
  currentTime = timeClient.getFormattedTime();
  String currentHour = currentTime.substring(0, 5);
  int currentSec = currentTime.substring(6, 8).toInt();
  Serial.println(String(currentTime) + ", " + String(timeValue));
  if ((currentHour == timeValue) && (currentSec < 3)){
    openServo();
    delay(700);
    closeServo();
  }
}

void loop() {
  temp = getTemp();
  distance = getDistance();
  runWebServer(temp, distance);
  checkTime();
  
  delay(1000);
}