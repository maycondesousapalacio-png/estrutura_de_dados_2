#ifndef TRANSACAO_H_INCLUDED
#define TRANSACAO_H_INCLUDED

struct Registro {
    char id[15];
    char data[15];
    char dia[15];
    char hora[15];
    char bandeira[25];
    char modoEntrada[10];
    float valor;
    char tipoTransacao[15];
    char categoria[35];
    char paisTransacao[30];
    char paisEntrega[30];
    char paisResidencia[30];
    char genero[5];
    char idade[10];
    char banco[25];
    int status;
};

struct Transacao {
    unsigned long id;
    char data[11];
    short dataInt;
    char hora[9];
    char bandeira[20];
    char categoria[30];
    float valor;
    int status;
};

#endif
