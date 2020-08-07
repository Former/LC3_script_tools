//#include <string.h>

int f2();
int f1(int a, int b);

int f1(int a, int b)
{
    printf("%d", a + b);
    printf("\n");
    return a + b;
}
int main()
{
    int ret;
    printf("%d", 0);
    printf("\n");
    f1(5, 8);
    ret = f2();
    printf("%d", 3);
    printf("\n");
    printf("%d", ret);
    printf("\n");
    ret = 2*f2() - 3;
    printf("%d", ret);
    printf("\n");
}
int f2()
{
    printf("%d", 2);
    printf("\n");
    return 4;
}
