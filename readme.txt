This is README file for Algorithm PA#3
Author: <»¯«Û¦w B06901176>
Date: 2019/12/27
=====
SYNOPSIS:

./cb <input_file_name> <output_file_name>
=====
DIRECTORY:

public_cases/   input data
src/ 	  source C++ codes
======
HOW TO CIMPILE:

Then compile the demo, simply follow the following steps
	make
======
HOW TO RUN:

	./cb <input_file_name> <output_file_name>
 
	For example,
	./cb public_cases/public_case_1.in test
======
HOW TO VERIFY Answer

    ./PA3/pa3_checker <input_file_name> <output_file_name>
    
	For example,
	./PA3/pa3_checker public_cases/public_case_1.in test
======
HOW TO VERIFY Submit

    ./PA3/checkSubmitPA3.sh <input_tgz>
    
	For example,
	./PA3/checkSubmitPA3.sh b06901176_pa3.tgz
======
OTHER NOTICE:
If your code run well for small test case but get "Segmentation fault" for the large test case, you can use the the following commend to increase the stack size to 256MB:
    ulimit -s 262144