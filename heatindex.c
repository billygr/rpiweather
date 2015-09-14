#include <stdio.h>

/* T is temperature in degrees Fahrenheit,
*  R is relative humidity in percent
*  source https://en.wikipedia.org/wiki/Heat_index
*  http://www.wpc.ncep.noaa.gov/html/heatindex.shtml
*/
double Heat_Index(double T, double R)
{
	const double C1 = -42.379;
	const double C2 = 2.04901523;
	const double C3 = 10.14333127;
	const double C4 = -0.22475541;
	const double C5 = -6.83783e-3;
	const double C6 = -5.481717e-2;
	const double C7 = 1.22874e-3;
	const double C8 = 8.5282e-4;
	const double C9 = -1.99e-6;
	return C1 + C2 * T + C3 * R + C4 * T * R + C5 * T * T + C6 * R * R +
	    C7 * T * T * R + C8 * T * R * R + C9 * T * T * R * R;
}

double Temperature_F(double C)
{
	return C * (9. / 5.) + 32;
}

double Temperature_C(double F)
{
	return (F - 32) * (5.0 / 9.0);
}
