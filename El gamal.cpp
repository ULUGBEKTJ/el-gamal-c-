#include <iostream>
#include <fstream>
#include <string>
using namespace std;



int power(int a, int b, int n) {// a^b mod n вспомогательная функция 
    int tmp = a;
    int sum = tmp;
    for (int i = 1; i < b; i++) {
        for (int j = 1; j < a; j++) {
            sum += tmp;
            if (sum >= n) {
                sum -= n;
            }
        }
        tmp = sum;
    }
    return tmp;
}

int mul(int a, int b, int n) {// a*b mod nвспомогательная функция 
    int sum = 0;

    for (int i = 0; i < b; i++) {
        sum += a;

        if (sum >= n) {
            sum -= n;
        }
    }

    return sum;
}

/*****************************************************
    p - простое число
    0 < g < p-1
    0 < x < p-1
    m - шифруемое сообщение m < p
*****************************************************/




void decrypt(int p, int x) // расшифровка
{
    string nam = "out.txt"; //
    ifstream inf(nam.c_str());// выходной файл, там хранится шифр

    cout << "\nДешифрованый текст:" << endl;

    while (inf.good()) {
        int a = 0;
        int b = 0;
        inf >> a;
        inf >> b;

        if (a != 0 && b != 0) {
            wcout << "  " << a << " " << b << endl;

            int deM = mul(b, power(a, p - 1 - x, p), p);// m=b*(a^x)^(-1)mod p =b*a^(p-1-x)mod p  формула
            char m = static_cast<char>(deM);// преобразования числа шифра в char символ
            wcout << m;
        }
    }

    cout << endl;

    inf.close();
}








void crypt(int p, int g, int x, string text) // функции шифрования
{
    string text1 = text.c_str();

    string nam = "out.txt";
    ofstream outf(nam.c_str());

    int y = power(g, x, p);

    cout << "Открытый ключ (p,g,y)=" << "(" << p << "," << g << "," << y << ")" << endl;
    cout << "Закрытый ключ x=" << x << endl;
    cout << "\nШифруемый текст:" << endl;

    for (int i = 0; i < text1.length(); i++)
    {
        int m = text1[i];
        if (m > 0)
        {
            cout << (char)m;
            int k = rand() % (p - 2) + 1; // 1 < k < (p-1)
            int a = power(g, k, p);
            int b = mul(power(y, k, p), m, p);

            outf << a << " " << b << " ";
        }
    }

    cout << endl;

    outf.close();

}



int main()
{
    setlocale(LC_ALL, "rus");
    string text;
    getline(cin, text);//чтение

    crypt(593, 123, 8, text);
    decrypt(593, 8);

    system("pause");
    return 0;
}