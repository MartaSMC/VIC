/******************************************************************************
 * @section DESCRIPTION
 *
 * This subroutine computes the cosine of the solar zenith angle, given the
 * current location and date.
 *
 * @section LICENSE
 *
 * The Variable Infiltration Capacity (VIC) macroscale hydrological model
 * Copyright (C) 2014 The Land Surface Hydrology Group, Department of Civil
 * and Environmental Engineering, University of Washington.
 *
 * The VIC model is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *****************************************************************************/

#include <vic_def.h>
#include <vic_run.h>
#include <mtclim_constants_vic.h>

/******************************************************************************
 * @brief    This subroutine computes the cosine of the solar zenith angle.
 *****************************************************************************/
double
compute_coszen(double     lat,
               double     lng,
               double     time_zone_lng,
               dmy_struct dmy)
{
    double               coslat;
    double               sinlat;
    double               decl;
    double               cosdecl;
    double               sindecl;
    double               cosegeom;
    double               sinegeom;
    double               coshss;
    double               hour_offset;
    double               cosh;
    double               coszen;

    /* calculate cos and sin of latitude */
    coslat = cos(lat * PI / 180);
    sinlat = sin(lat * PI / 180);

    /* calculate cos and sin of declination */
    decl = MINDECL * cos(((double)dmy.day_in_year + DAYSOFF) * RADPERDAY);
    cosdecl = cos(decl);
    sindecl = sin(decl);

    /* calculate daylength as a function of lat and decl */
    cosegeom = coslat * cosdecl;
    sinegeom = sinlat * sindecl;
    coshss = -(sinegeom) / cosegeom;
    if (coshss < -1.0) {
        coshss = -1.0; /* 24-hr daylight */
    }
    if (coshss > 1.0) {
        coshss = 1.0; /* 0-hr daylight */
    }

    /* calculate cos of hour angle */
    hour_offset = (time_zone_lng - lng) * 24 / 360;
    cosh = cos(((double)dmy.hour + hour_offset - 12) * PI / 12);

    /* calculate cosine of solar zenith angle */
    coszen = cosegeom * cosh + sinegeom;

    return coszen;
}
