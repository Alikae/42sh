# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/19 17:24:14 by ede-ram          #+#    #+#              #
#    Updated: 2019/08/06 01:37:25 by ede-ram         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### MAIN FILES ###
C_FILES = \
	sh_basename.c \
	sh_false.c \
	sh_set.c \
	sh_cd.c \
	sh_true.c

C_FILES_tools = \
	sh_are_you_sur.c \
	sh_check_path.c \
	sh_error_path.c \
	sh_getopt.c
	#sh_find_law.c
	#sh_add_to_path.c

# SUPPA concat loop
C_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(C_FILES_$(SUB_DIR))))
