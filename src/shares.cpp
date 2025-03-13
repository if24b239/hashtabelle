#include <shares.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

using json = nlohmann::json;

// Helper function to convert string with dollar sign to double
double string_to_double(const std::string& str) {
    std::string cleaned_str;

    // Remove dollar sign and any other non-numeric characters except decimal point
    for (char c : str) {
        if (isdigit(c) || c == '.' || c == '-') {
            cleaned_str += c;
        }
    }

    // Convert to double
    return std::stod(cleaned_str);
}

bool Share::import_history(const std::string& filename) {
    // Try different path options
    std::string filepath = filename;  // First try the path as given
    std::ifstream file(filepath);

    // If file didn't open, try with "./" prefix
    if (!file.is_open()) {
        filepath = "./" + filename;
        file.open(filepath);
    }

    // If still not open, try with "../" prefix (parent directory)
    if (!file.is_open()) {
        filepath = "../" + filename;
        file.open(filepath);
    }

    // Check if file opened successfully with any of the paths
    if (!file.is_open()) {
        std::cout << "Error: Could not open file. Tried paths: " << std::endl;
        std::cout << "  - " << filename << std::endl;
        std::cout << "  - ./" << filename << std::endl;
        std::cout << "  - ../" << filename << std::endl;
        std::cout << "Please check that the file exists and specify the correct path." << std::endl;
        return false;
    }

    std::cout << "Successfully opened file: " << filepath << std::endl;

    std::string line;
    bool first_line = true;

    // Read the file line by line
    while (std::getline(file, line)) {
        // Skip the header line
        if (first_line) {
            first_line = false;
            continue;
        }

        // Parse the CSV line
        std::stringstream ss(line);
        std::string date, close_str, volume_str, open_str, high_str, low_str;

        // Get each field from the line
        std::getline(ss, date, ',');
        std::getline(ss, close_str, ',');
        std::getline(ss, volume_str, ',');
        std::getline(ss, open_str, ',');
        std::getline(ss, high_str, ',');
        std::getline(ss, low_str, ',');

        try {
            // Convert string values to appropriate types
            double close = string_to_double(close_str);
            int volume = std::stoi(volume_str);
            double open = string_to_double(open_str);
            double high = string_to_double(high_str);
            double low = string_to_double(low_str);

            // Create a Day object and add it to history
            Day day(date, close, volume, open, high, low);
            history.push_back(day);
        }
        catch (const std::exception& e) {
            std::cout << "Error parsing line: " << line << std::endl;
            std::cout << "Error message: " << e.what() << std::endl;
        }
    }

    std::cout << "Successfully imported " << history.size() << " days of history for " << name << std::endl;
    return true;
}

void Share::print_share_data() {
    std::cout << "Share: " << name << " (" << token << ")" << std::endl;
    std::cout << "WKN: " << wkn << std::endl;
    std::cout << "History size: " << history.size() << " days" << std::endl;

    // Print first 5 days of history (or less if there are fewer days)
    std::cout << "Sample of history data:" << std::endl;
    int count = 0;
    for (const auto& day : history) {
        if (count >= 5) break;

        std::cout << "  Date: " << day.date
                  << ", Open: " << day.open
                  << ", High: " << day.high
                  << ", Low: " << day.low
                  << ", Close: " << day.close
                  << ", Volume: " << day.volume << std::endl;
        count++;
    }
}

void from_json(const json& j, Share& share) {
    j.at("name").get_to(share.name);
    j.at("wkn").get_to(share.wkn);
    j.at("token").get_to(share.token);
}

void Share::plot_schlusskurse(int tage) {
    // Prüfen, ob Kursdaten vorhanden sind
    if (history.empty()) {
        std::cout << "Keine Daten für " << name << " verfügbar!" << std::endl;
        return;
    }

    // Anzahl der verfügbaren Tage begrenzen
    int verfuegbare_tage = history.size();
    int anzeige_tage = (tage < verfuegbare_tage) ? tage : verfuegbare_tage;

    // Die letzten X Tage auswählen
    std::cout << "\nSchlusskurse (" << token << ") - letzte " << anzeige_tage << " Tage:\n";

    // Höchsten und niedrigsten Kurs finden
    double max_kurs = 0;
    double min_kurs = 999999;
    for (int i = verfuegbare_tage - anzeige_tage; i < verfuegbare_tage; i++) {
        double kurs = history[i].close;
        if (kurs > max_kurs) max_kurs = kurs;
        if (kurs < min_kurs) min_kurs = kurs;
    }

    // Höhe des Diagramms
    const int hoehe = 10;

    // Diagramm-Matrix erstellen (Höhe x Breite)
    char diagramm[hoehe][anzeige_tage];

    // Diagramm mit Leerzeichen initialisieren
    for (int y = 0; y < hoehe; y++) {
        for (int x = 0; x < anzeige_tage; x++) {
            diagramm[y][x] = ' ';
        }
    }

    // Kurspunkte in die Matrix eintragen
    for (int tag = 0; tag < anzeige_tage; tag++) {
        // Tatsächlicher Index in der Historie
        int idx = verfuegbare_tage - anzeige_tage + tag;
        double kurs = history[idx].close;
        // Kurswert normalisieren (0 bis hoehe-1)
        int y_pos = hoehe - 1 - (int)((kurs - min_kurs) / (max_kurs - min_kurs) * (hoehe - 1));
        if (y_pos < 0) y_pos = 0;
        if (y_pos >= hoehe) y_pos = hoehe - 1;
        diagramm[y_pos][tag] = '*';
    }

    // Diagramm ausgeben mit extra Spacing zwischen den Spalten
    for (int y = 0; y < hoehe; y++) {
        if (y % 2 == 0) {
            double kurs_wert = max_kurs - y * (max_kurs - min_kurs) / (hoehe - 1);
            printf("%6.2f |", kurs_wert);
        } else {
            printf("       |");
        }
        for (int x = 0; x < anzeige_tage; x++) {
            // Hier wird ein zusätzlicher Leerraum hinzugefügt
            std::cout << diagramm[y][x] << " ";
        }
        std::cout << std::endl;
    }

    // X-Achse anpassen (hier werden zwei '-' pro Tag gedruckt)
    std::cout << "       +";
    for (int i = 0; i < anzeige_tage; i++) {
        std::cout << "--";
    }
    std::cout << std::endl;

    // Datum alle 5 Tage ausgeben, ebenfalls mit zusätzlichem Leerraum
    std::cout << "        ";
    for (int i = 0; i < anzeige_tage; i += 4) {
        if (i < anzeige_tage) {
            std::string datum = history[verfuegbare_tage - anzeige_tage + i].date;
            std::cout << datum.substr(0, 5);
            // Zusätzliche Leerzeichen für die Ausrichtung, hier 2 Leerzeichen
            std::cout << "  ";
        }
    }
    std::cout << std::endl;
}

