#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("para: n-threads i-th_iteration  matrixX.txt\n");
        return 0;
    }

    int thread_num = atoi(argv[1]);
    int iteration_num = atoi(argv[2]);
    char *file_path = argv[3];

    omp_set_num_threads(thread_num);

    double **x;
    int *row_ptr;
    int *col_ind;
    double *datas;

    int row_counter;
    int col_count;
    int non_0_counter;


    FILE *file = fopen(file_path, "r");
    fscanf(file, "%d %d %d\n", &row_counter, &col_count, &non_0_counter);


    double **tempMatrix = (double **) calloc(row_counter, sizeof(double *));

    for (int i = 0; i < row_counter; i++) {
        tempMatrix[i] = (double *) calloc(col_count, sizeof(double));
    }


    while (!feof(file)) {
        int rowIndex;
        int colIndex;
        double value;
        fscanf(file, "%d %d  %lf\n", &rowIndex, &colIndex, &value);
        rowIndex = rowIndex - 1;
        colIndex = colIndex - 1;
        tempMatrix[rowIndex][colIndex] = value;
    }
    fclose(file);

    non_0_counter = 0;

    for (int i = 0; i < row_counter; i++) {
        for (int j = 0; j < col_count; j++) {
            if (tempMatrix[i][j] != 0) {
                non_0_counter++;
            }
        }
    }

    //Initialize vector and CSR
    x = (double **) calloc(iteration_num + 1, sizeof(double *));
    for (int i = 0; i < iteration_num + 1; i++) {
        x[i] = (double *) calloc(non_0_counter, sizeof(double));
    }

    col_ind = (int *) calloc(non_0_counter, sizeof(int));
    datas = (double *) calloc(non_0_counter, sizeof(double));
    row_ptr = (int *) calloc(row_counter + 1, sizeof(int));

    //Initialize X0 (np.ones(row_len))
    for (int i = 0; i < non_0_counter; i++) {
        x[0][i] = 1;
    }

    int cur_i = 0;
    for (int i = 0; i < row_counter; i++) {
        int nonZeroCountCurRow = 0;

        for (int j = 0; j < col_count; j++) {
            if (tempMatrix[i][j] != 0) {
                if (nonZeroCountCurRow == 0) {
                    row_ptr[i] = cur_i;
                }
                col_ind[row_ptr[i] + nonZeroCountCurRow] = j;
                datas[row_ptr[i] + nonZeroCountCurRow] = tempMatrix[i][j];
                cur_i++;
                nonZeroCountCurRow++;
            }
        }
        if (nonZeroCountCurRow == 0) {
            row_ptr[i] = cur_i;
        }
    }
    //Point last row outside
    row_ptr[row_counter] = non_0_counter;

    double start_time, end_time, total_time = 0;

    //Computation
    for (int k = 0; k < iteration_num; k++) {
        start_time = omp_get_wtime();
        //Parallel Section
#pragma omp parallel for schedule(static)
        for (int i = 0; i < row_counter; i++) {
            for (int j = row_ptr[i]; j < row_ptr[i + 1]; j++)
                x[k + 1][i] += datas[j] * x[k][col_ind[j]];
        }

        end_time = omp_get_wtime();
        total_time += end_time - start_time;
    }


    printf("%d -th Vector\n",&iteration_num);
    for (int i = 0; i < row_counter; i++) {
        printf("%d : %.10g\n", i, x[iteration_num][i]);
    }
    printf("total time: %lf seconds.\n", total_time);
}