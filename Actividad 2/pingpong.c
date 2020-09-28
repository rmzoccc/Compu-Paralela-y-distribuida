#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  const int LIMITE = 10;

  MPI_Init(NULL, NULL);
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Se asume que el pingpong se realiza entre 2 procesos
  if (world_size != 2) {
    fprintf(stderr, "EL numero de procesos debe ser 2 para %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  int contador = 0;
  int partner_rank = (world_rank + 1) % 2; //dato para saber hacia donde va la pelota del ping pong
  while (contador < LIMITE) {
    if (world_rank == contador % 2) {
      // Se incrementa el contador de ping pong antes de enviarlo
      contador++;
      MPI_Send(&contador, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
      printf("Proceso: %d envio e incremento contador_ping_pong %d hacia el proceso: %d\n",
             world_rank, contador, partner_rank);
    } else {
      MPI_Recv(&contador, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      printf("Proceso: %d recepción contador_ping_pong %d de el proceso: %d\n",
             world_rank, contador, partner_rank);
    }
  }
  MPI_Finalize();
}