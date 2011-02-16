#ifndef COLOR_HH
#define COLOR_HH

struct color {
	double r, g, b;
};

color colorRGB(double, double, double);
color colorHSV(double, double, double);

#endif
