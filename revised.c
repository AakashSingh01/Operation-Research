#include <stdio.h>

int main(){

	int n,m,maxeq,i,j,k,l,lvi,evi,loop=4,stop;

    printf("Enter the no. of variable.\n");
    scanf("%d",&n); 

    printf("Enter the no. of equations.\n");
    scanf("%d",&m); 

    printf("\nAnd '0' for min eq or '1' for max eq.\n");
    scanf("%d",&maxeq);
		
	double cj[m+n+1],a[m+1][m+n+1],b[m+1];	
	double P[m+1][n+1+m],B[m+1][m+1],cb[m+1];	
	double PP[m+1][n+1+m],temp,bb[m+1],C[m+n+1];
	double temp1,ratio[m+1], BB[m+1][m+1],deter;
	int nb[n+m+1],swap[m+1];

	printf("Enter the coefficients of for Objective Function.\n");
   	for(i=1;i<=n+m;i++) {if(i<=n){scanf("%lf",&cj[i]); nb[i]=1;}else {cj[i]=0;nb[i]=0;}}  

	for(i=1;i<=m;i++){swap[i]=0;
		    printf("Enter the coeff of %d equations.\n",i);
		for(j=1;j<=n+m;j++){
				if(j<=n)scanf("%lf",&a[i][j]);
				else a[i][j]=0;
			
			 }	a[i][n+i]=1;   }


	printf("Enter the bi one by one.\n");
		for(i=1;i<=m;i++)scanf("%lf",&b[i]);

for(i=1;i<=m;i++){
for(j=1;j<=n+m;j++) 
printf("%.2lf ",a[i][j]);
printf("\n");
}

//for(i=1;i<=m;i++)
//for(j=1;j<=n;j++) P[i][j]=a[i][j];

for(i=1;i<=m;i++)
for(j=n+1;j<=n+m;j++) {B[i][j-n]=a[i][j];BB[i][j-n]=a[i][j];}

for(j=n+1;j<=n+m;j++) cb[j-n]=cj[j];
//B[2][2]=2.0;
/////////////////////
while(loop--){

for(i=1;i<=m+n;i++){
if(nb[i]==1){
for(j=1;j<=m;j++) {
temp=0;
for(k=1;k<=m;k++)temp+=BB[j][k]*a[k][i];
PP[j][i]=temp;
}
}
else for(j=1;j<=m;j++){ PP[j][i]=0;}
}

//for(j=1;j<=m;j++){
//for(i=1;i<=m+n;i++)printf("%lf ",PP[j][i]);printf("\n");}
//for(j=1;j<=m;j++)printf(" cb %lf ",cb[j]);
stop=0;
for(i=1;i<=m+n;i++){
if(nb[i]==1){
temp=0;
for(k=1;k<=m;k++)temp+=cb[k]*PP[k][i];
C[i]=-cj[i]-temp;
if(C[i]<0)stop=-1;
}
//printf("%lf ",C[i]);

}


//printf("\n");
temp=999999;
for(i=1;i<=m+n;i++){
if(nb[i]==1){
if(C[i]<temp){temp=C[i];lvi=i;}
}}

for(k=1;k<=m;k++){
temp=0;
for(j=1;j<=m;j++)temp+=BB[k][j]*b[j];
bb[k]=temp;
}
//for(i=1;i<=m;i++)printf(" bb %lf ",bb[i]);
if(stop==0)break;

for(k=1;k<=m;k++){
ratio[k]=bb[k]/PP[k][lvi];

}

for(k=1;k<=m;k++)if(ratio[k]>0){temp=ratio[k];evi=k;break;}

for(k=1;k<=m;k++)if(ratio[k]>0&&ratio[k]<temp){temp=ratio[k];evi=k;}

for(k=1;k<=m;k++)B[k][evi]=a[k][lvi];


//printf("\n%d %d\n",lvi,evi);
swap[evi]=lvi;
cb[lvi]=-cj[lvi];
nb[lvi]=0;nb[evi+n]=1;

if(m==2){
deter=B[1][1]*B[2][2]-B[1][2]*B[2][1];
BB[1][1]=B[2][2]/deter;
BB[1][2]=-B[1][2]/deter;
BB[2][1]=-B[2][1]/deter;
BB[2][2]=B[1][1]/deter;
}
else if(m==3){
deter=B[1][1]*(B[2][2]*B[3][3]-B[2][3]*B[3][2])
	- B[1][2]*(B[2][1]*B[3][3]-B[3][1]*B[2][3])
	+B[1][3]*(B[2][1]*B[3][2]-B[3][1]*B[2][2]);
BB[1][1]=(B[2][2]*B[3][3]-B[2][3]*B[3][2])/deter;
BB[2][2]=(B[1][1]*B[3][3]-B[1][3]*B[3][1])/deter;
BB[3][3]=(B[1][1]*B[2][2]-B[1][2]*B[2][1])/deter;
BB[1][2]=-(B[1][2]*B[3][3]-B[1][3]*B[3][2])/deter;
BB[2][1]=-(B[2][1]*B[3][3]-B[2][3]*B[3][1])/deter;
BB[3][1]=(B[2][1]*B[3][2]-B[3][1]*B[2][2])/deter;
BB[1][3]=(B[1][2]*B[2][3]-B[1][3]*B[2][2])/deter;
BB[2][3]=-(B[1][1]*B[2][3]-B[1][3]*B[2][1])/deter;
BB[3][2]=-(B[1][1]*B[3][2]-B[1][2]*B[3][1])/deter;
}


}
for(i=1;i<=m;i++){
//if(swap[i]!=0)
printf("X%d= %.2lf\n",swap[i],bb[i]);

}

}

