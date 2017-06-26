#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#define NUM_OF_THREADS 18   /* Total number of threads used */
#define LENGTH 16   /* 16 rows, 16 columns, 16 grids */
#define ONE_FOURTH_LENGTH 4 /* Dimension of small grid */
#define FALSE 0
#define TRUE 1


static int *puz[LENGTH];    /* Data Structure to contain the Puzzle Board */
static int duplicate = FALSE;   /* duplicate entry in the puzzle, it set to true */
static int outOfRange = FALSE;  /* if entry is out of range, it set to true */
pthread_mutex_t lock;   /* Mutex lock to manipulate global variables */

/* Function used to test on each Thread to validate 16 rows,16 columns & 16 4x4 grids */
void *validator_threads(void *param);

/* read the input puzzle from file and store */
void read_puzzle_file(const char *inputfile);


int main(int argc, const char *argv[])
{
    pthread_t workers[NUM_OF_THREADS];  /* Array of 48 threads */
    int threads[NUM_OF_THREADS];
    int i,j;    /* Integer used for iterating over threads */
    
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    
    /* There has to be 2 arguments, executable file and txt file name */
    if (argc < 2)
    {
        printf("An input file must be provided.\n\nSyntax:   sudokuXX <FILE>\n");
        return 1;
    }
    
    /* Allocate memory for the columns in each row */
    for (i = 0; i < LENGTH; i++)
        puz[i] = (int *)malloc(sizeof(int) * LENGTH);
    
    
    read_puzzle_file(argv[1]);  /* read in the file and store the input */
    
    /* initialize mutex variable */
    pthread_mutex_init(&lock, NULL);
    
    /* Creating NUM_OF_THREADS Threads */
    for (i = 0; i < NUM_OF_THREADS ; i++)
    {
        threads[i]=i;
        pthread_create(&workers[i], NULL, validator_threads, (void *)&threads[i]);
    }
    
    /* Join each thread using pthread_join */
    for (i = 0; i < NUM_OF_THREADS; i++)
        pthread_join(workers[i], NULL);
    
    /* parent thread validates the result from 48 child threads and gives the result */
    printf("***************************************************************\n");
    if (duplicate == TRUE || outOfRange == TRUE)
    {
        printf("\t\tHEXADOKU SOLUTION IS INVALID !!\n");
    }
    else
    {
        printf("\t\tHEXADOKU SOLUTION IS VALID !!\n");
    }
    printf("***************************************************************\n");
    
    /* destroy mutex variable */
    pthread_mutex_destroy(&lock);
    
    /* Free memory for the columns in each row */
    for (i = 0; i < LENGTH; i++)
        free(puz[i]);
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("%G \n",cpu_time_used);

    return 0;
}

/* Scans each item in a Designated area. Expects a void pointer with the row,
  column or segment to test. Sets the pthread_value pointer to be 0 (FALSE)
  if no duplicates are found.  Otherwise, it sets it to 1 (TRUE). */
void *validator_threads(void *param)
{
    int id;
    id = *((int *)param);
    int i, j, k, val1, val2, row, col, grid;
    
    /* First 16 threads validates the correctness of 16 rows of sudoku puzzle */
    if (id == 0)
    {
        for (row = 0; row < LENGTH; row++)
        {
            for (i = 0; i < LENGTH; i++)
            {
                val1 = puz[row][i];
                
                /* if are any invalid and outof range entries in the row*/
                if(val1<0 || val1>15)
                {
                    printf("Invalid Entry in row %d & column %d : %d\n", row,i,val1);
                    pthread_mutex_lock(&lock);
                    outOfRange = TRUE;
                    pthread_mutex_unlock(&lock);
                    
                }
                
                for (j = 0; j < LENGTH; j++)
                {
                    val2 = puz[row][j];
                    
                    /* if duplicate entry in row, set duplicate to TRUE */
                    if (val1 == val2 && !(i == j))
                    {
                        //printf("Row: %d Invalid!!\n", row);
                        fflush(stdout);
                        pthread_mutex_lock(&lock);
                        duplicate = TRUE;
                        pthread_mutex_unlock(&lock);
                        break;
                    }
                }
            }
        }
    }
    /* Next 16 threads validates the correctness of 16 columns of sudoku puzzle */
    else if (id == 1)
    {
        for (col = 0; col < LENGTH; col++)
        {
            for (i = 0; i < LENGTH; i++)
            {
                val1 = puz[i][col];
                for (j = 0; j < LENGTH; j++)
                {
                    val2 = puz[j][col];
                    
                    /* if duplicate entry in column, set duplicate to TRUE */
                    if (val1 == val2 && !(i == j))
                    {
                        //printf("Column: %d Invalid!!\n", col);
                        fflush(stdout);
                        pthread_mutex_lock(&lock);
                        duplicate = TRUE;
                        pthread_mutex_unlock(&lock);
                        break;
                    }
                }
            }
        }
    }
    /* Last 16 threads validates the correctness of 16 sungrids of sudoku puzzle */
    else if(id > 1 && id < LENGTH)
    {
        grid = id;
        
        for (k = 0; k < ONE_FOURTH_LENGTH; k++)
        {
            for (i = 0; i < ONE_FOURTH_LENGTH; i++)
            {
                val1 = puz[grid][i];
                for (j = 0; j < ONE_FOURTH_LENGTH; j++)
                {
                    val2 = puz[grid][j];
                    
                    /* if duplicate entry in subgrid, set duplicate to TRUE */
                    if (val1 == val2 && !(i == j))
                    {
                        //printf("4x4 Subgrid Invalid !!\n");
                        fflush(stdout);
                        pthread_mutex_lock(&lock);
                        duplicate = TRUE;
                        pthread_mutex_unlock(&lock);
                        break;
                        
                    }
                    
                }
                
                for (i = 0; i < ONE_FOURTH_LENGTH; i++)
                {
                    val1 = puz[i][grid];
                    for (j = 0; j < ONE_FOURTH_LENGTH; j++)
                    {
                        val2 = puz[j][grid];
                        
                        /* if duplicate entry in subgrid, set duplicate to TRUE */
                        if (val1 == val2 && !(i == j))
                        {
                            //printf("4x4 Subgrid Invalid !!");
                            fflush(stdout);
                            pthread_mutex_lock(&lock);
                            duplicate = TRUE;
                            pthread_mutex_unlock(&lock);
                            break;
                        }
                    }
                }
            }
        }
    }
    
    pthread_exit(FALSE);
}

void read_puzzle_file(const char *inputfile)
{
    int i;
    FILE *f;    /* pointer to the input file */
    
    if ((f = fopen(inputfile, "r")))     /* Try to open the file to read */
    {
        
        for (i = 0; i < LENGTH; i++)    /* read 16 lines of input */
        {
            /* Parse normal sudoku layout */
            int *ptr = puz[i];
            fscanf(f, "%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x", ptr, ptr+1, ptr+2, ptr+3, ptr+4, ptr+5, ptr+6, ptr+7, ptr+8, ptr+9, ptr+10, ptr+11, ptr+12, ptr+13, ptr+14, ptr+15);
        }
        
        fclose(f);  /* Close the file */
    }
    else
    {
        /* otherwise, print an error message */
        printf("No such file name !! please enter the valid file name/path !!\n");
    }
}

