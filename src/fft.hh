#ifndef FFT_H
#define FFT_H

#include<complex>

void fft(std::complex<double>*, int);
std::complex<double> complex_unit(double);
void fft_resolve_range(std::complex<double>*, int);

#endif
