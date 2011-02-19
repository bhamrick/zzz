#include<fft.hh>
#include<const.hh>

std::complex<double> complex_unit(double arg) {
	std::complex<double> ans = std::polar(1.0,arg);
	return ans;
}

void fft(std::complex<double> *arr, int N) {
	int i = 0, ibar = 0, bits = 0;
	while((1 << bits) < N) {
		bits++;
	}
	while(i < N) {
		if(i < ibar) {
			std::complex<double> t = arr[i];
			arr[i] = arr[ibar];
			arr[ibar] = t;
		}
		i++;
		for(int j = bits-1; j>=0; j--) {
			ibar ^= (1<<j);
			if(ibar & (1<<j)) {
				break;
			}
		}
	}
	fft_resolve_range(arr,N);
}

void fft_resolve_range(std::complex<double> *arr, int N) {
	if(N == 1) return;
	int n = N/2;
	fft_resolve_range(arr, n);
	fft_resolve_range(arr+n, n);
	for(int i = 0; i<n; i++) {
		arr[i] = arr[i] + complex_unit(2.*pi*i/N)*arr[n+i];
		arr[n+i] = arr[i] - 2.*complex_unit(2.*pi*i/N)*arr[n+i];
	}
}
