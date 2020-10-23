
int main()
{
    int k, i, res = 0;

    for (k = 0; k < 30; ++k)
    {
        for (i = 0; i < 15000; ++i)
        {
            res += (i >> 1 + k << 2) & 0xFF;
            res &= 0x1F;
        }
        printf("%d res = %d\n", k, res);
    }

    printf("Test finish %d\n", res);
    return 0;
}
