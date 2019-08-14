8
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







