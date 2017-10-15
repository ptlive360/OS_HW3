#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

//char inputFileName[] = "Sudoku.txt";
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

int main(int argc, char* argv[])
{
	//for loop counter
	int i = 0;
	int j = 0;
 
	//**** Generic Filo IO ******
	FILE *filePtr;
	filePtr = (fopen(argv[1], "r"));
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
    int curr_read;
    curr_read = 1;

    //****** Read File into the Matrix and Format Check *******
    while((input_digit = fgetc(filePtr)) != EOF){
    	if(curr_read > 90)
    		break;

    	if(curr_read%10 == 0 && input_digit != '\n')
    	{
			printf("Incorrect Format\n");
			printf("here1");
			exit(1);
    	}

    	if(curr_read%10 != 0 && (input_digit-'0' <= 0 || input_digit - '0' > 9))
    	{
			printf("Incorrect Format\n");
			printf("here2");
			exit(1);
		}	
    	if(input_digit != '\n')
        {
        	inputMatrix[i][j] = input_digit;
        	if(j+1>=9)
        		i++;
        	j = (j+1)%9;
        }
        curr_read++;
    }
 

	struct params square_1_coord;	
	struct params square_2_coord;
	struct params square_3_coord;
	struct params square_4_coord;
	struct params square_5_coord;
	struct params square_6_coord;
	struct params square_7_coord;
	struct params square_8_coord;
	struct params square_9_coord;

	

	void* row_correct;
	void* column_correct;

	void* square_1_correct;	
	void* square_2_correct;
	void* square_3_correct;
	void* square_4_correct;
	void* square_5_correct;
	void* square_6_correct;
	void* square_7_correct;
	void* square_8_correct;
	void* square_9_correct;

	
	square_1_coord.row = 0;
	square_1_coord.column = 0;
	
	square_2_coord.row = 0;
	square_2_coord.column = 3;
	
	square_3_coord.row = 0;
	square_3_coord.column = 6;


	square_4_coord.row = 3;
	square_4_coord.column = 0;
	
	square_5_coord.row = 3;
	square_5_coord.column = 3;

	square_6_coord.row = 3;
	square_6_coord.column = 6;


	square_7_coord.row = 6;
	square_7_coord.column = 0;

	square_8_coord.row = 6;
	square_8_coord.column = 3;

	square_9_coord.row = 6;
	square_9_coord.column = 6;

	
    pthread_t check_row_thread;
    pthread_t check_column_thread;
    pthread_t check_square_thread_1;
    pthread_t check_square_thread_2;
    pthread_t check_square_thread_3;
    pthread_t check_square_thread_4;
    pthread_t check_square_thread_5;
    pthread_t check_square_thread_6;
    pthread_t check_square_thread_7;
    pthread_t check_square_thread_8;
    pthread_t check_square_thread_9;
    
    printf("Before Thread\n");
    pthread_create(&check_row_thread, NULL, Check_row, &square_1_coord);
    pthread_create(&check_column_thread, NULL, Check_column, &square_1_coord);
    pthread_create(&check_square_thread_1, NULL, Check_square, &square_1_coord);
    pthread_create(&check_square_thread_2, NULL, Check_square, &square_2_coord);
    pthread_create(&check_square_thread_3, NULL, Check_square, &square_3_coord);
    pthread_create(&check_square_thread_4, NULL, Check_square, &square_4_coord);
    pthread_create(&check_square_thread_5, NULL, Check_square, &square_5_coord);
    pthread_create(&check_square_thread_6, NULL, Check_square, &square_6_coord);
    pthread_create(&check_square_thread_7, NULL, Check_square, &square_7_coord);
    pthread_create(&check_square_thread_8, NULL, Check_square, &square_8_coord);
    pthread_create(&check_square_thread_9, NULL, Check_square, &square_9_coord);


    pthread_join(check_row_thread, &row_correct);
    pthread_join(check_column_thread, &column_correct);
    pthread_join(check_square_thread_1, &square_1_correct);
    pthread_join(check_square_thread_2, &square_2_correct);
    pthread_join(check_square_thread_3, &square_3_correct);
    pthread_join(check_square_thread_4, &square_4_correct);
    pthread_join(check_square_thread_5, &square_5_correct);
    pthread_join(check_square_thread_6, &square_6_correct);
    pthread_join(check_square_thread_7, &square_7_correct);
    pthread_join(check_square_thread_8, &square_8_correct);
    pthread_join(check_square_thread_9, &square_9_correct);

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
    
    if((bool)square_2_correct == true)
    	printf("Square_2 check passed!\n");
    else
    	printf("Square_2 check failed!\n");
    
    if((bool)square_3_correct == true)
    	printf("Square_3 check passed!\n");
    else
    	printf("Square_3 check failed!\n");

    if((bool)square_4_correct == true)
    	printf("Square_4 check passed!\n");
    else
    	printf("Square_4 check failed!\n");
    
    if((bool)square_5_correct == true)
    	printf("Square_5 check passed!\n");
    else
    	printf("Square_5 check failed!\n");

    if((bool)square_6_correct == true)
    	printf("Square_6 check passed!\n");
    else
    	printf("Square_6 check failed!\n");

    if((bool)square_7_correct == true)
    	printf("Square_7 check passed!\n");
    else
    	printf("Square_7 check failed!\n");


    if((bool)square_8_correct == true)
    	printf("Square_8 check passed!\n");
    else
    	printf("Square_8 check failed!\n");

    if((bool)square_9_correct == true)
    	printf("Square_9 check passed!\n");
    else
    	printf("Square_9 check failed!\n");

	
    printf("After Thread\n");


    fclose(filePtr);
    exit(0);
}
