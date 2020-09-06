
int main()
{
    int i;
    int res;

    for (i = -8; i < 64; i++)
    {
        for (res = -8; res < 256; res++)
        {
            printf("%d * %d = %d\n", res, i, res * i);
        }
    }

    return 0;
}
