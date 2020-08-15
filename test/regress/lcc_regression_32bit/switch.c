main()
{
	int i; char *s;

	for (s = "bfnrtvx"; *s; s++)
		printf("%c = 0x%x\n", *s, backslash(*s));
	sf();
	sg();
	sh();
	for (i = 0x10000; i&0x70000; i += 0x10000)
		big(i);
	limit();
	return 0;
}

char backslash_c(char c)
{
	switch (c) {
	case 'b':
		return '\b';
	case 'f':
		return '\f';
	case 'n':
		return '\n';
	case 'r':
		return '\r';
	case 't':
		return '\t';
	case 'v':
		return '\v';
	}
	return c;
}

backslash(c)
{
	switch (c) {
	case 'b':
		return '\b';
	case 'f':
		return '\f';
	case 'n':
		return '\n';
	case 'r':
		return '\r';
	case 't':
		return '\t';
	case 'v':
		return '\v';
	}
	return c;
}

sf_c() {
	char i, x = 0, y;

	printf("f:\n");
	for (i = 100000; i <= 100020; i++) {
		y = i;
		switch (i) {
		case 100001: x = i; break;
		case 100002: x = i; break;
		case 100007: x = i; break;
		case 100008: x = i; break;
		case 100009: x = i; break;
		case 100016: x = i; break;
		case 100017: x = i; break;
		case 100018: x = i; break;
		case 100019: x = i; break;
		case 100020: x = i; break;
		}
		printf("x = %d\n", x);
	}
}

sf() {
	int i, x = 0, y;

	printf("f:\n");
	for (i = 234560; i <= 234580; i++) {
		y = i;
		switch (i) {
		case 234501: x = i; break;
		case 234502: x = i; break;
		case 234507: x = i; break;
		case 234508: x = i; break;
		case 234509: x = i; break;
		case 234516: x = i; break;
		case 234517: x = i; break;
		case 234518: x = i; break;
		case 234519: x = i; break;
		case 234520: x = i; break;
		}
		printf("x = %d\n", x);
	}
}

sg() {
	int i;

	printf("g:\n");
	for (i = 1; i <= 10; i++)
		switch (i) {
		case 1: case 2: printf("1 %d\n", i); break;
		case 3: case 4: case 5: printf("2 %d\n", i); break;
		case 6: case 7: case 8: printf("3 %d\n", i);
		default:
			printf("d %d\n", i); break;
		case 1001: case 1002: case 1003: case 1004:
			printf("5 %d\n", i); break;
		case 3001: case 3002: case 3003: case 3004:
			printf("6 %d\n", i); break;
	}
}

sh()
{
	int i, n=0;

	printf("h:\n");
	for (i = 65001; i <= 65500; i++)
		switch (i) {
		default: n++; continue;
		case 65128: printf("i = %d\n", i); break;
		case 65016: printf("i = %d\n", i); break;
		case 65008: printf("i = %d\n", i); break;
		case 65120: printf("i = %d\n", i); break;
		case 65280: printf("i = %d\n", i); break;
		case 65264: printf("i = %d\n", i); break;
		case 65248: printf("i = %d\n", i); break;
		case 65272: printf("i = %d\n", i); break;
		case 65304: printf("i = %d\n", i); break;
		case 65296: printf("i = %d\n", i); break;
		case 65288: printf("i = %d\n", i); break;
		case 65312: printf("i = %d\n", i); break;
		}
	printf("%d defaults\n", n);
}

big(x) int x; {
	switch(x&0x60000){
	case -1:
	case -2:
	case 0x00000:
		printf("x = 0x%x (0)\n", x); break;
	case 0x20000:
		printf("x = 0x%x (2)\n", x); break;
	case 0x40000:
		printf("x = 0x%x (4)\n", x); break;
	default:
		printf("x = 0x%x (default)\n", x); break;
	}
}

#define INT_MIN -320000
#define INT_MAX 320000

int limit() {
	int i;

	for (i = INT_MIN; i <= INT_MIN+5; i++)
		switch (i) {
		case INT_MIN:	printf("0\n"); break;
		case INT_MIN+1:	printf("1\n"); break;
		case INT_MIN+2:	printf("2\n"); break;
		case INT_MIN+3:	printf("3\n"); break;
		case INT_MIN+4:	printf("4\n"); break;
		default:	printf("5\n"); break;
		}
	for (i = INT_MAX; i >= INT_MAX-5; i--)
		switch (i) {
		case INT_MAX:	printf("0\n"); break;
		case INT_MAX-1:	printf("1\n"); break;
		case INT_MAX-2:	printf("2\n"); break;
		case INT_MAX-3:	printf("3\n"); break;
		case INT_MAX-4:	printf("4\n"); break;
		default:	printf("5\n"); break;
		}
	return 0;
}
