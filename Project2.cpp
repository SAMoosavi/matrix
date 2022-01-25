#include <iostream>
using namespace std;

const int maxN = 100;
int An, Am, Bn, Bm = 0;
double A[maxN][maxN];
double B[maxN][maxN];
double Da, Db = 0;

void enterA()
{
    bool enterAn = true;
    bool enterAm = true;

    while (enterAn)
    {
        cout << "An = ";
        cin >> An;
        enterAn = false;
        if (An <= 0)
        {
            cout << "An is not valid! Please  re-enter An \n";
            enterAn = true;
        }
    }

    while (enterAm)
    {
        cout << "Am = ";
        cin >> Am;
        enterAm = false;
        if (Am <= 0)
        {
            cout << "Am is not valid! Please  re-enter Am \n";
            enterAm = true;
        }
    }

    for (int i = 0; i < An; i++)
    {
        for (int j = 0; j < Am; j++)
        {
            cin >> A[i][j];
        }
    }
}

void enterB()
{
    bool enterBn = true;
    bool enterBm = true;

    while (enterBn)
    {
        cout << "Bn = ";
        cin >> Bn;
        enterBn = false;
        if (Bn <= 0)
        {
            cout << "Bn is not valid! Please  re-enter Bn \n";
            enterBn = true;
        }
    }

    while (enterBm)
    {
        cout << "Bm = ";
        cin >> Bm;
        enterBm = false;
        if (Bm <= 0)
        {
            cout << "Bm is not valid! Please  re-enter Bm \n";
            enterBm = true;
        }
    }

    for (int i = 0; i < Bn; i++)
    {
        for (int j = 0; j < Bm; j++)
        {
            cin >> B[i][j];
        }
    }
}

void AToB()
{
    Bn = An;
    Bm = Am;
    for (int i = 0; i < An; i++)
    {
        for (int j = 0; j < Am; j++)
        {
            B[i][j] = A[i][j];
        }
    }
}

void BToA()
{
    An = Bn;
    Am = Bm;
    for (int i = 0; i < Bn; i++)
    {
        for (int j = 0; j < Bm; j++)
        {
            A[i][j] = B[i][j];
        }
    }
}

void AMultipliedB()
{
    double C[maxN][maxN];
    for (int i = 0; i < An; i++)
    {
        for (int j = 0; j < Bm; j++)
        {
            double sum = 0;
            for (int k = 0; k < Am; k++)
            {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    Am = Bm;
    for (int i = 0; i < An; i++)
    {
        for (int j = 0; j < Am; j++)
        {
            A[i][j] = C[i][j];
        }
    }
}

void sum()
{
    for (int i = 0; i < An; i++)
    {
        for (int j = 0; j < Am; j++)
        {
            A[i][j] += B[i][j];
        }
    }
}

bool ADivisionB()
{
    long long n = Bn;
    double MM[n][2 * n];

    for (long long i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            MM[i][j] = B[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = n; j < 2 * n; j++)
        {
            (i + n == j) ? MM[i][j] = 1 : MM[i][j] = 0;
        }
    }


    bool a = 1;
    for (int i = 0; i < n && a; i++)
    {
        bool b = 1;
        while (b && a)
        {
            double i1, i2, q = -1;
            long long int k1 = -1, k2 = -1, k3 = -1;
            for (int j = 0; j < n; j++)
            {
                if (MM[j][i] != 0)
                {
                    if (k1 == -1)
                    {
                        k1 = j;
                        i1 = MM[j][i];
                    }
                    else if (j >= i)
                    {
                        k2 = j;
                        i2 = MM[j][i];
                    }
                    else
                    {
                        k3 = j;
                    }
                }
                if (k2 == -1 && k1 < i)
                {
                    k3 = 1;
                }
                else
                {
                    k3 = -1;
                }
            }
            if (k1 == -1 || (k3 != -1 && k2 == -1))
            {
                a = 0;
            }
            else if (k2 != -1)
            {
                q = -i1 / i2;

                for (int j = 0; j < 2 * n; j++)
                {
                    MM[k1][j] += q * MM[k2][j];
                }
            }
            else
            {
                for (int j = 0; j < 2 * n; j++)
                {
                    double c = -1;
                    c = MM[k1][j];
                    MM[k1][j] = MM[i][j];
                    MM[i][j] = c / i1;
                }
                b = 0;
            }
        }
    }
    
    if (a)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (MM[i][j] == 0)
                    MM[i][j] = 0;
                MM[i][j] = MM[i][j + n];
            }
        }

        double C[maxN][maxN];
        for (int i = 0; i < An; i++)
        {
            for (int j = 0; j < Bm; j++)
            {
                double sum = 0;
                for (int k = 0; k < Am; k++)
                {
                    sum += A[i][k] * MM[k][j];
                }
                C[i][j] = sum;
            }
        }
        Am = Bm;
        for (int i = 0; i < An; i++)
        {
            for (int j = 0; j < Am; j++)
            {
                A[i][j] = C[i][j];
            }
        }
    }

    return a;
}

void Submission()
{
    for (int i = 0; i < An; i++)
    {
        for (int j = 0; j < Am; j++)
        {
            A[i][j] -= B[i][j];
        }
    }
}

void aMultipliedA()
{
    double a = 0;
    cout << "a = ";
    cin >> a;
    for (int i = 0; i < An; i++)
    {
        for (int j = 0; j < Am; j++)
        {
            A[i][j] *= a;
        }
    }
}

void determinantA()
{
    if (An > 1)
    {

        long long n = An;
        double MM[n][n];

        for (long long i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                MM[i][j] = A[i][j];
            }
        }
        bool a = 1;
        int mark = 0;
        double pow = 1;
        for (int i = 0; i < n && a; i++)
        {
            bool b = 1;
            while (b && a)
            {
                double i1, i2, q = -1;
                long long int k1 = -1, k2 = -1, k3 = -1;
                for (int j = 0; j < n; j++)
                {
                    if (MM[j][i] != 0)
                    {
                        if (k1 == -1)
                        {
                            k1 = j;
                            i1 = MM[j][i];
                        }
                        else if (j >= i)
                        {
                            k2 = j;
                            i2 = MM[j][i];
                        }
                        else
                        {
                            k3 = j;
                        }
                    }
                    if (k2 == -1 && k1 < i)
                    {
                        k3 = 1;
                    }
                    else
                    {
                        k3 = -1;
                    }
                }
                if (k1 == -1 || (k3 != -1 && k2 == -1))
                {
                    a = 0;
                }
                else if (k2 != -1)
                {
                    q = -i1 / i2;

                    for (int j = 0; j < n; j++)
                    {
                        MM[k1][j] += q * MM[k2][j];
                    }
                }
                else
                {
                    pow *= MM[k1][i];
                    for (int j = 0; j < n; j++)
                    {
                        double c = MM[k1][j];
                        MM[k1][j] = MM[i][j];
                        MM[i][j] = c / i1;
                    }
                    b = 0;
                    if (k1 != i)
                        mark++;
                }
            }
        }
        if (a)
        {
            (mark % 2 == 0) ? Da = pow : Da = -1 * pow;
        }
        else
            Da = 0;
    }
    else
        Da = A[0][0];
    if (Da == 0)
        Da = 0;
}

void determinantB()
{
    if (Bn > 1)
    {

        long long n = Bn;
        double MM[n][n];

        for (long long i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                MM[i][j] = B[i][j];
            }
        }
        bool a = 1;
        int mark = 0;
        double pow = 1;
        for (int i = 0; i < n && a; i++)
        {
            bool b = 1;
            while (b && a)
            {
                double i1, i2, q = -1;
                long long int k1 = -1, k2 = -1, k3 = -1;
                for (int j = 0; j < n; j++)
                {
                    if (MM[j][i] != 0)
                    {
                        if (k1 == -1)
                        {
                            k1 = j;
                            i1 = MM[j][i];
                        }
                        else if (j >= i)
                        {
                            k2 = j;
                            i2 = MM[j][i];
                        }
                        else
                        {
                            k3 = j;
                        }
                    }
                    if (k2 == -1 && k1 < i)
                    {
                        k3 = 1;
                    }
                    else
                    {
                        k3 = -1;
                    }
                }
                if (k1 == -1 || (k3 != -1 && k2 == -1))
                {
                    a = 0;
                }
                else if (k2 != -1)
                {
                    q = -i1 / i2;

                    for (int j = 0; j < n; j++)
                    {
                        MM[k1][j] += q * MM[k2][j];
                    }
                }
                else
                {
                    pow *= MM[k1][i];
                    for (int j = 0; j < n; j++)
                    {
                        double c = MM[k1][j];
                        MM[k1][j] = MM[i][j];
                        MM[i][j] = c / i1;
                    }
                    b = 0;
                    if (k1 != i)
                        mark++;
                }
            }
        }
        if (a)
        {
            (mark % 2 == 0) ? Db = pow : Db = -1 * pow;
        }
        else
            Db = 0;
    }
    else
        Db = B[0][0];
    if (Db == 0)
        Db = 0;
}

void GetA()
{

    for (int i = 0; i < An; i++)
    {
        for (int j = 0; j < Am; j++)
        {
            cout << " " << A[i][j];
        }
        cout << " \n";
    }
}

void GetB()
{
    for (long long int i = 0; i < Bn; i++)
    {
        for (long long int j = 0; j < Bm; j++)
        {
            cout << " " << B[i][j];
        }
        cout << " \n";
    }
}

int main()
{
    while (1)
    {
        int number;
        cout << "-------------------\n";
        cout << "| Enter A |   1   |\n";
        cout << "-------------------\n";
        cout << "| Enter B |   2   |\n";
        cout << "-------------------\n";
        cout << "| A To B  |   3   |\n";
        cout << "-------------------\n";
        cout << "| B To A  |   4   |\n";
        cout << "-------------------\n";
        cout << "| A * B   |   5   |\n";
        cout << "-------------------\n";
        cout << "| A + B   |   6   |\n";
        cout << "-------------------\n";
        cout << "| A / B   |   7   |\n";
        cout << "-------------------\n";
        cout << "| A - B   |   8   |\n";
        cout << "-------------------\n";
        cout << "| a * A   |   9   |\n";
        cout << "-------------------\n";
        cout << "| dA      |   10  |\n";
        cout << "-------------------\n";
        cout << "| dB      |   11  |\n";
        cout << "-------------------\n";
        cout << "| Get A   |   12  |\n";
        cout << "-------------------\n";
        cout << "| Get B   |   13  |\n";
        cout << "-------------------\n";
        cout << "number = ";
        cin >> number;
        bool c = 1;
        bool yes = true;
        switch (number)
        {
        case 1:

            enterA();
            cout << "done successfully!\n";

            break;
        case 2:

            enterB();
            cout << "done successfully!\n";
            break;
        case 3:

            if (An == 0)
            {
                cout << "What's A? Please enter number 1 to enter A then go back! \n";
            }
            else
            {
                AToB();
                cout << "done successfully!\n";
            }
            break;
        case 4:

            if (Bn == 0)
            {
                cout << "What's B? Please enter number 2 to enter B then go back! \n";
            }
            else
            {
                BToA();
                cout << "done successfully!\n";
            }
            break;
        case 5:

            if (An == 0)
            {
                cout << "What's A? Please enter number 1 to enter A then go back! \n";
                yes = false;
            }
            if (Bn == 0)
            {
                cout << "What's B? Please enter number 2 to enter B then go back! \n";
                yes = false;
            }
            if (Am != Bn && yes)
            {
                cout << "ooh noo!!!! Can not be multiplied!! Must be Am = Bn but Am = " << Am << " , Bn = " << Bn << "\n";
                yes = false;
            }
            if (yes)
            {
                AMultipliedB();
                cout << "done successfully!\n";
            }
            break;
        case 6:

            if (An == 0)
            {
                cout << "What's A? Please enter number 1 to enter A then go back! \n";
                yes = false;
            }
            if (Bn == 0)
            {
                cout << "What's B? Please enter number 2 to enter B then go back! \n";
                yes = false;
            }
            if ((An != Bn || Am != Bm) && yes)
            {
                if (An != Bn)
                    cout << "ooh noo!!!! Can not be multiplied!! Must be An = Bn but An = " << An << " , Bn = " << Bn << "\n";
                if (Am != Bm)
                    cout << "ooh noo!!!! Can not be multiplied!! Must be Am = Bm but Am = " << Am << " , Bm = " << Bm << "\n";
                yes = false;
            }
            if (yes)
            {
                sum();
                cout << "done successfully!\n";
            }

            break;
        case 7:

            if (An == 0)
            {
                cout << "What's A? Please enter number 1 to enter A then go back! \n";
                yes = false;
            }
            if (Bn == 0)
            {
                cout << "What's B? Please enter number 2 to enter B then go back! \n";
                yes = false;
            }
            if (Bm != Bn && yes)
            {
                cout << "ooh noo!!!! Can not be multiplied!! Must be Bn = Bm but Bn = " << Bn << " , Bm = " << Bm << "\n";
                yes = false;
            }
            if (Am != Bn && yes)
            {
                cout << "ooh noo!!!! Can not be multiplied!! Must be Am = Bn but Am = " << Am << " , Bn = " << Bn << "\n";
                yes = false;
            }
            if (yes)
            {
                ADivisionB() ? cout << "done successfully!\n" : cout << "Cannot perform split operation Because B is not the inverse";
            }

            break;
        case 8:

            if (An == 0)
            {
                cout << "What's A? Please enter number 1 to enter A then go back! \n";
                yes = false;
            }
            if (Bn == 0)
            {
                cout << "What's B? Please enter number 2 to enter B then go back! \n";
                yes = false;
            }
            if ((An != Bn || Am != Bm) && yes)
            {
                if (An != Bn)
                    cout << "ooh noo!!!! Can not be multiplied!! Must be An = Bn but An = " << An << " , Bn = " << Bn << "\n";
                if (Am != Bm)
                    cout << "ooh noo!!!! Can not be multiplied!! Must be Am = Bm but Am = " << Am << " , Bm = " << Bm << "\n";
                yes = false;
            }
            if (yes)
            {
                Submission();
                cout << "done successfully!\n";
            }

            break;
        case 9:
            if (An == 0)
            {
                cout << "What's A? Please enter number 1 to enter A then go back! \n";
            }
            else
            {
                aMultipliedA();
                cout << "done successfully!\n";
            }

            break;
        case 10:
            if (An == 0)
            {
                cout << "What's A? Please enter number 1 to enter A then go back! \n";
            }
            else if (An != Am)
            {
                cout << "ooh noo!!!! Can not be multiplied!! Must be An = Am but An = " << An << " , Am = " << Am << "\n";
            }
            else
            {
                determinantA();
                cout << "determinant A is " << Da << "\n";
            }

            break;
        case 11:

            if (Bn == 0)
            {
                cout << "What's B? Please enter number 2 to enter B then go back! \n";
            }
            else if (Bn != Am)
            {
                cout << "ooh noo!!!! Can not be multiplied!! Must be Bn = Bm but Bn = " << Bn << " , Bm = " << Bm << "\n";
            }
            else
            {
                determinantB();
                cout << "determinant B is " << Db << "\n";
            }

            break;
        case 12:
            if (An == 0)
            {
                cout << "What's A? Please enter number 1 to enter A then go back! \n";
            }
            else
            {
                GetA();
            }
            break;
        case 13:
            if (Bn == 0)
            {
                cout << "What's B? Please enter number 1 to enter B then go back! \n";
            }
            else
            {
                GetB();
            }
            break;
        default:

            cout << "Error 404 :|  \n";
            c = 0;
        }
        while (c)
        {
            cout << "Do you have another request?(Y/N)";
            char C;
            cin >> C;
            if (C == 'N' || C == 'n')
            {
                cout << "Goodbye :(";
                return 0;
            }
            else if (C == 'Y' || C == 'y')
            {
                c = 0;
            }
        }
    }
}
