# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maboye <maboye@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/30 14:33:15 by thdelmas          #+#    #+#              #
#    Updated: 2020/01/13 12:54:16 by tmeyer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### MAIN FILES ###
C_FILES = \

C_FILES_conv = \
	ft_atoi.c \
	ft_itoa.c

C_FILES_int = \
	ft_is_prime.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isblank.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_isspace.c \
	ft_isxdigit.c \
	ft_tolower.c \
	ft_toupper.c

C_FILES_lst = \
	ft_lstadd.c \
	ft_lstdel.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_lstnew.c

C_FILES_math = \
	ft_factorial.c \
	ft_power.c \
	ft_sqrt.c

C_FILES_mem = \
	ft_bzero.c \
	ft_memalloc.c \
	ft_memccpy.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memdel.c \
	ft_memmove.c \
	ft_memset.c

C_FILES_print = \
	ft_putchar.c \
	ft_putchar_fd.c \
	ft_putendl.c \
	ft_putendl_fd.c \
	ft_putnbr.c \
	ft_putnbr_fd.c \
	ft_putstr.c \
	ft_putstr_fd.c

C_FILES_str = \
	ft_match.c \
	ft_nmatch.c \
	ft_str_dupsize.c \
	ft_strcat.c \
	ft_strchr.c \
	ft_strclen.c \
	ft_strclr.c \
	ft_strcmp.c \
	ft_strcpy.c \
	ft_strdel.c \
	ft_strdup.c \
	ft_strequ.c \
	ft_striter.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strjoin_free.c \
	ft_strlcat.c \
	ft_strlen.c \
	ft_strmap.c \
	ft_strmapi.c \
	ft_strncat.c \
	ft_strncmp.c \
	ft_strncpy.c \
	ft_strndup.c \
	ft_strnequ.c \
	ft_strnew.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strsplit.c \
	ft_strstr.c \
	ft_strsub.c \
	ft_strtrim.c \
	ft_strncmp_n.c \
	ft_strlen_w.c \
	ft_strconv.c \
	ft_to_lower.c

C_FILES_tab_str = \
	ft_tab_strdel.c \
	ft_free_tabstr.c \
	sh_tab_realloc.c \
	ft_tab_strdup.c

C_FILES_print = \
	ft_putchar.c \
	ft_putchar_fd.c \
	ft_putendl.c \
	ft_putendl_fd.c \
	ft_putnbr.c \
	ft_putnbr_fd.c \
	ft_putstr.c \
	ft_putstr_fd.c

C_FILES_opt = \
	ft_getopt.c \
	ft_fetch_opt.c \
	ft_free_opts.c \
	ft_create_opt.c \
	ft_print_opt.c

# SUPPA concat loop
C_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(C_FILES_$(SUB_DIR))))
