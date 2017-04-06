#include <stdlib.h>
#include <stdio.h>
#include "t2.h"


static int memory = 0;



void CONCAT(NAME,_test)(){
  printf("TWO first : %d\n", memory);
  memory++;
  printf("TWO then : %d\n", memory);
}


