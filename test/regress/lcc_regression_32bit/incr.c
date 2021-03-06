char gx = 'd';
char gy = 'd';
int a = 60123;
int b = 10432;

main() {
	memchar();
	memint();
	regchar();
	regint();
  return 0;
}

memchar() {
	char x, *p;

	&x, &p;
	x = gx;
	p = &gy;
	x = *p++;
	x = *++p;
	x = *p--;
	x = *--p;
	printf("%c %c\n",x,*p);
}

memint() {
	int x, *p;

	&x, &p;

	x = a;
	p = &b;
	x = *p++;
	x = *++p;
	x = *p--;
	x = *--p;
	printf("%d %x %o %d\n",x, x, x,*p);
	printf("%d %d\n", x,*p);
}

regchar() {
	register char x, *p;
	x = gx;
	p = &gy;

	x = *p++;
	x = *++p;
	x = *p--;
	x = *--p;
	printf("%c %c\n",x,*p);
}

regint() {
	register int x, *p;

	x = a;
	p = &b;
	x = *p++;
	x = *++p;
	x = *p--;
	x = *--p;
	printf("%x %d\n",x,*p);
}
