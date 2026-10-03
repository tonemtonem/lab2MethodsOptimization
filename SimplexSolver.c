#include "SimplexSolver.h"
#include "numericUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
CheckStatus CheckMatrix(const SimplexTable* table,  int* falseRow,  int* falseCol) {
    if (table == NULL ) return CHECK_INFIASIBLE;
    *falseRow = -1;
    *falseCol = -1;
    for (int i = 0; i < table->rows - 1 ; i++) {
        if (IsNegative(table->cells[i][0])) {
            *falseRow = i;
            for (int j = 1; j < table->cols; j++) {
                if (table -> cells[i][j] < 0) {
                    *falseCol = j;
                    break;
                }
            }
            break;
        }
    }
    if (*falseRow == -1)return CHECK_OK;
    if (*falseCol == -1) return CHECK_INFIASIBLE;
    double minRatio = INFINITY;
    for (int i =0; i < table->rows - 1; i++) {
        const double a = table-> cells[i][*falseCol];
        if (IsZero(a)) continue;
        const double ratio = table->cells[i][0] / a;
        if (IsPositive(ratio) && ratio < minRatio) {
            minRatio = ratio;
            *falseRow = i;
        }
    }
    return CHECK_STEP;
}
void FindAllowingRowCol(const SimplexTable* table, int* allowingRow, int* allowingCol) {
    if (table == NULL) return;
    *allowingRow = -1;
    *allowingRow = -1;
    for (int i =1; i< table-> cols; i++) {
        if (IsPositive(table->cells[table->rows - 1][i])) {
            *allowingCol = i;
            break;
        }
    }
    if (*allowingCol == -1) return;
    double minRatio = INFINITY;
    for (int i =0; i < table->rows - 1; i++) {
        const double a = table->cells[i][*allowingCol];
        if (IsPositive(a)) {
            const double ratio = table->cells[i][0] / a;
            if (ratio < minRatio) {
                minRatio = ratio;
                *allowingRow = i;
            }
        }
    }
}