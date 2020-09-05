
int main()
{
    int i;
    int k;
    int res;
    int res1;

    for (res = -256; res <= 256; res++)
    {
        res1 = res;
        for (i = -128; i <= 128; i++)
        {
            for (k = -res1; k <= res1; k++)
                res += k;
        }
        printf("summ(%d, %d) = %d\n", res1, i, res);
    }

    return 0;
}
