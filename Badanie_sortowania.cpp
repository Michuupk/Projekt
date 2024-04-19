#include <iostream>
#include <cstdlib>
#include <chrono>
#include <fstream>

using namespace std;

const unsigned long long WielkoscTablicy = 300; // określanie rozmiaru tablicy
unsigned int zakres_losowania = 100;     // zakres losowania
int Tablica_org[WielkoscTablicy];        // tworzenie tablicy o określonym rozmiarze
int Tablica[WielkoscTablicy];            // tworzenie tablicy o określonym rozmiarze
int temp_tab[WielkoscTablicy];

auto start = 0, end = 0;
unsigned short i = 0, n = 0;
int ilerazy, theend = 1;
short memo, sort = 0;
bool check;

void Losowanie_Tablicy()
{
    srand(time(0)); // seed dla funkcji rand()
    unsigned int random;
    for (i = 0; i < WielkoscTablicy; i++)
    {
        random = rand() % zakres_losowania; // losowanie liczby w zakresie modulo
        Tablica_org[i] = random;            // wpisywanie wylosowanych wartości do tablicy
        Tablica[i] = random;
    }
}

void Przywracanie_Tablicy()
{
    for (i = 0; i < WielkoscTablicy; i++)
    {
        Tablica[i] = Tablica_org[i];
    }
}

void Sortowanie_Przez_Wybor(int tab[]) // sortowanie przez wybór
{
    short min, max, temp;
    for (i = 0; i < WielkoscTablicy - 1; i++)
    {
        min = i;
        for (n = i + 1; n < WielkoscTablicy; n++) // sortowanie po minimum
        {
            if (tab[min] > tab[n])
            {
                min = n;
            }
        }

        temp = tab[i]; // zamiana miejsc min
        tab[i] = tab[min];
        tab[min] = temp;

        max = WielkoscTablicy - 1 - i;
        for (n = WielkoscTablicy - 1 - i; n > 0; n--) // sortowanie po maximum
        {
            if (tab[max] < tab[n])
            {
                max = n;
            }
        }

        temp = tab[WielkoscTablicy - 1 - i]; // zamiana miejsc max
        tab[WielkoscTablicy - 1 - i] = tab[max];
        tab[max] = temp;
    }
}
void Sortowanie_Przez_Wstawianie(int tab[]) // sortowanie przez wstaiwanie
{
    for (int i = 1; i < WielkoscTablicy; i++)
    {
        while (i > 0 && tab[i - 1] > tab[i])
        {
            memo = tab[i - 1];
            tab[i - 1] = tab[i];
            tab[i] = memo;
            i--;
        }
    }
}
void Sortowanie_Babelkowe(int tab[]) // sortowanie bąbelkowe
{
    int min = 0;
    int max = WielkoscTablicy - 1;
    int zmiana;
    do
    {
        zmiana = -1;
        for (i = min; i < max; i++)
        {
            if (tab[i] > tab[i + 1])
            {
                memo = tab[i];
                tab[i] = tab[i + 1];
                tab[i + 1] = memo;
                if (zmiana < 0)
                {
                    min = i; // indeks pierwszej zmiany jako nowy początek pętli
                }
                zmiana = i; // indeks zmiany jako wartość logiczna
            }
        }

        if (min)
            min--; // porównywanie poprzedniej liczbę wcześniej ze zbioru
        max = zmiana;
    } while (zmiana >= 0);
}

void merge(int tab[], int poczatek, int srodek, int koniec)
{
    for (i = poczatek; i <= koniec; i++)
    {
        temp_tab[i] = tab[i];
    }
    int k = poczatek;
    i = poczatek;
    n = srodek + 1;
    while (i <= srodek && n <= koniec)
    {
        if (temp_tab[i] <= temp_tab[n])
        {
            tab[k] = temp_tab[i++];
            k++;
        }
        else
        {
            tab[k] = temp_tab[n++];
            k++;
        }
    }

    while (i <= srodek)
    {
        tab[k] = temp_tab[i++];
        k++;
    }

    while (n <= koniec)
    {
        tab[k] = temp_tab[n++];
        k++;
    }
}

void Sortowanie_Przez_Scalanie(int tab[], int poczatek, int koniec)
{

    if (poczatek >= koniec)
        return;

    int srodek = (poczatek + koniec) / 2;

    Sortowanie_Przez_Scalanie(tab, poczatek, srodek);
    Sortowanie_Przez_Scalanie(tab, srodek + 1, koniec);

    merge(tab, poczatek, srodek, koniec);
}

void Sortowanie_Szybkie(int tab[], int poczatek, int koniec)
{
    ;
}


bool Sprawdz_Sortowanie(int tab[]) // sprawdzanie sortowania
{
    check = true;

    for (n = 0; n <= WielkoscTablicy - 2; n++)
    {

        for (i = n + 1; i <= WielkoscTablicy - 1; i++)
        {
            if (tab[n] > tab[i]) // porównywanie najmniejszego elementu do wszystkich pozostałych
            {
                check = false;
            }
        }
    }
    return check;
}

void Wypisz_Tablice(int tab[]) // wypisywanie całej tablicy
{
    for (i = 0; i < WielkoscTablicy; i++)

    {
        cout << tab[i] << " ";
    }

    cout << endl;
}

int main()
{
    ofstream wyniki;
    string Nazwy_wynikow[5] = {"Przez_Wybor", "Przez_Wstawianie", "Babelkowe", "Przez_Scalanie", "QuickSort"};

    int max_wykon = 4;

    //cout << "Wpisz zakres losowania %";
    // cin>>zakres_losowania;
    wyniki.open("AiZO.txt", ios::app);

    while (theend != 0)
    {
        cout << "------ MENU--------\n"; // *MENU*
        cout << "Wybierz sortowanie:\n";
        cout << "Przez wybór -> 1\n";
        cout << "Przez wstawianie -> 2\n";
        cout << "Bąbelkowe -> 3\n";
        cout << "Przez scalanie -> 4\n";
        cout << "Szybkie -> 5\n";

        cout << "Ile razy? \n"; // *Pętla ile razy*
        cin >> ilerazy;
        cout << endl;

        cout << "Sortowanie: \n";
        
        if (wyniki.is_open())
        {
            wyniki << "Przez wybór;Przez Wstawianie;Bąbelkowe;PrzezScalanie;QuickSort" << endl;
        }
        for (ilerazy; ilerazy > 0; ilerazy--)
        {
            Losowanie_Tablicy();
            cout<< "Wykonanie "<<endl;

                // cout<<"Przed sort "<<endl;
                // Wypisz_Tablice(Tablica);

                chrono::time_point<std::chrono::high_resolution_clock> start, end;
                start = chrono::high_resolution_clock::now();
                    Sortowanie_Przez_Wybor(Tablica);
                end = chrono::high_resolution_clock::now();
                chrono::duration<long double> t1{end - start};
                cout << "Wynik sprawdzania (1 - poprawne; 0 - niepoprawne) == " << Sprawdz_Sortowanie(Tablica) << endl;
                cout << t1.count() << "s\n";
                if (wyniki.is_open())   
                {
                    cout << "Udało się otworzyć plik" << endl;
                    wyniki << t1.count() << ";";
                }
                else
                {
                    cout << "Nie udało się otworzyć pliku" << endl;
                }
                Przywracanie_Tablicy();


                start = chrono::high_resolution_clock::now();
                    Sortowanie_Przez_Wstawianie(Tablica);
                end = chrono::high_resolution_clock::now();
                chrono::duration<long double> t2{end - start};
                cout << "Wynik sprawdzania (1 - poprawne; 0 - niepoprawne) == " << Sprawdz_Sortowanie(Tablica) << endl;
                cout << t2.count() << "s\n";
                if (wyniki.is_open())   
                {
                    cout << "Udało się otworzyć plik" << endl;
                    wyniki << t2.count() << ";";
                }
                else
                {
                    cout << "Nie udało się otworzyć pliku" << endl;
                }
                Przywracanie_Tablicy();



                start = chrono::high_resolution_clock::now();
                    Sortowanie_Babelkowe(Tablica);
                end = chrono::high_resolution_clock::now();
                chrono::duration<long double> t3{end - start};
                cout << "Wynik sprawdzania (1 - poprawne; 0 - niepoprawne) == " << Sprawdz_Sortowanie(Tablica) << endl;
                cout << t3.count() << "s\n";
                if (wyniki.is_open())   
                {
                    cout << "Udało się otworzyć plik" << endl;
                    wyniki << t3.count() << ";";
                }
                else
                {
                    cout << "Nie udało się otworzyć pliku" << endl;
                }
                Przywracanie_Tablicy();


                start = chrono::high_resolution_clock::now();
                    Sortowanie_Przez_Scalanie(Tablica, 0, WielkoscTablicy - 1);
                end = chrono::high_resolution_clock::now();
                chrono::duration<long double> t4{end - start};
                cout << "Wynik sprawdzania (1 - poprawne; 0 - niepoprawne) == " << Sprawdz_Sortowanie(Tablica) << endl;
                cout << t4.count() << "s\n";
                if (wyniki.is_open())   
                {
                    cout << "Udało się otworzyć plik" << endl;
                    wyniki << t4.count() << ";";
                }
                else
                {
                    cout << "Nie udało się otworzyć pliku" << endl;
                }
                Przywracanie_Tablicy();


                // start = chrono::high_resolution_clock::now();
                //     Sortowanie_Szybkie(Tablica, 0, WielkoscTablicy - 1);
                // end = chrono::high_resolution_clock::now();
                // chrono::duration<long double> t5{end - start};
                // cout << "Wynik sprawdzania (1 - poprawne; 0 - niepoprawne) == " << Sprawdz_Sortowanie(Tablica) << endl;
                // cout << t5.count() << "s\n";
                // if (wyniki.is_open())   
                // {
                //     cout << "Udało się otworzyć plik" << endl;
                //     wyniki << t5.count() << ";";
                // }
                // else
                // {
                //     cout << "Nie udało się otworzyć pliku" << endl;
                // }
                // Przywracanie_Tablicy();


                //  wyniki<<endl;
                //  cout<<"Po sort "<<endl;
                //  Wypisz_Tablice(Tablica);

            
                wyniki<<endl;
        }

        cout << "Czy zakończyć?\n";
        cout << "0 - aby zakończyć | 1 - aby kontynuwać\n";
        cin >> theend;
        cout << "No to jeszcze raz";
    }
    wyniki.close();

    // Wypisz_Tablice(Tablica);
    // Wypisz_Tablice(Tablica_org);

    // cout<<"Wynik sprawdzania (1 - poprawne; 0 - niepoprawne) == "<<Sprawdz_Sortowanie(Tablica)<<endl<<endl;
    return 0;
}