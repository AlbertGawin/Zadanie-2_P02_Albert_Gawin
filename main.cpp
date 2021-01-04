#include <iostream>
#include <fstream>
#include <ctime>
#include <conio.h>
#include <chrono>

struct Zegar
{
    std::chrono::time_point<std::chrono::high_resolution_clock> _start, _end;
    std::chrono::duration<float> czas;

    Zegar()
    {
        _start = std::chrono::high_resolution_clock::now();
        czas = std::chrono::seconds(0);
    }

    ~Zegar()
    {
        _end = std::chrono::high_resolution_clock::now();
        czas = _end - _start;

        float ms = czas.count() * 1000.f;
        std::cout << "Skrypt potrzebowal " << ms << "ms\n\n";
    }
};

class Tablica
{
public:
    int* dane;
    int dlugosc;

    Tablica(int N)
    {
        dlugosc = N;
        dane = new int[dlugosc];
    }

    ~Tablica()
    {
        delete[] dane;
    }

    void sortujBabelkowo()
    {
        // Liczy czas wykonania funkcji
        Zegar zegar;

        for (int i = 0; i < dlugosc - 1; i++)
        {
            for (int j = i + 1; j < dlugosc; j++)
            {
                if (dane[i] > dane[j])
                    std::swap(dane[i], dane[j]);
            }
        }
    }

    void sortujPrzezZliczanie()
    {
        // Liczy czas wykonania funkcji
        Zegar zegar;

        int* licznik = new int[dlugosc + 1];

        // Wypelnienie tablicy liczników zerami
        for (int i = 0; i < dlugosc + 1; i++)
            licznik[i] = 0;

        // Zwiekszanie liczników
        for (int i = 0; i < dlugosc; i++)
            licznik[dane[i]]++;

        // Sortowanie tablicy
        int k = 0;
        for (int i = 0; i < dlugosc + 1; i++)
        {
            if (licznik[i] > 0)
            {
                for (int j = 0; j < licznik[i]; j++)
                {
                    dane[k] = i;
                    k++;
                }
            }
        }

        delete[] licznik;
    }
};

void OdczytajDaneZPlikuDoTablicy(Tablica &tab, std::string sciezka)
{
    std::fstream plik(sciezka, std::ios::in);
    bool isEmpty = plik.peek() == std::ifstream::traits_type::eof();

    if (plik.good() && !isEmpty)
    {
        for (int i = 0; i < tab.dlugosc; i++)
        {
            plik >> tab.dane[i];
        }
    }
    else
    {
        std::cout << "Plik nie istnieje lub podano zla sciezke" << std::endl;
        plik.close();
    }
    plik.close();
}

void ZapiszTabliceDoPliku(Tablica &tab, std::string sciezka)
{
    std::fstream plik;
    plik.open(sciezka, std::ios::out);

    if (plik.good())
    {
        for (int i = 0; i < tab.dlugosc; i++)
        {
            plik << tab.dane[i] << " ";
        }
    }
    else
    {
        std::cout << "Plik nie istnieje lub podano zla sciezke" << std::endl;
        plik.close();
    }

    plik.close();
}

int main()
{
    int N = 0;
    std::cout << "Podaj N: ";   std::cin >> N;
    Tablica tab(N);

    srand((unsigned int)time(NULL));
    for (int i = 0; i < N; i++)
    {
        tab.dane[i] = rand() % (N + 1);
    }
    ZapiszTabliceDoPliku(tab, "tablice/1.txt");

    tab.sortujBabelkowo();

    OdczytajDaneZPlikuDoTablicy(tab, "tablice/1.txt");

    tab.sortujPrzezZliczanie();

    ZapiszTabliceDoPliku(tab, "wyniki/wynik1.txt");

    system("pause");
}
