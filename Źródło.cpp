#include "Nag³ówek.h"
#include <random>

void Zbior::alokuj(int n)
{
	if (n > 0)
	{
		m_elementy = new(std::nothrow) double[n];
		m_liczbaElementow = n;
	}
}

void Zbior::zwolnij()
{
	if (m_elementy != nullptr)
	{
		delete[] m_elementy;
		m_elementy = nullptr;
	}
}


Zbior::Zbior(size_t liczbaElementow, double gornaGranica)
{

	Zbior nowyZbior(liczbaElementow, 0, gornaGranica);

	std::random_device generator;
	std::uniform_real_distribution<double> zakres(0, gornaGranica);
	for (int elem = 0; elem < liczbaElementow; elem++)
	{
		nowyZbior.m_elementy[0] = zakres(generator);
	}

}

Zbior::Zbior(Zbior&& element)
	:m_liczbaElementow(element.m_liczbaElementow), m_dolnaGranica(element.m_dolnaGranica), m_gornaGranica(element.m_gornaGranica)
{
	this->m_elementy = element.m_elementy;
	element.m_elementy = nullptr;
}

double Zbior::getSrednia() const {
	if (m_liczbaElementow == 0) {
		return 0.0;  // Zabezpieczenie przed dzieleniem przez zero
	}

	double suma = 0.0;
	for (size_t i = 0; i < m_liczbaElementow; ++i) {
		suma += m_elementy[i];
	}

	return suma / m_liczbaElementow;
}

ostream& operator<<(ostream& os, const Zbior& zbior) {
	os << "Zbior(" << zbior.getDolnaGranica() << " - " << zbior.getGornaGranica() << "): ";
	for (size_t i = 0; i < zbior.getLiczbaElementow(); ++i) {
		os << zbior.getElement()[i] << " ";
	}
	return os;