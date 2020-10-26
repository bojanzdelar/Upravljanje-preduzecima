#include "Podaci.h"

void popuniPreduzeca(KolekcijaPreduzeca &kolekcijaPreduzeca, const KolekcijaOdeljenja &kolekcijaOdeljenja) {
    for (Preduzece *preduzece : kolekcijaPreduzeca.getPreduzeca()) {
        for (Odeljenje *odeljenje : kolekcijaOdeljenja.getOdeljenja()) {
            if (preduzece->getNaziv() == odeljenje->getPreduzece()) {
                preduzece->getOdeljenja()->push_back(odeljenje);
            }
        }
    }
}

void popuniOdeljenja(KolekcijaOdeljenja &kolekcijaOdeljenja, const KolekcijaRadnika &KolekcijaRadnika) {
    for (Odeljenje *odeljenje : kolekcijaOdeljenja.getOdeljenja()) {
        for (Radnik *radnik : KolekcijaRadnika.getRadnici()) {
            // Dodela zaposlenog odeljenju
            if (odeljenje->getId() == radnik->getOdeljenje()) {
                odeljenje->getZaposleni()->push_back(radnik);
            }
            // Dodela sefa odeljenju
            if (odeljenje->getSef()->getId() == radnik->getId()) {
                odeljenje->setSef(radnik);
            }
        }
    }
}

void dodeliNadredjene(KolekcijaRadnika &kolekcijaRadnika) {
    for (Radnik *sef : kolekcijaRadnika.getRadnici()) {
        for (Radnik *radnik : kolekcijaRadnika.getRadnici()) {
            if (sef->getId() == radnik->getIdNadredjeni()) {
                radnik->setNadredjeni(sef);
            }
        }
    }

}

void dodeliNagrade(KolekcijaRadnika &kolekcijaRadnika, const KolekcijaNagrada &kolekcijaNagrada) {
    for (Radnik *radnik : kolekcijaRadnika.getRadnici()) {
        for (Nagrada *nagrada : kolekcijaNagrada.getNagrade()) {
            if (radnik->getId() == nagrada->getRadnikId()) {
                radnik->getNagrade()->push_back(nagrada);
            }
        }
    }
}

void poveziPodatke(KolekcijaPreduzeca &kolekcijaPreduzeca, KolekcijaOdeljenja &kolekcijaOdeljenja,
         KolekcijaRadnika &kolekcijaRadnika, KolekcijaNagrada &kolekcijaNagrada) {
    popuniPreduzeca(kolekcijaPreduzeca, kolekcijaOdeljenja);
    popuniOdeljenja(kolekcijaOdeljenja, kolekcijaRadnika);
    dodeliNadredjene(kolekcijaRadnika);
    dodeliNagrade(kolekcijaRadnika, kolekcijaNagrada);
}

void procitajPodatke(KolekcijaPreduzeca &kolekcijaPreduzeca, KolekcijaOdeljenja &kolekcijaOdeljenja,
        KolekcijaRadnika &kolekcijaRadnika, KolekcijaNagrada &kolekcijaNagrada) {
    ifstream input("podaci.txt");
    input >> kolekcijaPreduzeca;
    input >> kolekcijaOdeljenja;
    input >> kolekcijaRadnika;
    input >> kolekcijaNagrada;
    input.close();
}

void ispisiPodatke(KolekcijaPreduzeca &kolekcijaPreduzeca, KolekcijaOdeljenja &kolekcijaOdeljenja,
        KolekcijaRadnika &kolekcijaRadnika, KolekcijaNagrada &kolekcijaNagrada) {
    ofstream output("test.txt"); // privremeno
    output << kolekcijaPreduzeca;
    output << kolekcijaOdeljenja;
    output << kolekcijaRadnika;
    output << kolekcijaNagrada;
    output.close();
}