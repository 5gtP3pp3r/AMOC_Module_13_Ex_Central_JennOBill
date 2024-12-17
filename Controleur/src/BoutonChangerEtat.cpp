#include "BoutonChangerEtat.h"

BoutonChangerEtat::BoutonChangerEtat(
    uint8_t p_pin,
    uint8_t p_delaiActionMS,
    ActionChangerEtat* p_actionChangerEtat
) :
    m_pin(p_pin),
    m_delaiActionMS(p_delaiActionMS),
    m_actionChangerEtat(p_actionChangerEtat),
    m_etatBouton(HIGH),
    m_dernierEtatBouton(HIGH),
    m_dernierEtatStable(HIGH),
    m_tempsActuel(DEFAUT),
    m_dernierChangementTemps(DEFAUT) {
        pinMode(this->m_pin,INPUT);
    }

void BoutonChangerEtat::tick() {
    this->m_etatBouton = digitalRead(this->m_pin);
    this->m_tempsActuel = millis();
    if (this->m_etatBouton != this->m_dernierEtatBouton) {
        this->m_dernierChangementTemps = this->m_tempsActuel;
        this->m_dernierEtatStable = this->m_etatBouton;
    }
    if (this->m_tempsActuel - this->m_dernierChangementTemps > this->m_delaiActionMS) {
        if (this->m_dernierEtatStable == LOW && this->m_etatBouton == HIGH) {
            m_actionChangerEtat->executer();
        }
        this->m_dernierEtatStable = this->m_etatBouton;
    }
}