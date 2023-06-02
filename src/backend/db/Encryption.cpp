//Encryption algorithm from geeksforgeeks, will edit

#include <bits/stdc++.h>
#include <fstream>
using namespace std;

class secDB {
    int key;
    string file = "geeksforgeeks.txt";
    char c;
 
public:
    void encrypt();
    void decrypt();
};

void secDB::encrypt()
{
    cout << "key: ";
    cin >> key;
 
    fstream fin, fout;
    fin.open(file, fstream::in);
    fout.open("encrypt.txt", fstream::out);
 
    while (fin >> noskipws >> c) {
        int temp = (c + key);
        fout << (char)temp;
    }
 
    fin.close();
    fout.close();
}
 
void secDB::decrypt()
{
    cout << "key: ";
    cin >> key;
    fstream fin;
    fstream fout;
    fin.open("encrypt.txt", fstream::in);
    fout.open("decrypt.txt", fstream::out);
 
    while (fin >> noskipws >> c) {
        int temp = (c - key);
        fout << (char)temp;
    }
 
    fin.close();
    fout.close();
}
 
// Driver Code
// int main()
// {
//     secDB enc;
//     char c;
//     cout << "\n";
//     cout << "Enter Your Choice : -> \n";
//     cout << "1. encrypt \n";
//     cout << "2. decrypt \n";
//     cin >> c;
//     cin.ignore();
 
//     switch (c) {
//     case '1': {
//         enc.encrypt();
//         break;
//     }
//     case '2': {
//         enc.decrypt();
//         break;
//     }
//     }
// }