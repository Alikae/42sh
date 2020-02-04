### MAIN FILES ###
H_FILES = \
	libft.h

### SUB FILES ###

# SUPPA concat loop
H_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(H_FILES_$(SUB_DIR))))
