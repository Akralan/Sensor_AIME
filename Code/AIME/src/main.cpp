#include <Arduino.h>
#include "gaz_sensor.h"
#include "oled_screen.h"
#include "BluetoothSerial.h"

#include <HardwareSerial.h>

// Définition du port série pour LoRa (UART2)
#define RXD2 16 // GPIO16 (RX)
#define TXD2 17 // GPIO17 (TX)
HardwareSerial LoRaSerial(2); // Utilise UART2

void setup() {
  Serial.begin(9600); // Moniteur série
  LoRaSerial.begin(9600, SERIAL_8N1, RXD2, TXD2); // Port série LoRa, 9600 baud

  // Envoyer une commande AT pour vérifier la connexion
  LoRaSerial.println("AT");
  delay(5000);

  // Lire la réponse
  while (LoRaSerial.available()) {
    String response = LoRaSerial.readString();
    Serial.print("Réponse LoRa: ");
    Serial.println(response);
  }

  // Récupérer l'EUI64
  Serial.println("Demande de l'EUI64...");
  LoRaSerial.println("sys get hweui"); // Commande pour l'EUI (à vérifier dans la documentation)
  delay(1000);
}

void loop() {
    if (LoRaSerial.available()) {
        String response = LoRaSerial.readString();
        Serial.print("EUI64: ");
        Serial.println(response);
    }
}


/*#define LED 4

#define BOARD_TYPE "ESP32"
#define SENSOR_TYPE "MQ-9"
#define ANALOG_PIN 36
#define VOLTAGE_RESOLUTION 5.0
#define ADC_BIT_RESOLUTION 10
#define RATIO_CLEAN_AIR 9.83 // Ratio du capteur en air propre (selon datasheet)

BluetoothSerial SerialBT;
GazSensor mq9(BOARD_TYPE, SENSOR_TYPE, ANALOG_PIN, VOLTAGE_RESOLUTION, ADC_BIT_RESOLUTION, RATIO_CLEAN_AIR);
bool blink = false;
bool ledState = false;
unsigned long previousMillis = 0;

void setup() {
    Serial.begin(9600);
    SerialBT.begin("ESP32_BT_Alix");

    pinMode(LED, OUTPUT);
    digitalWrite(LED, ledState);

    mq9.begin(); // Initialisation et calibration du capteur

    OLEDManager oled;
    if (!oled.begin()) {
        Serial.println("Erreur d'initialisation de l'écran !");
        while (true); // Arrête le programme si l'initialisation échoue
    }

    oled.reset(); // Réinitialisation de l'écran

    // Affichage de texte sur différentes lignes
    oled.displayText(0, "Bonjour !");
    oled.displayText(1, "Ligne 1 : Test");
    oled.displayText(2, "Ligne 2 : OK");
}

void loop() {
    unsigned long currentMillis = millis(); // Temps actuel

    if (Serial.available()) {
        SerialBT.write(Serial.read()); // Envoie les données reçues via Bluetooth
    }
    if (SerialBT.available()) {
        int data = SerialBT.read();
        switch(data) {
            case 1:
                blink = false;
                digitalWrite(LED, HIGH);
                break;
            case 2:
                blink = false;
                digitalWrite(LED, LOW);
                break;
            case 3:
                blink = true;
                break;
            default:
                break;
        }
        Serial.println(data); // Affiche les données Bluetooth sur le port série
    }
    if (currentMillis - previousMillis >= 1000) {
        previousMillis = currentMillis; // Met à jour le moment du dernier changement

        // Inverse l'état de la LED
        if (blink) {
            ledState = !ledState;
            digitalWrite(LED, ledState);
        }
        float ch4_ppm = mq9.readPPM("CH4");
        Serial.println(ch4_ppm);
        SerialBT.write(ch4_ppm); // Envoie les données reçues via Bluetooth
    }
}*/