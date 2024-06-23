#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"

/* RWCA-2d uder cyclic boundary condition */

int main(void){

  get_control_param();
  init_mem();

  /*================= average calculation ======================*/
  for(sys.average_step = 0; 
      sys.average_step <ctl.average_iteration_num;
      sys.average_step++){

/* fix */
/*    printf("sys.average_step = %d\n",sys.average_step); */

    set_init_conf();
    mk_copy(sys.mat0, sys.mat1);
    
    /*----------- RWCA moving step -----------*/
    for(sys.time_step=0;sys.time_step<ctl.max_time_step;sys.time_step++)
      {
/*-------------- X interface -------------------*/
	egg_disp();

	move_walkers();       /* sys.mat0 => RWCA  => sys.mat1 */
	mk_copy(sys.mat1, sys.mat0);  /* sys.mat1  =  sys.mat0 */

      }
    /*-------- end of RWCA moving step -------*/
  }
  getchar();

  return 0;
}

