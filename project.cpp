#include<iostream>
using namespace std;

const int maxN = 100;
int An,Am,Bn,Bm =0;
long long A[maxN][maxN];
long long B[maxN][maxN];

void enterA()
{
    bool enterAn = true;
    bool  enterAm = true;

    while(enterAn )
    {
        cout << "An = ";
        cin >> An;
        enterAn = false;
        if(An <= 0)
        {
            cout << "An is not valid! Please  re-enter An \n";
            enterAn = true;
        }
    }

    while(enterAm )
    {
        cout << "Am = ";
        cin >> Am;
        enterAm = false;
        if(Am <= 0)
        {
            cout << "Am is not valid! Please  re-enter Am \n";
            enterAm = true;
        }
    }

    for(int i = 0; i< An; i++)
    {
        for(int j =0; j< Am; j++)
        {
            cin >> A[i][j];
        }
    }
}

void enterB()
{
    bool enterBn = true;
    bool  enterBm = true;

    while(enterBn )
    {
        cout << "Bn = ";
        cin >> Bn;
        enterBn = false;
        if(Bn <= 0)
        {
            cout << "Bn is not valid! Please  re-enter Bn \n";
            enterBn = true;
        }
    }

    while(enterBm )
    {
        cout << "Bm = ";
        cin >> Bm;
        enterBm = false;
        if(Bm <= 0)
        {
            cout << "Bm is not valid! Please  re-enter Bm \n";
            enterBm = true;
        }
    }

    for(int i = 0; i< Bn; i++)
    {
        for(int j =0; j< Bm; j++)
        {
            cin >> B[i][j];
        }
    }
}

void AToB()
{
    Bn = An;
    Bm =Am;
    for(int i = 0; i < An ; i++)
    {
        for(int j =0; j <Am; j++)
        {
            B[i][j] = A[i][j];
        }
    }
}

void BToA()
{
    An=Bn;
    Am =Bm;
    for(int i = 0; i < Bn ; i++)
    {
        for(int j =0; j <Bm; j++)
        {
            A[i][j] = B[i][j];
        }
    }
}

void AMultipliedB()
{
    long long C[maxN][maxN];
    for(int i=0; i< An; i++)
    {
        for(int j = 0 ; j < Bm; j++)
        {
            long long sum = 0 ;
            for(int k = 0; k < Am ; k++)
            {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }

    }
    Am = Bm;
    for(int i = 0; i< An; i++)
    {
        for(int j = 0; j<Am; j++)
        {
            A[i][j] = C[i][j];
        }
    }
}

void sum()
{
    for(int i =0 ; i < An; i++)
    {
        for(int j=0; j < Am; j++)
        {
            A[i][j] += B[i][j];
        }
    }
}


void Submission()
{
    for(int i =0 ; i < An; i++)
    {
        for(int j=0; j < Am; j++)
        {
            A[i][j] -= B[i][j];
        }
    }
}

void aMultipliedA()
{
    long long a = 0;
    cout << "a = ";
    cin >> a;
    for(int i =0 ; i < An; i++)
    {
        for(int j=0; j < Am; j++)
        {
            A[i][j] *= a;
        }
    }
}


void GetA()
{
    cout << "     _";
    for(int i =0; i < 2*Am-1 ; i++)
    {
        cout<<" ";
    }
    cout<<"_\n";
    for(int i=0; i< An ; i++)
    {
        if(i == An/2)
        {
            cout<<"A = |";
        }
        else
        {
            cout<<"    |";
        }
        for(int j = 0; j <Am; j++)
        {
            cout << " " << A[i][j];
        }
        cout<<" |\n";
    }
    cout << "     -";
    for(int i =0; i < 2*Am-1 ; i++)
    {
        cout<<" ";
    }
    cout<<"-\n";
}

void GetB()
{
    cout << "     _";
    for(int i =0; i < 2*Bm-1 ; i++)
    {
        cout<<" ";
    }
    cout<<"_\n";
    for(int i=0; i< Bn ; i++)
    {
        if(i == Bn/2)
        {
            cout<<"B = |";
        }
        else
        {
            cout<<"    |";
        }
        for(int j = 0; j <Bm; j++)
        {
            cout << " " << B[i][j];
        }
        cout<<" |\n";
    }
    cout << "     -";
    for(int i =0; i < 2*Bm-1 ; i++)
    {
        cout<<" ";
    }
    cout<<"-\n";
}

int main()
{
    while(1)
    {
        int number;
        cout << "-------------------\n";
        cout << "| Exit    |   0   |\n";
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


        cout << "| A - B   |   8   |\n";
        cout << "-------------------\n";
        cout << "| a * A   |   9   |\n";
        cout << "-------------------\n";



        cout << "| Get A  |   12   |\n";
        cout << "-------------------\n";
        cout << "| Get B  |   13   |\n";
        cout << "-------------------\n";
        cout << "number = ";
        cin >> number;

        if(number == 0)
        {
            cout << "Goodbye :(";
            return 0;
        }
        else if(number == 1)
        {
            enterA();
            cout << "done successfully!\n";
        }
        else if(number == 2)
        {
            enterB();
            cout << "done successfully!\n";
        }
        else if(number == 3)
        {
            if(An == 0 )
            {
                cout << "What's A? Please enter number 1 to enter A then go back! \n";
            }
            else
            {
                AToB();
                cout << "done successfully!\n";
            }
        }
        else if(number == 4)
        {
            if(Bn == 0)
            {
                cout << "What's B? Please enter number 2 to enter B then go back! \n";
            }
            else
            {
                BToA();
                cout << "done successfully!\n";
            }
        }
        else if(number == 5)
        {
            bool yes = true;
            if(An == 0)
            {
                cout << "What's A? Please enter number 1 to enter A then go back! \n";
                yes = false;
            }
            if(Bn == 0)
            {
                cout << "What's B? Please enter number 2 to enter B then go back! \n";
                yes = false;
            }
            if(Am != Bn && yes)
            {
                cout << "ooh noo!!!! Can not be multiplied!! Must be Am = Bn but Am = "<<Am <<" , Bn = "<< Bn<<"\n";
                yes = false;
            }
            if(yes)
            {
                AMultipliedB();
                cout << "done successfully!\n";
            }
        }
        else if(number == 6)
        {
            bool yes = true;
            if(An == 0)
            {
                cout << "What's A? Please enter number 1 to enter A then go back! \n";
                yes = false;
            }
            if(Bn == 0)
            {
                cout << "What's B? Please enter number 2 to enter B then go back! \n";
                yes = false;
            }
            if((An != Bn || Am != Bm ) && yes)
            {
                if(An != Bn) cout << "ooh noo!!!! Can not be multiplied!! Must be An = Bn but An = "<<An <<" , Bn = "<< Bn<<"\n";
                if(Am != Bm) cout << "ooh noo!!!! Can not be multiplied!! Must be Am = Bm but Am = "<<Am <<" , Bm = "<< Bm<<"\n";
                yes = false;
            }
            if(yes)
            {
                sum();
                cout << "done successfully!\n";
            }
        }
        else if(number == 7)
        {
            //Code
        }
        else if(number == 8)
        {
            bool yes = true;
            if(An == 0)
            {
                cout << "What's A? Please enter number 1 to enter A then go back! \n";
                yes = false;
            }
            if(Bn == 0)
            {
                cout << "What's B? Please enter number 2 to enter B then go back! \n";
                yes = false;
            }
            if((An != Bn || Am != Bm ) && yes)
            {
                if(An != Bn) cout << "ooh noo!!!! Can not be multiplied!! Must be An = Bn but An = "<<An <<" , Bn = "<< Bn<<"\n";
                if(Am != Bm) cout << "ooh noo!!!! Can not be multiplied!! Must be Am = Bm but Am = "<<Am <<" , Bm = "<< Bm<<"\n";
                yes = false;
            }
            if(yes)
            {
                Submission();
                cout << "done successfully!\n";
            }
        }
        else if(number == 9)
        {
            if(An == 0)
            {
                cout << "What's A? Please enter number 1 to enter A then go back! \n";
            }
            else
            {
                aMultipliedA();
                cout << "done successfully!\n";
            }
        }
        else if(number == 10)
        {
            //Code
        }
        else if(number == 11)
        {
            //Code
        }
        else if(number == 12)
        {
            if(An == 0)
            {
                cout << "What's A? Please enter number 1 to enter A then go back! \n";
            }
            else
            {
                GetA();
            }
        }
        else if(number == 13)
        {
            if(Bn == 0)
            {
                cout << "What's B? Please enter number 1 to enter B then go back! \n";
            }
            else
            {
                GetB());
            }
        }
    }
}
