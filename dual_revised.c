#include <stdio.h>
#include <stdbool.h>
#include <math.h>
int c[100][100],table_no=0;
bool unbound=false,optimal=false,infeasibile=false,infinite=false;
float a[100][100][100];
void print1(int m,int n,int index){
	int i,j;
	if(index!=0)printf("Tableau %d\n\n",(index+1));
	else printf("The Initial Tableu\n\n");
	for(i=0;i<=m;i++){
		for(j=0;j<=n;j++){
			printf("%f\t",a[index][i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void print2(int m,int n,int index){
	int i,j;
	printf("The basic variables are:\n");
	for(i=0;i<m;i++){
		printf("x[%d] = %f\t",(c[index][n+i]+1),a[index][i][n]);
		if(c[index][n+i]>=n)printf("Slack\t");
		printf("\n");
	}
	printf("\nThe non-basic variables are:\n");
	for(i=0;i<n;i++){
		printf("x[%d] = %f\t",(c[index][i]+1),0.0);
		if(c[index][i]>=n)printf("Slack\t");
		printf("\n");
	}
}
int mostNeg(int m,int n){
	float neg=0;
	int i,k=-1;
	for(i=0;i<m;i++){
		if(a[table_no][i][n]>=0) continue;
		else{
			if(a[table_no][i][n]<neg){
				neg=a[table_no][i][n];
				k=i;
			}
		}
	}
	if(k==-1){optimal=true;}
	return k;
}
int pivot(int m,int n,int *y){
	int i,j,r,p=-1;
	r=mostNeg(m,n);
	(*y)=r;
	float min=90000.0,k;
	if(r==-1) return -1;

	for(i=0;i<n;i++){
		if(a[table_no][r][i]!=0){
			k=fabs(a[table_no][m][i]/a[table_no][r][i]);
			if(min>k){
				min=k;
				p=i;
			}
		}
	}
	if(p==-1) unbound=true;
	return p;
}
void simplex(int m,int n){
	int i,j,k,r,index;
	r=pivot(m,n,&k);
	if(unbound || infeasibile || optimal){
		if(!optimal)table_no--;
		return;
	}
	for(i=0;i<n+m;i++){
		c[table_no+1][i]=c[table_no][i];
	}
	for(i=0;i<=m;i++){
		for(j=0;j<=n;j++){
			if(i!=k && j!=r){
				a[table_no+1][i][j]=((a[table_no][k][r]*a[table_no][i][j])-(a[table_no][i][r]*a[table_no][k][j]))/a[table_no][k][r];
			}
		}
	}
	for(i=0;i<=m;i++){
		if(i!=k)a[table_no+1][i][r]=a[table_no][i][r]/(0-a[table_no][k][r]);
	}
	for(j=0;j<=n;j++){
		if(j!=r)a[table_no+1][k][j]=a[table_no][k][j]/a[table_no][k][r];
	}
	a[table_no+1][k][r]=1/a[table_no][k][r];
	table_no++;
	index=c[table_no][r];
	c[table_no][r]=c[table_no][n+k];
	c[table_no][n+k]=index;
	simplex(m,n);
}
void dual(int m,int n,int cg[100]){
	int i,j,k=0,l;
	while(1){
		if(k==m) break;
		for(i=0;i<=n;i++){
			if(cg[k]==0)continue;
			else if(cg[k]==1)a[table_no][k][i]=(-1)*a[table_no][k][i];
			else if(cg[k]==2){
				for(j=n;j>k;j++){
					a[table_no][j+1][i]=a[table_no][j][i];
				}
				a[table_no][k+1][i]=(-1)*a[table_no][k][i];
				if(i==n){
					k++;
					m++;
				}
			}
		}
		k++;
	}
	for(i=0;i<n+m;i++){
		c[table_no][i]=i;
	}
	simplex(m,n);
}
void revised(){
	printf("put the code here:");
}
int main(){
	char ch[10];
	int m,n,k=0,i,j,ans,choice,decide=0,ith;
	printf("Enter the number of variables:\n");
	scanf("%d",&n);
	printf("Enter the number of inequation:\n");
	scanf("%d",&m);
	int cg[m];
	while(1){
		if(k==m) break;
		printf("enter coefficients, inequality and bi. %d:\n" , k + 1);
		for(i=0;i<n;i++)scanf("%f",&a[table_no][k][i]);
		scanf("%s",ch);
		scanf("%f",&a[table_no][k][n]);
		for(i=0;i<=n;i++){
			if(ch[0]=='<')cg[k]=0;
			else if(ch[0]=='>'){
				cg[k]=1;
				decide=1;
			}
			else if(ch[0]=='='){
				cg[k]=2;
				decide=1;
			}
		}
		k++;
	}
	printf("Enter 0 for maxi-equation and enter 1 for mini-equation:");
	scanf("%d",&ans);
	printf("Enter coefficients and constant term of the objective function:\n");
	for(j=0;j<=n;j++){
		scanf("%f", &a[table_no][m][j]);
		if(ans){
			if(j==n)a[table_no][m][j]=(-1)*a[table_no][m][j];
		}
		else {
			if(j!=n)a[table_no][m][j]=(-1)*a[table_no][m][j];
		}
	}
	if(decide==1)dual(m,n,cg);
	else revised();
	printf("The total iteration no. is:%d\n",table_no);
	do{
		printf("\nEnter 1:To display the initial tableau.\nEnter 2:To display the list of basic and non basic variables of ith iteration.\n");
		printf("Enter 3:To display the tableau at ith iteration.\nEnter 4:To display the optimal solution if exists.\nEnter 0: To exit\n");
		printf("Give your choice:\n");
		scanf("%d",&choice);
		if(choice==1){
			print1(m,n,0);
		}
		if(choice==2){
			printf("Give the i:\n");
			scanf("%d",&ith);
			print2(m,n,ith);
		}
		if(choice==3){
			printf("Give the i:\n");
			scanf("%d",&ith);
			print1(m,n,ith);
		}
		if(choice==4){
			if(optimal){
				if(ans)printf("The optimal solution is z = %f",(0-a[table_no][m][n]));
				else printf("The optimal solution is z = %f",a[table_no][m][n]);
			}
			else{
				if(unbound)printf("The linear programming problem is unbounded.");
				else if(infeasibile)printf("The problem is infeasibile.");
			}
		}
	}while(choice!=0);

}
