#ifndef LABMETHODSOPTIMISATION2_SIMPLEXTYPES_H
#define LABMETHODSOPTIMISATION2_SIMPLEXTYPES_H

#include<stdbool.h>
#include<stdlib.h>
typedef struct {
    double** stMatrix; // матрица коэффициентов
    double* valArr; // правые ограничения b_i CountOfRest элементов
    double* funArr; // целевая функция [0] - свободный член, остальные элменты - коэффициенты
    int countOfVar; // число исходных переменных
    int countOfRestr; // число фиктивных переменных
    bool isMax; // целевая функция стремится к максимуму или минимуму True-максимизировать, False-минимизировать
} SimplexData;
typedef struct {
    double** cells; // значения таблицы, rows x columns
    int rows; // число ограничений + 1 (последняя строка - целевая функция)
    int cols; // число переменных + 1 (нулевой столбец - свободные члены)
    int* basisVar; // basisVariables[i] - номер переменной (с нуля) в строке i
    int* columnVar; // columnVariables[j - 1] - номер переменной (с нуля) в столбце j
}SimplexTable;
typedef enum {
    SOLVE_OK,               // оптимальное решение найдено
    SOLVE_INFEASIBLE,       // система ограничений несовместна
    SOLVE_UNBOUNDED,        // целевая функция не ограничена
    SOLVE_ITERATION_LIMIT,  // превышен лимит итераций
    SOLVE_NO_MEMORY         // не удалось выделить память
} SolveStatus;
inline void MakeNewData(SimplexData* data, int countOfVar, int countOfRestr, bool isMax ) {
    if (data == NULL || countOfRestr <= 0 || countOfVar <= 0) return;
    data->stMatrix = NULL;
    data->valArr = NULL;
    data->funArr = NULL;
    data->countOfVar = countOfVar;
    data->countOfRestr = countOfRestr;
    data->isMax = isMax;
    data->stMatrix = calloc(countOfRestr, sizeof(double* ));
    data->valArr = calloc(countOfRestr, sizeof(double));
    data->funArr = calloc(countOfVar + 1, sizeof(double));
    for (int i=0; i< countOfRestr;i++) {
        data->stMatrix[i] = calloc(countOfVar, sizeof(double));
    }
}
inline void DeleteSimplexData(SimplexData* data) {
    if (data == NULL) return;
    for (int i =0; i< data->countOfRestr; i++) {
        free(data->stMatrix[i]);
    }
    free(data->stMatrix);
    free(data->funArr);
    free(data->valArr);
    data->stMatrix = NULL;
    data->valArr = NULL;
    data->funArr = NULL;
    data->countOfVar = 0;
    data->countOfRestr = 0;
}
inline void MakeDVdata(SimplexData* data) {
    SimplexData newData;
    MakeNewData(&newData, data->countOfVar, data->countOfRestr, data->isMax);

}
#endif //LABMETHODSOPTIMISATION2_SIMPLEXTYPES_H
