#include "ft_printf.h"

int     find_spec(char *str)
{
    int i;

    i = 0;
    while (*str != 's' && *str != 'S' && *str != 'p' && *str != 'd'
           && *str != 'D' && *str != 'i' && *str != 'o' && *str != 'O'
           && *str != 'u' && *str != 'U' && *str != 'x' && *str != 'X'
           && *str != 'c' && *str != 'C' && *str != '\0')
    {
        str++;
        i++;
    }
    return (i + 1);
}

char     *proc(const char *str, t_print *print, va_list ap, int *ret)
{
    size_t len;

    len = (ft_strchr(str, '%') - str);
    ft_strchr(str, '%') == NULL ? len = (ft_strchr(str, '\0') - str) : 0;
    *str == '%' ? len = 0 : 0;
    print->p = (char *)malloc(sizeof(char) * len + 1);
    ft_memcpy(print->p, str, len + 1);
    while (*str != '\0')
    {
        print = check_flag(&str, print);
        print = check_width(&str, ap, print);
        print = check_accurancy(&str, ap, print);
        print = check_size(&str, print);
        print = check_type(&str, print);
        print = change(print);
		if (print->type == 'd' || print->type == 'i' || print->type == 'o' || print->type == 'x' || print->type == 'X')
			if (print->accuracy >= 0 && print->null == 1)
				print->null = 0;
        if ((*str == '%' || *str == '\0') && print->type == 0 && *print->p != *str)
        {
            *ret += ft_print(print, ap);
            *str != '\0' ? str++ : 0;
            return (char *) (str);
        }
        else if (*str == '%' && print->type == 0 && *print->p == *str)
        {
            print->proc = 1;
            *ret += ft_print(print, ap);
			str++;
            return (char *) (str);
        }
        else if (print->type != 0)
        {
            *ret += ft_print(print, ap);
            return (char *) (str);
        }
        else if (check_all(print, (char **) &str) == 0)
        {
            *ret += ft_print(print, ap);
            return (char *) (str);
        }
    }
    return (char *) (str);
}

int    fill(const char *str, t_print *print, va_list ap)
{
    int ret;

    ret = 0;
    while (*str != '\0')
    {
        full(&print);
        while (*str != '\0' && *str != '%') {
            ret++;
            write(1, &(*(str++)), 1);
        }
        if (*str == '%')
            str = proc(++str, print, ap, &ret);
    }
    return (ret);
}

void       full(t_print **print)
{
    (*print)->proc = 0;
    (*print)->weidth = 0;
    (*print)->plus = 0;
    (*print)->null = 0;
    (*print)->space = 0;
    (*print)->hash = 0;
    (*print)->mynus = 0;
    (*print)->accuracy = -1;
    (*print)->type = 0;
    (*print)->cost = 0;
    (*print)->size = NULL;
    (*print)->p = NULL;
}

int     ft_printf(const char *format, ... )
{
    t_print print;
    va_list ap;
    int ret;

	if (format == NULL)
		return (0);
    va_start(ap, format);
    ret = fill(format, &print, ap);
    va_end(ap);
    return (ret);
}
