#include <iostream>
#include <vector>
#include <algorithm>
#include "Nagłówek.h"
#include <list>
#include <random>

using namespace std;

Zbior convertToZbior(double gornaGranica) {
    return Zbior(0, 0, gornaGranica);
}

int main() 
{
    std::vector<double> listaElementow = { 1.0, 2.5, 3.0, 4.2, 5.8, 6.7, 7.9, 8.3, 9.6, 10.0 };
    std::vector<Zbior> wektorZbiorow;

    // Wypełnianie wektora instancjami klasy Zbior przy użyciu konwersji z double
    for (const auto& elem : listaElementow) {
        wektorZbiorow.push_back(convertToZbior(elem));
    }

    // Tworzenie funktora na bazie instancji typu Zbior
    Zbior referencyjnyZbior(5, 0, 10);  // Przykładowy referencyjny zbiór
    Functor functor(referencyjnyZbior, 1e-1);

    // Przykład użycia funktora z funkcją z biblioteki <algorithm>
    auto it = std::find_if(wektorZbiorow.begin(), wektorZbiorow.end(), functor);

    if (it != wektorZbiorow.end()) {
        std::cout << "Znaleziono zbior blisko sredniej referencyjnej." << std::endl;
    }
    else {
        std::cout << "Nie znaleziono zbioru blisko sredniej referencyjnej." << std::endl;
    }



}