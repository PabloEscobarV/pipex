NAME = pipex

SRCDIR = src
OBJDIR = obj
GNLDIR = get_next_line
LIBFTDIR = libft

LIBFT = ftfull
GNL = gnlfull
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CFLAGSO = -c -Wall -Wextra -Werror
COMPILFLAG = -L$(GNLDIR) -l$(GNL) -L$(LIBFTDIR) -l$(LIBFT)

.PHONY: all, re, clean, fclan

all: $(NAME)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(GNLDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	$(MAKE) -C $(GNLDIR) fclean

re_clean:
	rm -rf $(OBJDIR)

re_fclean: re_clean
	rm -f $(NAME)

re: re_fclean all

$(NAME): $(OBJ)
	$(MAKE) -C $(GNLDIR) bonus
	$(MAKE) -C $(LIBFTDIR) bonus
	$(CC) $(CFLAGS) $(OBJ) $(COMPILFLAG) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGSO) $< -o $@