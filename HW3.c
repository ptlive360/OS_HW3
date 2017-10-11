#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

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
    //leep(1);
    printf("Printing GeeksQuiz from Thread \n");
    return (void *)true;
}

void *Check_column(struct params *passed_in)
{
	int a;
	a = passed_in->row;
	printf("----%d---- \n", a);
    //leep(1);
    printf("Printing GeeksQuiz from Thread \n");
    return (void *)true;
}

  
int main()
{
	//int passed_in = 1;
	struct params currParams;
	void* row_correct;
	void* column_correct;

	currParams.row = 500;
	currParams.column = 1;

    pthread_t check_row_thread;
    pthread_t check_column_thread;

    printf("Before Thread\n");
    pthread_create(&check_row_thread, NULL, Check_row, &currParams);
    pthread_create(&check_column_thread, NULL, Check_column, &currParams);

    pthread_join(check_row_thread, &row_correct);
    pthread_join(check_column_thread, &column_correct);

    printf("Told Ya! %d\n", (bool)row_correct);
    printf("After Thread\n");
    exit(0);
}
