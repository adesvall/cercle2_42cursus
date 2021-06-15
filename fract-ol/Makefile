NAME		= fract-ol

SRCS		= main.c create_img.c complex.c get_color.c events.c utils.c

SRCSS		= ${addprefix srcs/, ${SRCS}}

OBJS		= ${SRCSS:.c=.o}

HEADERS		= includes/fract-ol.h

OPENGL		= -lXext -lX11 -lm -lbsd
CFLAGS		= -Wall -Wextra -Werror -Iincludes -Imlx_linux -O3

all:		${NAME}

$(NAME):	${OBJS}
			make -C mlx_linux
			gcc -o ${NAME} ${OBJS} ${CFLAGS} mlx_linux/libmlx.a $(OPENGL)

$(OBJS):	${HEADERS}

.c.o:		
			gcc ${CFLAGS} $(OPENGL) -c $< -o ${<:.c=.o}

clean:
			make -C mlx_linux clean
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
