# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/05 17:18:13 by thdelmas          #+#    #+#              #
#    Updated: 2019/11/16 04:15:51 by ede-ram          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := 42sh
PROJECT := 42SH
AUTHORS := Ede-ram Tcillard Thdelmas Tmeyer

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
	builtins \
	builtins/echo \
	exitpoint \
	history \
	parameters \
	tokenizer \
	executer \
	tokens \
	error \
	redirections \
	debug_mode \
	tools \
	word_expansion \
	job_control


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

###  CC && FLAGS ###
CC = clang -g
DEBUG_FLAGS = -g3
CFLAGS = \
		 $(addprefix -I ,$(INC_DIR) $(INC_SUB_DIRS) $(FT_INC_DIR)) \
		 -Wall -Werror -Wextra

LFLAGS = -ltermcap \
		 -lncurses \
		 $(FT_LNK) \



.PHONY: all clean fclean re

all: $(FT) $(NAME) bye_msg

### Lib compil ###
$(FT): | lib_msg
	@make -C $(FT_DIR)

### Mkdir obj ###
$(OBJ_DIR): | mkdir_msg
	@mkdir -p $(OBJ_DIR) $(OBJ_SUB_DIRS)

### Compilation ###
.ONESHELL:
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) $(MAKEFILE_LIST) | compil_msg
	@echo "$(SCURSOR)$(@F) \c"
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "$(RCURSOR)$(ERASEL)\c"

### Link ###
.ONESHELL:
$(NAME): $(OBJ_DIR) $(OBJ) $(INC) $(MAKEFILE_LIST) $(FT_DIR)/libft.a | link_msg
	@$(CC) $(OBJ) $(LFLAGS) -o $(NAME)
	@printf "$@: Done !\n"

### Clean ###
$(FT)_clean: | lib_msg
	@make -C $(FT_DIR) clean

clean: $(FT)_clean | clean_msg
	$(RM) -rf $(OBJ_DIR)

$(FT)_fclean: | lib_msg
	@make -C $(FT_DIR) fclean

fclean: $(FT)_fclean | fclean_msg
	$(RM) -rf $(OBJ_DIR)
	$(RM) -rf $(NAME).dSYM
	$(RM) -rf $(NAME)

re: fclean all

### INCLUDE TOOLS MAKEFILE ###
include ./tools.mk
