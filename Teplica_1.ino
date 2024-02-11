
//Подключение датчиков температуры
#include "DHT.h"

#define DHT1PIN 2            //Подключение первого датчика температуры на пин
#define DHT2PIN 4            //Подключение второго датчика температуры на пин
#define DHT3PIN 16           //Подключение третьего датчика температуры на пин
#define DHTTYPE DHT22        // Выбор типа датчика DHT 11 DHT 22  (AM2302), AM2321
DHT dht1(DHT1PIN, DHTTYPE);   //определяем первый датчик температуры
DHT dht2(DHT2PIN, DHTTYPE);  //определяем второй датчик температуры
DHT dht3(DHT3PIN, DHTTYPE);  //определяем третий датчик температуры
//---------Определение кнопок и концевиков для окон----------------------------------
#define RELE_1 14      //Подключение первого реле
#define RELE_2 27      //Подключение второго реле
#define KONCEVIK_1 13  //Подключение концевика открыто
#define KONCEVIK_2 12  //Подключение концевика закрыто
#define BUTTON_3 26    //Подключение кнопки на открытие
#define BUTTON_4 25    //Подключение кнопки на закрытие

#define ON 0
#define OFF 1

#define DEBUG_DHT

//Для кнопок
#include "GyverButton.h"
GButton KONC_1(KONCEVIK_1);
GButton KONC_2(KONCEVIK_2);
GButton butt3(BUTTON_3);
GButton butt4(BUTTON_4);

unsigned long ms = 0, dht22Ms = 0, windowMs = 0;
int window = 0; //автомат работы двигателя открытия окон


void setup() {
  Serial.begin(115200);
  Serial.println(F("DHT22 test!"));


  KONC_1.setTickMode(AUTO);
  KONC_2.setTickMode(AUTO);
  butt3.setTickMode(AUTO);
  butt4.setTickMode(AUTO);

  //Включаем управление модулем реле
  pinMode(RELE_1, OUTPUT);  //Управление реле 1
  pinMode(RELE_2, OUTPUT);  //Управление реле 2

  //Отключаем реле на старте
  digitalWrite(RELE_1, OFF);
  digitalWrite(RELE_2, OFF);

  //Датчики температуры
  dht1.begin();
  dht2.begin();
  dht3.begin();



}  //setup

void loop() {
  ms = millis();
delay (2000);
  // раз в 2 секунды опрашиваем датчики
  if ((ms - dht22Ms) > 2000) {
    dht22Ms = ms;
  }
    int h1 = dht1.readHumidity();
    int h2 = dht2.readHumidity();
    int h3 = dht3.readHumidity();
    // Чтение температуры в цельсиях
    int t1 = dht1.readTemperature();
    int t2 = dht2.readTemperature();
    int t3 = dht3.readTemperature();
  

 
 switch(window){
  case 0:
  // инициализация, ничего не делаем
  windowMs =0;
  window = 5;
  break;
  case 5:
  
  break;
  case 10:
  break;
 }
 
  
  //---------------------------------------------------------------------------------------------------
  //Подключение кнопок и концевиков для реле 1
   if (KONC_1.isClick()) {
    Serial.println("KONCEVIK_1");
    digitalWrite (RELE_1, OFF);
  }
  if (KONC_2.isClick()) {
    Serial.println("KONCEVIK_2");
    digitalWrite (RELE_2, OFF);
  }
  if (butt3.isClick()) {
    Serial.println("BUTTON_3");
    digitalWrite (RELE_1, ON);
  }
  if (butt4.isClick()) {
    Serial.println("BUTTON_4");
    digitalWrite (RELE_2, ON);
  }
  //---------------------------------------------------------------------------------------------------



//-------------Датчики температуры и влажности воздуха-------------------------------------------------------------------
  //Проверка датчиков температуры
  if (isnan(h1) || isnan(t1)) {  //Проверка первого датчика температуры
    Serial.println(F("DHT_1 Error!"));
      }//if первого датчика температуры
  if (isnan(h2) || isnan(t2)) {  //Проверка второго датчика температуры
    Serial.println(F("DHT_2 Error!"));
  }//if второго датчика температуры
  if (isnan(h3) || isnan(t3)) {  //Проверка третьего датчика температуры
    Serial.println(F("DHT_3 Error!"));
  }  //if третьего датчика температуры

  
 #ifdef DEBUG_DHT 
//Выдача информации о температуре и влажности в серийный порт
//  Первый датчик
  Serial.print(F("Temperature1: "));
  Serial.print(t1);
  Serial.print(F("°C Humidity1: "));
  Serial.print(h1);
  Serial.println(F("%"));
// Второй датчик
  Serial.print(F("Temperature2: "));
  Serial.print(t2);
  Serial.print(F("°C Humidity2: "));
  Serial.print(h2);
  Serial.println(F("%"));
// Третий датчик
  Serial.print(F("Temperature3: "));
  Serial.print(t3);
  Serial.print(F("°C Humidity3: "));
  Serial.print(h3);
  Serial.println(F("%"));
#endif

}  //loop
