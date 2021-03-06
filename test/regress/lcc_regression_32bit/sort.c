short nn[] = {103123, 39654, -1, 56754, 3, 18, 1, -51555, 789, 1};
short foo[] = { 1, 2, 3, 4, 5 };

main() {
	int i;

	//sort(nn, (sizeof nn)/(sizeof nn[0]));
	for (i = 0; i < (sizeof nn)/(sizeof nn[0]); i++) {
     putd(nn[i]);
     putchar('\n');
     //printf("%d/10=%d\n;\n %d%%10=%d\n;\n", nn[i], nn[i]/10, nn[i], nn[i]%10);
     //printf("%d*%d=%hd\n;\n", nn[i], nn[i+1], nn[i]*nn[i+1]);
     //printf("%d*%d=%hd\n;\n", nn[i], nn[i+2], nn[i]*nn[i+2]);
     //printf("%d*%d=%hd\n;\n", nn[i], nn[i+3], nn[i]*nn[i+3]);
     //printf("%d/%d=%hd\n;\n", nn[i], nn[i+1], nn[i]/nn[i+1]);
     //printf("%d/%d=%hd\n;\n", nn[i], nn[i+2], nn[i]/nn[i+2]);
     //printf("%d/%d=%hd\n;\n", nn[i], nn[i+3], nn[i]/nn[i+3]);
     //printf("%d%%%d=%hd\n;\n", nn[i], nn[i+1], nn[i]%nn[i+1]);
     //printf("%d%%%d=%hd\n;\n", nn[i], nn[i+2], nn[i]%nn[i+2]);
     //printf("%d%%%d=%hd\n;\n", nn[i], nn[i+3], nn[i]%nn[i+3]);
	}
	return 0;
}

/* putd - output decimal number */
putd(n) {
	if (n < 0) {
		putchar('-');
		n = -n;
	}
	if (n/10)
		putd(n/10);
	putchar(n%10 + '0');
}

int *xx;

/* sort - sort a[0..n-1] into increasing order */
sort(a, n) int a[]; {
	quick(xx = a, 0, --n);
}

/* quick - quicksort a[lb..ub] */
quick(a, lb, ub) int a[]; {
	int k, partition();

	if (lb >= ub)
		return;
	k = partition(a, lb, ub);
	quick(a, lb, k - 1);
	quick(a, k + 1, ub);
}

/* partition - partition a[i..j] */
int partition(a, i, j) int a[]; {
	int v, k;

	j++;
	k = i;
	v = a[k];
	while (i < j) {
		i++; while (a[i] < v) i++;
		j--; while (a[j] > v) j--;
		if (i < j) exchange(&a[i], &a[j]);
	}
	exchange(&a[k], &a[j]);
	return j;
}

/* exchange - exchange *x and *y */
exchange(x, y) int *x, *y; {
	int t;

	printf("exchange(%d,%d)\n", x - xx, y - xx);
	t = *x; *x = *y; *y = t;
}
