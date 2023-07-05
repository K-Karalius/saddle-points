// @author Kristupas Karalius
#include <stdio.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

int GetIntegerInput(int minValue, int maxValue);
void ChangeMatrix(int size, int arr[][size]);
void FindBalnoCoord(int size, int arr[][size]);
int FindMinColCoord(int size, int arr[][size], int row);
int FindMaxColCoord(int size, int arr[][size], int row);
int IsMaxInCol(int size, int arr[][size], int colCoord, int rowCoord);
int IsMinInCol(int size, int arr[][size], int colCoord, int rowCoord);
void PrintMatrix(int size, int matrix[][size]);

int main()
{
	printf("The application creates a square matrix based on the user input, then a program searches for the saddle points and prints them out\n");

    int matrixSize;

    int maxMatrixSize = 1000;
    printf("Enter the size of a matrix [1; %d]:\n", maxMatrixSize);
    matrixSize = GetIntegerInput(1, maxMatrixSize);

    int matrix[matrixSize][matrixSize];

    printf("Enter %d matrix elements:\n", INT_MAX);
    ChangeMatrix(matrixSize, matrix);

    printf("Your matrix:\n");
    PrintMatrix(matrixSize, matrix);

    printf("Saddle point coordinates (row; column):\n");
    FindBalnoCoord(matrixSize, matrix);
    
    return 0;
}

void PrintMatrix(int size, int matrix[][size])
{
    for (int i = 0; i <= (size - 1); ++i)
    {
        printf("%c", '{');
        for (int j = 0; j <= (size - 1); ++j)
        {
            if (j != (size - 1))
            {
                printf("%d, ", matrix[i][j]);
            }
            else
            {
                printf("%d", matrix[i][j]);
            }
        }
        printf("%c\n", '}');
    }
}

void FindBalnoCoord(int size, int arr[][size])
{
    int minRowCoord;
    int minColCoord;
    int maxRowCoord;
    int maxColCoord;

    int count = 0;

    if (size != 1)
    {
        for (int i = 0; i <= (size - 1); ++i)
        {
            minRowCoord = i;
            maxRowCoord = i;
            
            minColCoord = FindMinColCoord(size, arr, i);
            maxColCoord = FindMaxColCoord(size, arr, i);

            if (minColCoord != -1)
            {
                if (IsMaxInCol(size, arr, minColCoord, i) != FALSE)
                {
                    printf("(%d; %d)\n", minRowCoord + 1, minColCoord + 1);
                    ++count;
                }
            }

            if (maxColCoord != -1)
            {
                if (IsMinInCol(size, arr, maxColCoord, i) != FALSE)
                {
                    printf("(%d; %d)\n", maxRowCoord + 1, maxColCoord + 1);
                    ++count;
                }
            }
        }
    }

    if (count == 0)
    {
        printf("Saddle points don't exit in the given matrix...\n");
    }
}

int IsMaxInCol(int size, int arr[][size], int colCoord, int rowCoord)
{

    for (int k = 0; k <= (size - 1); ++k)
    {
        if (arr[k][colCoord] >= arr[rowCoord][colCoord] && k != rowCoord)
        {
            return FALSE;
        }
    }

    return TRUE;
}

int IsMinInCol(int size, int arr[][size], int colCoord, int rowCoord)
{

    for (int k = 0; k <= (size - 1); ++k)
    {
        if (arr[k][colCoord] <= arr[rowCoord][colCoord] && k != rowCoord)
        {
            return FALSE;
        }
    }

    return TRUE;
}

int FindMinColCoord(int size, int arr[][size], int row)
{
    int minCoord = 0;

    for (int i = 0; i <= (size - 1); ++i)
    {
        if (arr[row][i] < arr[row][minCoord])
        {
            minCoord = i;
        }
    }

    for (int i = 0; i <= (size - 1); ++i)
    {
        if (arr[row][minCoord] == arr[row][i] && i != minCoord)
        {
            return -1;
        }
    }

    return minCoord;
}

int FindMaxColCoord(int size, int arr[][size], int row)
{
    int maxCoord = 0;

    for (int i = 0; i <= (size - 1); ++i)
    {
        if (arr[row][i] > arr[row][maxCoord])
        {
            maxCoord = i;
        }
    }

    for (int i = 0; i <= (size - 1); ++i)
    {
        if (arr[row][maxCoord] == arr[row][i] && i != maxCoord)
        {
            return -1;
        }
    }

    return maxCoord;
}

void ChangeMatrix(int size, int arr[][size])
{
    for (int i = 0; i <= (size - 1); ++i)
    {
        for (int j = 0; j <= (size - 1); ++j)
        {
            printf("%d row, %d column:\n", (i + 1), (j + 1));
            arr[i][j] = GetIntegerInput(INT_MIN, INT_MAX);
        }
    }
}

int GetIntegerInput(int minValue, int maxValue)
{
    long num;

    while (TRUE)
    {
        if (scanf("%ld", &num) == 1 && getchar() == '\n')
        {
            if (num >= minValue && num <= maxValue)
            {
                return (int)(num);
            }
            printf("The number does not belong to the [%d; %d] interval... Try again\n", minValue, maxValue);
        }
        else
        {
            printf("The submitted number is not an integer... Try again:\n");
            while (getchar() != '\n')
                ;
        }
    }
}