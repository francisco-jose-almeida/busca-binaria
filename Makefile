TARGET = a

SRCS = src/main/main.c \
	   src/main/arquivos.c \
	   src/visualizacoes/barras/barras.c \
	   src/visualizacoes/arvore/arvore.c 

LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all: 
	gcc $(SRCS) -o $(TARGET) $(LIBS)
	./$(TARGET)

