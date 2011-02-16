#include<color.hh>

color colorRGB(double r, double g, double b) {
	color c;
	c.r = r;
	c.g = g;
	c.b = b;
	return c;
}

color colorHSV(double h, double s, double v) {
	color c;
	if(h < 1/6.) {
		c.r = v;
		c.g = (6*h)*v + (1-6*h)*v*(1-s);
		c.b = v*(1-s);
	} else if(h < 2/6.) {
		c.r = (6*h-1)*v*(1-s) + (2-6*h)*v; 
		c.g = v;
		c.b = v*(1-s);
	} else if(h < 3/6.) {
		c.r = v*(1-s);
		c.g = v;
		c.b = (6*h-2)*v + (3-6*h)*v*(1-s);
	} else if(h < 4/6.) {
		c.r = v*(1-s);
		c.g = (6*h-3)*v*(1-s) + (4-6*h)*v;
		c.b = v;
	} else if(h < 5/6.) {
		c.r = (6*h-4)*v + (5-6*h)*v*(1-s);
		c.g = v*(1-s);
		c.b = v;
	} else {
		c.r = v;
		c.g = v*(1-s);
		c.b = (6*h-5)*v*(1-s) + (6-6*h)*v;
	}
	return c;
}
