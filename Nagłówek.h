#pragma once
using namespace std;
class Zbior
{
	size_t m_liczbaElementow = 0;
	double* m_elementy = nullptr;
	double m_dolnaGranica = 0;
	double m_gornaGranica = 0;
	void alokuj(int);
	void zwolnij();
public:
	Zbior(size_t liczElem, double dGran, double gGran);
	~Zbior() { zwolnij(); }

	//przenoszenie
	Zbior(Zbior&& element);

	Zbior& operator=(Zbior&& element) = delete;

	//kopiowanie
	Zbior(const Zbior& element) = delete;

	Zbior& operator=(const Zbior& element) {
		if (this != &element) {
			bool roznyRozmiar = this->m_liczbaElementow != element.m_liczbaElementow;
			if (this->m_elementy != nullptr && roznyRozmiar) {
				zwolnij();
			}
			if (element.m_elementy != nullptr) {
				if (roznyRozmiar) {
					alokuj(element.m_liczbaElementow);
				}

				for (int i = 0; i < element.m_liczbaElementow; i++) {
					this->m_elementy[i] = element.m_elementy[i];
				}
			}
			this->m_liczbaElementow = element.m_liczbaElementow;
		}
		return *this;
	}

	Zbior(size_t liczbaElementow, double gornaGranica);
	size_t getLiczbaElementow() const { return m_liczbaElementow; }
	friend Zbior convertToZbior(double gornaGranica);


	double getElement(size_t index) const 
	{ return m_elementy[index]; }

	double getDolnaGranica() const 
	{ return m_dolnaGranica; }

	double getGornaGranica() const 
	{ return m_gornaGranica; }

	double getSrednia() const;

	friend ostream& operator<<(ostream& os, const Zbior& zbior);
};

ostream& operator<<(ostream& os, const Zbior& zbior);

class Functor {
private:
	Zbior referencyjny;
	double tolerance;

public:
	Functor(const Zbior& ref, double tol) : referencyjny(ref), tolerance(tol) {}

	bool operator()(const Zbior& zbior) const {
		// Sprawdzenie czy œrednia zbioru jest zbli¿ona do œredniej referencyjnego zbioru
		double sredniaZbioru = 0;
		for (size_t i = 0; i < zbior.getLiczbaElementow(); ++i) {
			sredniaZbioru += zbior.getElement(i);
		}
		sredniaZbioru /= zbior.getLiczbaElementow();

		double roznica = std::abs(sredniaZbioru - referencyjny.getSrednia());
		return roznica <= tolerance;
	}
};
