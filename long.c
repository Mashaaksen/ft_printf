#include "ft_printf.h"

long long		ft_int_min(long long n)
{
    return (n < 0 ? -n : n);
}

int		ft_len_int(long long n)
{
    int len;

    len = 0;
    if (n <= 0)
        len++;
    while (n)
    {
        n = n / 10;
        len++;
    }
    return (len);
}

char			*ft_itoa_long(long long n)
{
    int				len;
    long long	num;
    char			*str;

    len = 0;
    len = ft_len_int(n);
    if (!(str = (char *)malloc(sizeof(*str) * (len + 1))))
        return (0);
    str[len--] = '\0';
    num = ft_int_min(n);
    while (len >= 0)
    {
        if (n < 0 && len == 0)
        {
            len--;
            str[0] = '-';
        }
        else if (num % 10 < 0)
        {
            str[len--] = (char) (num % 10 * -1 + 48);
            num = num / 10;
        }
        else
        {
            str[len--] = (char) (num % 10 + 48);
            num = num / 10;
        }
    }
    return (str);
}
