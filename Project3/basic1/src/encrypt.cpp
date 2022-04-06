#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<cassert>
#include<algorithm>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::vector;
using std::string;

void generateNewCodebook(vector<char> &codebook, const string &codebook_file)
{
    for(int i = 0; i != 26; ++i)
        codebook.push_back(static_cast<char>(i + 97));
    std::srand(time(NULL));
    std::random_shuffle(codebook.begin(), codebook.end());

    std::ofstream ofs_codebook(codebook_file);
    for(const auto i : codebook)
        ofs_codebook << i;
    ofs_codebook.close();
    cout << "A new codebook is generated!" << endl;
}

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
    cout << "The existing codebook is used for encryption!" << endl;
}


void readOriginalFile(vector<char> &original, const string &original_file)
{
    std::ifstream ifs_original(original_file);
    string original_line;
    if(ifs_original.is_open())
    {
        while(std::getline(ifs_original, original_line))
        {
            for(const auto ch : original_line)
                original.push_back(ch);
        }
    }
    else
    {
        cerr << "The file " << original_file << " can not be found." << endl;
        assert(false);
    }
    ifs_original.close();
}

void encrypt(vector<char> &original, vector<char> &codebook, const string &encrypted_file)
{
    // ASCII Chart:
    // 0...9:   48 ~ 57
    // A...Z:   65 ~ 90
    // a...z:   97 ~ 122
    vector<char> encrypted;
    char ch_lower = ' ';
    unsigned char_order = 0;
    for(const auto ch : original)
    {
        if(!(std::ispunct(ch) || std::isspace(ch)))
        {
            ch_lower = std::tolower(ch);
            char_order = static_cast<int>(ch_lower) - 97;
            encrypted.push_back(codebook[char_order]);
        }
        else
        {
            encrypted.push_back(ch);
        }
    }

    std::ofstream ofs_encrypted(encrypted_file);
    for(const auto ch : encrypted)
        ofs_encrypted << ch;
    cout << "Encryption is finished!" << endl;
}

int main(int argc, char* argv[]) {
    string codebook_file = argv[1];
    string original_file = argv[2];
    string encrypted_file = argv[3];

    vector<char> codebook;
    vector<char> original;

    string s;
    cout << "Generate a new codebook for character a ~ z? [yes/no]" << endl;
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

