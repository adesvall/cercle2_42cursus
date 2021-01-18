NAME		= miniRT

SGNL		= get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
SLIB		= libft/libftutils.c libft/libftutils2.c libft/libftutils3.c

SRCS		= main/main.c \
			collisions/vectop.c main/create_img.c collisions/collision.c collisions/collisionany.c collisions/collisionutils.c \
			parse/parse_file.c parse/parseutils.c main/events.c parse/add_elem.c main/save_bmp.c main/skybox.c ${SLIB} ${SGNL}

SRCSS		= ${addprefix srcs/, ${SRCS}}

OBJS		= ${SRCSS:.c=.o}

CFLAGS		= -Wall -Wextra -I./includes -I/usr/include -Imlx_linux -lpthread -O0 -g

all:		${NAME}

$(NAME):	${OBJS}
			gcc -o ${NAME} ${OBJS} ${CFLAGS} -L.. -lmlx -L/usr/lib -lXext -lX11 -lm -lpthread -lbsd -g

.c.o:		
			gcc ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
