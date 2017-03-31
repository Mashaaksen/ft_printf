#include "ft_printf.h"

char    *find_str(t_print *print, va_list ap) {
    void *i;
    char *str;

    str = NULL;
	i = NULL;
	if (print->type != 0) {
		i = va_arg(ap, void *);
		if (i == NULL && print->type == 's') {
			return ("(null)");
		}
		if (i == NULL && print->accuracy == 0 && print->type == 'p')
			return ("0x");
		if (print->accuracy == 0 && i == 0 && print->type != 'c' && print->type != 'C') {
			if (print->hash == 1 && print->type == 'x')
				print->hash = 0;
			return ("");
		}
		if (print->size == NULL && print->type != 0) {
			if (print->type == 's')
				str = (char *) i;
			else if (print->type == 'c' || print->type == 'C') {
				str = (char *) malloc(sizeof(char) * 2);
				if (i == 0) {
					print->cost++;
					return ("\0");
				}
				str[0] = (char) i;
				str[1] = '\0';
			} else if (print->type == 'd' || print->type == 'i')
				str = ft_itoa_long((int) i);
			else if (print->type == 'p') {
				if (i == NULL)
					return ("0x0");
				str = ft_strjoin("0x", ft_itoa_base((unsigned long long) i, print->type));
			} else
				str = ft_itoa_base((unsigned int) i, print->type);
		} else if (print->size != NULL && print->type != 0) {
			if (!ft_strcmp(print->size, "hh")) {
				if (print->type == 'd' || print->type == 'i')
					str = ft_itoa_long((signed char) i);
				else
					str = ft_itoa_base((unsigned char) i, print->type);
			} else if (!ft_strcmp(print->size, "h")) {
				if (print->type == 'd' || print->type == 'i')
					str = ft_itoa_long((short int) i);
				else
					str = ft_itoa_base((unsigned short int) i, print->type);
			} else if (!ft_strcmp(print->size, "ll")) {
				if (print->type == 'd' || print->type == 'i')
					str = ft_itoa_long((long long int) i);
				else
					str = ft_itoa_base((unsigned long long int) i, print->type);
			} else if (!ft_strcmp(print->size, "l")) {
				if (print->type == 'd' || print->type == 'i')
					str = ft_itoa_long((long int) i);
				else if (print->type == 's')
					str = ft_wchar((wchar_t *) i, print);
				else
					str = ft_itoa_base((unsigned long int) i, print->type);
			} else if (!ft_strcmp(print->size, "j")) {
				if (print->type == 'd' || print->type == 'i')
					str = ft_itoa_long((intmax_t) i);
				else
					str = ft_itoa_base((uintmax_t) i, print->type);
			} else if (!ft_strcmp(print->size, "z")) {
				if (print->type == 'd' || print->type == 'i')
					str = ft_itoa_long((size_t) i);
				else
					str = ft_itoa_base((size_t) i, print->type);
			}
			if (print->type == 'p' && !ft_strstr(str, "0x"))
				str = ft_strjoin("0x", str);
		}
	}
    else if (print->type == 0 && print->proc == 1)
        str = "%";
    return (str);
}

char    *flag_weidth(t_print *print, char *str)
{
    char *s;
    char *p;
    int i;
    int sizeline;
    int ret;
    int fm;

    fm = 0;
    i = 0;
    s = NULL;
    sizeline = (int) (str != NULL ? ft_strlen(str) : 0);
    ret = print->weidth - sizeline;
    if (print->cost == 1)
        ret--;
    if ((print->type == 'o' || print->type =='O') && print->hash == 1)
        ret--;
    else if ((print->type == 'x' || print->type == 'X') && print->hash == 1)
        ret -= 2;
    if (ret > 0)
    {
        if (print->hash == 1)
        {
            if (print->type == 'o')
                s = "0";
            else if (print->type == 'x' || print->type == 'X')
            {
                if (print->type == 'x')
                    s = "0x";
                else
                    s = "0X";
            }
            if (print->null == 1 && print->mynus == 0)
            {
                p = (char *) malloc(sizeof(char) * (ret + 1));
                p[ret] = '\0';
                while (ret-- > 0)
                    p[i++] = '0';
                str = ft_strjoin(p, str);
            }
            s != NULL ? str = ft_strjoin(s, str) : 0;
        }
        if (print->mynus == 1)
        {
            p = (char *) malloc(sizeof(char) * (ret + 1));
            p[ret] = '\0';
            while (ret-- > 0)
                p[i++] = ' ';
            str = ft_strjoin(str, p);
        }
        else
        {
            if (print->null == 1 && print->hash == 0)
            {
                if (*str == '-' || *str == '+' || *str == ' ')
                {
                    *str == '-' ? fm++ : 0;
                    str++;
                }
                p = (char *) malloc(sizeof(char) * (ret + 1));
                p[ret] = '\0';
                while (ret-- > 0)
                    p[i++] = '0';
				if (print->type == 'p')
					str = ft_strjoin(str, p);
				else
					str = ft_strjoin(p, str);
                if (fm != 0 || print->plus != 0 || print->space != 0)
                {
                    fm != 0 ? str = ft_strjoin("-", str) : 0;
                    print->plus != 0 ? str = ft_strjoin("+", str) : 0;
					print->space != 0 ? str = ft_strjoin(" ", str) : 0;
                }
            }
            p = (char *) malloc(sizeof(char) * (ret + 1));
            p[ret] = '\0';
            while (ret-- > 0)
                p[i++] = ' ';
            str = (str != NULL ? ft_strjoin(p, str) : p);
        }
    }
    else
    {
        if (print->hash == 1 && *str != '0')
        {
            if (print->type == 'o')
                s = "0";
            else if (print->type == 'x' || print->type == 'X')
            {
                if (print->type == 'x')
                    s = "0x";
                else
                    s = "0X";
            }
            s != NULL ? str = ft_strjoin(s, str) : 0;
        }
    }
    return (str);
}

char    *accuarcy(t_print *print, char *str)
{
    int flag;
    char *p;
    int ret = 0;
    int i = 0;

    p = str;
    flag = 0;
	if (*p == '-' && (print->type == 'd' || print->type == 'i' || print->type == 'x' || print->type == 'X' || print->type == 'o' || print->type == 'u'))
	{
		flag++;
		p++;
		ret++;
		str = ft_strdup(p);
	}
    ret = (int) (print->accuracy - ft_strlen(str));
    if ((print->type == 'd' || print->type == 'i' || print->type == 'x' || print->type == 'X' || print->type == 'o' || print->type == 'u') && ret > 0)
    {
        p = (char *) malloc(sizeof(char) * (ret + 1));
        p[ret] = '\0';
        flag == 1 ? p[i++] = '-' : 0;
        while (ret-- > 0)
            p[i++] = '0';
        str = ft_strjoin(p, str);
		if ((print->type == 'x' || print->type == 'X') && print->hash == 1)
			str = ft_strjoin("0x", str);
    }
	else if (flag == 1)
		str = ft_strjoin("-", str);
	else if (print->type == 'p')
	{
		str += 2;
		ret = (int) (print->accuracy - ft_strlen(str));
		if (ret > 0)
		{
			p = (char *) malloc(sizeof(char) * (ret + 1));
			p[ret] = '\0';
			ret--;
			while (ret-- >= 0)
				p[i++] = '0';
			p = ft_strjoin("0x", p);
			str = ft_strjoin(p, str);
		}
		else
			str = ft_strjoin("0x", str);
	}
    else if (print->type == 's')
    {
        ret = print->accuracy;
        p = (char *) malloc(sizeof(char) * (ret + 1));
        p[ret--] = '\0';
        while (ret >= 0)
        {
            p[ret] = str[ret];
            ret--;
        }
        return (p);
    }
    return (str);
}

int    ft_print(t_print *print, va_list ap)
{
    int len;
    char a;
    char *str;

	str = 0;
    a = '\0';
    len = 0;
	str = find_str(print, ap);
    if (str != NULL || print->p != NULL)
    {
        str == NULL ? str = print->p : 0;
		if (print->accuracy > 0 && ((print->type != 's' && !ft_strcmp(str, "l")) || (print->type == 's' && ft_strcmp(str, "l")) || (print->type != 's' && ft_strcmp(str, "l"))))
			str = accuarcy(print, str);
		if (print->accuracy == 0 && print->type == 's')
			str = "" ;
        print->accuracy > 0 && print->type != 's' ? print->null = 0 : 0;
        *str == '-' ? print->plus = 0 : 0;
        if ((print->type == 'd' || print->type == 'i') && print->plus == 1)
            str = ft_strjoin("+", str);
        else if ((print->type == 'd' || print->type == 'i') && print->space == 1 && *str != '-')
            str = ft_strjoin(" ", str);
		if ((print->type != 's' && !ft_strcmp(str, "l")) || (print->type == 's' && ft_strcmp(str, "l")) || (print->type != 's' && ft_strcmp(str, "l")))
        	str = flag_weidth(print, str);
		else if ((print->type == 'd' || print->type == 'i') && print->space == 1 && *str != '-')
			str = ft_strjoin(" ", str);
		if ((print->cost == 1 && print->mynus == 0) || (print->type != 'c' && print->type != 'C') || ((print->type == 'c' || print->type == 'C') && print->cost == 0))
			ft_putstr(str);
        len = (int) ft_strlen(str);
        if ((print->type != 'c' || print->type != 'C') && print->cost == 1)
        {
            len++;
            write(1, &a, 1);
			print->mynus == 1 ? ft_putstr(str) : 0;
        }
    }
    return (str != NULL ? len : 0);
}