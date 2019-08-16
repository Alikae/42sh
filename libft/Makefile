# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/12 15:20:07 by thdelmas          #+#    #+#              #
#    Updated: 2019/08/12 15:39:14 by thdelmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a
PROJECT := LIBFT
RM = /bin/rm

### Directories ###
SRC_DIR := ./srcs
INC_DIR := ./includes
OBJ_DIR := ./.obj

### SUB FILES ###
SUB_DIRS := \
	conv \
	int \
	opt \
	lst \
	math \
	mem \
	str \
	print \
	tab_str

### INCLUDE SRC MAKEFILE ###
include $(SRC_DIR)/sources.mk

### INCLUDE INC MAKEFILE ###
include $(INC_DIR)/includes.mk


### ALL SUB DIRS ###
SRC_SUB_DIRS = $(addprefix $(SRC_DIR)/,$(SUB_DIRS))
OBJ_SUB_DIRS = $(addprefix $(OBJ_DIR)/,$(SUB_DIRS))
INC_SUB_DIRS = $(addprefix $(INC_DIR)/,$(SUB_DIRS))


### MAIN AND SUB FILES ###
O_FILES = $(C_FILES:.c=.o)


### Full Paths ###
SRC = $(addprefix $(SRC_DIR)/,$(C_FILES))
OBJ = $(addprefix $(OBJ_DIR)/,$(O_FILES))
INC = $(addprefix $(INC_DIR)/,$(H_FILES))


###  CC && FLAGS ###
CC = clang
DEBUG_FLAGS= -g3
CFLAGS = $(addprefix -I ,$(INC_DIR) $(INC_SUB_DIRS)) \
		 $(DEBUG_FLAGS) \
		 -Wall -Werror -Wextra


LFLAGS = \


.PHONY: all clean fclean re

all: hey_msg $(FT_LIB) $(NAME) bye_msg

### Mkdir obj ###
.ONESHELL:
$(OBJ_DIR): mkdir_msg
	mkdir -p $(OBJ_DIR) $(OBJ_SUB_DIRS)

### Compilation ###
.ONESHELL:
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) Makefile | compil_msg
	@printf "$(BBLUE)$(@F): $(CLEAR)"
	@$(CC) $(LFlAGS) $(CFLAGS) -o $@ -c $<
	@printf "$(BBLUE)Done !$(CLEAR)\n"

### Link ###
.ONESHELL:
$(NAME): $(OBJ_DIR) $(OBJ) | link_msg
	@ar rcs $(NAME) $(OBJ)
	@printf "$(BBLUE)$@: Done.$(CLEAR)\n"

.ONESHELL:
test: re
	./$(NAME)

### Clean ###
.ONESHELL:
clean: clean_msg
	$(RM) -rf $(OBJ_DIR)

.ONESHELL:
fclean: clean fclean_msg
	$(RM) -rf $(NAME)

re: fclean all

### INCLUDE TOOLS MAKEFILE ###
include ./tools.mk
