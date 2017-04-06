#include <stdlib.h>
#include <stdio.h>
//#include "interface.h"
//#include "server.h"
#include "interface.h"
#include "server.h"


struct Map_info get_map_info(char* file_name){
  FILE * f = fopen(file_name, "r");
  int nb_read = 0;
  struct Map_info map_info;
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
	    printf("ERROR : more objectives than expected\n");
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










void get_towns(struct Town * towns, int nb, char *file_name){

  FILE * f = fopen(file_name, "r");
  char c = getc(f);
  int skiped_line1 = 0;
  int nb_towns = 0; // nb of towns read
  
  int id = 0;
  
  while (nb_towns < nb){
    
    
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
    
    
    
    
    
    // get the towns
    else{
      id = 0;
      int nb_townsss = 0;
      //for (int nb_townsss = 0; nb_townsss < nb; nb_townsss++){ // while all the towns haven't be read
      while (nb_townsss < nb){
	printf("nb_townsss = %d\n", nb_towns);
	
	char name[100];// = '\0';
	
	// skip spaces
	while (c == ' ')
	  c = getc(f);
	
	while (c != '\n'){ // read line by line
	  
	  // read the id :
	  for (int n = 0; c != ' '; n++){
	    id = 10*n+atoi(&c);
	    c = getc(f);  
	  }
	  
	  // skip spaces
	  while (c == ' '){
	    c = getc(f);
	  }
	  
	  // read the town name :
	  int i=0;
	  for (i = 0; c != ' ' && c != '\n'; i++){
	    printf("%c",c);
	    name[i] = c;
	    c = getc(f);
	    
	  }
	  
	  name[i] = '\0';
	  
	  // skip spaces
	  
	  while (c != '\n')
	    c = getc(f);
	  
	  
	  c = getc(f);    
	  towns[nb_townsss].id = id;
	  towns[nb_townsss].name = name;
	  //printf("\ntown = %s\n",towns[0].name);
	  //printf("name = %s\n", name);
	  //printf("nb_townsss=%d\n",nb_townsss);
	  nb_townsss++;
	}
	
	// skip all other lines
	
	//printf("nb_townsss=%d\n",nb_towns);
	nb_towns++;
      }
      //printf("nb_towns=%d\n",nb_towns);
      //break;
    }
    
  }
}
