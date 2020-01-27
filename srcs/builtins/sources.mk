/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
