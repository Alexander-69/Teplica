
//Подключение датчиков температуры
#include "DHT.h"

#define DHT1PIN 2 //Подключение первого датчика температуры на пин
#define DHT2PIN 4 //Подключение второго датчика температуры на пин
#define DHT3PIN 16 //Подключение третьего датчика температуры на пин
#define DHTTYPE DHT22   // Выбор типа датчика DHT 11 DHT 22  (AM2302), AM2321
DHT dht(DHT1PIN, DHTTYPE);  //определяем первый датчик температуры
DHT dht2(DHT2PIN, DHTTYPE); //определяем второй датчик температуры
DHT dht3(DHT3PIN, DHTTYPE); //определяем третий датчик температуры

#define RELE_1 13 //Подключение первого реле
#define RELE_2 12 //Подключение второго реле
#define KONCEVIK_1 14 //Подключение концевика открыто
#define KONCEVIK_2 27 //Подключение концевика закрыто
#define BUTTON_3 26 //Подключение кнопки на открытие
#define BUTTON_4 25 //Подключение кнопки на закрытие

#define ON 0
#define OFF 1

//Для кнопок
#include "GyverButton.h"
GButton butt1(KONCEVIK_1);
GButton butt2(KONCEVIK_2);
GButton butt3(BUTTON_3);
GButton butt4(BUTTON_4);


void setup() {
  Serial.begin(115200);
  Serial.println(F("DHT22 test!"));

//Отключаем реле на старте


    butt1.setTickMode(AUTO);
      butt2.setTickMode(AUTO);
      butt3.setTickMode(AUTO);
      butt4.setTickMode(AUTO);

//Включаем управление модулем реле
  pinMode (RELE_1, OUTPUT); //Управление реле 1
  pinMode (RELE_2, OUTPUT); //Управление реле 2

//Отключаем реле на старте
digitalWrite (RELE_1, OFF);
digitalWrite (RELE_2, OFF);

//Датчики температуры
  dht.begin();
  dht2.begin();
  dht3.begin();

    

} //setup

void loop() {
   delay(2000); // Пауза в 2 секунды
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
//---------------------------------------------------------------------------------------------------
//Подключение кнопок и концевиков для реле 1
  if (butt1.isClick()) Serial.println("Button 1"); {
    digitalWrite (RELE_1, OFF);
  }
  if (butt2.isClick()) Serial.println("Button 2"); {
    digitalWrite (RELE_2, OFF);
  }
  if (butt3.isClick()) Serial.println("Button 3"); {
    digitalWrite (RELE_1, ON);
  }
  if (butt4.isClick()) Serial.println("Button 4"); {
    digitalWrite (RELE_2, ON);
  }
//---------------------------------------------------------------------------------------------------

  float h = dht.readHumidity();
  float h2 = dht2.readHumidity();
  float h3 = dht2.readHumidity();
  // Чтение температуры в цельсиях
  float t = dht.readTemperature();
  float t2 = dht2.readTemperature();
  float t3 = dht3.readTemperature();
   
  // Проверка датчиков температуры
  if (isnan(h) || isnan(t)) {  //Проверка первого датчика температуры
    Serial.println(F("Failed to read from DHT_1 sensor!"));
    return;
  } //if первого датчика температуры
  if (isnan(h2) || isnan(t2)) {   //Проверка второго датчика температуры
    Serial.println(F("Failed to read from DHT_2 sensor!"));
    return;
  } //if второго датчика температуры
  if (isnan(h3) || isnan(t3)) {   //Проверка третьего датчика температуры
    Serial.println(F("Failed to read from DHT_2 sensor!"));
    return;
  } //if третьего датчика температуры
    
//    float hic = dht.computeHeatIndex(t, h, false);
  //Выдача информации о температуре и влажности в серийный порт
  Serial.print(F("Humidity1: "));
  Serial.print(h);
  Serial.print(F("% Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
//  Serial.print(hic);
//  Serial.print(F("°C "));
  
//  float hic2 = dht2.computeHeatIndex(t2, h2, false);
  Serial.print(F("Humidity2: "));
  Serial.print(h2);
  Serial.print(F("% Temperature2: "));
  Serial.print(t2);
  Serial.println(F("°C "));
// Serial.print(hic2);
//  Serial.print(F("°C "));
  
 // float hic3 = dht3.computeHeatIndex(t3, h3, false);
  Serial.print(F("Humidity3: "));
  Serial.print(h3);
  Serial.print(F("% Temperature3: "));
  Serial.print(t3);
  Serial.println(F("°C "));
 // Serial.print(hic3);
 // Serial.print(F("°C "));

  } //loop
