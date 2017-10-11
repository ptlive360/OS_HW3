#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct params
{
	int row;
	int column;
};

void *Check_row(struct params *passed_in)
{
	int a;
	a = passed_in->row;
	printf("----%d---- \n", a);
    sleep(1);
    printf("Printing GeeksQuiz from Thread \n");
    return NULL;
}

void *Check_column(void *vargp)
{
    sleep(1);
    printf("Printing GeeksQuiz from Thread \n");
    return NULL;
}

  
int main()
{
	//int passed_in = 1;
	struct params currParams;

	currParams.row = 500;
	currParams.column = 1;

    pthread_t tid;
    printf("Before Thread\n");
    pthread_create(&tid, NULL, Check_row, &currParams);
    pthread_join(tid, NULL);
    printf("After Thread\n");
    exit(0);
}
