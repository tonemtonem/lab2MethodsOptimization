#include "AdditionalMethods.h"
#include "SimplexTypes.h"
#include "numericUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include<math.h>

void PrintCanonical(const SimplexData* data) {
    if (data == NULL) return;
    for (int i=0; i< data->countOfRestr; i++) {
        for (int j =0; j< data->countOfVar; j++) {
            if (!IsZero(data->stMatrix[i][j]))
                printf("%+g*x%d ", data->stMatrix[i][j], j + 1);
        }
        printf("+ x%d = %g\n", data->countOfVar + i + 1, data->valArr[i]);
    }
    printf("x1..x%d >= 0\n\n", data->countOfVar + data->countOfRestr);
}
void PrintSolution(const SimplexTable* table, const SimplexData* data) {
    if (table == NULL || data == NULL) return;
    const int numVars = (table->rows - 1) + (table->cols - 1);
    double* xValues = calloc(numVars, sizeof(double));
    for (int i =0; i< table->rows - 1; i++) {
        if (table->basisVar[i] < table->cols - 1) xValues[i] = table->cells[i][0];
    }
    for (int k = 0; k < table-> cols - 1; k++) {
        printf("x%d = %lf\n", k + 1, xValues[k]);
    }
    const double F = table->cells[table->rows - 1][0];
    const double answer = data -> isMax ? -F : F;
    printf("Answer = %lf\n", answer);
    //проверка
    double check = data->funArr[0];
    for (int j = 0; j < data->countOfVar; j++) {
        check += data->funArr[j + 1] * xValues[j];
    }
    printf("Проверка: F(x) = %lf, ", check);
    printf("%s\n", fabs(check - answer) <=DBL_EPSILON? "совпадает с Answer" : "НЕ совпадает с Answer");
    free(xValues);
}
void PrintSimplexTable(const SimplexTable* table) {
    if (table ==  NULL) return;
    printf("%8s %10s", "", "s_i0");
    for (int j = 1; j < table -> cols; j++) {
        char name[16];
        snprintf(name, sizeof(name), "x%d", table->columnVar[j - 1] + 1);
        printf(" %10s", name);
    }
    printf("\n");
    for (int i = 0; i < table->rows - 1; i++) {
        char name[16];
        snprintf(name, sizeof(name), "x%d", table->basisVar[i] + 1);
        printf("%8s", name);
        for (int j = 0; j < table->cols; j++) {
            printf(" %10.4f", table->cells[i][j]);
        }
        printf("\n");
    }
    printf("%8s", "F");
    for (int j = 0; j < table->cols; j++) {
        printf(" %10.4f", table->cells[table->rows - 1][j]);
    }
    printf("\n========================================================================================\n");
    printf("\n\n");
}
