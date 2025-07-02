# === COLORS ===
RED=\033[1;31m
YELLOW=\033[1;33m
ORANGE=\033[1;38;5;214m
GREEN=\033[1;32m
CYAN=\033[1;36m
RESET=\033[0m

# === NAME ===
NAME = philo

# === VALGRIND FLAGS ===
VAL = valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
	--track-origins=yes

# === COMPILATION ===
CC = cc
CFLAGS =  -Wall -Werror -Wextra -I$(INCLUDES) -g
OBJDIR = build

# === INCLUDES ===
INCLUDES = include/

# === SRC PATH ===
SRC = src

# === MODULE DIRS ===
DIR_BUILT_INS = built_ins
DIR_GENERAL = .
DIR_EXEC = exec
DIR_PARSE = parse
DIR_UTILS = utils

# === FILES ===
SRC_GENERAL = main.c

SRC_EXEC	= routine.c

SRC_PARSE	= parser.c checkers.c ft_strtol.c

SRC_UTILS	= constructors.c cleaners.c utils.c

SRCS_DIR =	$(addprefix $(SRC)/, $(addprefix $(DIR_GENERAL)/, $(SRC_GENERAL))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_EXEC)/, $(SRC_EXEC))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_PARSE)/, $(SRC_PARSE))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_UTILS)/, $(SRC_UTILS)))

OBJS_DIR = $(addprefix $(OBJDIR)/, $(SRCS_DIR:$(SRC)/%.c=%.o))

# === RULES ===
all: $(NAME)

$(NAME): $(OBJS_DIR)
	@echo "$(YELLOW)Compiling $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS_DIR) -o $(NAME)
	@echo "$(GREEN)Done!$(RESET)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRC)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Removing objects$(RESET)"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "$(RED)Removing $(NAME)$(RESET)"
	@rm -rf $(NAME)

re: fclean all
	@echo "$(ORANGE)Re-Done!!$(RESET)"

.PHONY: all clean fclean re
