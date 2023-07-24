#include <stdio.h>

#define MAX_POINTS 100

int dominates(float a[], float b[], int n) {
  int i, count = 0;
  for (i = 0; i < n; i++) {
    if (a[i] >= b[i]) {
      count++;
    }
  }
  return (count == n && a != b);
}

int main() {
  float points[MAX_POINTS][2];
  int num_points = 0;
  int i, j;
  int pareto_ranks[MAX_POINTS] = {0};

  // Read in the points from file
  FILE *fp = fopen("bikes.csv", "r");
  if (fp == NULL) {
    printf("Failed to open file\n");
    return 1;
  }
  char buffer[80];
  while (fgets(buffer, 80, fp) != NULL) {
    sscanf(buffer, "%f*%f", &points[num_points][0], &points[num_points][1]);
    num_points++;
  }
  fclose(fp);

  // Compute the Pareto ranks
  for (i = 0; i < num_points; i++) {
    int num_dominated = 0;
    for (j = 0; j < num_points; j++) {
      if (i != j && dominates(points[j], points[i], 2)) {
        num_dominated++;
      }
    }
    pareto_ranks[i] = num_dominated + 1;
  }

  // Print the Pareto front and ranks
  printf("Pareto front and ranks:\n");
  for (i = 0; i < num_points; i++) {
    if (pareto_ranks[i] == 1) {
      printf("(%g, %g) - Rank: %d (Pareto front)\n", points[i][0], points[i][1], pareto_ranks[i]);
    } else {
      printf("(%g, %g) - Rank: %d\n", points[i][0], points[i][1], pareto_ranks[i]);
    }
  }

  return 0;
}
