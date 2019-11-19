#include <stdlib.h>

#include "rshmem.h"


void incrementa(int *mem, int k) {
	int i;
	i = *mem; TP
		i = i + k;  TP
		*mem = i;
}


int main(int argn, char **argv) {


	FILE *fsal;                   /*Puntero a fichero con salida de resultados*/

	char *marcaFin,               /*Puntero fin de zona de memoria compartida*/
		*c1,                     /*Variable de cerradura Proceso Padre*/
		*c2;                     /*Variable de cerradura Proceso Hijo*/
	int  *turno,                  /*Variable turno de entrada del proceso*/
		*recurso,                /*Puntero a zona de memoria compartida*/
		nIteraciones = 0;          /*Contador de iteracciones del proceso*/


   /* Comprobacion del numero de argumentos */

	if (argn != 3) {
		printf("Error en la entrada de argumentos/n");
		exit(1);
	}


	/*Apertura de ficheros*/

	if ((fsal = fopen(argv[2], "a+")) == NULL) {
		printf("Error de apertura en el fichero de salidan");
		exit(-1);
	}                /*Comprobacion de apertura correcta del fichero de texto de entrada*/

	nIteraciones = atoi(argv[1]);

	/* crear zona de memoria compartida */

	if (!crearMemoria())
		fprintf(stderr, "error de crearMemorian");


	recurso = (int *)memoria;
	turno = (int  *)recurso + sizeof(int);
	marcaFin = (char *)turno + sizeof(int);
	c1 = (char *)marcaFin + sizeof(char);
	c2 = (char *)c1 + sizeof(char);
	*recurso = 0;
	*marcaFin = 'p';
	*c1 = 'F';
	*c2 = 'F';


	if (0 != fork()) {                               /* Proceso Padre */

		int i;
		fprintf(fsal, "P1: SOY EL PROCESO PADREn");

		for (i = 0; i < nIteraciones; i++) {

			*c1 = 'T';                                /* Seccion */
			*turno = 2;                                     /*  de  */
			while (((*c2) == 'T') && ((*turno) == 2));           /*  entrada */

			incrementa(recurso, -5);                          /* Seccion */
			fprintf(fsal, "P1: recurso[%d]=%dn", i, *recurso);       /* critica */

			*c1 = 'F';    /* Seccion de salida */

		}/* fin del for */

		while (*marcaFin != 'x'); /* El Proceso Padre espera al Poceso Hijo */

		fprintf(fsal, "El recurso valia 0 y ahora vale %dn", *recurso);

		if (!eliminarMemoria())   /* eliminar memoria compartida */
			fprintf(stderr, "error de eliminarMemorian");

		exit(0);

	}/*if (0!=fork())*/

	else {                                      /* Proceso Hijo */

		int i;
		fprintf(fsal, "P2: SOY EL PROCESO HIJOn");

		for (i = 0; i < nIteraciones; i++) {

			*c2 = 'T';                          /* Seccion */
			*turno = 1;                                 /* de */
			while (((*c1) == 'T') && ((*turno) == 1));        /* entrada */

			incrementa(recurso, 5);                             /* Seccion */
			fprintf(fsal, "P2: recurso[%d]=%dn", i, *recurso);       /* critica */

			*c2 = 'F';  /* Seccion de salida */

		} /* fin del for */


	/*Cierre de los ficheros*/

		fclose(fsal);

		/* termina */
		*marcaFin = 'x';
		exit(0);

	}/*fin else Proceso Hijo*/


}/* *************** FIN MAIN ****************** */