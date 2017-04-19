/*
How to compile
--------------

gcc simplex.c -std=c99
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int get_slack(int ies[], int m){
    int slack = 0;
    for(int i=0; i<m; i++){
        if(ies[i] == -1){
            slack++;
        }
    }
    return slack;
}

int get_surplus(int ies[], int m){
    int surplus = 0;
    for(int i=0; i<m; i++){
        if(ies[i] == 1){
            surplus++;
        }
    }
    return surplus;
}

int get_artificial(int ies[], int m){
    int slack = get_slack(ies, m);
    return m - slack;
}

void initialize_table(float table[][100], float a[][100], float b[], float c[], int ies[], int m, int n){
    float cbv[100];
    for(int i=0; i<m; i++){
        if(ies[i] >= 0){
            cbv[i] = -100000;
        } else {
            cbv[i] = 0;
        }
    }
    int surplus = get_surplus(ies, m);
    for(int i=0; i<m; i++){
        int curr_surplus = 0;
        for(int j=0; j<n; j++){
            table[i][j] = a[i][j];
        }
        for(int j=n; j<n+surplus; j++){
            table[i][j] = 0;
        }
        if(ies[i] == 1){
            table[i][n+curr_surplus++] = -1;
        }
        table[i][n+surplus] = b[i];
    }
    for(int i=0; i<=n+surplus; i++){
        float inner_product = 0;
        for(int j=0; j<m; j++){
            inner_product += table[j][i]*cbv[j];
        }
        if(i>=n) table[m][i] = inner_product;
        else table[m][i] = inner_product - c[i];
    }
}

void copy_2d_array(float src[][100], float dest[][100], int m, int n){
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            //printf("i=%d, j=%d\n", i, j);
            dest[i][j] = src[i][j];
        }
    }
}

void print_line(int len){
    for(int i=0; i<len; i++){
        printf("-");
    }
    printf("\n");
}

void print_simplex_table(float arr[][100], int bv[], int nbv[], int m, int n){
    printf("\n");
    printf("         ");
    print_line(10*(n+1)+1);

    printf("         |");
    for(int i=0; i<n; i++){
        printf("    X%d   |", nbv[i]+1);
    }
    printf("    Xb   |\n");

    print_line(10*(n+2));

    for(int i=0; i<=m; i++){
        if(i!=m){
            printf("    X%d   |", bv[i]+1);
        } else {
            printf("         |");
        }
        for(int j=0; j<=n; j++){
            printf(" %+7.2f |", arr[i][j]);
        }
        printf("\n");
        if(i!=m){
            print_line(10*(n+2));
        } else {
            printf("         ");
            print_line(10*(n+1)+1);
        }
    }
    printf("\n");
}

void print_solution(float table[][100], int bv[], int nbv[], int m,
int n, int surplus){
    float sol_array[100];
    printf("\nThe solution is: \n");
    for(int i=0; i<n+surplus; i++){
        if(nbv[i] >= n) continue;
        sol_array[nbv[i]] = 0;
        //printf("x%d = 0 ,", nbv[i]+1);
    }
    for(int i=0; i<m; i++){
        if(bv[i] >= n) continue;
        sol_array[bv[i]] = table[i][n+surplus];
        //printf("x%d = %f ,", bv[i]+1, table[i][n]);
    }
    for(int i=0; i<n; i++){
        printf("X[%d] = %.0f\n", i+1, sol_array[i]);
    }
    printf("\nZ = %.0f\n\n", table[m][n+surplus]);
}

void get_solution(float table[][100], float sol_array[100], int bv[], int nbv[], int m, int n, int surplus){
    for(int i=0; i<n+surplus; i++){
        if(nbv[i] >= n) continue;
        sol_array[nbv[i]] = 0;
    }
    for(int i=0; i<m; i++){
        if(bv[i] >= n) continue;
        sol_array[bv[i]] = table[i][n+surplus];
    }
}

int is_nearly_equal(float a, float b, float abs_err_th){
    int flag = 0;
    float err = fabs(a-b);
    if(err <= abs_err_th){
        flag = 1;
    }
    return flag;
}

int get_pivot_h(float table[][100], int m, int n){
    float min = 0;
    int pivot_h = -1;
    for(int i=0; i<n; i++){
        float value = table[m][i];
        if(value > 0 || is_nearly_equal(value, 0, pow(2, -6))) continue;
        if(value < min || pivot_h == -1){
            pivot_h = i;
            min = table[m][i];
        }
    }
    return pivot_h;
}

int get_pivot_v(float table[][100], int pivot_h, int m, int n){
    float min = 0;
    int pivot_v = -1;
    for(int i=0; i<m; i++){
        float ai = table[i][pivot_h];
        float ratio = table[i][n]/ai;
        if(ai < 0 || is_nearly_equal(ai, 0, pow(2, -6))) continue;
        if(ratio < min || pivot_v == -1){
            pivot_v = i;
            min = ratio;
        }
    }
    return pivot_v;
}

void next_iteration(float table[][100], int bv[], int nbv[], int pivot_h, int pivot_v, int m, int n){
    //this method will only be called if some element is less than 0

    //printf("pivot_h = %d, pivot_v = %d\n", pivot_h, pivot_v);

    float new_table[100][100];
    float pivot = table[pivot_v][pivot_h];
    //printf("pivot = table[%d][%d] = %f\n\n", pivot_v+1, pivot_h+1, pivot);

    int temp = bv[pivot_v];
    bv[pivot_v] = nbv[pivot_h];
    nbv[pivot_h] = temp;

    //printf("pivot = %f\n", pivot);
    //printf("Exchanging X%d with X%d\n", bv[pivot_v]+1, nbv[pivot_h]+1);

    new_table[pivot_v][pivot_h] = 1.0/pivot;

    for(int i=0; i<=n; i++){
        if(i == pivot_h) continue;
        new_table[pivot_v][i] = table[pivot_v][i]/pivot;
    }

    for(int i=0; i<=m; i++){
        if(i == pivot_v) continue;
        new_table[i][pivot_h] = -table[i][pivot_h]/pivot;
    }

    for(int i=0; i<=m; i++){
        for(int j=0; j<=n; j++){
            if(i == pivot_v || j == pivot_h) continue;
            float p = pivot, s = table[i][j];
            float q = table[i][pivot_h], r = table[pivot_v][j];
            new_table[i][j] = (p*s - q*r)/p;
        }
    }

    //print_2d_array(new_table, m+1, n+1);
    copy_2d_array(new_table, table, m+1, n+1);
    //print_simplex_table(table, bv, nbv, m, n);
    //print_solution(table, bv, nbv, m, n);
}

int simplex(float a[][100], float b[], float c[], int ies[], int m, int n, float sol_array[100], float *solution){
    float table[100][100];
    int bv[100], nbv[100];
    int status;

    initialize_table(table, a, b, c, ies, m, n);

    int surplus = get_surplus(ies, m);

    for(int i=0; i<m; i++){
        bv[i] = n+surplus+i;
    }
    for(int i=0; i<n + surplus; i++){
        nbv[i] = i;
    }
    //print_simplex_table(table, bv, nbv, m, n+surplus);
    int flag=1;
    while(flag){
        int pos=0, neg=0, zero=0;
        for(int i=0; i<n+surplus; i++){
            if(is_nearly_equal(table[m][i], 0, pow(2, -6))) zero++;
            else if(table[m][i] < 0) neg++;
            else pos++;
        }
        if(neg == 0){
            for(int j=0; j<m; j++){
                int index = bv[j] - n - surplus;
                if(index >= 0 && ies[index] != -1){
                    //printf("Problem is Infeasible\n");
                    flag = 0;
                    status = 4;
                    break;
                }
            }
            if(flag == 0){
                continue;
            }
            if(zero > 0){
                //print solution here
                //print_solution(table, bv, nbv, m, n, surplus);
                //printf("Alternate solution exists\n");
                status = 2;
                flag = 0;
            }
            else{
                //print solution here
                //print_solution(table, bv, nbv, m, n, surplus);
                //printf("Unique solution\n");
                status = 1;
                flag = 0;
            }
        }else{
            /*printf("proceed to next iteration?\n");
            int temp;
            scanf("%d", &temp);*/
            int pivot_h = get_pivot_h(table, m, n+surplus);
            if(pivot_h < 0){
                printf("Error occurred!\n");
                exit(-1);
            }
            int pos_col=0, neg_col=0, zero_col=0;
            for(int i=0; i<m; i++){
                if(is_nearly_equal(table[i][pivot_h], 0, pow(2, -6))) zero_col++;
                else if(table[i][pivot_h] < 0) neg_col++;
                else pos_col++;
            }
            if(pos_col == 0){
                //printf("Unbounded Solution detected\n");
                //printf("column %d has all elements 0 or negative\n", pivot_h+1);
                status = 3;
                flag = 0;
                continue;
            }
            int pivot_v = get_pivot_v(table, pivot_h, m, n+surplus);
            if(pivot_v < 0){
                printf("Error occurred!\n");
                exit(-1);
            }
            next_iteration(table, bv, nbv, pivot_h, pivot_v, m, n+surplus);
        }
    }
    get_solution(table, sol_array, bv, nbv, m, n, surplus);
    *solution = table[m][n+surplus];
    return status;
}

int is_array_integral(float arr[100], int size){
    for(int i=0; i<size; i++){
        if(!is_nearly_equal(arr[i] - (int)(arr[i]), 0, pow(2, -6))) return 0;
    }
    return 1;
}

void branch_and_bound(float a[][100], float b[100], float c[100], float ies[100], int m, int n){
    float sol_array[100];
    float solution;
    int status = simplex(a, b, c, ies, m, n, sol_array, &solution);
    if(status > 2) return;
    if(is_array_integral(sol_array, n)){
        for(int i=0; i<n; i++){
            printf("X[%d] = %.0f\n", i+1, sol_array[i]);
        }
        printf("\nZ = %.0f\n\n", solution);
    }
    printf("\n");
    for(int i=0; i<n; i++){
        if(!is_nearly_equal(sol_array[i] - (int)(sol_array[i]), 0, pow(2, -6))){
            for(int j=0; j<n; j++){
                a[m][j] = 0;
            }
            a[m][i] = 1;
            b[m] = (int)(sol_array[i]);
            ies[m] = -1;
            branch_and_bound(a, b, c, ies, m + 1, n);

            b[m] = (int)(sol_array[i]) + 1;
            ies[m] = 1;
            branch_and_bound(a, b, c, ies, m + 1, n);
        }
    }
}

int main(){
    int m,n;
    float c[100], b[100], a[100][100];
    int ies[100];

    printf("\nEnter the no. of constraint equations :\n ");
    scanf("%d", &m);
    printf("Enter the no. of variables :\n ");
    scanf("%d", &n);
    printf("Enter the maximizing equation:\n");
    for(int i=0; i<n; i++){
        scanf("%f", &c[i]);
    }
    printf("\nEnter the constraint equation:\n");
    for(int i=0; i<m; i++){
        printf("Constraint eq%d :\n ", i+1);
        for(int j=0; j<n; j++){
            scanf("%f", &a[i][j]);
        }
        printf(" -1 for < type, 0 for = type and 1 for > type\n ");
        scanf("%d", &ies[i]);
        printf("b%d = ", i+1);
        scanf("%f", &b[i]);
    }
    float sol_array[100];
    branch_and_bound(a, b, c, ies, m, n);
    //simplex(a, b, c, ies, m, n, sol_array);
    return 0;
}
