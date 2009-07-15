/*!
 * \file raster/interp.c
 *
 * \brief Raster Library - Interpolation
 *
 * (C) 2001-2009 GRASS Development Team
 *
 * This program is free software under the GNU General Public License 
 * (>=v2). Read the file COPYING that comes with GRASS for details.
 *
 * \author Original author CERL
 */

#include <grass/gis.h>
#include <grass/raster.h>

DCELL Rast_interp_linear(double u, DCELL c0, DCELL c1)
{
    return u * (c1 - c0) + c0;
}

DCELL Rast_interp_bilinear(double u, double v,
			   DCELL c00, DCELL c01, DCELL c10, DCELL c11)
{
    DCELL c0 = Rast_interp_linear(u, c00, c01);
    DCELL c1 = Rast_interp_linear(u, c10, c11);

    return Rast_interp_linear(v, c0, c1);
}

DCELL Rast_interp_cubic(double u, DCELL c0, DCELL c1, DCELL c2, DCELL c3)
{
    return (u * (u * (u * (c3 - 3 * c2 + 3 * c1 - c0) +
		      (-c3 + 4 * c2 - 5 * c1 + 2 * c0)) + (c2 - c0)) +
	    2 * c1) / 2;
}

DCELL Rast_interp_bicubic(double u, double v,
			  DCELL c00, DCELL c01, DCELL c02, DCELL c03,
			  DCELL c10, DCELL c11, DCELL c12, DCELL c13,
			  DCELL c20, DCELL c21, DCELL c22, DCELL c23,
			  DCELL c30, DCELL c31, DCELL c32, DCELL c33)
{
    DCELL c0 = Rast_interp_cubic(u, c00, c01, c02, c03);
    DCELL c1 = Rast_interp_cubic(u, c10, c11, c12, c13);
    DCELL c2 = Rast_interp_cubic(u, c20, c21, c22, c23);
    DCELL c3 = Rast_interp_cubic(u, c30, c31, c32, c33);

    return Rast_interp_cubic(v, c0, c1, c2, c3);
}
