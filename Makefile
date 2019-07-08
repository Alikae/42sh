# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/05 17:18:13 by thdelmas          #+#    #+#              #
#    Updated: 2019/07/08 20:57:38 by thdelmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := 42sh
PROJECT := 42SH
RM = /bin/rm

### Directories ###
SRC_DIR := ./srcs
INC_DIR := ./includes
OBJ_DIR := ./.obj

### SUB FILES ###
SUB_DIRS := \
	command_line \
	command_edition \
	entrypoint \
	exitpoint \
	history \
	parameters \
	tokenizer \


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
FT_DIR = ./lib$(FT)
FT_INC_DIR = $(FT_DIR)/includes
FT_LNK = -L$(FT_DIR) -l$(FT)

SHUTIL = shutil
SHUTIL_DIR = ./lib$(SHUTIL)
SHUTIL_INC_DIR = $(SHUTIL_DIR)/includes
SHUTIL_LNK = -L$(SHUTIL_DIR) -l$(SHUTIL)

###  CC && FLAGS ###
CC = clang
DEBUG_FLAGS = -g3
CFLAGS = \
		 $(addprefix -I ,$(INC_DIR) $(INC_SUB_DIRS) $(FT_INC_DIR) $(SHUTIL_INC_DIR)) \
		 $(DEBUG_FLAGS) \
		 #-Wall -Werror -Wextra

LFLAGS = -ltermcap \
		 -lncurses \
		 $(FT_LNK) \
		 $(SHUTIL_LNK)


.PHONY: all clean fclean re

all: hey_msg $(FT) $(SHUTIL) $(NAME) bye_msg

### Lib compil ###
$(FT): lib_msg
	@make -C $(FT_DIR)

$(SHUTIL): lib_msg
	@make -C $(SHUTIL_DIR)

### Mkdir obj ###
.ONESHELL:
$(OBJ_DIR): mkdir_msg
	mkdir -p $(OBJ_DIR) $(OBJ_SUB_DIRS)

### Compilation ###
.ONESHELL:
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) Makefile | compil_msg
	@$(CC) $(LFlAGS) $(CFLAGS) -o $@ -c $<
	@printf "$(BBLUE)$(@F)$(CLEAR) "

### Link ###
.ONESHELL:
$(NAME): $(OBJ_DIR) $(OBJ) | link_msg
	@$(CC) $(OBJ) $(LFLAGS) -o $(NAME)
	@printf "$(BBLUE)$@: Done.$(CLEAR)\n"

### Clean ###
.ONESHELL:
clean: clean_msg
	$(RM) -rf $(OBJ_DIR)
	@make -C $(FT_DIR) clean
	@make -C $(SHUTIL_DIR) clean

.ONESHELL:
fclean: clean fclean_msg
	$(RM) -rf $(NAME)
	@make -C $(FT_DIR) fclean
	@make -C $(SHUTIL_DIR) fclean

re: fclean all

### INCLUDE TOOLS MAKEFILE ###
include ./tools.mk
