#include "stdio.h"

struct Point {
	float X;
	float Y;
	int T;
};

struct Line {
	float A;
	float B;
	float D;
	int R;
};

struct Line S[100][100];

void printline(int i, int j)
{
	if (S[i][j].A == 0) {
		if (S[i][j].B == 0) printf("%f=0\n", S[i][j].D);
		else if (S[i][j].D > 0) printf("%f*y+%f=0\n", S[i][j].B, S[i][j].D);
		else printf("%f*y%f=0\n", S[i][j].B, S[i][j].D);
	}
	else {
		printf("%f*x", S[i][j].A);
		if (S[i][j].B > 0) printf("+%f*y", S[i][j].B);
		else if (S[i][j].B < 0) printf("%f*y", S[i][j].B);
		if (S[i][j].D > 0) printf("+%f", S[i][j].D);
		else if (S[i][j].D < 0) printf("%f", S[i][j].D);
		printf("=0\n");
	}
}

void main()
{
	struct Point C[100];
	int i, j, k, n, max, p, q;
	printf("Enter the number of points: ");
	scanf_s("%i", &n);
	printf("\n");
	for (i = 0; i < n; i++) {
		printf("Enter coordinates of points: ");
		scanf_s("%f%f", &C[i].X, &C[i].Y);
		C[i].T = 0;
	}
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			S[i][j].R = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) if (i != j) {
			S[i][j].A = C[j].Y - C[i].Y;
			S[i][j].B = C[i].X - C[j].X;
			S[i][j].D = C[i].X*C[i].Y - C[i].X*C[j].Y + C[j].X*C[i].Y - C[i].X*C[i].Y;
			for (k = 0; k < n; k++) if (S[i][j].A*C[k].X + S[i][j].B*C[k].Y + S[i][j].D == 0) S[i][j].R++;
		}	
	do {
		max = 0;
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if ((S[i][j].R > max) && (C[i].T == 0) && (C[j].T == 0)) {
					max = S[i][j].R;
					p = i;
					q = j;
				}
		if (max > 2) {
			printline(p, q);
			C[p].T = 1;
			C[q].T = 1;
			for (i = 0; i < n; i++)
				if (C[i].T == 0) {
					if (S[p][q].A*C[i].X + S[p][q].B*C[i].Y + S[p][q].D == 0) {
						C[i].T = 1;
						for (j = 0; j < n; j++) if (i != j)
							for (k = 0; k < n; k++)
								if ((C[j].T == 0) && (C[k].T == 0) && (i != k) && (j != k))
									if (S[i][j].A*C[k].X + S[i][j].B*C[k].Y + S[i][j].D == 0) S[j][k].R--;
					}
					else for (j = 0; j < n; j++) if (C[j].T == 0)
						if ((S[i][j].A*C[p].X + S[i][j].B*C[p].Y + S[i][j].D == 0) || (S[i][j].A*C[q].X + S[i][j].B*C[q].Y + S[i][j].D == 0)) S[i][j].R--;
				}
		}
	}
	while (max > 2);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			if ((C[i].T == 0) && (C[j].T == 0) && (i != j)) {
				printline(i, j);
				C[i].T = 1;
				C[j].T = 1;
			}
		if (C[i].T == 0) {
			if (i != 0) {
				printline(i, 0);
				C[i].T = 1;
			}
			else {
				printline(i, 1);
				C[i].T = 1;
			}
		}
	}
}