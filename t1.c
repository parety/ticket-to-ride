#include <stdlib.h>
#include <stdio.h>
#include "t1.h"


static int memory = 0;



void CONCAT(NAME,_test)(){
  printf("ONE before : %d\n", memory);
  memory++;
  printf("ONE after : %d\n", memory);
}
