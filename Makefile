#  Makefile 
#  Auteur : Farès BELHADJ
#  Email  : amsi@ai.univ-paris8.fr
#  Date   : 15/12/2014

SHELL = /bin/sh
# définition des commandes utilisées
CC = gcc
ECHO = echo
RM = rm -f
TAR = tar
MKDIR = mkdir
CHMOD = chmod
CP = rsync -R
# déclaration des options du compilateur
PG_FLAGS =
CPPFLAGS = -I. 
CFLAGS = -Wall -O3 
LDFLAGS = -lm -lpng -ljpeg -lopencv_highgui -lopencv_imgproc -lopencv_core

UNAME := $(shell uname)
ifeq ($(UNAME),Darwin)
	MACOSX_DEPLOYMENT_TARGET = 10.8
        CFLAGS += -I/usr/X11R6/include -mmacosx-version-min=$(MACOSX_DEPLOYMENT_TARGET) -I/opt/local/include/ -Wno-unused-function
        LDFLAGS += -lopencv_videoio -L/opt/local/lib -mmacosx-version-min=$(MACOSX_DEPLOYMENT_TARGET)
else
        LDFLAGS +=  -L/usr/lib -L/usr/X11R6/lib
endif

#définition des fichiers et dossiers
PROGS = opcv1
HEADERS = 
SOURCES = openCV.c
OBJ = $(SOURCES:.c=.o)

all: $(PROGS)

$(PROGS): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(PROGS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(PROGS) $(OBJ) *~ gmon.out core.* 
