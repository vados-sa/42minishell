# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/05 14:44:55 by vados-sa          #+#    #+#              #
#    Updated: 2024/10/08 18:53:30 by vados-sa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -Iincludes -g
LDFLAGS	= -lreadline
RM		= rm -rf

# Paths
OBJDIR = ./objects
SRCDIR = ./src
LEXING_DIR = $(SRCDIR)/1_lexing
PARSING_DIR = $(SRCDIR)/2_parsing
EXECUTION_DIR = $(SRCDIR)/3_execution
BUILTINS_DIR = $(EXECUTION_DIR)/builtins
UTILS_DIR = $(SRCDIR)/utils
LIBFT_DIR = ./libs/libft
GNL_DIR = ./libs/get_next_line
HEADERS_DIR = ./includes
LIBFT = libft.a
GNL = libgnl.a

# Soure files
SRC = $(SRCDIR)/main.c $(SRCDIR)/init.c $(SRCDIR)/signals.c $(SRCDIR)/signals_heredoc.c \
	$(LEXING_DIR)/checker.c $(LEXING_DIR)/handler.c \
	$(LEXING_DIR)/lex.c $(LEXING_DIR)/token.c \
	$(PARSING_DIR)/command.c $(PARSING_DIR)/concat_expanded_vars.c \
	$(PARSING_DIR)/parser_utils.c \
	$(PARSING_DIR)/expander.c $(PARSING_DIR)/handle_arg_for_export.c \
	$(PARSING_DIR)/arg_for_export_utils.c $(PARSING_DIR)/open_io.c\
	$(PARSING_DIR)/handle_heredoc.c $(PARSING_DIR)/fd_utils.c \
	$(PARSING_DIR)/organize_final_cmd_array.c \
	$(PARSING_DIR)/parse.c $(PARSING_DIR)/split_token.c $(EXECUTION_DIR)/builtin_exec.c \
	$(BUILTINS_DIR)/cd.c $(BUILTINS_DIR)/echo.c \
	$(BUILTINS_DIR)/env.c $(BUILTINS_DIR)/exit.c $(BUILTINS_DIR)/export.c \
	$(BUILTINS_DIR)/pwd.c $(BUILTINS_DIR)/unset.c $(EXECUTION_DIR)/command_exec.c \
	$(BUILTINS_DIR)/builtins_utils.c \
	$(EXECUTION_DIR)/paths.c $(EXECUTION_DIR)/exec.c \
	$(EXECUTION_DIR)/pipe.c $(EXECUTION_DIR)/close_fd.c \
	$(UTILS_DIR)/free.c $(UTILS_DIR)/free_structures.c $(UTILS_DIR)/print_message.c $(UTILS_DIR)/utils.c

# Object files
OBJS = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

# Building executables
$(NAME): $(OBJS)
	@make --no-print-directory bonus -C $(LIBFT_DIR) > /dev/null 2>&1
	@make --no-print-directory -C $(GNL_DIR) > /dev/null 2>&1
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -I$(HEADERS_DIR) $(LIBFT_DIR)/$(LIBFT) $(GNL_DIR)/$(GNL) -o $(NAME) 2>/dev/null
	@echo "\033[32;1mMalu' and Vanessa's Minishell is ready to roll\033[5m ✓ ✓ ✓\033[0m"

# Compilation rule for object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

# Cleanup
clean:
	@$(RM) $(OBJDIR)
	@make --no-print-directory -C ${LIBFT_DIR} clean
	@make --no-print-directory -C ${GNL_DIR} clean
	@echo "\033[37;1mObject files removed.\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@make --no-print-directory -C ${LIBFT_DIR} fclean
	@make --no-print-directory -C ${GNL_DIR} fclean
	@echo "\033[37;1mExecutable removed.\033[0m"

re: fclean all

.PHONY: all clean fclean re
