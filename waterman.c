#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MAX(int x, int y) {
  if(x>y){ return x; }
  else   { return y; }
}
// function to dynamically allocate a 2D array
int** ppCreateMatrix(int nRows, int nCols) {
  // allocate memory for nRows pointers to int
  int** matrix = (int**) malloc(nRows * sizeof(int*));
  // set all elements of the row to 0
  for (int i = 0; i < nRows; i++) {
    matrix[i] = (int*) malloc(nCols * sizeof(int));
    memset(matrix[i], 0, nCols * sizeof(int));
  }
  return matrix;
}

void FreeMatrix(int** matrix, int nRows) {
  for (int i = 0; i < nRows; i++) { free(matrix[i]); }
  free(matrix);
}

int nMatchScore(char cA, char cB) {
  if (cA == cB) { return  2;}
  else          { return -1;}
}
int nSmithWaterman(char* pSeq1, char* pSeq2, int nGapPenalty, int nMatchScoreValue, int nMismatch) {
  int nLenSeq1 = strlen(pSeq1); int nLenSeq2 = strlen(pSeq2);
  int** pScoreMatrix = ppCreateMatrix(nLenSeq1 + 1, nLenSeq2 + 1);
  int nMaxScore = 0; int nMaxI = 0; int nMaxJ = 0;

  // fill in the score matrix
  for (int i = 1; i < nLenSeq1 + 1; i++) {
    for (int j = 1; j < nLenSeq2 + 1; j++) {
      // calculate scores for each of the three possible cases
      int nMatch =       pScoreMatrix[i-1][j-1] + nMatchScore(pSeq1[i-1], pSeq2[j-1]);
      int nDeleteScore = pScoreMatrix[i-1][j]   + nGapPenalty;
      int nInsertScore = pScoreMatrix[i]  [j-1] + nGapPenalty;

      // choose the highest score and update the score matrix
      if (nMatch > nDeleteScore && nMatch > nInsertScore) {
        pScoreMatrix[i][j] = (nMatch > 0) ? nMatch : 0;
      } else if (nDeleteScore > nInsertScore) {
        pScoreMatrix[i][j] = (nDeleteScore > 0) ? nDeleteScore : 0;
      } else {
        pScoreMatrix[i][j] = (nInsertScore > 0) ? nInsertScore : 0;
      }
      // update the maximum score and its position
      if (pScoreMatrix[i][j] > nMaxScore) {
        nMaxScore = pScoreMatrix[i][j];
        nMaxI = i;
        nMaxJ = j;
      }  
    }
  }

  int i = nMaxI; int j = nMaxJ; int nLen = 0;
  while (i > 0 && j > 0 && pScoreMatrix[i][j] > 0) {
    if      (pScoreMatrix[i][j] == pScoreMatrix[i-1][j] + nGapPenalty) { i--; }
    else if (pScoreMatrix[i][j] == pScoreMatrix[i][j-1] + nGapPenalty) { j--; }
    else { nLen++; i--; j--; }
  }

  FreeMatrix(pScoreMatrix, nLenSeq1 + 1);
  return (nLen * nMatchScoreValue + (nMaxScore - nLen) * nMismatch);
}

int main() {
  char* pSequance1 = "ACGTTAC";
  char* pSequance2 = "AGTTGCA";
  int nGapPenalty = -2; int nMatchScoreValue = 2; int nMismatch = -1;

  int nAlignmentScore = nSmithWaterman(pSequance1, pSequance2, nGapPenalty, nMatchScoreValue, nMismatch);
  printf("Alignment score: %d\n", nAlignmentScore);

  return 0;
}
