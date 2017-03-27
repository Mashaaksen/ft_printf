
NAME = libftprintf.a
G = gcc
FLAG = -Wall -Wextra -Werror
SRC =	ft_printf.c \
		change.c \
		check.c \
		ft_itoa_base.c \
		ft_print.c \
		ft_printf.c \
		long.c
HDR = ft_printf.h
OBJ = $(SRC:.c=.o)
DEL = rm -f
all: $(NAME)
$(NAME) : $(OBJ)
		make -C libft
		ar -cru $(NAME) $(OBJ) libft/*.o
		ranlib $(NAME)
		@echo libftprintf.a is ALIVE!!!
%.o: %.c
		$(G) $(CFLAGS) -c -o $@ $<
clean:
		make clean -C ./libft
		$(DEL) $(OBJ)
		@echo OBJ_libftprintf is DEAD!!!
fclean: clean
		make fclean -C ./libft
		$(DEL) $(NAME)
		@echo libftprintf.a is DESTROYED!!!
re: fclean all
		make re -C ./libft
		@echo ALL DAMM FPS is DESTROYED!!!