#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double random_double(double max);
int random_int(int max);

int main(int argc, char** argv){
	int T = 10000;
	int Q = 1000;
	int N = 10000;
	int num_children = 10;

	printf("%d %d %d\n", T, Q, N);
	for (int i = 0; i < T; i++){
		printf("%d %f %f\n", i, random_double(100), random_double(100));
	}
	for (int i = 0; i < Q; i++){
		printf("%d %d ", i, num_children);
		for(int j = 0; j < num_children; j++){
			printf("%d ", random_int(T));
		}
		printf("\n");
	}
	
	for (int i = 0; i < N; i++){
		printf("t 100 %f %f\n", random_double(100), random_double(100));
	}
	
		
	return 0;
}

double random_double(double max){
	return max*(rand()/((double) RAND_MAX));
}

int random_int(int max){
	return rand()%max;
}
