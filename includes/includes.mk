# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    includes.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/30 14:33:36 by thdelmas          #+#    #+#              #
#    Updated: 2019/07/11 01:54:26 by ede-ram          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### MAIN FILES ###
H_FILES = \
	history.h \
	sh.h

### SUB FILES ###
H_FILES_entrypoint = \
	sh_entrypoint.h

H_FILES_tools = \
	sh_tools.h

H_FILES_command_line = \
	sh_command_line.h \
	sh_line.h

H_FILES_command_edition = \
	sh_command_edition.h

H_FILES_parameters = \
	sh_env.h

H_FILES_tokens = \
	t_token.h

H_FILES_error = \
	error.h

H_FILES_redirections = \
	redirections.h

# SUPPA concat loop
H_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(H_FILES_$(SUB_DIR))))
