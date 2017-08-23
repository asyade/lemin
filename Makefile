CC = gcc

NAME = lem-in

PATH_SRC = srcs

DIRS =	obj/lemin \
		obj/parser \
		obj/pathfind \

SRC = srcs/lemin.c \
		srcs/lemin_free.c \
		srcs/lemin_play.c \
		srcs/parser/pr_utils.c \
		srcs/parser/pr_rooms.c \
		srcs/parser/pr_pipes.c \
		srcs/parser/pr_check.c \
		srcs/parser/parser.c \
		srcs/parser/reader.c \
		srcs/pathfind/pf_find_path.c \
		srcs/pathfind/pf_utils.c \

OBJ = $(patsubst $(PATH_SRC)/%.c, obj/%.o, $(SRC))

FLAGS = -g3 -Wall -Wextra -Werror

LIBS = -L./libft -lft

HEADERS = -I includes/ -I libft/includes

DEPTHS = Makefile includes/structs.h includes/lemin.h libft/includes/libft.h

.SILENT :

all : $(NAME)

$(NAME) : $(OBJ)
	make -C libft/
	$(CC) $(OBJ) libft/libft.a -o $(NAME) $(HEADERS) $(FLAGS)
	echo "\033[33mCreating  \033[32m[✔] \033[0m$(NAME)"

obj/%.o : $(PATH_SRC)/%.c $(DEPTHS)
	mkdir -p $(DIRS)
	$(CC) -c $< -o $@ $(HEADERS) $(FLAGS)
	echo "\033[33mCompiling \033[32m[✔] \033[0m$<"

.PHONY : clean fclean

clean :
	make -C libft/ clean
	/bin/rm -rf obj/
	echo "\033[31mRemoving  \033[32m[✔] \033[0mObject files"

fclean : clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)
	echo "\033[31mRemoving  \033[32m[✔] \033[0m$(NAME)"

re : fclean all
