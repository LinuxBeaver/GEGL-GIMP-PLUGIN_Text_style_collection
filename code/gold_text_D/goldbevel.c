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
 * 2023 Beaver (GEGL Gold)

Requires plugins lb:innerglow, lb:embosstexture, lb:threshold-alpha, lb:edge-extract to work proper.
Said plugins ship with this filter.

Rough Graph recreation here. If you paste this syntax in GEGL Graph you can loosely test this plugin without installing it. 

median-blur radius=10 alpha-percentile=100
gaussian-blur std-dev-x=7 std-dev-y=7
id=first2
plus aux=[ ref=first2 emboss depth=55 elevation=13 azimuth=94 opacity value=3.9 ]
median-blur radius=0
 id=ig alien-map cpn-1-frequency=5 cpn-2-frequency=3 cpn-2-frequency=13 gimp:desaturate mode=average hue-chroma lightness=-13 opacity value=6.0 id=color gimp:layer-mode layer-mode=hsl-color composite-mode=auto opacity=0.021  composite-mode=auto  aux=[ ref=color color-overlay value=#ffec2b box-blur radius=30 ] noise-reduction iterations=3 gimp:layer-mode layer-mode=grain-merge opacity=0.54 composite-mode=auto aux=[ ref=ig lb:innerglow radius=14 value2=#ffeb2b gaussian-blur std-dev-x=5 std-dev-y=5 ] levels in-low=0.032 id=shadow gimp:layer-mode layer-mode=behind opacity=0.033 aux=[ ref=shadow color-overlay value=#000000 gaussian-blur std-dev-x=12 std-dev-y=12  translate x=6 y=15  ] saturation scale=1.00 lb:threshold-alpha alphadegree=0.7 median-blur radius=0 id=ee gimp:layer-mode layer-mode=subtract opacity=0.07 aux=[ ref=ee lb:edge-extract ] id=et gimp:layer-mode layer-mode=subtract opacity=0.015 aux=[ ref=et  lb:embosstexture ] median-blur radius=0 id=sg gimp:layer-mode layer-mode=normal opacity=0.25 aux=[ ref=sg softglow brightness=0.45 ] bloom strength=20 id=dog gimp:layer-mode  layer-mode=grain-merge opacity=0.19 aux=[ ref=dog difference-of-gaussians ]
hue-chroma lightness=9


 */

#include "config.h"
#include <glib/gi18n-lib.h>

#ifdef GEGL_PROPERTIES

 /*This is a long GEGL graph that makes a gold effect on top of a specialized custom bevel like command. This depends on my plugins Inner Glow, Advance Emboss, Threshold Alpha 2, and Edge Extract.*/
#define GEGLGRAPHSTRING \
" id=ig alien-map cpn-1-frequency=5 cpn-2-frequency=3 cpn-2-frequency=13 gimp:desaturate mode=average hue-chroma lightness=-13 opacity value=6.0 id=color gimp:layer-mode layer-mode=hsl-color composite-mode=auto opacity=0.021  composite-mode=auto  aux=[ ref=color color-overlay value=#ffec2b box-blur radius=30 ] noise-reduction iterations=3 gimp:layer-mode layer-mode=grain-merge opacity=0.54 composite-mode=auto aux=[ ref=ig lb:innerglow radius=14 value2=#ffeb2b gaussian-blur abyss-policy=none std-dev-x=5 std-dev-y=5  clip-extent=false ] levels in-low=0.032 id=shadow gimp:layer-mode layer-mode=behind opacity=0.033 aux=[ ref=shadow color-overlay value=#000000 gaussian-blur abyss-policy=none  clip-extent=false std-dev-x=12 std-dev-y=12  translate x=6 y=15  ] saturation scale=1.00 lb:threshold-alpha alphadegree=0.7 median-blur abyss-policy=none radius=0 id=ee gimp:layer-mode layer-mode=subtract opacity=0.07 aux=[ ref=ee lb:edge-extract ] id=et gimp:layer-mode layer-mode=subtract opacity=0.015 aux=[ ref=et  lb:embosstexture ] median-blur radius=0 abyss-policy=none id=sg gimp:layer-mode layer-mode=normal opacity=0.25 aux=[ ref=sg softglow brightness=0.45 ] bloom strength=20 id=dog gimp:layer-mode  layer-mode=grain-merge opacity=0.19 aux=[ ref=dog difference-of-gaussians ] "\

enum_start (meme_gold_text)
  enum_value (GEGL_BLEND_MODE_TYPE_COLORDODGE,      "colordodge",
              N_("Color Dodge"))
  enum_value (GEGL_BLEND_MODE_TYPE_PLUS,      "plus",
              N_("Plus"))
enum_end (memegoldtext)
 /*for an unknown reason softlight and overlay do exactly the same thing as color dodge with this filter. so they have been removed.*/

property_enum (blendmode, _("Blend Mode of Internal Emboss"),
    memegoldtext, meme_gold_text,
    GEGL_BLEND_MODE_TYPE_PLUS)
  description    (_("Blend mode of the internal emboss. Changing this will radically alter the bevel. "))


enum_start (median_blur_neighborhoodcbgold)
  enum_value (MEDIAN_BLUR_NEIGHBORHOOD_SQUAREcb,  "squarecb",  N_("Square"))
  enum_value (MEDIAN_BLUR_NEIGHBORHOOD_CIRCLEcb,  "circlecb",  N_("Circle"))
  enum_value (MEDIAN_BLUR_NEIGHBORHOOD_DIAMONDcb, "diamondcb", N_("Diamond"))
enum_end (MedianBlurNeighborhoodcbgold)


property_boolean (pluginpolicy, _("Enable or Disable Plugin"), TRUE)
  description    (_("Hidden operation to disable Gold Text incase another plugin needs to call it. If you are a GEGL plugin developer you can call this plugin and have a disable checkbox easy this way."))
    ui_meta     ("role", "output-extent")
 /*Output extent is code to hide this option from Gimp's GUI*/


property_enum (medianshape, _("Choose Internal Median Shape"),
               MedianBlurNeighborhoodcbgold, median_blur_neighborhoodcbgold,
               MEDIAN_BLUR_NEIGHBORHOOD_CIRCLEcb)
  description (_("Neighborhood type"))
    ui_meta     ("role", "output-extent")


property_double (expand, _("Expand Bevel"), 5)
   description (_("Internal gaussian blur to increase the size of the gold bevel"))
   value_range (2.0, 11.0)


property_double (azimuth, _("Azimuth"), 67.0)
    description (_("Light angle (degrees)"))
    value_range (30, 90)
    ui_meta ("unit", "degree")
    ui_meta ("direction", "ccw")

property_double (elevation, _("Elevation"), 9.0)
    description (_("Elevation angle (degrees). This is an emboss setting that rotates the brightest pixels."))
    value_range (7, 70)
    ui_meta ("unit", "degree")


property_int  (medianradius, _("Internal Median Blur Radius"), 3)
  value_range (0, 10)
  ui_range    (0, 10)
  ui_meta     ("unit", "pixel-distance")
  description (_("Median Blur's Radius for wideness control. Lower values make the bevel more wide, higher values make the bevel less wide."))


property_double (huerotate, _("Hue Rotation -0 resets"),  0.0)
   description  (_("Hue rotation -  0 resets. This will hue rotate everything in the gold bevel to make it an alternative color."))
   value_range  (-180.0, 180.0)

property_double (desaturate, _("Desaturate Gold Bevel (for silver)"),  1.4)
   description  (_("Desaturate entirely for Silver Effect or just because you want to make the color less intense."))
   value_range  (0.0, 1.5)

property_double (light, _("Lightness adjustment"),  1.0)
   description  (_("Light adjustment of the bevel."))
   value_range  (0.0, 10.0)

#else

#define GEGL_OP_META
#define GEGL_OP_NAME     goldbevel
#define GEGL_OP_C_SOURCE goldbevel.c

#include "gegl-op.h"

typedef struct
{
  GeglNode *input;
  GeglNode *white;
  GeglNode *fix;
  GeglNode *goldmegagraph;
  GeglNode *median;
  GeglNode *gaussian;
  GeglNode *colordodge;
  GeglNode *emboss;
  GeglNode *plus;
  GeglNode *opacity;
  GeglNode *huerotate;
  GeglNode *saturation;
  GeglNode *output;
}State;

static void
update_graph (GeglOperation *operation)
{
  GeglProperties *o = GEGL_PROPERTIES (operation);
  State *state = o->user_data;
  if (!state) return;


  GeglNode *usethis = state->plus; /* the default blend mode */
  switch (o->blendmode) {
    case GEGL_BLEND_MODE_TYPE_COLORDODGE: usethis = state->colordodge; break;
    case GEGL_BLEND_MODE_TYPE_PLUS: usethis = state->plus; break;
default: usethis = state->plus;

}

  if (o->pluginpolicy)
  {
  gegl_node_link_many (state->input, state->white, state->median, state->gaussian, usethis, state->opacity, state->goldmegagraph, state->fix,  state->huerotate, state->saturation, state->output, NULL);
/*Above contains most of the GEGL GRAPH, the first command (white) forces a white color overlay, ignoring whatever the color original was. 
After that is gaussian blur connecting to a blendable emboss (usethis) to make a bevel.
Then (gold mega graph) which is a long string of GEGL syntax is added on top of the bevel to make a gold metallic effect on the bevel*/
  gegl_node_connect (usethis, "aux", state->emboss, "output");
  gegl_node_link_many (state->gaussian, state->emboss,  NULL);
/*Emboss is being instructed to fuse with a selected blend mode.*/
  }
else
  gegl_node_link_many (state->input, state->output,  NULL);
}
/*This is an instruction to disable the plugin with a hidden dev checkbox. It is code for - do nothing.*/
static void attach (GeglOperation *operation)
{
  GeglNode *gegl = operation->node;
GeglProperties *o = GEGL_PROPERTIES (operation);
  GeglNode *input, *output, *median, *huerotate, *white, *fix, *saturation, *goldmegagraph, *colordodge, *plus, *opacity, *gaussian, *emboss;

  input    = gegl_node_get_input_proxy (gegl, "input");
  output   = gegl_node_get_output_proxy (gegl, "output");
  GeglColor *white_embedded_for_gold = gegl_color_new ("#ffffff"); /*The color white is being embedded and feed to color-overlay's value property.*/

  white   = gegl_node_new_child (gegl,
                                  "operation", "gegl:color-overlay", "value", white_embedded_for_gold,  
                                  NULL);

  goldmegagraph    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", GEGLGRAPHSTRING,
                                  NULL);


  median    = gegl_node_new_child (gegl,
                                  "operation", "gegl:median-blur", "alpha-percentile", 0.0, "abyss-policy",     GEGL_ABYSS_NONE,
                                  NULL);

  fix    = gegl_node_new_child (gegl,
                                  "operation", "gegl:median-blur", "radius", 0, "abyss-policy",     GEGL_ABYSS_NONE,
                                  NULL); /* Median Blur at zero is used to fix all sorts of bugs in GEGL Graph. I don't know why
                                            but it has a interesting property that solves several known bugs in GEGL. It is 
                                            at 0 so it makes no changes to the image. In this case it is solving a unique
                                            bug relating to hue rotation being darker then usual. */

  colordodge    = gegl_node_new_child (gegl,
                                  "operation", "gegl:color-dodge",
                                  NULL);


  plus    = gegl_node_new_child (gegl,
                                  "operation", "gegl:plus",
                                  NULL);


  opacity   = gegl_node_new_child (gegl,
                                  "operation", "gegl:opacity", "value", 3.9,
                                  NULL);

  saturation   = gegl_node_new_child (gegl,
                                  "operation", "gegl:saturation", 
                                  NULL);

  gaussian    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gaussian-blur", "clip-extent", FALSE, "abyss-policy",     0,
   "filter", 1,
                                  NULL);


  emboss    = gegl_node_new_child (gegl,
                                  "operation", "gegl:emboss", "depth", 60,
                                  NULL);


  huerotate    = gegl_node_new_child (gegl,
                                  "operation", "gegl:hue-chroma",
                                  NULL);

  gegl_operation_meta_redirect (operation, "medianradius", median, "radius");
  gegl_operation_meta_redirect (operation, "expand", gaussian, "std-dev-x");
  gegl_operation_meta_redirect (operation, "expand", gaussian, "std-dev-y");
  gegl_operation_meta_redirect (operation, "azimuth", emboss, "azimuth");
  gegl_operation_meta_redirect (operation, "elevation", emboss, "elevation");
  gegl_operation_meta_redirect (operation, "medianshape", median, "neighborhood");
  gegl_operation_meta_redirect (operation, "huerotate", huerotate, "hue");
  gegl_operation_meta_redirect (operation, "light", huerotate, "lightness");
  gegl_operation_meta_redirect (operation, "desaturate", saturation, "scale");

  State *state = g_malloc0 (sizeof (State));
  state->input = input;
  state->median = median;
  state->fix = fix;
  state->saturation = saturation;
  state->white = white;
  state->goldmegagraph = goldmegagraph;
  state->gaussian = gaussian;
  state->colordodge = colordodge;
  state->emboss = emboss;
  state->plus = plus;
  state->opacity = opacity;
  state->huerotate = huerotate;
  state->output = output;

  o->user_data = state;
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
    "name",        "lb:gold",
    "title",       _("Gold Text"),
    "reference-hash", "h234325gold2ac",
    "description", _("Transform normal text into Gold"
                     ""),
    "gimp:menu-path", "<Image>/Filters/Text Styling",
    "gimp:menu-label", _("Gold..."),
    NULL);
}

#endif
