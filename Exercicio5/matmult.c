#include <stdio.h>
#include <stdlib.h>    /* exit, malloc, calloc, etc. */
#include <string.h>
#include <getopt.h>    /* getopt */
#include <unistd.h>    /* stdconf */

#if 0
#include <likwid.h>    /* LIKWID */
#endif

#include "matriz.h"

/**
 * Exibe mensagem de erro indicando forma de uso do programa e termina
 * o programa.
 */

static void usage(char *progname)
{
  fprintf(stderr, "Forma de uso: %s [ -n <ordem> ] \n", progname);
  exit(1);
}



/**
 * Programa principal
 * Forma de uso: matmult [ -n <ordem> ]
 * -n <ordem>: ordem da matriz quadrada e dos vetores
 *
 */

int main (int argc, char *argv[]) 
{
  int c, n=DEF_SIZE;
  
  MatPtr mPtr_1, mPtr_2, resMatPtr;
  MatRow mRow_1, mRow_2, resMatRow;
  Vetor vet, resPtr, resRow;
  
  /* =============== TRATAMENTO DE LINHA DE COMANDO =============== */

  char *opts = "n:";
  c = getopt (argc, argv, opts);
  
  while ( c != -1 ) {
    switch (c) {
    case 'n':  n = atoi(optarg);              break;
    default:   usage(argv[0]);
    }
      
    c = getopt (argc, argv, opts);
  }
  
  /* ================ FIM DO TRATAMENTO DE LINHA DE COMANDO ========= */
 
  srand(20202);
      
  resPtr = (double *) calloc (n, sizeof(double));
  resRow = (double *) calloc (n, sizeof(double));
  resMatPtr = geraMatPtr(n, n, 1);
  resMatRow = geraMatRow(n, n, 1);
    
  mPtr_1 = geraMatPtr (n, n, 0);
  mPtr_2 = geraMatPtr (n, n, 0);

  mRow_1 = geraMatRow (n, n, 0);
  mRow_2 = geraMatRow (n, n, 0);

  vet = geraVetor (n, 0);
    
#ifdef DEBUG
#if 0
    prnMatPtr (mPtr_1, n, n);
    prnMatPtr (mPtr_2, n, n);
#endif
    prnMatRow (mRow_1, n, n);
#if 0
    prnMatRow (mRow_2, n, n);
    prnVetor (vet, n);
#endif
    printf ("=================================\n\n");
#endif /* DEBUG */

  multMatRowVet_otimiz (mRow_1, vet, n, n, 4, resRow);
#if 0 
  multMatRowVet (mRow_1, vet, n, n, resRow);
  LIKWID_MARKER_INIT;

  LIKWID_MARKER_START("MatPtrVet");
  
  multMatPtrVet (mPtr_1, vet, n, n, resPtr);
  
  LIKWID_MARKER_STOP("MatPtrVet");

  LIKWID_MARKER_START("MatRowVet");

  multMatRowVet (mRow_1, vet, n, n, resRow);

  LIKWID_MARKER_STOP("MatRowVet");
    
  LIKWID_MARKER_START("MatMatPtr");

  multMatMatPtr (mPtr_1, mPtr_2, n, resMatPtr);

  LIKWID_MARKER_STOP("MatMatPtr");
    
  LIKWID_MARKER_START("MatMatRow");

  multMatMatRow (mRow_1, mRow_2, n, resMatRow);

  LIKWID_MARKER_STOP("MatMatRow");
    
  LIKWID_MARKER_CLOSE;
#endif
#ifdef DEBUG
#if 0
    prnVetor (resPtr, n);
#endif
    prnVetor (resRow, n);
#if 0
    prnMatRow (resMatRow, n, n);
    prnMatPtr (resMatPtr, n, n);
#endif
#endif /* DEBUG */

  liberaMatPtr (mPtr_1, n);
  liberaMatPtr (mPtr_2, n);
  liberaMatPtr (resMatPtr, n);
  liberaVetor ((void*)mRow_1);
  liberaVetor ((void*)mRow_2);
  liberaVetor ((void*)resMatRow);
  liberaVetor ((void*)vet);
    
  free(resRow);
  free(resPtr);

  return 0;
}

