MAIN_SRC	+=	src/main.c

SRC		+=	src/display.c
SRC		+=	src/free/map.c
SRC		+=	src/input/reader.c
SRC		+=	src/solver.c

LDFLAGS		+=	-lcurses

MAIN_OBJ	+=	$(MAIN_SRC:.c=.o)
OBJ		+=	$(SRC:.c=.o)

NAME		=	viewver

CPPFLAGS	+=	-iquote include
CFLAGS		+= -Wall -Wextra #-Werror

ifdef DEBUG
CPPFLAGS	+=	-DDEBUG
CFLAGS		+=	-ggdb3
endif

$(NAME):	$(MAIN_OBJ) $(OBJ)
	gcc -o $(NAME) $(MAIN_OBJ) $(OBJ) $(LDFLAGS)

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	rm -f $(MAIN_OBJ) $(OBJ)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)
	rm -f team.data

.PHONY: re
re: fclean all
