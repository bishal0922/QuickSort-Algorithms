// Bishal Giri

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void ReadFile(int argc, char *argv[], int **ptr, int **n)
{
    FILE *myFile;
    char file_name[100];
    char file_line[10];
    int file_number, total_sum = 0, file_line_tracker = 0;
    char *token;

    if (argc >=2)
    {
        strcpy(file_name, argv[1]);
        myFile = fopen(file_name, "r");
    }
    else
    {
        printf("File must be provided on command line...exiting\n");
        exit(0);
    }

    while (fgets(file_line, sizeof(file_line) - 1, myFile))
    {
        file_line_tracker++; // this will be the number of entries in the file
    }

    **n = file_line_tracker;
    // mallocing an array for the number of lines in the file
    *ptr = malloc(file_line_tracker * sizeof(int));
    fseek(myFile, 0, SEEK_SET);

    // reading through the file again and adding the integers to the dynamic array
    int id=0;
    while (fgets(file_line, sizeof(file_line) - 1, myFile))
    {
        token = strtok(file_line, " ");
        file_number = atoi(file_line);
        (*ptr)[id] = file_number;
        id++;
    }

    fclose(myFile);
}
void Swap(int *A, int *B)
{
    int temp = *A;
    *A = *B;
    *B = temp;
}
int partition(int A[], int low, int high)
{
    int i, j = 0;
    // int pivot = A[high];

    #if QSM
    int middle = (high + low) / 2;
    Swap(&A[middle], &A[high]);
        #elif QSRND
    int random = (rand() % (high - low + 1)) + low;
    Swap(&A[random], &A[high]);
        #endif
    int pivot = A[high];

    i = (low - 1);

    for (j = low; j < high; j++)
    {
        if (A[j] < pivot)
        {
            i++;
            Swap(&A[i], &A[j]);
        }
    }
    Swap(&A[i + 1], &A[high]);

    return (i + 1);
}
void QuickSort(int A[], int low, int high)
{
    if (low < high)
    {
        int ndx = partition(A, low, high);
        QuickSort(A, low, ndx - 1);
        QuickSort(A, ndx + 1, high);
    }
}


void print_array(int list[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        printf("%d\n", list[i]);
    }

}

int main(int argc, char *argv[])
{
    clock_t start, end;
    clock_t mStart, mEnd;

    int counter;
    if (argc < 3)
    {
        printf("Number of runs not specified on command line...defaulting to 10\n");
        counter = 10;
    }
    else
    {
        counter = atoi(argv[2]);
    }
    // pointer for array and its length
    int *list_ptr;
    int n_items = 0;
    int *ptr_to_n_items = &n_items;

    long int total_run_time;
    int i;
    for (i = 0; i < counter; i++)
    {

        ReadFile(argc, argv, &list_ptr, &ptr_to_n_items);
        // printing before quick sort
        #ifdef PRINTARRAY
        printf("\n");
        print_array(list_ptr, n_items);
        #endif

        // starting the clock for quick sort
        mStart = clock();
        QuickSort(list_ptr, 0, n_items - 1);
        mEnd = clock();
        long int clock_timer = mEnd-mStart;
        printf("\nRun %d complete: %ld tics\n",(i+1), clock_timer);
        total_run_time = total_run_time + (clock_timer);

        // printing after quick sort
        #ifdef PRINTARRAY
        printf("\n");
        print_array(list_ptr, n_items);
        #endif

        free(list_ptr);
    }
    printf("\nThe average run time for %d runs is %ld\n", counter, (total_run_time / counter));

    printf("\nProcessed %d records\n", n_items);

    return 0;
}
