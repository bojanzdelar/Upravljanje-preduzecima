#include "GrupaOdeljenja.h"

GrupaOdeljenja::GrupaOdeljenja(int x, int y, int w, int h, Kolekcije *kolekcije, const char *label) 
: Fl_Group(x, y, w, h, label), kolekcije(kolekcije) {
    tabela = new Tabela<Odeljenje*>(x + 10, y + 10, 700, 415, &kolekcije->odeljenja);
    id = new Fl_Input(x + 800, y + 10, 150, 30, "ID:");
    naziv = new Fl_Input(x + 800, y + 50, 150, 30, "Naziv:");
    sef = new Fl_Input(x + 800, y + 90, 150, 30, "Sef:");
    preduzece = new Fl_Int_Input(x + 800, y + 130, 150, 30, "Preduzece:");
    preduzece->maximum_size(8);
    dodajButton = new Fl_Button(x + 750, y + 180, 80, 40, "Dodaj");
    dodajButton->callback(dodaj, this);
    prikaziButton = new Fl_Button(x + 840, y + 180, 80, 40, "Prikazi");
    prikaziButton->callback(prikazi, this);
    izmeniButton = new Fl_Button(x + 930, y + 180, 80, 40, "Izmeni");
    izmeniButton->callback(izmeni, this);
    ukloniButton = new Fl_Button(x + 1020, y + 180, 80, 40, "Ukloni");
    ukloniButton->callback(ukloni, this);
    end();
}

GrupaOdeljenja::~GrupaOdeljenja() {
    
}

void GrupaOdeljenja::dodaj(Fl_Widget *widget, void *data) {
    GrupaOdeljenja *grupa = (GrupaOdeljenja*) data;
    string id = grupa->id->value();
    string naziv = grupa->naziv->value();
    string sef = grupa->sef->value();
    string preduzece = grupa->preduzece->value();
    if (id == "" || naziv == "" || preduzece == "" 
            || grupa->kolekcije->odeljenja.idZauzet(id) 
            || (!grupa->kolekcije->radnici.idZauzet(sef) && sef != "") // moguce je kreirati odeljenje bez sefa, pa ga kasnije dodeliti
            || !grupa->kolekcije->preduzeca.maticniBrojZauzet(stoi(preduzece))) {
        fl_alert("Niste ispunili zahteve za izvrsavanje funkcije");
        return;
    }
    Odeljenje *odeljenje = new Odeljenje(id, naziv, (sef != "" ) ? grupa->kolekcije->radnici.dobaviId(sef) : nullptr, grupa->kolekcije->preduzeca.dobaviId(stoi(preduzece)));
    grupa->kolekcije->odeljenja.dodaj(odeljenje);
    odeljenje->getPreduzece()->dodajOdeljenje(odeljenje);
    grupa->azuriraj();
}

void GrupaOdeljenja::prikazi(Fl_Widget *widget, void *data) {
    GrupaOdeljenja *grupa = (GrupaOdeljenja*) data;
    int red = grupa->tabela->izabraniRed();
    if (red == -1) {
        fl_alert("Niste ispunili zahteve za izvrsavanje funkcije");
        return;
    }
    Odeljenje *odeljenje = grupa->kolekcije->odeljenja.dobavi(red);
    grupa->id->value(odeljenje->getId().c_str());
    grupa->naziv->value(odeljenje->getNaziv().c_str());
    Radnik *sef = odeljenje->getSef(); // provera da li odeljenja ima sefa
    grupa->sef->value((sef != nullptr ? sef->getId() : "").c_str());
    ostringstream out;
    out << odeljenje->getPreduzece()->getMaticniBroj();
    grupa->preduzece->value(out.str().c_str());
}

void GrupaOdeljenja::izmeni(Fl_Widget *widget, void *data) {
    GrupaOdeljenja *grupa = (GrupaOdeljenja*) data;
    string id = grupa->id->value();
    string naziv = grupa->naziv->value();
    string sef = grupa->sef->value();
    string preduzece = grupa->preduzece->value();
    int red = grupa->tabela->izabraniRed();
    if (id == "" || naziv == "" || preduzece == "" || red == -1
            || (id != grupa->kolekcije->odeljenja.dobavi(red)->getId() && grupa->kolekcije->odeljenja.idZauzet(id))
            || (!grupa->kolekcije->radnici.idZauzet(sef) && sef != "") 
            || !grupa->kolekcije->preduzeca.maticniBrojZauzet(stoi(preduzece))) {
        fl_alert("Niste ispunili zahteve za izvrsavanje funkcije");
        return;
    }
    Odeljenje *odeljenje = grupa->kolekcije->odeljenja.dobavi(red);
    odeljenje->setId(id);
    odeljenje->setNaziv(naziv);
    odeljenje->setSef(grupa->kolekcije->radnici.dobaviId(sef));
    odeljenje->getPreduzece()->ukloniOdeljenje(odeljenje); // brisanje iz starog preduzeca
    odeljenje->setPreduzece(grupa->kolekcije->preduzeca.dobaviId(stoi(preduzece)));
    odeljenje->getPreduzece()->dodajOdeljenje(odeljenje); // dodavanje u novo preduzece
    grupa->azuriraj();
}

void GrupaOdeljenja::ukloni(Fl_Widget *widget, void *data) {
    GrupaOdeljenja *grupa = (GrupaOdeljenja*) data;
    int red = grupa->tabela->izabraniRed();
    if (red == -1) {
        fl_alert("Niste ispunili zahteve za izvrsavanje funkcije");
        return;
    }
    Odeljenje *odeljenje = grupa->kolekcije->odeljenja.dobavi(red);
    grupa->kolekcije->ukloniOdeljenje(odeljenje);
    delete odeljenje;
    grupa->azuriraj();
}

void GrupaOdeljenja::azuriraj() {
    tabela->azuriraj();
}