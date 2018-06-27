CC		=	g++

EXEC	=	Makegen

SRC		=	./src/writer.cpp		\
			./src/list_files.cpp	\
			./src/main.cpp			\
			./src/file_op.cpp

OBJ		=	$(SRC:.cpp=.o)

LDFLAGS	=	

CFLAGS	=	-W -Wall -Wextra
CFLAGS	+=	-I ./include

all:	$(EXEC)

$(EXEC):	$(OBJ)
		$(CC) -o $(EXEC) $(OBJ)

%.o:	%.cpp
		$(CC) -o $@ -c $< $(CFLAGS)

clean:
		rm -f $(OBJ)

mrproper:	clean
		rm -f $(EXEC)

re:	mrproper all

.PHONY: clean mrproper
