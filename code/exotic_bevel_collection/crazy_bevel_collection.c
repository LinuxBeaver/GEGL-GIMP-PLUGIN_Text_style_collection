/* This file is an image processing operation for GEGL
 *
 * GEGL is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * GEGL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GEGL; if not, see <https://www.gnu.org/licenses/>.
 *
 * Credit to Øyvind Kolås (pippin) for major GEGL contributions
 * 2023 Beaver, Exotic Bevel Collection


This Gimp plugin can be tested without installing by pasting syntax from g1, g2, g3, g4, ect... into Gimp's GEGL graph.
--

THERE IS NO NEED TO PROVIDE SYNTAX WHEN ALL OF IT IS BELOW in each g definition. Paste each g individually into GEGL graph, not all of them at once.


Check which numbers correspond to what g graph
 */

#include "config.h"
#include <glib/gi18n-lib.h>


#ifdef GEGL_PROPERTIES

#define g1 \
"  id=contain src aux=[ ref=contain levels out-low=0.10 id=1 dst-out aux=[ ref=1 median-blur abyss-policy=none radius=5 alpha-percentile=0 lb:ssg radius=0 stroke=2 opacityssg=1.8 lb:ssg radius=0 stroke=2  opacityssg=1.8 lb:ssg radius=0 stroke=2  opacityssg=1.8 lb:ssg radius=0 stroke=2 opacityssg=1.8 lb:ssg radius=0 stroke=2  opacityssg=1.8 lb:ssg radius=0 stroke=2  opacityssg=1.8 lb:ssg radius=0 stroke=2 opacityssg=1.8 lb:ssg radius=0 stroke=2  opacityssg=1.8 lb:ssg radius=0 stroke=2  opacityssg=1.8 gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=1 std-dev-y=1 ] id=silly overlay aux=[ ref=silly emboss depth=1  ] id=cropaux crop aux=[ ref=cropaux ] median-blur abyss-policy=none radius=0 id=2 gimp:layer-mode layer-mode=grain-merge composite-mode=clip-to-backdrop opacity=0.5  aux=[  ref=2 lb:bevel type=sharpbevel   radius1=7 radius2=0 bevel1=45 bevel2=21 th=0.1 azimuth=40.0 slideupblack=0 metric=chebyshev smooth=0 ] dst-over  aux=[ ref=contain lb:custom-bevel gaus=1 box=2 ]  median-blur abyss-policy=none radius=0 "\


#define g2 \
" id=contain src aux=[ ref=contain levels out-low=0.10 id=1 dst-out aux=[ ref=1 median-blur radius=5 alpha-percentile=0 lb:ssg radius=0 stroke=4 opacityssg=1.8 lb:ssg radius=0 stroke=4  opacityssg=1.8 lb:ssg radius=0 stroke=4  opacityssg=1.8 lb:ssg radius=0 stroke=4 opacityssg=1.8 lb:ssg radius=0 stroke=4  opacityssg=1.8 lb:ssg radius=0 stroke=4  opacityssg=1.8 lb:ssg radius=0 stroke=4 opacityssg=1.8 lb:ssg radius=0 stroke=4  opacityssg=1.8 lb:ssg radius=0 stroke=4  opacityssg=1.8 gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=1 std-dev-y=1 ] id=silly overlay aux=[ ref=silly emboss depth=1  ] id=cropaux crop aux=[ ref=cropaux ] median-blur abyss-policy=none radius=0 id=2 gimp:layer-mode layer-mode=grain-merge composite-mode=clip-to-backdrop opacity=0.5  aux=[  ref=2 lb:bevel type=sharpbevel radius1=7 radius2=0 bevel1=45 bevel2=21 th=0.1 azimuth=40.0 slideupblack=0 metric=chebyshev smooth=0 ] dst-over  aux=[ ref=contain lb:custom-bevel gaus=1 box=2 ]  median-blur abyss-policy=none radius=0 "\


#define g3 \
" id=contain src aux=[ ref=contain levels out-low=0.10 id=1 dst-out aux=[ ref=1 median-blur abyss-policy=none radius=5 alpha-percentile=0 lb:ssg radius=0 stroke=6 opacityssg=1.8 lb:ssg radius=0 stroke=6  opacityssg=1.8 lb:ssg radius=0 stroke=6  opacityssg=1.8lb:ssg radius=0 stroke=6 opacityssg=1.8 lb:ssg radius=0 stroke=6  opacityssg=1.8 lb:ssg radius=0 stroke=6  opacityssg=1.8 lb:ssg radius=0 stroke=6 opacityssg=1.8 lb:ssg radius=0 stroke=6  opacityssg=1.8 lb:ssg radius=0 stroke=6  opacityssg=1.8 gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=1 std-dev-y=1 ] id=silly overlay aux=[ ref=silly emboss depth=1  ] id=cropaux crop aux=[ ref=cropaux ] median-blur abyss-policy=none radius=0 id=2 gimp:layer-mode layer-mode=grain-merge composite-mode=clip-to-backdrop opacity=0.5  aux=[  ref=2 lb:bevel type=sharpbevel   radius1=7 radius2=0 bevel1=45 bevel2=21 th=0.1 azimuth=40.0 slideupblack=0 metric=chebyshev smooth=0 ] dst-over  aux=[ ref=contain lb:custom-bevel gaus=1 box=2 ]  median-blur abyss-policy=none radius=0 "\

#define g4 \
" id=contain src aux=[ ref=contain levels out-low=0.10 id=1 dst-out aux=[ ref=1 median-blur abyss-policy=none radius=5 alpha-percentile=0 lb:ssg radius=0 stroke=8 opacityssg=1.8 lb:ssg radius=0 stroke=8  opacityssg=1.8 lb:ssg radius=0 stroke=8  opacityssg=1.8 lb:ssg radius=0 stroke=8 opacityssg=1.8 lb:ssg radius=0 stroke=8  opacityssg=1.8 lb:ssg radius=0 stroke=8  opacityssg=1.8 lb:ssg radius=0 stroke=8 opacityssg=1.8 lb:ssg radius=0 stroke=8  opacityssg=1.8 lb:ssg radius=0 stroke=8  opacityssg=1.8 gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=1 std-dev-y=1 ] id=silly overlay aux=[ ref=silly emboss depth=1  ] id=cropaux crop aux=[ ref=cropaux ] median-blur abyss-policy=none radius=0 id=2 gimp:layer-mode layer-mode=grain-merge composite-mode=clip-to-backdrop opacity=0.5  aux=[  ref=2 lb:bevel type=sharpbevel   radius1=7 radius2=0 bevel1=45 bevel2=21 th=0.1 azimuth=40.0 slideupblack=0 metric=chebyshev smooth=0 ] dst-over  aux=[ ref=contain lb:custom-bevel gaus=1 box=2 ]  median-blur abyss-policy=none radius=0 "\

#define g5 \
" id=blendit gimp:layer-mode layer-mode=multiply composite-mode=clip-to-backdrop  aux=[ ref=blendit  id=1 gimp:layer-mode layer-mode=normal composite-mode=clip-to-backdrop aux=[color value=#ffffff  opacity value=10 ] gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=1 std-dev-y=1 box-blur radius=11 emboss azimuth=44.0 depth=3 emboss depth=20 elevation=90.0 emboss elevation=40.0 depth=20 ] "\


#define g6 \
" id=blendit gimp:layer-mode layer-mode=grain-merge composite-mode=clip-to-backdrop  aux=[ ref=blendit  id=1 gimp:layer-mode layer-mode=normal composite-mode=clip-to-backdrop aux=[color value=#ffffff  opacity value=10 ] gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=1 std-dev-y=1 box-blur radius=11 emboss azimuth=44.0 depth=3 emboss depth=20 elevation=90.0 emboss elevation=40.0 depth=20 ] "\


#define g7 \
" lb:ring lb:gold expand=5.0 blendmode=colordodge expand=2.5720000000000001 elevation=10.0 medianradius=1 huerotate=0 desaturate=1.3999999999999999 light=1 "\


#define g8 \
" distance-transform   threshold-hi=0.7 metric=chebyshev color-to-alpha color=#000000 color-overlay value=#f587ff  id=3 screen aux=[ ref=3  emboss  type=bumpmap azimuth=90.0 depth=20  elevation=15.0 ]  gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=3 std-dev-y=3 id=3 screen aux=[ ref=3  emboss  type=bumpmap azimuth=90.0  depth=20    elevation=15.0 ]  median-blur abyss-policy=none  percentile=90 alpha-percentile=61 screen aux=[ ref=3  emboss  type=bumpmap azimuth=90.0  elevation=15.0 ]  median-blur abyss-policy=none percentile=90 alpha-percentile=100 screen aux=[ ref=3  emboss  type=bumpmap azimuth=90.0   depth=20   elevation=15.0 ]  opacity value=7.0 median-blur abyss-policy=none radius=0 unsharp-mask scale=0.9 median-blur abyss-policy=none radius=0 "\

#define g9 \
" lb:ring  color-overlay value=#f587ff median-blur  percentile=20 alpha-percentile=30 gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=2 std-dev-y=2 id=3 screen aux=[ ref=3  emboss  type=bumpmap azimuth=90.0  elevation=15.0 ]  gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=2 std-dev-y=2 id=3 screen aux=[ ref=3  emboss  type=bumpmap azimuth=90.0  elevation=15.0 ]  screen aux=[ ref=3  emboss  type=bumpmap azimuth=90.0  elevation=15.0 ]  opacity value=10.0 median-blur abyss-policy=none radius=0 "\

#define g10 \
" id=contain src aux=[ ref=contain levels out-low=0.10 id=1 dst-out aux=[ ref=1 median-blur abyss-policy=none radius=5 alpha-percentile=0 lb:ssg radius=0 stroke=7 opacityssg=1.53 lb:ssg radius=0 stroke=7 opacityssg=1.53 lb:ssg radius=0 stroke=7 opacityssg=1.53 ] id=cropaux crop aux=[ ref=cropaux ] median-blur abyss-policy=none radius=0 id=2 gimp:layer-mode layer-mode=grain-merge composite-mode=clip-to-backdrop opacity=0.5  aux=[  ref=2 lb:bevel type=sharpbevel radius1=7 radius2=0 bevel1=45 bevel2=21 th=0.1 azimuth=40.0 slideupblack=0 metric=chebyshev smooth=0 ] dst-over  aux=[ ref=contain lb:custom-bevel gaus=1 box=2 ] unsharp-mask scale=0.9 \ median-blur abyss-policy=none radius=0"\


#define g11 \
" color-overlay value=#3b3b3b gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=2 std-dev-y=2 id=1  overlay aux=[ ref=1 emboss  depth=59 elevation=30.0 opacity value=0.3   ] lb:threshold-alpha id=x gimp:layer-mode layer-mode=softlight composite-mode=auto aux=[ ref=x cell-noise seed=4345 scale=16 color-to-alpha color=black opacity value=1.2  ] id=y gimp:layer-mode layer-mode=softlight composite-mode=auto aux=[ ref=y cell-noise seed=12345 shape=01  scale=0.7 color-to-alpha color=white opacity value=0.75  gimp:threshold-alpha noise-spread amount-x=30 amount-y=30  box-blur radius=1 opacity value=1.7   ] id=x2 gimp:layer-mode layer-mode=softlight composite-mode=auto aux=[ ref=x2 lb:chrome  ] multiply value=3 bloom radius=0 strength=65 id=x3 gimp:layer-mode layer-mode=exclusion composite-mode=auto opacity=0.05  aux=[ ref=x3 emboss depth=30  elevation=30.0  ] mean-curvature-blur iterations=2 id=x4 gimp:layer-mode layer-mode=softlight composite-mode=auto aux=[ ref=x4 sinus x-scale=208.02 y-scale=208.02 complexity=1.012 seed=2050109389 tiling=yes perturbation=yes color1=#8c8c8c color2=#000000 blend-mode=bilinear blend-power=1.905 opacity value=1.2 ]   "\


#define g12 \
" nop   "\

#define g13 \
"  color-overlay value=white gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=1 std-dev-y=1 emboss depth=20 gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=1 std-dev-y=1 emboss depth=20   "\

#define g14 \
"  color-overlay value=white gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=3 std-dev-y=3 emboss depth=20 gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=3 std-dev-y=3 emboss depth=20   "\



#define g15 \
"  color-overlay value=white gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=4 std-dev-y=4 emboss depth=90 elevation=9.0 edge amount=2 algorithm=prewitt gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=1 std-dev-y=1 opacity value=2.0 lb:threshold-alpha levels in-high=0.7 out-high=0.65 id=3 gimp:layer-mode layer-mode=replace opacity=0.6 aux=[ ref=3  color-overlay value=black ] median-blur radius=0 abyss-policy=none "\

#define g16 \
"  id=0 over aux=[ ref=0 id=1 median-blur abyss-policy=none radius=20 alpha-percentile=100 src-in aux=[ ref=1 id=2 gimp:layer-mode layer-mode=split  aux=[ ref=2 color-overlay value=#ffffff gimp:layer-mode layer-mode=behind opacity=1.00 aux=[ color value=#000000  ]  gimp:layer-mode layer-mode=color-erase opacity=1.00 aux=[ color value=#ffffff ] id=cropaux2 crop aux=[ ref=cropaux2 ] median-blur abyss-policy=none radius=7 alpha-percentile=100 gaussian-blur color-overlay value=#ffffff gimp:layer-mode layer-mode=behind opacity=1.00 aux=[ color value=#000000  ]  gimp:layer-mode layer-mode=color-erase opacity=1.00 aux=[ color value=#ffffff ] id=cropaux crop aux=[ ref=cropaux ] ] id=3 median-blur abyss-policy=none radius=8 alpha-percentile=70 src-in aux=[ ref=3 levels out-low=0.01  gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=2 std-dev-y=2 lb:custom-bevel  depth=6 blendmode=Multiply gaus=1 box=1 elevation=70.0 size=0.3 opacity=1.7 opacity value=0.95   ] ] nop ] lb:edgesmooth lb:threshold-alpha median-blur abyss-policy=none radius=0 "\

#define g17 \
"    id=0 over aux=[ ref=0 id=1 median-blur abyss-policy=none radius=20 alpha-percentile=100 src-in aux=[ ref=1 id=2 gimp:layer-mode layer-mode=split  aux=[ ref=2 color-overlay value=#ffffff gimp:layer-mode layer-mode=behind opacity=1.00 aux=[ color value=#000000  ]  gimp:layer-mode layer-mode=color-erase opacity=1.00 aux=[ color value=#ffffff ] id=cropaux crop aux=[ ref=cropaux ] median-blur abyss-policy=none radius=12 alpha-percentile=100 gaussian-blur  abyss-policy=none  clip-extent=false color-overlay value=#ffffff gimp:layer-mode layer-mode=behind opacity=1.00 aux=[ color value=#000000  ]  gimp:layer-mode layer-mode=color-erase opacity=1.00 aux=[ color value=#ffffff ] id=cropaux2 crop aux=[ ref=cropaux2 ] ] id=3 median-blur abyss-policy=none radius=8 alpha-percentile=70 src-in aux=[ ref=3 levels out-low=0.01  gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=2 std-dev-y=2 lb:custom-bevel  depth=6 blendmode=Multiply gaus=1 box=1 elevation=70.0 size=0.3 opacity=1.7 opacity value=0.95   ] ] nop ] lb:edgesmooth lb:threshold-alpha median-blur abyss-policy=none radius=0 "\

#define g18 \
"  id=0 over aux=[ ref=0 id=1 median-blur abyss-policy=none radius=20 alpha-percentile=100 src-in aux=[ ref=1 id=2 gimp:layer-mode layer-mode=split  aux=[ ref=2 color-overlay value=#ffffff gimp:layer-mode layer-mode=behind opacity=1.00 aux=[ color value=#000000  ]  gimp:layer-mode layer-mode=color-erase opacity=1.00 aux=[ color value=#ffffff ] id=bcrop2 crop aux=[ ref=bcrop2 ] median-blur abyss-policy=none radius=16 alpha-percentile=100 gaussian-blur  abyss-policy=none  clip-extent=false color-overlay value=#ffffff gimp:layer-mode layer-mode=behind opacity=1.00 aux=[ color value=#000000  ]  gimp:layer-mode layer-mode=color-erase opacity=1.00 aux=[ color value=#ffffff ] id=bcrop crop aux=[ ref=bcrop ] ] id=3 median-blur  abyss-policy=none radius=8 alpha-percentile=70 src-in aux=[ ref=3 levels out-low=0.01  gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=2 std-dev-y=2 lb:custom-bevel  depth=6 blendmode=Multiply gaus=1 box=1 elevation=70.0 size=0.3 opacity=1.7 opacity value=0.95   ] ] nop ] lb:edgesmooth lb:threshold-alpha median-blur abyss-policy=none radius=0 "\

#define g19 \
" color-overlay value=white id=x gimp:layer-mode layer-mode=normal blend-space=rgb-linear aux=[ ref=x  id=s gimp:layer-mode layer-mode=behind opacity=0.31  aux=[ ref=s   gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=14 std-dev-y=14 color-to-alpha color=#000000 emboss depth=39 elevation=65.0 opacity value=4 ]  ] lb:edgesmooth lb:edgesmooth gimp:layer-mode layer-mode=split composite-mode=auto aux=[ ref=x   ] over aux=[  ref=x lb:innerglow value2=#000000 radius=4 fixoutline=68  ] id=am gimp:layer-mode layer-mode=overlay composite-space=rgb-perceptual aux=[ ref=am gegl:alien-map color-model=rgb cpn-1-frequency=7.6059999999999999 cpn-2-frequency=10.3 cpn-3-frequency=6.13 cpn-1-phaseshift=0 cpn-2-phaseshift=0 cpn-3-phaseshift=0 cpn-1-keep=no cpn-2-keep=no cpn-3-keep=no cubism tile-size=3 gimp:desaturate mean-curvature-blur iterations=1 ] id=all  gimp:layer-mode layer-mode=grain-merge composite-space=rgb-perceptual aux=[ ref=all  ] gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=1 std-dev-y=1 gimp:desaturate "\

#define g20 \
" color-overlay value=white lb:custom-bevel gaus=8 box=4  opacity=3.0 coloroverlay=#90baff blendmode=Hardlight size=7 alphapercentile=5  alien-map cpn-1-frequency=12 cpn-2-frequency=1.0 cpn-2-frequency=6.0 gimp:desaturate mode=luminance noise-reduction iterations=1 id=color gimp:layer-mode layer-mode=hsl-color composite-mode=auto opacity=0.86  composite-mode=auto  aux=[ ref=color color value=#c29a23] levels in-low=0.01 id=blendthis median-blur abyss-policy=none radius=0 id=blendthis gimp:layer-mode layer-mode=hsv-value opacity=0.3 aux=[ ref=blendthis  softglow  ] bloom radius=0.36 strength=18 median-blur abyss-policy=none radius=0 gegl:opacity value=2.0 lb:threshold-alpha id=blendburn gimp:layer-mode layer-mode=linear-burn opacity=0.02 aux=[ ref=blendburn ] median-blur radius=0 abyss-policy=none "\

#define g21 \
" color-overlay value=#ffd44f gegl:dropshadow x=0.00  y=0.00 radius=1.00 grow-shape=circle grow-radius=1 opacity=1   color=#3b3b3b gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=4 std-dev-y=3 emboss type=bumpmap depth=41 elevation=55.0 azimuth=12.0 unsharp-mask scale=1 gimp:threshold-alpha  bloom strength=25 id=noise2  divide    aux=[ ref=noise2 simplex-noise scale=12 invert box-blur radius=1  ]  id=1 multiply aux=[ linear-gradient start-color=#ffffff end-color=#000000 start-x=256 start-y=346 end-x=256 end-y=-54 ] id=noise  multiply aux=[ ref=noise color-overlay value=#ffffff  noise-cie-lch chroma-distance=0 holdness=2 crop gaussian-blur  abyss-policy=none  clip-extent=false std-dev-x=1 std-dev-y=1   ]  id=sg soft-light  aux=[  ref=sg softglow opacity value=0.7 id=bcrop crop aux=[ ref=bcrop ] dropshadow x=5 y=0 opacity=0.45 ] id=bcrop3 crop aux=[ ref=bcrop3 ] id=gold opacity value=2.0 hue-chroma lightness=16  chroma=7 gimp:layer-mode layer-mode=behind opacity=0.63 aux=[ ref=gold  lens-blur radius=2 id=bcrop2 crop aux=[ ref=bcrop2 ] aux=[ ref=bcrop ]   ] exposure exposure=-0.1 lb:threshold-alpha alphadegree=0.8 "\


#define g22 \
" lb:glossy-balloon gaus=5.5 id=1  gimp:layer-mode layer-mode=color-erase aux=[ ref=1 opacity value=1.5    lb:edge-extract edgeamount=3.8170000000000002 threshold=0.28399999999999997 gaus=18.190000000000001 value=#ff00fd ] lb:threshold-alpha median-blur abyss-policy=none radius=0 "\


#define g23 \
" lb:glossy-balloon gaus=8.5 id=1  gimp:layer-mode layer-mode=color-erase aux=[ ref=1 opacity value=2.0    lb:edge-extract edgeamount=3.8170000000000002 threshold=0.28399999999999997 gaus=18.190000000000001 value=#ff00fd ] lb:threshold-alpha median-blur abyss-policy=none radius=0 "\


#define g24 \
"  lb:glossy-balloon gaus=11.5 id=1  gimp:layer-mode layer-mode=color-erase aux=[ ref=1 opacity value=2.4    lb:edge-extract edgeamount=3.8170000000000002 threshold=0.28399999999999997 gaus=18.190000000000001 value=#ff00fd ]  lb:threshold-alpha median-blur abyss-policy=none radius=0 "\



#define g25 \
" nop    "\

#define g26 \
" nop "\

property_enum (crazybevel, _("Select a crazy bevel effect:"),
    nichebevel, niche_bevel,
    crazy1)
   description  (_("Choose a niche bevel effect from the list. These bevels would be tedious to turn into individual plugins, so they are just all put in a drop down list here."))

property_int  (radius, _("Size Control"), 3)
  value_range (0, 10)
  ui_range    (0, 10)
  ui_meta     ("unit", "pixel-distance")
  description (_("Median Radius for size control of the bevels"))

property_double (saturation, _("Saturation Boost"), 1)
  value_range (0.0, 2.0)
  ui_range    (0.0, 2.0)
  ui_meta     ("unit", "pixel-distance")
  description (_("Saturation control. If the bevel you choose is desaturated and lightened you can make it any color you want using Gimp's other tools."))

property_double (lightness, _("Lightness"), 0)
  value_range (-10.0, 10.0)
  ui_range    (-10.0, 10.0)
  ui_meta     ("unit", "pixel-distance")
  description (_("Light Control.  If the bevel you choose is desaturated and lightened you can make it any color you want using Gimp's other tools.  "))


enum_start (niche_bevel)
  enum_value (crazy1,      "crazy1",
              N_("9 Rings Sharp Bevel (Grain Merge) Size=2"))
  enum_value (crazy2,      "crazy2",
              N_("9 Rings Sharp Bevel (Grain Merge) Size=4"))
  enum_value (crazy3,      "crazy3",
              N_("9 Rings Sharp Bevel (Grain Merge) Size=6"))
  enum_value (crazy4,      "crazy4",
              N_("9 Rings Sharp Bevel (Grain Merge) Size=8"))
  enum_value (crazy5,      "crazy5",
              N_("Deep Carvings (Multiply)"))
  enum_value (crazy6,      "crazy6",
              N_("Deep Carvings (Grain Merge)"))
  enum_value (crazy7,      "crazy7",
              N_("Gold Rings"))
  enum_value (crazy8,      "crazy8",
              N_("Sharp Glossy Balloon"))
  enum_value (crazy9,      "crazy9",
              N_("Ringed Glossy Balloon"))
  enum_value (crazy10,      "crazy10",
              N_("Sharp Bevel + Faint Rings (Grain Merge)"))
  enum_value (crazy11,      "crazy11",
              N_("Rusted Cracked Metal"))
  enum_value (crazy12,      "crazy12",
              N_("NO CONTENT YET"))
  enum_value (crazy13,      "crazy13",
              N_("(TO BLEND) Default Bevel Doubled"))
  enum_value (crazy14,      "crazy14",
              N_("(TO BLEND) Default Bevel Doubled 2"))
  enum_value (crazy15,      "crazy15",
              N_("Glossed Black Bevel"))
  enum_value (crazy16,      "crazy16",
              N_("Outline Edges Only Bevel (small)"))
  enum_value (crazy17,      "crazy17",
              N_("Outline Edges Only Bevel (medium)"))
  enum_value (crazy18,      "crazy18",
              N_("Outline Edges Only Bevel (large)"))
  enum_value (crazy19,      "crazy19",
              N_("(TO BLEND WITH LCH LIGHTNESS) Burned Chisel"))
  enum_value (crazy20,      "crazy20",
              N_("Gold Bump Bevel (Hard Light)"))
  enum_value (crazy21,      "crazy21",
              N_("Fake Gold"))
  enum_value (crazy22,      "crazy22",
              N_("Transparent Glossy Balloon (low inflation)"))
  enum_value (crazy23,      "crazy23",
              N_("Transparent Glossy Balloon (mid-high inflation)"))
  enum_value (crazy24,      "crazy24",
              N_("Transparent Glossy Balloon (high inflation)"))
  enum_value (crazy25,      "crazy25",
              N_("NO CONTENT YET"))
  enum_value (crazy26,      "crazy26",
              N_("NO CONTENT YET"))
enum_end (nichebevel)

#else

#define GEGL_OP_META
#define GEGL_OP_NAME     crazy_bevel_collection
#define GEGL_OP_C_SOURCE crazy_bevel_collection.c

#include "gegl-op.h"

typedef struct
{
 GeglNode *input;
 GeglNode *sizecontrol;
 GeglNode *saturation;
 GeglNode *light;
 GeglNode *color;
 GeglNode *a;
 GeglNode *b;
 GeglNode *c;
 GeglNode *d;
 GeglNode *e;
 GeglNode *f;
 GeglNode *g;
 GeglNode *h;
 GeglNode *i;
 GeglNode *j;
 GeglNode *k;
 GeglNode *l;
 GeglNode *m;
 GeglNode *n;
 GeglNode *o;
 GeglNode *p;
 GeglNode *q;
 GeglNode *r;
 GeglNode *s;
 GeglNode *t;
 GeglNode *u;
 GeglNode *v;
 GeglNode *w;
 GeglNode *x;
 GeglNode *y;
 GeglNode *z;
 GeglNode *output;
}State;


static void attach (GeglOperation *operation)
{
  GeglNode *gegl = operation->node;
  GeglProperties *o = GEGL_PROPERTIES (operation);

  State *state = o->user_data = g_malloc0 (sizeof (State));

  state->input    = gegl_node_get_input_proxy (gegl, "input");
  state->output   = gegl_node_get_output_proxy (gegl, "output");

  state->a    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g1,
                                  NULL);

  state->b    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g2,
                                  NULL);

  state->c    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g3,
                                  NULL);

  state->d    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g4,
                                  NULL);

  state->e    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g5,
                                  NULL);

  state->f    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g6,
                                  NULL);

  state->g    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g7,
                                  NULL);

  state->h    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g8,
                                  NULL);

  state->i    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g9,
                                  NULL);

  state->j    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g10,
                                  NULL);

  state->k    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g11,
                                  NULL);

  state->l    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g12,
                                  NULL);

  state->m    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g13,
                                  NULL);

  state->n    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g14,
                                  NULL);

  state->o    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g15,
                                  NULL);

  state->p    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g16,
                                  NULL);

  state->q    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g17,
                                  NULL);

  state->r    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g18,
                                  NULL);

  state->s    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g19,
                                  NULL);

  state->t    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g20,
                                  NULL);

  state->u    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g21,
                                  NULL);

  state->v    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g22,
                                  NULL);

  state->w    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g23,
                                  NULL);

  state->x    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g24,
                                  NULL);

  state->y    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g25,
                                  NULL);

  state->z    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", g26,
                                  NULL);

  state->saturation    = gegl_node_new_child (gegl,
                                  "operation", "gegl:saturation",
                                  NULL);

  state->sizecontrol    = gegl_node_new_child (gegl,
                                  "operation", "gegl:median-blur",  "abyss-policy",     GEGL_ABYSS_NONE, "alpha-percentile", 100.0,
                                  NULL);


  state->light    = gegl_node_new_child (gegl,
                                  "operation", "gegl:hue-chroma",
                                  NULL);
  gegl_operation_meta_redirect (operation, "radius",  state->sizecontrol, "radius");
  gegl_operation_meta_redirect (operation, "saturation",  state->saturation, "scale");
  gegl_operation_meta_redirect (operation, "lightness",  state->light, "lightness");

}

static void update_graph (GeglOperation *operation)
{
  GeglProperties *o = GEGL_PROPERTIES (operation);
  State *state = o->user_data;
  if (!state) return;

switch (o->crazybevel) {
        break;
    case crazy1:
  gegl_node_link_many (state->input, state->sizecontrol, state->a, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy2:
  gegl_node_link_many (state->input, state->sizecontrol, state->b, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy3:
  gegl_node_link_many (state->input, state->sizecontrol, state->c, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy4:
  gegl_node_link_many (state->input, state->sizecontrol, state->d, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy5:
  gegl_node_link_many (state->input, state->sizecontrol, state->e, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy6:
  gegl_node_link_many (state->input, state->sizecontrol, state->f, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy7:
  gegl_node_link_many (state->input, state->sizecontrol, state->g, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy8:
  gegl_node_link_many (state->input, state->sizecontrol, state->h, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy9:
  gegl_node_link_many (state->input, state->sizecontrol, state->i, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy10:
  gegl_node_link_many (state->input, state->sizecontrol, state->j, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy11:
  gegl_node_link_many (state->input, state->sizecontrol, state->k, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy12:
  gegl_node_link_many (state->input, state->sizecontrol, state->l, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy13:
  gegl_node_link_many (state->input, state->sizecontrol, state->m, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy14:
  gegl_node_link_many (state->input, state->sizecontrol, state->n, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy15:
  gegl_node_link_many (state->input, state->sizecontrol, state->o, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy16:
  gegl_node_link_many (state->input, state->sizecontrol, state->p, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy17:
  gegl_node_link_many (state->input, state->sizecontrol, state->q, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy18:
  gegl_node_link_many (state->input, state->sizecontrol, state->r, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy19:
  gegl_node_link_many (state->input, state->sizecontrol, state->s, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy20:
  gegl_node_link_many (state->input, state->sizecontrol, state->t, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy21:
  gegl_node_link_many (state->input, state->sizecontrol, state->u, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy22:
  gegl_node_link_many (state->input, state->sizecontrol, state->v, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy23:
  gegl_node_link_many (state->input, state->sizecontrol, state->w, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy24:
  gegl_node_link_many (state->input, state->sizecontrol, state->x, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy25:
  gegl_node_link_many (state->input, state->sizecontrol, state->y, state->saturation,  state->light, state->output,  NULL);
        break;
    case crazy26:
  gegl_node_link_many (state->input, state->sizecontrol, state->z, state->saturation,  state->light, state->output,  NULL);

    }
  }

static void
gegl_op_class_init (GeglOpClass *klass)
{
  GeglOperationClass *operation_class;
GeglOperationMetaClass *operation_meta_class = GEGL_OPERATION_META_CLASS (klass);
  operation_class = GEGL_OPERATION_CLASS (klass);

  operation_class->attach = attach;
  operation_meta_class->update = update_graph;

  gegl_operation_class_set_keys (operation_class,
    "name",        "lb:bevelcollection",
    "title",       _("Text Style Collection (Bevel Type)"),
    "reference-hash", "afgjaksharpa3rings",
    "description", _("Collection of Bevel/Bump algorithms that do not fit with any other plugin of mine or have not yet been properly converted into a full editable filter. All these filters have very limited editability and nothing unique. One day some of these bevel algorithms may be stand alone filters with complete editable options. Filters with the 'TO BLEND' option are meant to be used with 'blend modes/blending options'. "),
    "gimp:menu-path", "<Image>/Filters/Text Styling",
    "gimp:menu-label", _("Misc Bevel Collection..."),
    NULL);
}

#endif
