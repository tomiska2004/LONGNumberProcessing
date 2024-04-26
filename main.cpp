//numbers are given as an array so it can be bigger than int
//implemented methods which can work with these numbers : +,-,*,/,++(prefix),--(prefix),>,>=,<,<=,==,!=
#include <iostream>
#include "P1_snim2308.h"
using namespace std;
int main()
{
    try
    {
        int szam1Arr[] = {1, 2, 3, 4, 5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2};
        NagyEgesz szam1(1,20, szam1Arr);

        int szam2Arr[] = {9, 8, 7,3,4,5,6,7,8,9,1,2,3,4,5,0,3};
        NagyEgesz szam2(1, 3, szam2Arr);

        std::cout << "Szam1: " << szam1 << std::endl;
        std::cout << "Szam2: " << szam2 << std::endl;

        NagyEgesz osszeg = szam1 + szam2;std::cout << "Osszeg: " << osszeg << std::endl;osszeg-=szam2;cout<<osszeg<<endl;
        NagyEgesz kulonbseg = szam1 - szam2;std::cout << "Kulonbseg: " << kulonbseg << std::endl;kulonbseg+=szam2;cout << "Kulonbseg: " << kulonbseg << std::endl;
        NagyEgesz szorzat = szam1 * szam2;std::cout << "Szorzat: " << szorzat << std::endl;
        //szorzat/=szam2;cout << "Szorzat: " << szorzat << std::endl;
        cout<<szam1<<" "<<szam2<<endl;
        NagyEgesz hanyados = szam1 / szam2;
        
        
        
        std::cout << "Hanyados: " << hanyados << std::endl; hanyados*=szam2;cout << "Hanyados: " << hanyados << std::endl;

        // std::cout << "Szam1 novelese: " << szam1 << std::endl;
        ++szam1;
        --szam2;

        std::cout << "Szam1 novelese: " << szam1 << std::endl;
        std::cout << "Szam2 csokkentese: " << szam2 << std::endl;

        if (szam1 > szam2)
        {
            std::cout << "Szam1 nagyobb, mint Szam2" << std::endl;
        }
        else if (szam1 < szam2)
        {
            std::cout << "Szam1 kisebb, mint Szam2" << std::endl;
        }
        else
        {
            std::cout << "Szam1 egyenlo Szam2-vel" << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "Hiba tortent: " << e.what() << std::endl;
    }


    NagyEgesz m(-15);
    cout<<++m<<endl;
     cout<<--m<<endl;
     cout<<m*3;
    return 0;
}

