#include "ft_ssl_crypt.h"
#include "crypt.h"

char *xor_function(char *a, char *b)
{
    size_t  i;
    char    *ans;

    if (!(ans = malloc(ft_strlen(a) + 1)))
        return (NULL);
    i = -1;
    while (++i < ft_strlen(a))
    {
        if(a[i] == b[i]) 
            ans[i] = '0'; 
        else 
            ans[i] = '1';
    }
    ans[i] = '\0';
    free(a);
    free(b);
    return ans;
}

char *permute(char *key, int* arr, int n)
{ 
    char    *per;
    int     i;

    if (!(per = (char*)malloc(n + 1)))
        return (NULL);
    i = -1;
    per[n] = '\0';
    while(++i < n)
        per[i] = key[arr[i] - 1];
    free(key);
    return per; 
}

char *shift_left(char *k, int shifts)
{
    char    *s;
    int     i;
    int     j;

    i = -1;
    while (++i < shifts)
    {
        if (!(s = (char *)malloc(29)))
            return (NULL);
        j = 0;
        s[28] = '\0';
        while (++j < 28)
            s[j - 1] = k[j];
        s[j - 1] = k[0];
        free(k); 
        k = s;
    }
    return (k); 
} 

int split(char *str, char **left, char **right, int size)
{
    if (!(*left = malloc(size + 1)))
        return (0);
    if (!(*right = malloc(size + 1)))
    {
        free(*left);
        return (0);
    }
    //Splitting
    ft_memcpy(*left, str, size);
    ft_memcpy(*right, str + size, size);
    (*left)[size] = '\0';
    (*right)[size] = '\0';
    free(str);
    return (1);
}
