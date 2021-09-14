//parser_LL.c
#include <stdlib.h>
#include <stdio.h>

#define FALSE (0)
#define TRUE (-1)

/*Simbolos no-Terminales de la gramatica LEXAL*/
#define SIMBOLO_NO_TERMINAL_S 1
#define SIMBOLO_NO_TERMINAL_InstruccionCompuesta 2
#define SIMBOLO_NO_TERMINAL_BloqueInstrucciones 3
#define SIMBOLO_NO_TERMINAL_BloqueInstrucciones2 4
#define SIMBOLO_NO_TERMINAL_Instruccion 5
#define SIMBOLO_NO_TERMINAL_InstruccionAsignacion 6
#define SIMBOLO_NO_TERMINAL_InstruccionIf 7
#define SIMBOLO_NO_TERMINAL_InstruccionIf2 8
#define SIMBOLO_NO_TERMINAL_InstruccionWhile 9
#define SIMBOLO_NO_TERMINAL_InstruccionImprime 10
#define SIMBOLO_NO_TERMINAL_InstruccionFor 11
#define SIMBOLO_NO_TERMINAL_InstruccionBreak 12
#define SIMBOLO_NO_TERMINAL_InstruccionDo 13
#define SIMBOLO_NO_TERMINAL_Expresion 14
#define SIMBOLO_NO_TERMINAL_Expresion2 15
#define SIMBOLO_NO_TERMINAL_ExpRelacional 16
#define SIMBOLO_NO_TERMINAL_ExpRelacional2 17
#define SIMBOLO_NO_TERMINAL_ExpCompuesta 18
#define SIMBOLO_NO_TERMINAL_ExpCompuesta2 19
#define SIMBOLO_NO_TERMINAL_ExpSimple 20
#define SIMBOLO_NO_TERMINAL_ExpSimple2 21
#define SIMBOLO_NO_TERMINAL_Factor 22
#define SIMBOLO_NO_TERMINAL_Factor2 23
#define SIMBOLO_NO_TERMINAL_Termino 24
#define SIMBOLO_NO_TERMINAL_OpAditivo 25
#define SIMBOLO_NO_TERMINAL_OpMultiplicativo 26
#define SIMBOLO_NO_TERMINAL_OpRelacional 27
#define SIMBOLO_NO_TERMINAL_OpLogico 28
#define SIMBOLO_NO_TERMINAL_OpPon 29
#define SIMBOLO_NO_TERMINAL_Numero 30
#define SIMBOLO_NO_TERMINAL_InstruccionSelect 31

#define TIPO_SIMBOLO_NO_TERMINAL            1
#define SIMBOLOS_NO_TERMINALES_NUMAX        31

/*Simbolos Terminales de la gramatica LEXAL*/
#define SIMBOLO_TERMINAL_PROGRAMA 1
#define SIMBOLO_TERMINAL_EOF 2
#define SIMBOLO_TERMINAL_Espacio 3
#define SIMBOLO_TERMINAL_Tabulador 4
#define SIMBOLO_TERMINAL_SaltoDeLinea 5
#define SIMBOLO_TERMINAL_AbreLlave 6
#define SIMBOLO_TERMINAL_CierraLlave 7
#define SIMBOLO_TERMINAL_AbreParentesis 8
#define SIMBOLO_TERMINAL_CierraParentesis 9
#define SIMBOLO_TERMINAL_PuntoYComa 10
#define SIMBOLO_TERMINAL_Interrogacion 11
#define SIMBOLO_TERMINAL_Exclamacion 12
#define SIMBOLO_TERMINAL_Asterisco 13
#define SIMBOLO_TERMINAL_Diagonal 14
#define SIMBOLO_TERMINAL_Mas 15
#define SIMBOLO_TERMINAL_Menos 16
#define SIMBOLO_TERMINAL_Igual 17
#define SIMBOLO_TERMINAL_MenorQue 18
#define SIMBOLO_TERMINAL_MayorQue 19
#define SIMBOLO_TERMINAL_Potencia 20
#define SIMBOLO_TERMINAL_MenorIgual 21
#define SIMBOLO_TERMINAL_MayorIgual 22
#define SIMBOLO_TERMINAL_Identico 23
#define SIMBOLO_TERMINAL_Diferente 24
#define SIMBOLO_TERMINAL_If 25
#define SIMBOLO_TERMINAL_Else 26
#define SIMBOLO_TERMINAL_While 27
#define SIMBOLO_TERMINAL_And 28
#define SIMBOLO_TERMINAL_Or 29
#define SIMBOLO_TERMINAL_NumEnt 30
#define SIMBOLO_TERMINAL_NumDec 31
#define SIMBOLO_TERMINAL_ID 32
#define SIMBOLO_TERMINAL_For 33
#define SIMBOLO_TERMINAL_Break 34
#define SIMBOLO_TERMINAL_DO 35
#define SIMBOLO_TERMINAL_Select 36
#define SIMBOLO_TERMINAL_From 37
#define SIMBOLO_TERMINAL_Where 38

#define TIPO_SIMBOLO_TERMINAL               2
#define SIMBOLOS_TERMINALES_NUMAX           38


/*Predict para el parser LL (1)*/
int MR[SIMBOLOS_NO_TERMINALES_NUMAX][SIMBOLOS_TERMINALES_NUMAX] = {
    {1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, 3, -1, -1, -1, -1, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 3, -1, 3, -1, -1, -1, -1, 3, 3, 3, 3,-1,-1},
   {-1, -1, -1, -1, -1, -1, 5, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, 10, -1, -1, -1, -1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 7, -1, 8, -1, -1, -1, -1, 6, 11, 12, 13,57,57},
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 14, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, 17, -1, -1, 17, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 18, -1, -1, -1, -1, -1, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 20, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 21, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 22,-1,-1},
   {-1, -1, -1, -1, -1, -1, -1, 23, -1, -1, -1, 23, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 23, 23, 23, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, 25, -1, 25, 25, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 25, -1, 24, 24, -1, -1, -1, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, -1, 26, -1, -1, -1, 26, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 26, 26, 26, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, 28, -1, 28, 28, -1, -1, -1, -1, -1, -1, -1, 27, 27, -1, 27, 27, 27, 27, -1, 27, -1, 28, 28, -1, -1, -1, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, -1, 29, -1, -1, -1, 29, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 29, 29, 29, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, 31, -1, 31, 31, -1, -1, -1, -1, 30, 30, -1, 31, 31, -1, 31, 31, 31, 31, -1, 31, -1, 31, 31, -1, -1, -1, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, -1, 32, -1, -1, -1, 32, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 32, 32, 32, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, 34, -1, 34, 34, -1, -1, 33, 33, 34, 34, -1, 34, 34, -1, 34, 34, 34, 34, -1, 34, -1, 34, 34, -1, -1, -1, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, -1, 35, -1, -1, -1, 35, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 35, 35, 35, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, 37, -1, 37, 37, -1, -1, 37, 37, 37, 37, -1, 37, 37, 36, 37, 37, 37, 37, -1, 37, -1, 37, 37, -1, -1, -1, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, -1, 40, -1, -1, -1, 41, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 38, 38, 39, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 42, 43, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 44, 45, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 47, 46, -1, 49, 48, 50, 51, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52, 53, -1, -1, -1, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 54, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 55, 56, -1, -1, -1, -1,-1,-1},
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,58,-1},

};

struct t_token
{
    int intTokenCodigo;
    char *strTokenTextoFuente;
    int intReglon;
    int intColumna;
    struct t_token *ptrSig;
};
typedef struct t_token t_token;

t_token *ptrTokenList;
t_token *ptrCurrentToken;

//STACK DE RECONOCIMIENTO LL
struct t_StackLL
{
    int intSimboloTipo; //Si es Terminal o No Terminal
    int intSimboloCodigo; //Código Numérico (#define) de T o NT

    struct t_StackLL *ptrSig;
};
typedef struct t_StackLL t_StackLL;
t_StackLL *ptrStackLLTop = NULL;



/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*                                                             Parser LL (1)                                                                               */
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void pushLL(int intSimboloTipo, int intSimboloCodigo)
{
    t_StackLL *nuevo = (t_StackLL *)malloc(sizeof(t_StackLL));
    nuevo ->intSimboloTipo = intSimboloTipo;
    nuevo ->intSimboloCodigo = intSimboloCodigo;
    nuevo ->ptrSig=NULL;

    if(ptrStackLLTop != NULL) /*Hay elementos en el stack*/
    {
        nuevo ->ptrSig=ptrStackLLTop;
    }/*if*/
    ptrStackLLTop =nuevo;
}/*pushLL*/

void pushLL_T(int intSimboloCodigo)
{
    pushLL(TIPO_SIMBOLO_TERMINAL, intSimboloCodigo);
}/*pushLL_T*/

void pushLL_NT(int intSimboloCodigo)
{
    pushLL(TIPO_SIMBOLO_NO_TERMINAL, intSimboloCodigo);
}/*pushLL_NT*/

void popLL()
{
    t_StackLL *aux;
    if(ptrStackLLTop != NULL) /*Hay elementos en el stack*/
    {
        aux = ptrStackLLTop;
        ptrStackLLTop = ptrStackLLTop->ptrSig;
        free(aux);
    }/*if*/
}/*popLL*/

void vaciar_StackLL()
{
    while(ptrStackLLTop != NULL)
        popLL();
}/*vaciar_StackLL*/

int stack_top_es_NT()
{
    int bolRes=FALSE;
    if(ptrStackLLTop!=NULL)
    {
        if(ptrStackLLTop->intSimboloTipo==TIPO_SIMBOLO_NO_TERMINAL)
        {
            bolRes=TRUE;
        }
    }
    return bolRes;
}

void imprimeT(int intSimboloCodigo)
{
    switch(intSimboloCodigo)
    {
        case SIMBOLO_TERMINAL_PROGRAMA: printf("SIMBOLO_TERMINAL_PROGRAMA"); break;
        case SIMBOLO_TERMINAL_EOF: printf("SIMBOLO_TERMINAL_EOF"); break;
        case SIMBOLO_TERMINAL_Espacio: printf("SIMBOLO_TERMINAL_Espacio"); break;
        case SIMBOLO_TERMINAL_Tabulador: printf("SIMBOLO_TERMINAL_Tabulador"); break;
        case SIMBOLO_TERMINAL_SaltoDeLinea: printf("SIMBOLO_TERMINAL_Salto_Linea"); break;
        case SIMBOLO_TERMINAL_AbreLlave: printf("SIMBOLO_TERMINAL_AbreLlave"); break;
        case SIMBOLO_TERMINAL_CierraLlave: printf("SIMBOLO_TERMINAL_CierraLlave"); break;
        case SIMBOLO_TERMINAL_AbreParentesis: printf("SIMBOLO_TERMINAL_AbreParentesis"); break;
        case SIMBOLO_TERMINAL_CierraParentesis: printf("SIMBOLO_TERMINAL_CierraParentesis"); break;
        case SIMBOLO_TERMINAL_PuntoYComa: printf("SIMBOLO_TERMINAL_PuntoYComa"); break;
        case SIMBOLO_TERMINAL_Interrogacion: printf("SIMBOLO_TERMINAL_Interrogacion"); break;
        case SIMBOLO_TERMINAL_Exclamacion: printf("SIMBOLO_TERMINAL_Exclamacion"); break;
        case SIMBOLO_TERMINAL_Asterisco: printf("SIMBOLO_TERMINAL_Asterisco"); break;
        case SIMBOLO_TERMINAL_Diagonal: printf("SIMBOLO_TERMINAL_Diagonal"); break;
        case SIMBOLO_TERMINAL_Mas: printf("SIMBOLO_TERMINAL_Mas"); break;
        case SIMBOLO_TERMINAL_Menos: printf("SIMBOLO_TERMINAL_Menos"); break;
        case SIMBOLO_TERMINAL_Igual: printf("SIMBOLO_TERMINAL_Igual"); break;
        case SIMBOLO_TERMINAL_MenorQue: printf("SIMBOLO_TERMINAL_MenorQue"); break;
        case SIMBOLO_TERMINAL_MayorQue: printf("SIMBOLO_TERMINAL_MayorQue"); break;
        case SIMBOLO_TERMINAL_Potencia: printf("SIMBOLO_TERMINAL_Potencia"); break;
        case SIMBOLO_TERMINAL_MenorIgual: printf("SIMBOLO_TERMINAL_MenorIgual"); break;
        case SIMBOLO_TERMINAL_MayorIgual: printf("SIMBOLO_TERMINAL_MayorIgual"); break;
        case SIMBOLO_TERMINAL_Identico: printf("SIMBOLO_TERMINAL_Identico"); break;
        case SIMBOLO_TERMINAL_Diferente: printf("SIMBOLO_TERMINAL_Diferente"); break;
        case SIMBOLO_TERMINAL_If: printf("SIMBOLO_TERMINAL_If"); break;
        case SIMBOLO_TERMINAL_Else: printf("SIMBOLO_TERMINAL_Else"); break;
        case SIMBOLO_TERMINAL_While: printf("SIMBOLO_TERMINAL_While"); break;
        case SIMBOLO_TERMINAL_And: printf("SIMBOLO_TERMINAL_And"); break;
        case SIMBOLO_TERMINAL_Or: printf("SIMBOLO_TERMINAL_Or"); break;
        case SIMBOLO_TERMINAL_NumEnt: printf("SIMBOLO_TERMINAL_Num"); break;
        case SIMBOLO_TERMINAL_NumDec: printf("SIMBOLO_TERMINAL_Num"); break;
        case SIMBOLO_TERMINAL_ID: printf("SIMBOLO_TERMINAL_ID"); break;
        case SIMBOLO_TERMINAL_For: printf("SIMBOLO_TERMINAL_For"); break;
        case SIMBOLO_TERMINAL_Break: printf("SIMBOLO_TERMINAL_Break"); break;
        case SIMBOLO_TERMINAL_DO: printf("SIMBOLO_TERMINAL_DO"); break;
        case SIMBOLO_TERMINAL_Select: printf("SIMBOLO_TERMINAL_Select"); break;
        case SIMBOLO_TERMINAL_From: printf("SIMBOLO_TERMINAL_From"); break;
        case SIMBOLO_TERMINAL_Where: printf("SIMBOLO_TERMINAL_Where");break;
        default: printf("ERROR"); break;
    }/*switcg*/
}/*imprimeT*/

void imprimeNT(int intSimboloCodigo)
{
    switch(intSimboloCodigo)
    {
        case SIMBOLO_NO_TERMINAL_S: printf("SIMBOLO_NO_TERMINAL_S"); break;
        case SIMBOLO_NO_TERMINAL_InstruccionCompuesta: printf("SIMBOLO_NO_TERMINAL_InstruccionCompuesta"); break;
        case SIMBOLO_NO_TERMINAL_BloqueInstrucciones: printf("SIMBOLO_NO_TERMINAL_BloqueInstrucciones"); break;
        case SIMBOLO_NO_TERMINAL_BloqueInstrucciones2: printf("SIMBOLO_NO_TERMINAL_BloqueInstrucciones2"); break;
        case SIMBOLO_NO_TERMINAL_Instruccion: printf("SIMBOLO_NO_TERMINAL_Instruccion"); break;
        case SIMBOLO_NO_TERMINAL_InstruccionAsignacion: printf("SIMBOLO_NO_TERMINAL_InstruccionAsignacion"); break;
        case SIMBOLO_NO_TERMINAL_InstruccionIf: printf("SIMBOLO_NO_TERMINAL_InstruccionIf"); break;
        case SIMBOLO_NO_TERMINAL_InstruccionIf2: printf("SIMBOLO_NO_TERMINAL_InstruccionIf2"); break;
        case SIMBOLO_NO_TERMINAL_InstruccionWhile: printf("SIMBOLO_NO_TERMINAL_InstruccionWhile"); break;
        case SIMBOLO_NO_TERMINAL_InstruccionImprime: printf("SIMBOLO_NO_TERMINAL_InstruccionImprime"); break;
        case SIMBOLO_NO_TERMINAL_InstruccionFor: printf("SIMBOLO_NO_TERMINAL_InstruccionFor"); break;
        case SIMBOLO_NO_TERMINAL_InstruccionBreak: printf("SIMBOLO_NO_TERMINAL_InstruccionBreak"); break;
        case SIMBOLO_NO_TERMINAL_InstruccionDo: printf("SIMBOLO_NO_TERMINAL_DO"); break;
        case SIMBOLO_NO_TERMINAL_Expresion: printf("SIMBOLO_NO_TERMINAL_Expresion"); break;
        case SIMBOLO_NO_TERMINAL_Expresion2: printf("SIMBOLO_NO_TERMINAL_Expresion2"); break;
        case SIMBOLO_NO_TERMINAL_ExpRelacional: printf("SIMBOLO_NO_TERMINAL_ExpRelacional"); break;
        case SIMBOLO_NO_TERMINAL_ExpRelacional2: printf("SIMBOLO_NO_TERMINAL_ExpRelacional2"); break;
        case SIMBOLO_NO_TERMINAL_ExpCompuesta: printf("SIMBOLO_NO_TERMINAL_ExpCompuesta"); break;
        case SIMBOLO_NO_TERMINAL_ExpCompuesta2: printf("SIMBOLO_NO_TERMINAL_ExpCompuesta2"); break;
        case SIMBOLO_NO_TERMINAL_ExpSimple: printf("SIMBOLO_NO_TERMINAL_ExpSimple"); break;
        case SIMBOLO_NO_TERMINAL_ExpSimple2: printf("SIMBOLO_NO_TERMINAL_ExpSimple2"); break;
        case SIMBOLO_NO_TERMINAL_Factor: printf("SIMBOLO_NO_TERMINAL_Factor"); break;
        case SIMBOLO_NO_TERMINAL_Factor2: printf("SIMBOLO_NO_TERMINAL_Factor2"); break;
        case SIMBOLO_NO_TERMINAL_Termino: printf("SIMBOLO_NO_TERMINAL_Termino"); break;
        case SIMBOLO_NO_TERMINAL_OpAditivo: printf("SIMBOLO_NO_TERMINAL_OpAditivo"); break;
        case SIMBOLO_NO_TERMINAL_OpMultiplicativo: printf("SIMBOLO_NO_TERMINAL_OpMultiplicativo"); break;
        case SIMBOLO_NO_TERMINAL_OpRelacional: printf("SIMBOLO_NO_TERMINAL_OpRelacional"); break;
        case SIMBOLO_NO_TERMINAL_OpLogico: printf("SIMBOLO_NO_TERMINAL_OpLogico"); break;
        case SIMBOLO_NO_TERMINAL_OpPon: printf("SIMBOLO_NO_TERMINAL_OpPon"); break;
        case SIMBOLO_NO_TERMINAL_Numero: printf("SIMBOLO_NO_TERMINAL_Numero"); break;
        case SIMBOLO_NO_TERMINAL_InstruccionSelect: printf("SIMBOLO_NO_TERMINAL_InstruccionSelect"); break;
        default: printf("ERROR"); break;
    }/*switcg*/
}/*imprimeNT*/

void imprime_entrada()
{
    t_token *aux = ptrCurrentToken;
    printf("Entrada:  ");
    while(aux!=NULL)
    {
        imprimeT(aux->intTokenCodigo);
        printf("    ");
        aux = aux->ptrSig;
    }
    printf("\n");
}/*imprime_entrada*/

void stack_imprime2(t_StackLL *nodoStack)
{
    if(nodoStack != NULL)
    {
        stack_imprime2(nodoStack->ptrSig);
        switch(nodoStack->intSimboloTipo)
        {
        case TIPO_SIMBOLO_TERMINAL:
            imprimeT(nodoStack->intSimboloCodigo);
            break;
        case TIPO_SIMBOLO_NO_TERMINAL:
            imprimeNT(nodoStack->intSimboloCodigo);
            break;
        default:
            printf("Error");
            break;
        }/*switch*/
        printf("   ");
    }/*if*/
}/*stack_imprime2*/

void stack_imprime()
{
    printf("Stack:  ");
    stack_imprime2(ptrStackLLTop);
    printf("\n");
}/*stack_imprime*/

int Parser_LL_AplicarRegla()
{
    int intNumReglaObtenidaDeMR;
    /*Se obtiene una regla de la matriz de reconocimiento*/
    intNumReglaObtenidaDeMR = MR[ptrStackLLTop->intSimboloCodigo-1][ptrCurrentToken->intTokenCodigo-1];

    if(intNumReglaObtenidaDeMR>0)/*Regla gramatica valida*/
    {
        imprime_regla(intNumReglaObtenidaDeMR);
        SustituyeNTenStackPorParteDerechaDeLaRegla(intNumReglaObtenidaDeMR);
    }
    else
    {
        return TRUE; /* Hay error sintactico*/
    }
    return FALSE; /*No Hay error sintactico*/
}/*ParserLLAplicarRegla*/

void imprime_regla(int intNumReglaObtenidaDeMR)
{
    switch(intNumReglaObtenidaDeMR)
    {
        case 1: printf("1.	S -> programa InstruccionCompuesta"); break;
        case 2: printf("2.	InstruccionCompuesta -> { BloqueInstrucciones }"); break;
        case 3: printf("3.	BloqueInstrucciones -> Instruccion BloqueInstrucciones2"); break;
        case 4: printf("4.	BloqueInstrucciones2 -> ; Instruccion BloqueInstrucciones2"); break;
        case 5: printf("5.	BloqueInstrucciones2 -> epsilon"); break;
        case 6: printf("6.	Instruccion -> InstruccionAsignacion"); break;
        case 7: printf("7.	Instruccion -> InstruccionIf"); break;
        case 8: printf("8.	Instruccion -> InstruccionWhile"); break;
        case 9: printf("9.	Instruccion -> InstruccionImprime"); break;
        case 10: printf("10.	Instruccion -> InstruccionCompuesta"); break;
        case 11: printf("11.	Instruccion -> InstruccionFor"); break;
        case 12: printf("12.	Instruccion -> InstruccionBreak"); break;
        case 13: printf("13.	Instruccion -> InstruccionDo"); break;
        case 14: printf("14.	InstruccionAsignacion -> ID = Expresion"); break;
        case 15: printf("15.	InstruccionIf -> if ( Expresion ) Instruccion InstruccionIf2"); break;
        case 16: printf("16.	InstruccionIf2 -> else Instrucción"); break;
        case 17: printf("17.	Instruccionif2 -> epsilon"); break;
        case 18: printf("18.	InstruccionWhile -> while ( Expresion ) Instruccion"); break;
        case 19: printf("19.	InstruccionImprime -> ? Expresion"); break;
        case 20: printf("20.	InstruccionFor -> for ( InstruccionAsignacion ; Expresion ; Expresion ) { BloqueInstrucciones }"); break;
        case 21: printf("21.	InstruccionBreak -> break ;"); break;
        case 22: printf("22.	InstruccionDo -> do { InstruccionAsignacion ; Expresion ; Expresion ) { BloqueInstrucciones }"); break;
        case 23: printf("23.	Expresion -> ExpRelacional Expresion2"); break;
        case 24: printf("24.	Expresion2 -> OpLogico ExpRelacional Expresion2"); break;
        case 25: printf("25.	Expresion2 -> epsilon"); break;
        case 26: printf("26.	ExpRelacional -> ExpCompuesta ExpRelacional2"); break;
        case 27: printf("27.	ExpRelacional2 -> OpRelacional ExpCompuesta ExpRelacional2"); break;
        case 28: printf("28.	ExpRelacional2 -> epsilon"); break;
        case 29: printf("29.	ExpCompuesta -> ExpSimple ExpCompuesta2"); break;
        case 30: printf("30.	ExpCompuesta2 -> OpAditivo ExpSimple ExpCompuesta2"); break;
        case 31: printf("31.	ExpCompuesta2 -> epsilon"); break;
        case 32: printf("32.	ExpSimple -> Factor ExpSimple2"); break;
        case 33: printf("33.	ExpSimple2 -> OpMultiplicativo Factor ExpSimple2"); break;
        case 34: printf("34.	ExpSimple2 -> epsilon"); break;
        case 35: printf("35.	Factor -> Termino Factor2"); break;
        case 36: printf("36.	Factor2 -> OpPon Termino"); break;
        case 37: printf("37.	Factor2 -> epsilon"); break;
        case 38: printf("38.	Termino -> Numero"); break;
        case 39: printf("39.	Termino -> ID"); break;
        case 40: printf("40.	Termino -> ( Expresion )"); break;
        case 41: printf("41.	Termino -> ! ( Expresion )"); break;
        case 42: printf("42.	OpAditivo -> +"); break;
        case 43: printf("43.	OpAditivo -> -"); break;
        case 44: printf("44.	OpMultiplicativo -> *"); break;
        case 45: printf("45.	OpMultiplicativo -> /"); break;
        case 46: printf("46.	OpRelacional -> >"); break;
        case 47: printf("47.	OpRelacional -> <"); break;
        case 48: printf("48.	OpRelacional -> >="); break;
        case 49: printf("49.	OpRelacional -> <="); break;
        case 50: printf("50.	OpRelacional -> =="); break;
        case 51: printf("51.	OpRelacional -> !="); break;
        case 52: printf("52.	OpLogico -> AND"); break;
        case 53: printf("53.	OpLogico -> OR"); break;
        case 54: printf("54.	OpPon -> ^"); break;
        case 55: printf("55.	Numero -> NumeroEntero"); break;
        case 56: printf("56.	Numero -> NumeroReal"); break;
        case 57: printf("57.	Instruccion -> SIMBOLO_TERMINAL_Select"); break;
        case 58: printf("58. 	InstruccionSelect -> Select ID = Expresion"); break;
    }
    printf("\n");
}

void SustituyeNTenStackPorParteDerechaDeLaRegla(int intNumReglaObtenidaDeMR)
{
    /*Saca el NT arriba del stack*/
    popLL();
    /*Insertar los simbolos de la parte derecha de la regla en orden inverso en el stack*/
    switch(intNumReglaObtenidaDeMR)
    {
        case 1: /*1.	S -> programa InstruccionCompuesta*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_InstruccionCompuesta);
            pushLL_T(SIMBOLO_TERMINAL_PROGRAMA);
            break;
        case 2: /*2.	InstruccionCompuesta -> { BloqueInstrucciones } */
            pushLL_T(SIMBOLO_TERMINAL_CierraLlave);
            pushLL_NT(SIMBOLO_NO_TERMINAL_BloqueInstrucciones);
            pushLL_T(SIMBOLO_TERMINAL_AbreLlave);
            break;
        case 3: /*3.	BloqueInstrucciones -> Instruccion BloqueInstrucciones2 */
            pushLL_NT(SIMBOLO_NO_TERMINAL_BloqueInstrucciones2);
            pushLL_NT(SIMBOLO_NO_TERMINAL_Instruccion);
            break;
        case 4: /*4.	BloqueInstrucciones2 -> ; Instruccion BloqueInstrucciones2*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_BloqueInstrucciones2);
            pushLL_NT(SIMBOLO_NO_TERMINAL_Instruccion);
            pushLL_T(SIMBOLO_TERMINAL_PuntoYComa);
            break;
        case 5: /*5.	BloqueInstrucciones2 -> epsilon*/
            break;
        case 6: /*6.	Instruccion -> InstruccionAsignacion*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_InstruccionAsignacion);
            break;
        case 7: /*7.	Instruccion -> InstruccionIf*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_InstruccionIf);
            break;
        case 8: /*8.	Instruccion -> InstruccionWhile*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_InstruccionWhile);
            break;
        case 9: /*9.	Instruccion -> InstruccionImprime*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_InstruccionImprime);
            break;
        case 10: /*10.	Instruccion -> InstruccionCompuesta*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_InstruccionCompuesta);
            break;
        case 11: /*11.	Instruccion -> InstruccionFor*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_InstruccionFor);
            break;
        case 12: /*12.	Instruccion -> InstruccionBreak*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_InstruccionBreak);
            break;
        case 13: /*13.	Instruccion -> InstruccionFor*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_InstruccionDo);
            break;
        case 14: /*14.	InstruccionAsignacion -> ID = Expresion*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_Expresion);
            pushLL_T(SIMBOLO_TERMINAL_Igual);
            pushLL_T(SIMBOLO_TERMINAL_ID);

            break;
        case 15: /*15.	InstruccionIf -> if ( Expresion ) Instruccion InstruccionIf2*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_InstruccionIf2);
            pushLL_NT(SIMBOLO_NO_TERMINAL_Instruccion);
            pushLL_T(SIMBOLO_TERMINAL_CierraParentesis);
            pushLL_NT(SIMBOLO_NO_TERMINAL_Expresion);
            pushLL_T(SIMBOLO_TERMINAL_AbreParentesis);
            pushLL_T(SIMBOLO_TERMINAL_If);
            break;
        case 16: /*16.	InstruccionIf2 -> else Instrucción*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_Instruccion);
            pushLL_T(SIMBOLO_TERMINAL_Else);
            break;
        case 17: /*17.	Instruccionif2 -> epsilon*/
            break;
        case 18: /*18.	InstruccionWhile -> while ( Expresion ) Instruccion*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_Instruccion);
            pushLL_T(SIMBOLO_TERMINAL_PuntoYComa);
            pushLL_T(SIMBOLO_TERMINAL_CierraParentesis);
            pushLL_NT(SIMBOLO_NO_TERMINAL_Expresion);
            pushLL_T(SIMBOLO_TERMINAL_AbreParentesis);
            pushLL_T(SIMBOLO_TERMINAL_While);
            break;
        case 19: /*19.	InstruccionImprime -> ? Expresion*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_Expresion);
            pushLL_T(SIMBOLO_TERMINAL_Interrogacion);
            break;
        case 20: /*20.	InstruccionFor -> for ( InstruccionAsignacion ; Expresion ; Expresion ) { BloqueInstrucciones }*/
            pushLL_T(SIMBOLO_TERMINAL_CierraLlave);
            pushLL_NT(SIMBOLO_NO_TERMINAL_BloqueInstrucciones);
            pushLL_T(SIMBOLO_TERMINAL_AbreLlave);
            pushLL_T(SIMBOLO_TERMINAL_CierraParentesis);
            pushLL_NT(SIMBOLO_NO_TERMINAL_Expresion);
            pushLL_T(SIMBOLO_TERMINAL_PuntoYComa);
            pushLL_NT(SIMBOLO_NO_TERMINAL_Expresion);
            pushLL_T(SIMBOLO_TERMINAL_PuntoYComa);
            pushLL_NT(SIMBOLO_NO_TERMINAL_InstruccionAsignacion);
            pushLL_T(SIMBOLO_TERMINAL_AbreParentesis);
            pushLL_T(SIMBOLO_TERMINAL_For);
            break;
        case 21: /*21.	InstruccionBreak -> break ;*/
            pushLL_T(SIMBOLO_TERMINAL_PuntoYComa);
            pushLL_T(SIMBOLO_TERMINAL_Break);
            break;
        case 22: /*22.	InstruccionFor -> for ( InstruccionAsignacion ; Expresion ; Expresion ) { BloqueInstrucciones } pushLL_T(SIMBOLO_TERMINAL_CierraLlave);*/
            pushLL_T(SIMBOLO_TERMINAL_PuntoYComa);
            pushLL_T(SIMBOLO_TERMINAL_CierraParentesis);
            pushLL_NT(SIMBOLO_NO_TERMINAL_Expresion);
            pushLL_T(SIMBOLO_TERMINAL_AbreParentesis);
            pushLL_T(SIMBOLO_TERMINAL_While);
            pushLL_T(SIMBOLO_TERMINAL_CierraLlave);
            pushLL_T(SIMBOLO_TERMINAL_PuntoYComa);
            pushLL_NT(SIMBOLO_NO_TERMINAL_InstruccionAsignacion);
            pushLL_T(SIMBOLO_TERMINAL_AbreLlave);
            pushLL_T(SIMBOLO_TERMINAL_DO);
            break;
        case 23: /*23.	Expresion -> ExpRelacional Expresion2*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_Expresion2);
            pushLL_NT(SIMBOLO_NO_TERMINAL_ExpRelacional);
            break;
        case 24: /*24.	Expresion2 -> OpLogico ExpRelacional Expresion2*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_Expresion2);
            pushLL_NT(SIMBOLO_NO_TERMINAL_ExpRelacional);
            pushLL_NT(SIMBOLO_NO_TERMINAL_OpLogico);
            break;
        case 25: /*25.	Expresion2 -> epsilon*/
            break;
        case 26: /*26.	ExpRelacional -> ExpCompuesta ExpRelacional2*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_ExpRelacional2);
            pushLL_NT(SIMBOLO_NO_TERMINAL_ExpCompuesta);
            break;
        case 27: /*27.	ExpRelacional2 -> OpRelacional ExpCompuesta ExpRelacional2*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_ExpRelacional2);
            pushLL_NT(SIMBOLO_NO_TERMINAL_ExpCompuesta);
            pushLL_NT(SIMBOLO_NO_TERMINAL_OpRelacional);
            break;
        case 28: /*28.	ExpRelacional2 -> epsilon*/
            break;
        case 29: /*29.	ExpCompuesta -> ExpSimple ExpCompuesta2*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_ExpCompuesta2);
            pushLL_NT(SIMBOLO_NO_TERMINAL_ExpSimple);
            break;
        case 30: /*30.	ExpCompuesta2 -> OpAditivo ExpSimple ExpCompuesta2*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_ExpCompuesta2);
            pushLL_NT(SIMBOLO_NO_TERMINAL_ExpSimple);
            pushLL_NT(SIMBOLO_NO_TERMINAL_OpAditivo);
            break;
        case 31: /*31.	ExpCompuesta2 -> epsilon*/
            break;
        case 32: /*32.	ExpSimple -> Factor ExpSimple2*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_ExpSimple2);
            pushLL_NT(SIMBOLO_NO_TERMINAL_Factor);
            break;
        case 33: /*33.	ExpSimple2 -> OpMultiplicativo Factor ExpSimple2*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_ExpSimple2);
            pushLL_NT(SIMBOLO_NO_TERMINAL_Factor);
            pushLL_NT(SIMBOLO_NO_TERMINAL_OpMultiplicativo);
            break;
        case 34: /*34.	ExpSimple2 -> epsilon*/
            break;
        case 35: /*35.	Factor -> Termino Factor2*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_Factor2);
            pushLL_NT(SIMBOLO_NO_TERMINAL_Termino);
            break;
        case 36: /*36.	Factor2 -> OpPon Termino*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_Termino);
            pushLL_NT(SIMBOLO_NO_TERMINAL_OpPon);
            break;
        case 37: /*37.	Factor2 -> epsilon*/
            break;
        case 38: /*38.	Termino -> Numero*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_Numero);
            break;
        case 39: /*39.	Termino -> ID*/
            pushLL_T(SIMBOLO_TERMINAL_ID);
            break;
        case 40: /*40.	Termino -> ( Expresion )*/
            pushLL_T(SIMBOLO_TERMINAL_CierraParentesis);
            pushLL_NT(SIMBOLO_NO_TERMINAL_Expresion);
            pushLL_T(SIMBOLO_TERMINAL_AbreParentesis);
            break;
        case 41: /*41.	Termino -> ! ( Expresion )*/
            pushLL_T(SIMBOLO_TERMINAL_CierraParentesis);
            pushLL_NT(SIMBOLO_NO_TERMINAL_Expresion);
            pushLL_T(SIMBOLO_TERMINAL_AbreParentesis);
            pushLL_T(SIMBOLO_TERMINAL_Exclamacion);
            break;
        case 42: /*42.	OpAditivo -> + */
            pushLL_T(SIMBOLO_TERMINAL_Mas);
            break;
        case 43: /*43.	OpAditivo -> - */
            pushLL_T(SIMBOLO_TERMINAL_Menos);
            break;
        case 44: /*44.	OpMultiplicativo -> * */
            pushLL_T(SIMBOLO_TERMINAL_Asterisco);
            break;
        case 45: /*45.	OpMultiplicativo -> / */
            pushLL_T(SIMBOLO_TERMINAL_Diagonal);
            break;
        case 46: /*46.	OpRelacional -> > */
            pushLL_T(SIMBOLO_TERMINAL_MayorQue);
            break;
        case 47: /*47.	OpRelacional -> < */
            pushLL_T(SIMBOLO_TERMINAL_MenorQue);
            break;
        case 48: /*48.	OpRelacional -> >= */
            pushLL_T(SIMBOLO_TERMINAL_MayorIgual);
            break;
        case 49: /*49.	OpRelacional -> <= */
            pushLL_T(SIMBOLO_TERMINAL_MenorIgual);
            break;
        case 50: /*50.	OpRelacional -> == */
            pushLL_T(SIMBOLO_TERMINAL_Identico);
            break;
        case 51: /*51.	OpRelacional -> !=*/
            pushLL_T(SIMBOLO_TERMINAL_Diferente);
            break;
        case 52: /*52.	OpLogico -> AND */
            pushLL_T(SIMBOLO_TERMINAL_And);
            break;
        case 53: /*53.	OpLogico -> OR */
            pushLL_T(SIMBOLO_TERMINAL_Or);
            break;
        case 54: /*54.	OpPon -> ^ */
            pushLL_T(SIMBOLO_TERMINAL_Potencia);
            break;
        case 55: /*55.	Numero -> NumeroEntero */
            pushLL_T(SIMBOLO_TERMINAL_NumEnt);
            break;
        case 56: /*56.	Numero -> NumeroReal*/
            pushLL_T(SIMBOLO_TERMINAL_NumDec);
            break;
        case 57: /*57.	Instruccion -> InstruccionSelect*/
            pushLL_NT(SIMBOLO_NO_TERMINAL_InstruccionSelect);
            break;
        case 58: /*57.	InstruccionSelect -> Select ID = Expresion ;*/
            pushLL_T(SIMBOLO_TERMINAL_PuntoYComa);
            pushLL_NT(SIMBOLO_NO_TERMINAL_Expresion);
            pushLL_T(SIMBOLO_TERMINAL_Igual);
            pushLL_T(SIMBOLO_TERMINAL_ID);
            pushLL_T(SIMBOLO_TERMINAL_Select);
            break;
    }/*switch*/

}/*SustituyeNTenStackPorParteDerechaDeLaRegla*/

int parser_LL()
{
    int bolBanderaErrorSintactico = FALSE;
    int bolBanderaEntradaReconocida = FALSE;
    /*Inicializa el apuntador de recorrido de la cadena de entrada*/
    ptrCurrentToken = ptrTokenList;

    /*Condiciones iniciales del Stack*/
    pushLL_T(SIMBOLO_TERMINAL_EOF);
    pushLL_NT(SIMBOLO_NO_TERMINAL_S);

    do
    {
       printf("======================================\n");
       stack_imprime();
       printf("--------------------------------------\n");
       imprime_entrada();
       printf("--------------------------------------\n\n\n\n");
       /*Si lo que esta arriba del stack es un No Terminal*/
       if(stack_top_es_NT())
       {
        /*Aplicar regla gramatical*/
            bolBanderaErrorSintactico = Parser_LL_AplicarRegla();
            if(bolBanderaErrorSintactico == TRUE)
            {
                printf("Error Sintactico Token %d = %s, Renglon = %d, Columna = %d\n",
                   ptrCurrentToken->intTokenCodigo,
                   ptrCurrentToken->strTokenTextoFuente,
                   ptrCurrentToken->intReglon,
                   ptrCurrentToken->intColumna);
            }/*if*/
       }/*if*/
       else/*Si lo que esta arriba del stack es un Terminal*/
       {
            /*Si el stack está vacio y la entrada no está vacia*/
            if((ptrStackLLTop != NULL) && (ptrCurrentToken != NULL))
            {
                /*Si el Top del Stack y la entrada son los mismos terminales*/
                if((ptrStackLLTop->intSimboloCodigo == ptrCurrentToken->intTokenCodigo))
                {
                    /*Entrada Reconocida = % arriba stack y % en la entrada*/
                    if(ptrStackLLTop->intSimboloCodigo == SIMBOLO_TERMINAL_EOF)
                    {
                        printf("ACEPTAR\n");
                        bolBanderaEntradaReconocida = TRUE;
                        printf("\nEntrada Reconocida.\nAnalisis Sintatico Correcto\n\n");
                    }/*if*/
                    else /*Expect: Terminal arriba del Stack = Terminal enviado por Scanner*/
                    {
                        printf("EXPECT()\n");
                        popLL();
                        ptrCurrentToken = ptrCurrentToken->ptrSig;
                    }/*else*/
                }/*if*/
                else /*El Top del Stack y la Entrada son diferentes Terminales*/
                {   /* => Error sintático*/
                    bolBanderaErrorSintactico = TRUE;
                    printf("Error Sintactico Token %d = %s, Renglon = %d, Columna = %d\n",
                   ptrCurrentToken->intTokenCodigo,
                   ptrCurrentToken->strTokenTextoFuente,
                   ptrCurrentToken->intReglon,
                   ptrCurrentToken->intColumna);
                }/*else*/
            }/*if*/
            else /*El stack o la entrada está vacia*/
            {
                bolBanderaErrorSintactico = TRUE;
                if(ptrStackLLTop == NULL)
                {
                    printf("La Pila de Reconocimiento esta vacia\n");
                }/*if*/
                else if (ptrCurrentToken == NULL)
                {
                    printf("Ya no existen tokens de entrada desde el Scanner\n");
                }/*else if*/
            }/*else*/
       }/*else*/

    }while((!bolBanderaErrorSintactico) && (!bolBanderaEntradaReconocida));

    vaciar_StackLL();
    return(bolBanderaErrorSintactico);

}/*parser_LL*/

