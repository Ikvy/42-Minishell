#ifndef BUILTIN_H
# define BUILTIN_H

int		ft_findchar(char *str, char c);

int		built_echo(char *args);
int		built_cd(char *dir, char **env);
void	built_exit(int status);
void	built_pwd(char **env);
void	built_env(char **env, int opt);
char	**built_export(char *exported, char **env);
char	**built_unset(char *unseted, char **env);

#endif
