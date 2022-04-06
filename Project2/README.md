# Project 2
---
源文件: Project2_Jindong_Shi/main.cpp
可执行文件: Project2_Jindong_Shi/app/project2
记录两个长整数的文件: Project2_Jindong_Shi/data.txt

执行命令:
cd Project2_Jindong_Shi
app/project2  data.txt  10 8

测试案例展示: 
test1.png 用于展示十进制长整数的相加，尽可能的罗列了所有加减情况，总共4个例子:
     1. 两个十进制正整数相加
     2. 两个十进制负整数相加
     3. 一个十进制负整数 加上 一个十进制正整数
     4. 整数前面加0不影响该数的值，并且计算结果中不包含0

test2.png 用于展示某一种进制长整数的相加，并且输出也为输入数值同样的进制，总共4个例子:
     1. 两个二进制正整数相加，输出也为二进制
     2. 两个八进制负整数相加，输出也为八进制
     3. 一个十六进制正整数 加上 一个十六进制负整数，输出也为十六进制
     4. 两个八进制正整数相加，但是由于其中一个整数不合法，提示报错


test3.png 用于展示某一种进制长整数相加，输出为不一样的进制，总共4个例子:
     1. 两个十进制正整数相加，输出为二进制
     2. 一个八进制正整数 加上 一个八进制负整数，输出为三进制
     3. 一个二进制负整数 加上 一个二进制正整数，输出为十六进制


test4.png 两个大数相加:
        -893454371379534379863002565475343543647456834524567
        -532143239474385672346871235680182364884524523454577




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
代码解释:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
变量: 

	calculate_base: 用于保存两个相加的长整数的进制，比如2代表二进制， 8代表八进制， 10代表十进制，16代表十六进制
	output_base: 用于保存输出结果的进制，比如2代表二进制， 8代表八进制， 10代表十进制，16代表十六进制
	bool is_num1_positive, is_num2_positive: 保存两个长整数的正负号
	vector<int> num1, num2: 保存两个长整数的绝对值(也就是不带正负号), 从文件data.txt读取的任意进制的两个长整数的绝对值会先被转化为十进制，保存在int型的容器num1和num2中，其中容器中的每一个元素代表了该十进制长整数某一位上的数字。其中容器元素下标越小，其位数越高，也就是说num1[0]和num2[0]保存了两个长整数十进制形式的最高位，num1[num1.size()]和num2[num2.size()]保存了两个长整数十进制形式的最低位
	vector<int> result_in_calculate_base: 用于保存以calculate_base进制计算出的结果，只不过每一位保存的形式是十进制，比如对于十六进制的计算结果B7D，它在容器result_in_calculate_base中保存的形式为result_in_calculate_base[0] = 11, result_in_calculate_base[1] =7, result_in_calculate_base[2] =13


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
函数:

	void read_data(...): 将文件中的两个长整数以单行string的形式进行读取，并调用函数 void write_data_to_vector(...)
	void write_data_to_vector(...): 将string类型的长整数，读取其正负号和其绝对值，将正负号保存到变量bool is_num1_positive,和is_num2_positive中，将长整数绝对值以十进制形式保存到容器 vector<int> num1, num2
	bool add_num(...): 将某一种进制的两个长整数num1和num2相加或相减 (取决于两个长整数的正负号和其绝对值的大小，通过调用bool compare_num(...)来比较两个长整数num1和num2绝对值的大小)，计算得到同样进制的结果保存到变量result_in_calculate_base，该函数返回的bool值为计算结果的正负号
	bool compare_num(...): 该函数用于比较两个长整数num1和num2绝对值的大小，并返回bool值，该bool值为true，表示num2绝对值更大，该bool值为false，表示num2绝对值并不比num1大
	void from_decimal_to_output_base(): 虽然容器result_in_calculate_base是以calculate_base进制计算出的结果，但容器result_in_calculate_base保存的元素是以calculate_base进制计算出的结果的十进制形式，这个函数将其转化为output_base进制的输出结果
	void show_num(...): 该函数用于将不同进制的数展示到屏幕
