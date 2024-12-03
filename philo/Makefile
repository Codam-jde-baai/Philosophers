NAME := philo
CC := gcc
CFLAGS := -Wall -Wextra -Werror -pthread
INCLUDE := -I./include
SRC := main.c utils.c read_input.c structs.c threads.c actions.c monitor.c
SRC_PATH := $(addprefix ./src/, $(SRC))
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

# Debug flags
DEBUG_CFLAGS := -g
# valgrind --tool=helgrind
# valgrind --leak-check=full

all: $(NAME)

$(NAME): $(OBJ)
	@echo " -- COMPILING philo -- "
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo " -- SUCCESS -- "

$(OBJ_DIR)/%.o: ./src/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $^

debug: CFLAGS += $(DEBUG_CFLAGS)
debug: fclean all

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug