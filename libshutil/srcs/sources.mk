# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/19 17:24:14 by thdelmas          #+#    #+#              #
#    Updated: 2019/07/10 04:34:58 by thdelmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### MAIN FILES ###
C_FILES = \
	sh_basename.c \
	sh_false.c \
	sh_set.c \
	sh_true.c

C_FILES_tools = \
	sh_are_you_sur.c \
	sh_check_path.c \
	sh_error_path.c \
	#sh_find_law.c
	#sh_add_to_path.c

# SUPPA concat loop
C_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(C_FILES_$(SUB_DIR))))
