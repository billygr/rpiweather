#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define round(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))

/* T is temperature in degrees Fahrenheit,
*  RH is relative humidity in percent
*  source https://en.wikipedia.org/wiki/Heat_index
*  http://www.wpc.ncep.noaa.gov/html/heatindex.shtml
*  http://www.wpc.ncep.noaa.gov/html/heatindex_equation.shtml
*/
double Heat_Index(double T, double RH)
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
	double adjustment = 0;
	double heatindex = 0;

/* Try the simple formula first */
	heatindex = 0.5 * (T + 61.0 + ((T - 68.0) * 1.2) + (RH * 0.094));

	if (round(heatindex) > 80) {
/* If the RH is less than 13% and the temperature 
   is between 80 and 112 degrees F
*/
		if (round(RH) < 13) {
			if ((round(T) > 80) || round(T) < 112) {
				adjustment =
				    ((13 - RH) / 4) * sqrt(17 -
							   abs(T - 95.)) / 17;
			}
		}

/* if the RH is greater than 85% and the temperature
   is between 80 and 87 degrees F
*/
		if (round(RH) > 85) {
			if ((round(T) > 80) || round(T) < 87) {
				adjustment = ((RH - 85) / 10) * ((87 - T) / 5);
			}
		}

		heatindex = C1 + C2 * T + C3 * RH + C4 * T * RH + C5 * T * T +
		    C6 * RH * RH + C7 * T * T * RH + C8 * T * RH * RH +
		    C9 * T * T * RH * RH - adjustment;
	}
	return heatindex;
}

double Temperature_F(double C)
{
	return C * (9. / 5.) + 32;
}

double Temperature_C(double F)
{
	return (F - 32) * (5.0 / 9.0);
}
