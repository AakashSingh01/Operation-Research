#include<stdio.h>
#include<math.h>
#define size 20
// Aakash Singh
// 14MA20003
int main()
{
	int i,j,n,key;
	float sum = 0;
	float a[size][size],b[size], x[size],xo[size],er ;

	printf("enter the size of the matrix:\n");
	scanf("%d", &n);
	printf("enter the stopping criteria:\n");
	scanf("%f", &er);

	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			printf("a[%d][%d] = ", i, j);
			scanf("%f", &a[i][j]);
		}
	}
	for(i=1;i<=n;i++)
	{
		printf("b[%d] = ", i);
		scanf("%f", &b[i]);

	}

	for(i=1;i<=n;i++)xo[i]=0;

	redo:
	key = 0;
	for(i=1;i<=n;i++)
	{
		sum = b[i];
		for(j=1;j<=n;j++)
		{
			if(j!=i)
			{
				sum =  sum - a[i][j]*xo[j];
			}
		}
		x[i] = sum/a[i][i];
		if(fabs((x[i]-xo[i])/x[i])>er)
		{
			key = 1;
		}
		xo[i]=x[i];

	}
	if(key == 1)
		goto redo;

	else
		for(i=1;i<=n;i++)
			printf("x[%d] = %f\n", i, x[i]);
	return 0;
}
