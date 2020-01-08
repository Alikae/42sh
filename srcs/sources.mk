# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/13 19:40:02 by thdelmas          #+#    #+#              #
#    Updated: 2020/01/07 03:38:39 by tcillard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### MAIN FILES ###
C_FILES = \
	  main.c \
	  destructor.c \
	  constructor.c \
	  sh.c \
	  sh_rc.c

C_FILES_entrypoint = \
	sh_entrypoint.c \
	sh_loop.c \
	sh_init_debug.c \
	sh_init_cmd.c \
	sh_init_opts.c \
	sh_init_env.c \
	sh_init_signals.c \
	sh_init_history.c \
	sh_set_shlvl.c \
	sh_init_path.c \
	sh_init.c

C_FILES_sh_printf = \
			sh_printf.c 

C_FILES_job_control = \
		      t_job.c \
		      job_control.c

C_FILES_exitpoint = \
		    sh_free_params.c \

C_FILES_parameters = \
		     sh_create_param.c \
		     sh_env_params.c \
		     sh_putparams.c \
		     sh_setev.c \
		     sh_getev_value.c \
		     sh_del_env.c \
		     sh_getev.c \
		     sh_unsetev.c \
		     sh_set_pwd.c \
		     sh_isset.c \
		     sh_debug_env.c \

C_FILES_command_edition = \
			  sh_command_functions.c \
			  sh_reader.c \
			  sh_cursor_motion.c \
			  sh_cursor_motion2.c \
			  sh_cursor_motion_word.c \
			  sh_cursor_motion_line.c \
			  sh_controls.c \
			  sh_buffer.c \
			  sh_copy_option.c

C_FILES_command_line = \
		       sh_prompt.c \
		       sh_command_line.c \

C_FILES_history = \
		  sh_get_next_line.c \
		  sh_21_history.c \
		  sh_history_2.c \
		  sh_cursor_history.c \
		  sh_strnjoin.c

C_FILES_signals = \

#signals_handler.c

C_FILES_tokenizer = \
	t_token.c \
	t_tokens_utils.c \
	read_n_skip_operator.c \
	compound_tokenizer_utils.c \
	compound_tokenizer_case_utils.c \
	compound_tokenizer_case_utils_2.c \
	read_here_doc.c \
	tokenize_input.c \
	tokenize_input_words.c \
	tokenize_input_funcs.c \
	tokenize_input_tools.c \
	tokenize_input_redirections.c \
	compound_tokenizer.c \
	compound_tokenizer_if.c \
	compound_tokenizer_for.c \
	compound_tokenizer_for_utils.c \
	word_interpreter.c \
	operator_interpreter.c \
	opening_chars_handling.c \
	is_opening_char.c \
	assign_patend.c \
	sh_alias_substitution.c

C_FILES_executer = \
	sh_exec_file.c \
	sh_exec_stdin.c \
	sh_exec_arg.c \
	sh_exec_default.c \
	exec_script.c \
	exec_prgm.c \
	fd_handler.c \
	block_wait.c \
	functions_handler.c \
	get_path.c \
	generate_redirections.c \
	exec_compound.c \
	prepare_child.c \
	redirections_utils.c \
	assigns_handler.c \
	exec_simple_command.c \
	redirections_handler.c \
	open_files_handler.c

C_FILES_debug_mode = \
		     debug_mode.c

C_FILES_builtins/echo = \
	sh_echo.c \

C_FILES_builtins = \
		   sh_debug_builtin.c \
		   sh_cd.c \
		   sh_env.c \
		   sh_export.c \
		   sh_readonly.c \
		   sh_false.c \
		   sh_unset.c \
		   sh_set.c \
		   sh_test.c \
		   sh_source.c \
		   sh_type.c \
		   sh_true.c \
		   sh_alias.c \
		   sh_pwd.c \
		   sh_exit.c \
		   sh_jobs.c \
		   sh_fg.c \
		   sh_unalias.c

C_FILES_tools = \
		sh_resolve_dotpath.c \
		sh_print_all_token.c \
		sh_shdel.c \
		sh_hist_del.c \
		sh_job_del.c \
		sh_ln_del.c \
		sh_open_file_del.c \
		sh_pipe_lst_del.c \
		sh_redirect_lst_del.c \
		sh_token_del.c \
		sh_env_del.c \
		sh_tab_fusion.c \
		sh_are_you_sur.c \
		sh_check_path.c \
		sh_error_path.c \
		ft_join_with_char.c \
		sh_pattern_matching.c
#sh_find_law.c \

C_FILES_word_expansion = \
			 sh_arithmetic_expansion.c \
			 sh_word_expansion.c	\
			 sh_tilde_expansion.c \
			 sh_word_expression.c \
			 sh_expansion_size.c	\
			 sh_quote_removal.c \
			 sh_simple_word.c \
			 sh_subsh_expansion.c \
			 sh_check_arith.c \
			 sh_sub_arth_var.c \
			 sh_arth_tab.c \
			 sh_quote_removal_tool.c \
			 sh_word_expression_opt.c \
			 sh_expression_tool.c \
			 sh_word_opt_equal_tool.c \
			 pattern_matching.c \
			 sh_spetial_parameters.c

# SUPPA concat loop
C_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(C_FILES_$(SUB_DIR))))
