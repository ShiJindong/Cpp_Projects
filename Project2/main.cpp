#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<cassert>
#include<math.h>


using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::ifstream;
using std::cerr;

void write_data_to_vector(vector<int> &num,  bool &is_num_positive, const string &line, const int base)
{
    for(string::size_type i = 0; i != line.size(); ++i)
    {
        if( !i && (line[i] == '-' || line[i] == '+') )
        {
            if(line[i] == '-')
                is_num_positive = false;
            else
                is_num_positive = true;
        }
        else
        {
            // ASCII Chart:
            // 0...9:   48 ~ 57
            // A...Z:   65 ~ 90
            // a...z:   97 ~ 122

            int ch = static_cast<int>(line.c_str()[i]);

            if(base > 0 && base <= 10)
                if(!(ch >= 48 && ch < base + 48)) {
                    cerr << "The number " << line << " can not be expressed in base " << base << " ." << endl;
                    assert(false);
                }
            if (base > 10 && base <= 36)
                if(!((ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 65 + base - 11) ||  (ch >= 97 && ch <= 97 + base - 11))) {
                    cerr << "The number " << line << " can not be expressed in base " << base << " ." << endl;
                    assert(false);
                }

            if(ch >= 48 && ch <= 57)
                num.push_back(ch - 48);
            else if(ch >= 65 && ch <= 90)
                num.push_back(ch - 55);
            else if(ch >= 97 && ch <= 122)
                num.push_back(ch - 87);
        }
    }

}

void num_aligned(vector<int> &num1, vector<int> &num2)
{
    if(num1.size() >= num2.size())
    {
        vector<int> num2_aligned(num1.size() - num2.size(), 0);
        num2_aligned.insert(num2_aligned.end(), num2.cbegin(), num2.cend());
        num2 = num2_aligned;
    }
    else
    {
        vector<int> num1_aligned(num2.size() - num1.size(), 0);
        num1_aligned.insert(num1_aligned.end(), num1.cbegin(), num1.cend());
        num1 = num1_aligned;
    }
}

void read_data(const string &filename, vector<int> &num1, bool &is_num1_positive, vector<int> &num2, bool &is_num2_positive, const int base)
{
    ifstream ifs(filename);
    if(!ifs.is_open())
        cout << "File " << filename << " is not found." << endl;
    string line1, line2;
    getline(ifs, line1);
    getline(ifs, line2);

    for(const auto &s : line1)
        cout << s << " ";
    cout << "   --->num1" << endl;
    for(const auto &s : line2)
        cout << s << " ";
    cout << "   --->num2" << endl;

    write_data_to_vector(num1, is_num1_positive, line1, base);
    write_data_to_vector(num2, is_num2_positive, line2, base);

    num_aligned(num1, num2);

}

bool compare_num(vector<int> &num1, vector<int> &num2)
{
    // If num2 > num1, return true
    for(vector<int>::size_type i = 0; i != num1.size(); )
    {
        if (num2[i] > num1[i])
            return true;
        else if(num2[i] < num1[i])
            return false;
        else
            ++i;
    }
    return false;
}

bool add_num( vector<int>& result, vector<int> &num1, bool &is_num1_positive, vector<int> &num2, bool &is_num2_positive, const int base)
{
    result = vector<int>(num1.size(), 0);
    vector<int> result_single_position(num1.size(), 0);
    if(!(is_num1_positive ^ is_num2_positive))
    {
        // addition
        int carry = 0;
        for(int i = num1.size() - 1; i >= 0; --i)
        {
            result_single_position[i] = num1[i] + num2[i] + carry;
            result[i] = result_single_position[i] % base;
            carry = result_single_position[i] / base;
        }
        if(carry)
            result.insert(result.begin(), 1);

        if((!is_num1_positive) && (!is_num1_positive))
            return false;
        return true;
    }
    else
    {
        // subtraction
        bool is_num2_greater = compare_num(num1, num2);
        if(is_num2_greater)
            std::swap(num1, num2);

        int borrow = 0;
        for(int i = num1.size() - 1; i >= 0; --i)
        {
            if(num1[i] - borrow < num2[i])
            {
                result_single_position[i] = num1[i] - num2[i] - borrow + base;
                borrow = 1;
            }
            else
            {
                result_single_position[i] = num1[i] - num2[i] - borrow;
                borrow = 0;
            }
            result[i] = result_single_position[i];
        }

        if((is_num1_positive && is_num2_greater) || (!is_num1_positive && !is_num2_greater))
            return false;
        return true;
    }
}

void from_decimal_to_output_base(vector<int> &input, vector<int> &output, const int base, const int output_base)
{
    // 第1版: 不能处理大数
    /*
    int sum = 0;
    vector<int> temp;
    for(vector<int>::size_type i = 0; i < input.size(); ++i)
        sum += static_cast<int>(input[i] * std::pow(base, (input.size() - i - 1) * 1.0));
    int quotient = sum;
    int remainder = 0;
    while(quotient)
    {
        remainder = quotient % output_base;
        quotient /= output_base;
        temp.push_back(remainder);
    }
    for(int i = temp.size() - 1; i >= 0; --i)
        output.push_back(temp[i]);
    */


    // 迭代版: 能够处理大数
    vector<int> quotient = input;
    vector<int> temp;
    bool is_quotient_zero = false;

    while(!is_quotient_zero)
    {
        int remainder = 0;
        for(vector<int>::size_type i = 0; i != input.size(); ++i)
        {
            int temp_remainder = (quotient[i] + remainder * base) % output_base;
            quotient[i] = (quotient[i] + remainder * base) / output_base;
            remainder = temp_remainder;
        }
        temp.push_back(remainder);

        for(auto iter = quotient.cbegin(); iter != quotient.cend(); ++iter) {
            if (*iter != 0) {
                is_quotient_zero = false;
                break;
            }
            if(iter == quotient.cend() - 1)
                is_quotient_zero = true;
        }
    }

    for(auto r_iter = temp.crbegin(); r_iter != temp.crend(); ++r_iter)
        output.push_back(*r_iter);

}



void show_num(vector<int> &num, const bool is_num_positive, const int base)
{
    if(!is_num_positive)
        cout << "-" << " ";
    else
        cout << "  ";

    for(auto iter = num.begin(); iter != num.end(); )
    {
        if(*iter == 0)
            iter = num.erase(iter);
        else
            break;
    }

    // ASCII Chart:
    // 0...9:   48 ~ 57
    // A...Z:   65 ~ 90
    // a...z:   97 ~ 122
    if(base > 10)
    {
        for(const auto &i : num)
        {
            char ch;
            if(i>=0 && i<=9)
                ch = static_cast<char>(i+48);
            else if(i>=10 && i<=35)
                ch = static_cast<char>(i+55);
            cout << ch << " ";
        }
    }
    else
    {
        for(const auto &i : num)
        {
            cout << i << " ";
        }

    }
}

int main(int argc, char* argv[])
{
    string filename = argv[1];
    int calculate_base = atoi(argv[2]);
    int output_base = atoi(argv[3]);

    vector<int> num1, num2;
    bool is_num1_positive = true, is_num2_positive = true;
    read_data(filename, num1, is_num1_positive, num2, is_num2_positive, calculate_base);


    vector<int> result_in_calculate_base;
    bool is_result_positive = add_num(result_in_calculate_base, num1, is_num1_positive, num2, is_num2_positive, calculate_base);



    vector<int> result_in_output_base;
    from_decimal_to_output_base(result_in_calculate_base, result_in_output_base, calculate_base, output_base);

    cout << "= ------------------------" << endl;
    show_num(result_in_calculate_base, is_result_positive, calculate_base);
    cout << "       --->  Result in calculate base: " << calculate_base << endl;

    show_num(result_in_output_base, is_result_positive, output_base);
    cout << "       --->  Result in output base:: " << output_base << endl;


    return 0;
}
