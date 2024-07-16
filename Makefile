NAME = minishell

CC			= cc
# Mac:
CFLAGS		= -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include
LDFLAGS		= -L/opt/homebrew/opt/readline/lib -lreadline
#CFLAGS		= -Wall -Wextra -Werror -I/usr/local/opt/readline/include
#LDFLAGS		= -L/usr/local/opt/readline/lib -lreadline
# Linux: 
#CFLAGS		= -Wall -Wextra -Werror -Iincludes
#LDFLAGS	= -lreadline
RM			= rm -rf

# Paths
OBJDIR = ./objects
SRCDIR = ./src
LIBFT_DIR = ./libs/libft
GNL_DIR = ./libs/get_next_line
HEADERS_DIR = ./includes

LIBFT = libft.a
GNL = libgnl.a

# Soure files
SRC = $(SRCDIR)/main.c $(SRCDIR)/signals.c

# Object files
OBJS = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

# Building executables
$(NAME): $(OBJS)
	@make bonus -C $(LIBFT_DIR)
	@make -C $(GNL_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -I$(HEADERS_DIR) $(LIBFT_DIR)/$(LIBFT) $(GNL_DIR)/$(GNL) -o $(NAME) 
	@echo "\033[32;1mMalu' and Vanessa's Minishell is ready to roll\033[5m✓ ✓ ✓\033[0m"
	@echo "\033[35;1mProgram $(NAME) is ready to run.\033[0m"


# Compilation rule for object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

# Cleanup
clean:
	@$(RM) $(OBJDIR)
	@make -C ${LIBFT_DIR} clean
	@make -C ${GNL_DIR} clean
	@echo "\033[37;1mObject files removed.\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@make -C ${LIBFT_DIR} fclean
	@make -C ${GNL_DIR} fclean
	@echo "\033[37;1mExecutable removed.\033[0m"

re: fclean all

.PHONY: all clean fclean re