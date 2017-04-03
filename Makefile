NAME =  libftprintf.a

SRC =	ft_printf.c \
	change.c \
	check.c \
	check_flags.c \
	check_width.c \
	check_size.c \
	find.c \
	flags.c \
	accuracy.c \
	check_accuracy.c \
	proc.c \
	ft_itoa_base.c \
	ft_print.c \
	wchar.c \
	long.c

HDR = ft_printf.h

OBJ = $(SRC:.c=.o)

DEL = rm -rf

all: $(NAME)

$(NAME) : $(OBJ)
	    make -C libft
		ar -cru $(NAME) $(OBJ) libft/*.o
		ranlib $(NAME)
%.o: %.c
		gcc -c -o $@ $<
clean:
		make clean -C ./libft
		$(DEL) $(OBJ)
fclean: clean
		make fclean -C ./libft
		$(DEL) $(NAME)
re: fclean all
		make re -C ./libft