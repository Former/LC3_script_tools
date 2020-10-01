void func(void)
{
    printf("Test RES\n");
    __asm {
        AND R0, R0, #0 
        ADD R0, R0, #10 
        RES R0, #20
    }
}

int main()
{
    func();
    return 0;
}
