all : sam1 sam2 sam3 prog

sam1: sample1.c
	gcc -o s1 sample1.c -pthread

sam2: sample2.c
	gcc -o s2 sample2.c -pthread

sam3: sample3.c
	gcc -o s3 sample3.c -pthread

prog: lab6.cpp
	g++ -o run lab6.cpp -pthread
