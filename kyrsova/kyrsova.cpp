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
    c << "\nВведите название песни: ";
    getline(cin, title);
    c << "Введите автора: ";
    getline(cin, author);
    c << "Введите год (0, если неизвестно): ";
    getline(cin, year);
    c << "Введите текст песни (окончание - пустая строка):\n";
    while (getline(cin, line) && !line.empty()) {
        lyrics += line + "\n";
    }
    catalog.push_back({ title, author, year, lyrics });
    saveCatalogToFile();
    c << "Песня добавлена!\n";
}

void displaySong() {
    cin.ignore();
    string title;
    c << "Введите название песни: ";
    getline(cin, title);
    for (const auto& song : catalog) {
        if (song[0] == title) {
            c << "\nНазвание: " << song[0] << "\nАвтор: " << song[1] << "\nГод: " << song[2] << "\nТекст:\n" << song[3];
            return;
        }
    }
    c << "Песня не найдена!\n";
}

void searchByAuthor() {
    cin.ignore();
    string author;
    c << "Введите имя автора: ";
    getline(cin, author);
    for (const auto& song : catalog) {
        if (song[1] == author) {
            c << "\nНазвание: " << song[0] << "\nГод: " << song[2] << "\n";
        }
    }
}

void searchByWord() {
    cin.ignore();
    string word;
    c << "Введите слово для поиска: ";
    getline(cin, word);
    for (const auto& song : catalog) {
        if (song[3].find(word) != string::npos) {
            c << "\nНазвание: " << song[0] << "\nАвтор: " << song[1] << "\n";
        }
    }
}

void deleteSong() {
    cin.ignore();
    string title;
    c << "Введите название песни для удаления: ";
    getline(cin, title);
    catalog.erase(remove_if(catalog.begin(), catalog.end(), [&](const vector<string>& s) { return s[0] == title; }), catalog.end());
    saveCatalogToFile();
    c << "Песня удалена!\n";
}

void modifySong() {
    cin.ignore();
    string title;
    c << "Введите название песни для редактирования: ";
    getline(cin, title);
    for (auto& song : catalog) {
        if (song[0] == title) {
            c << "Введите новый текст песни (окончание - пустая строка):\n";
            song[3] = "";
            string line;
            while (getline(cin, line) && !line.empty()) {
                song[3] += line + "\n";
            }
            saveCatalogToFile();
            c << "Текст обновлен!\n";
            return;
        }
    }
    c << "Песня не найдена!\n";
}

int main() {
    system("chcp 1251>null");
    loadCatalogFromFile();
    int choice;
    do {
        c << "\nМеню:\n1. Добавить песню\n2. Показать текст песни\n3. Найти песни по автору\n4. Найти песни по слову\n5. Удалить песню\n6. Изменить текст песни\n7. Выход\nВаш выбор: ";
        cin >> choice;
        switch (choice) {
        case 1: addSong(); break;
        case 2: displaySong(); break;
        case 3: searchByAuthor(); break;
        case 4: searchByWord(); break;
        case 5: deleteSong(); break;
        case 6: modifySong(); break;
        case 7: c << "Выход...\n"; break;
        default: c << "Неверный ввод!\n";
        }
    } while (choice != 7);
    return 0;
}