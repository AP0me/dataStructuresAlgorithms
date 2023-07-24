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
  int i, j, k;
  int is_dominated;

  // Read in the points from file
  FILE *fp = fopen("bikes.csv", "r");
  if (fp == NULL) {
    printf("Failed to open file\n");
    return 1;
  }
  char buffer[80];
  while (fgets(buffer, 80, fp) != NULL) {
    int price;
    float weight;
    sscanf(buffer, "%d*%f", &price, &weight);
    points[num_points][0] = price;
    points[num_points][1] = weight;
    num_points++;
  }
  fclose(fp);

  // Compute the Pareto front
  int pareto_front[MAX_POINTS] = {0};
  for (i = 0; i < num_points; i++) {
    is_dominated = 0;
    for (j = 0; j < num_points; j++) {
      if (i != j && dominates(points[j], points[i], 2)) {
        is_dominated = 1;
        break;
      }
    }
    if (!is_dominated) {
      pareto_front[i] = 1;
    }
  }

  // Print the Pareto front
  printf("Pareto front:\n");
  for (i = 0; i < num_points; i++) {
    if (pareto_front[i]) {
      printf("(%f, ", points[i][0]);
      printf("%f)\n", points[i][1]);
    }
  }

  return 0;
}
