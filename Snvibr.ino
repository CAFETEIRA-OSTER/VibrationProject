#include <SPI.h>
#include <TFT_eSPI.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>


#define TFT_WIDTH  240
#define TFT_HEIGHT 240
#define TFT_MOSI   23
#define TFT_SCK    18
#define TFT_CS     15
#define TFT_DC     2
#define TFT_RST    -1  

// Inicializa instâncias do display e do MPU6050
TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);
Adafruit_MPU6050 mpu;

void setup() {
  // Inicializa comunicação serial para debug
  Serial.begin(115200);
  Serial.println("Inicializando...");

  // Inicializa o sensor MPU6050
  if (!mpu.begin()) {
    Serial.println("Falha ao inicializar o MPU6050!");
    while (1); 
  }
  Serial.println("MPU6050 inicializado com sucesso!");

  // Configurações do MPU6050
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Inicializa o display TFT
  tft.init();
  tft.setRotation(2); 
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);

  // Layout fixo no display
  tft.setCursor(78, 20);
  tft.println("MPU6050");

  tft.setCursor(50, 60);
  tft.println("Acc X:");
  tft.setCursor(50, 80);
  tft.println("Acc Y:");
  tft.setCursor(50, 100);
  tft.println("Acc Z:");

  tft.setCursor(50, 140);
  tft.println("Gyro X:");
  tft.setCursor(50, 160);
  tft.println("Gyro Y:");
  tft.setCursor(50, 180);
  tft.println("Gyro Z:");

}

void loop() {
  // Lê os dados do sensor MPU6050
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Atualiza os dados no Serial Monitor
  Serial.print("Acelerômetro (m/s²): X=");
  Serial.print(a.acceleration.x);
  Serial.print(", Y=");
  Serial.print(a.acceleration.y);
  Serial.print(", Z=");
  Serial.println(a.acceleration.z);

  Serial.print("Giroscópio (rad/s): X=");
  Serial.print(g.gyro.x);
  Serial.print(", Y=");
  Serial.print(g.gyro.y);
  Serial.print(", Z=");
  Serial.println(g.gyro.z);

  Serial.print("Temperatura (C): ");
  Serial.println(temp.temperature);

  // Atualiza apenas os valores no display
  tft.setCursor(130, 60); // Posição do valor Acc X
  tft.fillRect(130, 60, 100, 16, TFT_BLACK); // Limpa apenas o valor anterior
  tft.printf("%.2f", a.acceleration.x);

  tft.setCursor(130, 80); // Posição do valor Acc Y
  tft.fillRect(130, 80, 100, 16, TFT_BLACK); // Limpa apenas o valor anterior
  tft.printf("%.2f", a.acceleration.y);

  tft.setCursor(130, 100); // Posição do valor Acc Z
  tft.fillRect(130, 100, 100, 16, TFT_BLACK); // Limpa apenas o valor anterior
  tft.printf("%.2f", a.acceleration.z);

  tft.setCursor(140, 140); // Posição do valor Gyro X
  tft.fillRect(130, 140, 100, 16, TFT_BLACK); // Limpa apenas o valor anterior
  tft.printf("%.2f", g.gyro.x);

  tft.setCursor(140, 160); // Posição do valor Gyro Y
  tft.fillRect(140, 160, 100, 16, TFT_BLACK); // Limpa apenas o valor anterior
  tft.printf("%.2f", g.gyro.y);

  tft.setCursor(140, 180); // Posição do valor Gyro Z
  tft.fillRect(140, 180, 100, 16, TFT_BLACK); // Limpa apenas o valor anterior
  tft.printf("%.2f", g.gyro.z);

  tft.setCursor(75, 220); // Posição do valor Temp
  tft.fillRect(75, 220, 100, 14, TFT_BLACK); // Limpa apenas o valor anterior
  tft.printf("%.2f C", temp.temperature);

  delay(30); 
}
