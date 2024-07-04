NAME = minishell

CC			= cc
# Mac:
CFLAGS		= -Wall -Wextra -Werror -I/usr/local/opt/readline/include -fsanitize=address
LDFLAGS		= -L/usr/local/opt/readline/lib -lreadline
# Linux: 
#CFLAGS		= -Wall -Wextra -Werror -Iincludes -fsanitize=address
#LDFLAGS		= -lreadline
RM			= rm -rf

# Paths
OBJDIR = ./objects
SRCDIR = ./src

# Soure files
SRC = $(SRCDIR)/main.c $(SRCDIR)/signals.c

# Object files
OBJS = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

# Building executables
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)
	@echo "\033[32;1mMalu' and Vanessa's Minishell is ready to roll\033[5m✓ ✓ ✓\033[0m"
	@echo "\033[35;1mProgram $(NAME) is ready to run.\033[0m"


# Compilation rule for object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

# Cleanup
clean:
	@$(RM) $(OBJDIR)
	@echo "\033[37;1mObject files removed.\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[37;1mExecutable removed.\033[0m"

re: fclean all

.PHONY: all clean fclean re