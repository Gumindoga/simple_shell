#include "shell.h"

/**
 * _strcmp - string comparison
 * @s1: first string
 * @s2: second string
 * Return: difference, 0 otherwise
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}

	return (0);
}

/**
 * _strtok - tokenize strings
 * @str: string
 * @delim: delimiter
 * Return: a token or NULL
 */
char *_strtok(char *str, char *delim)
{
	static char *s;
	int dIndex; /* Delimiter index */
	char *tkn;

	if (str != NULL)
		s = str;
	if (!delim)
		return (NULL);
	while (*s != '\0')
	{
		dIndex = 0;
		while (delim[dIndex] != '\0')
		{
			if (*s == delim[dIndex])
				break;
			dIndex++;
		}
		if (!delim[dIndex])
			break;
		s++;
	}
	tkn = s;
	if (*tkn == '\0')
		return (NULL);
	while (*s != '\0')
	{
		dIndex = 0;
		while (delim[dIndex] != '\0')
		{
			if (*s == delim[dIndex])
			{
				*s = '\0';
				s++;
				return (tkn);
			}
			dIndex++;
		}
		s++;
	}
	return (tkn);
}

/**
 * _strdup_range - range duplication
 * @src: string
 * @from: index start
 * @to: index end
 * Return: string
 */
char *_strdup_range(char *src, int from, int to)
{
	int i = 0;
	char *dplt;

	dplt = malloc((to - from + 2) * sizeof(char));
	if (!dplt)
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}

	while (from < to)
		dplt[i++] = src[from++];
	dplt[i] = '\0';
	return (dplt);
}

/**
 * _strtrim - delete trail whitespace
 * @str: string
 * Return: string
 */
char *_strtrim(char *str)
{
	char *dplt = _strdup(str);
	int i = 0;

	while (*dplt == ' ')
		dplt++, i++;
	_strcpy(str, dplt);

	free(dplt - i);
	return (str);
}

/**
 * _isdigit - confirms digit
 * @s: string
 * Return: 1 if digit, 0 otherwise
 */
int _isdigit(char *s)
{

	int i = 0;

	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
