#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,m,i,j,tempindex,tempindex1,hh=7,cc;
	double temp,temp1,pivot,res;

    printf("Enter the no of variables.\n");
    scanf("%d",&n);
    double c[n+1];
    printf("enter the coefficients of for c1x1+c2x2+....cnxn.\n");

    for(i=1;i<=n;i++)scanf("%lf",&c[i]);
    for(i=1;i<=n;i++)printf("%lf ",c[i]);


    printf("\nEnter the no. of equations.\n");
    scanf("%d",&m);

    double a[m+1][n+m+1],A[m+1][n+m+1]; double b[m+1],B[m+1];
    double cb[m+1];double cj[n+m+1];
    double del[n+m+1]; double ratio[m+1];

    for(i=1;i<=m;i++){printf("Enter co eff of eq=%d eq.\n",i);
    for(j=1;j<=n+m;j++){scanf("%lf",&a[i][j]);}}

    printf("Enter all the b[i]\n");

    for(i=1;i<=m;i++){scanf("%lf",&b[i]);a[i][0]=b[i];}

   for(i=1;i<=m;i++)cb[i]=0;

     for(i=1;i<=n;i++)cj[i]=c[i];
      for(;i<=m+n;i++)cj[i]=0;
  /////////
 while(hh--){
        cc=0;
       for(i=1;i<=m+n;i++){temp=0;
        for(j=1;j<=m;j++){
            temp+=cb[j]*a[j][i];
        }
        del[i]=temp-cj[i];
if(del[i]>=0)cc++;
     }
if(cc==m+n) break;
       temp=del[1];tempindex=1;
      for(i=2;i<=m+n;i++)if(temp>del[i]){temp=del[i]; tempindex=i;}

      for(j=1;j<=m;j++){ ratio[j]=a[j][0]/a[j][tempindex];}

for(j=1;j<=m;j++)if(ratio[j]>0)break;

temp1=ratio[j];tempindex1=j;
for(j=1;j<=m;j++){
if(ratio[j]>0&&ratio[j]<temp1){temp1=ratio[j];tempindex1=j;}
}
pivot=a[tempindex1][tempindex];
//printf(" %lf %d",pivot,tempindex1);
//tempindex1=
 for(i=1;i<=m+n;i++){
        for(j=1;j<=m;j++){
if(j!=tempindex1)
A[j][i]=a[j][i]-(a[tempindex1][i]*a[j][tempindex])/pivot;
else A[j][i]=a[j][i]/pivot;

}}
for(i=1;i<=m;i++){

        if(i==tempindex1)
    B[i]=b[i]/pivot;
else B[i]=b[i]-(b[tempindex1]*a[i][tempindex])/pivot;

}
cb[tempindex1]=cj[tempindex];

for(i=1;i<=m;i++){
        for(j=1;j<=m+n;j++){
//printf("%lf ",A[i][j]);
a[i][j]=A[i][j];
}printf("\n");
}
res=0;
for(i=1;i<=m;i++){//printf("%lf ",cb[i]);
        b[i]=B[i];res+=cb[i]*b[i];}

 }
 /*  */
   printf("Hello world! %lf \n",res);
    return 0;
}
