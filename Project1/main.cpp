#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <time.h>
#include <chrono>
using namespace std;

struct Question
{
    unsigned index = 0;
    int num1 = 0, num2 = 0;
    double correct_solution = 0.;
    char calculate_type = 0;
};

int main() {
    // 输入问题的数量
    unsigned question_amount = 0;
    cout << "Please enter the amount of questions that you want to exercise: " << endl;
    cin >> question_amount;
    // 输入问题的难度, 难度决定运算数字的大小范围
    int difficulty;
    cout << "Please choose the difficulty of questions. [1/2/3]"
         << "\n1: range of calculated numbers is under 10."
         << "\n2: range of calculated numbers is under 100."
         << "\n3: range of calculated numbers is under 1000." << endl;
    int range;
    while(cin >> difficulty)
    {
        if(difficulty == 1)
        {
            range = 10;
            break;
        }
        else if(difficulty == 2)
        {
            range = 100;
            break;
        }
        else if(difficulty == 3)
        {
            range = 1000;
            break;
        }
        else
        {
            cout << "The difficulty of question is not entered correctly, please enter the difficulty of questions again:" << endl;
        }
    }

    // 输入是否包含乘除法。若是，则包含加减乘除法; 若否，则只包含加减法
    string s;
    bool isMulDivContained;
    cout << "Should the exercise contain multiplication and division [yes/no]: " << endl;
    while(cin >> s)
    {
        if(s[0] == 'y')
        {
            isMulDivContained = true;
            break;
        }
        else if(s[0] == 'n')
        {
            isMulDivContained = false;
            break;
        }
        else{
            cout << "Please enter yes/no correctly: " << endl;
        }
    }

    unsigned correct_answers = 0;
    vector<Question> question_wrong;
    vector<double> used_times;
    srand((unsigned)time(NULL));

    cout << "********The exercise of calculation of two numbers begins!*********************" << endl;;
    for(decltype(question_amount) i = 1; i <= question_amount; ++i)
    {
        // 使用随机数种子产生随机数
        int num1 = rand()%range + 1;     // number between 1 ~ range
        int num2 = rand()%range + 1;
        int calculate_type;
        if(isMulDivContained)
            calculate_type = rand()%4;
        else
            calculate_type = rand()%2;

        // 计算正确答案
        double correct_solution;
        switch(calculate_type)
        {
            case 0:
                correct_solution = num1 + num2;
                break;
            case 1:
                correct_solution = num1 - num2;
                break;
            case 2:
                correct_solution = num1 * num2;
                break;
            case 3:
                correct_solution = static_cast<double>(num1) / num2;
                break;
        }

        string symbols = "+-*/";
        cout << "Question " << i << ": " << num1 << symbols[calculate_type] << num2 << " = " << endl;;

        // 使用chrono记录每道题的用时
        auto startTime = chrono::system_clock::now();    //计时开始

        double answer = 0.;
        cin >> answer;

        auto endTime = chrono::system_clock::now();   //计时结束
        auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
        // 计算用时，精确到毫秒，并存储到容器中
        used_times.push_back(double(duration.count()) * chrono::microseconds::period::num / chrono::microseconds::period::den);

        // 答对一道题correct_answers累加1
        if(abs(answer - correct_solution)<1e-6)
            correct_answers++;
        else
        {
            // 将用户答错的题的信息记录下来，方便后续进行输出
            Question question;
            question.index = i;
            question.num1 = num1;
            question.num2 = num2;
            question.correct_solution = correct_solution;
            question.calculate_type = symbols[calculate_type];
            question_wrong.push_back(question);
        }
    }

    // 计算平均用时和最短用时
    double time_sum = 0;
    double time_min = 1e6;
    for(auto time:used_times)
    {
        time_sum += time;
        if(time < time_min)
            time_min = time;
    }
    double time_average = time_sum/used_times.size();


    // 输出关于用户答题情况的所有信息
    if(correct_answers == question_amount) {
        cout << "Congratulations, you have answered all questions correctly!   ["
             << correct_answers << "/" << question_amount << "]"
             << "\nThe score you have gotten: " << static_cast<int>(static_cast<double>(correct_answers)/question_amount*100)
             << "\nUsed average time: " << time_average << " s, Shortest time: " << time_min << " s." << endl;
    }
    else
    {
        cout << "The correctly solved questions:  [" << correct_answers << "/" << question_amount << "]"
             << "\nThe score you have gotten: " << static_cast<int>(static_cast<double>(correct_answers)/question_amount*100)
             << "\nUsed average time: " << time_average << " s, Shortest time: " << time_min << " s."
             << "\nThe following questions are not correctly solved, the correct answers are given as following:" << endl;
        for(const auto &question:question_wrong) {
            cout << "Question " << question.index << ": " << question.num1 << " "
                 << question.calculate_type << " " << question.num2 << " = "
                 << (question.calculate_type != '/' ? static_cast<int>(question.correct_solution) : question.correct_solution) << endl;
        }
    }


    return 0;
}
