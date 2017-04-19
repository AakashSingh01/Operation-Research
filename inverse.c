#include <stdio.h>
   

int main(){
int i,k;
double B[3][3],BB[3][3],deter;

B[1][1]=4;B[1][2]=3;
B[2][2]=2;B[2][1]=3;

deter=B[1][1]*B[2][2]-B[1][2]*B[2][1];
BB[1][1]=B[2][2]/deter;
BB[1][2]=-B[1][2]/deter;
BB[2][1]=-B[2][1]/deter;
BB[2][2]=B[1][1]/deter;

for(i=1;i<=2;i++){for(k=1;k<=2;k++)printf("%lf ",BB[i][k]);printf("\n");}  

    }
