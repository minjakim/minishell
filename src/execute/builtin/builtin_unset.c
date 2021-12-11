/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:35:19 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 10:03:00 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void
	free_declare(t_hash *tmp)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

int
	remove_declare(t_hash **head, const char *const key)
{
	t_hash	*back;

	if (*head == NULL || key == NULL)
		return (0);
	if (legal_identifier(key) == 0)
		return (1);
	back = check_declare_key(*head, key);
	if (back == *head && strcmp(key, back->key) == 0)
	{
		*head = back->next;
		free_declare(back);
	}
	if (back->next && strcmp(key, back->next->key) == 0)
	{
		back->next = back->next->next;
		free_declare(back->next);
	}
	return (0);
}

int
	builtin_unset(t_shell *mini)
{
	char	**argv;

	if (mini && mini->command && mini->command->value.simple.argv)
		argv = mini->command->value.simple.argv;
	if (argv[0] != NULL && argv[1] == NULL)
		return (0);
	while (*++argv)
	{
		if (remove_declare(&mini->env.declare, *argv) != 0)
			return (1);
	}
	if (replace_envp(&mini->env, 1) != 0)
		return (1);
	return (0);
}
