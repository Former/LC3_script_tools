
int main()
{
    int k, i, res = 0;

    for (k = 0; k < 1500; ++k)
    {
        for (i = 0; i < 1500; ++i)
        {
            res += (i + k) & 0xFF;
            res &= 0x1F;
        }
    }

    printf("Test finish %d\n", res);
    return 0;
}
