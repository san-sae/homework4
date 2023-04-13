#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **create_matrix(int row, int col){ // 행렬 생성 함수
    
    int **matrix = (int **)malloc(sizeof(int *) * row); // 행렬의 행에 대한 동적할당
    
    for (int i = 0; i < row; i++){
        matrix[i] = (int *)malloc(sizeof(int) * col); // 행렬의 열에 대한 동적할당
    }
    
    return matrix; // 새롭게 만든 행렬 반환
}

void fill_matrix(int **matrix, int row, int col){ // 행렬 요소 채우기 함수
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            matrix[i][j] = rand() % 10; // 행렬의 요소를 0~9까지 숫자로 구성
        }
    }
}

void print_matrix(int **matrix, int row, int col){
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            printf("%d\t", matrix[i][j]); // 행렬 출력
        }
        printf("\n");
    }
    printf("\n");
}

void addition_matrix(int **matrixA, int **matrixB, int **matrixResult, int row, int col){ // 행렬 A + B 구현 함수
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            matrixResult[i][j] = matrixA[i][j] + matrixB[i][j]; // // 행렬의 합의 결과를 새로운 행렬에 대입
        }
    }
    printf("----------- matrix A + B -----------\n");
    print_matrix(matrixResult, row, col); // 행렬의 합 결과 출력
}

void subtraction_matrix(int **matrixA, int **matrixB, int **matrixResult, int row, int col){ // 행렬 A − B 구현 함수
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            matrixResult[i][j] = matrixA[i][j] - matrixB[i][j]; // // 행렬의 차의 결과를 새로운 행렬에 대입
        }
    }
    printf("----------- matrix A - B -----------\n");
    print_matrix(matrixResult, row, col); // 행렬의 차 결과 출력
}

void transpose_matrix(int **matrixA, int **matrixResult, int row, int col){ // 전치행렬 A 구현 함수
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            matrixResult[j][i] = matrixA[i][j]; // 전치 행렬 결과를 새로운 행렬에 대입
        }
    }
    printf("------ transpose matrix of a ------\n");
    print_matrix(matrixResult, col, row); // 전치 행렬 결과 출력
}

void multiply_matrix(int **matrixA, int **matrixB, int row, int col){
    if (row != col){ // row와 col의 size가 다를 경우
        printf("Error: row and col should be the same for matrix multiplication\n");
        return; // 함수에서 빠져나오기
    }

    // row와 col이 같은 경우 다음과 같은 코드 실행
    // 행렬의 곱의 결과를 담을 새로운 행렬 생성
    int **matrixResult = (int **)malloc(sizeof(int *) * row); // 행렬의 행에 대한 동적 할당

    for (int i = 0; i < row; i++){
        matrixResult[i] = (int *)malloc(sizeof(int) * col); // 행렬의 열에 대한 동적 할당
    }

    for (int i = 0; i < row; i++){ // 행렬의 행에 대한 반복문
        for (int j = 0; j < col; j++){ // 행렬의 열에 대한 반복문
            matrixResult[i][j] = 0;
            for (int k = 0; k < col; k++){
                matrixResult[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    // 행렬 곱 결과 출력
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            printf("%d ", matrixResult[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(int **matrix, int row, int col){ // 할당 메모리 해제 함수
    for (int i = 0; i < row; i++){
        free(matrix[i]); // 행렬의 열에 대한 할당 해제
    }
    free(matrix); // 행렬의 행에 대한 할당 해제
}

int main(){

    printf("[----- [Choi Yoolim] [2020022001] -----]\n");

    int rows = 0;    // 행의 개수
    int columns = 0; // 열의 개수

    do{
        printf("Number of rows in the matrix?");
        scanf("%d", &rows);
        printf("Number of columns in the matrix?");
        scanf("%d", &columns);
    } while (rows == 0 || columns == 0); // 행 또는 열의 개수가 0일때 다시 입력받음

    int i, j;
    int **A, **B;                                 // 행렬 A, B 관련 double pointer
    int **addMat, **subMat, **transMat, **mulMat; // 행렬 연산에 대한 결과값 관련 double pointer
    srand(time(NULL));                            // 무작위 시드값을 위한 함수

    A = create_matrix(rows, columns); // 행렬 A 생성
    B = create_matrix(rows, columns); // 행렬 B 생성
    fill_matrix(A, rows, columns);    // 행렬 A의 요소 채우기
    fill_matrix(B, rows, columns);    // 행렬 B의 요소 채우기

    printf("-------- matrix A --------\n");
    print_matrix(A, rows, columns); // 행렬 A 출력
    printf("-------- matrix B --------\n");
    print_matrix(B, rows, columns); // 행렬 B 출력

    addMat = create_matrix(rows, columns);   // 행렬의 합의 결과를 저장하기 위한 행렬 생성
    subMat = create_matrix(rows, columns);   // 행렬의 차의 결과를 저장하기 위한 행렬 생성
    transMat = create_matrix(columns, rows); // 전치행렬의 결과를 저장하기 위한 행렬 생성

    addition_matrix(A, B, addMat, rows, columns);    // 행렬의 합 실행
    subtraction_matrix(A, B, subMat, rows, columns); // 행렬의 차 실행
    transpose_matrix(A, transMat, rows, columns);    // 전치 행렬 실행
    multiply_matrix(A, B, rows, columns);            // 행렬의 곱 실행

    // 행렬 동적할당 해제
    free_matrix(A, rows, columns);
    free_matrix(B, rows, columns);
    free_matrix(addMat, rows, columns);
    free_matrix(subMat, rows, columns);
    free_matrix(transMat, columns, rows);
    free_matrix(mulMat, rows, columns);

    return 0;
}