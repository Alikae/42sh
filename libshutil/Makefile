# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/19 17:23:30 by thdelmas          #+#    #+#              #
#    Updated: 2019/07/07 17:38:23 by thdelmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libshutil.a
PROJECT := LIBSHUtil
RM = /bin/rm

### Directories ###
SRC_DIR := ./srcs
INC_DIR := ./includes
OBJ_DIR := ./.obj

### SUB FILES ###
SUB_DIRS := \

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

### Lib ###
FT = ft
FT_DIR = ../lib$(FT)
FT_INC_DIR = $(FT_DIR)/includes
FT_LNK = -L$(FT_DIR) -l$(FT)

###  CC && FLAGS ###
CC = clang
CFLAGS = \
		 $(addprefix -I ,$(INC_DIR) $(INC_SUB_DIRS) $(FT_INC_DIR)) \
		 # -Wall -Werror -Wextra

LFLAGS = \
		 $(FT_LNK)

.PHONY: all clean fclean re


all: hey_msg $(FT) $(NAME) bye_msg

### Lib compil ###
$(FT): lib_msg
	@make -C $(FT_DIR)

### Mkdir obj ###
.ONESHELL:
$(OBJ_DIR): mkdir_msg
	mkdir -p $(OBJ_DIR) $(OBJ_SUB_DIRS)

### Compilation ###
.ONESHELL:
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) Makefile | compil_msg
	@printf "$(BBLUE)$(@F): $(CLEAR)"
	$(CC) $(LFlAGS) $(CFLAGS) -o $@ -c $<
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
