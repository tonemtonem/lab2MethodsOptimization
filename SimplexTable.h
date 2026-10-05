
#ifndef LABMETHODSOPTIMISATION2_SIMPLEXTABLE_H
#define LABMETHODSOPTIMISATION2_SIMPLEXTABLE_H
#include "SimplexTypes.h"

SimplexTable* CreateTable(int constrCount, int varCount);
void FillSimplexTable(SimplexTable* table, const SimplexData* data);
void FillSimplexTableAfterIter(SimplexTable* table, int allowingRow, int allowingCol);
void DeleteSimplexTable(SimplexTable* table);
#endif //LABMETHODSOPTIMISATION2_SIMPLEXTABLE_H
