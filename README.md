Ticket to ride 
===============

Presentaion of the project
-----------------------------

This project is a simulation of a ticket to ride game between some AI which have different strategies.<br/>
The game has been implemented with a relation host-server, the server had to check there were no cheat possible.

Compilation
-------------

Go in trunk/build and run the command `make` <br/>
To add options, like gdb or valgrind do the command `.. -DCMAKE_BUILD_TYPE=DEBUG` then compile with `make`

Execution
-----------
Run the command `./src/game ../tests/France.txt` from trunk/build

Tests
-------

Run the command `make test` from trunk/build <br/>
Run the executable files in the folder trunk/tests: <br>
  `./test_init`<br/>
  `./test_winner`<br/>
  `./test_play-turn` <br/>

Documentation
--------------

To produce the doc, go in trunk/doc and run th e command `doxygen`<br/>
To display the doc, open the file index.html in a browser<br/>
This can be found in the folder html generated in trunk/doc



---------------------------------------------------------

Les casaniers du rail
=====================

**Compilation projet**

aller dans trunk/build et effectuer la commande make
pour ajouter des options comme gdb et valgrind faire la commande cmake .. -DCMAKE_BUILD_TYPE=DEBUG puis recompiler avec make

**Exécution**

lancer la commande ./src/game ../tests/France.txt depuis trunk/build

**Test**

lancer la commande make test depuis trunk/build
lancer également les exécutables présents dans le dossier trunk/tests
./test_init
./test_winner
./test_play_turn

**Documentation**

pour générer la doc aller dans trunk/doc et lancer la commande doxygen

pour afficher la doc ouvrir le fichier index.html dans un navigateur
ce fichier est présent dans le dossier html généré dans trunk/doc  
