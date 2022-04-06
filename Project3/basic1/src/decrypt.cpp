#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#include<cassert>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::vector;
using std::string;

void useExistingCodebook(vector<char> &codebook, const string &codebook_file)
{
    std::ifstream ifs_codebook(codebook_file);
    string codebook_line;

    if(ifs_codebook.is_open())
    {
        while (std::getline(ifs_codebook, codebook_line))
        {
            for (const auto ch: codebook_line)
                codebook.push_back(ch);
        }
    }
    else
    {
        cerr << "The file " << codebook_file << " can not be found." << endl;
        assert(false);
    }
    ifs_codebook.close();
}

void readEncryptedFile(vector<char> &encrypted, const string &encrypted_file)
{
    std::ifstream ifs_encrypted(encrypted_file);
    string encrypted_line;
    if(ifs_encrypted.is_open())
    {
        while(std::getline(ifs_encrypted, encrypted_line))
        {
            for(const auto ch : encrypted_line)
                encrypted.push_back(ch);
        }
    }
    else
    {
        cerr << "The file " << encrypted_file << " can not be found." << endl;
        assert(false);
    }
    ifs_encrypted.close();
}

void decrypt(vector<char> &encrypted, vector<char> &codebook, const string &decrypted_file)
{
    // ASCII Chart:
    // 0...9:   48 ~ 57
    // A...Z:   65 ~ 90
    // a...z:   97 ~ 122

    vector<char> decrypted;
    unsigned char_order = 0;
    for(const auto ch : encrypted)
    {
        if(!(std::ispunct(ch) || std::isspace(ch)))
        {
            char_order = std::find(codebook.cbegin(), codebook.cend(), ch) - codebook.cbegin();
            decrypted.push_back(static_cast<char>(char_order + 97));
        }
        else
        {
            decrypted.push_back(ch);
        }
    }

    std::ofstream ofs_decrypted(decrypted_file);
    for(const auto ch : decrypted)
        ofs_decrypted << ch;
    cout << "Decryption is finished!" << endl;
}


int main(int argc, char* argv[]) {
    string codebook_file = argv[1];
    string encrypted_file = argv[2];
    string decrypted_file = argv[3];

    vector<char> codebook;
    vector<char> encrypted;
    vector<char> decrypted;

    useExistingCodebook(codebook, codebook_file);
    readEncryptedFile(encrypted, encrypted_file);
    decrypt(encrypted, codebook, decrypted_file);

    return 0;
}
