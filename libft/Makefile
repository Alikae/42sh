# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/16 17:21:54 by thdelmas          #+#    #+#              #
#    Updated: 2019/05/05 17:21:36 by thdelmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
PROJECT = LIBFT

### Directories ###
SRC_DIR = .
INC_DIR = .
OBJ_DIR = ./.obj

###  CC && FLAGS ###
CC = clang
CFLAGS = -Wall -Werror -Wextra

### FILES ###
C_FILES = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
		  ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strndup.c \
		  ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c \
		  ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c \
		  ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
		  ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c \
		  ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c \
		  ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c \
		  ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c \
		  ft_putchar.c ft_putchar_fd.c ft_putstr.c ft_putstr_fd.c \
		  ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c \
		  ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
		  ft_is_prime.c ft_sqrt.c ft_power.c ft_str_dupsize.c ft_factorial.c \
		  ft_joinfree.c ft_lstmap.c ft_2d_chardup.c ft_free_2d_char.c \
		  ft_isblank.c ft_isxdigit.c ft_isspace.c

O_FILES = $(C_FILES:%.c=%.o)

H_FILES = libft.h \

### Full Paths ###
SRC = $(addprefix $(SRC_DIR)/,$(C_FILES))
OBJ = $(addprefix $(OBJ_DIR)/,$(O_FILES))
INC = $(addprefix $(INC_DIR)/,$(H_FILES))

### Colors ###
BRED = \033[0;31;40m
BGREEN = \033[0;32;40m
BBLUE = \033[0;36;40m
WHITE = \033[0m
CYAN = \033[36m
GREEN = \033[1m\033[32m
WRED = \033[96;41m
WBLUE = \033[31;44m
YELLOW = \033[33m
CLEAR = \033[0;0m

### Phony ###
.PHONY: all clean fclean re so hey compil

### Rules ###
all: hey $(NAME)
	@printf "$(BBLUE)\t- by THDELMAS -\t$(CLEAR)\n\n"

### Mkdir obj ###
.ONESHELL:
$(OBJ_DIR):
	@printf "$(BRED)\t- - MKDIR $(OBJ_DIR) -  -\t$(CLEAR)\n"
	@printf "$(BGREEN)"
	mkdir -p $(OBJ_DIR)
	@printf "$(CLEAR)"

### Compilation ###
.ONESHELL:
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) Makefile | $(OBJ_DIR) compil
	@printf "$(GREEN)"
	$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $(SRC_DIR)/$(patsubst %.o,%.c,$(@F))
	@printf "$(CLEAR)"

### Link ###
.ONESHELL:
$(NAME): $(OBJ)
	@printf "$(BRED)\t-  - LINK -  -\t$(CLEAR)\n"
	@printf "$(GREEN)"
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	@printf "$(CLEAR)"

### Linux ###
.ONESHELL:
so:
	@printf "$(BRED)\t-  - LINUX -  -\t$(CLEAR)\n"
	@printf "$(GREEN)"
	cc -shared -o $(patsubst %.a, %.so, $(NAME)) -fPIC $(FILES)
	@printf "$(CLEAR)"

### Clean ###
.ONESHELL:
clean:
	@printf "$(BRED)\t-  - CLEAN -  -\t$(CLEAR)\n"
	@printf "$(GREEN)"
	rm -rf $(OBJ_DIR)
	@printf "$(CLEAR)"

.ONESHELL:
fclean: clean
	@printf "$(BRED)\t-  - FCLEAN -  -\t$(CLEAR)\n"
	@printf "$(GREEN)"
	rm -rf $(NAME)
	@printf "$(CLEAR)"

re: hey fclean all

### Tools ###
hey:
	@printf "$(BBLUE)\t-  - $(PROJECT) -  - \t$(CLEAR)\n"

compil:
	@printf "$(BRED)\t-  - COMPIL -  -\t$(CLEAR)\n"

### git-autosave ###
savegit: gitsave
gitsave: hey fclean
	@printf "$(BBLUE)\t-  - GIT SAVE FOR YOU	-  -\t$(CLEAR)\n"
	@printf "$(BRED)\t-  - SRC INCLUDES LIBFT MAKEFILE	-  -\t$(CLEAR)\n"
	@printf "$(GREEN)"
	@git add .
	@printf "GIT AUTO-SAVE !"
	@sleep 0.5
	@git commit -m "auto-save"
	@printf "$(CLEAR)"
	@git push

### Norminette ###
norm:
	@printf "$(BRED)\t-  - NORM 42	-  -\t$(CLEAR)\n"
	@printf "$(BRED)\t-  - SRC INCLUDES LIBFT MAKEFILE	-  -\t$(CLEAR)\n"
	@printf "$(GREEN)"
	@norminette -R CheckForbiddenSourceHeader $(HEADER) $(SRC_NAME)
	@printf "$(CLEAR)"
