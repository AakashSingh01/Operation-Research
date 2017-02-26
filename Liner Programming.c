#include <stdio.h>
#include <math.h>
double aa,bb,z;
int n;
double x[10][4],sol[3][30];

int check(double a, double b){
    double z,zz;
    int boo=1,i;
    for(i=1;i<=n;i++){
    z=x[i][1]*a+b*x[i][2];

    zz =x[i][3];
    z*=1000;
    zz*=1000;
    int z1=(int)z,zz1=(int)zz;

    if(z1>zz1){boo=0;break;}
    }
    return boo;
}

double solveeq(double a,double b,double c,double p,double q,double r){
    double t,x1,y1;
    t=p/a;
    y1=(c*t-r)/(b*t-q);
    x1=(c-y1*b)/a;

    int boolean=check(x1,y1);

    t=x1*aa+y1*bb;

    if(boolean)
    return t;
    else return -100;
}


int main()

{  int i,j,c=0,e=1;
double tem;
        printf("Enter the coeff of maximizing equation. ax+by \n");
    printf("a=");scanf("%lf",&aa);
    printf("b=");scanf("%lf",&bb);

    printf("Enter the no. of equations.\n");scanf("%d",&n);


    for(i=1;i<=n;i++){
        printf("Enter a,b and c of %d eq.\n",i);
        scanf("%lf",&x[i][1]);
             scanf( "%lf" ,&x[i][2]);
                  scanf(  "%lf",&x[i][3]);

    }
    for(i=1;i<=n;i++){
        for(j=i;j<=n;j++){
                if(i==j){
                  sol[0][c]=    solveeq(x[i][1],x[i][2],x[i][3],0,1,0);
        sol[1][c]=i; sol[2][c]=0;
        if(sol[0][c]!=-100){
        printf("Result %d: %lf\n",e,sol[0][c]);e++;}c++;
        sol[0][c]=    solveeq(x[i][1],x[i][2],x[i][3],1,0,0);
        sol[1][c]=0; sol[2][c]=j;
        if(sol[0][c]!=-100){
        printf("Result %d: %lf\n",e,sol[0][c]);e++;}c++;
                }
                else{

        sol[0][c]=    solveeq(x[i][1],x[i][2],x[i][3],x[j][1],x[j][2],x[j][3]);
        sol[1][c]=i; sol[2][c]=j;
        if(sol[0][c]!=-100){
        printf("Result %d: %lf\n",e,sol[0][c]);e++;}c++;
        }
                    }  }
                    sol[0][++c]=0;

                    printf("Result %d: %lf\n",e,sol[0][c]);
                    tem= sol[0][0];
for(j=1;j<c;j++){
    if(tem<sol[0][j]){tem=sol[0][j];

}


}
   printf("Result Max %lf \n",tem);
    return 0;
}
