NAME	=	Makegen

SRCS	=	./src/writer.cpp		\
			./src/list_files.cpp	\
			./src/main.cpp			\
			./src/file_op.cpp

OBJS	=	$(SRCS:.cpp=.o)

CFLAGS	=	-W -Wall -Wextra -Werror
CFLAGS	+=	-I ./include

all:	$(NAME)

$(NAME):
		g++ -o $(NAME) $(OBJS) $(CFLAGS)

clean:
		rm -f $(OBJS)

fclean:	clean
		rm -f $(NAME)

re:	fclean all
