#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "getLine.h"

#define MAXT 10000
#define MAXQ 1000
#define MAXN 10000

#define TRUE 1
#define FALSE 0

// you should have an array of topics and an array of questions

struct Topic{
	int id;
	double x;
	double y;
};

struct Question{
	int id;
	int num_topics;
	int* topics;
};

int main(int argc, char** argv){
	char* line = getLine(stdin);
	int T;
	int Q;
	int N;
	char* where_end;
	T = strtol(line, &where_end, 10);
	Q = strtol(where_end+1, &where_end, 10);
	N = strtol(where_end+1, &where_end, 10);
	printf("T: %d\nQ: %d\nN: %d\n", T, Q, N);
	return 0;
}
