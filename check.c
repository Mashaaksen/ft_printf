#include "ft_printf.h"

t_print *check_flag(const char **str, t_print *print)
{
    while (**str == ' ' || **str == '-' || **str == '+' || **str == '0' || **str == '#')
    {
        if (**str == ' ')
            print->space = 1;
        else if (**str == '-')
            print->mynus = 1;
        else if (**str == '0')
            print->null = 1;
        else if (**str == '+')
            print->plus = 1;
        else if (**str == '#')
            print->hash = 1;
        (*str)++;
        print->p++;
    }
    return (print);
}

t_print *check_width(const char **str, va_list ap, t_print *print)
{
    if ((**str >= 49 && **str <= 57) || **str == 42)
    {
        if (**str == 42)
        {
            print->weidth = va_arg(ap, int);
            (*str)++;
            print->p++;
        }
        else
        {
            print->weidth = ft_atoi(*str);
            while (**str >= 48 && **str <= 57)
            {
                print->p++;
                (*str)++;
            }
        }
		if (print->weidth < 0)
		{
			print->mynus = 1;
			print->weidth *= -1;
		}
    }
    return (print);
}

t_print *check_accurancy(const char **str, va_list ap, t_print *print)
{
    if (**str == '.')
    {
        print->p++;
        (*str)++;
        if (**str == 42)
        {
            print->accuracy = va_arg(ap, int);
            (*str)++;
            print->p++;
        }
        else
        {
            print->accuracy = ft_atoi(*str);
            while (**str >= 48 && **str <= 57)
            {
                print->p++;
                (*str)++;
            }
        }
    }
    return (print);
}

t_print *check_size(const char **str, t_print *print)
{
    char *p;
    int i;

    if (**str == 'l' || **str == 'h' || **str == 'z' || **str == 'j')
    {
        i = find_spec((char *) *str);
        p = (char *) malloc(sizeof(char) * i);
        p = ft_strncpy(p, (char *) *str, (size_t) i - 1);
        if (ft_strstr(p, "z"))
            print->size = ft_strdup("z");
        else if (ft_strstr(p, "j"))
            print->size = ft_strdup("j");
        else if (ft_strstr(p, "ll"))
            print->size = ft_strdup("ll");
        else if (ft_strstr(p, "l"))
            print->size = ft_strdup("l");
        else if (ft_strstr(p, "h"))
        {
            if (ft_strstr(p, "hh"))
                print->size = ft_strdup("hh");
            else
                print->size = ft_strdup("h");
        }
    }
    while (**str == 'l' || **str == 'h' || **str == 'z' || **str == 'j')
    {
        print->p++;
        (*str)++;
    }
    return (print);
}

t_print *check_type(const char **str, t_print *print)
{
    char *p;
    char *s;

    p = "sSpdDioOuUxXcC";
    s = ft_strchr(p, **str);
    if (s && **str != '\0')
    {
        print->type = *s;
        (*str)++;
        print->p++;
    }
    return (print);
}

int 	check_count(char *p)
{
	int i;

	i = 0;
	while (*p != '\0')
	{
		if (ft_strchr("sSpdDioOuUxXcC", *p))
			i++;
		p++;
	}
	return (i > 2 ? 0 : 1);
}

int     check_all(t_print *print, char **str)
{
    size_t len;
    char *p;

	len = 0;
	p = NULL;
	if (**str != '\0') {
		len = (ft_strchr(*str, '%') - *str);
		ft_strchr(*str, '%') == NULL ? len = (ft_strchr(*str, '\0') - *str) : 0;
		**str == '%' ? len = 0 : 0;
		p = (char *) malloc(sizeof(char) * len + 1);
		ft_memcpy(p, *str, len + 1);
		if ((ft_strchr(p, 's') == NULL && ft_strchr(p, 'S') == NULL && ft_strchr(p, 'p') == NULL &&
			 ft_strchr(p, 'd') == NULL
			 && ft_strchr(p, 'D') == NULL && ft_strchr(p, 'i') == NULL && ft_strchr(p, 'o') == NULL &&
			 ft_strchr(p, 'O') == NULL
			 && ft_strchr(p, 'u') == NULL && ft_strchr(p, 'U') == NULL && ft_strchr(p, 'x') == NULL &&
			 ft_strchr(p, 'X') == NULL
			 && ft_strchr(p, 'c') == NULL && ft_strchr(p, 'C') == NULL) || check_count(p) == 0) {
			print->p = (char *) malloc(sizeof(char) * 2);
			print->p[0] = *p;
			print->p[1] = '\0';
			(*str)++;
			free((void *) p);
			return (0);
		}

		free((void *) p);
	}
    return (1);
}