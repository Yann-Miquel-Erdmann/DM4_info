EXEC_C = generateur_de_formules
SOURCES_C = C/main.c C/5_maisons/5_maisons.c C/le_menteur/le_menteur.c C/coloriage_carte/coloriage_carte.c C/sudoku/sudoku.c C/taquin/taquin.c C/dames/n_dames.c  C/utils.c
C_FLAGS = -g -Wall -Wextra  

C: $(SOURCES_C)
	gcc $(SOURCES_C) -o $(EXEC_C) $(C_FLAGS)

clean_C:
	rm $(EXEC_C)

EXEC_OCAML = satsolver
SOURCES_OCAML = base_satsolver.ml valuation.ml satsolver.ml variable_priority.ml algo_quine.ml algo_naif.ml main.ml
OCAML_DIR = Ocaml

OCAML: $(addprefix $(OCAML_DIR)/, $(SOURCES_OCAML))
	cd $(OCAML_DIR) && ocamlopt $(SOURCES_OCAML) -o ../$(EXEC_OCAML) 

clean_OCAML:
	rm $(OCAML_DIR)/*.cmi	
	rm $(OCAML_DIR)/*.cmx	
	rm $(OCAML_DIR)/*.o	
	rm $(EXEC_OCAML)

clean: clean_C clean_OCAML
	echo "cleaned"