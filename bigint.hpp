#include <stdint.h>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

class bigint
{
private:
    std::vector<int64_t> v;

public:
    bigint();
    bigint(int64_t num);
    bigint(string &str);

    bigint &operator=(const bigint &rhs);
    bigint &operator+=(const bigint &rhs);
    bigint &operator-=(const bigint &rhs);
    bigint &operator*=(const bigint &rhs);

    friend ostream &operator<<(ostream &os, const bigint &b);

    bool operator==(const bigint &rhs) const;
    bool operator!=(const bigint &rhs) const;
    bool operator<=(const bigint &rhs) const;
    bool operator<(const bigint &rhs) const;
    bool operator>=(const bigint &rhs) const;
    bool operator>(const bigint &rhs) const;

    bigint operator+(const bigint &rhs) const;
    bigint operator-(const bigint &rhs) const;
    bigint operator-() const;

    bigint operator*(const bigint &rhs) const;

private:
    bigint zero(const bigint &rhs) const;
};

bigint::bigint()
{
    v = {0};
}

bigint::bigint(int64_t num)
{
    if (num < 0)
    {
        v.insert(v.begin(), 1);
    }
    else
    {
        v.insert(v.begin(), 0);
    }
    int64_t absnum = abs(num);

    while (absnum > 9)
    {
        int64_t i = absnum % 10;
        v.insert(v.begin() + 1, i);
        absnum = absnum / 10;
    }
    v.insert(v.begin() + 1, absnum);
}

bigint::bigint(string &str)
{
    if (str.empty())
    {
        v.insert(v.begin(), 0);
    }
    else
    {
        if (str[0] == '-')
        {
            v.insert(v.end(), 1);
            str = str.substr(1);
        }
        else if (str[0] == '+')
        {
            v.insert(v.end(), 0);
            str = str.substr(1);
        }
        else if (isdigit(str[0]))
        {
            v.insert(v.end(), 0);
        }
        else
        {
            throw invalid_argument("The first character must be digit or sign");
        }

        for (size_t i = 0; i < str.size(); ++i)
        {
            if (isdigit(str[i]))
            {
                v.insert(v.end(), str[i] - 48);
            }
            else
            {
                throw invalid_argument("Input must be digit");
            }
        }
    };
}

bigint bigint::zero(const bigint &rhs) const
{
    bigint result = rhs;
    while (result.v.size() > 2 && result.v[1] == 0)
    {
        result.v.erase(result.v.begin() + 1);
    }
    return result;
}

ostream &operator<<(ostream &out, const bigint &b)
{
    if (b.v.size() == 1)
    {
        out << '0';
    }

    if (!b.v.empty())
    {
        if (b.v[0] == 1)
        {
            out << '-';
        }
        for (size_t i = 1; i < b.v.size(); ++i)
        {
            out << static_cast<int>(b.v[i]);
        }
    }

    return out;
}

bool bigint::operator==(const bigint &rhs) const
{
    if (v.size() != rhs.v.size())
    {
        return false;
    }
    for (size_t i = 0; i < v.size(); ++i)
    {
        if (v[i] != rhs.v[i])
        {
            return false;
        }
    }
    return true;
}

bool bigint::operator!=(const bigint &rhs) const
{
    return !(*this == rhs);
}

bool bigint::operator<=(const bigint &rhs) const
{
    if (v[0] == 0 && rhs.v[0] == 1)
    {
        return false;
    }
    else if (v[0] == 1 && rhs.v[0] == 0)
    {
        return true;
    }
    else if (v[0] == 0 && rhs.v[0] == 0)
    {
        if (v.size() < rhs.v.size())
        {
            return true;
        }
        else if (v.size() > rhs.v.size())
        {
            return false;
        }
        else if (v.size() == rhs.v.size())
        {
            for (size_t i = 0; i < v.size(); ++i)
            {
                if (v[i] > rhs.v[i])
                {
                    return false;
                }
            }
            return true;
        }
    }
    else
    {
        if (v.size() > rhs.v.size())
        {
            return true;
        }
        else if (v.size() < rhs.v.size())
        {
            return false;
        }
        else if (v.size() == rhs.v.size())
        {
            for (size_t i = 0; i < v.size(); ++i)
            {
                if (v[i] < rhs.v[i])
                {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

bool bigint::operator<(const bigint &rhs) const
{
    if (*this == rhs)
    {
        return false;
    }
    else
    {
        return (*this <= rhs);
    }
}

bool bigint::operator>=(const bigint &rhs) const
{
    if (*this == rhs)
    {
        return true;
    }
    else
    {
        return !(*this <= rhs);
    }
}

bool bigint::operator>(const bigint &rhs) const
{
    if (*this == rhs)
    {
        return false;
    }
    else
    {
        return (*this >= rhs);
    }
}

bigint bigint::operator+(const bigint &rhs) const
{
    bigint a = *this;
    bigint b = rhs;
    bigint newint;
    int carry = 0;
    int sum = 0;
    if (a.v[0] == 0 && b.v[0] == 0)
    {
        newint.v[0] = 0;
    }
    else if (a.v[0] == 1 && b.v[0] == 1)
    {
        newint.v[0] = 1;
    }
    else if (a.v[0] == 0 && b.v[0] == 1)
    {
        b.v[0] = 0;
        return a - b;
    }
    else if (a.v[0] == 1 && b.v[0] == 0)
    {
        a.v[0] = 0;
        return b - a;
    }

    size_t i = a.v.size() - 1;
    size_t j = b.v.size() - 1;

    while (i > 0 || j > 0)
    {
        sum = carry;
        if (i > 0)
        {
            sum += a.v[i];
            i--;
        }
        if (j > 0)
        {
            sum += b.v[j];
            j--;
        }
        if (sum > 9)
        {
            carry = sum / 10;
            sum = sum % 10;
        }
        else
        {
            carry = 0;
        }
        newint.v.insert(newint.v.begin() + 1, sum);
    }
    if (carry != 0)
    {
        newint.v.insert(newint.v.begin() + 1, carry);
    }
    return newint;
}

bigint bigint::operator-(const bigint &rhs) const
{
    bigint newint;
    bigint swap;
    bigint a = *this;
    bigint b = rhs;
    int64_t borrow = 0;
    int sub = 0;
    if (a.v[0] == 0 && b.v[0] == 0 && a > b)
    {
        newint.v[0] = 0;
    }
    else if (a.v[0] == 0 && b.v[0] == 1)
    {
        newint.v[0] = 0;
        b.v[0] = 0;
        return a + b;
    }
    else if (a.v[0] == 1 && b.v[0] == 0)
    {
        b.v[0] = 1;
        return a + b;
    }
    else if (a.v[0] == 1 && b.v[0] == 1 && a < b)
    {
        newint.v[0] = 1;
        a.v[0] = 0;
        b.v[0] = 0;
    }
    else if (a.v[0] == 0 && b.v[0] == 0 && a < b)
    {
        newint.v[0] = 1;
        swap = a;
        a = b;
        b = swap;
    }
    else if (a.v[0] == 1 && b.v[0] == 1 && a > b)
    {
        newint.v[0] = 0;
        a.v[0] = 0;
        b.v[0] = 0;
        swap = a;
        a = b;
        b = swap;
    }

    size_t i = a.v.size() - 1;
    size_t j = b.v.size() - 1;

    while (i > 0)
    {
        sub = a.v[i] - borrow;
        i--;

        if (j > 0)
        {
            sub = sub - b.v[j];
            if (sub >= 0)
            {
                borrow = 0;
            }
            else
            {
                sub = sub + 10;
                borrow = 1;
            }
            newint.v.insert(newint.v.begin() + 1, sub);
            j--;
        }
        else
        {
            if (sub >= 0)
            {
                borrow = 0;
            }
            else
            {
                sub = sub + 10;
                borrow = 1;
            }
            newint.v.insert(newint.v.begin() + 1, sub);
        }
    }
    return zero(newint);
}

bigint bigint::operator-() const
{
    bigint result = *this;

    if (result.v.size() == 1)
    {
        result.v[0] = 0;
        result.v.insert(result.v.begin() + 1, 0);
    }

    if (result.v[0] == 0)
    {
        result.v[0] = 1;
    }
    else
    {
        result.v[0] = 0;
    }

    return result;
}

bigint &bigint::operator=(const bigint &rhs)
{
    if (this != &rhs)
    {
        v = rhs.v;
    }
    return *this;
}

bigint &bigint::operator+=(const bigint &rhs)
{
    *this = *this + rhs;
    return *this;
}

bigint &bigint::operator-=(const bigint &rhs)
{
    *this = *this - rhs;
    return *this;
}

bigint &bigint::operator*=(const bigint &rhs)
{
    *this = *this * rhs;
    return *this;
}

bigint bigint::operator*(const bigint &rhs) const
{
    bigint newint;

    for (size_t j = rhs.v.size() - 1; j > 0; --j)
    {
        bigint mul;
        int64_t carry = 0;

        for (size_t i = v.size() - 1; i > 0; --i)
        {
            int64_t c = v[i] * rhs.v[j] + carry;
            carry = c / 10;
            c = c % 10;
            mul.v.insert(mul.v.begin() + 1, c);
        }

        if (carry != 0)
        {
            mul.v.insert(mul.v.begin() + 1, carry);
        }

        size_t d = rhs.v.size() - 1 - j;
        while (d > 0)
        {
            mul.v.push_back(0);
            --d;
        }

        newint += mul;
    }
    newint = zero(newint);
    if ((v[0] == 0 && rhs.v[0] == 0) || (v[0] == 1 && rhs.v[0] == 1))
    {
        newint.v[0] = 0;
    }
    else if ((v[0] == 1 && rhs.v[0] == 0) || (v[0] == 0 && rhs.v[0] == 1))
    {
        newint.v[0] = 1;
    }
    // else if (v[1] == 0 || rhs.v[1] == 0)
    // {
    //     return 0;
    // }

    return newint;
}