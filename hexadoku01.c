#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LENGTH 16
#define ONE_FOURTH_LENGTH 4
#define FALSE 0
#define TRUE 1

static int *puz[LENGTH];
static int duplicate = FALSE;
static int outOfRange = FALSE;

/* read the input puzzle from file and store */
void read_puzzle_file(const char *inputfile);

/* function to validate 16 rows,16 columns and 16 4x4 grids */
int validate();

int main(int argc, const char *argv[])
{
    int i;
    
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
    
    
    read_puzzle_file(argv[1]);  /*read the puzzle from input file and store */
    
    validate(); /* function to validate 16 rows,16 columns and 16 4x4 grids */

    
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
    
    /* Free memory for the columns in each row */
    for (i = 0; i < LENGTH; i++)
        free(puz[i]);
 
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("%G \n",cpu_time_used);
    
    return 0;
}


int validate()
{
    int i, j, k , n, val1, val2; /* Integer to iterate through rows and columns */

    
    /* check all 16 rows for duplication and invalid entry */
    for (k = 0; k < LENGTH; k++)
    {
        for (i = 0; i < LENGTH; i++)
        {
            val1 = puz[k][i];
            
            /* if are any invalid and outof range entries */
            if(val1<0 || val1>15)
            {
                printf("Invalid Entry in row %d & column %d : %d\n", k,i,val1);
                outOfRange = TRUE;
                return 0;
            }
            
            for (j = 0; j < LENGTH; j++)
            {
                val2 = puz[k][j];
                
                /* if duplicate entry in row, set duplicate to TRUE and return to calling function */
                if (val1 == val2 && (!(i == j)))
                {
                    printf("Row: %d Invalid!!\n", k);
                    fflush(stdout);
                    duplicate = TRUE;
                    return 0;
                }
            }
        }

    }
    
    /* check all 16 columns for duplication and invalid entry */
    for (k = 0; k < LENGTH; k++)
    {
        
        for (i = 0; i < LENGTH; i++)
        {
            val1 = puz[i][k];
            
            for (j = 0; j < LENGTH; j++)
            {
                val2 = puz[j][k];
                if (val1 == val2)
                {
                    /* if duplicate entry in column, set duplicate to TRUE and return to calling function */
                    if (!(i == j))
                    {
                        printf("Column: %d Invalid!!\n", k);
                        fflush(stdout);
                        duplicate = TRUE;
                        return 0;
                    }
                }
                
            }

        }
    }
    
    
   /* for (n = 0; n < LENGTH; n++)
    {
        for (k = 0; k < ONE_FOURTH_LENGTH; k++)
        {
            for (i = 0; i < ONE_FOURTH_LENGTH; i++)
            {
                val1 = puz[n][i];
                for (j = 0; j < ONE_FOURTH_LENGTH; j++)
                {
                    val2 = puz[n][j];
                    if (val1 == val2)
                    {
                        // if duplicate entry in grid, set duplicate to TRUE and return to calling function
                        if (!(i == j))
                        {
                            printf("4x4 Subgrid Invalid !!\n");
                            fflush(stdout);
                            duplicate = TRUE;
                            return 0;
                        }
                    }
                    
                }
                
                for (i = 0; i < ONE_FOURTH_LENGTH; i++)
                {
                    val1 = puz[i][n];
                    for (j = 0; j < ONE_FOURTH_LENGTH; j++)
                    {
                        val2 = puz[j][n];
                        
                        if (val1 == val2)
                        {
                            // if they do, set duplicate to TRUE and return to calling function 
                            if (!(i == j))
                            {
                                printf("4x4 Subgrid Invalid !!");
                                fflush(stdout);
                                duplicate = TRUE;
                                return 0;
                            }
                        }
                        
                    }
                }
            }

        }
    } */
    
    return 0;

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
