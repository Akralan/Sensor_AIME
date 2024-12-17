#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Configuration de l'écran OLED
#define SCREEN_WIDTH 128 // Largeur de l'écran OLED
#define SCREEN_HEIGHT 64 // Hauteur de l'écran OLED
#define OLED_RESET -1    // Pin de reset (-1 si pas utilisé)
#define SSD1306_I2C_ADDRESS 0x3C

// Classe pour gérer un écran SSD1306
class OLEDManager {
private:
    Adafruit_SSD1306* display;

public:
    // Constructeur
    OLEDManager() {
        display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    }

    // Initialisation de l'écran
    bool begin() {
        if (!display->begin(SSD1306_I2C_ADDRESS, OLED_RESET)) {
            Serial.println("Échec de l'initialisation de l'écran OLED !");
            return false;
        }
        display->clearDisplay();
        display->display();
        Serial.println("Écran OLED initialisé !");
        return true;
    }

    // Réinitialisation de l'écran
    void reset() {
        display->clearDisplay();
        display->display();
        Serial.println("Écran OLED réinitialisé !");
    }

    // Afficher un texte sur une ligne spécifique
    void displayText(int line, const String& text) {
        if (line < 0 || line > 7) { // Vérification que la ligne est valide (max 8 lignes pour 64px avec une police standard de 8px)
            Serial.println("Ligne invalide !");
            return;
        }

        display->setTextSize(1);             // Taille du texte
        display->setCursor(0, line * 8);     // Définir la position en pixels (ligne * 8 pour espacement vertical)
        display->print(text);                // Afficher le texte
        display->display();                  // Mettre à jour l'écran
    }

    // Destructeur
    ~OLEDManager() {
        delete display;
    }
};