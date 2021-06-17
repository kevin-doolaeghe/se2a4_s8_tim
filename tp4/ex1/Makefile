#
# Makefile pour l'application de chiffrement
#

SOURCES = $(wildcard *.c)
OBJETS = $(SOURCES:.c=.o)
BIBLIOTHEQUES = -lm -L ../libs -lcrypt
CFLAGS += -std=c99 -D_DEFAULT_SOURCE -I ../libs
CIBLE = chiffrement

#
# Nom de la cible principale
#

all: $(CIBLE)

#
# Cible de nettoyage
#

clean: 
	rm -f core *.o $(CIBLE)

#
# Cible de recompilation
#

rebuild: clean all

#
# Dependances pour l'executable
#

$(CIBLE): $(OBJETS)
	$(CC) -o $@ $^ $(BIBLIOTHEQUES)

#
# Formatage
#

format :
	clang-format -i -style=WebKit *.c