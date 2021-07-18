#include <Arduino_FreeRTOS.h>
#include <queue.h>
int buzzPin=3 ;                             //定义蜂鸣器链接引脚
float t=0;
char c='z';

#include "dht11.h"
dht11 DHT11;
#define DHT11PIN A0

void setup()
{
  Serial.begin(9600);
  pinMode(buzzPin ,OUTPUT);   //定义蜂鸣器引脚模式为输出模式
  digitalWrite(buzzPin,HIGH);

}

void loop()
{
  // put your main code here, to run repeatedly:
  int chk = DHT11.read(DHT11PIN);
  
  Serial.print("Read sensor: ");
  switch (chk)
  {
    case DHTLIB_OK: 
                Serial.println("OK"); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                Serial.println("Checksum error"); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                Serial.println("Time out error"); 
                break;
    default: 
                Serial.println("Unknown error"); 
                break;
  }
  
  t=(float)DHT11.temperature;
  Serial.print("Temperature (oC): ");
  Serial.println(t, 2);

  //读取数据
  if(Serial.available()>0)//如果串口有数据进入的话
  {
    c=Serial.read();//每次读一个字符，是ASCII码的
  }
    
  if(c=='a'){
    digitalWrite(buzzPin,LOW);      //输入低电平，响
    delay(1000);
    digitalWrite(buzzPin,HIGH);
    c = 'b';
  }
  else if(c=='b'){
    digitalWrite(buzzPin,HIGH);       //输入高电平
  }
  delay(2000);
}
