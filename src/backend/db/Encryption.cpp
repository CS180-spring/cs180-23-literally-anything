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