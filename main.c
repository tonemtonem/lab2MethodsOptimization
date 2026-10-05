#include <stdio.h>
#include "AdditionalMethods.h"
#include "SimplexTypes.h"
#include "SimplexSolver.h"
#include "SimplexTable.h"

static void PrintErrors(const SolveStatus status) {
    switch (status) {
        case SOLVE_NO_MEMORY:
            fprintf(stderr, "не удалось выделить память");
        case SOLVE_UNBOUNDED:
            fprintf(stderr, "целевая функция не ограничена\n");
        case SOLVE_INFEASIBLE:
            fprintf(stderr, "система ограничений не совместима\n");
        case SOLVE_ITERATION_LIMIT:
            fprintf(stderr, "Лимит итерааций\n");
        case SOLVE_OK: break;
    }
}
int main(void) {
    SimplexData data;
    double StartMatrix[3][3] = {
        {1, 1, 1},
        {1, 1, 0},
        {0, 0.5, 2}
    };
    double FuncArr[4] = {0,1,3,8};
    double ValueArr[3] = {7,2,4};
    const bool isMax = true;
    const int countOfVar = sizeof(StartMatrix[0])/sizeof(StartMatrix[0][0]);
    const int countOfRestr = sizeof(StartMatrix) / sizeof(StartMatrix[0]);
    MakeNewData(&data, countOfVar, countOfRestr, isMax);
    for (int i=0; i< countOfRestr;i++) {
        for (int j =0; j< countOfVar; j++) {
            data.stMatrix[i][j] = StartMatrix[i][j];
        }
    }
    for (int i = 0; i<countOfRestr;i++) {
        data.valArr[i] = ValueArr[i];
    }
    for (int i = 0; i<countOfVar + 1;i++) {
        data.funArr[i] = FuncArr[i];
    }
    SimplexTable* table = CreateTable(countOfRestr, countOfVar);
    FillSimplexTable(table ,&data);
    PrintSimplexTable(table);
    const SolveStatus status = RunSimplex(table,PrintSimplexTable);
    if (status == SOLVE_OK) PrintSolution(table, &data);
    else PrintErrors(status);
    DeleteSimplexData(&data);
    DeleteSimplexTable(table);
    return 0;
}