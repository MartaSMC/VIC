/******************************************************************************
 * @section DESCRIPTION
 *
 * This routine corrects preciptation measurements for gauge catch
 * deficiencies.
 *
 * Correction values read from Bras Figure 4.16.
 *
 * NOTE: Should locate better reference with fitted equations, or at least data
 * with which to fit an equation.
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
#include <vic_driver_classic.h>

#define GAUGE_HEIGHT 1.0  /* precipitation gauge height (m) */

/******************************************************************************
 * @brief    Correct preciptation measurements for gauge catch deficiencies.
 *****************************************************************************/
void
correct_precip(double *gauge_correction,
               double  wind,
               double  wind_h,
               double  roughness,
               double  snow_roughness)
{
    double gauge_wind;

    gauge_wind = wind * (log((GAUGE_HEIGHT + roughness) / roughness) /
                         log(wind_h / roughness));

    gauge_correction[RAIN] = 100. / exp(4.606 - 0.041 *
                                        pow(gauge_wind, 0.69));

    gauge_wind = wind * (log((GAUGE_HEIGHT + snow_roughness) /
                             snow_roughness) /
                         log(wind_h / snow_roughness));

    gauge_correction[SNOW] = 100. / exp(4.606 - 0.036 *
                                        pow(gauge_wind, 1.75));
}

#undef GAUGE_HEIGHT
