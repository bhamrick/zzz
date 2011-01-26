#include<cstdio>

int main() {
	int N = 50;
	double dx = 0.1;
	printf("0.0 0.1\n0.0 10.0\n");
	printf("%d\n",2*N+1);
	for(int i = -N; i<=N; i++) {
		printf("1.0 %lf %lf 0.0 0.0 1\n",i*dx,i*i*dx*dx);
	}
	printf("%d\n",2*N);
	for(int i = 0; i<2*N; i++) {
		printf("%d %d 1 0\n",i,i+1);
	}
}
