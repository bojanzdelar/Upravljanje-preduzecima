#include "GrupaNagrada.h"

GrupaNagrada::GrupaNagrada(int x, int y, int w, int h, Kolekcije *kolekcije, const char *label) 
: Fl_Group(x, y, w, h, label), kolekcije(kolekcije) {
    tabela = new Tabela<Nagrada*>(x + 10, y + 10, 700, 415, &kolekcije->nagrade);
    radnik = new Fl_Input(x + 800, y + 10, 150, 30, "Radnik:");
    procenti = new Fl_Int_Input(x + 800, y + 50, 150, 30, "Procenti:");
    procenti->maximum_size(2);
    brojMeseci = new Fl_Int_Input(x + 800, y + 90, 150, 30, "Broj meseci\ntrajanja:");
    brojMeseci->maximum_size(1);
    dodajButton = new Fl_Button(x + 750, y + 140, 80, 40, "Dodaj");
    dodajButton->callback(dodaj, this);
    prikaziButton = new Fl_Button(x + 840, y + 140, 80, 40, "Prikazi");
    prikaziButton->callback(prikazi, this);
    izmeniButton = new Fl_Button(x + 930, y + 140, 80, 40, "Izmeni");
    izmeniButton->callback(izmeni, this);
    ukloniButton = new Fl_Button(x + 1020, y + 140, 80, 40, "Ukloni");
    ukloniButton->callback(ukloni, this);
    end();
}

GrupaNagrada::~GrupaNagrada() {

}

void GrupaNagrada::dodaj(Fl_Widget *widget, void *data) {
    GrupaNagrada *grupa = (GrupaNagrada*) data;
    string radnikId = grupa->radnik->value();
    string procenti = grupa->procenti->value();
    string brojMeseci = grupa->brojMeseci->value();
    if (radnikId == "" || procenti == "" || brojMeseci == "" || procenti.find("-") != string::npos || brojMeseci.find("-") != string::npos
            || !grupa->kolekcije->radnici.idZauzet(radnikId)) {
        fl_alert("Niste ispunili zahteve za izvrsavanje funkcije");
        return;
    }
    Radnik *radnik = grupa->kolekcije->radnici.dobaviId(radnikId);
    Nagrada *nagrada = new Nagrada(radnik, stoi(procenti), stoi(brojMeseci));
    grupa->kolekcije->nagrade.dodaj(nagrada);
    radnik->dodajNagradu(nagrada);
    grupa->azuriraj();
}

void GrupaNagrada::prikazi(Fl_Widget *widget, void *data) {
    GrupaNagrada *grupa = (GrupaNagrada*) data;
    int red = grupa->tabela->izabraniRed();
    if (red == -1) {
        fl_alert("Niste ispunili zahteve za izvrsavanje funkcije");
        return;
    }
    Nagrada *nagrada = grupa->kolekcije->nagrade.dobavi(red);
    grupa->radnik->value(nagrada->getRadnik()->getId().c_str());
    ostringstream out;
    out << nagrada->getProcenti();
    grupa->procenti->value(out.str().c_str());
    out.str("");
    out << nagrada->getBrojMeseci();
    grupa->brojMeseci->value(out.str().c_str());
}

void GrupaNagrada::izmeni(Fl_Widget *widget, void *data) {
    GrupaNagrada *grupa = (GrupaNagrada*) data;
    string radnikId = grupa->radnik->value();
    string procenti = grupa->procenti->value();
    string brojMeseci = grupa->brojMeseci->value();
    int red = grupa->tabela->izabraniRed();
    if (radnikId == "" || procenti == "" || brojMeseci == "" || procenti.find("-") != string::npos || brojMeseci.find("-") != string::npos
            || !grupa->kolekcije->radnici.idZauzet(radnikId) || red == -1) {
        fl_alert("Niste ispunili zahteve za izvrsavanje funkcije");
        return;
    }
    Nagrada *nagrada = grupa->kolekcije->nagrade.dobavi(red);
    nagrada->getRadnik()->ukloniNagradu(nagrada);
    nagrada->setRadnik(grupa->kolekcije->radnici.dobaviId(radnikId));
    nagrada->getRadnik()->dodajNagradu(nagrada);
    nagrada->setProcenti(stoi(procenti));
    nagrada->setBrojMeseci(stoi(brojMeseci));
    grupa->azuriraj();
}

void GrupaNagrada::ukloni(Fl_Widget *widget, void *data) {
    GrupaNagrada *grupa = (GrupaNagrada*) data;
    int red = grupa->tabela->izabraniRed();
    if (red == -1) {
        fl_alert("Niste ispunili zahteve za izvrsavanje funkcije");
        return;
    }
    Nagrada *nagrada = grupa->kolekcije->nagrade.dobavi(red);
    grupa->kolekcije->ukloniNagradu(nagrada);
    delete nagrada;
    grupa->azuriraj();
}

void GrupaNagrada::azuriraj() {
    tabela->azuriraj();
}