#ifndef LIBRERIA_H
#define LIBRERIA_H
#include <stdio.h>
#include<stdlib.h>
typedef struct nodo_fila{
    int valor;
    struct nodo_fila *siguiente_fila;


}nodo_fila;
typedef struct nodo_columna{
    int valor;
    struct nodo_columna *siguiente_columna;

}nodo_columna;
int recorrer_fila(nodo_fila* head,int indice);
void get_parametros(char* ,int*, int*);
int get_lines(char ***lines, FILE *file);
int get_total_lines(FILE *file);
nodo_fila **crear_vector_filas(char *texto,int);
nodo_fila *crear_nodo_fila(int valor);
nodo_columna *crear_nodo_columnas(int valor);
nodo_columna** crear_vector_columna(nodo_fila** vector_fila,int valor_columna,int valor_fila);
void eliminar_nodo_fila( struct nodo_fila *eliminar);
void eliminar_nodo_columna( struct nodo_columna *eliminar);
void agregar_nodo_fila(int valor,struct nodo_fila *head);
void agregar_nodo_columna(int valor, struct nodo_columna *head );
void imprimir_lista(nodo_fila *head);

//Funcion que recorre linas de un archivo .txt
int get_lines(char ***lines, FILE *file){
    *lines = malloc(get_total_lines(file)*sizeof(char*));
    char **old_lines = *lines;
    int total_lines = 0;
    int line_size = 0;
    long total_chars = 0;
    char c;
    int curr_char;
    long last_end = 0;
    int in_a_line = 0;
    while ((c = getc(file)) != EOF){
        if (c != '\n'){
            in_a_line = 1;
            line_size++;
            total_chars++;
        } else{
            line_size++;
            old_lines[total_lines] = malloc(sizeof(char)*(line_size+1));
            fseek(file, last_end, SEEK_SET);
            for (curr_char=0; curr_char < line_size; ++curr_char){
                old_lines[total_lines][curr_char] = getc(file);
            }
            old_lines[total_lines][curr_char] = '\0';
            last_end += line_size;
            line_size = 0;
            total_lines++;
            in_a_line = 0;
        }
    }
    if (in_a_line){
        if (c != '\n'){
            in_a_line = 1;
            line_size++;
            total_chars++;
        } else{
            old_lines[total_lines] = malloc(sizeof(char)*(line_size+1));
            fseek(file, total_chars-line_size, SEEK_SET);
            for (curr_char=0; curr_char < line_size; ++curr_char){
                old_lines[total_lines][curr_char] = getc(file);
            }
            old_lines[total_lines][curr_char] = '\0';
            line_size = 0;
            total_lines++;
            in_a_line = 0;
        }
    }
    
    return total_lines;
}

//Funcion que retorna el total de lineas
int get_total_lines(FILE *file){
    int in_a_line = 0;
    int lines = 0;
    char c;
    
    while ((c=getc(file)) != EOF){
        if (c != '\n'){
            in_a_line=1;
        } else{
            lines++;
            in_a_line = 0;
        }
    }
    
    fseek(file, 0, SEEK_SET);
    
    return lines+in_a_line;
}

//Funcion que retorna los parametros de la matriz, y los almacena en las variables fila y columnas
void get_parametros(char *texto,int*fila, int*columna){
    FILE *file = fopen(texto, "r");
    char **file_lines=NULL;
    int total_lines = get_lines(&file_lines, file);
    //printf("%d", total_lines);
    for (int filas=0; filas<total_lines; ++filas){
        int columnas=0;
        int j=0;
        while(*(file_lines[filas]+j)!='\n'){
            if (*(file_lines[filas]+j)!=' ') {
                columnas++;
                //printf("llega hasta el if");
                j++;
            }
            else{
            j++;
            }
        *columna = columnas;

        }
        *fila = filas-1;
    }
        /*if(*(file_lines[fila]+2*columna-1) =='\n'){
            total_lines=total_lines-1;
        }*/
    //filas=filas;
    //*fila = total_lines;
    //*columna = columnas;
    fclose(file);
    return;
}
//crea la matriz proveniente de un archivo
/*int** crear_matriz(char* texto,int valor_fila){
    FILE *file = fopen(texto, "r");
    int valor=0, numero_espacios=0;
    char caracter;
    nodo_fila *nodo_inicial_f;
    nodo_columna *nodo_inicial_c;
    int **p;
    char **file_lines=NULL;
    int total_lines = get_lines(&file_lines, file);
    int primer_valor_fila[valor_fila];
    int d=1;
    p=primer_valor_fila;
    for (int i=0; i<total_lines-2; ++i){
        char inicial=*file_lines[i];
        int valor_inicial=atoi(&inicial);
        primer_valor_fila[i]=valor_inicial;
        nodo_inicial_f=crear_nodo_fila(valor_inicial);
        //char inicial_columna=*file_lines[j];
        //int valor_inicial_columna=atoi(&inicial_columna);
        int j=1;
        while ((caracter=*(file_lines[i]+j)) != '\n'){
            if(caracter!=' '){
                valor= atoi(&caracter);
                agregar_nodo_fila(valor,nodo_inicial_f);
                j++;
            }
            else{
                numero_espacios++;
                j++;
            }
        }
        imprimir_lista(nodo_inicial_f);
        printf("cambiamos de fila\n");
    }
    for (int i=0; i<valor_fila; i++) {
        printf("%d\n",primer_valor_fila[i]);
    /
    fclose(file);
    return  p;
}*/

nodo_fila * crear_nodo_fila(int valor){
    nodo_fila *nodo = malloc (sizeof(nodo_fila));
    nodo->valor=valor;
    nodo->siguiente_fila=NULL;
    
    return nodo;
    
}
nodo_columna * crear_nodo_columna(int valor){
    nodo_columna *nodo = malloc (sizeof(nodo_columna));
    nodo->valor=valor;
    nodo->siguiente_columna=NULL;
    return nodo;
    
}
void eliminar_nodo_fila( nodo_fila* eliminar){
    free(eliminar);
    return ;
}
void eliminar_nodo_columna(nodo_columna* eliminar){
    free(eliminar);
    return ;
}
void agregar_nodo_fila(int valor,nodo_fila*head){
    nodo_fila* actual=head;
    while (actual->siguiente_fila != NULL){
        actual = actual->siguiente_fila;
    }
    actual->siguiente_fila = crear_nodo_fila(valor);
    return ;
}
void agregar_nodo_columna(int valor,nodo_columna* head ){
    nodo_columna* actual=head;
    while (actual->siguiente_columna != NULL){
        actual = actual->siguiente_columna;
    }
    actual->siguiente_columna = crear_nodo_columna(valor);
    
    return ;
}
void imprimir_fila(nodo_fila *head){
    nodo_fila *actual = head;
    while (actual != NULL){
        printf("%d   ", actual->valor);
        actual = actual->siguiente_fila;
    }
    
    return;
}
void imprimir_columna(nodo_columna *head){
    nodo_columna *actual = head;
    while (actual != NULL){
        printf("%d   ", actual->valor);
        actual = actual->siguiente_columna;
    }
    
    return;
}
int recorrer_fila(nodo_fila* head,int indice){
    nodo_fila* actual=head;
    for (int i=0; i<indice; i++) {
        actual=actual->siguiente_fila;
    }
    return actual->valor;

}
nodo_columna** crear_vector_columnas(nodo_fila** vector_fila,int valor_columna,int valor_fila){
    nodo_columna **puntero;
    nodo_columna* primer_valor_columna[valor_columna];
    puntero=primer_valor_columna;
    nodo_columna *nodo_inicial_c;
    int indice_columna=0;
    int d=0;
   
    for (int j=0; j<valor_columna; j++) {
        int valor=recorrer_fila(vector_fila[0], indice_columna);
        nodo_inicial_c=crear_nodo_columna(valor);
        //imprimir_columna(nodo_inicial_c);
        
        //primer_valor_columna[j]=nodo_inicial_c;
        //actual=nodo_inicial_c;
        int indice_fila=1;
        printf("es la columna %d \n",indice_columna);
        //printf("%d\n",indice_columna);
        //printf("%d",indice_fila);
        for (int i=1; i<valor_fila; i++) {
            imprimir_fila(vector_fila[indice_fila]);
            printf("\n pasaste el segundo for %d \n",indice_fila);
            int entero_columna=recorrer_fila(vector_fila[indice_fila],indice_columna);
            printf("%d\n",entero_columna);
            //printf("%d\n",valor_columna);
            agregar_nodo_columna(entero_columna,nodo_inicial_c);
            //printf("%d\n",indice_fila);
            indice_fila=indice_fila+1;
        }
        indice_columna=indice_columna+1;
        primer_valor_columna[d]=nodo_inicial_c;
        d=d+1;
    }
    return puntero;
}

nodo_fila** crear_vector_filas(char* texto,int valor_fila){
    FILE *file = fopen(texto, "r");
    int valor, numero_espacios,d=0;
    char caracter;
    nodo_fila *nodo_inicial_f;
    nodo_fila **p;
    char **file_lines=NULL;
    int total_lines = get_lines(&file_lines, file);
    nodo_fila* primer_valor_fila[valor_fila];
    p=primer_valor_fila;
    for (int i=0; i<total_lines-2; ++i){
        char inicial=*file_lines[i];
        int valor_inicial=atoi(&inicial);
        //primer_valor_fila[i]=valor_inicial;
        nodo_inicial_f=crear_nodo_fila(valor_inicial);
        //primer_valor_fila[i]=nodo_inicial_f;
        int j=1;
        while ((caracter=*(file_lines[i]+j)) != '\n'){
            if(caracter!=' '){
                valor= atoi(&caracter);
                agregar_nodo_fila(valor,nodo_inicial_f);
                j++;
            }
            else{
                numero_espacios++;
                j++;
            }
        }
        primer_valor_fila[d]=nodo_inicial_f;
        d++;
        imprimir_fila(nodo_inicial_f);
        printf("cambiamos de fila\n");
    }
    fclose(file);
    return  p;
}

#endif
