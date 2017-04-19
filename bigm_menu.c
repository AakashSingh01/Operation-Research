#include <stdio.h>
#include <stdlib.h>


int main()
{
    int n,m,i,j,ii,maxeq,z=1,iter=0,hi,vi,itable;	
int opti,loop=20;
double cj[20],result[20],total=0;  
   
	double M=999999,temp,pivot,AR[20];////// big m
double del[20]; ;


    printf("Enter the no. of variable in min/max eq.\n");
     scanf("%d",&n); 

	printf("\nAnd '0' for min eq or '1' for max eq.\n");
    scanf("%d",&maxeq);

    printf("enter the coefficients of for c1x1+c2x2+....cnxn.\n");
   	for(i=1;i<=n;i++){ scanf("%lf",&cj[i]); AR[i]=0;result[i]=0; }

 	for(i=n+1;i<20;i++){cj[i]=0;AR[i]=0;result[i]=0;}

   if(maxeq==1)M=-M;

     printf("Enter the no. of equations .\n");
    scanf("%d",&m);

    double a[20][m+1][20], ratio[20][m+1];
	int swap[m+1]; 
	double b[20][m+1],cb[20][m+1],CB[20][m+1],zj[20];

      for(i=1;i<=m;i++)
		{  cb[0][i]=0;CB[0][i]=0;swap[i]=0;
		printf("Enter co eff of eq=%d eq.\n",i);
    for(j=1;j<20;j++){  if(j<=n)scanf("%lf",&a[0][i][j]);else a[0][i][j]=0;}

    printf("\nAnd '0' for < eq , '1' for > eq and '2' for = eq.\n");
     scanf("%lf",&a[0][i][0]);
     if(a[0][i][0]==0)
		{a[0][i][n+z]=1;z++;}
     else if (a[0][i][0]==1)
		{a[0][i][n+z]=-1;z++;
			a[0][i][n+z]=1;cj[n+z]=M;cb[0][i]=M;
					z++;}
     else if (a[0][i][0]==2){a[0][i][n+z]=1;cj[n+z]=M;cb[0][i]=M;z++;}
    }
   if(maxeq==1)M=-M;
printf("\nEnter all the bi one by one.\n");
for(j=1;j<=m;j++)scanf("%lf",&b[0][j]);

/*
for(j=1;j<=m;j++)
	{  for(i=1;i<z+n;i++)
		printf("%.2lf ",a[0][j][i]);
			printf("\n");		}*/  //print func

//---------------------------------------

while(loop--){		
	//for(i=1;i<z+n;i++){if(i<=n)cj[i]=c[i];else cj}
for(i=1;i<z+n;i++){
zj[i]=0;
        for(j=1;j<=m;j++){
zj[i]+=cb[iter][j]*a[iter][j][i];
//printf("-- %.2lf  %.2lf %d %.2lf\n",cb[iter][j],a[iter][j][i],i,zj[i]);
}
zj[i]-=cj[i]; if(maxeq==0)
zj[i]=-zj[i];
}
temp=zj[1];  hi=1;

opti=0;

for(j=1;j<m+z;j++){if(AR[j]==1){//printf(" - "); 
continue;}
//printf("%.2lf ",zj[j]); 
if(zj[j]<temp){temp=zj[j];hi=j;}

if((zj[j]<0))opti=-1;

}
if(opti==0)break;
//printf("\nhi = %d\n",hi);

for(j=1;j<=m;j++)ratio[iter][j]=b[iter][j]/a[iter][j][hi];
temp=M;vi=1;
for(i=1;i<=m;i++)
		{//	printf("%.2lf ",ratio[iter][i]);
//printf("\n%lf %lf %d %d\n",temp,ratio[iter][i],vi,i);
if(ratio[iter][i]>0.00&&temp>ratio[iter][i]){temp=ratio[iter][i];vi=i;
}
}


pivot =a[iter][vi][hi];
swap[vi]=hi;
for(i=1;i<=m;i++)if(i==vi)cb[iter+1][vi]=cj[hi];else cb[iter+1][i]=cb[iter][i];

if(cb[iter][vi]==M){
for(i=n+1;i<n+z;i++)if(cj[i]==M&&a[0][vi][i]==1)AR[i]=1;
}


//printf("\nvi = %d\n",vi);

for(j=1;j<=m;j++)
	{ 
if(j==vi)b[iter+1][j]=b[iter][j]/pivot;
else
b[iter+1][j]=(pivot*b[iter][j]-b[iter][vi]*a[iter][j][hi])/pivot;

 for(i=1;i<z+n;i++)
		{
if(j==vi)a[iter+1][j][i]=a[iter][j][i]/pivot;
else if(i==hi)a[iter+1][j][i]=0;
else a[iter+1][j][i]=(pivot*a[iter][j][i]-a[iter][vi][i]*a[iter][j][hi])/pivot;

//printf("%.2lf ",a[iter+1][j][i]);

}
			//printf("\n");		
}
//printf("bbbb  %.2lf %.2lf\n",b[iter+1][1],b[iter+1][2]);

iter++;

//for(j=1;j<=m;j++)
//	{  for(i=1;i<z+n;i++)
//		printf("%.2lf ",a[iter][j][i]);
//			printf("\n");		}
}

for(j=1;j<=m;j++){//printf(" swap %d = %.2lf\n",swap[j],b[iter][j]); 

result[swap[j]]=b[iter][j]; }

for(j=1;j<=n;j++){

total+=result[j]*cj[j];
}

//printf("\n RESULT :  %.2lf\n",total);







while(1){

printf("\n Enter '1' for list of all bfs.\n");
printf(" Enter '2' no of iterations to solve the problem.\n");
printf(" Enter '3' List of non basic variables along with net values in ith iteration.\n");
printf(" Enter '4' List of Basic variables along with min ratio in ith iteration.\n");
printf(" Enter '5' simplex table for ith iteration.\n");
printf(" Enter '6' for Optimal solution.\n");
printf(" Enter '0' to stop.\n");
scanf("%d",&ii);
if(ii==0)break;
else if(ii== 1){
for(j=1;j<=n;j++){
printf("X%d = %.2lf\n",j,result[j]);total+=result[j]*cj[j];
}

}
else if(ii== 2){printf("\n No. of iteration required : %d \n",iter);}
else if(ii== 3){
for(j=1;j<=n;j++){
printf("X%d = %.2lf\n",j,result[j]);total+=result[j]*cj[j];
}

}
else if(ii== 4){
printf("\n Enter the 'i' for seeing ith iteration ratios. \n");
scanf("%d",&itable);
for(i=1;i<=m;i++)
printf("%.2lf ",ratio[itable][i]);
	      }
else if(ii== 5){

printf("\n Enter the 'i' for seeing ith iteration table. \n");
scanf("%d",&itable);

for(j=1;j<=m;j++)
	{  for(i=1;i<z+n;i++)
		printf("%.2lf ",a[itable][j][i]);
			printf("\n");		}


	     }
else if(ii== 6){


printf("\n RESULT :  %.2lf\n",total);

}

}




    return 0;
}
