#include <MQUnifiedsensor.h>

class GazSensor {
private:
    MQUnifiedsensor* sensor;
    String board;
    String type;
    int pin;
    float voltageResolution;
    int adcBitResolution;
    float ratioCleanAir;

public:
    // Constructeur
    GazSensor(const String& boardType, const String& sensorType, int analogPin, float vResolution, int adcResolution, float cleanAirRatio)
        : board(boardType), type(sensorType), pin(analogPin), voltageResolution(vResolution), adcBitResolution(adcResolution), ratioCleanAir(cleanAirRatio) {
        sensor = new MQUnifiedsensor(board, voltageResolution, adcBitResolution, pin, type);
    }

    // Initialisation
    void begin() {
        sensor->init();
        Serial.println("Capteur MQ-9 initialisé !");
        calibrate(); // Calibration initiale
    }

    // Calibration
    void calibrate() {
        sensor->setR0(10); // Résistance initiale (ajuster après calibration)
        Serial.println("Calibration terminée !");
    }

    // Lecture des données en fonction du type de gaz
    float readPPM(const String& gasType) {
        sensor->update(); // Mise à jour des données du capteur

        if (gasType == "CO") {
            sensor->setA(99.042);  // Coefficient A pour le CO
            sensor->setB(-1.518); // Coefficient B pour le CO
        } else if (gasType == "CH4") {
            sensor->setA(77.6);   // Coefficient A pour le CH4
            sensor->setB(-1.398); // Coefficient B pour le CH4
        } else if (gasType == "GPL") {
            sensor->setA(100.0);  // Coefficient A pour le GPL
            sensor->setB(-1.45);  // Coefficient B pour le GPL
        } else {
            Serial.println("Type de gaz inconnu !");
            return -1.0; // Retourne une valeur invalide pour signaler une erreur
        }

        float ppm = sensor->readSensor(); // Lecture de la concentration en ppm
        return ppm;
    }

    // Nettoyage
    ~GazSensor() {
        delete sensor;
    }
};