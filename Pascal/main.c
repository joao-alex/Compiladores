#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define AND 4
#define ARRAY 8
#define BEGIN 13
#define DO 15
#define DIV 17
#define END 20
#define ELSE 23
#define FUNCTION 31
#define IF 33
#define NOT 36
#define OR 38
#define OF 39
#define PROCEDURE 48
#define PROGRAM 52
#define THEN 56
#define VAR 59
#define WHILE 64
#define ID 65
#define NUM 66
#define PONTO_VIRGULA 67
#define PONTO 68
#define PONTO_PONTO 69
#define VIRGULA 70
#define DOIS_PONTOS 71
#define DOIS_PONTOS_IGUAL 72
#define MAIS 73
#define MENOS 74
#define ABRE_COLCHETES 75
#define FECHA_COLCHETES 76
#define ABRE_PARENTESES 77
#define FECHA_PARENTESES 78
#define IGUAL 79
#define MENOR 80
#define DIFERENTE 81
#define MENOR_IGUAL 82
#define MAIOR 83
#define MAIOR_IGUAL 84
#define ASTERISCO 85
#define FIM 99





typedef struct elemento{
    int token;
    int linha;
	char str[100];
    struct elemento *prox;
}No;

typedef struct Fila {
    int tamanho;
    No* primeiro;
    No* ultimo;
}Fila;

void iniciaFila(Fila* fila){
    fila->tamanho = 0;
    fila->primeiro = NULL;
    fila->ultimo = NULL;
}

void push(Fila* fila, int token,int linha,char* str) {
    if (fila->tamanho == 0) {
        fila->primeiro = (No*)malloc(sizeof(No));
        fila->primeiro->token = token;
        fila->primeiro->linha = linha; 
		strcpy(fila->primeiro->str,str);
        fila->ultimo = fila->primeiro;
        fila->tamanho++;
    }
    else {
        fila->ultimo->prox = (No*)malloc(sizeof(No));
        fila->ultimo->prox->token = token;
        fila->ultimo->prox->linha = linha;
		strcpy(fila->ultimo->prox->str,str);
        fila->ultimo->prox->prox = NULL;
        fila->ultimo = fila->ultimo->prox;
        fila->tamanho++;
    }
}

No* pull(Fila* fila) {
    int token;
    No* aux;
    
    
    if (fila->tamanho == 0) {
        return NULL;
    }
    else {
        aux = fila->primeiro;
        fila->primeiro = fila->primeiro->prox;
        fila->tamanho--;
        return aux;
    }
    return NULL;
}

int getToken(No* no){
    return no->token;
}

int getLinha(No* no){
    return no->linha;
}

char* getStr(No* no){
	return no->str;
}

No* token;

int ids[] = {2,3,5,6,7,9,10,11,12,14,16,18,19,21,22,24,25,26,27,28,29,30,32,34,35,37,40,41,42,43,44,45,46,47,49,50,51,53,54,55,57,58,60,61,62,63};

bool verifyIds(int state){
	int i;
	for (i = 0; i < 46; i++){
		if(state==ids[i])
			return true;
		else if(ids[i]>state)
			return false;
	}
	return false;	
}

bool states[]={false,false,true,true,true,true,true,true,
               true,true,true,true,true,true,true,true,
               true,true,true,true,true,true,true,true,
               true,true,true,true,true,true,true,true,
               true,true,true,true,true,true,true,true,
               true,true,true,true,true,true,true,true,
               true,true,true,true,true,true,true,true,
               true,true,true,true,true,true,true,true,
               true,true,true,true,true,true,true,true,
               true,true,true,true,true,true,true,true,
               true,true,true,true,true,true,false,false,true,false
            };

char symbols[] = {'0','1','2','3','4','5','6','7','8','9',
                  ';','.',',',':','+','-','[',']','(',')','=','<','>','*',
                  'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','{','}','_'
                };
int edges[90][54]={/* 0  1  2  3  4  5  6  7  8  9  ;  .  ,  :  +  -  [  ]  (  )  =  <  >  *  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  {  }  _  other*/
       /*state 0*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 1*/  {66,66,66,66,66,66,66,66,66,66,67,68,70,71,73,74,75,76,77,78,79,80,83,85, 2, 9,65,14,18,24,65,65,32,65,65,65,65,34,37,40,65,65,65,53,65,57,60,65,65,65,89, 0,65, 0},
       /*state 2*/  {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65, 3,65,65,65, 5,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 3*/  {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65, 4,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 4*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 5*/  {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 6,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 6*/  {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 7*/  {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 8,65, 0, 0,65, 0},
       /*state 8*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 9*/  {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,10,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 10*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,11,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 11*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,12,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 12*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65,13,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 13*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 14*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,16,65,65,65,65,65,15,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 15*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 16*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,17,65,65,65,65, 0, 0,65, 0},
       /*state 17*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 18*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,21,65,19,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 19*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,20,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 20*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 21*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,22,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 22*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,23,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 23*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 24*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,25,65,65,65,65,65, 0, 0,65, 0},
       /*state 25*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65,26,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 26*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,27,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 27*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,28,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 28*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,29,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0}, 
       /*state 29*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65,65,30,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 30*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65,31,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 31*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 32*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,33,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 33*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 34*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65,65,35,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 35*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,36,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 36*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 37*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,39,65,65,65,65,65,65,65,65,65,65,65,38,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 38*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 39*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 40*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,41,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 41*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65,65,42,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 42*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,43,65,65,65,49,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 43*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,44,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 44*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,45,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 45*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,46,65,65,65,65,65, 0, 0,65, 0},
       /*state 46*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,47,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 47*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,48,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 48*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 49*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,50,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 50*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,51,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 51*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,52,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 52*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 53*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,54,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 54*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,55,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 55*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65,56,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 56*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 57*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,58,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 58*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,59,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 59*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 60*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,61,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 61*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,62,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 62*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,63,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 63*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,64,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 64*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 65*/ {65,65,65,65,65,65,65,65,65,65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65, 0, 0,65, 0},
       /*state 66*/ {66,66,66,66,66,66,66,66,66,66, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 67*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 68*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,69, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 69*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 70*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 71*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 72*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 73*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 74*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 75*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 76*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 77*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,86, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 78*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 79*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},            
       /*state 80*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,82, 0,81, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 81*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 82*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 83*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,84, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 84*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 85*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 86*/ {86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,87,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86},
       /*state 87*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,88, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 88*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 89*/ {89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,89,88,89,89},
                  /*  0  1  2  3  4  5  6  7  8  9  ;  .  ,  :  +  -  [  ]  (  )  =  <  >  *  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  {  }  other*/ 
    }; 

int TOKENS_IDENTIFICADOS=0;
bool ERRO_SINTATICO=false;

int getIndex(char symbol){
    int i;
    if(symbol>='A' && symbol<='Z')
        symbol+=32;
    for(i=0;i<sizeof(symbols);i++){
        if(symbol==symbols[i])
            return i;
    }
    return i;
}

int isFinalState(int state){
    return states[state];
}

int lexico(char * info,Fila* fila,int count){
    int lastFinal = 0;
    int currentState = 1;
    int verticalCursor=0, bottomCursor=0, topCursor=0,indexToken=0;
    char token[100];
    char substr[100];
    int i;
    while(info[verticalCursor]!='\0'){
        topCursor=verticalCursor;
        currentState=1;
        strcpy(token,"");
        strcpy(substr,"");
        indexToken=0;
        i=0;
        while(info[bottomCursor]!='\0'){
            char nextSymbol = info[bottomCursor];
            int index =getIndex(nextSymbol);
            currentState = edges[currentState][index];
            if(isFinalState(currentState)){
                while(topCursor<=bottomCursor){
                    if(info[topCursor]!='\n'){
                        token[indexToken]=info[topCursor];
                        indexToken++;
                    }
                    topCursor++;
                    
                }
                lastFinal=currentState;
            }
            if(currentState==0){
                if(strlen(token)==0)
                    bottomCursor=topCursor;
                break;
            }
            substr[i]=info[bottomCursor];
            i++;
            bottomCursor++;
        }
        token[indexToken]='\0';
        substr[i]='\0';
        if(strlen(token)>0){
            if(strlen(substr)>strlen(token))bottomCursor=topCursor;
            if(strcmp(token," ")!=0){
				if(verifyIds(lastFinal))
					lastFinal=ID;
                if(lastFinal>=AND && lastFinal<=ASTERISCO)
                    push(fila,lastFinal,count,token);
            }
            
            TOKENS_IDENTIFICADOS++;
        }else{
            if(info[bottomCursor]!=' ' && info[bottomCursor]!='\n'){
				printf("ERRO LEXICO. Linha: %d Coluna: %d -> %c",count,bottomCursor+1,info[bottomCursor]);
				exit(1);
            }else bottomCursor++;
        } 
        verticalCursor=bottomCursor; 
    }
}




void S(Fila* tokens, int *err);
void PROGRAMA(Fila* tokens, int *err);
void BLOCO(Fila* tokens, int *err);
void B1(Fila* tokens, int *err);
void B1L(Fila* tokens, int *err);
void B1DL(Fila* tokens, int *err);
void BLOCO1(Fila* tokens, int *err);
void B2(Fila* tokens, int *err);
void B2L(Fila* tokens, int *err);
void TIPO(Fila* tokens, int *err);
void TIPOL(Fila* tokens, int *err);
void T1(Fila* tokens, int *err);
void T1L(Fila* tokens, int *err);
void FP(Fila* tokens, int *err);
void FP1(Fila* tokens, int *err);
void FP2(Fila* tokens, int *err);
void FP2L(Fila* tokens, int *err);
void FP2DL(Fila* tokens, int *err);
void V(Fila* tokens, int *err);
void V1(Fila* tokens, int *err);
void V2(Fila* tokens, int *err);
void V3(Fila* tokens, int *err);
void V3L(Fila* tokens, int *err);
void V3DL(Fila* tokens, int *err);
void CMD(Fila* tokens, int *err);
void CMDL(Fila* tokens, int *err);
void C1(Fila* tokens, int *err);
void C2(Fila* tokens, int *err);
void C2L(Fila* tokens, int *err);
void C3(Fila* tokens, int *err);
void C3L(Fila* tokens, int *err);
void C4(Fila* tokens, int *err);
void EXPRESSAO(Fila* tokens, int *err);
void E1(Fila* tokens, int *err);
void ES(Fila* tokens, int *err);
void ES1(Fila* tokens, int *err);
void TERMO(Fila* tokens, int *err);
void TERMO1(Fila* tokens, int *err);
void FATOR(Fila* tokens, int *err);
void FATORL(Fila* tokens, int *err);
void F1(Fila* tokens, int *err);
void F2(Fila* tokens, int *err);
void F2L(Fila* tokens, int *err);
void CONSTANTE(Fila* tokens, int *err); 







void eat(Fila* tokens, int validation, int* err){
    if(*err==1)
        return;
    
    if(getToken(token)==validation)
        token=pull(tokens);
    else{
        *err = 1;
        printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
    }
}


void S(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case PROGRAM :
			PROGRAMA(tokens,err);
			eat(tokens,FIM,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void PROGRAMA(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case PROGRAM :
			eat(tokens,PROGRAM,err);
            eat(tokens,ID,err);
            eat(tokens,PONTO_VIRGULA,err);
            BLOCO(tokens,err);
            eat(tokens,PONTO,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void BLOCO(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case VAR :
			eat(tokens,VAR, err);
			B1(tokens, err);
			break;
		case PROCEDURE :
			BLOCO1(tokens,err);
			break;
		case FUNCTION :
			BLOCO1(tokens,err);
			break;
		case BEGIN :
			BLOCO1(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void B1(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case ID :
			eat(tokens, ID, err);
			B1L(tokens, err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void B1L(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case VIRGULA :
			eat(tokens,VIRGULA,err);
			B1(tokens,err);
			break;
		case DOIS_PONTOS :
			eat(tokens,DOIS_PONTOS,err);
			TIPO(tokens,err);
			eat(tokens,PONTO_VIRGULA,err);
			B1DL(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void B1DL(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case ID :
			B1(tokens,err);
			break;
		case PROCEDURE :
			BLOCO1(tokens,err);
			break;
		case FUNCTION :
			BLOCO1(tokens,err);
			break;
		case BEGIN :
			BLOCO1(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void BLOCO1(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case PROCEDURE :
			eat(tokens,PROCEDURE,err);
			eat(tokens,ID,err);
			FP(tokens, err); //PF
			eat(tokens,PONTO_VIRGULA,err);
			BLOCO(tokens,err);
			eat(tokens,PONTO_VIRGULA,err);
			BLOCO1(tokens,err);
			break;
		case FUNCTION :
			eat(tokens,FUNCTION,err);
			eat(tokens,ID,err);
			FP(tokens,err);
			eat(tokens,DOIS_PONTOS,err);
			eat(tokens,ID,err);
			eat(tokens,PONTO_VIRGULA,err);
			BLOCO(tokens,err);
			eat(tokens,PONTO_VIRGULA,err);
			BLOCO1(tokens,err);
			break;
		case BEGIN :
			eat(tokens,BEGIN,err);
			B2(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void B2(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case ID :
			CMD(tokens,err);
			B2L(tokens,err);
			break;
		case PONTO_VIRGULA :
			CMD(tokens,err);
			B2L(tokens,err);
			break;
		case PONTO :
			CMD(tokens,err);
			B2L(tokens,err);
			break;
		case BEGIN :
			CMD(tokens,err);
			B2L(tokens,err);
			break;
		case END :
			CMD(tokens,err);
			B2L(tokens,err);
			break;
		case IF :
			CMD(tokens,err);
			B2L(tokens,err);
			break;
		case WHILE :
			CMD(tokens,err);
			B2L(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void B2L(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case PONTO_VIRGULA :
			eat(tokens,PONTO_VIRGULA,err);
			B2(tokens,err);
			break;
		case END :
			eat(tokens,END,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void TIPO(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case ID :
			eat(tokens,ID,err);
			TIPOL(tokens,err);
			break;
		case NUM :
			eat(tokens,NUM,err);
			eat(tokens,PONTO_PONTO,err);
			CONSTANTE(tokens,err);
			break;
		case MAIS :
			eat(tokens,MAIS,err);
			eat(tokens,NUM,err);
			eat(tokens,PONTO_PONTO,err);
			CONSTANTE(tokens,err);
			break;
		case MENOS :
			eat(tokens,MENOS,err);
			eat(tokens,NUM,err);
			eat(tokens,PONTO_PONTO,err);
			CONSTANTE(tokens,err);
			break;
		case ARRAY :
			eat(tokens, ARRAY,err);
			eat(tokens, ABRE_COLCHETES,err);
			T1(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void TIPOL(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case VIRGULA :
		case FECHA_COLCHETES :
        case PONTO_VIRGULA :
			break;
		case PONTO_PONTO :
			eat(tokens,PONTO_PONTO,err);
			CONSTANTE(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void T1(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case ID :
			TIPO(tokens,err);
			T1L(tokens,err);
			break;
		case NUM :
			TIPO(tokens,err);
			T1L(tokens,err);
			break;
		case MAIS :
			TIPO(tokens,err);
			T1L(tokens,err);
			break;
		case MENOS :
			TIPO(tokens,err);
			T1L(tokens,err);
			break;
		case ARRAY :
			TIPO(tokens,err);
			T1L(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void T1L(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case VIRGULA :
			eat(tokens,VIRGULA,err);
			T1(tokens,err);
			break;
		case FECHA_COLCHETES :
			eat(tokens,FECHA_COLCHETES,err);
			eat(tokens, OF,err);
			TIPO(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void FP(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case ABRE_PARENTESES :
			eat(tokens,ABRE_PARENTESES,err);
			FP1(tokens,err);
			break;
		case PONTO_VIRGULA:
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void FP1(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case ID :
			FP2(tokens,err);
			break;
		case VAR :
			eat(tokens,VAR,err);
			FP2(tokens,err);
			break;
		case FECHA_PARENTESES :
			eat(tokens,FECHA_PARENTESES,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void FP2(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case ID :
			eat(tokens,ID,err);
			FP2L(tokens, err);
			break;
		case VAR :
			eat(tokens,VAR,err);
			eat(tokens,ID,err);
			FP2L(tokens, err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void FP2L(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case DOIS_PONTOS :
			eat(tokens,DOIS_PONTOS,err);
			eat(tokens,ID,err);
			FP2DL(tokens,err);
			break;
		case VIRGULA:
			eat(tokens,VIRGULA,err);
			eat(tokens,ID,err);
			FP2L(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void FP2DL(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case PONTO_VIRGULA :
			eat(tokens,PONTO_VIRGULA,err);
			FP2(tokens,err);
			break; 
		case FECHA_PARENTESES :
			eat(tokens,FECHA_PARENTESES,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void V(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case ID :
			eat(tokens,ID,err);
			V1(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void V1(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case PONTO_VIRGULA :
		case VIRGULA :
		case END :
		case MAIS :
		case MENOS :
		case FECHA_COLCHETES :
		case FECHA_PARENTESES :
		case DOIS_PONTOS_IGUAL :
		case THEN :
		case DO :
		case IGUAL :
		case DIFERENTE :
		case MENOR :
		case MENOR_IGUAL :
		case MAIOR_IGUAL :
		case MAIOR :
		case OR :
		case ASTERISCO :
		case DIV :
		case AND :
			break;
		case ABRE_COLCHETES :
			V2(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void V2(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case ABRE_COLCHETES :
			eat(tokens, ABRE_COLCHETES,err);
			V3(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void V3(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case ID :
			EXPRESSAO(tokens,err);
			V3L(tokens,err);
			break;
		case NUM :
			EXPRESSAO(tokens,err);
			V3L(tokens,err);
			break;
		case MAIS :
			EXPRESSAO(tokens,err);
			V3L(tokens,err);
			break;
		case MENOS :
			EXPRESSAO(tokens,err);
			V3L(tokens,err);
			break;
		case ABRE_PARENTESES :
			EXPRESSAO(tokens,err);
			V3L(tokens,err);
			break;
		case NOT :
			EXPRESSAO(tokens,err);
			V3L(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void V3L(Fila* tokens, int *err){

	if(*err == 1)
		return;


	switch(getToken(token)){
		case VIRGULA :
			eat(tokens, VIRGULA,err);
			V3(tokens,err);
			break;
		case FECHA_COLCHETES :
			eat(tokens, FECHA_COLCHETES,err);
			V3DL(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void V3DL(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case VIRGULA :
		case PONTO_VIRGULA :
		case END :
		case MAIS :
		case MENOS :
		case FECHA_COLCHETES :
		case FECHA_PARENTESES :
		case DOIS_PONTOS_IGUAL :
		case THEN :
		case DO :
		case IGUAL :
		case DIFERENTE :
		case MENOR :
		case MENOR_IGUAL :
		case MAIOR_IGUAL :
		case MAIOR :
		case OR :
		case ASTERISCO :
		case DIV :
		case AND :
			break;
		case ABRE_COLCHETES :
			V2(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void CMD(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case ID :
			eat(tokens,ID,err);
			CMDL(tokens,err);
			break;
		case PONTO_VIRGULA :
		case END :	
			break;
		case BEGIN :
			eat(tokens,BEGIN,err);
			CMD(tokens,err);
			C3L(tokens,err);
			break;
		case IF :
			eat(tokens,IF,err);
			EXPRESSAO(tokens,err);
			eat(tokens,THEN,err);
			eat(tokens,BEGIN,err);
			CMD(tokens,err);
			eat(tokens,END,err);
			C4(tokens,err);
			break;
		case WHILE :
			eat(tokens,WHILE,err);
			EXPRESSAO(tokens,err);
			eat(tokens,DO,err);
			CMD(tokens,err);
			break; 
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void CMDL(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case PONTO_VIRGULA :
			V1(tokens,err);
			eat(tokens, DOIS_PONTOS_IGUAL,err);
			EXPRESSAO(tokens,err);
			break;
		case END :
			V1(tokens,err);
			eat(tokens, DOIS_PONTOS_IGUAL,err);
			EXPRESSAO(tokens,err);
			break;
		case ABRE_COLCHETES :
			V1(tokens,err);
			eat(tokens, DOIS_PONTOS_IGUAL,err);
			EXPRESSAO(tokens,err);
			break;
		case ABRE_PARENTESES :
			eat(tokens, ABRE_PARENTESES,err);
			C1(tokens,err);
			break;
		case DOIS_PONTOS_IGUAL :
			V1(tokens,err);
			eat(tokens, DOIS_PONTOS_IGUAL,err);
			EXPRESSAO(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void C1(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case ID :
			C2(tokens,err);
			break;
		case NUM :
			C2(tokens,err);
			break;
		case MAIS :
			C2(tokens,err);
			break;
		case MENOS :
			C2(tokens,err);
			break;
		case ABRE_PARENTESES :
			C2(tokens,err);
			break;
		case FECHA_PARENTESES :
			eat(tokens,FECHA_PARENTESES,err);
			break;
		case NOT :
			C2(tokens,err);
			break;		
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void C2(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case ID :
			EXPRESSAO(tokens,err);
			C2L(tokens,err);
			break;
		case NUM :
			EXPRESSAO(tokens,err);
			C2L(tokens,err);
			break;	
		case MAIS :
			EXPRESSAO(tokens,err);
			C2L(tokens,err);
			break;	
		case MENOS :
			EXPRESSAO(tokens,err);
			C2L(tokens,err);
			break;
		case ABRE_PARENTESES :
			EXPRESSAO(tokens,err);
			C2L(tokens,err);
			break;
		case NOT :
			EXPRESSAO(tokens,err);
			C2L(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void C2L(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case VIRGULA :
			eat(tokens,VIRGULA,err);
			C2(tokens,err);
			break;
		case FECHA_PARENTESES :
			eat(tokens,FECHA_PARENTESES,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void C3(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case ID :
			CMD(tokens,err);
			C3L(tokens,err);
			break;
		case PONTO_VIRGULA :
			CMD(tokens,err);
			C3L(tokens,err);
			break;
		case BEGIN :
			CMD(tokens,err);
			C3L(tokens,err);
			break;	
		case END :
			CMD(tokens,err);
			C3L(tokens,err);	
			break;
		case IF :
			CMD(tokens,err);
			C3L(tokens,err);
			break;
		case WHILE :
			CMD(tokens,err);
			C3L(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void C3L(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case PONTO_VIRGULA :
			eat(tokens,PONTO_VIRGULA,err);
			C3(tokens,err);
			break;
		case END :
			eat(tokens,END,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void C4(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case PONTO_VIRGULA :
		case END :
			break;
		case ELSE :
			eat(tokens,ELSE,err);
			eat(tokens,BEGIN,err);
			CMD(tokens,err);
			eat(tokens,END,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void EXPRESSAO(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case ID :
			ES(tokens,err);
			E1(tokens,err);
			break;
		case NUM :
			ES(tokens,err);
			E1(tokens,err);
			break;
		case MAIS :
			ES(tokens,err);
			E1(tokens,err);
			break;
		case MENOS :
			ES(tokens,err);
			E1(tokens,err);
			break;
		case ABRE_PARENTESES :
			ES(tokens,err);
			E1(tokens,err);
			break;
		case NOT :
			ES(tokens,err);
			E1(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void E1(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case PONTO_VIRGULA :
		case VIRGULA :
		case END :
		case FECHA_COLCHETES :
		case FECHA_PARENTESES :
		case THEN :
		case DO :
			break;
		case IGUAL :
			eat(tokens,IGUAL,err);
			ES(tokens,err);
			break;
		case DIFERENTE :
			eat(tokens,DIFERENTE,err);
			ES(tokens,err);
			break;
		case MENOR :
			eat(tokens,MENOR,err);
			ES(tokens,err);
			break;
		case MENOR_IGUAL :
			eat(tokens, MENOR_IGUAL,err);
			ES(tokens,err);
			break;
		case MAIOR_IGUAL :
			eat(tokens,MAIOR_IGUAL,err);
			ES(tokens,err);
			break;
		case MAIOR :
			eat(tokens,MAIOR,err);
			ES(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void ES(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case ID :
			TERMO(tokens,err);
			ES1(tokens,err);
			break;
		case NUM :
			TERMO(tokens,err);
			ES1(tokens,err);
			break;
		case MAIS :
			eat(tokens, MAIS,err);
			TERMO(tokens,err);
			ES1(tokens,err);
			break;
		case MENOS :
			eat(tokens, MENOS,err);
			TERMO(tokens,err);
			ES1(tokens,err);
			break;
		case ABRE_PARENTESES :
			TERMO(tokens,err);
			ES1(tokens,err);
			break;
		case NOT :
			TERMO(tokens,err);
			ES1(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void ES1(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case PONTO_VIRGULA :
		case VIRGULA :
		case END :
		case FECHA_COLCHETES :
		case FECHA_PARENTESES :
		case THEN :
		case DO :
		case IGUAL :
		case DIFERENTE :
		case MENOR :
		case MENOR_IGUAL :
		case MAIOR_IGUAL :
		case MAIOR :
			break;
		case MAIS :
			eat(tokens, MAIS,err);
			TERMO(tokens,err);
			ES1(tokens,err);
			break;
		case MENOS :
			eat(tokens, MENOS,err);
			TERMO(tokens,err);
			ES1(tokens,err);
			break;
		case OR :
			eat(tokens, OR,err);
			TERMO(tokens,err);
			ES1(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void TERMO(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case ID :
			FATOR(tokens,err);
			TERMO1(tokens,err);
			break;
		case NUM :
			FATOR(tokens,err);
			TERMO1(tokens,err);
			break; 
		case ABRE_PARENTESES :
			FATOR(tokens,err);
			TERMO1(tokens,err);
			break;
		case NOT :
			FATOR(tokens,err);
			TERMO1(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void TERMO1(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case PONTO_VIRGULA :
		case VIRGULA :
		case END :
		case MAIS :
		case MENOS :
		case FECHA_COLCHETES :
		case FECHA_PARENTESES :
		case THEN :
		case IGUAL :
		case DIFERENTE :
		case MENOR :
		case MENOR_IGUAL :
		case MAIOR_IGUAL :
		case MAIOR :
		case OR :
		case DO :
			break;
		case ASTERISCO :
			eat(tokens,ASTERISCO,err);
			FATOR(tokens,err);
			TERMO1(tokens,err);
			break;	
		case DIV :
			eat(tokens,DIV,err);
			FATOR(tokens,err);
			TERMO1(tokens,err);
			break;
		case AND :
			eat(tokens,AND,err);
			FATOR(tokens,err);
			TERMO1(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void FATOR(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case ID :
			eat(tokens,ID,err);
			FATORL(tokens,err);
			break;
		case NUM :
			eat(tokens,NUM,err);
			break;
		case ABRE_PARENTESES :
			eat(tokens,ABRE_PARENTESES,err);
			EXPRESSAO(tokens,err);
			eat(tokens,FECHA_PARENTESES,err);
			break;
		case NOT :
			eat(tokens,NOT,err);
			FATOR(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void FATORL(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case PONTO_VIRGULA :
			V1(tokens,err);
			break;
		case VIRGULA :
			V1(tokens,err);
			break;
		case END :
			V1(tokens,err);
			break;
		case MAIS :
			V1(tokens,err);
			break;
		case MENOS :
			V1(tokens,err);
			break;
		case ABRE_COLCHETES :
			V1(tokens,err);
			break;
		case FECHA_COLCHETES :
			V1(tokens,err);
			break;
		case ABRE_PARENTESES :
			eat(tokens, ABRE_PARENTESES,err);
			F1(tokens,err);
			break;
		case FECHA_PARENTESES :
			V1(tokens,err);
			break;
		case THEN :
			V1(tokens,err);
			break;
		case DO :
			V1(tokens,err);
			break;
		case IGUAL :
			V1(tokens,err);
			break;
		case DIFERENTE :
			V1(tokens,err);
			break;
		case MENOR :
			V1(tokens,err);
			break;
		case MENOR_IGUAL :
			V1(tokens,err);
			break;
		case MAIOR_IGUAL :
			V1(tokens,err);
			break;
		case MAIOR :
			V1(tokens,err);
			break;
		case OR :
			V1(tokens,err);
			break;
		case ASTERISCO :
			V1(tokens,err);
			break;
		case DIV :
			V1(tokens,err);
			break;
		case AND :
			V1(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void F1(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case ID :
			F2(tokens,err);
			break;
		case NUM :
			F2(tokens,err);
			break;
		case MAIS :
			F2(tokens,err);
			break;
		case MENOS :
			F2(tokens,err);
			break;
		case ABRE_PARENTESES :
			F2(tokens,err);
			break;
		case FECHA_PARENTESES :
			eat(tokens,FECHA_PARENTESES,err);
			break;
		case NOT :
			F2(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void F2(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case ID :
			EXPRESSAO(tokens,err);
			F2L(tokens,err);
			break;
		case NUM :
			EXPRESSAO(tokens,err);
			F2L(tokens,err);
			break;
		case MAIS :
			EXPRESSAO(tokens,err);
			F2L(tokens,err);
			break;
		case MENOS :
			EXPRESSAO(tokens,err);
			F2L(tokens,err);
			break;
		case ABRE_PARENTESES :
			EXPRESSAO(tokens,err);
			F2L(tokens,err);
			break;
		case NOT :
			EXPRESSAO(tokens,err);
			F2L(tokens,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void F2L(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case VIRGULA :
			eat(tokens, VIRGULA,err);
			F2(tokens,err);
			break;
		case FECHA_PARENTESES :
			eat(tokens, FECHA_PARENTESES,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}

void CONSTANTE(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch(getToken(token)){
		case ID :
			eat(tokens, ID,err);
			break;
		case NUM :
			eat(tokens, NUM,err);
			break;
		case MAIS :
			eat(tokens, MAIS,err);
			eat(tokens, NUM,err);
			break;
		case MENOS :
			eat(tokens, MENOS,err);
			eat(tokens, NUM,err);
			break;
		default :
			printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"",getLinha(token),getStr(token));
			*err = 1;
	}
}


void sintatico(Fila *tokens){
    int err = 0;
	token = pull(tokens);
	S(tokens,&err);
	if(err==0)
		printf("PROGRAMA CORRETO.");
}

int main(){
    char linha[2048];
	
    Fila* tokens = malloc(sizeof(Fila));
    iniciaFila(tokens);
    int count = 1;
    while(fgets(linha,2048,stdin)!=NULL){
        lexico(linha,tokens,count);
        count++;
    }
	push(tokens,FIM,count-1,"$");
	sintatico(tokens);
}