# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maboye <maboye@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/30 14:33:15 by thdelmas          #+#    #+#              #
#    Updated: 2019/05/11 20:45:09 by thdelmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### MAIN FILES ###
C_FILES = \
	main.c \

C_FILES_entrypoint = \
	sh_entrypoint.c \
	sh_free.c \
	sh_init.c \
	sh_init_envp.c \
	sh_loop.c

C_FILES_command_line = \
	sh_free_all_ln.c \
	sh_free_one_ln.c \
	sh_command_line.c \
	sh_init_ln.c \
	sh_command_parse.c \
	sh_strsplit_m.c

C_FILES_command_edition = \
	sh_command_functions.c \
	sh_reader.c \
	sh_cursor_motion.c \
	sh_cursor_motion2.c \
	sh_cursor_motion_word.c

C_FILES_tokenizer = \
	sh_print_onetok.c \
	sh_print_alltok.c \
	sh_init_tok.c \
	sh_match_tok_op.c \
	sh_set_toktype.c \
	sh_tokenizer.c

C_FILES_signals = \
	signals_handler.c

C_FILES_tools = \
	envp_tools.c \
	list_tools.c \
	utils.c


# SUPPA concat loop
C_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(C_FILES_$(SUB_DIR))))
