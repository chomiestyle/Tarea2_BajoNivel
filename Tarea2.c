#include <stdio.h>
#include<stdlib.h>

void get_parametros(char* ,int*, int*);
void agregar_nodo_columna(int valor, nodo_columna*);
nodo_fila * crear_nodo_fila(int valor);
nodo_columna * crear_nodo_columna(int valor);
void eliminar_nodo_fila( struct nodo_fila* eliminar);
void eliminar_nodo_columna( struct nodo_columna* eliminar);
void agregar_nodo_fila(int valor,struct nodo_fila*head);
void agregar_nodo_columna(int valor, struct nodo_columna* head );
int get_lines(char ***lines, FILE *file);
int get_total_lines(FILE *file);
void crear_matriz(char* texto);


int main (int argc,char** argv){
    char* Archivo1=argv[1];
    FILE *file = fopen(Archivo1, "r");
    int fila,columna;
    get_parametros(Archivo1,&fila,&columna);
    printf("%d\n%d\n",fila,columna);
    /*char* Archivo2=argv[2]
    char*Archivo3=argv[3]*/
    if (Archivo1==NULL)
    {
        printf("\nError deapertura del archivo. \n\n");
    }
    else{
        crear_matriz(Archivo1);
    
    }
return 0;
}
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
    int filas = 1;
    int columnas =1;
    char c;
    int parametros[2];
    while ((c=getc(file)) != EOF){
        if (c =='\n'){
            filas++;
        }
        if (filas==1) {
            if(c==' '){
                columnas++;
            }
        }
    }
    
    filas=filas-1;
    fseek(file, 0, SEEK_SET);
    *fila = filas;
    *columna = columnas;
    fclose(file);
    return;
}
void crear_matriz(char* texto){
    FILE *file = fopen(texto, "r");
    int contador_filas=0,contador_columnas=0,valor=0, numero_espacios=0;
    char caracter;
    struct nodo_fila *nodo_inicial=NULL;
    char **file_lines=NULL;
    int total_lines = get_lines(&file_lines, file);
    
    for (int i=0; i<total_lines; ++i){
        char inicial=getc(file_lines[i]);
        int valor_inicial=atoi(&inicial);
        nodo_inicial->valor=valor_inicial;
        while ((caracter=getc(file_lines[i])) != EOF){
            if (caracter != '\n'){
                if(caracter!=' '){
                    valor= atoi(&caracter);
                    agregar_nodo_fila(valor,nodo_inicial);
                }
                else{
                    numero_espacios++;
                }
            }
            else{
                contador_filas++;
            }
    }
    }
    fseek(file, 0, SEEK_SET);
    fclose(file);
    return ;
}
#ifndef MATRIX_H
#define MATRIX_H
typedef struct nodo_fila{
    int valor;
    struct nodo_fila * siguiente_fila;


}nodo_fila;
typedef struct nodo_columna{
    int valor;
    struct nodo_columna* siguiente_columna;

}nodo_columna;

nodo_fila * crear_nodo_fila(int valor){
    struct nodo_fila* nodo = malloc (sizeof(nodo_fila));
    nodo->valor=valor;
    nodo->siguiente_fila=NULL;
    
    return nodo;
    
}
nodo_columna * crear_nodo_columna(int valor){
    struct nodo_columna* nodo = malloc (sizeof(nodo_columna));
    nodo->valor=valor;
    nodo->siguiente_columna=NULL;
    
    return nodo;
    
}
void eliminar_nodo_fila(struct nodo_fila* eliminar){
    free(*eliminar);
    return;
}
void eliminar_nodo_columna(struct nodo_columna* eliminar){
    free(*eliminar);
    return;
}
void agregar_nodo_fila(int valor,struct nodo_fila*head){
    struct nodo_fila* actual=head;
    while (actual->siguiente_fila != NULL){
        actual = actual->siguiente_fila;
    }
    actual->siguiente_fila = crear_nodo_fila(valor);
    
    return;
}
void agregar_nodo_columna(int valor,struct nodo_columna* head ){
    struct nodo_columna* actual=head;
    while (actual->siguiente_columna != NULL){
        actual = actual->siguiente_columna;
    }
    actual->siguiente_columna = crear_nodo_columna(valor);
    
    return;
}

/*void recorrer_matriz(struct node_t matriz){
    node_t * current=head;
    while(current->next!=NULL){
        current=current-> siguiente_columna;
    }
    current->siguiente_columna=create_node(value);
    return;

}*/

/*void pop(node_t* eliminar, node_t *head){
    node_t* actual = head;
    while(actual->siguiente_columna!= to_delete){
        actual=actual->siguiente_columna;
    }
    actual->siguiente_columna = actual->siguiente_columna->siguiente_columna;
    eliminar_nodo(eliminar);
}*/
/*void  print_list(node_fila*head){
    nodo_fila * actual=head;
        while (actual!=NULL) {
            printf("%d\n",actual->valor);
            if (actual->siguiente_valor_fila !=NULL)) {
                actual= actual->siguiente_valor_fila;
            }
            else{
            actual=actual->siguiente_columna;
            }
        }
    if (actual->siguiente_valor_fila == NULL) {
        return;
    }
    }
}*/

#endif

