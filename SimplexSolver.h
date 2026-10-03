
#ifndef LABMETHODSOPTIMISATION2_SIMPLEXSOLVER_H
#define LABMETHODSOPTIMISATION2_SIMPLEXSOLVER_H
#include "SimplexTypes.h"

typedef enum {
    CHECK_STEP =0,// нужна итерация
    CHECK_OK = 1, //решение допустимо
    CHECK_INFIASIBLE = -1 //система несовместима
} CheckStatus;
CheckStatus CheckMatrix(const SimplexTable* table, int* falseRow, int* falseCol);
void FindAllowingRowCol(const SimplexTable* table, int* allowingRow, int* allowingCol);
#endif //LABMETHODSOPTIMISATION2_SIMPLEXSOLVER_H
