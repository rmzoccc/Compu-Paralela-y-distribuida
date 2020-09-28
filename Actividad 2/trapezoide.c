/*Esta versión acepta la entrada de los puntos finales del
Intervalo y el número de trapezoides..
 *
 * Input:    The endpoints of the interval of integration and the number
 *           of trapezoids
 * Output:   Estimate of the integral from a to b of f(x)
 *           using the trapezoidal rule and n trapezoids.
 *
 * Compile:  mpicc -g -Wall -o mpi_trap2 mpi_trap2.c
 * Run:      mpiexec -n <number of processes> ./mpi_trap2
 *
 * Algorithm:
 *    1.  Cada proceso calcula "su" intervalo de
 * la integración..
 *    3a. Cada proceso != 0 envia esta integral hacia el proceso 0.
 *    3b. Proceso 0 ssuma los calculos recibidos de
 *        de los procesos individuales e imprime el resultado
 *
 */
#include <stdio.h>
#include <mpi.h>

/* Funcion de Entrada de los valores a, b, n */
void Get_input(int my_rank, int comm_sz, double* a_p, double* b_p,
      int* n_p);

/* Calculamos la integral  */
double Trap(double left_endpt, double right_endpt, int trap_count, 
   double base_len);    

/* Function integracion */
double f(double x); 

int main(void) {
   int my_rank, comm_sz, n, local_n;   
   double a, b, h, local_a, local_b;
   double local_int, total_int;
   int source; 

   /* Inicializa el mpi MPI */
   MPI_Init(NULL, NULL);

   /* consigue el numero de proceso actual*/
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

   /* numero de procesos total*/
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

   Get_input(my_rank, comm_sz, &a, &b, &n);

   h = (b-a)/n;          
   local_n = n/comm_sz;  /* NUmero de trapzoides*/


   local_a = a + my_rank*local_n*h;
   local_b = local_a + local_n*h;
   /* Calculamos la integral  */
   local_int = Trap(local_a, local_b, local_n, h);

   /* Sume las integrales calculadas por cada proceso. */
   if (my_rank != 0)
      MPI_Send(&local_int, 1, MPI_DOUBLE, 0, 0, 
            MPI_COMM_WORLD);
   else {
      total_int = local_int;
      for (source = 1; source < comm_sz; source++) {
         MPI_Recv(&local_int, 1, MPI_DOUBLE, source, 0,
            MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         total_int += local_int;
      }
   }

   /* Print the result */
   if (my_rank == 0) {
      printf("With n = %d trapezoids, our estimate\n", n);
      printf("of the integral from %f to %f = %.15e\n",
          a, b, total_int);
   }

   /* Shut down MPI */
   MPI_Finalize();

   return 0;
} /*  main  */

/*------------------------------------------------------------------
 Get_input
 * Purpose:      Obtiene la entrada del usuario, punto izquierdo y el punto derecho, admeas
                  del numero de trapezoides
 * Output args:  a_p:  pointer to left endpoint               
 *               b_p:  pointer to right endpoint               
 *               n_p:  pointer to number of trapezoids
 */
void Get_input(int my_rank, int comm_sz, double* a_p, double* b_p,
      int* n_p) {
   int dest;

   if (my_rank == 0) {/* Si es el master o proceso 0 */

      printf("Enter a, b, and n\n");
      scanf("%lf %lf %d", a_p, b_p, n_p);

      for (dest = 1; dest < comm_sz; dest++) {
         MPI_Send(a_p, 1, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
         MPI_Send(b_p, 1, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
         MPI_Send(n_p, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
      } 
   } else { /* my_rank != 0 */
      /* MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag,
             MPI_Comm comm, MPI_Status * status)*/
      MPI_Recv(a_p, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,
            MPI_STATUS_IGNORE);
      MPI_Recv(b_p, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,
            MPI_STATUS_IGNORE);
      MPI_Recv(n_p, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
            MPI_STATUS_IGNORE);
   } 
}  /* Get_input */

/*------------------------------------------------------------------
 * Function:     Trap
 * Purpose:      Función serial para estimar una integral definida
 * usando la regla trapezoidal
 * Input args:   left_endpt
 *               right_endpt
 *               trap_count 
 *               base_len
 * Return val:   Trapezoidal rule estimate of integral from
 *               left_endpt to right_endpt using trap_count
 *               trapezoids
 */
double Trap(
      double left_endpt  , 
      double right_endpt , 
      int    trap_count  , 
      double base_len    ) {

   double estimate, x; 
   int i;

   estimate = (f(left_endpt) + f(right_endpt))/2.0;
   printf(" left_endpt: %lf\n",left_endpt);
   printf(" right_endpt: %lf\n",right_endpt);
  
   printf(" estimacion: %lf\n",estimate);

   for (i = 1; i <= trap_count-1; i++) {
      x = left_endpt + i*base_len;
      estimate += f(x);
   }
   estimate = estimate*base_len;
   printf(" estimacion Total: %lf\n",estimate);

   return estimate;
} /*  Trap  */


/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Compute value of function to be integrated
 * Input args:  x
 */
double f(double x) {
   return x*x;
} /* f */
