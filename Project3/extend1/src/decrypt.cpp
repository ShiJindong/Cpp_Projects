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
}

void readEncryptedFile(vector<int> &encrypted, const string &encrypted_file)
{
    std::ifstream ifs_encrypted(encrypted_file);
    string encrypted_line;
    string encrypted_single_number;
    if(ifs_encrypted.is_open())
    {
        while (std::getline(ifs_encrypted, encrypted_line))
        {
            std::istringstream iss(encrypted_line);
            while(iss >> encrypted_single_number)
                encrypted.push_back(std::stoi(encrypted_single_number));
        }
    }
    else
    {
        cerr << "The file " << encrypted_file << " can not be found." << endl;
        assert(false);
    }
    ifs_encrypted.close();

}


void decrypt(vector<int> &encrypted, vector<int> &codebook, const string &decrypted_file)
{
    vector<int> decrypted;
    for(const auto num : encrypted)
    {
        if(num < 0 || num > 255)
        {
            cerr << "The encrypted file contains the number which exceed the range of 0 ~ 255." << endl;
            assert(false);
        }
        decrypted.push_back(std::find(codebook.cbegin(), codebook.cend(), num) - codebook.cbegin());
    }

    std::ofstream ofs_decrypted(decrypted_file);
    for(const auto num : decrypted)
        ofs_decrypted << num << " ";

    cout << "Decryption is finished!" << endl;
}

int main(int argc, char* argv[]) {
    string codebook_file = argv[1];
    string encrypted_file = argv[2];
    string decrypted_file = argv[3];

    vector<int> codebook;
    vector<int> encrypted;

    useExistingCodebook(codebook, codebook_file);
    readEncryptedFile(encrypted, encrypted_file);
    decrypt(encrypted, codebook, decrypted_file);

    return 0;
}