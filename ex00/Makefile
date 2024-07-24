NAME =  btc
CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS =	main.cpp\
		BitcoinExchange.cpp\
		loadCsv.cpp\
		loadInput.cpp\
		parsingUtils.cpp

OBJ_DIR = objs

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:%.cpp=%.o))

# Colors
_BLUE=	$'\033[34m'
_WHITE=	$'\033[37m'

all: $(NAME)

show:
	@echo "$(_BLUE)SRCS :\n$(_BLUE)$(SRCS) $(_WHITE)"
	@echo "$(_BLUE)SRCS_DIR :\n$(_BLUE)$(SRCS_DIR) $(_WHITE)"
	@echo "$(_BLUE)OBJS :\n$(_BLUE)$(OBJS) $(_WHITE)"
	@echo "$(_BLUE)OBJ_DIR :\n$(_BLUE)$(OBJS_DIR) $(_WHITE)"
	@echo "$(_BLUE)CFLAGS :\n$(_BLUE)$(CFLAGS)$(_WHITE)"

$(OBJ_DIR)/%.o : %.cpp
	@echo -n "Compiling $(_BLUE)$@$(_WHITE) ... "
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c -D FT=false $<
	@echo "$(_BLUE)DONE$(_WHITE)"

$(NAME):	$(INC_DIR) $(OBJS) Makefile
	@echo -n "-----\nCreating Executable $(_BLUE)$@$(_WHITE) ... 🕊️"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(_BLUE)DONE$(_WHITE)\n-----"

exec: $(NAME)
	@echo "Launch Binary File $(_BLUE)$(NAME)$(_WHITE)\n-----"
	@./$(NAME)
	@echo "-----\n$(_BLUE)$(NAME) $(_BLUE)successfully end$(_WHITE)\n-----"

re: fclean all

clean:
	@echo -n "$(_WHITE)Deleting Objects Directory $(_BLUE)$(OBJ_DIR)" \
	"$(_WHITE) ... "
	@rm -rf $(OBJ_DIR)
	@echo "$(_BLUE)DONE$(_WHITE)\n-----"

fclean: clean
	@echo -n "Deleting Binaries Files $(_BLUE)$(NAME)" \
	"$(_WHITE) ... "
	@rm -f $(NAME)
	@echo "$(_BLUE)DONE$(_WHITE)\n-----"

.PHONY: all re clean fclean
