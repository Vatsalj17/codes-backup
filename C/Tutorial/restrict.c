
void f(int* restrict a, int* restrict b, int* restrict x) {
	*a += *x;
	*b += *x;
}

int main(void) {
	int a = 4, b = 3, x = 7;
	f(&a, &b, &x);
}
