all: hw3 read

hw3: hw3.c
	gcc hw3.c -o hw3

read: read.c
	gcc read.c -o read -lm

