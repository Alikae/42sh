# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maboye <maboye@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/30 14:33:15 by thdelmas          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2019/05/13 14:49:28 by tmeyer           ###   ########.fr        #
=======
#    Updated: 2019/05/13 15:47:25 by thdelmas         ###   ########.fr        #
>>>>>>> thdelmas
#                                                                              #
# **************************************************************************** #

### MAIN FILES ###
C_FILES = \
	main.c \
	sh.c

C_FILES_command_edition = \
	sh_command_functions.c \
	sh_reader.c \
	sh_cursor_motion.c \
	sh_cursor_motion2.c \
	sh_cursor_motion_word.c \
	sh_cursor_motion_line.c

C_FILES_command_line = \
	sh_prompt.c \
	sh_free_all_ln.c \
	sh_free_one_ln.c \
	sh_command_line.c \
	sh_init_ln.c \
	sh_command_parse.c \
	sh_strsplit_m.c

C_FILES_entrypoint = \
	sh_entrypoint.c \
	sh_free.c \
	sh_init.c \
	sh_loop.c

C_FILES_signals = \
	signals_handler.c

C_FILES_tokenizer = \
	sh_print_onetok.c \
	sh_print_alltok.c \
	sh_init_tok.c \
	sh_match_tok_op.c \
	sh_set_toktype.c \
	sh_tokenizer.c

C_FILES_env = \
	sh_init_env.c \
	sh_init_var.c \
	sh_get_env.c \
	sh_set_env.c \
	sh_set_value.c \
	sh_get_value.c \
	sh_set_pwd.c \
	sh_set_shlvl.c \
	sh_print_env.c \
	sh_fill_env.c \

C_FILES_tools = \


# SUPPA concat loop
C_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(C_FILES_$(SUB_DIR))))
