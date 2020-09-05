
int main()
{
    int i;
    int k;
    int res;

    for (i = 0; i < 64; i++)
    {
        for (res = 0; res < 256; res++)
        {
            if (i != 0)
                printf("%d div1 %d = %d\n", res, i, res % i);
        }
    }

    return 0;
}
