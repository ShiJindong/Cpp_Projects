# Project 3
---
文件夹Project3_Jindong_Shi内有四个文件夹，分别是
basic1:  给包含字母a~z的原始文件进行加密解密，码本文件包含a~z这26个字母
extend1: 给包含数字0~255的原始文件进行加密解密，码本文件包含0~255这256个数字
extend2: 加密解密一个任意可执行文件，使用的码本文件与extend1中一致，包含0~255这256个数字 
         以上这三个文件夹中可执行文件均位于各自的app文件夹内，源文件均位于各自的src文件夹内
pic:     程序运行结果展示，包含四个图片, 分别是basic1.png, extend1.png, extend2.png, test.png



对各个任务的说明:

- basic1:
	执行命令:
	
		cd   basic1
		app/encrypt_basic1   codebook.txt   original_file.txt    encrypted_file.txt
		(程序会提示是否重新生成一个含有字母a~z打乱顺序的码本文件，可输入yes/no进行选择。如果yes，则重新生成一个码本文件，否则使用现存文件夹内的码本文件)
		(程序结束后会提示文件加密成功，在basic1文件夹目录下会生成加密文件 encrypted_file.txt)
		app/decrypt_basic1   codebook.txt   encrypted_file.txt   decrypted_file.txt
		(程序结束后会提示文件解密成功，在basic文件夹目录下会生成解密文件 decrypted_file.txt)

	这里 
		codebook.txt是码本文件
		original_file.txt是未加密之前的文件
		encrypted_file.txt是加密后的文件
		decrypted_file.txt是解密后的文件

	---> 程序运行结果见 pic/basic1.png，我们看到 original_file.txt 与 decrypted_file.txt 内的数据一致，证明加密解密成功
	

- extend1:
	执行命令:
	
		cd   extend1
		app/encrypt_extend1   codebook.txt   original_file.txt    encrypted_file.txt
		(程序会提示是否重新生成一个含有数字0~255打乱顺序的码本文件，可输入yes/no进行选择。如果yes，则重新生成一个码本文件，否则使用现存文件夹内的码本文件)
		(程序结束后会提示文件加密成功，在extend1文件夹目录下会生成加密文件 encrypted_file.txt)

		app/decrypt_extend1   codebook.txt   encrypted_file.txt   decrypted_file.txt
		(程序结束后会提示文件解密成功，在extend1文件夹目录下会生成解密文件 decrypted_file.txt)

	这里 
		codebook.txt是码本文件
		original_file.txt是未加密之前的文件
		encrypted_file.txt是加密后的文件
		decrypted_file.txt是解密后的文件
	---> 程序运行结果见 pic/extend1.png，我们看到 original_file.txt 与 decrypted_file.txt 内的数据一致，证明加密解密成功


- extend2:
	先将 basic1/app 内的两个可执行文件 encrypt_basic1 和 decrypt_basic1 放入文件夹 extend2/app_file_from_basic1/ 内:
	
	然后执行命令:
		cd   extend2
	   加密解密可执行文件 encrypt_basic1:
		app/encrypt_extend2   codebook.txt   app_file_from_basic1/encrypt_basic1    app_file_after_encrypt_decrypt/encrypt_basic1_encrypted
		app/decrypt_extend2   codebook.txt   app_file_after_encrypt_decrypt/encrypt_basic1_encrypted   app_file_after_encrypt_decrypt/encrypt_basic1_decrypted
	   加密解密可执行文件 decrypt_basic1:
		app/encrypt_extend2   codebook.txt   app_file_from_basic1/decrypt_basic1    app_file_after_encrypt_decrypt/decrypt_basic1_encrypted
		app/decrypt_extend2   codebook.txt   app_file_after_encrypt_decrypt/decrypt_basic1_encrypted   app_file_after_encrypt_decrypt/decrypt_basic1_decrypted

	至此，我们在 extend2/app_file_after_encrypt_decrypt/ 文件夹目录下生成了四个文件: 
	   (encrypt_basic1_encrypted, encrypt_basic1_decrypted, decrypt_basic1_encrypted, decrypt_basic1_decrypted)
	---> 程序运行结果见 pic/extend1.png


	为了测试在extend2中加密解密后得到的可执行文件 encrypt_basic1_decrypted 和 decrypt_basic1_decrypted 是否可以正常运行，我们将其放入文件夹extend2/test/app内
	然后执行命令:
		cd test
	给加密解密后的可执行文件加上可执行权限:
		chmod +x app/encrypt_basic1_decrypted 
		chmod +x app/decrypt_basic1_decrypted 
	利用加密解密后的可执行文件给文件 original_file.txt 进行加密解密:
		app/encrypt_basic1_decrypted   codebook.txt   original_file.txt    encrypted_file.txt
		app/decrypt_basic1_decrypted   codebook.txt   encrypted_file.txt   decrypted_file.txt
	---> 程序运行结果见 pic/test.png。 我们看到test文件夹内 original_file.txt 与 decrypted_file.txt 内的数据一致，证明我们在extend2内对basic1的两个可执行文件加密解密后，这两个可执行文件仍然可以正确运行






对代码的说明:
	
	几个文件夹内的源文件基本上使用的函数是差不多的，就细节上不太一样，由于代码比较易读，这里不再介绍。

	重点说明的一点是，在extend2的源文件内，我们需要以二进制形式读取可执行文件，所以使用的是非格式化I/O的方式，即使用函数ifstream::read()和ofstream::write()。
	我们使用 read 和 write 每次只读取或写入一个char大小的数据。由于我们的码本文件内包含的是0~255的数字，所以我们在读取char后需要加上128，在将char写入到文件前需要先减去128。具体见函数:
	extend2/src/encrypt.cpp:
		void readOriginalFile(vector<int> &original, const string &original_file);
		void encrypt(vector<int> &original, vector<int> &codebook, const string &encrypted_file)
	extend2/src/decrypt.cpp:
		void readEncryptedFile(vector<int> &encrypted, const string &encrypted_file);
		void decrypt(vector<int> &encrypted, vector<int> &codebook, const string &decrypted_file);
