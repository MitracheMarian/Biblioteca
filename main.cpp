#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Carte {
private:
    string titlu;
    vector<string> autori;
    string editura;
    string isbn;
    int anAparitie;
    float pret;

public:
    Carte();
    Carte(string titlu, vector<string> autori, string editura, string isbn, int anAparitie, float pret);
    Carte(const Carte& other);
    void afisare();
    string getTitlu();
    string getEditura();
    string getIsbn() const;
    vector<string> getAutori();
};

Carte::Carte() : titlu(""), autori({}), editura(""), isbn(""), anAparitie(0), pret(0.0f) {}

Carte::Carte(string titlu, vector<string> autori, string editura, string isbn, int anAparitie, float pret) {
    this->titlu = titlu;
    this->autori = autori;
    this->editura = editura;
    this->isbn = isbn;
    this->anAparitie = anAparitie;
    this->pret = pret;
}

Carte::Carte(const Carte& other) {

    this->titlu = other.titlu;
    this->autori = other.autori;
    this->editura = other.editura;
    this->isbn = other.isbn;
    this->anAparitie = other.anAparitie;
    this->pret = other.pret;
}

void Carte::afisare() {
    cout << "------------------\n";
    cout << "Titlu: " << titlu << endl;
    cout << "Autori: ";
    for (const auto& autor : autori) {
        cout << autor << " ";
    }
    cout << "\nEditura: " << editura << endl;
    cout << "ISBN: " << isbn << endl;
    cout << "An Aparitie: " << anAparitie << endl;
    cout << "Pret: " << pret << endl;
    cout << "------------------\n\n";
}

string Carte::getTitlu() {
    return titlu;
}

string Carte::getEditura() {
    return editura;
}

string Carte::getIsbn() const {
    return isbn;
}

vector<string> Carte::getAutori() {
    return autori;
}

class Biblioteca {
private:
    vector<Carte> carti;
    set<string> isbnSet;

public:
    Biblioteca();
    Biblioteca(vector<Carte> carti);
    vector<Carte> cautaDupaTitlu(string);
    vector<Carte> cautaDupaEditura(string);
    Carte* cautaDupaISBN(string);
    bool adaugareCarte(const Carte& carteNoua);
};

bool Biblioteca::adaugareCarte(const Carte& carteNoua) {
    auto result = isbnSet.insert(carteNoua.getIsbn());
    if (result.second) {
        carti.push_back(carteNoua);
        return true;  // Carte adăugată cu succes
    }
    else {
        return false;  // ISBN duplicat
    }
}

Biblioteca::Biblioteca() {}

Biblioteca::Biblioteca(vector<Carte> carti) {
    this->carti = carti;
}

vector<Carte> Biblioteca::cautaDupaTitlu(string titlu) {
    vector<Carte> cartiGasite;
    for (int i = 0; i < carti.size(); i++) {
        if (carti[i].getTitlu() == titlu) {
            cartiGasite.push_back(carti[i]);
        }
    }
    return cartiGasite;
}

vector<Carte> Biblioteca::cautaDupaEditura(string editura) {
    vector<Carte> cartiGasite;
    for (int i = 0; i < carti.size(); i++) {
        if (carti[i].getEditura() == editura) {
            cartiGasite.push_back(carti[i]);
        }
    }
    return cartiGasite;
}

Carte* Biblioteca::cautaDupaISBN(string isbn) {
    for (int i = 0; i < carti.size(); i++) {
        if (carti[i].getIsbn() == isbn) {
            return &carti[i];
        }
    }
    return nullptr;
}

// Functie pentru a citi detalii despre o carte din consola
Carte citesteCarte() {
    string titlu, editura, isbn;
    int anAparitie;
    float pret;
    int nrAutori;
    vector<string> autori;
    string autor;

    cout << "Introduceti titlul cartii: ";
    getline(cin, titlu);

    cout << "Introduceti numarul de autori: ";
    cin >> nrAutori;
    cin.ignore();
    for (int i = 0; i < nrAutori; ++i) {
        cout << "Introduceti numele autorului " << i + 1 << ": ";
        getline(cin, autor);
        autori.push_back(autor);
    }

    cout << "Introduceti editura: ";
    getline(cin, editura);

    cout << "Introduceti ISBN: ";
    getline(cin, isbn);

    cout << "Introduceti anul aparitiei: ";
    cin >> anAparitie;
    cin.ignore();

    cout << "Introduceti pretul: ";
    cin >> pret;
    cin.ignore();

    return Carte(titlu, autori, editura, isbn, anAparitie, pret);
}

int main() {
    Biblioteca biblioteca;
    int optiune;

    do {
        cout << "\nMeniu:\n";
        cout << "1. Adauga o carte\n";
        cout << "2. Cauta o carte dupa titlu\n";
        cout << "3. Cauta o carte dupa ISBN\n";
        cout << "4. Cauta o carte dupa editura\n";
        cout << "5. Iesire\n";
        cout << "Alegeti o optiune: ";
        cin >> optiune;
        cin.ignore();  // Curatam buffer-ul

        if (optiune == 1) {
            Carte carteNoua = citesteCarte();
            if (biblioteca.adaugareCarte(carteNoua)) {
                cout << "Cartea a fost adaugata cu succes!\n";
            }
            else {
                cout << "Cartea cu acest ISBN exista deja!\n";
            }
        }
        else if (optiune == 2) {
            string titlu;
            cout << "Introduceti titlul: ";
            getline(cin, titlu);
            vector<Carte> carti = biblioteca.cautaDupaTitlu(titlu);
            if (!carti.empty()) {
                for (Carte& carte : carti) {
                    carte.afisare();
                }
            }
            else {
                cout << "Nicio carte cu acest titlu nu a fost gasita.\n";
            }
        }
        else if (optiune == 3) {
            string isbn;
            cout << "Introduceti ISBN-ul: ";
            getline(cin, isbn);
            Carte* carte = biblioteca.cautaDupaISBN(isbn);
            if (carte) {
                carte->afisare();
            }
            else {
                cout << "Nicio carte cu acest ISBN nu a fost gasita.\n";
            }
        }
        else if (optiune == 4) {
            string editura;
            cout << "Introduceti editura: ";
            getline(cin, editura);
            vector<Carte> carti = biblioteca.cautaDupaEditura(editura);
            if (!carti.empty()) {
                for (Carte& carte : carti) {
                    carte.afisare();
                }
            }
            else {
                cout << "Nicio carte de la aceasta editura nu a fost gasita.\n";
            }
        }
    } while (optiune != 5);

    cout << "Program terminat.\n";
    return 0;
}