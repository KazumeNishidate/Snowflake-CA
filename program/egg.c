#include <eggx.h>
#include <stdio.h>
#include  <stdlib.h>
#include  <math.h>
#include  <string.h>
#include  <X11/Xlib.h>
#include  <X11/Xutil.h>
#include "rw.h"
#include "prototypes.h"

void egg_disp(void){
  static int cnt=0, win;
  int r, g, b;
  int i, j;

  if(cnt==0){
    win=gopen(ctl.mat_size*2+4,ctl.mat_size*2+4);
    gsetbgcolor(win,"white");
    layer(win,0,1);
  }

  for (i = 2; i < ctl.mat_size+2; i++){
    for (j = 2; j < ctl.mat_size+2; j++){
      if(sys.mat0[ctl.shift*i+j]==1){
	makecolor(DS9_RAINBOW,0,100,sys.mat2[ctl.shift*i+j]%100,&r,&g,&b);
	newrgbcolor(win,r,g,b);
	if(i%2==1){  // odd line
	  fillcirc(win, i*2, j*2, 1, 1);
	}
	if(i%2==0){  // even line
	  fillcirc(win, i*2, j*2+1, 1, 1);
	}
      }
    }
  }
  copylayer(win,1,0);
  cnt++;  
}
