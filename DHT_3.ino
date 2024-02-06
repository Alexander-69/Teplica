
//Подключение датчиков температуры
#include "DHT.h"
#define DHT1PIN 13 //Подключение первого датчика температуры на пин
#define DHT2PIN 14 //Подключение второго датчика температуры на пин
#define DHT3PIN 15 //Подключение третьего датчика температуры на пин
#define DHTTYPE DHT22   // Выбор типа датчика DHT 11 DHT 22  (AM2302), AM2321
DHT dht(DHT1PIN, DHTTYPE);  //определяем первый датчик температуры
DHT dht2(DHT2PIN, DHTTYPE); //определяем второй датчик температуры
DHT dht3(DHT3PIN, DHTTYPE); //определяем третий датчик температуры

void setup() {
  Serial.begin(115200);
  Serial.println(F("DHT22 test!"));

  dht.begin();
  dht2.begin();
  dht3.begin();
} //setup

void loop() {
   delay(2000); // Пауза в 2 секунды
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
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
    
    float hic = dht.computeHeatIndex(t, h, false);
  //Выдача информации о температуре и влажности в серийный порт
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("% Temperature: "));
  Serial.print(t);
  
  Serial.print(F("°C "));
  Serial.print(hic);
  Serial.print(F("°C "));
  
  float hic2 = dht2.computeHeatIndex(t2, h2, false);
  Serial.print(F("Humidity2: "));
  Serial.print(h2);
  Serial.print(F("% Temperature2: "));
  Serial.print(t2);

  Serial.print(F("°C "));
  Serial.print(hic2);
  Serial.print(F("°C "));
  
  float hic3 = dht3.computeHeatIndex(t3, h3, false);
  Serial.print(F("Humidity3: "));
  Serial.print(h3);
  Serial.print(F("% Temperature3: "));
  Serial.print(t3);

  Serial.print(F("°C "));
  Serial.print(hic3);
  Serial.print(F("°C "));

  } //loop
