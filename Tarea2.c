#include"libreria.h"



int main (int argc,char** argv){
    char* Archivo1=argv[1];
    char* Archivo2=argv[2];
    int fila1,columna1;
    nodo_fila** vector_fila1;
    nodo_fila** vector_fila2;
    nodo_columna** vector_columna1;
    nodo_columna** vector_columna2;
    nodo_fila* prueba;
    get_parametros(Archivo1,&fila1,&columna1);
    printf("%d\n",columna1);
    printf("%d\n",fila1);
    int fila2,columna2;
    get_parametros(Archivo2,&fila2,&columna2);
    printf("%d\n",columna2);
    printf("%d\n",fila2);
    if (columna1!=fila2) {
        printf("Las matrices no son compatibles\n");
        return 0;
    }
    if (Archivo1==NULL || Archivo2==NULL)
    {
        printf("\nError deapertura del archivo. \n\n");
    }
    else{
        vector_fila1=crear_vector_filas(Archivo1,fila1);
        //printf("%d\n",columna1);
        //printf("%d\n",fila1);
        vector_columna1=crear_vector_columnas(vector_fila1,columna1,fila1);
        
        /*for (int i=0; i<3; i++) {
            prueba=vector_fila1[i];
            imprimir_lista(prueba);
        }
        printf("esta es la otra matriz\n");
        //vector_fila2=crear_vector_filas(Archivo2,fila2);
        //printf("llega despues del inicio\n");
        for (int i=0; i<8; i++) {
           printf("%d\n",inicio2[i]->valor);
        }*/
    }
    return 0;
}
