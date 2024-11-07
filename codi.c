#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 512
float Mat[N][N];
float MatDD[N][N];
float V1[N],V2[N],V3[N],V4[N];

void InitData(){
    int i, j;
    srand(334411);
    for( i = 0; i < N; i++ )
        for( j = 0; j < N; j++ ){
            Mat[i][j]= ( ((i * j)%3) ? -1 : 1 ) * (100.0 * ( rand() / (1.0 * RAND_MAX)) );
            if ( (abs(i - j) <= 3) && (i != j))
                MatDD[i][j] = ( ((i*j)%3) ? -1 : 1)*(rand()/(1.0*RAND_MAX));
            else if ( i == j )
                MatDD[i][j]=(((i*j)%3)?-1:1)*(10000.0*(rand()/(1.0*RAND_MAX)));
            else MatDD[i][j] = 0.0;
    }
    for( i = 0; i < N; i++ ){
        V1[i]=(i<N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
        V2[i]=(i>=N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
        V3[i]=(((i*j)%5)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));
    }
}

// 1. Per a comprovar que el codi funciona:
void PrintVect( float vect[N], int from, int numel ){
    if (from < 0 || from >= N || from + numel > N) {
        printf("Índexs fora de límits.\n");
        return;
    }

    for (int i = from; i < from + numel; i++) {
        printf("%.6f ", vect[i]);
    }
    printf("\n");
}

// 2. Amb el mateix objectiu, desenvoluparem una funció que mostri per pantalla un cert nombre d’elements (numel) d’una fila (row) d’una matriu a partir d’una posició donada (from).
void PrintRow( float mat[N][N], int row, int from, int numel ) {
    for (int i = from; i < from + numel; i++) {
        printf("%.6f ", mat[row][i]);
    }
}

// 3. Multiplicació d'un vector amb una constant (alfa). La funcio retorna el vector corresponent.
void MultEscalar( float vect[N], float vectres[N], float alfa ){
    for (int i = 0; i < N; i++){
        vectres[i] = alfa * vect[i];
    }
}

// 4. Producte escalar de dos vectors.
float Scalar( float vect1[N], float vect2[N] ){
    float producte = 0.0;
    for (int i = 0; i < N; i++){
        producte += vect1[i] * vect2[i];
    }
    return producte;
}

//5. Càlcul de la longitud d'un vector
float Magnitude( float vect[N] ){
        int m;
        float sumatori=0;
        for ( m=0; m<N; m++ ){
                sumatori+=vect[m]*vect[m];
        }
	sumatori = sqrt(sumatori);
        return sumatori;
}

//6. Els dos vectors són ortogonals (angle recte)
int Ortogonal( float vect1[N], float vect2[N] ){
        int i;
        float sumatori=0;
        for ( i=0; i<N; i++ ){
                sumatori+=vect1[i]*vect2[i];
        }
        if (sumatori == 0 ){
                return 1; // Ortogonal = True
        } else {
                return 0; // Ortogonal = False
        }
}

//7. Vector projecció sobre un altre vector
void Projection( float vect1[N], float vect2[N], float vectres[N] ){
        float nmdor = 0.0; // Numerador = Producte Escalar entre 2 vectors. Cridem la funció Scalar per no haver-ho de fer de nou.
        nmdor=Scalar(vect1, vect2);
        float dmdor = 0.0; //El denominador és el mòdul del vector 2. Cridem la funció Magnitude per no haver-ho de fer de nou.
        dmdor=Magnitude(vect2); 
	float divisio1 = 0.0; //Divisió entre el numerador i denominador.
        divisio1=nmdor/dmdor;
        // Reutilitzem la funció MultEscalar per a calcular el resultat.
        MultEscalar(vect2, vectres, divisio1);
}

//8. Infini-norma d’una matriu, on l'f serà el comptador de files i la c el comptador de columnes
float Infininorm( float M[N][N] ){ // És el màxim de les sumes dels valors absoluts dels elements de cada fila.
        int f, c;
        float sumatori_lin;
        float max=0;
        for ( f=0; f<N; f++ ){
                sumatori_lin=0;
                for ( c=0; c<N; c++){
                        sumatori_lin+=fabs(M[f][c]); // fabs == |float| (valor absolut d'un nombre en format float)
                }
        if ( sumatori_lin > max ){
                max=sumatori_lin;
        }
        }
        return max;
}

//9. Norma-ú d’una matriu, on la c serà el comptador de columnes i l'f serà el comptador de files
float Onenorm( float M[N][N] ){ // És el màxim de les sumes dels valors absoluts dels elements de cada columna.
        int c, f;
        float sumatori_col;
        float max=0;
        for ( c=0; c<N; c++ ){
                sumatori_col=0;
                for ( f=0; f<N; f++){
                        sumatori_col+=fabs(M[f][c]);
                }
        if ( sumatori_col > max ){
                max=sumatori_col;
        }
        }
        return max;
}

//10. Frobenius
float NormFrobenius( float M[N][N] ){
        int f, c;
        float sumatori=0;
        for ( f=0; f<N; f++){
                for ( c=0; c<N; c++ ){
                        sumatori+=M[f][c]*M[f][c];
                }
        }
        return sqrt(sumatori);
}

//11. Diagonal Dominant.
int DiagonalDom( float M[N][N] ){
        int comptador; // Comptador de files i columnes
        float sumatori_diag=0;
	// Reutilitzem el codi d'Infininorm per a calcular la suma total dels elements que són a fora de la diagonal de cada línia,
	// fent una petita variació perquè no sumi els elements que són a la diagonal.
        int f, c;
        float sumatori_no_diag;
        float max=0;
        for ( f=0; f<N; f++ ){
                sumatori_no_diag=0;
                for ( c=0; c<N; c++ ){
            		if ( f!=c ){
				sumatori_no_diag+=fabs(M[f][c]);
                    		}
        		}
        		if ( fabs(M[f][f]) < sumatori_no_diag ){
                        	max=sumatori_no_diag;
        			return 0; // DiagonalDom == False
        			}
        		}
        		return 1; // DiagonalDom == True
}

// 12. Multiplicació d'una matriu per un vector
void Matriu_x_Vector( float M[N][N], float vect[N], float vectres[N] ) {
    for (int i = 0; i < N; i++) {
        vectres[i] = 0.0;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            vectres[i] += M[i][j] * vect[j];
        }
    }
}

// 13. Resolució de sistemes d'equacions lineals
int Jacobi( float M[N][N] , float vect[N], float vectres[N], unsigned iter ) {
    if (!DiagonalDom(M)) {
        return 0;
    }
    float temp[N];
    for (int i = 0; i < N; i++) {
        vectres[i] = 0.0;
    }
    for (unsigned k = 0; k < iter; k++) {
        for (int i = 0; i < N; i++) {
            float sum = 0.0;
            for (int j = 0; j < N; j++) {
                if (j != i) {
                    sum += M[i][j] * vectres[j];
                }
            }
            temp[i] = (vect[i] - sum) / M[i][i];
        }
        for (int i = 0; i < N; i++) {
            vectres[i] = temp[i];
        }
    }
    return 1;
}


int main() {
        InitData();


        //A
        printf("V1 del 0 al 9 i del 256 al 265: \n");
        PrintVect(V1, 0, 10);
        PrintVect(V1, 256, 10);
        printf("V2 del 0 al 9 i del 256 al 265: \n");
        PrintVect(V2, 0, 10);
        PrintVect(V2, 256, 10);
        printf("V3 del 0 al 9 i del 256 al 265: \n");
        PrintVect(V3, 0, 10);
        PrintVect(V3, 256, 10);


        //B
        printf("Matriu fila 0 i fila 100 del 0 al 9:\n");
        PrintRow(Mat, 0, 0, 10);
        PrintRow(Mat, 100, 0, 10);
        printf("\n");


        //C
        printf("MatDD fila 0 del 0 al 9 i fila 100 del 95 al 104:\n");
        PrintRow(MatDD, 0, 0, 10);
        PrintRow(MatDD, 100, 95, 10);
        printf("\n");


        //D
        printf("Infininorma de Mat = %.3f\n", Infininorm(Mat));
        printf("Norma ú de Mat = %.3f\n", Onenorm(Mat));
        printf("Norma de Frobenius de Mat = %.3f\n", NormFrobenius(Mat));
        if (DiagonalDom(Mat)) {
                printf("La matriu Mat és diagonal dominant\n");
        } else {
                printf("La matriu Mat no és diagonal dominant\n");
        }


        printf("Infininorma de MatDD = %.3f\n", Infininorm(MatDD));
        printf("Norma ú de MatDD = %.3f\n", Onenorm(MatDD));
        printf("Norma de Frobenius de MatDD = %.3f\n", NormFrobenius(MatDD));
        if (DiagonalDom(MatDD)) {
                printf("La matriu MatDD és diagonal dominant\n");
        } else {
                printf("La matriu MatDD no és diagonal dominant\n");
        }


        //E
        printf("Escalar <V1,V2> = %.6f\n", Scalar(V1, V2));
        printf("Escalar <V1,V3> = %.6f\n", Scalar(V1, V3));
        printf("Escalar <V2,V3> = %.6f\n", Scalar(V2, V3));


        //F
        printf("Magnitud V1,V2 i V3 = %.6f %.6f %.6f\n", Magnitude(V1), Magnitude(V2), Magnitude(V3));


        //G
        if (Ortogonal(V1,V2)) {
                printf("V1 i V2 són ortogonals\n");
        } else {
                printf("V1 i V2 no són ortogonals\n");
        }
        if (Ortogonal(V1,V3)) {
                printf("V1 i V3 són ortogonals\n");
        } else {
                printf("V1 i V3 no són ortogonals\n");
        }
        if (Ortogonal(V2,V3)) {
                printf("V2 i V3 són ortogonals\n");
        } else {
                printf("V2 i V3 no són ortogonals\n");
        }


        //H
        float V3x2[N];
        MultEscalar(V3, V3x2, 2.0);
        printf("Els elements 0 al 9 i 256 al 265 de multiplicar V3x2.0 són:\n");
        PrintVect(V3x2, 0, 10);
        PrintVect(V3x2, 256, 10);


        //I
        float projV2_V3[N];
        Projection(V2, V3, projV2_V3);
        printf("Els elements 0 a 9 de la projecció de V2 sobre V3 són:\n");
        PrintVect(projV2_V3, 0, 10);
        float projV1_V2[N];
        Projection(V1, V2, projV1_V2);
        printf("Els elements 0 a 9 de la projecció de V1 sobre V2 són:\n");
        PrintVect(projV1_V2, 0, 10);


        //J
        float MatxV2[N];
        Matriu_x_Vector(Mat, V2, MatxV2);
        printf("Els elements 0 a 9 del resultat de Mat per v2 són:\n");
        PrintVect(MatxV2, 0, 10);


        //K
        float solució1[N];
        if (Jacobi(MatDD, V3, solució1, 1)) {
                printf("Els elements 0 a 9 de la solució (1 iter) del sistema són:\n");
                PrintVect(solució1, 0, 10);
        } else {
                printf("Com que MatDD no és diagonal dominant, no és possible fer Jacobi\n");
        }
        float solució1000[N];
        if (Jacobi(MatDD, V3, solució1000, 1000)) {
                printf("Els elements 0 a 9 de la solució (1000 ites) del sistema són:\n");
                PrintVect(solució1000, 0, 10);
        } else {
                printf("Com que MatDD no és diagonal dominant, no és possible fer Jacobi\n");
        }
}

