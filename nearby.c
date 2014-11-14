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
	struct Topic* topics = calloc(T, sizeof(struct Topic));
	struct Question* questions = calloc(Q, sizeof(struct Question));
	free(line);
	for (int i = 0; i < T; i++){
		line = getLine(stdin);
		struct Topic new_topic = topics[i];
		new_topic.id = strtol(line, &where_end, 10);
		new_topic.x = strtol(where_end+1, &where_end, 10);
		new_topic.y = strtol(where_end+1, &where_end, 10);
		free(line);
	}
	for (int i = 0; i < Q; i++){
		line = getLine(stdin);
		struct Question new_question = questions[i];
		new_question.id = strtol(line, &where_end, 10);
		int num_topics = strtol(where_end+1, &where_end, 10);
		new_question.num_topics = num_topics;
		int* topics = calloc(num_topics, sizeof(int));
		for (int j = 0; j < num_topics; j++){
			topics[j] = strtol(where_end+1, &where_end, 10);
		}
		new_question.topics = topics;
		free(line);
	}
	for (int i = 0; i < Q; i++){
		line = getLine(stdin);
		char type = line[0];
		int num_queries = strtol(line+2, &where_end, 10);
		double x = strtol(where_end+1, &where_end, 10);
		double y = strtol(where_end+1, &where_end, 10);
		if (type == 't'){
		}
	}


	// printf("T: %d\nQ: %d\nN: %d\n", T, Q, N)
	return 0;
}

void insert_and_shift(int index, double value, double** array_ptr, int length){
	double* array = *array_ptr;
	double holder;
	for(int i = index; i < length; i++){
		holder = array[i];
		array[i] = value;
		value = holder;
	}
}

// need code that binary searches and figures out where to insert
// need to account for the possibility of the difference being less
// than 0.001
