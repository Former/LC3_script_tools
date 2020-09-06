
int main()
{
    int i;
    int res;

    for (i = 0; i < 64; i++)
    {
        for (res = 0; res < 256; res++)
        {
            printf("%d ^ %d = %d\n", res, i, res ^ i);
        }
    }

    return 0;
}
