# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maboye <maboye@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/16 17:21:54 by thdelmas          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2019/05/11 17:16:26 by thdelmas         ###   ########.fr        #
=======
#    Updated: 2019/05/11 14:48:03 by maboye           ###   ########.fr        #
>>>>>>> master
#                                                                              #
# **************************************************************************** #

NAME := 21sh
PROJECT := 21SH
RM = /bin/rm

### Directories ###
SRC_DIR := ./srcs
INC_DIR := ./includes
OBJ_DIR := ./.obj

### SUB FILES ###
SUB_DIRS := \
	signals \
	tools \
	entrypoint \
	command_line \
	command_edition \
	tokenizer

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
FT_DIR = ./libft
FT_LIB = $(addprefix $(FT_DIR)/,libft.a)
FT_INC = -I ./libft
FT_LNK = -L ./libft -l ft


###  CC && FLAGS ###
CC = gcc
CFLAGS = $(FT_INC) \
		 $(addprefix -I ,$(INC_DIR) $(INC_SUB_DIRS)) \
		 #-Wall -Werror -Wextra

LFLAGS = -ltermcap \
		 -lncurses \
		 $(FT_LNK)


.PHONY: all clean fclean re

all: hey_msg $(FT_LIB) $(NAME) bye_msg

### Lib compil ###
$(FT_LIB): lib_msg
	@make -C $(FT_DIR)

### Mkdir obj ###
.ONESHELL:
$(OBJ_DIR): mkdir_msg
	mkdir -p $(OBJ_DIR) $(OBJ_SUB_DIRS)

### Compilation ###
.ONESHELL:
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) Makefile | compil_msg
	$(CC) $(LFlAGS) $(CFLAGS) -o $@ -c $<

### Link ###
.ONESHELL:
$(NAME): $(OBJ_DIR) $(OBJ) | link_msg
	$(CC) $(LFLAGS) $(OBJ) -o $(NAME)

.ONESHELL:
test: all
	./$(NAME)

### Clean ###
.ONESHELL:
clean: clean_msg
	$(RM) -rf $(OBJ_DIR)
	@make -C $(FT_DIR) clean

.ONESHELL:
fclean: clean fclean_msg
	$(RM) -rf $(NAME)
	@make -C $(FT_DIR) fclean

re: fclean all

### INCLUDE TOOLS MAKEFILE ###
include ./tools.mk
