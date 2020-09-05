
int main()
{
    int i;
    int res;

    for (i = 0; i < 8; i++)
    {
        for (res = 0; res < 100; res++)
        {
            printf("%d << %d = %d\n", res, i, res << i);
            printf("%d >> %d = %d\n", res, i, res >> i);
        }
    }

    return 0;
}
