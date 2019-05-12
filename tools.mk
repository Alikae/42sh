# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tools.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/28 17:25:36 by thdelmas          #+#    #+#              #
#    Updated: 2019/05/12 15:08:56 by thdelmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##################################### Tools ####################################

AUTHORS ?= Ede-Ram Tmeyer Thdelmas

### Colors ###
WHITE = \033[0m
CYAN = \033[36m
GREEN = \033[1m\033[32m
GRED = \033[30;41m
WRED = \033[96;41m
BRED = \033[0;31;40m
BBLUE = \033[0;36;40m
WBLUE = \033[31;44m
YELLOW = \033[33m
CLEAR = \033[0;0m

GITCOM ?= "Auto-Save"
GITSTATUS = $(shell git status | sed -n 2p | cut -d' ' -f4)
ADD_TO_NORME = $(SRC_DIR) $(INC_DIR) $(FT_DIR)

ADD_TO_GIT = $(SRC_DIR) $(INC_DIR) $(FT_DIR) $(GITLOG_FILE) \
			 Makefile tools.mk auteur README.md

.PHONY: hey link compil savegit gitsave norm


### git-autosave ###
savegit: gitsave

.ONESHELL:
gitsave: hey fclean
	@printf "\n$(BBLUE)\t GIT SAVE FOR YOU$(CLEAR)\n"
	@printf "$(BRED)\t $(ADD_TO_GIT)$(CLEAR)\n"
	@git add $(ADD_TO_GIT)
	@printf "\n$(BBLUE)\t GIT AUTO-SAVE ! : commit -m$(CLEAR)\n"
	@printf "$(BRED)\t COMMIT : \"$(GITCOM)\"$(CLEAR)\n"
	@sleep 0.5
	@-git commit -m "$(GITCOM)"
	@git push

### Norminette ###
.ONESHELL:
norm:
	@printf "\n$(BRED)\t NORM 42$(CLEAR)\n"
	@printf "$(BRED)\t $(ADD_TO_NORME)$(CLEAR)\n"
	@norminette -R CheckForbiddenSourceHeader $(HEADER) $(SRC_NAME)

### Messages rules ###
hey_msg:
	@printf "\n$(BBLUE)\t $(PROJECT)$(CLEAR)\n"

bye_msg:
	@printf "\n$(BBLUE)\t Made with love by:$(CLEAR)\n"
	@printf "$(BBLUE)\t $(AUTHORS)$(CLEAR)\n\n"

lib_msg:
	@printf "\n$(BRED)\t LIBS$(CLEAR)\n"

compil_msg:
	@printf "\n$(BRED)\t COMPIL$(CLEAR)\n"

link_msg:
	@printf "\n$(BRED)\t LINK$(CLEAR)\n"

mkdir_msg:
	@printf "\n$(BRED)\t MKDIR$(CLEAR)\n"

fclean_msg: hey_msg
	@printf "\n$(BRED)\t FCLEAN$(CLEAR)\n"

clean_msg: hey_msg
	@printf "\n$(BRED)\t CLEAN$(CLEAR)\n"
