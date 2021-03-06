#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../src/interface.h"
#include "../src/server.h"


//#include "interface.h"
//#include "server.h"

/*
int comp_string(char *a, char *b){
  for (int i = 0; a[i] != '\0' && b[i] != '\0', i++){
    if (a[i] != b[i])
      return 0;
  }
  if (a[i] != '\0' || b[i] != '\0')
    return 0;
  return 1;
}
*/


int test_get_map_info(){
  struct Map_info map_info = get_map_info("tests_file.txt");
  if (map_info.nb_towns == 2 && map_info.nb_links == 1 && map_info.nb_objs == 1 && map_info.nb_w_player == 10)
    return 1;
  return 0;
  
}



int test_file2rails(){
  struct Map_info map_info = get_map_info("tests_file.txt");
  struct Rail rails[map_info.nb_links];
  struct Objective objs[map_info.nb_objs];
  file2rails(rails, map_info.nb_links, objs, map_info.nb_objs, "tests_file.txt");
  if (rails[0].town1 == 1 // OK for rails ?
      && rails[0].town2 == 2 
      && rails[0].length == 6 
      && rails[0].color == 42
      && objs[0].town1 == 1
      && objs[0].town2 == 2
      && objs[0].points == 100000
      
      && objs[0].town1 == 1 // OK for objective ?
      && objs[0].town2 == 2
      && objs[0].points == 100000){

    return 1;
  }
  return 0;
}



int test_get_towns(){
  struct Map_info map_info = get_map_info("tests_file.txt");
  struct Town towns[map_info.nb_towns];

  get_towns(towns, map_info.nb_towns, "tests_file.txt");
  printf("%s\n",towns[0].name); //debugage
  printf("%s\n",towns[1].name);

  if ((towns[0].id == 1) && (strcmp(towns[0].name, "Vladivostok") == 0)
      && (towns[1].id == 2) && (strcmp(towns[0].name, "Kinshasa0") == 0))
    return 1;

  return 0;
}


int main(){ 
  printf("test of get_map_info ... ");
  if (test_get_map_info())
    printf("PASSED\n");
  else
    printf("FAILED\n");


  printf("test of file2rails ... ");
  if (test_file2rails())
    printf("PASSED\n");
  else
  printf("FAILED\n");


  printf("test of get_towns ... ");
  if (test_get_towns())
    printf("PASSED\n");
  else
  printf("FAILED\n");

  return 0;
}
