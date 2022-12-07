#include <iostream>

using namespace std;

int main()
{
	cout<<"Cryptanalysis Trying all possible solutions:: "<<endl;
    string cipher;
    cout << "Enter cipher text: ";
    cin >> cipher;

    string temps;

    for (int key = 0; key < 26; key++)
    {
        temps = cipher;
        int temp;
        for (int i = 0; i < temps.size(); i++)
        {
            temp = (temps[i] - key - 65) % 26;
            if (temp < 0)
                temp = 26 + temp;
            temps[i] = temp + 97;
        }

        cout << key << " : " <<key<<"  String of plaintext:  "<< temps << endl;
    }
}
