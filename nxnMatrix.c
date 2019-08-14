#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


//global variables
int sizeOfInput;


//creates a blank 0 matrix of dimensions size by size
int** matrixMaker(int size){
	int **matrixArray;
	matrixArray = malloc(size * sizeof (int*));
	for (int k = 0; k < size; k++) {
    	*(matrixArray+k) = malloc(size * sizeof (int));
    	for (int i = 0; i < size; ++i)
    	{
    		*(matrixArray[k] + i)  = 0;
    	}
	}	

    return matrixArray;
}

//creates the matrix that the user inputs
int** matrixMakerInput(int size, int array[]){
	int **matrixArray;
	int counter=0;
	matrixArray = malloc(size * sizeof (int*));
	for (int k = 0; k < size; k++) {
    	*(matrixArray+k) = malloc(size * sizeof (int));
    	for (int i = 0; i < size; ++i)
    	{
    		*(matrixArray[k] + i)  = array[counter];
    		counter++;
    	}
	}	
    return matrixArray;
}

//prints a given matrix to terminal
void matrixPrinter(int** ptr, int size){

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			printf("%d ", *(ptr[i] + j) );
		}

		printf("\n");
		
	}
}

//produces the minor of an n by n matrix (finds matrix of size (n-1) by (n-1))
int** reduceMatrix(int** originalMatrix, int size, int y, int x){
	int** newMatrix = matrixMaker(size - 1);
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if(i != x || j != y){
				int a = *(originalMatrix[i] + j);
				if(i<x && j<y) {				
					*(newMatrix[i] + j) = a;
				}
				if(i>x && j<y){					
					*(newMatrix[i -1 ] + j) = a;
				} 
				if(i<x && j>y){					
					*(newMatrix[i] + j - 1) = a;
				} 
				if(i>x && j>y){
					*(newMatrix[i-1] + j - 1) = a;

				} 
				
			}
			
		}
	}
	return newMatrix;
}

//finds the cofactor of a minor
int cofactor(int x, int y, int val){ 
	return pow(-1,x+y)*val; 
}

//base case of the recursive algorithm, finds the 2x2 matrix determinant
int det2x2(int** matrix){
	return (((*(matrix[0])) * (*(matrix[1] + 1))) - ((*(matrix[1])) * (*(matrix[0] + 1))));
}

//the main recursive algorithm, if size > 3 finds the determinant of all minors
int determinant(int** matrix, int size){
	int answer = 0;
	if (size == 2) return det2x2(matrix);
	else for (int i = 0; i < size; ++i)
	{
		answer += cofactor(0,i,*(matrix[i]) * determinant(reduceMatrix(matrix,size,0,i),size-1));
	}
	return answer;
}

//handles the input to program, and returns created matrix
int** inputOutput(){
	printf("what is the size of your nxn matrix?");
	scanf("%d",&sizeOfInput);
	int array[sizeOfInput*sizeOfInput];
	for (int i=0; i<sizeOfInput*sizeOfInput; i++) {
    	printf("Enter number %d: ", i+1);
    	scanf("%d", &array[i]);
  	}
  	return matrixMakerInput(sizeOfInput,array);
}

//TESTING


// A replacement for the library assert function.
void assert(int line,bool b) {
	
    if (b == false) {
		printf("The test on line %d fails.\n",line);
    	exit(1);

    }
    
}


// Tests 1 to 2: check equilateral
void testdeterminantvalidity() {
	int array1[9] ={1,2,3,4,5,6,7,8,9};
	int array2[9] ={62,33,45,79,37,54,42,14,34};
	int one =determinant(matrixMakerInput(3,array1),3);
	int two =determinant(matrixMakerInput(3,array2),3);
    assert(__LINE__,one == 0);
    assert(__LINE__,two == -2830);
    
}

void testdeterminant4x4validity() {
	int array1[16] ={4,7,2,9,8,2,6,3,9,4,1,8,4,6,8,3};
	int array2[16] ={1,3,4,2,5,4,7,8,2,5,33,7,9,4,2,5};
	int one =determinant(matrixMakerInput(4,array1),4);
	int two =determinant(matrixMakerInput(4,array2),4);
    assert(__LINE__,one == -562);
    assert(__LINE__,two == 2301);
}

void testdeterminant10x10validity() {
	int array1[100] = {2,5,3,7,8,35,5,4,7,3,46,7,5,4,3,6,5,4,3,7,8,9,2,4,0,4,2,5,7,8,3,5,7,5,3,6,8,9,3,4,6,8,5,3,5,6,7,4,2,5,6,9,0,4,3,6,7,8,4,3,6,8,9,5,3,5,7,8,9,5,4,3,6,8,9,5,4,3,5,7,8,9,2,3,4,5,1,2,4,5,8,7,5,4,3,6,5,3,9,4}; 
	
	int one =determinant(matrixMakerInput(10,array1),10);
	
    assert(__LINE__,one == 482268600);
   
}

void test2x2determinantvalidity() {
	int array1[9] ={1,2,3,4};
	int array2[9] ={3,7,2,1};
    assert(__LINE__,det2x2(matrixMakerInput(2,array1)) == -2);
    assert(__LINE__,det2x2(matrixMakerInput(2,array2)) == -11);
}

void cofactorvalidity() {
    assert(__LINE__,cofactor(1,1,5) == 5);
    assert(__LINE__,cofactor(2,1,54) == -54);
}

// Run tests on the triangle function.
void test() {
    test2x2determinantvalidity();
    cofactorvalidity();
    testdeterminantvalidity();
    testdeterminant4x4validity();
    testdeterminant10x10validity();
    printf("All tests passed\n");
}

//MAIN

int main(int n, char *args[n]){

	setbuf(stdout, NULL);
    if (n == 2) {
        test();
    }
    else{

    	int** ptr = inputOutput();

		printf("this is your matrix\n");

		matrixPrinter(ptr,sizeOfInput);

		printf("the determinant of this is: %d\n", determinant(ptr,sizeOfInput));
    }

	
}






