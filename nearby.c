#include <stdio.h>
#include <math.h>
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


void reset(double** values_ptr, int length);
int binary_search(int* ids, int id, double* values, double value, int min_index, int max_index);
void insert_and_shift(int index, double value, int** array_ptr, int length);
int mid_point(int min_index, int max_index);
double best_topic_value(int* children, int num_children, double x, double y, double** valuesT_ptr, struct Topic** topics_ptr);


int main(int argc, char** argv){
	char* line = getLine(stdin);
	int T;
	int Q;
	int N;
	char* where_end;
	T = strtol(line, &where_end, 10);
	Q = strtol(where_end+1, &where_end, 10);
	N = strtol(where_end+1, &where_end, 10);
	struct Topic* topics = malloc(T*sizeof(struct Topic));
	struct Question* questions = malloc(Q*sizeof(struct Question));
	free(line);
	for (int i = 0; i < T; i++){
		line = getLine(stdin);
		struct Topic new_topic = topics[i];
		new_topic.id = strtol(line, &where_end, 10);
		new_topic.x = strtod(where_end+1, &where_end);
		new_topic.y = strtod(where_end+1, &where_end);
		topics[i] = new_topic;
		free(line);
	}
	int num_zero = 0;
	for (int i = 0; i < Q; i++){
		line = getLine(stdin);
		struct Question new_question = questions[i];
		new_question.id = strtol(line, &where_end, 10);
		int num_topics = strtol(where_end+1, &where_end, 10);
		if (num_topics == 0)
			num_zero += 1;
		new_question.num_topics = num_topics;
		int* q_topics = malloc(num_topics*sizeof(int));
		for (int j = 0; j < num_topics; j++){
			q_topics[j] = strtol(where_end+1, &where_end, 10);
		}
		new_question.topics = q_topics;
		questions[i] = new_question;
		free(line);
	}
	double* valuesT = malloc(T*sizeof(double));
	double* valuesQ = malloc(Q*sizeof(double));
	int* ids = malloc(10*sizeof(int));
	for (int i = 0; i < N; i++){
		line = getLine(stdin);
		char type = line[0];
		int num_queries = strtol(line+2, &where_end, 10);
		double x = strtod(where_end+1, &where_end);
		double y = strtod(where_end+1, &where_end);
		int index;
		if (type == 't'){
			if (T < num_queries)
				num_queries = T;
			for (int i = 0; i < T; i++){
				double value = sqrt(pow(x-topics[i].x, 2)+pow(y-topics[i].y, 2)); 
				valuesT[i] = value;
				int id = topics[i].id;
				int length = num_queries;
				int one_more = 0;
				if (i < num_queries){
					length = i;
					one_more = 1;
				}
				index = binary_search(ids, id, valuesT, value, 0, length-1);
				insert_and_shift(index, id, &ids, length+one_more);
			}
			for (int i = 0; i < num_queries; i++){
				if (i != num_queries-1)
					printf("%d ", ids[i]);
				else
					printf("%d", ids[i]);
			}
			printf("\n");
		} else {
			reset(&valuesT, T);
			if (Q-num_zero < num_queries)
				num_queries = Q-num_zero;
			struct Question question;
			for (int i = 0; i < Q; i++){
				question = questions[i];
				int num_topics = question.num_topics;
				if (num_topics != 0){
					double best = best_topic_value(question.topics, num_topics, x, y, &valuesT, &topics);
					valuesQ[i] = best;
					int id = question.id;
					int length = num_queries;
					int one_more = 0;
					if (i < num_queries){
						length = i;
						one_more = 1;
					}
					index = binary_search(ids, id, valuesQ, best, 0, length-1);
					insert_and_shift(index, id, &ids, length+one_more);
				}
			}
			for (int i = 0; i < num_queries; i++){
				if (i != num_queries-1)
					printf("%d ", ids[i]);
				else
					printf("%d", ids[i]);
			}
			printf("\n");
		}
		free(line);
	}


	// printf("T: %d\nQ: %d\nN: %d\n", T, Q, N)
	return 0;
}

void reset(double** values_ptr, int length){
	double* values = *values_ptr;
	for (int i = 0; i < length; i++){
		values[i] = -1;
	}
}


void insert_and_shift(int index, double value, int** array_ptr, int length){
	int* array = *array_ptr;
	int holder;
	for(int i = index; i < length; i++){
		holder = array[i];
		array[i] = value;
		value = holder;
	}
}



// need code that binary searches and figures out where to insert
// need to account for the possibility of the difference being less
// than 0.001
int binary_search(int* ids, int id, double* values, double value, int min_index, int max_index){
	if (max_index < min_index){
		return min_index;
	} else {
		int mid_index = mid_point(min_index , max_index);
		double of_interest = values[ids[mid_index]];
		double diff = abs(of_interest-value);
		int same = FALSE;
		if (diff < 0.001){
			same = TRUE;
		}
		if ((of_interest > value && !same) || (same && id > ids[mid_index])){
			return binary_search(ids, id, values, value, min_index, mid_index-1);
		} else {
			return binary_search(ids, id, values, value, mid_index+1, max_index);
		}
	}
}

int mid_point(int min_index, int max_index){
	return min_index+(max_index-min_index)/2;
}
	
double best_topic_value(int* children, int num_children, double x, double y, double** valuesT_ptr, struct Topic** topics_ptr){
	double* valuesT = *valuesT_ptr;
	struct Topic* topics = *topics_ptr;
	double best = sqrt(2)*1000000.0 + 1;
	int index;
	double comparison;
	for (int i = 0; i < num_children; i++){
		index = children[i];
		comparison = valuesT[index];
		if (comparison == -1){
			comparison = sqrt(pow(x-topics[index].x, 2)+pow(y-topics[index].y, 2)); 
			valuesT[index] = comparison;
		}
		if (comparison < best){
			best = comparison;
		}
	}
	return best;
}
