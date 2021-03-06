#include <stdlib.h>
#include <stdio.h>
#include "interface.h"
#include "server.h"

/**
 * @brief get_map_info
 * @param file_name file which contains the game info
 * @return nb of towns, nb of links, nb of objectves and nb of wagon per player
 */
struct Map_info get_map_info(char* file_name){
  FILE * f = fopen(file_name, "r");
  int nb_read = 0;
  struct Map_info map_info={0,0,0,0};
  while (nb_read < 4){
    int i = 0;
    char c = getc(f);
    if (c == '%'){
      while (c != '\n'){
	c = getc(f);
      }
    }

    else if (c != ' ' && c!= '\n'){
      nb_read++;
      while (c != ' ' && c!='\n'){ 
	i = 10*i + atoi(&c);
	c = getc(f);
      }
      if (nb_read == 1){
	map_info.nb_towns = i;
      }
      else if (nb_read == 2){
	map_info.nb_links = i;
      }
      else if (nb_read == 3){
	map_info.nb_objs = i;
      }
      else if (nb_read == 4){
	map_info.nb_w_player = i;	
      }
      
    }
  }
  fclose(f);
  return map_info;
}

/**
 * \brief file2rails
 * \param rails empty table of rails to be completed
 * \param size the nb of links
 * \param file_name file_name file which contains the game info
 *
 * Completes the table rails with all the rail of the map
 */
void file2rails(struct Rail *rails, int nb_rails, struct Objective *objs, int nb_objs, char *file_name){
  
  FILE * f = fopen(file_name, "r");
  char c = getc(f);
  int skiped_line1 = 0;
  int nb_param = 0; // might be = 4 to be a rail, = 3 to be an objective
  int param1, param2, param3, param4; // the 1st,2rd,3rd,4th parametre of a line
  int n = 0; // the parametre which is read
  int ind_rails = 0; // indice in the table rails
  int ind_objs = 0; // indice in the table objs
  
  while (c != EOF){

   
    // skip all comments

    if (c == '%'){ 
      while (c != '\n'){
	c = getc(f);
      }
      c = getc(f);
    }

    // skip the first line
    
    else if (!skiped_line1){
      while (c != '\n'){
	c = getc(f);
      }
      skiped_line1 = 1;
      c = getc(f);
    }

    // test if the line is a rail and get the parameters:

    else{

      
      // skip spaces
      if (c == ' '){
	n = 0;
      }

      else if (c != '\n'){

	while (c != ' ' && c != '\n'){

	  n = 10*n+atoi(&c);

	  c = getc(f);
	}
	nb_param++;
	if (nb_param == 1) // to which param correspond n ?
	  param1 = n;
	else if (nb_param == 2)
	  param2 = n;
	else if (nb_param == 3)
	  param3 = n;
	else if (nb_param == 4)
	  param4 = n;
	n = 0;
	if (c !='\n') // need to get the first character of the next line
	  c = getc(f);

      }
      
      else{

	n = 0;
	if (nb_param == 4){ //if is a rail
	  if (ind_rails > nb_rails)
	    printf("ERROR : more rails than expected\n");
	  else{
	    struct Rail rail;
	    rail.town1 = param1;
	    
	    rail.town2 = param2;
	    
	    rail.color = param3;
	    
	    rail.length = param4;
	    
	    rails[ind_rails] = rail;
	    
	    ind_rails++;
	  }
	}
	
	else if (nb_param == 3){ //if is an objective
	  if (ind_objs > nb_objs)
	    printf("ERROR : more objectives (%d) than expected (%d)\n", ind_objs, nb_objs);
	  else{
	    struct Objective obj;
	    obj.town1 = param1;
	    obj.town2 = param2;
	    obj.points = param3;
	    objs[ind_objs] = obj;

	    ind_objs++;
	  }
	  }

	c = getc(f);
        nb_param = 0;
      }
    }
    }
  
}
