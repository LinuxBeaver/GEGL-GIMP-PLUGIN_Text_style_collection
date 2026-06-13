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
 * 2026, beaver, based metal 

syntax to this plugin without installing, requires lb:bevel which it ships with

color-overlay value=#acacac
 id=1 gimp:layer-mode layer-mode=grain-merge composite-mode=auto   aux=[ ref=1  lb:bevel type=sharpbeveltwo bevel2=2 bevel1=43  azimuth=24  flatsurface=2.8  ]

mean-curvature-blur iterations=4 median-blur radius=0  abyss-policy=none
 alien-map cpn-1-frequency=2 cpn-2-frequency=5.9 cpn-3-frequency=3 hue-chroma lightness=-5 noise-reduction iterations=2 saturation scale=0 gimp:layer-mode layer-mode=hsl-color opacity=0.8 composite-mode=auto  aux=[ color value=#ffdc00  ] id=darken gimp:layer-mode layer-mode=addition opacity=0.3 aux=[ ref=darken ]  levels out-low=0.024 median-blur  abyss-policy=none radius=0 
saturation scale=0


gimp:layer-mode layer-mode=hardlight opacity=0.7 composite-mode=auto aux=[ ref=2 noise-solid tileable=true  detail=9 y-size=10 x-size=10 seed=4224  ]
gimp:layer-mode layer-mode=overlay  opacity=0.35 composite-mode=auto aux=[ ref=2 noise-solid tileable=true  detail=7 y-size=10 x-size=10 seed=322  ]
id=3
over aux=[ ref=3 noise-cie-lch chroma-distance=0 hue-distance=0 opacity value=0.11 ]

shadows-highlights whitepoint=8

bloom strength=28

optionally put graph here

]

end of syntax
 */

#include "config.h"
#include <glib/gi18n-lib.h>

#ifdef GEGL_PROPERTIES

/*Properties go here*/

property_boolean (colorpolicy , _("Enable Color priority mode"), FALSE)
  description    (_("Enable a custom color overlay?"))

property_boolean (blur , _("Enable faint blur"), FALSE)
  description    (_("Enable a faint blur for smoothness?"))

property_boolean (darkenandsharpen , _("Enable darken and sharpen mode"), TRUE)
  description    (_("Enable darken and sharpen mode to give interest effects to the metal?"))

property_double (azimuth, _("Rotate Lighting"), 40.0)
    description (_("Light angle (degrees)"))
    value_range (0, 360)
    ui_meta ("unit", "degree")
    ui_meta ("direction", "ccw")
  ui_steps      (0.1, 0.50)


property_double (elevation, _("Elevation"), 73.0)
    description (_("Elevation angle (degrees)"))
    value_range (50, 125)
    ui_meta ("unit", "degree")
  ui_steps      (0.1, 1.50)

property_int (depth, _("Depth"), 7)
    description (_("Emboss depth -Brings out depth and detail of the bevel"))
    value_range (4, 10)

property_double (flatsurface, _("Flat surface"), 2.1)
  description(_("Flat Surface of the sharp chamfer bevel"))
  value_range   (2, 2.5)
  ui_range      (2, 2.5)

property_double (noisepresence, _("Noise opacity"), 0.70)
  description(_("Opacity of the noise"))
  value_range   (0.0, 1.0)
  ui_range      (0.0, 1.0)


property_seed (seed, _("Random seed of noise"), rand)


property_int (smooth, _("Internal smoothing"), 15)
    description (_("Internal smoothing of the metallic texture"))
    value_range (1, 30)


property_double (glow, _("Glow"), 20.0)
    description (_("Should the metal glow?"))
    value_range (0, 50)
    ui_meta ("unit", "degree")
  ui_steps      (0.1, 1.50)


property_double (whitepoint, _("White point"), 4.0)
    description (_("Shadow highlights white point of the metal"))
    value_range (1.0, 10.0)
    ui_meta ("unit", "degree")
  ui_steps      (0.1, 1.50)

property_double (lighting, _("Lightness"), 0.0)
    description (_("Lightness of the metal"))
    value_range (-10.0, 10.0)
    ui_meta ("unit", "degree")
  ui_steps      (0.1, 1.50)


property_color (color, _("Color Overlay"), "#ffffff")
    description (_("Color mode"))
  ui_meta     ("sensitive", " colorpolicy")


#else

#define GEGL_OP_META
#define GEGL_OP_NAME     metaltext
#define GEGL_OP_C_SOURCE metaltext.c

#include "gegl-op.h"

/*starred nodes go inside typedef struct */

typedef struct
{
 GeglNode *input;
 GeglNode *light;
 GeglNode *graphy;
 GeglNode *graphynext;
 GeglNode *nopgraphynext;
 GeglNode *overlay2;
 GeglNode *softlight;
 GeglNode *overlay1;
 GeglNode *normal;
 GeglNode *normalfaint;
 GeglNode *edgefaint;
 GeglNode *noise;
 GeglNode *glow;
 GeglNode *grainmerge;
 GeglNode *input2;
 GeglNode *input3;
 GeglNode *bevel;
 GeglNode *solidnoise1;
 GeglNode *solidnoise2;
 GeglNode *color;
 GeglNode *glitchfix;
 GeglNode *crop;
 GeglNode *smooth;
 GeglNode *shadowshighlights;
 GeglNode *coloroverlay;
 GeglNode *pinlight;
 GeglNode *input4;
 GeglNode *input5;
 GeglNode *imagegradient;
 GeglNode *blur;
 GeglNode *nopblur;
 GeglNode *output;
}State;

static void attach (GeglOperation *operation)
{
  GeglNode *gegl = operation->node;
  GeglProperties *o = GEGL_PROPERTIES (operation);
  GeglColor *gray = gegl_color_new ("#acacac");
  GeglColor *whitetwo = gegl_color_new ("#ffffff");

  State *state = o->user_data = g_malloc0 (sizeof (State));

/*new child node list is here, this is where starred nodes get defined

 state->newchildname = gegl_node_new_child (gegl, "operation", "lb:name", NULL);*/
  state->input    = gegl_node_get_input_proxy (gegl, "input");
  state->output   = gegl_node_get_output_proxy (gegl, "output");



 state->bevel = gegl_node_new_child (gegl, "operation", "lb:bevel", "type", 5, "flatsurface", 2.8, "smoothchamfer", 8, "metric", 0,  NULL);



#define EMBEDDEDGRAPH \
" mean-curvature-blur iterations=4 median-blur radius=0 abyss-policy=none alien-map cpn-1-frequency=2 cpn-2-frequency=5.9 cpn-3-frequency=3 hue-chroma lightness=-5 noise-reduction iterations=2 saturation scale=0 gimp:layer-mode layer-mode=hsl-color opacity=0.8 composite-mode=auto aux=[ color value=#ffdc00 ] id=darken gimp:layer-mode layer-mode=addition opacity=0.3 aux=[ ref=darken ] levels out-low=0.024 median-blur abyss-policy=none radius=0 saturation scale=0 "\

  state->graphy    = gegl_node_new_child (gegl,
				  "operation", "gegl:gegl", "string", EMBEDDEDGRAPH, 
				  NULL);

#define EMBEDDEDGRAPH2 \
"  id=0 gimp:layer-mode layer-mode=hardlight composite-mode=auto aux=[ ref=0 id=1 gimp:layer-mode layer-mode=color-erase aux=[ ref=1 gaussian-blur std-dev-x=1 std-dev-y=1 ] opacity value=1.8 ] "\

  state->graphynext    = gegl_node_new_child (gegl,
				  "operation", "gegl:gegl", "string", EMBEDDEDGRAPH2, 
				  NULL);


  state->grainmerge    = gegl_node_new_child (gegl,
				  "operation", "gimp:layer-mode", "layer-mode", 47, "composite-mode", 0, "blend-space", 2, 
				  NULL);


  state->overlay2    = gegl_node_new_child (gegl,
				  "operation", "gimp:layer-mode", "layer-mode", 23, "composite-mode", 0,  "opacity", 0.70,  "blend-space", 1, 
				  NULL);


  state->normal    = gegl_node_new_child (gegl,
				  "operation", "gimp:layer-mode", "layer-mode", 28,  "composite-mode", 0, "opacity", 0.07,
				  NULL);

  state->normalfaint    = gegl_node_new_child (gegl,
				  "operation", "gimp:layer-mode", "layer-mode", 28,  "composite-mode", 0, "opacity", 0.01,
				  NULL);


  state->overlay1    = gegl_node_new_child (gegl,
				  "operation", "gimp:layer-mode", "layer-mode", 23, "composite-mode", 0, "opacity", 0.20,  "blend-space", 1, 
				  NULL);

  state->pinlight    = gegl_node_new_child (gegl,
				  "operation", "gimp:layer-mode", "layer-mode", 49, "composite-mode", 0, "opacity", 0.35,   "blend-space", 2, 
				  NULL);



  state->softlight    = gegl_node_new_child (gegl,
				  "operation", "gimp:layer-mode", "layer-mode", 45, "composite-mode", 0, 
				  NULL);

  state->coloroverlay    = gegl_node_new_child (gegl,
				  "operation", "gegl:color-overlay", "value", gray, 
				  NULL);

  state->glow    = gegl_node_new_child (gegl,
				  "operation", "gegl:bloom", "strength", 18.0, 
				  NULL);

  state->smooth    = gegl_node_new_child (gegl,
				  "operation", "gegl:mean-curvature-blur", "iterations", 4, 
				  NULL);

  state->edgefaint   = gegl_node_new_child (gegl,
				  "operation", "gegl:image-gradient", 
				  NULL);


  state->crop   = gegl_node_new_child (gegl,
				  "operation", "gegl:crop", 
				  NULL);

  state->glitchfix    = gegl_node_new_child (gegl,
				  "operation", "gegl:median-blur", "radius", 0, "abyss-policy", 0, 
				  NULL);

  state->nopblur    = gegl_node_new_child (gegl,
				  "operation", "gegl:nop", 
				  NULL);

  state->nopgraphynext    = gegl_node_new_child (gegl,
				  "operation", "gegl:nop", 
				  NULL);

  state->input2    = gegl_node_new_child (gegl,
				  "operation", "gegl:nop", 
				  NULL);

  state->input3    = gegl_node_new_child (gegl,
				  "operation", "gegl:nop", 
				  NULL);

  state->input4    = gegl_node_new_child (gegl,
				  "operation", "gegl:nop", 
				  NULL);


  state->input5    = gegl_node_new_child (gegl,
				  "operation", "gegl:nop", 
				  NULL);

  state->light    = gegl_node_new_child (gegl,
				  "operation", "gegl:hue-chroma", 
				  NULL);

  state->imagegradient    = gegl_node_new_child (gegl,
				  "operation", "gegl:image-gradient", 
				  NULL);


  state->blur    = gegl_node_new_child (gegl,
				  "operation", "gegl:gaussian-blur", "std-dev-x", 0.5, "std-dev-y", 0.5, 
				  NULL);


state->solidnoise1 = gegl_node_new_child (gegl, "operation", "gegl:noise-solid", "x-size", 10.0, "y-size", 10.0,  "detail", 9, "tileable", TRUE,   NULL);


state->solidnoise2 = gegl_node_new_child (gegl, "operation", "gegl:noise-solid", "x-size", 10.0, "y-size", 10.0,  "detail", 7, "tileable", TRUE,  NULL);


  state->shadowshighlights    = gegl_node_new_child (gegl,
				  "operation", "gegl:shadows-highlights", "whitepoint", 4.0, 
				  NULL);

  state->noise    = gegl_node_new_child (gegl,
				  "operation", "gegl:noise-cie-lch", "chroma-distance", 0.0,  "hue-distance", 0.0, 
				  NULL);

  state->color    = gegl_node_new_child (gegl,
				  "operation", "gegl:color", "value", whitetwo,
				  NULL);

 gegl_operation_meta_redirect (operation, "seed", state->solidnoise1,  "seed");
 gegl_operation_meta_redirect (operation, "seed", state->solidnoise2,  "seed");
 gegl_operation_meta_redirect (operation, "seed", state->noise,  "seed");
 gegl_operation_meta_redirect (operation, "azimuth", state->bevel,  "azimuth");
 gegl_operation_meta_redirect (operation, "elevation", state->bevel,  "bevel1");
 gegl_operation_meta_redirect (operation, "depth", state->bevel,  "bevel2");
 gegl_operation_meta_redirect (operation, "flatsurface", state->bevel,  "flatsurface");
 gegl_operation_meta_redirect (operation, "smooth", state->bevel,  "smoothchamfer");
 gegl_operation_meta_redirect (operation, "color", state->color,  "value");
 gegl_operation_meta_redirect (operation, "glow", state->glow,  "strength");
 gegl_operation_meta_redirect (operation, "noisepresence", state->overlay2,  "opacity");
 gegl_operation_meta_redirect (operation, "whitepoint", state->shadowshighlights,  "whitepoint");
 gegl_operation_meta_redirect (operation, "lighting", state->light,  "lightness");

/*meta redirect property to new child orders go here

 gegl_operation_meta_redirect (operation, "propertyname", state->newchildname,  "originalpropertyname");
*/

}

static void
update_graph (GeglOperation *operation)
{
  GeglProperties *o = GEGL_PROPERTIES (operation);
  State *state = o->user_data;
  if (!state) return;

  GeglNode *blur = state->blur; 
  GeglNode *graphynext = state->graphynext; 


if (o->blur) blur = state->blur;
if (!o->blur) blur = state->nopblur;

if (o->darkenandsharpen) graphynext = state->graphynext;
if (!o->darkenandsharpen) graphynext = state->nopgraphynext;

 if (o->colorpolicy)
  {
  gegl_node_link_many (state->input,  state->coloroverlay, state->input2, state->grainmerge, state->smooth, state->graphy, state->overlay2, state->overlay1, state->input3, state->normal, state->shadowshighlights, state->glow,  state->crop, state->input4, state->pinlight, graphynext, state->input5, state->normalfaint,  state->glitchfix,  state->softlight, blur, state->light, state->output,  NULL);
  gegl_node_connect (state->overlay2, "aux", state->solidnoise1, "output");
  gegl_node_connect (state->overlay1, "aux", state->solidnoise2, "output");
  gegl_node_connect (state->normal, "aux", state->noise, "output");
  gegl_node_connect (state->grainmerge, "aux", state->bevel, "output");
  gegl_node_link_many (state->input3,  state->noise,     NULL);
  gegl_node_link_many (state->input2,  state->bevel,  NULL);
  gegl_node_connect (state->softlight, "aux", state->color, "output");
  gegl_node_connect (state->pinlight, "aux", state->imagegradient, "output");
  gegl_node_link_many (state->input4,  state->imagegradient,  NULL);
  gegl_node_link_many (state->input5,  state->edgefaint,  NULL);
  gegl_node_connect (state->normalfaint, "aux", state->edgefaint, "output");
  gegl_node_connect (state->crop, "aux", state->input3, "output");
  }


else
  {
  gegl_node_link_many (state->input,  state->coloroverlay, state->input2, state->grainmerge, state->smooth, state->graphy, state->overlay2, state->overlay1, state->input3, state->normal, state->shadowshighlights, state->glow, state->input4,  state->pinlight, graphynext, state->input5, state->normalfaint, blur, state->light, state->output,  NULL);
  gegl_node_connect (state->overlay2, "aux", state->solidnoise1, "output");
  gegl_node_connect (state->overlay1, "aux", state->solidnoise2, "output");
  gegl_node_connect (state->normal, "aux", state->noise, "output");
  gegl_node_connect (state->grainmerge, "aux", state->bevel, "output");
  gegl_node_link_many (state->input3,  state->noise,   NULL);
  gegl_node_link_many (state->input2,  state->bevel,  NULL);
  gegl_node_connect (state->pinlight, "aux", state->imagegradient, "output");
  gegl_node_link_many (state->input4,  state->imagegradient,  NULL);
  gegl_node_link_many (state->input5,  state->edgefaint,  NULL);
  gegl_node_connect (state->normalfaint, "aux", state->edgefaint, "output");

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
    "name",        "lb:metal-text",
    "title",       _("Metal Text"),
    "reference-hash", "metalwannasleeplease",
    "description", _("Make elegant and detailed metal text"),
/*<Image>/Colors <Image>/Filters are top level menus in GIMP*/
    "gimp:menu-path", "<Image>/Filters/Text Styling",
    "gimp:menu-label", _("Metal Text..."),
    NULL);
}

#endif
