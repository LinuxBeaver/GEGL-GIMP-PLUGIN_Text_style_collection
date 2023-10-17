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
 * Copyright 2006 Øyvind Kolås <pippin@gimp.org>
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
"  id=contain src aux=[ ref=contain levels out-low=0.10 id=1 dst-out aux=[ ref=1 median-blur radius=5 alpha-percentile=0 ssg radius=0 stroke=2 opacityssg=1.8 ssg radius=0 stroke=2  opacityssg=1.8 ssg radius=0 stroke=2  opacityssg=1.8 ssg radius=0 stroke=2 opacityssg=1.8 ssg radius=0 stroke=2  opacityssg=1.8 ssg radius=0 stroke=2  opacityssg=1.8 ssg radius=0 stroke=2 opacityssg=1.8 ssg radius=0 stroke=2  opacityssg=1.8 ssg radius=0 stroke=2  opacityssg=1.8 gaussian-blur std-dev-x=1 std-dev-y=1 ] id=fucky overlay aux=[ ref=fucky emboss depth=1  ] crop median-blur radius=0 id=2 gimp:layer-mode layer-mode=grain-merge composite-mode=clip-to-backdrop opacity=0.5  aux=[  ref=2 lb:bevel type=sharpbevel radius1=7 radius2=0 bevel1=45 bevel2=21 th=0.1 azimuth=40 slideupblack=0 metric=chebyshev smooth=0 ] dst-over  aux=[ ref=contain custom-bevel gaus=1 box=2 ]  median-blur radius=0 "\


#define g2 \
" id=contain src aux=[ ref=contain levels out-low=0.10 id=1 dst-out aux=[ ref=1 median-blur radius=5 alpha-percentile=0 ssg radius=0 stroke=4 opacityssg=1.8 ssg radius=0 stroke=4  opacityssg=1.8 ssg radius=0 stroke=4  opacityssg=1.8 ssg radius=0 stroke=4 opacityssg=1.8 ssg radius=0 stroke=4  opacityssg=1.8 ssg radius=0 stroke=4  opacityssg=1.8 ssg radius=0 stroke=4 opacityssg=1.8 ssg radius=0 stroke=4  opacityssg=1.8 ssg radius=0 stroke=4  opacityssg=1.8 gaussian-blur std-dev-x=1 std-dev-y=1 ] id=fucky overlay aux=[ ref=fucky emboss depth=1  ] crop median-blur radius=0 id=2 gimp:layer-mode layer-mode=grain-merge composite-mode=clip-to-backdrop opacity=0.5  aux=[  ref=2 lb:bevel type=sharpbevel radius1=7 radius2=0 bevel1=45 bevel2=21 th=0.1 azimuth=40 slideupblack=0 metric=chebyshev smooth=0 ] dst-over  aux=[ ref=contain custom-bevel gaus=1 box=2 ]  median-blur radius=0 "\


#define g3 \
" id=contain src aux=[ ref=contain levels out-low=0.10 id=1 dst-out aux=[ ref=1 median-blur radius=5 alpha-percentile=0 ssg radius=0 stroke=6 opacityssg=1.8 ssg radius=0 stroke=6  opacityssg=1.8 ssg radius=0 stroke=6  opacityssg=1.8 ssg radius=0 stroke=6 opacityssg=1.8 ssg radius=0 stroke=6  opacityssg=1.8 ssg radius=0 stroke=6  opacityssg=1.8 ssg radius=0 stroke=6 opacityssg=1.8 ssg radius=0 stroke=6  opacityssg=1.8 ssg radius=0 stroke=6  opacityssg=1.8 gaussian-blur std-dev-x=1 std-dev-y=1 ] id=fucky overlay aux=[ ref=fucky emboss depth=1  ] crop median-blur radius=0 id=2 gimp:layer-mode layer-mode=grain-merge composite-mode=clip-to-backdrop opacity=0.5  aux=[  ref=2 lb:bevel type=sharpbevel radius1=7 radius2=0 bevel1=45 bevel2=21 th=0.1 azimuth=40 slideupblack=0 metric=chebyshev smooth=0 ] dst-over  aux=[ ref=contain custom-bevel gaus=1 box=2 ]  median-blur radius=0 "\

#define g4 \
" id=contain src aux=[ ref=contain levels out-low=0.10 id=1 dst-out aux=[ ref=1 median-blur radius=5 alpha-percentile=0 ssg radius=0 stroke=8 opacityssg=1.8 ssg radius=0 stroke=8  opacityssg=1.8 ssg radius=0 stroke=8  opacityssg=1.8 ssg radius=0 stroke=8 opacityssg=1.8 ssg radius=0 stroke=8  opacityssg=1.8 ssg radius=0 stroke=8  opacityssg=1.8 ssg radius=0 stroke=8 opacityssg=1.8 ssg radius=0 stroke=8  opacityssg=1.8 ssg radius=0 stroke=8  opacityssg=1.8 gaussian-blur std-dev-x=1 std-dev-y=1 ] id=fucky overlay aux=[ ref=fucky emboss depth=1  ] crop median-blur radius=0 id=2 gimp:layer-mode layer-mode=grain-merge composite-mode=clip-to-backdrop opacity=0.5  aux=[  ref=2 lb:bevel type=sharpbevel radius1=7 radius2=0 bevel1=45 bevel2=21 th=0.1 azimuth=40 slideupblack=0 metric=chebyshev smooth=0 ] dst-over  aux=[ ref=contain custom-bevel gaus=1 box=2 ]  median-blur radius=0 "\

#define g5 \
" id=blendit gimp:layer-mode layer-mode=multiply composite-mode=clip-to-backdrop  aux=[ ref=blendit  id=1 gimp:layer-mode layer-mode=normal composite-mode=clip-to-backdrop aux=[color value=#ffffff  opacity value=11 ] gaussian-blur std-dev-x=1 std-dev-y=1 box-blur radius=11 emboss azimuth=44 depth=3 emboss depth=20 elevation=90 emboss elevation=40 depth=00 ] "\


#define g6 \
" id=blendit gimp:layer-mode layer-mode=grain-merge composite-mode=clip-to-backdrop  aux=[ ref=blendit  id=1 gimp:layer-mode layer-mode=normal composite-mode=clip-to-backdrop aux=[color value=#ffffff  opacity value=11 ] gaussian-blur std-dev-x=1 std-dev-y=1 box-blur radius=11 emboss azimuth=44 depth=3 emboss depth=20 elevation=90 emboss elevation=40 depth=00 ] "\


#define g7 \
" lb:ring lb:gold blendmode=colordodge expand=2.5720000000000001 azimuth=67 elevation=10.460000000000001 medianradius=1 huerotate=0 desaturate=1.3999999999999999 light=1 "\


#define g8 \
" distance-transform   threshold-hi=0.7 metric=chebyshev color-to-alpha color=#000000 color-overlay value=#f587ff  id=3 screen aux=[ ref=3  emboss  type=bumpmap azimuth=90 depth=0  elevation=15 ]  gaussian-blur std-dev-x=3 std-dev-y=3 id=3 screen aux=[ ref=3  emboss  type=bumpmap azimuth=90  depth=0    elevation=15 ]  median-blur  percentile=90 alpha-percentile=61 screen aux=[ ref=3  emboss  type=bumpmap azimuth=90  elevation=15 ]  median-blur  percentile=90 alpha-percentile=100 screen aux=[ ref=3  emboss  type=bumpmap azimuth=90   depth=0   elevation=15 ]  opacity value=7 median-blur radius=0 unsharp-mask scale=0.9 median-blur radius=0 "\

#define g9 \
" lb:ring  color-overlay value=#f587ff median-blur  percentile=20 alpha-percentile=30 gaussian-blur std-dev-x=2 std-dev-y=2 id=3 screen aux=[ ref=3  emboss  type=bumpmap azimuth=90  elevation=15 ]  gaussian-blur std-dev-x=2 std-dev-y=2 id=3 screen aux=[ ref=3  emboss  type=bumpmap azimuth=90  elevation=15 ]  screen aux=[ ref=3  emboss  type=bumpmap azimuth=90  elevation=15 ]  opacity value=10 median-blur radius=0 "\

#define g10 \
" id=contain src aux=[ ref=contain levels out-low=0.10 id=1 dst-out aux=[ ref=1 median-blur radius=5 alpha-percentile=0 ssg radius=0 stroke=7 opacityssg=1.53 ssg radius=0 stroke=7 opacityssg=1.53 ssg radius=0 stroke=7 opacityssg=1.53 ] crop median-blur radius=0 id=2 gimp:layer-mode layer-mode=grain-merge composite-mode=clip-to-backdrop opacity=0.5  aux=[  ref=2 lb:bevel type=sharpbevel radius1=7 radius2=0 bevel1=45 bevel2=21 th=0.1 azimuth=40 slideupblack=0 metric=chebyshev smooth=0 ] dst-over  aux=[ ref=contain custom-bevel gaus=1 box=2 ] unsharp-mask scale=0.9 \ median-blur radius=0"\


#define g11 \
" median-blur radius=25 alpha-percentile=20 cubism tile-size=5  tile-size=9 snn-mean gaussian-blur color-overlay value=#f95dff median-blur  percentile=90 alpha-percentile=290 gaussian-blur std-dev-x=4 std-dev-y=4 id=3 screen aux=[ ref=3  emboss  type=bumpmap azimuth=90  elevation=15 ]  median-blur  percentile=90 alpha-percentile=290 gaussian-blur std-dev-x=4 std-dev-y=4 id=3 screen aux=[ ref=3  emboss  type=bumpmap azimuth=90  elevation=15 ]  median-blur  percentile=90 alpha-percentile=290 screen aux=[ ref=3  emboss  type=bumpmap azimuth=90  elevation=15 ]  median-blur  percentile=90 alpha-percentile=290 screen aux=[ ref=3  emboss  type=bumpmap azimuth=90  elevation=15 ]  opacity value=10 median-blur radius=0 id=color gimp:layer-mode layer-mode=hsv-hue composite-mode=auto aux=[ ref=color  color value=#3c1200 ] levels in-low=0.250 in-high=1.924 out-low=0.056 out-high=0.610 opacity value=4 id=olsn gimp:layer-mode layer-mode=overlay composite-mode=auto opacity=0.16 aux=[ ref=olsn simplex-noise scale=2.31 iterations=1 seed=33  ] median-blur radius=0 lb:edgesmooth hue-chroma lightness=5 chroma=-8 median-blur radius=2 id=lchhuerecolor gimp:layer-mode composite-mode=auto layer-mode=lch-hue aux=[ ref=lchhuerecolor  color value=#ffca9e ] id=ba gimp:layer-mode layer-mode=burn blend-space=rgb-perceptual opacity=0.16 composite-mode=auto aux=[ ref=ba ] hue-chroma lightness=3 median-blur radius=0 bloom strength=50 median-blur radius=0  "\


#define g12 \
" id=n1 gaussian-blur std-dev-x=3 std-dev-y=3 color-overlay value=#52ebff id=0 gimp:layer-mode layer-mode=hardlight aux=[ ref=0 emboss depth=5 ] id=1 gimp:layer-mode layer-mode=hsl-color opacity=0.91 aux=[ ref=1 color-overlay value=#52ebff ] noise-reduction iterations=3 id=2 gimp:layer-mode layer-mode=overlay opacity=0.6 blend-space=rgb-perceptual aux=[ ref=2 wind direction=bottom style=blast threshold=1 seed=23 strength=1 oilify mask-radius=3 ] id=3 gimp:layer-mode layer-mode=softlight blend-space=rgb-perceptual opacity=0.90 aux=[ ref=1 lb:bevel bevel1=90 radius1=1 ] noise-reduction iterations=4 id=4 gimp:layer-mode layer-mode=overlay opacity=0.2 blend-space=rgb-linear aux=[ ref=4  edge-extract wind direction=bottom style=blast threshold=4 seed=13 strength=21 oilify mask-radius=2 custom-bevel box=1 gaus=1 depth=3 blendmode=Overlay coloroverlay=#a3e9ff ] opacity value=1.2 median-blur radius=0  softglow glow-radius=1 hue-chroma chroma=4 median-blur radius=0 id=5 gimp:layer-mode layer-mode=overlay aux=[ ref=5 edge  ] median-blur radius=0 saturation scale=0.5 mean-curvature-blur iterations=7 hue-chroma lightness=-3 gimp:layer-mode layer-mode=split opacity=0.20 aux=[ ref=n1 gaussian-blur ] id=got gimp:layer-mode layer-mode=linear-light opacity=0.75 aux=[ ref=got lb:glassovertext hyperopacity=1.5 azimuth=227 depth=20 ] median-blur radius=0 mean-curvature-blur iterations=1 id=sgh src-atop aux=[ ref=sgh softglow opacity value=0.94   ] id=ov gimp:layer-mode layer-mode=overlay opacity=0.30 aux=[ ref=ov emboss ] median-blur radius=0    "\

#define g13 \
"  color-overlay value=white gaussian-blur std-dev-x=1 std-dev-y=1 emboss depth=20 gaussian-blur std-dev-x=1 std-dev-y=1 emboss depth=20   "\

#define g14 \
"  color-overlay value=white gaussian-blur std-dev-x=3 std-dev-y=3 emboss depth=20 gaussian-blur std-dev-x=3 std-dev-y=3 emboss depth=20   "\

#define g14 \
"  color-overlay value=white  gaussian-blur std-dev-x=3 std-dev-y=3 emboss depth=60 gaussian-blur std-dev-x=3 std-dev-y=3 emboss depth=60  "\


#define g15 \
"  color-overlay value=white gaussian-blur std-dev-x=4 std-dev-y=4 emboss depth=90 elevation=9 edge amount=2 algorithm=prewitt gaussian-blur std-dev-x=1 std-dev-y=1 opacity value=2 lb:threshold-alpha levels in-high=0.7 out-high=0.65 id=3 gimp:layer-mode layer-mode=replace opacity=0.6 aux=[ ref=3  color-overlay value=black ] "\

#define g16 \
"  id=0 over aux=[ ref=0 id=1 median-blur radius=20 alpha-percentile=100 src-in aux=[ ref=1 id=2 gimp:layer-mode layer-mode=split  aux=[ ref=2 color-overlay value=#ffffff gimp:layer-mode layer-mode=behind opacity=1.00 aux=[ color value=#000000  ]  gimp:layer-mode layer-mode=color-erase opacity=1.00 aux=[ color value=#ffffff ] crop median-blur radius=7 alpha-percentile=100 gaussian-blur color-overlay value=#ffffff gimp:layer-mode layer-mode=behind opacity=1.00 aux=[ color value=#000000  ]  gimp:layer-mode layer-mode=color-erase opacity=1.00 aux=[ color value=#ffffff ] crop ] id=3 median-blur radius=8 alpha-percentile=70 src-in aux=[ ref=3 levels out-low=0.01  gaussian-blur std-dev-x=2 std-dev-y=2 custom-bevel  depth=6 blendmode=Multiply gaus=1 box=1 elevation=70 size=0.3 opacity=1.7 opacity value=0.95   ] ] nop ] lb:edgesmooth lb:threshold-alpha median-blur radius=0 "\

#define g17 \
"    id=0 over aux=[ ref=0 id=1 median-blur radius=20 alpha-percentile=100 src-in aux=[ ref=1 id=2 gimp:layer-mode layer-mode=split  aux=[ ref=2 color-overlay value=#ffffff gimp:layer-mode layer-mode=behind opacity=1.00 aux=[ color value=#000000  ]  gimp:layer-mode layer-mode=color-erase opacity=1.00 aux=[ color value=#ffffff ] crop median-blur radius=12 alpha-percentile=100 gaussian-blur color-overlay value=#ffffff gimp:layer-mode layer-mode=behind opacity=1.00 aux=[ color value=#000000  ]  gimp:layer-mode layer-mode=color-erase opacity=1.00 aux=[ color value=#ffffff ] crop ] id=3 median-blur radius=8 alpha-percentile=70 src-in aux=[ ref=3 levels out-low=0.01  gaussian-blur std-dev-x=2 std-dev-y=2 custom-bevel  depth=6 blendmode=Multiply gaus=1 box=1 elevation=70 size=0.3 opacity=1.7 opacity value=0.95   ] ] nop ] lb:edgesmooth lb:threshold-alpha median-blur radius=0 "\

#define g18 \
"  id=0 over aux=[ ref=0 id=1 median-blur radius=20 alpha-percentile=100 src-in aux=[ ref=1 id=2 gimp:layer-mode layer-mode=split  aux=[ ref=2 color-overlay value=#ffffff gimp:layer-mode layer-mode=behind opacity=1.00 aux=[ color value=#000000  ]  gimp:layer-mode layer-mode=color-erase opacity=1.00 aux=[ color value=#ffffff ] crop median-blur radius=16 alpha-percentile=100 gaussian-blur color-overlay value=#ffffff gimp:layer-mode layer-mode=behind opacity=1.00 aux=[ color value=#000000  ]  gimp:layer-mode layer-mode=color-erase opacity=1.00 aux=[ color value=#ffffff ] crop ] id=3 median-blur radius=8 alpha-percentile=70 src-in aux=[ ref=3 levels out-low=0.01  gaussian-blur std-dev-x=2 std-dev-y=2 custom-bevel  depth=6 blendmode=Multiply gaus=1 box=1 elevation=70 size=0.3 opacity=1.7 opacity value=0.95   ] ] nop ] lb:edgesmooth lb:threshold-alpha median-blur radius=0 "\

#define g19 \
" color-overay value=white id=x gimp:layer-mode layer-mode=normal blend-space=rgb-linear aux=[ ref=x  id=s gimp:layer-mode layer-mode=behind opacity=0.31  aux=[ ref=s   gaussian-blur std-dev-x=14 std-dev-y=14 color-to-alpha color=#000000 emboss depth=39 elevation=65 opacity value=4 ]  ] lb:edgesmooth lb:edgesmooth gimp:layer-mode layer-mode=split composite-mode=auto aux=[ ref=x   ] over aux=[  ref=x lb:innerglow value2=#000000 radius=4 fixoutline=68  ] id=am gimp:layer-mode layer-mode=overlay composite-space=rgb-perceptual aux=[ ref=am gegl:alien-map color-model=rgb cpn-1-frequency=7.6059999999999999 cpn-2-frequency=10.359 cpn-3-frequency=6.1349999999999998 cpn-1-phaseshift=0 cpn-2-phaseshift=0 cpn-3-phaseshift=0 cpn-1-keep=no cpn-2-keep=no cpn-3-keep=no cubism tile-size=3 gimp:desaturate mean-curvature-blur iterations=1 ] id=all  gimp:layer-mode layer-mode=grain-merge composite-space=rgb-perceptual aux=[ ref=all  ] gaussian-blur std-dev-x=1 std-dev-y=1 gimp:desaturate "\

#define g20 \
" color-overlay value=white custom-bevel gaus=8 box=4  opacity=3.0 coloroverlay=#90baff blendmode=Hardlight azimuth=4  size=7 alphapercentile=5 elevation=1 alien-map cpn-1-frequency=12 cpn-2-frequency=23 cpn-2-frequency=6 gimp:desaturate mode=luminance noise-reduction iterations=1 id=color gimp:layer-mode layer-mode=hsl-color composite-mode=auto opacity=0.86  composite-mode=auto  aux=[ ref=color color value=#c29a23] levels in-low=0.01 id=blendthis median-blur radius=0 id=blendthis gimp:layer-mode layer-mode=hsv-value opacity=0.3 aux=[ ref=blendthis  softglow  ] bloom radius=0.36 strength=18 median-blur radius=0 gegl:opacity value=2 lb:threshold-alpha id=blendburn gimp:layer-mode layer-mode=linear-burn opacity=0.02 aux=[ ref=blendburn ] "\

#define g21 \
" id=1  color-overlay value=#ffd44f gegl:dropshadow x=0.00  y=0.00 radius=1.00 grow-shape=circle grow-radius=1 opacity=1   color=#3b3b3b gaussian-blur std-dev-x=4 std-dev-y=3 emboss type=bumpmap depth=41 elevation=55 azimuth=12 unsharp-mask scale=1 gimp:threshold-alpha ] bloom strength=25 id=noise2  divide    aux=[ ref=noise2 simplex-noise scale=12 invert box-blur radius=1  ]  id=1 multiply aux=[ linear-gradient start-color=#ffffff end-color=#000000 start-x=256 start-y=346 end-x=256 end-y=-54 ] id=noise  multiply aux=[ ref=noise color-overlay value=#ffffff  noise-cie-lch chroma-distance=0 holdness=2 crop gaussian-blur std-dev-x=1 std-dev-y=1   ]  id=sg soft-light  aux=[  ref=sg softglow opacity value=0.7 crop dropshadow x=5 y=0 opacity=0.45 ] crop id=gold opacity value=2 hue-chroma lightness=16  chroma=7 gimp:layer-mode layer-mode=behind opacity=0.63 aux=[ ref=gold  lens-blur radius=2 crop   ] exposure exposure=-0.1 lb:threshold-alpha alphadegree=4.5  "\

#define g22 \
" color-overlay value=#f40014 cubism tile-size=8 tile-saturation=22 seed=334 gaussian-blur std-dev-x=3 std-dev-y=3 id=1 gimp:layer-mode layer-mode=grain-extract aux=[ ref=1 lb:bevel radius1=50 bevel1=145 bevel2=92 th=0.60 azimuth=4229 ] box-blur radius=1 brightness-contrast brightness=-0.11 id=3 gimp:layer-mode layer-mode=linear-light  opacity=0.10 aux=[ ref=3 lb:bevel radius1=50  bevel1=145 bevel2=92 th=0.60 azimuth=4 ] opacity value=1.3 median-blur radius=1 alpha-percentile=10   "\


#define g23 \
" color-overlay value=white id=x cubism tile-size=4 seed=442 dst aux=[ ref=x median-blur radius=2  alpha-percentile=0 id=x2  ] color-overlay value=#ffffff cubism tile-size=4 seed=442 gaussian-blur std-dev-x=5 std-dev-y=5 id=1 gaussian-blur std-dev-x=6 std-dev-y=6 emboss  xor aux=[ ref=1     ] opacity value=2 emboss depth=20 over aux=[ ref=x2  lb:innerglow value2=black radius=5  opacity value=0.65 ] over aux=[ ref=x2  color-overlay value=#747474 opacity value=0.3 ] mean-curvature-blur  opacity value=2 softglow brightness=90 sharpness=90 glow-radius=50 softglow brightness=90 sharpness=90 glow-radius=40 median-blur radius=0 hue-chroma lightness=2 dst-over aux=[ ref=x median-blur radius=40 alpha-percentile=100 color-overlay value=#ee83ff  cubism tile-size=12 gaussian-blur std-dev-x=2 std-dev-y=2  custom-bevel blendmode=Plus ] saturation scale=1.25 median-blur radius=0 id=hslx gimp:layer-mode layer-mode=hsl-color composite-mode=auto aux=[ ref=hslx  id=melaniescake median-blur radius=0 over aux=[ ref=melaniescake starfield saturation-distance=0.045999999999999999  value-distance=0.050999999999999997  seed=0  out-high=3.972  gamma=6.8529999999999998  std-dev=0.52500000000000002  saturation=1  color-to-alpha color=black opacity value=2.2 median-blur radius= percentile=0 opacity value=2 ] gaussian-blur  std-dev-x=1.5 std-dev-y=1.5 median-blur radius=0 ] id=bottomcake  dst-over aux=[ ref=bottomcake id=bread dst-over aux=[ ref=bread color-overlay value=#ffc383   median-blur radius=25 alpha-percentile=100 id=texture gimp:layer-mode layer-mode=softlight opacity=0.84 composite-mode=auto aux=[ ref=texture noise-rgb noise-rgb noise-rgb noise-reduction iterations=1 ] id=recolorit gimp:layer-mode layer-mode=hsl-color aux=[ ref=recolorit color-overlay value=#ffd09f  ] ] median-blur radius=0  lb:extrusion behindextrusion=yes  center-x=0.083000000000000004  center-y=-2.6709999999999998  factor=0.014  depth=6 exposure=-0.97099999999999997  median-blur radius=0 id=lnburn gimp:layer-mode layer-mode=linear-burn composite-space=rgb-perceptual  opacity=0.011 aux=[ ref=lnburn ]  id=insidebread gimp:layer-mode layer-mode=normal opacity=0.08 aux=[ ref=insidebread noise-rgb noise-reduction iterations=1 ] ] median-blur radius=0 id=bevit gimp:layer-mode layer-mode=softlight opacity=0.34 composite-mode=auto aux=[ ref=bevit lb:bevel hue-chroma lightness=9 ] bloom strength=9 dropshadow  x=4.79 y=8.79 radius=8.14 grow-radius=0 color=#000000 opacity=1.04    "\


#define g24 \
" color-overlay value=white median-blur radius=8  alpha-percentile=20 gaussian-blur std-dev-x=2 std-dev-y=2 lb:threshold-alpha median-blur radius=8  alpha-percentile=20 gaussian-blur std-dev-x=2 std-dev-y=2 lb:threshold-alpha cubism tile-size=2 seed=442 id=x dst aux=[ ref=x median-blur radius=2  alpha-percentile=0 id=x2  ] color-overlay value=#ffffff cubism tile-size=10 seed=442 gaussian-blur std-dev-x=5 std-dev-y=5 id=1 gaussian-blur std-dev-x=6 std-dev-y=6 emboss  lb:threshold-alpha lb:threshold-alpha id=chocolate gimp:layer-mode layer-mode=grain-merge opacity=0.70 aux=[ ref=chocolate color-overlay value=#f579ff ] gimp:layer-mode layer-mode=split composite-space=auto aux=[ ref=1     ] opacity value=2 emboss depth=20 over aux=[ ref=x2  lb:innerglow value2=black radius=5  opacity value=0.65 ] over aux=[ ref=x2  color-overlay value=#f579ff opacity value=0.3 ] mean-curvature-blur  opacity value=2 softglow brightness=90 sharpness=90 glow-radius=50 softglow brightness=90 sharpness=90 glow-radius=40 median-blur radius=0 hue-chroma lightness=2 id=colorfrosting gimp:layer-mode layer-mode=hsl-color opacity=0.44 aux=[ ref=colorfrosting   median-blur radius=0 color-overlay  value=#ff0500 ] mean-curvature-blur iterations=3 lb:threshold-alpha dst-over aux=[ ref=x median-blur radius=40 alpha-percentile=100 color-overlay value=#934c00  cubism tile-size=12 gaussian-blur std-dev-x=2 std-dev-y=2  custom-bevel blendmode=Multiply ] saturation scale=1.25 median-blur radius=0 id=hslx gimp:layer-mode layer-mode=hsl-color composite-mode=auto aux=[ ref=hslx  id=melaniescake median-blur radius=0 gaussian-blur  std-dev-x=1.5 std-dev-y=1.5 median-blur radius=0 ] id=bottomcake  dst-over aux=[ ref=bottomcake id=bread dst-over aux=[ ref=bread color-overlay value=#ffc383   median-blur radius=25 alpha-percentile=100 id=texture gimp:layer-mode layer-mode=softlight opacity=0.84 composite-mode=auto aux=[ ref=texture noise-rgb noise-rgb noise-rgb noise-reduction iterations=1 ] id=recolorit gimp:layer-mode layer-mode=hsl-color aux=[ ref=recolorit color-overlay value=#ffd09f  ] ] median-blur radius=0  lb:extrusion behindextrusion=yes  center-x=0.083000000000000004  center-y=-2.6709999999999998  factor=0.014  depth=6 exposure=-0.97099999999999997  median-blur radius=0 id=lnburn gimp:layer-mode layer-mode=linear-burn composite-space=rgb-perceptual  opacity=0.011 aux=[ ref=lnburn ]  id=insidebread gimp:layer-mode layer-mode=normal opacity=0.08 aux=[ ref=insidebread noise-rgb noise-reduction iterations=1 ] ] median-blur radius=0 id=bevit gimp:layer-mode layer-mode=softlight opacity=0.34 composite-mode=auto aux=[ ref=bevit lb:bevel hue-chroma lightness=9 ] bloom strength=9 dropshadow  x=4.79 y=8.79 radius=8.14 grow-radius=0 color=#000000 opacity=1.04   "\

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
              N_("Bathroom humor text"))
  enum_value (crazy12,      "crazy12",
              N_("Ice Text"))
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
              N_("Gold Custom Bevel (Hard Light)"))
  enum_value (crazy21,      "crazy21",
              N_("Fake Gold"))
  enum_value (crazy22,      "crazy22",
              N_("Wax Text"))
  enum_value (crazy23,      "crazy23",
              N_("Strawberry Cake Text (WARNING - EXTREMELY SLOW)"))
  enum_value (crazy24,      "crazy24",
              N_("Chocolate Cake Text (WARNING - EXTREMELY SLOW)"))
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


  state->saturation    = gegl_node_new_child (gegl,
                                  "operation", "gegl:saturation",
                                  NULL);

  state->sizecontrol    = gegl_node_new_child (gegl,
                                  "operation", "gegl:median-blur", "alpha-percentile", 100.0,
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
    "title",       _("Misc Bevel and Bump Collection"),
    "reference-hash", "afgjaksharpa3rings",
    "description", _("Collection of Bevel/Bump algorithms that do not fit with any other plugin of mine or have not yet been properly converted into a full editable filter. All these filters have very limited editability and nothing unique. One day some of these bevel algorithms may be stand alone filters with complete editable options. Filters with the 'TO BLEND' option are meant to be used with 'blend modes/blending options'. "),
    "gimp:menu-path", "<Image>/Filters/Text Styling",
    "gimp:menu-label", _("Misc Bevel Collection"),
    NULL);
}

#endif
