#ifndef SERVER_H
#define SERVER_H

#include "interface.h"

enum Town_name;

struct Map_info{
  int nb_towns;
  int nb_links;
  int nb_objs;
  int nb_w_player;

};
  
struct Map_info get_map_info(char* file_name);
//void file2rails(struct Rail *rails, int size, char *file_name);  
void file2rails(struct Rail *rails, int nb_rails, struct Objective *objs, int nb_objs, char *file_name);



#endif
