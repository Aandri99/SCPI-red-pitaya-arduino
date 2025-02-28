#include <Ethernet.h>

// MAC адрес модуля W5500 (можно изменить по вашему усмотрению)
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
char server[] = "www.google.com";  // Целевой сервер

EthernetClient client;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;  // Ждем завершения инициализации
  }

  // Запуск Ethernet подключения
  if (Ethernet.begin(mac) == 0) {
    Serial.println(
        "Не удалось настроить Ethernet, используйте статическую конфигурацию");
    while (true) {
      delay(1);
    }
  }

  Serial.println("Ethernet подключение установлено!");
  delay(1000);
}

void loop() {
  if (client.connect(server, 80)) {
    Serial.println("Подключено к серверу");
    client.print("GET / HTTP/1.1");
    client.println();
    client.println("Host: www.google.com");
    client.println();
  } else {
    Serial.println("Не удалось подключиться к серверу");
  }

  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
  }

  Serial.println();
  Serial.println("Закрытие соединения");
  client.stop();
  delay(5000);  // Пауза в 5 секунд перед следующей попыткой
}