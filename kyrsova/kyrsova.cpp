#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;
#define c cout
#define e endl

vector<vector<string>> catalog;
const string FILENAME = "songs.txt";

void saveCatalogToFile() {
    ofstream file(FILENAME);
    for (const auto& song : catalog) {
        file << song[0] << "\n" << song[1] << "\n" << song[2] << "\n" << song[3] << "<END>\n";
    }
    file.close();
}

void loadCatalogFromFile() {
    ifstream file(FILENAME);
    if (!file) return;
    catalog.clear();
    string title, author, year, lyrics, line;
    while (getline(file, title) && getline(file, author) && getline(file, year)) {
        lyrics = "";
        while (getline(file, line) && line != "<END>") {
            lyrics += line + "\n";
        }
        catalog.push_back({ title, author, year, lyrics });
    }
    file.close();
}

void addSong() {
    cin.ignore();
    string title, author, year, lyrics, line;
    c << "\nВедіть назву пісні: ";
    getline(cin, title);
    c << "Ведіть автора: ";
    getline(cin, author);
    c << "Ведіть рік (0, якщо незнаєте): ";
    getline(cin, year);
    c << "Ведіть текст пісні(закінченя - пуста строка) :\n";
    while (getline(cin, line) && !line.empty()) {
        lyrics += line + "\n";
    }
    catalog.push_back({ title, author, year, lyrics });
    saveCatalogToFile();
    c << "Пісня додана!\n";
}

void displaySong() {
    cin.ignore();
    string title;
    c << "Ведіть назву пісні: ";
    getline(cin, title);
    for (const auto& song : catalog) {
        if (song[0] == title) {
            c << "\nНазва: " << song[0] << "\nАвтор: " << song[1] << "\nРік: " << song[2] << "\nТекст:\n" << song[3];
            return;
        }
    }
    c << "пісня не знайдена!\n";
}

void searchByAuthor() {
    cin.ignore();
    string author;
    c << "Ведіть ім'я автора: ";
    getline(cin, author);
    for (const auto& song : catalog) {
        if (song[1] == author) {
            c << "\nНазва: " << song[0] << "\nРік: " << song[2] << "\n";
        }
    }
}

void searchByWord() {
    cin.ignore();
    string word;
    c << "Ведіть слово для пошуку: ";
    getline(cin, word);
    for (const auto& song : catalog) {
        if (song[3].find(word) != string::npos) {
            c << "\nНазва: " << song[0] << "\nАвтор: " << song[1] << "\n";
        }
    }
}

void deleteSong() {
    cin.ignore();
    string title;
    c << "Ведіть назву пісні для видаленя: ";
    getline(cin, title);
    catalog.erase(remove_if(catalog.begin(), catalog.end(), [&](const vector<string>& s) { return s[0] == title; }), catalog.end());
    saveCatalogToFile();
    c << "Пісня видалена!\n";
}

void modifySong() {
    cin.ignore();
    string title;
    c << "Ведіть назву пісні для редагуваня: ";
    getline(cin, title);
    for (auto& song : catalog) {
        if (song[0] == title) {
            c << "Ведіть новий текст пісні (закінченя - порожня строка):\n";
            song[3] = "";
            string line;
            while (getline(cin, line) && !line.empty()) {
                song[3] += line + "\n";
            }
            saveCatalogToFile();
            c << "Текст оновлено!\n";
            return;
        }
    }
    c << "Пісня не зайдена!\n";
}

int main() {
    system("chcp 1251>null");
    loadCatalogFromFile();
    int choice;
    do {
        c << "\t\t\tКАТАЛОГ ПІСЕНЬ";
        c << "\nМеню:\n1. Додати пісню\n2. Показати текст пісні\n3. Знайти пісні за автором\n4. Знайти пісні за словом\n5. видалити пісню\n6. змінити текст пісні\n7. Вихід\nВаш вибір: ";
        cin >> choice;
        switch (choice) {
        case 1: addSong(); break;
        case 2: displaySong(); break;
        case 3: searchByAuthor(); break;
        case 4: searchByWord(); break;
        case 5: deleteSong(); break;
        case 6: modifySong(); break;
        case 7: c << "вихід...\n"; break;
        default: c << "невірний ввод!\n";
        }
    } while (choice != 7);
    return 0;
}