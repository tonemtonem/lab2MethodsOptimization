#include "SimplexTable.h"
#include "SimplexTypes.h"
#include <stddef.h>
#include <stdlib.h>

static void SwapBasis(SimplexTable* table, const int allowingRow, const int allowingCol ) {
    const int enterVar = table->columnVar[allowingCol - 1];
    const int leavingVar = table->basisVar[allowingRow - 1];
    table->basisVar[allowingRow] = enterVar;
    table->columnVar[allowingCol - 1] = leavingVar;
}

SimplexTable* CreateTable(const int constrCount,const int varCount) {
    if (constrCount <= 0 || varCount <= 0) {
        return NULL;
    }
    SimplexTable* table = calloc(1, sizeof(SimplexTable));
    if (table == NULL) return NULL;
    table->rows = constrCount + 1;
    table->cols = varCount + 1;
    table->cells = calloc(table->rows, sizeof(double*));
    table->basisVar = calloc(constrCount, sizeof(int));
    table->columnVar = calloc(varCount, sizeof(int));
    if ( table->cells == NULL || table->basisVar == NULL || table->columnVar == NULL) {
        DeleteSimplexTable(table);
    }
    for (int i =0; i < table->rows; i++) {
        table -> cells[i] = calloc(table->cols, sizeof(double));
        if (table->cells[i] == NULL) {
            DeleteSimplexTable(table);
        }
    }
    for (int row =0; row < constrCount; row++ ) {
        table->basisVar[row] = constrCount + row;
    }
    for (int col = 0; col < varCount; col++) {
        table->columnVar[col] = col;
    }
    return table;

}
void DeleteTable(SimplexTable* table) {
    for (int i = 0; i < table->rows; i++) {
    free(table->cells[i]);
    }
    free(table->cells);
    free(table->basisVar);
    free(table->columnVar);
    free(table);
}
void FillSimplexTable(SimplexTable* table, const SimplexData* data) {
    if (table == NULL || data == NULL) return;
    const double sign = data->isMax ? 1 : -1;
    for (int i =0; i< data->countOfRestr; i++) {
        table->cells[i][0] = data->valArr[i];
        for (int j=1; j < data->countOfVar + 1; j++) {
            table->cells[i][j] = data->stMatrix[i][j-1];
        }
    }
    for (int j = 1; j< data->countOfVar + 1; j++) {
        table->cells[data->countOfRestr][j] = sign * data->funArr[j];
    }
    table->cells[data->countOfRestr][0] = -sign * data->funArr[0];
}

void FillSimpleTableAfterIter(SimplexTable* table, const int allowingRow, const int allowingCol) {
    if (table == NULL || allowingRow < 0 || allowingCol < 0) return;
    double* oldRow = malloc(table->cols * sizeof(double));
    double* oldCol = malloc(table->rows * sizeof(double));
    if (oldCol == NULL || oldRow == NULL) {
        free(oldRow);
        free(oldCol);
        return;
    }
    for (int j = 0; j< table->cols; j++) {
        oldCol[j] = table->cells[allowingRow][j];
    }
    for (int i = 0; i< table->rows; i++) {
        oldRow[i] = table->cells[i][allowingCol];
    }
    const double pivot = 1 / table->cells[allowingRow][allowingCol];
    const double valueOfAllow = table->cells[allowingRow][allowingCol];
    for (int i = 0; i< table->rows; i++) {
        for (int j = 0; j< table->cols; j++) {
            if (i == allowingRow && j == allowingCol)
                table->cells[i][j] = pivot;
            else if ( i == allowingRow)
                table->cells[i][j] = oldCol[j] * pivot;
        }
    }
    SwapBasis(table, allowingRow, allowingCol);
}
