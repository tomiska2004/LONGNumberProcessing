//Szocs Nandor,514/2, snim2308
#include <iostream>
#include <stdexcept>

NagyEgesz::NagyEgesz() : szam(nullptr), n(0), elojel(0) {}

NagyEgesz::NagyEgesz(int elojel, int n, const int *szamjegyek) : elojel(elojel)
{
    if (n <= 0)
    {
        throw std::invalid_argument("Nem megfelelő számjegyek száma!");
    }

    this->n = n;
    szam = new int[n];
    for (int i = 0; i < n; i++)
    {
        szam[i] = szamjegyek[i];
    }
}

NagyEgesz::NagyEgesz(const NagyEgesz &other) : n(other.n), elojel(other.elojel)
{
    szam = new int[n];
    for (int i = 0; i < n; i++)
    {
        szam[i] = other.szam[i];
    }
}

NagyEgesz::NagyEgesz(int szam)
{
    if (szam == 0)
    {
        this->elojel = 0;
        this->n = 0;
        this->szam = nullptr;
        return;
    }

    if (szam < 0)
    {
        this->elojel = -1;
        szam = -szam;
    }
    else
    {
        this->elojel = 1;
    }

    int temp = szam;
    int digitCount = 0;
    while (temp > 0)
    {
        temp /= 10;
        digitCount++;
    }

    this->n = digitCount;
    this->szam = new int[n];
    for (int i = n - 1; i >= 0; i--)
    {
        this->szam[i] = szam % 10;
        szam /= 10;
    }
}

NagyEgesz::NagyEgesz(long szam)
{
    NagyEgesz(static_cast<int>(szam));
}

NagyEgesz::~NagyEgesz()
{
    delete[] szam;
}

NagyEgesz &NagyEgesz::operator=(const NagyEgesz &other)
{
    if (this != &other)
    {
        delete[] szam;

        n = other.n;
        elojel = other.elojel;
        szam = new int[n];
        for (int i = 0; i < n; i++)
        {
            szam[i] = other.szam[i];
        }
    }
    return *this;
}

NagyEgesz NagyEgesz::operator+(const NagyEgesz &other) const
{
    if (elojel == 0)
    {
        return other;
    }

    if (other.elojel == 0)
    {
        return *this;
    }

    if (elojel != other.elojel)
    {
        NagyEgesz negaltOther = other;
        negaltOther.elojel *= -1;
        return *this - negaltOther;
    }

    int carry = 0;
    int maxDigits = std::max(n, other.n);
    int *result = new int[maxDigits+1];
    int i = n - 1;
    int j = other.n - 1;
    int k = maxDigits - 1;
    int jelzo=0;
    while (i >= 0 || j >= 0 || carry > 0)
    {
        int digitSum = carry;
        if (i >= 0)
        {
            digitSum += szam[i];
            i--;
        }
        if (j >= 0)
        {
            digitSum += other.szam[j];
            j--;
        }
        result[k] = digitSum % 10;
        carry = digitSum / 10;
        
        k--;
    }
    if (result[0] == 0)
    {
        // Skip leading zero
        NagyEgesz sum(elojel, maxDigits - 1, &result[1]);
        if(sum<other)
        {
            sum.n++;
        }
        delete[] result;
        return sum;
    }
    else
    {
        NagyEgesz sum(elojel, maxDigits, result);
        //-1std::cout<<sum<<" "<<other.n;
        if(sum<other)
        {   int temp = sum.szam[sum.n - 1];
               // std::cout<<sum;
            
            for (int i = sum.n - 1; i > 0; i--) {
                sum.szam[i] = sum.szam[i - 1];
            }

            sum.szam[0] = 1;
            sum.n++;
            sum.szam[sum.n-1]=temp;
        }
        return sum;
    }
}

NagyEgesz NagyEgesz::operator-(const NagyEgesz &other) const
{
    if (elojel == 0)
    {
        NagyEgesz negaltOther = other;
        negaltOther.elojel *= -1;
        return negaltOther;
    }

    if (other.elojel == 0)
    {
        return *this;
    }

    if (elojel != other.elojel)
    {
        NagyEgesz negaltOther = other;
        negaltOther.elojel *= -1;
        return *this + negaltOther;
    }

    if (*this < other)
    {
        NagyEgesz diff = other - *this;
        diff.elojel *= -1;
        return diff;
    }

    int borrow = 0;
    int *result = new int[n];
    int i = n - 1;
    int j = other.n - 1;
    int k = n - 1;

    while (i >= 0)
    {
        int digitDiff = borrow + szam[i];
        if (j >= 0)
        {
            digitDiff -= other.szam[j];
            j--;
        }
        if (digitDiff < 0)
        {
            digitDiff += 10;
            borrow = -1;
        }
        else
        {
            borrow = 0;
        }
        result[k] = digitDiff;
        i--;
        k--;
    }

    int firstNonZeroDigit = 0;
    while (result[firstNonZeroDigit] == 0)
    {
        firstNonZeroDigit++;
    }

    NagyEgesz diff(elojel, n - firstNonZeroDigit, &result[firstNonZeroDigit]);
    delete[] result;
    return diff;
}

NagyEgesz NagyEgesz::operator*(const NagyEgesz &other) const
{
    if (elojel == 0 || other.elojel == 0)
    {
        return NagyEgesz();
    }

    NagyEgesz product;
    product.n = n + other.n;
    product.szam = new int[product.n];
    for (int i = 0; i < product.n; i++)
    {
        product.szam[i] = 0;
    }

    for (int i = n - 1; i >= 0; i--)
    {
        int carry = 0;
        for (int j = other.n - 1; j >= 0; j--)
        {
            int digitProduct = szam[i] * other.szam[j] + carry + product.szam[i + j + 1];
            product.szam[i + j + 1] = digitProduct % 10;
            carry = digitProduct / 10;
        }
        product.szam[i] = carry;
    }

    if (product.szam[0] == 0)
    {
        //
        product.elojel = elojel * other.elojel;
        NagyEgesz prod(product.elojel, product.n - 1, &product.szam[1]);
        // delete[] product.szam;
        // std::cout<<product<<" uuuuuuuuu "<<other.n<<std::endl;
        return prod;
    }
    else
    {
        product.elojel = elojel * other.elojel;
        return product;
    }
}

NagyEgesz &NagyEgesz::operator++()
{
    *this = *this + 1;
    // std::cout<<"oop";
    return *this;
}

NagyEgesz NagyEgesz::operator++(int)
{
    NagyEgesz temp(*this);
    *this = *this + 1;
    return temp;
}

NagyEgesz &NagyEgesz::operator--()
{
    *this = *this - 1;
    return *this;
}

NagyEgesz NagyEgesz::operator--(int)
{
    NagyEgesz temp(*this);
    *this = *this - 1;
    return temp;
}

NagyEgesz &NagyEgesz::operator+=(const NagyEgesz &other)
{
    *this = *this + other;
    return *this;
}
NagyEgesz &NagyEgesz::operator-=(const NagyEgesz &other)
{
    *this = *this - other;
    return *this;
}

NagyEgesz &NagyEgesz::operator*=(const NagyEgesz &other)
{
    *this = *this * other;
    return *this;
}



bool NagyEgesz::operator<(const NagyEgesz &other) const
{
    if (elojel < other.elojel)
    {
        return true;
    }
    if (elojel > other.elojel)
    {
        return false;
    }

    if (n < other.n)
    {
        return true;
    }
    if (n > other.n)
    {
        return false;
    }

    for (int i = 0; i < n; i++)
    {
        if (szam[i] < other.szam[i])
        {
            return true;
        }
        if (szam[i] > other.szam[i])
        {
            return false;
        }
    }

    return false;
}

bool NagyEgesz::operator==(const NagyEgesz &other) const
{
    if (elojel != other.elojel || n != other.n)
    {
        return false;
    }

    for (int i = 0; i < n; i++)
    {
        if (szam[i] != other.szam[i])
        {
            return false;
        }
    }

    return true;
}

bool NagyEgesz::operator>(const NagyEgesz &other) const
{
    return !(*this < other || *this == other);
}

bool NagyEgesz::operator<=(const NagyEgesz &other) const
{
    return (*this < other || *this == other);
}

bool NagyEgesz::operator>=(const NagyEgesz &other) const
{
    return (*this > other || *this == other);
}

std::ostream &operator<<(std::ostream &os, const NagyEgesz &nagyEgesz)
{   if(nagyEgesz.n>0)
    {if (nagyEgesz.elojel < 0)
    {
        os << "-";
    }
    int i=0;
    while(nagyEgesz.szam[i]==0 )
    {
        i++;
    }
    while ( i < nagyEgesz.n)
    {
        os << nagyEgesz.szam[i];
        i++;
    }
    }
    else{
        os<<"0";
    }
    return os;
}

NagyEgesz NagyEgesz::operator/(const NagyEgesz &other) const
{
    if (other.elojel == 0)
    {
        throw std::invalid_argument("Nullával való osztás!");
    }

    if (elojel == 0)
    {
        return *this;
    }
    if (*this < other)
    {
        return NagyEgesz();
    }
    bool neg=false;
if (elojel ==-1)
    {
        neg=true;
    }
    bool neg2=false;
if (other.elojel ==-1)
    {
        neg2=true;
    }

    NagyEgesz quotient;
    NagyEgesz quotientc;
    quotient.n = n - other.n + 1;
    quotient.szam = new int[quotient.n];
    for (int i = 0; i < quotient.n; i++)
    {
        quotient.szam[i] = 0;
    }
    quotientc.n = n - other.n + 1;
    quotientc.szam = new int[quotientc.n];
    for (int i = 0; i < quotientc.n; i++)
    {
        quotientc.szam[i] = 0;
    }

    NagyEgesz dividend(*this);
    dividend.elojel = 1;
    NagyEgesz divisor(other);
    divisor.elojel = 1;

    NagyEgesz currentDivisor;
    NagyEgesz szam;
   
    szam.n = n - other.n + 1;
    szam.szam = new int[szam.n];
    for (int i = 0; i < szam.n; i++)
    {
        szam.szam[i] = 0;
    }
    int n1 = n - other.n - 1, k = 1, i = 1;
    currentDivisor=divisor;
    while (n1 > 0)
    {
        quotient.n = 1;
        i = 1;
        quotient.szam = new int[n1];
        quotient.szam[0] = 1;
        while (n1 > 0)
        {
            quotient.szam[i] = 0;
            quotient.n++;
            n1--;
            i++;
        }
        quotient.elojel = 1;
        szam = szam + quotient;

        quotient.elojel = 1;
        divisor.elojel=1;
        quotient *= divisor;
        
        quotient.elojel = 1;
        currentDivisor = divisor;
        dividend.elojel=1;
        dividend =dividend- quotient;
        n1 = dividend.n - other.n - 1; 
        
    } 
    {  
        int quotientDigit = 0;
        while (dividend >=currentDivisor)
        {
            dividend = dividend - currentDivisor;
            quotientDigit++;
        }
        int i = 0;
        while (quotientDigit > 0)
        {
            quotientc.szam[i] = quotientDigit % 10;
            
            quotientDigit /= 10;
            i++;
        }
        int db = 0;
        while (i > 0)
        {
            quotient.szam[i - 1] = quotientc.szam[db];
            i--;
            db++;
        } 
        quotient.n = db;
        quotient.elojel=1;
        quotient += szam;
    }

    quotient.elojel = elojel * other.elojel;
    return quotient;
}
NagyEgesz &NagyEgesz::operator/=(const NagyEgesz &other)
{
    *this = *this / other;
    return *this;
}