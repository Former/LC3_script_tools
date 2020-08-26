
int main()
{
    int k, i, res = 0;

    for (k = 0; k < 500; ++k)
    {
        for (i = 0; i < 500; ++i)
        {
            res += (i >> 1 + k << 2) & 0xFF;
            res &= 0x1F;
        }
    }

    printf("Test finish %d\n", res);
    return 0;
}
