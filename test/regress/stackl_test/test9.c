//#include <sysio.h>

typedef struct
{
    int aa;
    int bb;
    char cc;
} struct_t;

int main()
{
    printf("Testing pointer arithmetic\n");

    {
        char data[10];
        int ii;
        char *ptr;

        for (ii=0; ii<10; ii++)
        {
            data[ii] = (char)ii;
        }

        ptr = data;
        for (ii=0; ii<10; ii++)
        {
            if (*ptr++ != data[ii]) 
            {
                printf("pointer error ");
                printf("%d", (int)ptr);
                printf(" ");
                printf("%d", (int)&data[ii]);
                printf("\n");
            }
            else
            {
                printf("Index ");
                printf("%d", ii);
                printf(" OK\n");
            }
        }
    }

    {
        char *cptr;
        int  *iptr;
        struct_t *sptr;
        void *vptr;
        int  ii;
        int sizeofstr; 

        cptr = 0;
        iptr = 0;
        sptr = 0;
        vptr = 0;
        sizeofstr = sizeof(struct_t);
        for (ii=0; ii<10; ii++)
        {
            if (cptr++ != (char*)ii) 
                printf("char pointer arithmetic error\n");
            else
                printf("char pointer arithmetic OK\n");

            if (iptr++ != (int *)(ii*1)) 
                printf("int pointer arithmetic error %d!=%d\n", (int)iptr, (ii*1));
            else
                printf("int pointer arithmetic OK\n");

            if (sptr++ != (struct_t*)(sizeofstr * ii))
                printf("struct pointer arithmetic error %d!=%d s=%d\n", (int)sptr, (sizeofstr * ii), sizeof(struct_t));
            else
                printf("struct pointer arithmetic OK\n");

            if (vptr != (void*)ii) 
                printf("void pointer arithmetic error\n");
            else
                printf("void pointer arithmetic OK\n");
            vptr=(char*)vptr+1; 
        }
    }

    printf("Test complete\n");
    return 0;
}
