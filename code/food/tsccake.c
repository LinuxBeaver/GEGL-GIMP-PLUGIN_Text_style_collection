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
 * 2023 Beaver, Exotic Text Collection

This Gimp plugin can be tested without installing by pasting syntax from g1, g2, g3, g4, ect... into Gimp's GEGL graph.
--

THERE IS NO NEED TO PROVIDE SYNTAX WHEN ALL OF IT IS BELOW in each g definition. Paste each g individually into GEGL graph, not all of them at once.


Check which numbers correspond to what g graph
 */

#include "config.h"
#include <glib/gi18n-lib.h>


#ifdef GEGL_PROPERTIES


#define g1 \
" color-overlay value=white id=x cubism tile-size=4 seed=442 dst aux=[ ref=x median-blur radius=2  alpha-percentile=0 id=x2  ] color-overlay value=#ffffff cubism tile-size=4 seed=442 gaussian-blur std-dev-x=5 std-dev-y=5 id=1 gaussian-blur std-dev-x=6 std-dev-y=6 emboss  xor aux=[ ref=1     ] opacity value=2 emboss depth=20 over aux=[ ref=x2  lb:innerglow value2=black radius=5  opacity value=0.65 ] over aux=[ ref=x2  color-overlay value=#747474 opacity value=0.3 ] mean-curvature-blur  opacity value=2 softglow brightness=90 sharpness=90 glow-radius=50 softglow brightness=90 sharpness=90 glow-radius=40 median-blur radius=0 hue-chroma lightness=2 dst-over aux=[ ref=x median-blur radius=40 alpha-percentile=100 color-overlay value=#ee83ff  cubism tile-size=12 gaussian-blur std-dev-x=2 std-dev-y=2  lb:custom-bevel blendmode=Plus ] saturation scale=1.25 median-blur radius=0 id=hslx gimp:layer-mode layer-mode=hsl-color composite-mode=auto aux=[ ref=hslx  id=melaniescake median-blur radius=0 over aux=[ ref=melaniescake lb:starfield saturation-distance=0.045999999999999999  value-distance=0.050999999999999997  seed=0  out-high=3.972  gamma=6.8529999999999998  std-dev=0.52500000000000002  saturation=1  color-to-alpha color=black opacity value=2.2 median-blur radius= percentile=0 opacity value=2 ] gaussian-blur  std-dev-x=1.5 std-dev-y=1.5 median-blur radius=0 ] id=bottomcake  dst-over aux=[ ref=bottomcake id=bread dst-over aux=[ ref=bread color-overlay value=#ffc383   median-blur radius=25 alpha-percentile=100 id=texture gimp:layer-mode layer-mode=softlight opacity=0.84 composite-mode=auto aux=[ ref=texture noise-rgb noise-rgb noise-rgb noise-reduction iterations=1 ] id=recolorit gimp:layer-mode layer-mode=hsl-color aux=[ ref=recolorit color-overlay value=#ffd09f  ] ] median-blur radius=0  lb:extrusion behindextrusion=yes  center-x=0.083000000000000004  center-y=-2.6709999999999998  factor=0.014  depth=6 exposure=-0.97099999999999997  median-blur radius=0 id=lnburn gimp:layer-mode layer-mode=linear-burn composite-space=rgb-perceptual  opacity=0.011 aux=[ ref=lnburn ]  id=insidebread gimp:layer-mode layer-mode=normal opacity=0.08 aux=[ ref=insidebread noise-rgb noise-reduction iterations=1 ] ] median-blur radius=0 id=bevit gimp:layer-mode layer-mode=softlight opacity=0.34 composite-mode=auto aux=[ ref=bevit lb:bevel hue-chroma lightness=9 ] bloom strength=9 dropshadow  x=4.79 y=8.79 radius=8.14 grow-radius=0 color=#000000 opacity=1.04    "\


#define g2 \
" color-overlay value=white median-blur radius=8  alpha-percentile=20 gaussian-blur std-dev-x=2 std-dev-y=2 lb:threshold-alpha median-blur radius=8  alpha-percentile=20 gaussian-blur std-dev-x=2 std-dev-y=2 lb:threshold-alpha cubism tile-size=2 seed=442 id=x dst aux=[ ref=x median-blur radius=2  alpha-percentile=0 id=x2  ] color-overlay value=#ffffff cubism tile-size=10 seed=442 gaussian-blur std-dev-x=5 std-dev-y=5 id=1 gaussian-blur std-dev-x=6 std-dev-y=6 emboss  lb:threshold-alpha lb:threshold-alpha id=chocolate gimp:layer-mode layer-mode=grain-merge opacity=0.70 aux=[ ref=chocolate color-overlay value=#f579ff ] gimp:layer-mode layer-mode=split composite-space=auto aux=[ ref=1     ] opacity value=2 emboss depth=20 over aux=[ ref=x2  lb:innerglow value2=black radius=5  opacity value=0.65 ] over aux=[ ref=x2  color-overlay value=#f579ff opacity value=0.3 ] mean-curvature-blur  opacity value=2 softglow brightness=90 sharpness=90 glow-radius=50 softglow brightness=90 sharpness=90 glow-radius=40 median-blur radius=0 hue-chroma lightness=2 id=colorfrosting gimp:layer-mode layer-mode=hsl-color opacity=0.44 aux=[ ref=colorfrosting   median-blur radius=0 color-overlay  value=#ff0500 ] mean-curvature-blur iterations=3 lb:threshold-alpha dst-over aux=[ ref=x median-blur radius=40 alpha-percentile=100 color-overlay value=#934c00  cubism tile-size=12 gaussian-blur std-dev-x=2 std-dev-y=2  lb:custom-bevel blendmode=Multiply ] saturation scale=1.25 median-blur radius=0 id=hslx gimp:layer-mode layer-mode=hsl-color composite-mode=auto aux=[ ref=hslx  id=melaniescake median-blur radius=0 gaussian-blur  std-dev-x=1.5 std-dev-y=1.5 median-blur radius=0 ] id=bottomcake  dst-over aux=[ ref=bottomcake id=bread dst-over aux=[ ref=bread color-overlay value=#ffc383   median-blur radius=25 alpha-percentile=100 id=texture gimp:layer-mode layer-mode=softlight opacity=0.84 composite-mode=auto aux=[ ref=texture noise-rgb noise-rgb noise-rgb noise-reduction iterations=1 ] id=recolorit gimp:layer-mode layer-mode=hsl-color aux=[ ref=recolorit color-overlay value=#ffd09f  ] ] median-blur radius=0  lb:extrusion behindextrusion=yes  center-x=0.083000000000000004  center-y=-2.6709999999999998  factor=0.014  depth=6 exposure=-0.97099999999999997  median-blur radius=0 id=lnburn gimp:layer-mode layer-mode=linear-burn composite-space=rgb-perceptual  opacity=0.011 aux=[ ref=lnburn ]  id=insidebread gimp:layer-mode layer-mode=normal opacity=0.08 aux=[ ref=insidebread noise-rgb noise-reduction iterations=1 ] ] median-blur radius=0 id=bevit gimp:layer-mode layer-mode=softlight opacity=0.34 composite-mode=auto aux=[ ref=bevit lb:bevel hue-chroma lightness=9 ] bloom strength=9 dropshadow  x=4.79 y=8.79 radius=8.14 grow-radius=0 color=#000000 opacity=1.04   "\


#define g3 \
" id=cookiecontainer src aux=[ ref=cookiecontainer id=x cubism tile-size=8 seed=442 dst aux=[ ref=x median-blur radius=2  alpha-percentile=0 id=x2  ] color-overlay value=#ffffff cubism tile-size=4 seed=442 gaussian-blur std-dev-x=5 std-dev-y=5 id=1 gaussian-blur std-dev-x=6 std-dev-y=6 emboss  xor aux=[ ref=1     ] opacity value=2 emboss depth=20 over aux=[ ref=x2  lb:innerglow value2=black radius=5  opacity value=0.65 ] over aux=[ ref=x2  color-overlay value=#747474 opacity value=0.3 ] mean-curvature-blur  opacity value=2 softglow brightness=90 sharpness=90 glow-radius=50 softglow brightness=90 sharpness=90 glow-radius=40 median-blur radius=0 id=topcreamcolor gimp:layer-mode layer-mode=multiply composite-mode=clip-to-backdrop aux=[ ref=topcreamcolor color value=#f0a479  ] id=chips src-atop aux=[ ref=chips lb:bokeh neighborhood=circle color=black amount=0.095000000000000001 seed=4214089293 size=5 opacity=0.90100000000000002 blur=2 ] id=chips src-atop aux=[ ref=chips lb:bokeh neighborhood=circle color=black amount=0.3 seed=76 size=3 opacity=0.90100000000000002 blur=2 ] id=chips src-atop aux=[ ref=chips lb:bokeh neighborhood=circle color=black amount=0.095000000000000001 seed=1736 size=3 opacity=0.90100000000000002 blur=2 ] id=chips src-atop aux=[ ref=chips id=chips src-atop aux=[ ref=chips lb:bokeh neighborhood=circle color=black amount=0.4 seed=1736 size=3 opacity=0.90100000000000002 blur=2 ] id=chips src-atop aux=[ ref=chips lb:bokeh neighborhood=circle color=black amount=34 seed=5335 size=3 opacity=0.90100000000000002 blur=2 ] id=chips src-atop aux=[ ref=chips lb:bokeh neighborhood=circle color=black amount=0.4 seed=52 size=3 opacity=0.90100000000000002 blur=2 ] ] lb:threshold-alpha dropshadow x=0 y=0 radius=4 grow-radius=0 opacity=1.84 dst-over aux=[ ref=x median-blur radius=40 alpha-percentile=100 color-overlay value=#96664a cubism tile-size=12 gaussian-blur std-dev-x=2 std-dev-y=2  lb:custom-bevel blendmode=Multiply ] saturation scale=1.25 median-blur radius=0 id=hslx gimp:layer-mode layer-mode=hsl-color composite-mode=auto aux=[ ref=hslx  id=melaniescake median-blur radius=0 over aux=[ ref=melaniescake median-blur radius= percentile=0 opacity value=2 ] gaussian-blur  std-dev-x=1.5 std-dev-y=1.5 median-blur radius=0 ] id=bottomcake  dst-over aux=[ ref=bottomcake id=bread dst-over aux=[ ref=bread color-overlay value=#ffc383   median-blur radius=25 alpha-percentile=100 id=texture gimp:layer-mode layer-mode=softlight opacity=0.84 composite-mode=auto aux=[ ref=texture noise-reduction iterations=1 ] id=recolorit gimp:layer-mode layer-mode=hsv-hue opacity=0.40 aux=[ ref=recolorit color-overlay value=#fcd0ff ] ] median-blur radius=0  lb:extrusion behindextrusion=yes  center-x=0.083000000000000004  center-y=-2.6709999999999998  factor=0.014  depth=6 exposure=-0.97099999999999997  median-blur radius=0 id=lnburn gimp:layer-mode layer-mode=linear-burn composite-space=rgb-perceptual  opacity=0.012 aux=[ ref=lnburn ]  ] median-blur radius=0 id=bevit gimp:layer-mode layer-mode=softlight opacity=0.14 composite-mode=auto aux=[ ref=bevit lb:bevel hue-chroma lightness=9 ] bloom strength=9 dropshadow  x=4.79 y=.479 radius=8.14 grow-radius=0 color=#000000 opacity=1.04    "\

#define g4 \
" id=cookiecontainer src aux=[ ref=cookiecontainer id=x cubism tile-size=8 seed=442 dst aux=[ ref=x median-blur radius=2  alpha-percentile=0 id=x2  ] color-overlay value=#ffffff cubism tile-size=4 seed=442 gaussian-blur std-dev-x=5 std-dev-y=5 id=1 gaussian-blur std-dev-x=6 std-dev-y=6 emboss  xor aux=[ ref=1     ] opacity value=2 emboss depth=20 over aux=[ ref=x2  lb:innerglow value2=black radius=5  opacity value=0.65 ] over aux=[ ref=x2  color-overlay value=#747474 opacity value=0.3 ] mean-curvature-blur  opacity value=2 softglow brightness=90 sharpness=90 glow-radius=50 softglow brightness=90 sharpness=90 glow-radius=40 median-blur radius=0 id=topcreamcolor gimp:layer-mode layer-mode=multiply composite-mode=clip-to-backdrop aux=[ ref=topcreamcolor color value=#f0a479  ] id=chips src-atop aux=[ ref=chips lb:bokeh neighborhood=circle color=black amount=0.095000000000000001 seed=4214089293 size=5 opacity=0.90100000000000002 blur=2 ] id=chips src-atop aux=[ ref=chips lb:bokeh neighborhood=circle color=black amount=0.3 seed=76 size=3 opacity=0.90100000000000002 blur=2 ] id=chips src-atop aux=[ ref=chips lb:bokeh neighborhood=circle color=black amount=0.095000000000000001 seed=1736 size=3 opacity=0.90100000000000002 blur=2 ] id=chips src-atop aux=[ ref=chips id=chips src-atop aux=[ ref=chips lb:bokeh neighborhood=circle color=black amount=0.4 seed=1736 size=3 opacity=0.90100000000000002 blur=2 ] id=chips src-atop aux=[ ref=chips lb:bokeh neighborhood=circle color=black amount=34 seed=5335 size=3 opacity=0.90100000000000002 blur=2 ] id=chips src-atop aux=[ ref=chips lb:bokeh neighborhood=circle color=black amount=0.4 seed=52 size=3 opacity=0.90100000000000002 blur=2 ] ] lb:threshold-alpha  "\

#define g5 \
"  cubism tile-size=4.5 gaussian-blur std-dev-x=1 std-dev-y=1 color-overlay value=#ffbb00 hue-chroma lightness=7 median-blur radius=13 id=-1 id=0 multiply aux=[ ref=0   lb:bevel bevel2=7 bevel1=90 ] id=1 over aux=[ ref=1 lb:glassovertext elevation=23 ] ripple amplitude=12 abyss-policy=clamp angle=6 dst-over aux=[ ref=-1 ripple amplitude=12 abyss-policy=clamp angle=6 median-blur neighborhood=diamond radius=45 alpha-percentile=100 cubism tile-size=14 median-blur radius=20 median-blur radius=20 color-overlay value=#ff0000 ] id=2 gimp:layer-mode layer-mode=normal aux=[ ref=2 lb:innerglow value2=#000000 fixoutline=66 radius=3 opacity=0.9 ] id=3 gimp:layer-mode layer-mode=normal aux=[ ref=3  lb:glassovertext azimuth=23 ]  "\




#define g6 \
"  cubism tile-size=9 color-overlay value=white lb:threshold-alpha id=contain over aux=[ ref=contain median-blur radius=0 cubism tile-size=10 distance-transform median-blur radius=0 alpha-percentile=10 neighborhood=diamond median-blur radius=0 ] id=legacy gimp:layer-mode layer-mode=hardlight-legacy aux=[ ref=legacy shadows-highlights shadows=100 highlights=-95 whitepoint=-10 radius=33.560000000000002 compress=31.800000000000001 shadows-ccorrect=54.390000000000001 highlights-ccorrect=20.5 ] edge id=extract dst-in aux=[ ref=extract  component-extract component=cmyk-y  gaussian-blur std-dev-x=2 std-dev-y=2 color-to-alpha ] lb:threshold-alpha opacity value=1.4 id=greenleaf median-blur radius=0 gimp:layer-mode layer-mode=darken-only composite-mode=clip-to-backdrop  aux=[ ref=greenleaf  color value=#26ff00 ] levels out-high=1.6 saturation scale=1.2 id=greenit gimp:layer-mode layer-mode=hsl-color composite-mode=clip-to-backdrop  aux=[ color value=green ] hue-chroma lightness=4   "\


#define g7 \
"  id=x cubism tile-size=4 seed=442 dst aux=[ ref=x median-blur radius=2  alpha-percentile=0 cubism tile-size=3 id=x2  ] color-overlay value=#ecc7ff cubism tile-size=4 seed=442 gaussian-blur std-dev-x=5 std-dev-y=5 id=1 gaussian-blur std-dev-x=6 std-dev-y=6 id=frostingcolor gimp:layer-mode layer-mode=overlay opacity=0.60 aux=[ ref=frostingcolor emboss ] xor aux=[ ref=1     ] opacity value=2 id=frostingcolor2 gimp:layer-mode layer-mode=overlay opacity=0.60 aux=[ ref=frostingcolor2 emboss  ] over aux=[ ref=x2  lb:innerglow value2=black radius=5  opacity value=0.65 ] over aux=[ ref=x2  color-overlay value=#747474 opacity value=0.3 ] mean-curvature-blur  opacity value=2 softglow brightness=90 sharpness=90 glow-radius=50 softglow brightness=90 sharpness=90 glow-radius=40 median-blur radius=0 dst-over aux=[ ref=x median-blur radius=40 alpha-percentile=100 color-overlay value=#ee83ff  cubism tile-size=12 gaussian-blur std-dev-x=2 std-dev-y=2  lb:custom-bevel blendmode=Plus ] saturation scale=1.25 median-blur radius=0 id=hslx gimp:layer-mode layer-mode=hsl-color composite-mode=auto aux=[ ref=hslx  id=melaniescake median-blur radius=0 over aux=[ ref=melaniescake lb:starfield saturation-distance=0.045999999999999999  value-distance=0.050999999999999997  seed=0  out-high=3.972  gamma=8.8529999999999998  std-dev=0.52500000000000002  saturation=1  color-to-alpha color=black opacity value=2.2 median-blur radius= percentile=0 opacity value=2 ] gaussian-blur  std-dev-x=1.5 std-dev-y=1.5 median-blur radius=0 ] id=bottomcake  dst-over aux=[ ref=bottomcake id=bread dst-over aux=[ ref=bread color-overlay value=#ffc383   median-blur radius=25 alpha-percentile=100 id=texture gimp:layer-mode layer-mode=softlight opacity=0.84 composite-mode=auto aux=[ ref=texture noise-rgb noise-rgb noise-rgb noise-reduction iterations=1 ] id=recolorit gimp:layer-mode layer-mode=hsl-color aux=[ ref=recolorit color-overlay value=#ab84b5 ] ] median-blur radius=0  lb:extrusion behindextrusion=yes  center-x=0.493000000000000004  center-y=-1.9709999999999998  factor=0.016  depth=2 exposure=-0.97099999999999997  median-blur radius=0 id=lnburn gimp:layer-mode layer-mode=linear-burn composite-space=rgb-perceptual  opacity=0.011 aux=[ ref=lnburn ]  ] median-blur radius=0 id=bevit gimp:layer-mode layer-mode=softlight opacity=0.34 composite-mode=auto aux=[ ref=bevit lb:bevel hue-chroma lightness=14 ] bloom strength=9 dropshadow  x=0 y=0 radius=8.14 grow-radius=0 color=#000000 opacity=1.04  "\

#define g8 \
"  nop "\

#define g9 \
"  nop  "\

#define g10 \
"  nop "\


#define g11 \
"  nop  "\

#define g12 \
" nop   "\

#define g13 \
" nop  "\

#define g14 \
"   nop   "\

#define g14 \
"   nop  "\

#define g15 \
"   nop "\

#define g16 \
"   nop  "\

#define g17 \
"  nop "\

#define g18 \
"  nop "\

#define g19 \
" nop "\

#define g20 \
"  nop "\

#define g21 \
"  nop  "\

#define g22 \
"  nop  "\

#define g23 \
"  nop    "\

#define g24 \
"  nop   "\

#define g25 \
"  nop   "\

#define g26 \
" nop  "\




property_enum (crazybevel, _("Select a crazy text effect:"),
    nichebeveldesert, niche_beveldesert,
    crazy5)
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


enum_start (niche_beveldesert)
  enum_value (crazy1,      "crazy1",
              N_("Pink Frosting Cake Text (WARNING - EXTREMELY SLOW)"))
  enum_value (crazy2,      "crazy2",
              N_("Chocolate Cake Text (WARNING - EXTREMELY SLOW)"))
  enum_value (crazy3,      "crazy3",
              N_("Chocolate Chip Cake Text (WARNING - EXTREMELY SLOW)"))
  enum_value (crazy4,      "craz4",
              N_("Chocolate Chip Cookie Text"))
  enum_value (crazy5,      "crazy5",
              N_("Eggy Tomato"))
  enum_value (crazy6,      "crazy6",
              N_("Leaf Text"))
  enum_value (crazy7,      "crazy7",
              N_("Pink bread and frosting Cake text (WARNING -EXTREMELY SLOW"))
  enum_value (crazy8,      "crazy8",
              N_("NO CONTENT YET"))
  enum_value (crazy9,      "crazy9",
              N_("NO CONTENT YET"))
  enum_value (crazy10,      "crazy10",
              N_("NO CONTENT YET"))
  enum_value (crazy11,      "crazy11",
              N_("NO CONTENT YET"))
  enum_value (crazy12,      "crazy12",
              N_("NO CONTENT YET"))
  enum_value (crazy13,      "crazy13",
              N_("NO CONTENT YET"))
  enum_value (crazy14,      "crazy14",
              N_("NO CONTENT YET"))
  enum_value (crazy15,      "crazy15",
              N_("NO CONTENT YET"))
  enum_value (crazy16,      "crazy16",
              N_("NO CONTENT YET"))
  enum_value (crazy17,      "crazy17",
              N_("NO CONTENT YET"))
  enum_value (crazy18,      "crazy18",
              N_("NO CONTENT YET"))
  enum_value (crazy19,      "crazy19",
              N_("NO CONTENT YET"))
  enum_value (crazy20,      "crazy20",
              N_("NO CONTENT YET"))
  enum_value (crazy21,      "crazy21",
              N_("NO CONTENT YET"))
  enum_value (crazy22,      "crazy22",
              N_("NO CONTENT YET"))
  enum_value (crazy23,      "crazy23",
              N_("NO CONTENT YET"))
  enum_value (crazy24,      "crazy24",
              N_("NO CONTENT YET"))
  enum_value (crazy25,      "crazy24",
              N_("NO CONTENT YET"))
  enum_value (crazy26,      "crazy25",
              N_("NO CONTENT YET"))
enum_end (nichebeveldesert)

#else

#define GEGL_OP_META
#define GEGL_OP_NAME     tsccake
#define GEGL_OP_C_SOURCE tsccake.c

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
    "name",        "lb:textcollectionfood",
    "title",       _("Text Styling Collection (Food Type)"),
    "reference-hash", "a3434agcatscratch3mrblik3",
    "description", _("Collection of Text Style algorithms that do not fit with any other plugin of mine or have not yet been properly converted into a full editable filter. All these filters have very limited editability and nothing unique. One day some of these algorithms may be stand alone filters with complete editable options."),
    "gimp:menu-path", "<Image>/Filters/Text Styling",
    "gimp:menu-label", _("Misc Text Styling Collection (Food type)"),
    NULL);
}

#endif
