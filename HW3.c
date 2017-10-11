#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

char inputFileName[] = "Sudoku.txt";
char inputMatrix[9][9];

struct params
{
	int row;
	int column;
};

void *Check_row(struct params *passed_in)
{
	/*
	int a;
	a = passed_in->row;
	printf("----%d---- \n", a);

    printf("Printing GeeksQuiz from Thread \n");
    */
	int i;
	int j;
	int k;

	bool check[9];

	for(i = 0;i<=8;i++)
		check[i] = false;

	for(i = 0;i<=8;i++)
	{
		for(j = 0;j<=8; j++)
			for(k = 1;k<=9;++k)
				if(inputMatrix[i][j] == k+'0') // +'0' is to convert int to char
					check[k-1] = true;

		for(k = 0;k<=8;++k)
			if(check[k] != true)
				return (void *)false;

		for(k = 0;k<=8;k++)
			check[k] = false;
	}

    return (void *)true;
}

void *Check_column(struct params *passed_in)
{
	/*
	int a;
	a = passed_in->row;
	printf("----%d---- \n", a);

    printf("Printing GeeksQuiz from Thread \n");
    */
	int i;
	int j;
	int k;

	bool check[9];

	for(i = 0;i<=8;i++)
		check[i] = false;

	for(i = 0;i<=8;i++)
	{
		for(j = 0;j<=8; j++)
			for(k = 1;k<=9;++k)
				if(inputMatrix[j][i] == k+'0') // +'0' is to convert int to char
					check[k-1] = true;

		for(k = 0;k<=8;++k)
			if(check[k] != true)
				return (void *)false;

		for(k = 0;k<=8;k++)
			check[k] = false;
	}

    return (void *)true;
}

void *Check_square(struct params *passed_in)
{
	/*
	int a;
	a = passed_in->row;
	printf("----%d---- \n", a);

    printf("Printing GeeksQuiz from Thread \n");
    */
	int i;
	int j;
	int k;

	bool check[9];

	for(i = 0;i<=8;i++)
		check[i] = false;

	for(i = 0;i<=2;i++)
		for(j = 0;j<=2; j++)
			for(k = 1;k<=9;++k)
				if(inputMatrix[i+passed_in->row][j+passed_in->column] == k+'0') // +'0' is to convert int to char
					check[k-1] = true;

	for(k = 0;k<=8;++k)
		if(check[k] != true)
			return (void *)false;

    return (void *)true;
}

int main()
{
	//for loop counter
	int i = 0;
	int j = 0;
 
	//**** Generic Filo IO ******
	FILE *filePtr;
	filePtr = (fopen(inputFileName, "r"));
	if(filePtr == NULL)
    {
       printf("Fail to read the file\n");
       exit(1);
    }
    else
    {
    	printf("Successfully read the file\n");
    }

    //****** Read the file into inpuMatrix *******
    char input_digit;
    while((input_digit = fgetc(filePtr))!=EOF){
    	if(input_digit != '\n')
        {
        	inputMatrix[i][j] = input_digit;
        	if(j+1>=9)
        		i++;
        	j = (j+1)%9;
        }
    }
 
	struct params currParams;
	void* row_correct;
	void* column_correct;
	void* square_1_correct;

	currParams.row = 0;
	currParams.column = 0;

    pthread_t check_row_thread;
    pthread_t check_column_thread;
    pthread_t check_square_thread_1;

    printf("Before Thread\n");
    pthread_create(&check_row_thread, NULL, Check_row, &currParams);
    pthread_create(&check_column_thread, NULL, Check_column, &currParams);
    pthread_create(&check_square_thread_1, NULL, Check_square, &currParams);


    pthread_join(check_row_thread, &row_correct);
    pthread_join(check_column_thread, &column_correct);
    pthread_join(check_square_thread_1, &square_1_correct);

    if((bool)row_correct == true)
    	printf("Row check passed!\n");
    else
    	printf("Row check failed!\n");

    if((bool)column_correct == true)
    	printf("Column check passed!\n");
    else
    	printf("Column check failed!\n");

    if((bool)square_1_correct == true)
    	printf("Square_1 check passed!\n");
    else
    	printf("Square_1 check failed!\n");

    printf("After Thread\n");


    fclose(filePtr);
    exit(0);
}
