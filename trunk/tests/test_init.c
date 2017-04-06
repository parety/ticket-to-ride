#include <stdlib.h>
#include <stdio.h>
#include "../src/interface.h"
#include "../src/server.h"



int test_get_map_info(){
  struct Map_info map_info = get_map_info("tests_file.txt");
  if (map_info.nb_towns == 2 && map_info.nb_links == 1 && map_info.nb_objs == 1 && map_info.nb_w_player == 10)
    return 1;
  return 0;
  
}

int test_get_map_info_France(){
  struct Map_info map_info = get_map_info("France.txt");
  if (map_info.nb_towns == 37 && map_info.nb_links == 101 && map_info.nb_objs == 33 && map_info.nb_w_player == 45)
    return 1;
  return 0;
  
}



int test_file2rails(){
  struct Map_info map_info = get_map_info("tests_file.txt");
  struct Rail rails[map_info.nb_links];
  struct Objective objs[map_info.nb_objs];
  file2rails(rails, map_info.nb_links, objs, map_info.nb_objs, "tests_file.txt");
  if (rails[0].town1 == 1 
      && rails[0].town2 == 2 
      && rails[0].length == 6 
      && rails[0].color == 42
      && objs[0].town1 == 1
      && objs[0].town2 == 2
      && objs[0].points == 100000){
    return 1;
  }
  return 0;
}

int test_file2rails_France(){
  struct Map_info map_info = get_map_info("France.txt");
  struct Rail rails[map_info.nb_links];
  struct Objective objs[map_info.nb_objs];
  file2rails(rails, map_info.nb_links, objs, map_info.nb_objs, "France.txt");
  
  if (!(rails[0].town1 == 32
      && rails[0].town2 == 17
      && rails[0].length == 3 
	&& rails[0].color == 6))
    return 0;

  if (!(rails[6].town1 == 31
      && rails[6].town2 == 29
      && rails[6].length == 6 
	&& rails[6].color == 2))
    return 0;

  if (!(rails[14].town1 == 28
      && rails[14].town2 == 19
      && rails[14].length == 6 
	&& rails[14].color == 6))
    return 0;

  if (!(rails[32].town1 == 26
      && rails[32].town2 == 23
      && rails[32].length == 3 
	&& rails[32].color == 1))
    return 0;
  
  if (!(rails[100].town1 == 37
      && rails[100].town2 == 34
      && rails[100].length == 1 
	&& rails[100].color == 0))
    return 0;


  if (!(objs[0].town1 == 3
      && objs[0].town2 == 6
	&& objs[0].points == 13))
    return 0;

  if (!(objs[32].town1 == 12
      && objs[32].town2 == 14
	&& objs[32].points == 4))
    return 0;

  return 1;
}


int main(){
  printf("test of get_map_info ... ");
  if (test_get_map_info())
    printf("PASSED\n");
  else
    printf("FAILED\n");

  printf("test of get_map_info_France ... ");
  if (test_get_map_info_France())
    printf("PASSED\n");
  else
    printf("FAILED\n");

  printf("test of file2rails ... ");
  if (test_file2rails())
    printf("PASSED\n");
  else
  printf("FAILED\n");

  printf("test of file2rails_2 ... ");
  if (test_file2rails_France())
    printf("PASSED\n");
  else
  printf("FAILED\n");

  return 0;
}


