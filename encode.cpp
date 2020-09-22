#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>


/**
The original implementation of the huffman encoding algorithm was derived from
https://www.techiedelight.com/huffman-coding/
The decoding segment of the algorithm was discarded and the encoding segment
was modified to take in a file, create two new files and store the huffman code in
"Huffman.txt" and store the dictionary for decoding the huffman code in "Dictionary.txt"
*/


using namespace std;

int main()
{
    string name, text;
    cout << "Enter name of the file to be decoded most likely 'Huffman.txt': ";
    cin >> name;
    ifstream readfile;
    readfile.open(name, ios::in);

    getline(readfile, text);
    readfile.close();

    unsigned long long int lenlen = text.length();

    string dictionary, dict, tet = "";
    cout << "Enter name of the dictionary, most likely 'Dictionary.txt': ";
    cin >> dictionary;
    ifstream dictfile;
    dictfile.open(dictionary, ios::in);

    while (getline(dictfile, dict))
    {
        tet = tet + "\n" + dict;
    }
    dictfile.close();

    unsigned long long int len = tet.length();
    char names[256];
    string nameValue[256];
    int tempo = 0;

    for (int i = 0; i < len; i++)
    {
        if (tet[i] == '_')
        {
            names[tempo] = tet[i - 2];
            tempo++;
        }
    }
    tempo = 0;
    for (int i = 0; i < len; i++)
    {
        if (tet[i] == '_')
        {
            i = i + 2;
            while (tet[i] != '~')
            {
                nameValue[tempo] = nameValue[tempo] + tet[i];
                i++;
            }
            tempo++;
        }
    }
    string checker = "";

    tempo++;

    ofstream finfile;
    finfile.open("Original.txt", ios::app);

    for (int i = 0; i < lenlen; i++)
    {
        checker = checker + text[i];
        for (int j = 0; j < tempo; j++)
        {
            if (checker == nameValue[j])
            {
                finfile << names[j];
                checker = "";
                break;
            }
        }
    }
    finfile.close();

    return 0;
}
