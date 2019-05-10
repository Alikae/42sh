# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/30 14:33:15 by thdelmas          #+#    #+#              #
#    Updated: 2019/05/10 19:15:17 by thdelmas         ###   ########.fr        #
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
	sh_get_tok_type.c \
	sh_tokenizer.c


# SUPPA concat loop
C_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(C_FILES_$(SUB_DIR))))
