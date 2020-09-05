
int main()
{
    int i;
    int k;
    int res;

    for (i = -8; i < 64; i++)
    {
        for (res = -64; res < 256; res++)
        {
            if (i != 0)
                printf("%d / %d = %d\n", res, i, res / i);
        }
    }

    return 0;
}
