#include<stdio.h>
#include<math.h>
#include <stdarg.h>

int check(int n, int com[][20], int c, int m)
{
    int i;
    for(i=1; i<=m; i++)
        if(com[c][i]==n)
            return 0;
    return 1;
}


int com[20][20];
int count=0;
void Comp(int arr[], int data[], int start, int end, int index, int r);

void C(int n, int r)
{
    int i, data[20], arr[20];
    for(i=1; i<=n; i++)
        arr[i]=i;
    Comp(arr, data, 1, n, 1, r);
}

void Comp(int arr[], int data[], int start, int end, int index, int r)
{
    int j, i;
    if (index > r)
    {
        count++;
        for (j=1; j<=r; j++)
	    {
	        com[count][j]=data[j];
	    }
        return;
    }
    for (i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        Comp(arr, data, i+1, end, index+1, r);
    }
}


void GaussSei(float a[][20], int n, float er)
{
    int i, j, itr, k;
    float xo[20], x[20];
    for(i=1; i<=n; i++)
    {
	    x[i]=0;
	    xo[i]=0;
    }
    itr=0;
    flag:
    itr++;
    for(i=1; i<=n; i++)
    {
        x[i]=a[i][n+1];
        for(j=1; j<=n; j++)
	    if(j!=i)
	    {
	        x[i]=x[i]-a[i][j]*x[j];
	    }
        x[i]=x[i]/a[i][i];
    }
    for( k=1; k<=n; k++)
    {
        if(fabs((x[k]-xo[k])/x[k])>er)
	    {
  	        for(i=1; i<=n; i++)
	        {
	            xo[i]=x[i];
	        }
	        goto flag;
        }


    }
    for(i=1; i<=n; i++)
    {
        printf("  x[%d] = %.2f\t", i, x[i]);
    }
    printf("\n");
}

int main()
{
    int m, n, i, j, l, g, h;
    float a[20][20], er, b[20][20];
    printf("enter the no. of equations:\n");
    scanf("%d", &m);
    printf("enter the no. of unknowns: \n");
    scanf("%d", &n);
    printf("enter the stopping criteria:\n");
    scanf("%f", &er);


    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n+1; j++)
        {
	        if(i>m)
                a[i][j]=0;
	        else
	        {
                if(j==n+1)
                    printf("enter b[%d] ", i);
                else
	                printf("enter a[%d][%d] ", i, j);
	            scanf("%f", &a[i][j]);
	        }
        }
    }
    C(n, m);
    printf("no. of Basic solutions = %d\n", count);
    for(l=1; l<=count; l++)
    {
        printf("\nSolution %d: ", l);
        for(i =1; i<=n; i++)
	    {
	        h=1;
	        for(j=1; j<=n+1; j++)
	        {
	            if(check(j,com, l, n-m))
		        {
		            b[i][h++]=a[i][j];
		        }
	        }
	    }
        GaussSei(b, m, er);
    }
    printf("\n");
    return 0;
}
