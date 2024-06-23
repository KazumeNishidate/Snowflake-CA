#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"

void move_walkers()
{
/*****************************************************************/
/* move_walkers                                                  */
/*                                                               */
/* All walkers will move according to the RWCA-2D dynamics.      */
/* sys.mat0  => MOVE => sys.mat1                                 */
/*                                                               */
/*****************************************************************/
  int i, j, x, y=0;
  int n, e, s, w;
  int ne, se, sw, nw;
  int nn, ee, ss, ww;
  int nne, nee, see, sse, ssw, sww, nww, nnw;
  int move_cnt = 0;
  int cnt;


  for (i = 2; i < ctl.mat_size+2; i++){
    for (j = 2; j < ctl.mat_size+2; j++){

      x  = sys.mat0[ctl.shift*i+j];

      n  = sys.mat0[ctl.shift*(i-1)+j];
      e  = sys.mat0[ctl.shift*i+j+1];
      s  = sys.mat0[ctl.shift*(i+1)+j];
      w  = sys.mat0[ctl.shift*i+j-1];

      ne  = sys.mat0[ctl.shift*(i-1)+j+1];
      se  = sys.mat0[ctl.shift*(i+1)+j+1];
      sw  = sys.mat0[ctl.shift*(i+1)+j-1];
      nw  = sys.mat0[ctl.shift*(i-1)+j-1];

      nn  = sys.mat0[ctl.shift*(i-2)+j];
      ee  = sys.mat0[ctl.shift*i+j+2];
      ss  = sys.mat0[ctl.shift*(i+2)+j];
      ww  = sys.mat0[ctl.shift*i+j-2];

      nne = sys.mat0[ctl.shift*(i-2)+j+1];
      nnw = sys.mat0[ctl.shift*(i-2)+j-1];
      nee = sys.mat0[ctl.shift*(i-1)+j+2];
      nww = sys.mat0[ctl.shift*(i-1)+j-2];
      see = sys.mat0[ctl.shift*(i+1)+j+2];
      sww = sys.mat0[ctl.shift*(i+1)+j-2];
      sse = sys.mat0[ctl.shift*(i+2)+j+1];
      ssw = sys.mat0[ctl.shift*(i+2)+j-1];

      if(x==0 && i%2==1){  // odd line
	cnt = n+e+s+w+nw+sw;
	if(cnt==1){
	  y = 1;
	} else {
	  y = 0;
	}
      }
      if(x==0 && i%2==0){  // even line
	cnt = n+e+s+w+ne+se;
	if(cnt==1){
	  y = 1;
	} else {
	  y = 0;
	}
      }
      if(x==1) y =1;
      *(sys.mat1+ctl.shift*i+j) = y;
      *(sys.mat2+ctl.shift*i+j)+= y;      
    }
  }
  set_bc(sys.mat1);

  //    show_matrix(sys.mat0);
  //    show_matrix(sys.mat1);
  //    getchar();
}

void set_bc(int *ants)
{
  int i;

/* corner adjustment 1 */
  *ants     = *(ants+( ctl.shift*(ctl.mat_size+1) - 4));
  *(ants+1) = *(ants+( ctl.shift*(ctl.mat_size+1) - 3));
  *(ants+ctl.shift) = *(ants+( ctl.shift*(ctl.mat_size+2) - 4));
  *(ants+(ctl.mat_size+5)) = *(ants+( ctl.shift*(ctl.mat_size+2) - 3));

/* corner adjustment 2 */
  *(ants+(ctl.mat_size+2))   = *(ants+(ctl.shift*ctl.mat_size + 2));
  *(ants+(ctl.mat_size+3))   = *(ants+(ctl.shift*ctl.mat_size + 3));
  *(ants+2*(ctl.mat_size+3)) = *(ants+(ctl.shift*(ctl.mat_size+1)+2));
  *(ants+2*(ctl.mat_size+3)+1) = *(ants+(ctl.shift*(ctl.mat_size+1)+3));

/* corner adjustment 3 */
  *(ants+(ctl.mat_size+3)*(ctl.mat_size+3)-1) = *(ants+3*ctl.shift-4);
  *(ants+(ctl.mat_size+3)*(ctl.mat_size+3)) = *(ants+3*ctl.shift-3);
  *(ants+(ctl.mat_size+3)*ctl.shift) = *(ants+4*ctl.shift-4);
  *(ants+(ctl.mat_size+3)*ctl.shift+1) = *(ants+4*ctl.shift-3);

/* corner adjustment 4 */
  *(ants+ctl.shift*(ctl.mat_size+3)-2) = *(ants+2*ctl.shift+2);
  *(ants+ctl.shift*(ctl.mat_size+3)-1) = *(ants+2*ctl.shift+3);
  *(ants+ctl.shift*ctl.shift-2) = *(ants+3*ctl.shift+2);
  *(ants+ctl.shift*ctl.shift-1) = *(ants+3*ctl.shift+3);

/* border adjustment   */

  for (i = 2; i < ctl.mat_size+2; i++){
      *(ants+i) = *(ants+ctl.shift*ctl.mat_size+i);
      *(ants+ctl.mat_size+4+i) = *(ants+ctl.shift*(ctl.mat_size+1)+i); 
      *(ants+ctl.shift*(ctl.mat_size+2)+i)=*(ants+2*ctl.shift+i);
      *(ants+ctl.shift*(ctl.mat_size+3)+i) = *(ants+3*ctl.shift+i); 

      *(ants+i*ctl.shift)   = *(ants+(i+1)*ctl.shift-4);
      *(ants+i*ctl.shift+1) = *(ants+(i+1)*ctl.shift-3);

      *(ants+(i+1)*ctl.shift-2)   = *(ants+i*ctl.shift+2);
      *(ants+(i+1)*ctl.shift-1)   = *(ants+i*ctl.shift+3);
    }

}

void mk_copy(int *original, int *copy)
{
  int i, j;

  for(i=0; i<ctl.mat_size+4; i++){
    for(j=0; j<ctl.mat_size+4; j++){
      *(copy+ctl.shift*i+j)  = *(original+ctl.shift*i+j);
    }
  }
}

