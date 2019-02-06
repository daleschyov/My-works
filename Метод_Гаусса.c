#include <stdio.h> 
#include <malloc.h> 
#include <math.h> 
#define N 100 
#define eps 0.00001


void Output_Matrix(int str, int stolbik, float a[][N]);
void Output_SLU(int str, int stolbik, float a[][N]);
int Output_roots(int str, int stolbik, float a[][N]);

int main()
{
	float a[N][N], cmp, tmp;
	int k = 1, k1 = 1, n_str, n_stolbik, i, j, flag = 0, max_elements_string_number;
	printf("Enter the number of strings(equations):");
	scanf("%d", &n_str);
	printf("Enter the number of columns(variables + free terms of the equation):");
	scanf("%d", &n_stolbik);
	printf("Input the numbers:\n");
	for (i = 0; i < n_str; i++)
		for (j = 0; j < n_stolbik; j++)
		{
			if (j != n_stolbik - 1)
				scanf("%f", &a[i][j]);
			else
			{
				printf("b[%d]=", i);
				scanf("%f", &a[i][j]);
			}
		}
	printf("Inputed SLU:\n");
	Output_SLU(n_str, n_stolbik, a);
	printf("Matrix of SLU:\n");
	Output_Matrix(n_str, n_stolbik, a);
	//óäàëåíèå íóëåâîãî ñòîëáöà 
	for (j = 0; j < n_stolbik - 1; j++)
	{
		for (i = 0; i < n_str; i++)
		{
			if (a[i][j] != 0)
			{
				flag = 1;
				break;
			}
			if (flag == 0 && i == n_str - 1)
			{
				for (i = 0; i < n_str; i++)
					for (k = j; k < n_stolbik; k++)
						a[i][k] = a[i][k + 1];
				n_stolbik--;
				j--;
			}
		}
		flag = 0;
	}
	printf("Matrix after deleting zero columns:\n");
	Output_Matrix(n_str, n_stolbik, a);
	for (k = 1; k < n_str; k++)
	{
		//Ñõåìà åäèíñòâåííîãî äåëåíèÿ è óæå ïîèñêà ìàêñèìàëüíîãî ýëåìåíòà 
		max_elements_string_number = k - 1;
		for (i = k - 1; i < n_str - 1; i++)
		{
			if (fabs(a[i + 1][k - 1]) > fabs(a[i][k - 1]))
				max_elements_string_number = i + 1;
		}
		for (j = 0; j < n_stolbik; j++)
		{
			tmp = a[k - 1][j];
			a[k - 1][j] = a[max_elements_string_number][j];
			a[max_elements_string_number][j] = tmp;
		}
		if (a[k - 1][k - 1] != 0)
		{
			for (i = k; i < n_str; i++)
			{
				if (a[i][k - 1] != 0)
				{
					cmp = a[i][k - 1] / a[k - 1][k - 1];
					for (j = k - 1; j < n_stolbik; j++)
						a[i][j] -= a[k - 1][j] * cmp;
					Output_Matrix(n_str, n_stolbik, a);
					i = k1;
					k1++;
				}
			}
		}
		k1 = k;
	}
	//Èçìåíåíèÿ ñ ó÷¸òîì ïîãðåøíîñòè
	for (i = 0; i < n_str; i++)
	{
		for (j = 0; j < n_stolbik; j++)
		{
			if (fabs(a[i][j]) < eps)
				a[i][j] = 0;
		}
	}
	//Óäàëåíèå íóëåâûõ ñòðîê
	k = 0;
	for (i = 0; i < n_str; i++)
	{
		for (j = 0; j < n_stolbik; j++)
		{
			if (a[i][j] != 0)
			{
				flag = 1;
				break;
			}
			if (flag == 0 && j == n_stolbik - 1 && i != n_str - 1)
			{
				for (k = i; k < n_str; k++)
					a[k][j] = a[k + 1][j];
				n_str--;
				i--;
			}
			if (flag == 0 && j == n_stolbik - 1 && i == n_str - 1)
			{
				for (j = 0; j < n_stolbik; j++)
					a[i][j] = a[i - 1][j];
				n_str--;
				i--;
			}
		}
		flag = 0;
	}
	printf("Final matrix:\n\n");
	Output_Matrix(n_str, n_stolbik, a);
	printf("Final SLU:\n\n");
	Output_SLU(n_str, n_stolbik, a);
	printf("\n\n");
	Output_roots(n_str, n_stolbik, a);
	getchar();
	getchar();
	getchar();
	return 0;
}

void Output_Matrix(int str, int stolbik, float a[][N])
{
	int i, j;
	for (i = 0; i < str; i++)
	{
		for (j = 0; j < stolbik; j++)
			printf("%-12.4f", a[i][j]);
		printf("\n");
	}
	printf("_____________________________________________________________________________\n\n\n");
}

void Output_SLU(int str, int stolbik, float a[][N])
{
	int i, j, print = 0;
	for (i = 0; i < str; i++)
	{
		for (j = 0; j < stolbik; j++)
		{
			if (a[i][j] != 0)
			{
				if (j < stolbik - 2)
				{
					printf("%f*x[%d]", a[i][j], j);
					print++;
					if (a[i][j + 1] > 0)
						printf("+");
				}
				if (j == stolbik - 2)
				{
					printf("%f*x[%d]", a[i][j], j);
					print++;
				}
			}
			if (j == stolbik - 1)
			{
				if (print)
					printf("=%f;", a[i][j]);
				else printf("0=%f;", a[i][j]);
			}
			if (a[i][j] == 0 && a[i][j + 1] > 0 && j != stolbik - 1 && j != stolbik - 2 && print != 0)
			{
				printf("+");
				print++;
			}
		}
		printf("\n");
		print = 0;
	}
	printf("\n");
}

int Output_roots(int str, int stolbik, float a[][N])
{
	int i, j, k, n, matrix_rang = 0, expanded_matrix_rang = 0, flag = 0;
	float *x, chislitel = 0,cmp;
	x = (float*)malloc((stolbik - 1) * sizeof(float));
	printf("\n\nMatrix after taking errors into account\n\n ");
	Output_Matrix(str, stolbik, a);
	//Ñ÷èòàåì ðàíã ðàñøèðåííîé ìàòðèöû 
	for (i = 0; i < str; i++)
	{
		for (j = 0; j < stolbik; j++)
			if (fabs(a[i][j]) > eps)
			{
				expanded_matrix_rang++;
				break;
			}
	}
	// Ñ÷èòàåì ðàíã ìàòðèöû 
	for (i = 0; i < str; i++)
	{
		for (j = 0; j < stolbik - 1; j++)
			if (fabs(a[i][j]) > eps)
			{
				matrix_rang++;
				break;
			}
	}
	printf("Expanded matrix rank=%d\nMatrix rank=%d\n", expanded_matrix_rang, matrix_rang);
	if (expanded_matrix_rang > matrix_rang)
	{
		printf("There are no roots\n");
		return 0;
	}
	if (matrix_rang < stolbik - 1)
	{
		printf("\n\nInfinitely many solutions\n\n");
		for (i = str - 1; i >= 0; i--)
		{
			if (a[i][i] != 0)
			{
				cmp = a[i - 1][i] / a[i][i];
				for (k = i - 1; k >= 0; k--)	
					for (n = stolbik-1 ; n >= 0; n--)
						a[k][n] -= cmp*a[k+1][n];
			}
		}
		Output_Matrix(str, stolbik, a);
		for (i = 0; i < str; i++)
		{
			if (a[i][i] != 0)
			{
				cmp = a[i][i];
				for (j = i; j < stolbik; j++)
					a[i][j] /= cmp;
			}
		}
		//printf("Final Matrix for infinitely many solutions\n\n");
		Output_Matrix(str, stolbik, a);
		printf("The roots of equation :\n");
		for (i = 0; i < str; i++)//Íå âñ¸ ãîòîâî òóò åù¸!!! 
		{
			for (j = 0; j < stolbik; j++)
			{
				if (flag == 1 && a[i][j] != 0)
				{
					if (j < stolbik - 1)
					{
						printf("%.4f*x[%d]", -a[i][j], j);
					}
					if (j == stolbik - 1)
					{
						printf("%.4f", a[i][j]);
					}
					if (((a[i][j + 1] < 0) && ((j + 2) < stolbik)) || ((a[i][j + 1] > 0) && (j == stolbik - 2)))
						printf("+");
				}
				if (flag == 1 && a[i][j] == 0 && ((a[i][j + 1] < 0 && j < stolbik - 2) || (a[i][j + 1] > 0 && j == stolbik - 2)))
					printf("+");
				
				if (a[i][j] != 0 && flag == 0)
				{
					flag = 1;
					printf("x[%d]=", j);
				}
			}
			flag = 0;
			printf("\n");
		}
		return 0;
	}
	if (matrix_rang == stolbik - 1)
	{

		for (i = str - 1; i >= 0; i--)
		{
			for (j = 0; j < (str - i); j++)
			{
				if (j == 0)
					chislitel = a[i][stolbik - j - 1];
				if (j != 0)
					chislitel -= a[i][stolbik - j - 1] * x[stolbik - j - 1];
			}
			if(a[i][stolbik-j-1]!=0)
			x[stolbik - j - 1] = chislitel / a[i][stolbik - j - 1];
		}
	}
	printf("The roots of equation :\n");
	for (i = 0; i < (stolbik - 1); i++)
		printf("x[%d]=%.5f\n", i, x[i]);
	free(x);
	return 0;
}
