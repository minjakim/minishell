#include "minishell.h"

t_env	*export(char *str, t_env *head, int	flag)
{
	int	i;
	t_env	*env;
	t_env	*tmp;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		++i;
	if (!str[i]) // bash 출력 결과 env: ‘qwe’: No such file or directory 
	{
		printf("you should type =\n");
		return(NULL);
	}
	str[i] = '\0';
	//if (!str[0]) key값이 없이 들어와도 bash에서 환경변수로 변한다. 
	tmp = head;
	while (tmp && strcmp(tmp->key, str) && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp && !strcmp(tmp->key, str) && strcmp(tmp->value, str + i + 1))
	{
		free(tmp->value);
		tmp->value = strdup(str + i + 1);
	}
	else
	{
		env = (t_env *)malloc(1);
		env->key = strdup(str);
		env->value = strdup(str + i + 1);
		env->next = NULL;
		if (head == NULL)
			return (env);
		tmp->next = env;
	}
	return (head);
}

t_env	*parent_env(char **old_env)
{
	t_env	*head;
	int		i;

	head = NULL;
	i = 0;
	while (old_env[i] != NULL)
	{
		head = export(old_env[i], head, 0);
		++i;
	}
	return (head);
}
