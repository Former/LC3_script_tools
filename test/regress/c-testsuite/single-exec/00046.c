typedef struct {
	int a;
	union {
		int b1;
		int b2;
	} un1;
	struct { union { struct { int c; } st1; } un2; } st2;
	struct {
		int d;
	} st3;
} s;

int
main()
{
	s v;
	
	v.a = 1;
	v.un1.b1 = 2;
	v.st2.un2.st1.c = 3;
	v.st3.d = 4;
	
	if (v.a != 1)
		return 1;
	if (v.un1.b1 != 2 && v.un1.b2 != 2)
		return 2;
	if (v.st2.un2.st1.c != 3)
		return 3;
	if (v.st3.d != 4)
		return 4;
	
	return 0;
}
