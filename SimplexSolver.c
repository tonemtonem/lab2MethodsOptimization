#include "SimplexSolver.h"
#include "numericUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "SimplexTable.h"

CheckStatus CheckMatrix(const SimplexTable* table,  int* falseRow,  int* falseCol) {
    if (falseRow == NULL || falseCol == NULL ) return CHECK_INFIASIBLE;
    *falseRow = -1;
    *falseCol = -1;
    if (table == NULL) return CHECK_INFIASIBLE;
    int negativerRow = -1;
    for (int i = 0; i < table->rows - 1 ; i++) {
        if (IsNegative(table->cells[i][0])) {
            *falseRow = i;
            for (int j = 1; j < table->cols; j++) {
                if (IsNegative(table -> cells[i][j])) {
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
    *allowingCol = -1;
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
static SolveStatus RunIterationWIthNegativeElement(SimplexTable* table, StepCallBack callback) {
    int allowingRow, allowingCol;
    if (table == NULL) return SOLVE_INFEASIBLE;
    for (int iteration = 0; iteration < MAX_ITERATION_COUNT; iteration++) {
        const CheckStatus status = CheckMatrix(table, &allowingRow, &allowingCol);
        if (status == CHECK_OK) {
            return SOLVE_OK;
        }
        if (status == CHECK_INFIASIBLE) {
            return SOLVE_INFEASIBLE;
        }
        FillSimplexTableAfterIter(table, allowingRow, allowingCol);
        if (callback != NULL) {
            callback(table);
        }

    }
    return SOLVE_ITERATION_LIMIT;
}
static SolveStatus RunOptimization(SimplexTable* table, StepCallBack callback) {
    if (table == NULL) return SOLVE_INFEASIBLE;
    int allowingRown = -1;
    int allowingCol = -1;
    for (int iteration = 0; iteration<MAX_ITERATION_COUNT; iteration++) {
        FindAllowingRowCol(table, &allowingRown, &allowingCol);
        if (allowingCol == -1 ) return SOLVE_OK;
        if (allowingRown == -1) return SOLVE_UNBOUNDED;
        FillSimplexTableAfterIter(table, allowingRown, allowingCol);
        if (callback != NULL) {
            callback(table);
        }
    }
    return SOLVE_ITERATION_LIMIT;
}
SolveStatus RunSimplex(SimplexTable* table, StepCallBack callback) {
    if (table == NULL) return SOLVE_INFEASIBLE;
    const SolveStatus NegativeElementStatus = RunIterationWIthNegativeElement(table, callback);
    if (NegativeElementStatus != SOLVE_OK) return NegativeElementStatus;
    return RunOptimization(table, callback);
}