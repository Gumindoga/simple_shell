#include "shell.h"

/**
 * _strlen - finds string length
 * @str: string
 * Return: string length
 */
size_t _strlen(const char *str)
{
	size_t stringln = 0;

	while (str[stringln] != '\0')
		stringln++;
	return (stringln);
}

/**
 * _strcpy - copies source to destination
 * @to: to
 * @from: from
 * Return: to memory pointer
 */
char *_strcpy(char *to, const char *from)
{
	size_t i = 0;

	while (from[i] != '\0')
	{
		to[i] = from[i];
		i++;
	}
	to[i] = '\0';
	return (to);
}

/**
 * _strcat - concatenates two strings
 * @to: dest
 * @from: source
 * Return: pt
 */
char *_strcat(char *to, const char *from)
{
	size_t destln = _strlen(to);
	size_t i = 0;

	while (from[i] != '\0')
	{
		to[destln + i] = from[i];
		i++;
	}
	to[destln + i] = '\0';
	return (to);
}

/**
 * _strncmp - Compares matching strings
 * @s1: string 1
 * @s2: string 2
 * @n: matching characters
 * Return: 0 if match, difference otherwise
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i = 0;

	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}
/**
 * _strdup - Duplicates a string
 * @str: string
 * Return: pt, otherwise NULL on failure
 */
char *_strdup(const char *str)
{
	char *dplt;
	size_t stringln;

	if (str == NULL)
		return (NULL);
	stringln = _strlen(str) + 1;
	dplt = malloc(stringln);

	if (!dplt)
		return (NULL);
	_strcpy(dplt, str);
	return (dplt);
}
