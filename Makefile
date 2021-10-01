# Source Code // Output executable
MAIN = main.c
SYS = bridge.c camera.c objects.c 
EXE = hw4


all: $(EXE)
SRCOBJ = $(MAIN:.c=.o) $(SYS:.c=.o)

CC=gcc

# MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-03 -Wall -DUSEGLEW
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32 -lm
CLEAN=del *.exe *.o *.a

# Mac OSX
else
ifeq "$(shell uname)" "Darwin"
CLFG=-O3 -Wall  -Wno-deprecated-declarations -DRES=1
LIBS=-framework GLUT -framework OpenGL
CLEAN=rm -f $(EXE) *.o *.a

# Linux/Unix/Solaris
else
CFLG=-O3 -Wall 
LIBS=-lglut -lGLU -lGL -lm
CLEAN=rm -f $(EXE) *.o *.a

endif
endif


# Compilation / Linking
$(EXE): $(SRCOBJ)
	$(CC) $(CLFG) -o $(EXE) $(SRCOBJ) $(LIBS)

%.o: %.c %.h
	$(CC) $(CLFG) -c $< -o $@


# Cleanup rule
clean:
	$(CLEAN)