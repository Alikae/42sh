
#ifndef LIBSHUTIL
 #define LIBSHUTIL
 #define NOT_FOUND	1
 #define NOT_DIR	2
 #define NOT_ACCESS	4
 #define CREAT		8 

int	sh_basename(int ac, char **av, char **ev);
int	sh_false(int ac, char **av, char **ev);
int	sh_pwd(int ac, char **av, char **ev);
int	sh_true(int ac, char **av, char **ev);
int	sh_rm(int ac, char **av, t_env **env);
int	sh_check_path(char *all_path, int *error);
int	sh_find_opt(char **av, int *i);
int	sh_error_rm_opt(char c);
int sh_are_you_sure(char *question);

#endif
