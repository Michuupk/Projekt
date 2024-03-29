#include <iostream>
#include <cstdlib>
#include <chrono>
#include <fstream>

using namespace std;


const unsigned int WielkoscTablicy = 5000;     // określanie rozmiaru tablicy
int Tablica[WielkoscTablicy];       // tworzenie tablicy o określonym rozmiarze
int *temp_tab;
string Nazwy_wynikow[5];

unsigned short i = 0, n = 0;
int ilerazy, theend = 1;
short memo, sort = 0;
bool check;


void Losowanie_Tablicy()
{
    srand(time(0));                     //seed dla funkcji rand()
    unsigned int random;
    for(i = 0 ; i < WielkoscTablicy ; i++)
    {
        random = rand() % 1000;          //losowanie liczby w zakresie modulo 100
        Tablica[i] = random;            //wpisywanie wylosowanych wartości do tablicy
    }
}

void Sortowanie_Przez_Wybor(int tab[])              //sortowanie przez wybór
{
    short min, max, temp;
    for(i=0; i < WielkoscTablicy-1 ;i++)
    {
        min = i;
        for(n=i+1; n < WielkoscTablicy; n++)        //sortowanie po minimum
        {
            if(tab[min] > tab[n])
            {
                min = n;           
            }
        }

        temp = tab[i];                              //zamiana miejsc min
        tab[i] = tab[min];
        tab[min] = temp;

        max = WielkoscTablicy-1-i;
        for(n = WielkoscTablicy-1-i; n > 0; n--)   //sortowanie po maximum
        {
            if(tab[max] < tab[n])
            {
                max = n;         
            }
        }

        temp = tab[WielkoscTablicy-1-i];            //zamiana miejsc max
        tab[WielkoscTablicy-1-i] = tab[max];
        tab[max] = temp;
    }
}
void Sortowanie_Przez_Wstawianie(int tab[])         //sortowanie przez wstaiwanie
{
    for(i=1; i< WielkoscTablicy; i++)
    {
        while (tab[i-1] > tab[i])
        {
                memo = tab[i-1];
                tab[i-1] = tab[i];
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

void merge(int tab, int poczatek, int srodek, int koniec)
{
    





}

void Sortowanie_Przez_Scalanie(int tab[], int poczatek, int koniec)
{

    if( poczatek<=koniec ) return;

    int srodek = (poczatek+koniec)/2;

    Sortowanie_Przez_Scalanie(tab, poczatek, srodek);
    Sortowanie_Przez_Scalanie(tab, srodek+1, koniec);

   // merge(tab, poczatek, srodek, koniec);
}


void Sortowanie_Szybkie()
{
    ;
}

void Wybor_Sortowania(int tab[], int sort)
{
    switch(sort)                                    // *Switch wyboru*
    {
        case 1:     Sortowanie_Przez_Wybor(tab);
            break;

        case 2:     Sortowanie_Przez_Wstawianie(tab);
            break;
        
        case 3:     Sortowanie_Babelkowe(tab);
            break;
        
        case 4:     Sortowanie_Przez_Scalanie(tab, 0, WielkoscTablicy-1);
            break;
        
        case 5:     Sortowanie_Szybkie();
            break;
            
        default: "Podaj prawidłową wartość";
            break;
    }
}


bool Sprawdz_Sortowanie(int tab[])                  // sprawdzanie sortowania
{
    check = true;

    for(n = 0 ; n <= WielkoscTablicy-2 ; n++)
    {    
        
        for(i = n+1 ; i<=WielkoscTablicy-1 ; i++)
        {
            if(tab[n] > tab[i])                     //porównywanie najmniejszego elementu do wszystkich pozostałych
            {
                check = false;
            }            
                
        }
    }
    return check;
}


void Wypisz_Tablice(int tab[])                      // wypisywanie całej tablicy
{
    for(i = 0 ; i < WielkoscTablicy ; i++)
    {
        cout << tab[i] << " ";  
    }
        cout << endl;
}

int main()
{   
    fstream wyniki;

    Nazwy_wynikow[0] = "Przez_Wybor";
    Nazwy_wynikow[1] = "Przez_Wstawianie";
    Nazwy_wynikow[2] = "Babelkowe";
    Nazwy_wynikow[3] = "Przez_Scalanie";
    Nazwy_wynikow[4] = "QuickSort";


    while(theend != 0)
    {
        cout<<"------ MENU--------\n";               // *MENU*                       
        cout<<"Wybierz sortowanie:\n";          
        cout<<"Przez wybór -> 1\n";
        cout<<"Przez wstawianie -> 2\n";                 
        cout<<"Bąbelkowe -> 3\n";
        cout<<"Przez scalanie -> 4\n";
        cout<<"Szybkie -> 5\n";
        cin>>sort;

        wyniki.open("AiZO"+Nazwy_wynikow[sort-1]+".txt", ios::app);

        cout<<"Ile razy? \n";                    // *Pętla ile razy*
        cin>>ilerazy;                                        
        cout<<endl;
        
        cout<<"Sortowanie: \n";
        

        for(ilerazy; ilerazy>0; ilerazy--)
        {
            Losowanie_Tablicy();
                chrono::time_point<std::chrono::high_resolution_clock> start, end;
                start = chrono::high_resolution_clock::now();
            Wybor_Sortowania(Tablica, sort);
                end = chrono::high_resolution_clock::now();
                chrono::duration<long double>elapsed{end - start};
            //Wypisz_Tablice(Tablica);
            cout<<"Wynik sprawdzania (1 - poprawne; 0 - niepoprawne) == "<<Sprawdz_Sortowanie(Tablica)<<endl;
            cout<<elapsed.count()<<"s\n";
            if(wyniki.good())
            {
                wyniki<<elapsed.count()<<endl;
            }
            
        }
        wyniki<<endl;
        wyniki.close();
        cout<<"Czy zakończyć?\n";
        cout<<"0 - aby zakończyć | 1 - aby kontynuwać\n";
        cin>>theend;
    }

    //Wypisz_Tablice(Tablica);

    //cout<<"Wynik sprawdzania (1 - poprawne; 0 - niepoprawne) == "<<Sprawdz_Sortowanie(Tablica)<<endl<<endl;
    return 0;
}