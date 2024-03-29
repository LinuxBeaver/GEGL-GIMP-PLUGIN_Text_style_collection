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
"   color-overlay value=#f40014 cubism tile-size=8 tile-saturation=22 seed=334 gaussian-blur abyss-policy=none clip-extent=false  std-dev-x=3 std-dev-y=3 id=1 gimp:layer-mode layer-mode=grain-extract aux=[ ref=1 lb:bevel radius1=50 bevel1=145 bevel2=92 th=0.60 azimuth=4229 ] box-blur radius=1 brightness-contrast brightness=-0.11 id=3 gimp:layer-mode layer-mode=linear-light  opacity=0.10 aux=[ ref=3 lb:bevel radius1=50  bevel1=145 bevel2=92 th=0.60 azimuth=4 ] opacity value=1.3 median-blur abyss-policy=none radius=1 alpha-percentile=10 "\


#define g2 \
"  id=n1 gaussian-blur abyss-policy=none clip-extent=false std-dev-x=3 std-dev-y=3 color-overlay value=#52ebff id=0 gimp:layer-mode layer-mode=hardlight aux=[ ref=0 emboss depth=5 ] id=1 gimp:layer-mode layer-mode=hsl-color opacity=0.91 aux=[ ref=1 color-overlay value=#52ebff ] noise-reduction iterations=3 id=2 gimp:layer-mode layer-mode=overlay opacity=0.6 blend-space=rgb-perceptual aux=[ ref=2 wind direction=bottom style=blast threshold=1 seed=23 strength=1 oilify mask-radius=3 ] id=3 gimp:layer-mode layer-mode=softlight blend-space=rgb-perceptual opacity=0.90 aux=[ ref=1 lb:bevel bevel1=90 radius1=1 ] noise-reduction iterations=4 id=4 gimp:layer-mode layer-mode=overlay opacity=0.2 blend-space=rgb-linear aux=[ ref=4  lb:edge-extract wind direction=bottom style=blast threshold=4 seed=13 strength=21 oilify mask-radius=2 lb:custom-bevel box=1 gaus=1 depth=3 blendmode=Overlay coloroverlay=#a3e9ff ] opacity value=1.2 median-blur abyss-policy=none radius=0  softglow glow-radius=1 hue-chroma chroma=4 median-blur abyss-policy=none radius=0 id=5 gimp:layer-mode layer-mode=overlay aux=[ ref=5 edge  ] median-blur abyss-policy=none radius=0 saturation scale=0.5 mean-curvature-blur iterations=7 hue-chroma lightness=-3 gimp:layer-mode layer-mode=split opacity=0.20 aux=[ ref=n1 gaussian-blur abyss-policy=none clip-extent=false ] id=got gimp:layer-mode layer-mode=linear-light opacity=0.75 aux=[ ref=got lb:glassovertext hyperopacity=1.5 azimuth=227 depth=20 ] median-blur abyss-policy=none radius=0 mean-curvature-blur iterations=1 id=sgh src-atop aux=[ ref=sgh softglow opacity value=0.94   ] id=ov gimp:layer-mode layer-mode=overlay opacity=0.30 aux=[ ref=ov emboss ] median-blur abyss-policy=none radius=0 "\


#define g3 \
" median-blur abyss-policy=none radius=25 alpha-percentile=20 cubism tile-size=5  tile-size=9 snn-mean gaussian-blur abyss-policy=none clip-extent=false color-overlay value=#f95dff median-blur abyss-policy=none  percentile=90 alpha-percentile=290 gaussian-blur abyss-policy=none clip-extent=false std-dev-x=4 std-dev-y=4 id=3 screen aux=[ ref=3  emboss  type=bumpmap azimuth=90  elevation=15 ]  median-blur abyss-policy=none  percentile=90 alpha-percentile=290 gaussian-blur abyss-policy=none clip-extent=false std-dev-x=4 std-dev-y=4 id=3 screen aux=[ ref=3  emboss  type=bumpmap azimuth=90  elevation=15 ]  median-blur abyss-policy=none  percentile=90 alpha-percentile=290 screen aux=[ ref=3  emboss  type=bumpmap azimuth=90  elevation=15 ]  median-blur abyss-policy=none  percentile=90 alpha-percentile=290 screen aux=[ ref=3  emboss  type=bumpmap azimuth=90  elevation=15 ]  opacity value=10 median-blur abyss-policy=none radius=0 id=color gimp:layer-mode layer-mode=hsv-hue composite-mode=auto aux=[ ref=color  color value=#3c1200 ] levels in-low=0.250 in-high=1.924 out-low=0.056 out-high=0.610 opacity value=4 id=olsn gimp:layer-mode layer-mode=overlay composite-mode=auto opacity=0.16 aux=[ ref=olsn simplex-noise scale=2.31 iterations=1 seed=33  ] median-blur abyss-policy=none radius=0 lb:edgesmooth hue-chroma lightness=5 chroma=-8 median-blur abyss-policy=none radius=2 id=lchhuerecolor gimp:layer-mode composite-mode=auto layer-mode=lch-hue aux=[ ref=lchhuerecolor  color value=#ffca9e ] id=ba gimp:layer-mode layer-mode=burn blend-space=rgb-perceptual opacity=0.16 composite-mode=auto aux=[ ref=ba ] hue-chroma lightness=3 median-blur abyss-policy=none radius=0 bloom strength=50 median-blur abyss-policy=none radius=0 id=anotherhue gimp:layer-mode layer-mode=hsv-hue composite-mode=clip-to-backdrop aux=[ ref=anotherhue color value=#ff8200 ] "\




#define g4 \
" id=1 color-overlay value=red cubism tile-size=10 seed=23 median-blur abyss-policy=none radius=2 median-blur abyss-policy=none radius=9 alpha-percentile=70 neighborhood=diamond lb:threshold-alpha opacity value=1 median-blur abyss-policy=none radius=0 lb:custom-bevel depth=4 lb:custom-bevel blendmode=ColorDodge gimp:layer-mode layer-mode=hsl-color composite-mode=auto aux=[ ref=1  median-blur abyss-policy=none radius=50 alpha-percentile=100 ] "\



#define g5 \
" id=1 color-overlay value=#ff0f00 cubism tile-size=15 seed=23 median-blur abyss-policy=none radius=2 median-blur abyss-policy=none radius=9 alpha-percentile=70 neighborhood=diamond lb:threshold-alpha opacity value=1 median-blur abyss-policy=none radius=0 lb:custom-bevel depth=4 lb:custom-bevel blendmode=ColorDodge gimp:layer-mode layer-mode=hsl-color composite-mode=auto aux=[ ref=1  median-blur abyss-policy=none radius=50 alpha-percentile=100 ]  "\




#define g6 \
" id=1 color-overlay value=#ff0f00 cubism tile-size=14 seed=23 median-blur abyss-policy=none radius=2 median-blur abyss-policy=none radius=9 alpha-percentile=70 neighborhood=diamond lb:threshold-alpha opacity value=1 median-blur abyss-policy=none radius=0 lb:custom-bevel depth=4 lb:custom-bevel blendmode=ColorDodge gimp:layer-mode layer-mode=hsl-color composite-mode=auto aux=[ ref=1  median-blur abyss-policy=none radius=50 alpha-percentile=100 ]  "\





#define g7 \
" id=1 color-overlay value=red cubism tile-size=7 seed=93 median-blur abyss-policy=none radius=1 median-blur abyss-policy=none radius=4 alpha-percentile=70 neighborhood=diamond lb:threshold-alpha opacity value=1 median-blur abyss-policy=none radius=0 lb:custom-bevel depth=4 lb:custom-bevel blendmode=ColorDodge gimp:layer-mode layer-mode=hsl-color composite-mode=auto aux=[ ref=1  median-blur abyss-policy=none radius=50 alpha-percentile=100 ]   "\





#define g8 \
" cubism tile-size=1 emboss depth=2  "\

#define g9 \
" cubism tile-size=2 emboss depth=4 "\

#define g10 \
" gaussian-blur abyss-policy=none clip-extent=false std-dev-x=2 std-dev-y=2 id=1 lb:glassovertext over aux=[ ref=1 lb:ssg stroke=1 colorssg=#0a0028  blurstroke=2 opacityssg=2.5 ] gray "\




#define g11 \
" transform transform=matrix(0.85676532983779907,-0.083190269768238068,-1.0763975295356106e-19,0.15398488938808441,1.0494217872619629,-2.1621131194246602e-19,35.636863708496094,106.15763092041016,1)   sampler=nohalo gegl:color-overlay value=#dbdbdb svg:src-atop aux=[gegl:layer noise-solid levels in-low=-0.4        gimp:layer-mode layer-mode=grain-merge composite-mode=clip-to-backdrop aux=[ color value=#07ff00  ] ]  crop gaussian-blur abyss-policy=none clip-extent=false emboss  type=bumpmap azimuth=30 elevation=45 depth=12 gegl:dropshadow x=0.00  y=0 radius=0.00 grow-shape=circle grow-radius=1 opacity=2 color=#ffffff gegl:dropshadow x=0.00  y=0 radius=0.00 grow-shape=circle grow-radius=6 opacity=1 color=#ffffff gegl:dropshadow x=0.00  y=0.00 radius=0.00 grow-shape=circle grow-radius=6 opacity=1 color=#000000 gegl:dropshadow opacity=0.4 radius=0.1 x=-1.8 y=2.8 gegl:long-shadow style=finite angle=152.94 length=11 midpoint=100 midpoint-rel=0.5 color=#000000 composition=shadow-plus-image   "\




#define g12 \
" transform transform=matrix(1.0156650757686598,0.075701741929592628,0.000365746118200971,0.013317261513591921,1.2296272065975005,9.0806881192612718e-05,0,0,1)   sampler=nohalo sampler=nohalo gegl:color-overlay value=#dbdbdb svg:src-atop aux=[gegl:layer noise-solid levels in-low=-0.4       gimp:layer-mode layer-mode=grain-merge composite-mode=clip-to-backdrop aux=[ color value=#07ff00  ] ]  crop gaussian-blur abyss-policy=none clip-extent=false emboss  type=bumpmap azimuth=30 elevation=45 depth=12 gegl:dropshadow x=0.00  y=0 radius=0.00 grow-shape=circle grow-radius=1 opacity=2 color=#ffffff gegl:dropshadow x=0.00  y=0 radius=0.00 grow-shape=circle grow-radius=6 opacity=1 color=#ffffff gegl:dropshadow x=0.00  y=0.00 radius=0.00 grow-shape=circle grow-radius=6 opacity=1 color=#000000 gegl:dropshadow opacity=0.4 radius=0.1 x=-1.8 y=2.8 gegl:long-shadow style=finite angle=172.94 length=11 midpoint=100 midpoint-rel=0.5 color=#000000 composition=shadow-plus-image    "\




#define g13 \
" id=containall src aux=[ ref=containall color-overlay value=#00dfff cubism tile-size=7 seed=334 median-blur abyss-policy=none radius=11 id=1 gimp:layer-mode layer-mode=overlay opacity=0.45 aux=[  ref=1 emboss depth=20 denoise-dct sigma=35 ] lb:threshold-alpha id=2 over aux=[ ref=2 lb:glassovertext azimuth=33 depth=19   ] lb:edgesmooth value=2 id=3 gimp:layer-mode layer-mode=replace opacity=0.09 aux=[ ref=3 color-to-alpha color=#0ee2fd ] ] crop denoise-dct sigma=4 median-blur abyss-policy=none radius=0  "\


#define g14 \
"  id=containall src aux=[ ref=containall color-overlay value=#00dfff cubism tile-size=15 seed=33 median-blur abyss-policy=none radius=11 id=1 gimp:layer-mode layer-mode=overlay opacity=0.45 aux=[  ref=1 emboss depth=20 denoise-dct sigma=35 ] lb:threshold-alpha id=2 over aux=[ ref=2 lb:glassovertext azimuth=33 depth=19   ] lb:edgesmooth value=2 id=3 gimp:layer-mode layer-mode=replace opacity=0.09 aux=[ ref=3 color-to-alpha color=#0ee2fd ] ] crop denoise-dct sigma=4 median-blur abyss-policy=none radius=0    "\




#define g15 \
" id=containall src aux=[ ref=containall color-overlay value=#00dfff cubism tile-size=10 seed=383 median-blur abyss-policy=none radius=11 id=1 gimp:layer-mode layer-mode=hardlight opacity=0.25 aux=[  ref=1 emboss depth=20 denoise-dct sigma=35 ] lb:threshold-alpha id=2 over aux=[ ref=2 lb:glassovertext azimuth=33 depth=19   ] lb:edgesmooth value=2 id=3 gimp:layer-mode layer-mode=replace opacity=0.09 aux=[ ref=3 color-to-alpha color=#0ee2fd ] ] crop denoise-dct sigma=4 median-blur abyss-policy=none radius=0-dct sigma=4 median-blur abyss-policy=none radius=0    "\


#define g16 \
" id=containall src aux=[ ref=containall color-overlay value=#00dfff cubism tile-size=12 seed=683 median-blur abyss-policy=none radius=11 id=1 gimp:layer-mode layer-mode=hardlight opacity=0.25 aux=[  ref=1 emboss depth=20 denoise-dct sigma=35 ] lb:threshold-alpha id=2 over aux=[ ref=2 lb:glassovertext azimuth=33 depth=19   ] lb:edgesmooth value=2 id=3 gimp:layer-mode layer-mode=replace opacity=0.09 aux=[ ref=3 color-to-alpha color=#0ee2fd ] ] crop denoise-dct sigma=4 median-blur abyss-policy=none radius=0-dct sigma=4 median-blur abyss-policy=none radius=0  "\



#define g17 \
"  id=containall src aux=[ ref=containall color-overlay value=#00dfff cubism tile-size=7 seed=353 median-blur abyss-policy=none radius=5 id=1 gimp:layer-mode layer-mode=hardlight opacity=0.25 aux=[  ref=1 emboss depth=20 denoise-dct sigma=35 ] lb:threshold-alpha id=2 over aux=[ ref=2 lb:glassovertext azimuth=33 depth=19   ] lb:edgesmooth value=2 id=3 gimp:layer-mode layer-mode=replace opacity=0.09 aux=[ ref=3 color-to-alpha color=#0ee2fd ] ] crop denoise-dct sigma=4 median-blur abyss-policy=none radius=0   "\



#define g18 \
"  color-overlay value=#ffffff cubism tile-size=8 seed=33 gaussian-blur abyss-policy=none clip-extent=false std-dev-x=3.5 std-dev-y-=3.5 dropshadow x=0 y=0 opacity=0.6  "\

#define g19 \
" color-overlay value=white gaussian-blur std-dev-x=12 std-dev-y=12 id=1 hard-light  aux=[ ref=1 emboss depth=30 elevation=20 ] cubism tile-size=5 opacity value=2.6 lb:threshold-alpha median-blur radius=0 cubism tile-size=5 id=2 over aux=[ ref=2] shift shift=2 shift shift=2 direction=vertical gimp:threshold-alpha id=3 multiply aux=[ ref=3 noise-rgb red=0 green=0 blue=0 opacity value=3  ] id=replace gimp:layer-mode layer-mode=replace opacity=0.80 aux=[ ref=replace lb:edgesmooth gaus=2 value=1 alpha-percentile2=90 ] gaussian-blur std-dev-x=0.5 std-dev-y=0.50 median-blur radius=0 id=6 gimp:layer-mode layer-mode=difference blend-space=rgb-perceptual opacity=0.30 composite-mode=auto aux=[ ref=6 image-gradient output-mode=magnitude  ] ripple amplitude=1.19 period=19 phi=-02 angle=0 sampler-type=cubic wave-type=sine abyss-policy=clamp tileable=yes id=7 over aux=[ ref=7 softglow opacity value=0.2  ] id=8 gimp:layer-mode layer-mode=behind opacity=0.14 aux=[ ref=8 lb:skeleton xstretch=0.68 ystretch=0.6 internalcubism=1.6 seed=1992011 color=#ffffff ] levels out-low=0.011 "\

#define g20 \
" color-overlay value=white gaussian-blur std-dev-x=12 std-dev-y=12 id=1 screen srgb=true  aux=[ ref=1 emboss depth=30 elevation=20 ] cubism tile-size=5 opacity value=2.6 lb:threshold-alpha median-blur radius=0 cubism tile-size=5 id=2 over aux=[ ref=2] shift shift=2 shift shift=2 direction=vertical gimp:threshold-alpha id=3 multiply aux=[ ref=3 noise-rgb red=0 green=0 blue=0 opacity value=3  ] id=replace gimp:layer-mode layer-mode=replace opacity=0.80 aux=[ ref=replace lb:edgesmooth gaus=2 value=1 alpha-percentile2=90 ] gaussian-blur std-dev-x=0.5 std-dev-y=0.50 median-blur radius=0 id=6 gimp:layer-mode layer-mode=difference blend-space=rgb-perceptual opacity=0.30 composite-mode=auto aux=[ ref=6 image-gradient output-mode=magnitude  ] ripple amplitude=1.19 period=19 phi=-02 angle=0 sampler-type=cubic wave-type=sine abyss-policy=clamp tileable=yes id=7 over aux=[ ref=7 softglow opacity value=0.2  ] id=8 gimp:layer-mode layer-mode=behind opacity=0.14 aux=[ ref=8 lb:skeleton xstretch=0.68 ystretch=0.6 internalcubism=1.6 seed=1992011 color=#ffffff ] levels out-low=0.011 "\

#define g21 \
" color-overlay value=white gaussian-blur std-dev-x=12 std-dev-y=12 id=1 gimp:layer-mode layer-mode=grain-merge aux=[ ref=1 emboss depth=30 elevation=20 ] cubism tile-size=5 opacity value=2.6 lb:threshold-alpha median-blur radius=0 cubism tile-size=5 id=2 over aux=[ ref=2] shift shift=2 shift shift=2 direction=vertical gimp:threshold-alpha id=3 multiply aux=[ ref=3 noise-rgb red=0 green=0 blue=0 opacity value=3  ] id=replace gimp:layer-mode layer-mode=replace opacity=0.80 aux=[ ref=replace lb:edgesmooth gaus=2 value=1 alpha-percentile2=90 ] gaussian-blur std-dev-x=0.5 std-dev-y=0.50 median-blur radius=0 id=6 gimp:layer-mode layer-mode=difference blend-space=rgb-perceptual opacity=0.30 composite-mode=auto aux=[ ref=6 image-gradient output-mode=magnitude  ] ripple amplitude=1.19 period=19 phi=-02 angle=0 sampler-type=cubic wave-type=sine abyss-policy=clamp tileable=yes id=7 over aux=[ ref=7 softglow opacity value=0.2  ] id=8 gimp:layer-mode layer-mode=behind opacity=0.14 aux=[ ref=8 lb:skeleton xstretch=0.68 ystretch=0.6 internalcubism=1.6 seed=1992011 color=#ffffff ] levels out-low=0.011    "\

#define g22 \
" color-overlay value=#c87d00 cubism tile-size=3 gaussian-blur std-dev-x=4 std-dev-y=4 cubism tile-size=7 noise-spread amount-x=24 amount-y=24 gaussian-blur lb:custom-bevel blendmode=Plus saturation scale=0.9 id=2 gimp:layer-mode layer-mode=grain-merge opacity=0.33 aux=[ ref=2 lb:innerglow value2=#ffff00 radius=11 grow-radius=5 ] id=1 gimp:layer-mode layer-mode=grain-merge opacity=0.53 aux=[ ref=1 lb:innerglow value2=#ff8c00 radius=11 grow-radius=5 ] unsharp-mask scale=2.6 lb:threshold-alpha levels in-low=0.1 in-high=0.7 unsharp-mask scale=0.3 id=3 gimp:layer-mode layer-mode=grain-merge aux=[ ref=3 color-overlay value=#be7f29 opacity value=0.3 ] id=4 overlay srgb=true aux=[ ref=4 emboss depth=2 opacity value=0.2 ] id=5 gimp:layer-mode layer-mode=subtract opacity=0.1 aux=[ ref=5 edge algorithm=sobel amount=1] unsharp-mask scale=0.2 lb:threshold-alpha alphadegree=9.5 lb:threshold-alpha alphadegree=9.5 lb:edgesmooth id=6 gimp:layer-mode layer-mode=multiply blend-space=rgb-perceptual opacity=0.50 aux=[ ref=6 ]  "\




#define g23 \
" nop   "\


#define g24 \
" nop  "\


#define g25 \
" nop    "\

#define g26 \
" nop "\

property_enum (crazybevel, _("Select a crazy text effect:"),
    nichetextrandom, niche_textrandom,
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


enum_start (niche_textrandom)
  enum_value (crazy1,      "crazy1",
              N_("Wax Text"))
  enum_value (crazy2,      "crazy2",
              N_("Ice Text"))
  enum_value (crazy3,      "crazy3",
              N_("Bathroom humor text"))
  enum_value (crazy4,      "crazy4",
              N_("Melted Plastic"))
  enum_value (crazy5,      "crazy5",
              N_("Melted Plastic 2"))
  enum_value (crazy6,      "crazy6",
              N_("Melted Plastic 3"))
  enum_value (crazy7,      "crazy7",
              N_("Melted Plastic 4 (small)"))
  enum_value (crazy8,      "crazy8",
              N_("Little Grains (to blend)"))
  enum_value (crazy9,      "crazy9",
              N_("Little Grains 2 (to blend)"))
  enum_value (crazy10,      "crazy10",
              N_("Watermark Text"))
  enum_value (crazy11,      "crazy11",
              N_("Nov 2021 3D text graph"))
  enum_value (crazy12,      "crazy12",
              N_("Nov 2021 3D text graph 2"))
  enum_value (crazy13,      "crazy13",
              N_("Toothpaste 1"))
  enum_value (crazy14,      "crazy14",
              N_("Toothpaste 2"))
  enum_value (crazy15,      "crazy15",
              N_("Toothpaste 3"))
  enum_value (crazy16,      "crazy16",
              N_("Toothpaste 4"))
  enum_value (crazy17,      "crazy17",
              N_("Toothpaste 5"))
  enum_value (crazy18,      "crazy18",
              N_("Cloud Text"))
  enum_value (crazy19,      "crazy19",
              N_("Fuzz Text (Hard Light)"))
  enum_value (crazy20,      "crazy20",
              N_("Fuzz Text (Screen)"))
  enum_value (crazy21,      "crazy21",
              N_("Fuzz Text (Grain Merge)"))
  enum_value (crazy22,      "crazy22",
              N_("Lava type (jan 2024)"))
  enum_value (crazy23,      "crazy23",
              N_("NO CONTENT YET"))
  enum_value (crazy24,      "crazy24",
              N_("NO CONTENT YET"))
  enum_value (crazy25,      "crazy24",
              N_("NO CONTENT YET"))
  enum_value (crazy26,      "crazy25",
              N_("NO CONTENT YET"))
enum_end (nichetextrandom)

#else

#define GEGL_OP_META
#define GEGL_OP_NAME     tscunsorted
#define GEGL_OP_C_SOURCE tscunsorted.c

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
    "name",        "lb:textcollectionunsorted",
    "title",       _("Text Style Collection (Unsorted)"),
    "reference-hash", "t2pysolsolitare349s",
    "description", _("Collection of Text Style algorithms that do not fit with any other plugin of mine or have not yet been properly converted into a full editable filter. All these filters have very limited editability and nothing unique. One day some of these algorithms may be stand alone filters with complete editable options.  "),
    "gimp:menu-path", "<Image>/Filters/Text Styling",
    "gimp:menu-label", _("Misc Text Styling Collection (Unsorted Misc)"),
    NULL);
}

#endif
