NAME		= miniRT

SGNL		= get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
SLIB		= libft/libftutils.c libft/libftutils2.c libft/libftutils3.c libft/libftutils4.c

SRCS		= main/main.c \
			main/set_objs.c \
			main/raytrace.c \
			main/create_img.c \
			main/events.c \
			main/events2.c \
			main/hooks.c \
			main/save_bmp.c \
			main/skybox.c \
			collisions/collision.c \
			collisions/collision2.c \
			collisions/collisionany.c \
			collisions/fill_rescl.c \
			collisions/disruptions.c \
			collisions/vectop.c \
			collisions/vectop2.c \
			collisions/rgb_op.c \
			parse/parse_file.c \
			parse/parseutils.c \
			parse/parseutils2.c \
			parse/add_elem.c \
			parse/add_elem2.c \
			parse/add_elem3.c \
			parse/add_elem4.c \
			${SLIB} ${SGNL}

SRCSS		= ${addprefix srcs/, ${SRCS}}

OBJS		= ${SRCSS:.c=.o}

HEADERS		= includes/basics.h \
			includes/elems.h \
			includes/libftutils.h \
			includes/parse.h \
			includes/minirt.h \
			srcs/get_next_line/get_next_line.h

OPENGL		= -lXext -lX11 -lm -lbsd
CFLAGS		= -Wall -Wextra -Werror -Iincludes -Imlx_linux -lpthread -O0 -g 

all:		${NAME}

$(NAME):	${OBJS} ${HEADERS}
			make -C mlx_linux
			gcc -o ${NAME} ${OBJS} ${CFLAGS} mlx_linux/libmlx.a $(OPENGL)

.c.o:		
			gcc ${CFLAGS} $(OPENGL) -c $< -o ${<:.c=.o}

clean:
			make -C mlx_linux clean
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
