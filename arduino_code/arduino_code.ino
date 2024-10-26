#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include <WiFiS3.h>
#include <WiFiClient.h>

#define ONE_WIRE_BUS 2 //กำหนดว่าขาของเซนเซอร์ 18B20 ต่อกับขา 2

const char* ssid = "ENDDOWN";      // Your SSID
const char* password = "02122547";  // Your Password

const int trigPin = 9;
const int echoPin = 10;
long duration;
int distanceCm, distanceInch;
int temp = 0, distance = 0;
String generateHTML(double temp_, int food) {
    String html = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>pc</title>
    <style>
        *{
        margin: 0;
        padding: 0;
        box-sizing: border-box;
        font-family: "Itim", cursive;
        font-weight: 400;
        font-style: normal;
    }
    body{
        background: rgb(2,0,36);
        background: radial-gradient(circle, rgba(2,0,36,1) 0%, rgb(255, 243, 222) 0%, rgb(118, 191, 231) 100%);
        /* background: rgb(255,255,255);
    background: radial-gradient(circle, rgba(255,255,255,1) 0%, rgb(161, 208, 255) 81%); */
    }
    .auto{
        position: relative;
        width: 100%;
        height: 200px;
        padding: 25px;
        margin-left: auto;
        margin-right: auto;
        border-radius: 35px;
        background-color: aliceblue;    
        margin-top: 3%;
        justify-content: center;
        max-width: 90%;
        box-shadow: 2px 4px 8px 2px rgba(255, 255, 255, 0.64), 0 6px 20px 0 rgba(255, 255, 255, 0.346);

    }

    .text{
        font-size: 15vh;
        text-align: center;
        color: rgb(54, 130, 206);
    }

    .not{
        /* position: absolute; */
        font-size: 4vh;
        text-align: center;
        color: rgb(54, 130, 206);
    }

    .tem{
        position: relative;
        width: 100%;
        height: 230px;
        padding: 25px;
        /* align-items:  */
        margin-left: 5%;
        border-radius: 35px;
        background-color: #ffffff;
        margin-top: 2%;
        /* justify-content: center; */
        max-width: 20%;
        opacity: 0.8;
        box-shadow: 2px 4px 8px 2px rgb(255, 255, 255);


        p{
            font-size: 3vh;
            text-align: center;
            color: rgb(54, 130, 206);
        }
        .tempo{
            font-size: 9vh;
            text-align: center;
            color: rgb(54, 130, 206);
            margin-top: 20px;
        }
    }

    .emoji{
        position: relative;
        width: 100%;
        height: 230px;
        padding: 25px;
        margin-top: -20px;
        margin-left: 5%;
        border-radius: 35px;
        background-color: #ffffff;
        margin-top: 2%;
        max-width: 20%;
        opacity: 0.8;
        align-items: center;
        box-shadow: 2px 4px 8px 2px rgb(255, 255, 255);

    }
    .emo{
        font-size: 4vh;
        margin-top: 15%;
        text-align: center;
        justify-items: center;
        color: rgb(54, 130, 206);
    }
    .sta{
        font-size: 3vh;
        text-align: center;
        justify-items: center;
        color: rgb(54, 130, 206);
    }

    .noti{
        position: relative;
        /* display: flex; */
        width: 30%;
        height: 300px;
        padding: 25px;
        border-radius: 35px;
        background-color: #ffffff;
        opacity: 0.8;
        margin-top: -490px; /* ปรับระยะห่างจาก .auto */
        margin-left: auto;
        margin-right: 5%;
        right: 0;
        overflow: scroll;
        overflow-y: auto; /* เปิดการ scroll แนวตั้ง */
        overflow-x: auto; /* ซ่อนการ scroll แนวนอน */
        box-shadow: 2px 4px 8px 2px rgb(255, 255, 255);
        


    }

    /* p{
        font-size: 3vh;
        text-align: center;
        color: rgb(54, 130, 206);
        margin-top: 3%;
    } */

    .sentnoti{
        position: relative;
        margin-top: 5%;
        width: 90%;
        height: 70px;
        padding: 25px;
        border-radius: 25px;
        background-color: #9fd2f4;
        align-items: center;
        margin-left: auto;
        margin-right: auto
    }


    .timer{
        position: absolute;
        width: 35%;
        height: 490px;
        padding: 25px;
        border-radius: 35px;
        background-color: #ffffff;
        opacity: 0.8;
        margin-top: -300px; /* ระดับเดียวกับ .noti */
        left: 27.5%;
        box-shadow: 2px 4px 8px 2px rgb(255, 255, 255);

    }

    .feeder{
        font-size: 4vh;
        /* text-align: center; */
        color: rgb(54, 130, 206);
        margin-left: 4%;
    }


    .box{
        position: relative;
        margin-top: 3%;
        width: 90%;
        height: 250px;
        padding: 25px;
        border-radius: 25px;
        background-color: #9fd2f4;
        align-items: center;
        margin-left: auto;
        margin-right: auto
    }
    .but{
        display: flex; /* ทำให้เป็น flex container */
        justify-content: center; /* จัดกลางในแนวนอน */
        align-items: center; /* จัดกลางในแนวตั้ง */
        margin-top: 10px;
    }
    .but button{
        height: 6.5vh;
        width: 60%;
        color: #ffffff;
        font-size: 1.7vh;
        font-weight: 400;
        margin-top: 30px;
        border: none;
        border-radius: 2vh;
        background-color: #ecb5df;
        font-size: 3vh;
        cursor: pointer;
        transition: all 0.2s ease;
    }

    .but button:hover{
        background-color: #b3d5fa;
    }

    .input-box input{
        position: relative;
        height: 6vh;
        width: 80%;
        outline: none;
        font-size: 1.5vh;
        color: #000000;
        margin-top: 20px;
        margin-left: 32px;
        border: none;
        border-radius: 7px;
        padding: 0 15px;
        font-size: 2vh;
        color: #5ab7f5;
    }

    .box p{
        font-size: 3vh;
        text-align: center;
        color: rgb(54, 130, 206);
        /* margin-top: 6%; */
    }

    .but2{
        display: flex; /* ทำให้เป็น flex container */
        justify-content: center; /* จัดกลางในแนวนอน */
        align-items: center; /* จัดกลางในแนวตั้ง */
        margin-top: 10px;
    }
    .but2 button{
        height: 5vh;
        width: 40%;
        color: #ffffff;
        font-size: 1.7vh;
        font-weight: 400;
        margin-top: 30px;
        border: none;
        border-radius: 1vh;
        background-color: #6fbcff;
        font-size: 2vh;
        cursor: pointer;
        transition: all 0.2s ease;
    }

    .but2 button:hover{
        background-color: #f7d8fc;
    }
    .food{
        position: absolute;
        /* display: flex; */
        width: 30%;
        height: 165px;
        padding: 25px;
        border-radius: 35px;
        background-color: #ffffff;
        opacity: 0.8;
        margin-top: 1.5%;
        margin-left: auto;
        margin-right: 5%;
        right: 0;
        box-shadow: 2px 4px 8px 2px rgb(255, 255, 255);

        p{
            font-size: 3vh;
            text-align: center;
            color: rgb(54, 130, 206);
        }

        .amount{
            font-size: 7vh;
            text-align: center;
            color: rgb(54, 130, 206);
        }
    }
    </style>
</head>
<body>
    <div class="auto">
        <div class="text"><label for="text">Auto-Fishcare</label></div>
    </div>
    <div class="tem">
        <p>Temperature-Now</p>
        <p class="tempo">%TEMP%°C</p>
    </div>
    <div class="emoji">
        <div class="sta"><p>Status</p></div>
        <div class="emo"><p>%EMO%</p></div>
    </div>
    <div class="noti">
        <div class="not"><label for="text" >Notification</label></div>
          <div class="sentnoti">
            <p>%TEMPno%</p>
          </div>
          <div class="sentnoti">
            <p>%FOODno%</p>
          </div>
    </div>
    <div class="timer">
        <div class="feeder">
            <div><p>Set timer/Feeder</p></div>
        </div>
        <div class="box">
            <div><p>Set time</p></div>
            <div class="input-box">
                <input type="time" placeholder="" required>
            </div>
            <div class="but2">
                <button>Submit</button>
            </div>
        </div>
        <div class="but">
            <button>Feed now</button>
        </div>
    </div>
    <div class="food">
        <p>Amount of food</p>
        <p class="amount">%FOOD% %</p>
    </div>
    
    
</body>
</html>
)rawliteral";

    // Replace placeholders with actual values
    html.replace("%TEMP%", String(temp_));
    html.replace("%FOOD%", String(food));
    String tempStatus;
    if (temp_ < 24) {
        tempStatus = "Water temperature too cool. ❄️!!!";
    } else if (temp_ > 28) {
        tempStatus = "Water temperature too hot. 🔥!!!";
    } else {
        tempStatus = "Water temperature was good. :D";
    }
    html.replace("%TEMPno%", tempStatus);

    String foodStatus;
      if (food < 30) {
          html.replace("%FOODno%", String("Thefood"));
      } else {
          foodStatus = "The food level was good :D";
      }
    
    
    return html;
}
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Servo myServo;
WiFiServer server(80);

void setup(){
  Serial.begin(9600); // Initialize serial communication at 9600 bits per second
  sensors.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(9);  // Attach the servo to pin = 9

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi network");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.begin(); // Start the server
}

int getTemp() {
  sensors.requestTemperatures(); //สั่งอ่านค่าอุณหภูมิ
  return sensors.getTempCByIndex(0); // แสดงค่าอุณหภูมิ
}

int getDistance() {
  // lear trigPin
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

  return distanceCm;
}

void openServo() {
  myServo.write(90);
}

void closeServo() {
  myServo.write(0);
}

void runWebServer() {
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client) {
    Serial.println("New Client Connected.");
    String request = client.readStringUntil('\r'); // Read the request
    Serial.println(request);
    client.flush();

    // Send a response to the client
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    Serial.println(generateHTML(40, 10));
    client.print(generateHTML(40, 10));

    delay(1);
    client.stop(); // Close the connection
    Serial.println("Client Disconnected.");
  }
}

void loop() {
  temp = getTemp();
  distance = getDistance();
  runWebServer();
  
  delay(1000);
}