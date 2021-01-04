#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>

using namespace std;

struct Timer
{
    std::chrono::time_point<std::chrono::high_resolution_clock> _start, _end;
    std::chrono::duration<float> duration;

    Timer()
    {
        _start = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        _end = std::chrono::high_resolution_clock::now();
        duration = _end - _start;

        float ms = duration.count() * 1000.f;
        cout << "Skrypt potrzebowal " << ms << "ms\n\n";
    }
};

int* getArrayFromFile(string path)
{
    fstream file(path, ios::in);
    bool isEmpty = file.peek() == std::ifstream::traits_type::eof();

    int* _array;

    // Sprawdz czy plik poprawnie otwarty oraz czy nie jest pusty
    if(file.good() && !isEmpty)
    {
        int i = 0;
        while (file >> _array[i])
        {
            i++;
        }
    }
    else
    {
        file.close();
        return 0;
    }
    file.close();

    return _array;
}

void SortowanieBabelkowe(int* tab, int N)
{
    // Liczy czas wykonania funkcji
    Timer timer;

    // Utworzenie kopii listy
    int tabCopy[N];
    for (int i = 0; i < N; i++)
    {
        tabCopy[i] = tab[i];
    }

    for (int i = 0; i < N-1; i++)
    {
        for (int j = i+1; j < N; j++)
        {
            if (tabCopy[i] > tabCopy[j])
                swap(tabCopy[i], tabCopy[j]);
        }
    }
}

void SortowaniePrzezZliczanie(int* tab, int N, int _MIN, int _MAX)
{
    // Liczy czas wykonania funkcji
    Timer timer;

    // Utworzenie kopii listy
    int tabCopy[N];
    for (int i = 0; i < N; i++)
    {
        tabCopy[i] = tab[i];
    }

    int licznik[_MAX - _MIN + 1];

    // Wypelnienie tablicy liczników zerami
    for (int i = _MIN; i <= _MAX; i++)
        licznik[i] = 0;

    // Zwiekszanie liczników
    for (int i = 0; i < N; i++)
        licznik[tabCopy[i]]++;

    // Sortowanie tablicy
    int k = 0;
    for (int i = 0; i < _MAX - _MIN + 1; i++)
    {
        if (licznik[i] > 0)
        {
            for (int j = 0; j < licznik[i]; j++)
            {
                tabCopy[k] = i;
                k++;
            }
        }
    }
}

int main()
{
    int N = 200000, _MIN = 0, _MAX = 100;
    int tab[N];

    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        tab[i] = _MIN + rand() % (_MAX - _MIN);
    }

    SortowanieBabelkowe(tab, N);
    SortowaniePrzezZliczanie(tab, N, _MIN, _MAX);

    int tab* = getArrayFromFile("tablice/1.txt");
    for (int i=0; i<sizeof(tab)/sizeof(typeof(int)); i++)
    {
}

    std::cin.get();

    return 0;
}
