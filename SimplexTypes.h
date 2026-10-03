#ifndef LABMETHODSOPTIMISATION2_SIMPLEXTYPES_H
#define LABMETHODSOPTIMISATION2_SIMPLEXTYPES_H

#include<stdbool.h>
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
#endif //LABMETHODSOPTIMISATION2_SIMPLEXTYPES_H
