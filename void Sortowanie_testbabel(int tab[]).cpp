#include <iostream>
#include <cstdlib>

int tab[10];

void Sortowanie_testbabel(int tab[])
{
    int pmin = 0, pmax = 9;
    int p;

    do
    {
        p= -1;
        for (i = pmin; i < pmax; i++ )
        {
            if(tab[i]>tab[i+1])
            {
                swap(tab[i], tab[i+1]);
                if(p<0) pmin = i;
                p=i;
            }
            if (pmin) pmin--;
            pmax = p;
        }
    } while (p >= 0 );
     
}

int main ()
{
    for(int i = 0 ; i<10; i++)
    {
        tab[i] = i;
    }

    Sortowanie_testbabel(tab);



}