//Szocs Nandor,514/2, snim2308
#include <iostream>
#include <stdexcept>

class NullavalValoOsztas : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Nullával való osztás!";
    }
};
class NagyEgesz
{
private:
    int *szam;
    int n;
    int elojel;

public:
    NagyEgesz();
    NagyEgesz(int elojel, int n, const int *szamjegyek);
    NagyEgesz(const NagyEgesz &other);
    NagyEgesz(int szam);
    NagyEgesz(long szam);
    ~NagyEgesz();
    NagyEgesz &operator=(const NagyEgesz &other);
    NagyEgesz operator+(const NagyEgesz &other) const;
    NagyEgesz operator-(const NagyEgesz &other) const;
    NagyEgesz operator*(const NagyEgesz &other) const;
    NagyEgesz operator/(const NagyEgesz &other) const;
    NagyEgesz &operator++();
    NagyEgesz operator++(int);
    NagyEgesz &operator--();
    NagyEgesz operator--(int);
    NagyEgesz &operator+=(const NagyEgesz &other);
    NagyEgesz &operator-=(const NagyEgesz &other);
    NagyEgesz &operator*=(const NagyEgesz &other);
    NagyEgesz &operator/=(const NagyEgesz &other);
    bool operator<(const NagyEgesz &other) const;
    bool operator==(const NagyEgesz &other) const;
    bool operator>(const NagyEgesz &other) const;
    bool operator<=(const NagyEgesz &other) const;
    bool operator>=(const NagyEgesz &other) const;
    friend std::ostream &operator<<(std::ostream &os, const NagyEgesz &nagyEgesz);
    void SzamjegyeketBalraShiftel(int shift)
    {
        if (shift <= 0)
        {
            return;
        }

        int *shiftedSzam = new int[n + shift];
        for (int i = 0; i < shift; i++)
        {
            shiftedSzam[i] = 0;
        }
        for (int i = shift; i < n + shift; i++)
        {
            shiftedSzam[i] = szam[i - shift];
        }

        delete[] szam;
        szam = shiftedSzam;
        n += shift;
        std::cout<<n<<std::endl;
    }

    void SzamjegyeketJobbraShiftel(int shift)
    {
        if (shift <= 0 || n <= shift)
        {
            delete[] szam;
            szam = nullptr;
            n = 0;
            return;
        }

        int *shiftedSzam = new int[n - shift];
        //int j=1;
        for (int i = 0; i < n - shift; i++)
        {
            shiftedSzam[i] = szam[i];
            //j++;
        }

        delete[] szam;
        szam = shiftedSzam;
        n -= shift;
    }

    void ElolNullakkalValoMeghosszabbitas()
    {
        if (elojel == 0)
        {
            return;
        }

        int firstNonZeroDigit = 0;
        while (firstNonZeroDigit < n && szam[firstNonZeroDigit] == 0)
        {
            firstNonZeroDigit++;
        }
        //std::cout<<"l"<<firstNonZeroDigit<<std::endl;
        if (firstNonZeroDigit == n)
        {
            // 0 a szam
            elojel = 0;
            delete[] szam;
            szam = nullptr;
            n = 0;
            return;
        }

        if (firstNonZeroDigit > 0)
        {
            SzamjegyeketBalraShiftel(firstNonZeroDigit);
        }
    }
};
#include "P1_snim2308.cpp"