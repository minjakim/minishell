#include "../includes/minishell.h"

int
	parse_env(char ***original_envp)
{
	char	**new_envp;
	int		i;

	new_envp = malloc(sizeof(char *) * ARG_MAX);
	i = -1;
	while ((*original_envp)[++i] != NULL)
	{
		new_envp[i] = strdup((*original_envp)[i]);//replace strdup
		if (new_envp[i] == NULL)
			return (1);
	}
	new_envp[i] = NULL;
	*original_envp = new_envp;
	return(0);
}

/*
** Make char **env size ARG_MAX in limits.h
** fill last index NULL
*/
