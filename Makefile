NAME	=	test

SRCS	=	./src/main.cpp		\
		./src/fill_tab.cpp		\
		./src/check_info_file.cpp		\


OBJS	=	$(SRCS:.cpp=.o)


CFLAGS	=	-W -Wall -Wextra -Werror
CFLAGS	+=	-I ./include/ 

all:		$(NAME)

$(NAME):
		g++ -o $(NAME) $(SRCS) $(CFLAGS)

clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f $(NAME)

re:		fclean all
