DIR_INC = ./includes/

DIR_SRCS = ./srcs/

FUNC = 	scene/camera.c scene/light.c \
	  	utils/vector.c utils/vector2.c utils/gnl.c utils/error.c utils/ato_pars.c utils/math.c \
	  	scene/scene.c scene/plane.c scene/sphere.c scene/triangle.c scene/square.c scene/cylinder.c \
		main.c \
		utils/color.c \
		parser/parser.c parser/parser_object_scene.c parser/parser_object_figure.c \
		ray_tracing/ray_tracing.c \
		ray_tracing/intersect/intersect_object.c ray_tracing/intersect/intersect_plane.c ray_tracing/intersect/intersect_sphere.c \
		ray_tracing/intersect/intersect_triangle.c ray_tracing/intersect/intersect_square.c ray_tracing/intersect/intersect_cylinder.c ray_tracing/lighting/lighting.c

SRCS = $(addprefix $(DIR_SRCS), $(FUNC))

OBJS = $(SRCS:.c=.o)

NAME = miniRT

LIBMLX = libmlx.dylib

GCC = gcc
FLAGS =  -g

%.o: %.c
	$(GCC) $(FLAGS) -I $(DIR_INC) -c $< -o $@

$(NAME): $(OBJS)
	make -C ./minilibx_mms_20200219
	cp ./minilibx_mms_20200219/libmlx.dylib .
	$(GCC) $(FLAGS) -I $(DIR_INC) $(LIBMLX) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all


