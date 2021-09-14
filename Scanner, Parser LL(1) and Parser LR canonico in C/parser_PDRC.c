//parser_PDRC.c
#include <stdio.h>
#include <stdlib.h>

#define TRUE -1
#define FALSE 0

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

#define SIMBOLO_NO_TERMINAL_S 1
#define SIMBOLO_NO_TERMINAL_IntruccionCompuesta 2
#define SIMBOLO_NO_TERMINAL_BloqueInstrucciones 3
#define SIMBOLO_NO_TERMINAL_Instruccion 4
#define SIMBOLO_NO_TERMINAL_InstruccionAsignacion 5
#define SIMBOLO_NO_TERMINAL_InstruccionIf 6
#define SIMBOLO_NO_TERMINAL_InstruccionWhile 7
#define SIMBOLO_NO_TERMINAL_InstruccionImprime 8
#define SIMBOLO_NO_TERMINAL_Expresion 9
#define SIMBOLO_NO_TERMINAL_ExpRelacional 10
#define SIMBOLO_NO_TERMINAL_ExpCompuesta 11
#define SIMBOLO_NO_TERMINAL_ExpSimple 12
#define SIMBOLO_NO_TERMINAL_Factor 13
#define SIMBOLO_NO_TERMINAL_Termino 14
#define SIMBOLO_NO_TERMINAL_OpAditivo 15
#define SIMBOLO_NO_TERMINAL_OpMultiplicativo 16
#define SIMBOLO_NO_TERMINAL_OpRelacional 17
#define SIMBOLO_NO_TERMINAL_OpLogico 18
#define SIMBOLO_NO_TERMINAL_OpPon 19
#define SIMBOLO_NO_TERMINAL_Numero 20
#define SIMBOLO_NO_TERMINAL_InstruccionFor 21
#define SIMBOLO_NO_TERMINAL_InstruccionBreak 22
#define SIMBOLO_NO_TERMINAL_InstruccionDo 23
#define SIMBOLO_NO_TERMINAL_Numero 30
#define SIMBOLO_NO_TERMINAL_InstruccionSelect 31


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
int     bolPDRCError = FALSE;

int CurrentToken(int intSimboloT)
{
    if(ptrCurrentToken->intTokenCodigo == intSimboloT)
    {
        return TRUE;
    }else{
        return FALSE;
    }/*else*/
}/*CurrentToken*/

void Expect(int intSimboloT)
{
    if(CurrentToken(intSimboloT))
    {/*Token Actual esta en la posición correcta de acuerdo a la gramática*/
        printf("Token Correcto: [%s], Renglon: %d, Columna: %d\n",
               ptrCurrentToken->strTokenTextoFuente,
               ptrCurrentToken->intReglon,
               ptrCurrentToken->intColumna);
        ptrCurrentToken = ptrCurrentToken->ptrSig;
    }else{/*Hay un error sintático*/
          printf("Error sintactico Token: [%s], Renglon: %d, Columna: %d\n",
               ptrCurrentToken->strTokenTextoFuente,
               ptrCurrentToken->intReglon,
               ptrCurrentToken->intColumna);
            bolPDRCError=TRUE;
    }/*ELSE*/

}/*Expect*/

int CurrentTokenInFirst(int intSimboloNT)
{
    int bolRes = FALSE;
    /*if(!bolPDRCError)*/
    /*{*/
        switch(intSimboloNT)
        {
            case SIMBOLO_NO_TERMINAL_S:
                if(CurrentToken(SIMBOLO_TERMINAL_PROGRAMA)) {bolRes=TRUE; break;}
                    break;/*end SIMBOLO_NO_TERMINAL_S*/

            case SIMBOLO_NO_TERMINAL_IntruccionCompuesta:
                if(CurrentToken(SIMBOLO_TERMINAL_AbreParentesis)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_CierraParentesis)) {bolRes=TRUE; break;}
                    break;/*end SIMBOLO_NO_TERMINAL_IntruccionCompuesta*/

            case SIMBOLO_NO_TERMINAL_BloqueInstrucciones:
                if(CurrentToken(SIMBOLO_TERMINAL_Igual)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_If)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_While)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_For)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_Break)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_DO)) {bolRes=TRUE; break;}
                    break;/*end SIMBOLO_NO_TERMINAL_BloqueInstrucciones*/

            case SIMBOLO_NO_TERMINAL_Instruccion:
                if(CurrentToken(SIMBOLO_TERMINAL_Igual)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_If)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_While)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_For)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_Break)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_DO)) {bolRes=TRUE; break;}

                    break;/*end SIMBOLO_NO_TERMINAL_Instruccion*/

            case SIMBOLO_NO_TERMINAL_InstruccionAsignacion:
                if(CurrentToken(SIMBOLO_TERMINAL_ID)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_Igual)) {bolRes=TRUE; break;}
                    break;/*end SIMBOLO_NO_TERMINAL_InstruccionAsignacion*/

            case SIMBOLO_NO_TERMINAL_InstruccionIf:
                if(CurrentToken(SIMBOLO_TERMINAL_If)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_AbreParentesis)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_CierraParentesis)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_Else)) {bolRes=TRUE; break;}
                    break;/*end SIMBOLO_NO_TERMINAL_InstruccionIf*/

            case SIMBOLO_NO_TERMINAL_InstruccionWhile:
                if(CurrentToken(SIMBOLO_TERMINAL_While)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_AbreParentesis)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_CierraParentesis)) {bolRes=TRUE; break;}
                    break;/*end SIMBOLO_NO_TERMINAL_InstruccionWhile*/

            case SIMBOLO_NO_TERMINAL_InstruccionImprime:
                if(CurrentToken(SIMBOLO_TERMINAL_Interrogacion)) {bolRes=TRUE; break;}
                    break;/*end SIMBOLO_NO_TERMINAL_InstruccionImprime*/

            case SIMBOLO_NO_TERMINAL_Expresion:
                if(CurrentToken(SIMBOLO_TERMINAL_And)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_Or)) {bolRes=TRUE; break;}
                    break;/*end SIMBOLO_NO_TERMINAL_Expresion*/

            case SIMBOLO_NO_TERMINAL_ExpRelacional:
                if(CurrentToken(SIMBOLO_TERMINAL_MayorQue)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_MenorQue)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_MayorIgual)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_MenorIgual)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_Identico)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_Diferente)) {bolRes=TRUE; break;}
                    break;/*end SIMBOLO_NO_TERMINAL_ExpRelacional*/

            case SIMBOLO_NO_TERMINAL_ExpCompuesta:
                if(CurrentToken(SIMBOLO_TERMINAL_Mas)); {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_Menos)) {bolRes=TRUE; break;}
                    break;/*end SIMBOLO_NO_TERMINAL_ExpCompuesta*/

            case SIMBOLO_NO_TERMINAL_ExpSimple:
                if(SIMBOLO_TERMINAL_Asterisco); {bolRes=TRUE; break;}
                    break;/*end SIMBOLO_NO_TERMINAL_ExpSimple*/

            case SIMBOLO_NO_TERMINAL_Termino:
                if(CurrentToken(SIMBOLO_TERMINAL_NumEnt)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_NumDec)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_ID)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_AbreParentesis)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_CierraParentesis)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_Exclamacion)) {bolRes=TRUE; break;}
                    break;/*end SIMBOLO_NO_TERMINAL_Termino*/

            case SIMBOLO_NO_TERMINAL_OpAditivo:
                if(CurrentToken(SIMBOLO_TERMINAL_Mas)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_Menos)) {bolRes=TRUE; break;}
                    break;/*end SIMBOLO_NO_TERMINAL_OpAditivo*/

            case SIMBOLO_NO_TERMINAL_OpMultiplicativo:
                if(CurrentToken(SIMBOLO_TERMINAL_Asterisco)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_Diagonal)) {bolRes=TRUE; break;}
                    break;/*end SIMBOLO_NO_TERMINAL_OpMultiplicativo*/

            case SIMBOLO_NO_TERMINAL_OpRelacional:
                if(CurrentToken(SIMBOLO_TERMINAL_MayorQue)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_MenorQue)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_MayorIgual)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_MenorIgual)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_Identico)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_Diferente)) {bolRes=TRUE; break;}
                    break;/*end SIMBOLO_NO_TERMINAL_OpRelacional*/

            case SIMBOLO_NO_TERMINAL_OpLogico:
                if(CurrentToken(SIMBOLO_TERMINAL_And)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_Or)) {bolRes=TRUE; break;}
                    break;/*end SIMBOLO_NO_TERMINAL_OpLogico*/

            case SIMBOLO_NO_TERMINAL_OpPon:
                if(CurrentToken(SIMBOLO_TERMINAL_Potencia)) {bolRes=TRUE; break;}
                break;/*end SIMBOLO_NO_TERMINAL_OpPon*/

            case SIMBOLO_NO_TERMINAL_Numero:
                if(CurrentToken(SIMBOLO_TERMINAL_NumEnt)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_NumDec)) {bolRes=TRUE; break;}
                    break;/*end SIMBOLO_NO_TERMINAL_Numero*/

            case SIMBOLO_NO_TERMINAL_InstruccionFor:
                if(CurrentToken(SIMBOLO_TERMINAL_For)) {bolRes=TRUE; break;}
                break;/*end SIMBOLO_TERMINAL_Etiqueta_FOR*/

            case SIMBOLO_NO_TERMINAL_InstruccionBreak:
                if(CurrentToken(SIMBOLO_TERMINAL_Break)) {bolRes=TRUE; break;}
                if(CurrentToken(SIMBOLO_TERMINAL_PuntoYComa)) {bolRes=TRUE; break;}
                break;/*end SIMBOLO_TERMINAL_Etiqueta_BREAK*/
            case SIMBOLO_NO_TERMINAL_InstruccionDo:
                if(CurrentToken(SIMBOLO_TERMINAL_DO)) {bolRes=TRUE; break;}
                break;/*end SIMBOLO_TERMINAL_Etiqueta_FOR*/

        }/*switch*/

    /*}*/
    return bolRes;
}/*end CurrentTokenInFirst*/

void s ();
void InstruccionCompuesta();
void BloqueInstrucciones();
void Instruccion();
void InstruccionAsignacion();
void InstruccionIf();
void InstruccionWhile();
void InstruccionImprime();
void Expresion();
void ExpRelacional();
void ExpCompuesta();
void ExpSimple();
void Factor();
void Termino();
void OpAditivo();
void OpMultiplicativo();
void OpRelacional();
void OpLogico();
void OpPon();
void Numero();
void InstruccionFor();
void InstruccionBreak();
void InstruccionDo();


/*S ::= "programa" InstruccionCompuesta*/
void s ()
{
        Expect(SIMBOLO_TERMINAL_PROGRAMA);
        InstruccionCompuesta();
        /*Expect(SIMBOLO_TERMINAL_FinalDeArchivo);*/
}/* end s */

/*InstruccionCompuesta ::= "{" BloqueInstrucciones "}"*/
void InstruccionCompuesta()
{
    if(!bolPDRCError) {
        Expect(SIMBOLO_TERMINAL_AbreLlave);
        BloqueInstrucciones();
        Expect(SIMBOLO_TERMINAL_CierraLlave);
    }
}/* end InstruccionCompuesta*/

/*BloqueInstrucciones ::= Instruccion { ";" Instruccion } */
void BloqueInstrucciones() /*Duda */
{
    if(!bolPDRCError) {
        Instruccion();
        while (CurrentToken(SIMBOLO_TERMINAL_PuntoYComa))
        {
            Expect(SIMBOLO_TERMINAL_PuntoYComa);
            Instruccion();
        }/*end Intruccion*/
    }

} /*end BloqueInstrucciones*/

/*Instruccion ::= InstruccionAsignacion | InstruccionIf | InstruccionWhile | InstruccionImprime | InstruccionCompuesta*/
void Instruccion()
{
    if(!bolPDRCError) {
        if(CurrentTokenInFirst(SIMBOLO_NO_TERMINAL_InstruccionAsignacion))
        {
            InstruccionAsignacion();
        }/*end if*/
        else if (CurrentTokenInFirst(SIMBOLO_NO_TERMINAL_InstruccionIf))
        {
            InstruccionIf();
        }/*end else if*/
        else if(CurrentTokenInFirst(SIMBOLO_NO_TERMINAL_InstruccionWhile))
        {
            InstruccionWhile();
        }/*end else if*/
        else if (CurrentTokenInFirst(SIMBOLO_NO_TERMINAL_InstruccionImprime))
        {
            InstruccionImprime();
        }/*end else if*/
        else if (CurrentTokenInFirst(SIMBOLO_NO_TERMINAL_IntruccionCompuesta))
        {
            InstruccionCompuesta();
        }/* end else*/
        else if (CurrentTokenInFirst(SIMBOLO_NO_TERMINAL_InstruccionFor))
        {
            InstruccionFor();
        }
        else if (CurrentTokenInFirst(SIMBOLO_NO_TERMINAL_InstruccionBreak))
        {
            InstruccionBreak();
        }else if (CurrentTokenInFirst(SIMBOLO_NO_TERMINAL_InstruccionDo))
        {
            InstruccionDo();
        }


    }
}/* end Instruccion*/

/*InstruccionAsignacion ::= ID "=" Expresion*/
void InstruccionAsignacion()
{
    if(!bolPDRCError) {
        Expect(SIMBOLO_TERMINAL_ID);
        Expect(SIMBOLO_TERMINAL_Igual);
        Expresion();
    }
}/* end InstruccionAsignacion*/

/*InstruccionIf ::= "if" "("  Expresion ")" Instruccion [ "else" Instruccion ]*/
void InstruccionIf()
{
    if(!bolPDRCError) {
        Expect(SIMBOLO_TERMINAL_If);
        Expect(SIMBOLO_TERMINAL_AbreParentesis);
        Expresion();
        Expect(SIMBOLO_TERMINAL_CierraParentesis);
        Instruccion();
        if (CurrentToken(SIMBOLO_TERMINAL_Else))
        {
            Expect(SIMBOLO_TERMINAL_Else);
            Instruccion();
        }
    }

}/*end InstruccionIf*/

/*InstruccionWhile ::= "while" "(" Expresion ")" Instruccion*/
void InstruccionWhile()
{
    if(!bolPDRCError) {
        Expect(SIMBOLO_TERMINAL_While);
        Expect(SIMBOLO_TERMINAL_AbreParentesis);
        Expresion();
        Expect(SIMBOLO_TERMINAL_CierraParentesis);
        Instruccion();
    }
}/*end InstruccionWhile*/

/*InstruccionImprime ::= "?" Expresion*/
void InstruccionImprime()
{
    if(!bolPDRCError) {
        Expect(SIMBOLO_TERMINAL_Interrogacion);
        Expresion();
    }
}/*end InstruccionImprime*/

/*Expresion ::= ExpRelacional { OpLogico ExpRelacional } */
void Expresion()
{
    if(!bolPDRCError) {
        ExpRelacional();
        while (CurrentTokenInFirst(SIMBOLO_NO_TERMINAL_OpLogico))
        {
            OpLogico();
            ExpRelacional();
        }
    }

}/*end Expresion*/

/*ExpRelacional ::= ExpCompuesta { OpRelacional ExpCompuesta }*/
void ExpRelacional()
{
    if(!bolPDRCError) {
        ExpCompuesta();
        while (CurrentTokenInFirst(SIMBOLO_NO_TERMINAL_OpRelacional))
        {
          OpRelacional();
          ExpCompuesta();
        }
    }
}/*end ExpRelacional*/

/*ExpCompuesta ::= ExpSimple { OpAditivo ExpSimple } */
void ExpCompuesta()
{
    if(!bolPDRCError) {
        ExpSimple();
        while (CurrentTokenInFirst(SIMBOLO_NO_TERMINAL_OpAditivo))
        {
            OpAditivo();
            ExpSimple();
        }
    }

}/*end ExpCompuesta*/

/*ExpSimple ::= Factor { OpMultiplicativo Factor }*/
void ExpSimple()
{
    if(!bolPDRCError) {
        Factor();
        while (CurrentTokenInFirst(SIMBOLO_NO_TERMINAL_OpMultiplicativo))
        {
            OpMultiplicativo();
            Factor();
        }/*end while*/
    }
}/* end ExpSimple*/

/*Factor ::= Termino [ OpPon Termino ] */
void Factor()
{
    if(!bolPDRCError) {
        Termino();
        if(CurrentTokenInFirst(SIMBOLO_NO_TERMINAL_OpPon))
        {
            OpPon();
            Termino();
        }
    }

}/*end Factor*/

/*Termino ::= Numero | ID | "(" Expresion ")" | "!" "(" Expresion ")" */
void Termino()
{
    if(!bolPDRCError) {
        if (CurrentTokenInFirst(SIMBOLO_NO_TERMINAL_Numero))
        {
            Numero();
        }/*end if*/
        else if(CurrentToken(SIMBOLO_TERMINAL_ID))
        {
            Expect(SIMBOLO_TERMINAL_ID);
        }/*end else if*/
        else if (CurrentToken(SIMBOLO_TERMINAL_AbreParentesis))
        {
            Expect(SIMBOLO_TERMINAL_AbreParentesis);
            Expresion();
            Expect(SIMBOLO_TERMINAL_CierraParentesis);
        }/*end else if*/
        else
        {
            Expect(SIMBOLO_TERMINAL_Exclamacion);
            Expect(SIMBOLO_TERMINAL_AbreParentesis);
            Expresion();
            Expect(SIMBOLO_TERMINAL_CierraParentesis);
        }/*end else*/
    }
}/*end Termino*/

/*OpAditivo ::= "+" | "-" */
void OpAditivo()
{
    if(!bolPDRCError) {
        if (CurrentToken(SIMBOLO_TERMINAL_Mas))
        {
            Expect(SIMBOLO_TERMINAL_Mas);
        }/*end if*/
        else
        {
            Expect(SIMBOLO_TERMINAL_Menos);
        }/*end else*/
    }
}/*OpAditivo*/

/*OpMultiplicativo ::= "*" | "/"*/
void OpMultiplicativo()
{
    if(!bolPDRCError) {
        if (CurrentToken(SIMBOLO_TERMINAL_Asterisco))
        {
            Expect(SIMBOLO_TERMINAL_Asterisco);
        }/*end if*/
        else
        {
            Expect(SIMBOLO_TERMINAL_Diagonal);
        }/*end else*/
    }
}/*end OpMultiplicativo*/

/*OpRelacional ::= ">" | "<" | ">=" | "<=" | "==" | "!="*/
void OpRelacional()
{
    if(!bolPDRCError) {
        if(CurrentToken(SIMBOLO_TERMINAL_MayorQue))
        {
            Expect(SIMBOLO_TERMINAL_MayorQue);
        }/*end if*/
        else if (CurrentToken(SIMBOLO_TERMINAL_MenorQue))
        {
            Expect(SIMBOLO_TERMINAL_MenorQue);
        }/*end else if*/
        else if (CurrentToken(SIMBOLO_TERMINAL_MayorIgual))
        {
            Expect(SIMBOLO_TERMINAL_MayorIgual);
        }/*end else if*/
        else if (CurrentToken(SIMBOLO_TERMINAL_MenorIgual))
        {
            Expect(SIMBOLO_TERMINAL_MenorIgual);
        }/*end else if*/
        else if (CurrentToken(SIMBOLO_TERMINAL_Identico))
        {
            Expect(CurrentToken(SIMBOLO_TERMINAL_Identico));
        }/*end else if*/
        else
        {
            Expect(CurrentToken(SIMBOLO_TERMINAL_Diferente));
        }/*end else*/
    }
}/*OpRelacional*/

/*OpLogico ::= "AND" | "OR" */
void OpLogico()
{
    if(!bolPDRCError) {
        if (CurrentToken(SIMBOLO_TERMINAL_And))
        {
            Expect(SIMBOLO_TERMINAL_And);
        }/*end if*/
        else
        {
            Expect(SIMBOLO_TERMINAL_Or);
        }/*end else*/
    }
}/*end OpLogico*/

/*OpPon ::= "^"*/
void OpPon()
{
    if(!bolPDRCError) {
        Expect(SIMBOLO_TERMINAL_Potencia);
    }
}/*end OpPon*/

/*Numero ::= NumeroEntero | NumeroReal*/
void Numero()
{
    if(!bolPDRCError) {
        if (CurrentToken(SIMBOLO_TERMINAL_NumEnt))
        {
            Expect(SIMBOLO_TERMINAL_NumEnt);
        }/*end if*/
        else
        {
            Expect(SIMBOLO_TERMINAL_NumDec);
        }/*end else*/
    }
}/*end Numero*/

/*InstruccionFor::= "for" "(" InstrAsignacion ";" expresion ";" expresion ")" "{" BloqueInstrucciones "}"*/
void InstruccionFor()
{
    Expect(SIMBOLO_TERMINAL_For);
    Expect(SIMBOLO_TERMINAL_AbreParentesis);
    InstruccionAsignacion();
    Expect(SIMBOLO_TERMINAL_PuntoYComa);
    Expresion();
    Expect(SIMBOLO_TERMINAL_PuntoYComa);
    Expresion();
    Expect(SIMBOLO_TERMINAL_CierraParentesis);
    Expect(SIMBOLO_TERMINAL_AbreLlave);
    BloqueInstrucciones();
    Expect(SIMBOLO_TERMINAL_CierraLlave);
}

/*InstruccionBreak::= "break" ";"*/
void InstruccionBreak()
{
    Expect(SIMBOLO_TERMINAL_Break);
    Expect(SIMBOLO_TERMINAL_PuntoYComa);
}

void InstruccionDo()
{
    Expect(SIMBOLO_TERMINAL_DO);
    Expect(SIMBOLO_TERMINAL_AbreLlave);
    InstruccionAsignacion();
    Expect(SIMBOLO_TERMINAL_PuntoYComa);
    Expect(SIMBOLO_TERMINAL_CierraLlave);
}


//InstruccionSelect ::= Select ID = Expresion
void InstruccionSelect(){
    //Expect(SIMBOLO_TERMINAL_Select);
    InstruccionAsignacion();
}



int parser_PDRC()
{
    int bolRes = TRUE;
/*Se inicializa el token actual con la cabeza de la lista que envia el scanner*/
    ptrCurrentToken = ptrTokenList;

    s(); /*simbolo Inicial de la Gramática*/

    if(bolPDRCError)
        return FALSE; /*reconocimiento sintático incorrecto*/
    else
        printf("\n\nACEPTAR\n");
        printf("\nEntrada Reconocida.\nAnalisis Sintatico Correcto\n\n");
        return TRUE; /*reconocimiento sintático correcto*/

    return bolRes;
}/*parser_PDRC()*/
