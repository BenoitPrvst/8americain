# Définit le compilateur C, gcc par défaut si CC n'est pas déjà défini
CC ?= gcc
# Ajoute des options de compilation pour afficher tous les avertissements
CFLAGS += -Wall
# Définit le chemin vers les bibliothèques
LIB_PATH = .

# Cible principale : construit le programme et la bibliothèque
all: lib
	# Compile le programme principal en liant avec la bibliothèque dynamique
	$(CC) $(LDFLAGS) -L$(LIB_PATH) -o 8americain $(CFLAGS) 8americain.c -lfuns-8americain

# Construit la bibliothèque dynamique
lib:
	# Compile le fichier source de la bibliothèque avec position indépendante du code
	$(CC) -fPIC -c funs-8americain.c
	# Lie les fichiers objets pour créer une bibliothèque partagée
	$(CC) -shared -o libfuns-8americain.so funs-8americain.o

# Nettoie les fichiers générés par la compilation
clean:
	# Supprime les fichiers objet, la bibliothèque partagée et l'exécutable
	rm -f *.o *.so 8americain