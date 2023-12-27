#include "bigint.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
using namespace std;

int main()
{
    try
    {
        string str = "+8tq3";
        bigint A(str);
        cout << "A: " << A << '\n';
    }
    catch (const invalid_argument &e)
    {
        cout << "Error: " << e.what() << '\n';
    }

    try
    {
        bigint A;
        cout << "A: " << A << '\n';
        string str = "100000000000000000000";
        bigint B(str);
        cout << "B: " << B << '\n';
        string str1 = "-999888777666555444";
        bigint C(str1);
        cout << "C: " << C << '\n';
        bigint D(2024);
        cout << "D: " << D << '\n';

        // addition
        cout << "A+B: " << (A + B) << '\n';
        cout << "A+C: " << (A + C) << '\n';
        cout << "B+C: " << (B + C) << '\n';
        cout << "C+D: " << (C + D) << '\n';

        // subtract
        cout << "A-B: " << (A - B) << '\n';
        cout << "A-C: " << (A - C) << '\n';
        cout << "B-C: " << (B - C) << '\n';
        cout << "C-D: " << (C - D) << '\n';

        // multiply
        cout << "A*B: " << (A * B) << '\n';
        cout << "A*C: " << (A * C) << '\n';
        cout << "B*C: " << (B * C) << '\n';
        cout << "C*D: " << (C * D) << '\n';

        // comparison
        cout << "A == B: " << (A == B) << '\n';
        cout << "B == C: " << (B == C) << '\n';
        cout << "B != C: " << (B != C) << '\n';
        cout << "B == D: " << (B == D) << '\n';

        cout << "A < B: " << (A <= B) << '\n';
        cout << "B <= C: " << (B <= C) << '\n';
        cout << "B >= C: " << (B >= C) << '\n';
        cout << "B < D: " << (B < D) << '\n';
        cout << "B <= D: " << (B <= D) << '\n';

        // negation operations
        cout << "-A: " << -A << '\n';
        cout << "-B: " << -B << '\n';
        cout << "-C: " << -C << '\n';

        // add and assign, subtract and assign, multiply and assign
        bigint E(2);
        cout << "E: " << E << '\n';
        string str2 = "100";
        bigint F(str2);
        cout << "F: " << F << '\n';
        E += F;
        cout << "E+=F: " << E << '\n';
        E -= F;
        cout << "E-=F: " << E << '\n';
        E *= F;
        cout << "E*=F: " << E << '\n';
    }
    catch (const invalid_argument &e)
    {
        cout << "Error: " << e.what() << '\n';
    }
    return 0;
}
