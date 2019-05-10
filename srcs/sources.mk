# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/30 14:33:15 by thdelmas          #+#    #+#              #
#    Updated: 2019/05/10 17:59:08 by thdelmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### MAIN FILES ###
C_FILES = \
	main.c \

C_FILES_entrypoint = \
	sh_free_sh.c \
	sh_entrypoint.c \
	sh_init_sh.c

C_FILES_command_line = \
	sh_free_all_ln.c \
	sh_free_one_ln.c \
	command_line.c \
	sh_init_ln.c \
	command_parse.c \
	sh_strsplit_m.c

C_FILES_command_edition = \
	command_functions.c \
	reader.c \
	cursor_motion.c \
	cursor_motion2.c \
	cursor_motion_word.c

C_FILES_tokenizer = \
	sh_print_onetok.c \
	sh_print_alltok.c \
	sh_init_tok.c \
	sh_match_tok_op.c \
	sh_get_tok_type.c \
	sh_tokenizer.c


# SUPPA concat loop
C_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(C_FILES_$(SUB_DIR))))
