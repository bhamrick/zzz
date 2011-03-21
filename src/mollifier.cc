#include<mollifier.hh>
#include<cmath>

mollifier::mollifier() {
	
}

void mollifier::apply(double* buf, int N, int sample_rate) {
	double min = 0, max = N;
	for(int i = 0; i<N; i++) {
		double t = -1 + 2*(i / (max - min));
		double ratio = exp(-1/(1-t*t));
		buf[i] *= ratio;
	}
}
