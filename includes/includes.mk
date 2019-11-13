# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    includes.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/30 14:33:36 by thdelmas          #+#    #+#              #
#    Updated: 2019/11/13 12:28:00 by thdelmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### MAIN FILES ###
H_FILES = \
	sh_exitpoint.h \
	sh_history.h \
	sh_builtins.h \
	sh.h \
	sh_entrypoint.h \
	sh_tools.h \
	sh_command_line.h \
	sh_line.h \
	sh_command_edition.h \
	sh_env.h \
	sh_error.h \
	sh_word_expansion.h \
	sh_redirections.h \
	sh_job_control.h 

# SUPPA concat loop
H_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(H_FILES_$(SUB_DIR))))
