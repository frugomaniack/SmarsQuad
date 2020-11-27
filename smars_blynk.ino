/*Wemos Sterownik
 * D1    SCL
 * D2     SDA 
 * 3V3   - VCC
 * 5V     - 5V
 */

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             50


// our servo # counter
uint8_t servonum = 0;
int zmiana=90;


int v0;
int v1;
int v2;

int lewezmiana=90;
int prawazmiana=90;

#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "b522def33e9c427098a5f00019040395";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "-----";
char pass[] = "----";
void setup()
{
  // Debug console
  Serial.begin(9600);
    Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  
  ruch(5,115);
  ruch(7,115);
  ruch(9,115);
  ruch(11,115);
  
       
  lewezmiana=45;
     lewezmiana  = map(lewezmiana,0, 180, SERVOMIN, SERVOMAX);
       pwm.setPWM(4, 0, lewezmiana); //45 przod 135 tyl
        lewezmiana=135;
     lewezmiana  = map(lewezmiana,0, 180, SERVOMIN, SERVOMAX);
       pwm.setPWM(6, 0, lewezmiana); //135 przod 45 tyl
        lewezmiana=135;
     lewezmiana  = map(lewezmiana,0, 180, SERVOMIN, SERVOMAX);
       pwm.setPWM(8, 0, lewezmiana); //45 przod 135 tyl

       lewezmiana=45;
     lewezmiana  = map(lewezmiana,0, 180, SERVOMIN, SERVOMAX);
       pwm.setPWM(10, 0, lewezmiana); //135 przod 45 tyl


    
  delay(1000);
  
  Blynk.begin(auth, ssid, pass);
}


// you can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz //60
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution  //4096
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000000;  // convert to us
  pulse /= pulselength;
  Serial.println(pulse);

  pwm.setPWM(n, 0, pulse);

}



void lewosetpwm(int nrserwa,int kat,int opoznienie)
{
      servonum=nrserwa;
     lewezmiana=kat;
     lewezmiana  = map(lewezmiana,0, 180, SERVOMIN, SERVOMAX);
     pwm.setPWM(servonum, 0, lewezmiana);

}
void prawosetpwm(int nrserwa,int kat,int opoznienie)
{
     kat=180-kat;
      servonum=nrserwa;
     lewezmiana=kat;
     lewezmiana  = map(lewezmiana,0, 180, SERVOMIN, SERVOMAX);
     pwm.setPWM(servonum, 0, lewezmiana);

}
void ruch(int servo,int kat)
{
  if(servo==5||servo==4||servo==8||servo==11)
  {
    lewezmiana=kat;
     lewezmiana  = map(lewezmiana,0, 180, SERVOMIN, SERVOMAX);
       pwm.setPWM(servo, 0, lewezmiana); 
  }
  else
  {
     lewezmiana=180-kat;
     lewezmiana  = map(lewezmiana,0, 180, SERVOMIN, SERVOMAX);
      pwm.setPWM(servo, 0, lewezmiana); 
  }
}
void przod()
{
  ruch(4,90);
  delay(100);
  ruch(10,90);
  
  delay(500);
  ruch(7,45);
  ruch(6,45);
  delay(100);
  ruch(7,115);
delay(100);
ruch(4,90);
ruch(10,135);
ruch(9,45);
delay(100);
ruch(8,90);
ruch(9,115);
delay(500);
//faza 2
ruch(5,45);
delay(100);
ruch(4,45);
delay(100);
ruch(5,115);
delay(100);
ruch(6,90);
ruch(8,135);
ruch(11,45);
delay(100);
ruch(10,90);
ruch(11,115);
delay(100);
   


   
   
   
  
}

void defaultpoz()
{
  ruch(4,45);
  ruch(6,45);
  ruch(8,135);
  ruch(10,135);
  
ruch(5,115);
ruch(7,115);
ruch(9,115);
ruch(11,115);
  
}
void prawo()
{

delay(500);
 defaultpoz();
 delay(500);
 
ruch(7,45);
delay(100);
ruch(6,90);
delay(100);
ruch(7,115);

delay(500);
ruch(4,90);
ruch(6,45);
ruch(8,180);
ruch(11,45);
delay(100);
ruch(10,180);
delay(100);
ruch(11,115);

delay(500);
ruch(9,45);
delay(100);
ruch(8,135);
delay(100);
ruch(9,115);
delay(100);
ruch(4,45);
ruch(10,135);
delay(100);
}
void lewo()
{
delay(500);
 defaultpoz();
 delay(500);

ruch(5,45);
delay(100);
ruch(4,90);
delay(100);
ruch(5,115);

delay(500);
ruch(9,45);
delay(100);
ruch(4,45);
ruch(6,90);
ruch(10,180);
ruch(8,180);
delay(100);
ruch(9,115);

delay(500);
ruch(11,45);
delay(100);
ruch(10,135);
delay(100);
ruch(11,115);
delay(100);
ruch(8,135);
ruch(6,45);
delay(100);

}
BLYNK_WRITE(V0){
v0=param.asInt();
if(v0==1)
{
  przod();
}
}

BLYNK_WRITE(V1){
 v1=param.asInt();
if(v1==1)
{
  lewo();
}
}

BLYNK_WRITE(V2){
 v2=param.asInt();
if(v2==1)
{
  prawo();
}
}

void loop() {
Blynk.run();

 if(v0==0&&v1==0&&v2==0)
 {
  delay(500);
  defaultpoz();
 }



}
