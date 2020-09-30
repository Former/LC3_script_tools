void func(void)
{
    printf("Hello world\n");
    __asm {
        ; Comment
        NOP
    }
    printf("Error1\n");
}

int main()
{
    func();
    printf("Error2\n");
    return 0;
}
