#include "csapp.h"

#define N 25
#define M 25

#define THREAD          (1 << 4)
#define ROWS_PER_THREAD (N / THREAD)

int M1[N][M];
int M2[N][M];
int MUL[N][M];

void *matrix_multiplication(void *vargp)
{
    int index = *(int *)vargp;
    int start = ROWS_PER_THREAD * index;

    for (int i = start; i < start + ROWS_PER_THREAD; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < M; k++) {
                sum += M1[i][k] * M2[k][j];
            }
            MUL[i][j] = sum;
        }
    }
}

void matrix(void)
{
    pthread_t tid[THREAD];
    int param[THREAD];

    for (int i = 0; i < THREAD; i++) {
        param[i] = i;
        Pthread_create(&tid[i], NULL, matrix_multiplication, &param[i]);
    }

    for (int i = 0; i < THREAD; i++) {
        Pthread_join(tid[i], NULL);
    }
}

int main(void)
{
    matrix();
    return 0;
}
