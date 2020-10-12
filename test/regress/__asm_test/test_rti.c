void func(void)
{
    printf("Test RTI\n");
    __asm {
        AND R0, R0, #0
        ADD R0, R0, #10
        AND R1, R1, #0
        ADD R1, R1, #11
        RTI R0, R1, #20
    }
}

int main()
{
    func();
    return 0;
}
