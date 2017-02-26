#include<stdio.h>
#define size 50
int check(int n, int com[][size], int c, int m)
{
int i;
for(i=1; i<=m; i++)
if(com[c][i]==n)
return 0;
return 1;
}
int com[size][size];
int ctr=0;
void comb(int a[], int temp[], int s, int e,
int index, int r);
void combination(int n, int r)
{
int i, temp[size], a[size];
for(i=1; i<=n; i++)
a[i]=i;
comb(a, temp, 1, n, 1, r);
}void comb(int a[], int temp[], int s, int e, int index, int r)
{
int j, i;
if (index > r)
{
ctr++;
for (j=1; j<=r; j++)
com[ctr][j]=temp[j];
return;
}
for (i=s; i<=e && e-i+1 >= r-index; i++)
{
temp[index] = a[i];
comb(a, temp, i+1, e, index+1, r);
}
}
void GS(float a[][size], int n, int m, int l, float y[][size])
{
int i, j, k;
static int ctr=1;
float c, x[size]={0}, sum;
for(i=1; i<n; i++)
{for(j=i+1; j<=n; j++)
{
c=(a[i][i]!=0)?a[j][i]/a[i][i]:0;
for(k=1; k<=n+1; k++)
{
a[j][k]-=(a[i][k]*c);
}
}
}
x[n]=a[n][n+1]/a[n][n];
for(i=n-1; i>=1; i--)
{
sum=0;
for(j=n; j>=i+1; j--)
{
sum+=a[i][j]*x[j];
}
x[i]=(a[i][n+1]-sum)/a[i][i];
}
y[ctr][m+1]=y[ctr][m+2]=1;
for(i=1; i<=n; i++)
{
y[ctr][i]=x[i];
if(x[i]<0)
y[ctr][m+1]=y[ctr][m+2]=0;
else if(x[i]==0)y[ctr][m+2]=0;
}
ctr++;
}
void main()
{
int m, n, i, j, l, h, c[size][size];
float a[size][size], er, b[size][size], y[size][size];
printf("\nenter the number of variables : ");
scanf("%d", &n);
printf("\nenter the number of equations : ");
scanf("%d", &m);
for(i=1; i<=n; i++)
{
for(j=1; j<=n+1; j++)
{
if(i>m)
a[i][j]=0;
else
{
printf("a[%d][%d] = ", i, j);
scanf("%f", &a[i][j]);
}
}printf("\n");
}
combination(n, n-m);
for(i=1; i<=ctr; i++)
{
h=1;
for(j=1; j<=n; j++)
if(check(j,com,i,n-m))
c[i][h++]=j;
}
printf("\nTotal number of Basic solutions = %d\n", ctr);
for(l=1; l<=ctr; l++)
{
for(i =1; i<=n; i++)
{
h=1;
for(j=1; j<=n+1; j++)
if(check(j,com, l, n-m))
b[i][h++]=a[i][j];
}
GS(b, m, n, l, y); }
repeat:
printf("\n'1' Non degenerate Sol\n'2' Degenerate Sol\n'3' Feasible Sol\n'4' Basic
Solutions");printf("\n'5' Stop ");
scanf("%d", &i);
switch(i)
{
case 4:
printf("\nBasic solutions :\n");
for(j=1; j<=ctr; j++)
{
for(h=1; h<=m; h++)
printf("x[%d] = %f ", c[j][h], y[j][h]);
printf("\n");
}
break;
case 3:
printf("\nFeasible solutions :\n");
for(j=1; j<=ctr; j++)
{
if(y[j][n+1]==1)
{
for(h=1; h<=m; h++)
printf("x[%d] = %f ", c[j][h], y[j][h]);
printf("\n");
} }
break;
case 2:
printf("\nDegenerate solutions :\n");for(j=1; j<=ctr; j++)
{
if(y[j][n+2]==0&&y[j][n+1]==1)
{
for(h=1; h<=m; h++)
printf("x[%d] = %f ", c[j][h], y[j][h]);
printf("\n");
} }
break;
case 1:
printf("\nNon Degenerate solutions :\n");
for(j=1; j<=ctr; j++)
{
if(y[j][n+2]==1)
{
for(h=1; h<=m; h++)
printf("x[%d] = %f ", c[j][h], y[j][h]);
printf("\n");
}}
break;
default: printf("\nExiting\n");
return;
}
goto repeat;
}