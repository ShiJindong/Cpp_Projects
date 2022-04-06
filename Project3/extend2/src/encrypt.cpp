#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<cassert>
#include<algorithm>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::vector;
using std::string;

void generateNewCodebook(vector<int> &codebook, const string &codebook_file)
{
    for(int i = 0; i != 256; ++i)
        codebook.push_back(i);
    std::srand(time(NULL));
    std::random_shuffle(codebook.begin(), codebook.end());

    std::ofstream ofs_codebook(codebook_file);
    for(const auto i : codebook)
        ofs_codebook << i << " ";
    ofs_codebook.close();
    cout << "A new codebook is generated!" << endl;
}

void useExistingCodebook(vector<int> &codebook, const string &codebook_file)
{
    std::ifstream ifs_codebook(codebook_file);
    string codebook_line;
    string codebook_single_number;
    if(ifs_codebook.is_open())
    {
        while (std::getline(ifs_codebook, codebook_line))
        {
            std::istringstream iss(codebook_line);
            while(iss >> codebook_single_number)
                codebook.push_back(std::stoi(codebook_single_number));
        }
    }
    else
    {
        cerr << "The file " << codebook_file << " can not be found." << endl;
        assert(false);
    }
    ifs_codebook.close();
    if(codebook.size() != 256)
    {
        cerr << "The existing codebook is not correct, please generate a new code book." << endl;
        assert(false);
    }
    cout << "The existing codebook is used for encryption!" << endl;
}

void readOriginalFile(vector<int> &original, const string &original_file)
{
    std::ifstream ifs_original(original_file, std::ifstream::binary);
    char original_single_number;

    if(ifs_original.is_open())
    {
        while(ifs_original.read((char*) &original_single_number, sizeof(char)))
            original.push_back(static_cast<int>(original_single_number) + 128);
            // char的取值范围为-128~127,需将其转化为0~255
    }
    else
    {
        cerr << "The file " << original_file << " can not be found." << endl;
        assert(false);
    }
    ifs_original.close();
}

void encrypt(vector<int> &original, vector<int> &codebook, const string &encrypted_file)
{
    vector<int> encrypted;
    for(const auto num : original)
    {
        if(num < 0 || num > 255)
        {
            cerr << "The original file contains the number which exceed the range of 0 ~ 255." << endl;
            assert(false);
        }
        encrypted.push_back(codebook[num]);
    }

    std::ofstream ofs_encrypted(encrypted_file, std::ofstream::binary);
    for(const auto num : encrypted)
    {
        char num_char = static_cast<char>(num - 128);   // 需将0~255的整数转化为char的取值范围-128~127
        ofs_encrypted.write((char *) &num_char, sizeof(char));
    }

    cout << "Encryption is finished!" << endl;

}

int main(int argc, char* argv[])
{
    string codebook_file = argv[1];
    string original_file = argv[2];
    string encrypted_file = argv[3];

    vector<int> codebook;
    vector<int> original;


    string s;
    cout << "Generate a new codebook for numbers 0 ~ 255? [yes/no]" << endl;
    while(cin >> s)
    {
        if(s[0] == 'y')
        {
            generateNewCodebook(codebook, codebook_file);
            break;
        }
        else if(s[0] == 'n')
        {
            useExistingCodebook(codebook, codebook_file);
            break;
        }
        else{
            cout << "Please enter yes/no correctly: " << endl;
        }
    }

    readOriginalFile(original, original_file);
    encrypt(original, codebook, encrypted_file);

    return 0;
}