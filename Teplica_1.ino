
// Подключение датчиков температуры
#include "DHT.h"

#define DHT1PIN 2           // Подключение первого датчика температуры на пин
#define DHT2PIN 4           // Подключение второго датчика температуры на пин
#define DHT3PIN 16          // Подключение третьего датчика температуры на пин
#define DHTTYPE DHT22       // Выбор типа датчика DHT 11 DHT 22  (AM2302), AM2321
DHT dht1(DHT1PIN, DHTTYPE); // определяем первый датчик температуры
DHT dht2(DHT2PIN, DHTTYPE); // определяем второй датчик температуры
DHT dht3(DHT3PIN, DHTTYPE); // определяем третий датчик температуры
//---------Определение кнопок и концевиков для окон----------------------------------
#define RELE_UP 14     // Подключение первого реле
#define RELE_DOWN 27   // Подключение второго реле
#define KONCEVIK_UP 13  // Подключение концевика открыто
#define KONCEVIK_DOWN 12  // Подключение концевика закрыто
#define BUTTON_UP 26   // Подключение кнопки на открытие
#define BUTTON_DOWN 25 // Подключение кнопки на закрытие

#define ON 0
#define OFF 1

#define DEBUG_DHT

// Для кнопок
#include "GyverButton.h"
GButton koncevikUp(KONCEVIK_UP);
GButton koncevikDown(KONCEVIK_DOWN);
GButton buttonUp(BUTTON_UP);
GButton buttonDown(BUTTON_DOWN);

unsigned long ms = 0, dht22Ms = 0, windowMs = 0;
int window = 0; // автомат работы двигателя открытия окон

int h1 = -127, h2 = -127, h3 = -127, t1 = -127, t2 = -127, t3 = -127; // значения состояний если датчик не отдал темературу ( отвалился)
void setup()
{
  Serial.begin(115200);
  Serial.println(F("DHT22 test!"));

  // Включаем управление модулем реле
  pinMode(RELE_UP, OUTPUT);   // Управление реле 1
  pinMode(RELE_DOWN, OUTPUT); // Управление реле 2

  // Отключаем реле на старте
  digitalWrite(RELE_UP, OFF);
  digitalWrite(RELE_DOWN, OFF);

  // Датчики температуры
  dht1.begin();
  dht2.begin();
  dht3.begin();

} // setup

void loop()
{
  koncevikUp.tick();
  koncevikDown.tick();
  buttonUp.tick();
  buttonDown.tick();
  ms = millis();

  // раз в 2 секунды опрашиваем датчики
  if ((ms - dht22Ms) > 2000)
  {
    dht22Ms = ms;
    //-------------Датчики температуры и влажности воздуха DHT22 воздуха-------------------------------------------------------------------
    h1 = dht1.readHumidity();
    h2 = dht2.readHumidity();
    h3 = dht3.readHumidity();
    // Чтение температуры в цельсиях
    t1 = dht1.readTemperature();
    t2 = dht2.readTemperature();
    t3 = dht3.readTemperature();

    // Проверка датчиков температуры
    if (h1 == -127 || t1 == -127)
    { // Проверка первого датчика температуры
      Serial.println(F("DHT_1 Error!"));
    } // if первого датчика температуры
    if (h2 == -127 || t2 == -127)
    { // Проверка первого датчика температуры
      Serial.println(F("DHT_2 Error!"));
    } // if второго датчика температуры
    if (h3 == -127 || t3 == -127)
    { // Проверка первого датчика температуры
      Serial.println(F("DHT_3 Error!"));
    } // if третьего датчика температуры

#ifdef DEBUG_DHT
    // Выдача информации о температуре и влажности в серийный порт
    //   Первый датчик
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

  } // if 2000

  switch (window)
  {
  case 0:
    // инициализация, ничего не делаем
    windowMs = ms;
    window = 5;
    break;
    // опрос кнопок или температуры
  case 5:
    if (buttonUp.isClick() && !koncevikUp.isHold())
    {
      window = 10;
    }

    break;
  // начало движения окна  ВВЕРХ, это состояние пригодится в будущем, поэтому оно отдельное
  case 10:
    digitalWrite(RELE_UP, ON);
    digitalWrite(RELE_DOWN, OFF);
    window = 12;
    break;
    // отлавливаем нажатия на концевик
  case 12:
    if (koncevikUp.isPress())
    {
      digitalWrite(RELE_UP, OFF);
      digitalWrite(RELE_DOWN, OFF);
      windowMs = ms;
      window = 14;
    }
    break;
    case 14:
    // подождем немного чтобы концевик смог обрести состояние isHold()
    if((ms - windowMs)> 350){
      windowMs = ms;
      window = 16;
    }
  //  нажатие на концевик уже было, но если нет удержания, продолжаем ехать дальше
  case 16:
    if (koncevikUp.isHold())
    {
      // концевик удерживается, возводим флаг, что мы в открытом состоянии
      // opened = 1;
      window = 0; // автомат в начало
    }
    else // нету удержания, продолжаем движение 
    {
      window = 10;
    }
    break;

  // начало движения окна  ВНИЗ
  //сделай по аналогии
case 20:
break;

  } // switch(window)

  //---------------------------------------------------------------------------------------------------

} // loop
