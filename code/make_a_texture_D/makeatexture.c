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
 * 2023 Beaver (GEGL Advance emboss texture maker)
 */

/*
June 25 2023 GEGL Graph recreation of plugin.

gray
id=1 hard-light aux=[ ref=1 emboss
gaussian-blur std-dev-x=0 std-dev-y=0
opacity value=1
unsharp-mask scale=0

mean-curvature-blur iterations=9


 ]

#id=2 multiply aux=[ ref=2 color-overlay value=#5365ff  ]
hue-chroma lightness=0
denoise-dct  sigma=20
 */


#include "config.h"
#include <glib/gi18n-lib.h>

#ifdef GEGL_PROPERTIES

enum_start (gegl_blend_mode_typecbevelem)
  enum_value (GEGL_BLEND_MODE_TYPE_HARDLIGHT, "Hardlight",
              N_("HardLight"))
  enum_value (GEGL_BLEND_MODE_TYPE_MULTIPLY,      "Multiply",
              N_("Multiply"))
  enum_value (GEGL_BLEND_MODE_TYPE_COLORDODGE,      "ColorDodge",
              N_("ColorDodge"))
  enum_value (GEGL_BLEND_MODE_TYPE_PLUS,      "Plus",
              N_("Plus"))
  enum_value (GEGL_BLEND_MODE_TYPE_DARKEN,      "Darken",
              N_("Darken"))
  enum_value (GEGL_BLEND_MODE_TYPE_LIGHTEN,      "Lighten",
              N_("Lighten"))
  enum_value (GEGL_BLEND_MODE_TYPE_OVERLAY,      "Overlay",
              N_("Overlay"))
  enum_value (GEGL_BLEND_MODE_TYPE_GRAINMERGE,      "GrainMerge",
              N_("Grain Merge"))
  enum_value (GEGL_BLEND_MODE_TYPE_SOFTLIGHT,      "Softlight",
              N_("Soft Light"))
  enum_value (GEGL_BLEND_MODE_TYPE_ADDITION,      "Addition",
              N_("Addition"))
  enum_value (GEGL_BLEND_MODE_TYPE_EMBOSSBLEND,      "EmbossBlend",
              N_("ImageandColorOverlayMode"))
enum_end (GeglBlendModeTypecbevelem)

property_enum (blendmode, _("Blend Mode of Internal Emboss"),
    GeglBlendModeTypecbevelem, gegl_blend_mode_typecbevelem,
    GEGL_BLEND_MODE_TYPE_HARDLIGHT)




property_double (azimuth, _("Azimuth"), 67.0)
    description (_("Light angle (degrees)"))
    value_range (0, 360)
    ui_meta ("unit", "degree")
    ui_meta ("direction", "ccw")

property_double (elevation, _("Elevation"), 25.0)
    description (_("Elevation angle (degrees)"))
    value_range (0, 180)
    ui_meta ("unit", "degree")

property_int (depth, _("Depth (makes darker)"), 24)
    description (_("Filter width"))
    value_range (1, 100)





property_double (gaus, _("Internal Gaussian Blur"), 1)
   description (_("Standard deviation for the XY axis"))
   value_range (0.0, 3.5)




property_int  (mcb, _("Smooth"), 1)
  description (_("Controls the number of iterations"))
  value_range (0, 46)
  ui_range    (0, 46)


property_double (denoise, _("Smooth 2 (will only work in Gimp 2.10.32+)"), 1)
   description (_("Denoise filter"))
   value_range (0.0, 9.5)


property_double (sharpen, _("Sharpen"), 0.2)
    description(_("Scaling factor for unsharp-mask, the strength of effect"))
    value_range (0.0, 4.5)
    ui_range    (0.0, 4.5)
    ui_gamma    (3.0)


property_file_path(src, _("Image file Overlay"), "")
    description (_("Source image file path (png, jpg, raw, svg, bmp, tif, ...)"))



property_double (lightness, _("Lightness that can help image file and color overlay"), 0.0)
   description  (_("Lightness adjustment"))
   value_range  (-12, 26.0)


property_color (coloroverlay, _("Forced Color Overlay"), "#ffffff")
    description (_("The color to paint over the input"))



#else

#define GEGL_OP_META
#define GEGL_OP_NAME     makeatexture
#define GEGL_OP_C_SOURCE makeatexture.c

#include "gegl-op.h"

typedef struct
{
  GeglNode *input;
  GeglNode *gray;
  GeglNode *gaussian;
  GeglNode *hardlight;
  GeglNode *multiply;
  GeglNode *colordodge;
  GeglNode *emboss;
  GeglNode *plus;
  GeglNode *darken;
  GeglNode *lighten;
  GeglNode *opacity;
  GeglNode *mcb;
  GeglNode *sharpen;
  GeglNode *desat;
  GeglNode *multiply2;
  GeglNode *nop;
  GeglNode *mcol;
  GeglNode *col;
  GeglNode *imagefileoverlay;
  GeglNode *lightness;
  GeglNode *grainmerge;
  GeglNode *overlay;
  GeglNode *softlight;
  GeglNode *addition;
  GeglNode *embossblend;
  GeglNode *dn;
  GeglNode *output;
}State;

static void
update_graph (GeglOperation *operation)
{
  GeglProperties *o = GEGL_PROPERTIES (operation);
  State *state = o->user_data;
  if (!state) return;


  GeglNode *usethis = state->hardlight; /* the default */
  switch (o->blendmode) {
    case GEGL_BLEND_MODE_TYPE_MULTIPLY: usethis = state->multiply; break;
    case GEGL_BLEND_MODE_TYPE_COLORDODGE: usethis = state->colordodge; break;
    case GEGL_BLEND_MODE_TYPE_PLUS: usethis = state->plus; break;
    case GEGL_BLEND_MODE_TYPE_DARKEN: usethis = state->darken; break;
    case GEGL_BLEND_MODE_TYPE_LIGHTEN: usethis = state->lighten; break;
    case GEGL_BLEND_MODE_TYPE_OVERLAY: usethis = state->overlay; break;
    case GEGL_BLEND_MODE_TYPE_GRAINMERGE: usethis = state->grainmerge; break;
    case GEGL_BLEND_MODE_TYPE_SOFTLIGHT: usethis = state->softlight; break;
    case GEGL_BLEND_MODE_TYPE_ADDITION: usethis = state->addition; break;
    case GEGL_BLEND_MODE_TYPE_EMBOSSBLEND: usethis = state->embossblend; break;
default: usethis = state->hardlight;

  }
  gegl_node_link_many (state->input, state->gray, usethis, state->gaussian, state->opacity, state->mcb, state->sharpen, state->desat, state->multiply2, state->nop, state->mcol, state->lightness, state->dn, state->output,  NULL);
  gegl_node_connect (usethis, "aux", state->emboss, "output");

}

static void attach (GeglOperation *operation)
{
  GeglNode *gegl = operation->node;
GeglProperties *o = GEGL_PROPERTIES (operation);
  GeglNode *input, *output, *gray, *multiply, *hardlight, *embossblend, *addition, *colordodge, *grainmerge, *softlight, *overlay, *darken, *desat, *multiply2, *lighten, *mcol, *col, *nop, *plus, *opacity, *gaussian, *emboss, *lightness, *imagefileoverlay, *mcb, *sharpen, *dn;

  input    = gegl_node_get_input_proxy (gegl, "input");
  output   = gegl_node_get_output_proxy (gegl, "output");



  nop    = gegl_node_new_child (gegl,
                                  "operation", "gegl:nop",
                                  NULL);

  multiply    = gegl_node_new_child (gegl,
                                  "operation", "gegl:multiply",
                                  NULL);

  multiply2    = gegl_node_new_child (gegl,
                                  "operation", "gegl:multiply",
                                  NULL);

  hardlight    = gegl_node_new_child (gegl,
                                  "operation", "gegl:hard-light",
                                  NULL);

  colordodge    = gegl_node_new_child (gegl,
                                  "operation", "gegl:color-dodge",
                                  NULL);

  darken    = gegl_node_new_child (gegl,
                                  "operation", "gegl:darken",
                                  NULL);

  lighten    = gegl_node_new_child (gegl,
                                  "operation", "gegl:lighten",
                                  NULL);

  plus    = gegl_node_new_child (gegl,
                                  "operation", "gegl:plus",
                                  NULL);



  opacity   = gegl_node_new_child (gegl,
                                  "operation", "gegl:opacity",
                                  NULL);

  gray   = gegl_node_new_child (gegl,
                                  "operation", "gegl:gray",
                                  NULL);


  mcol   = gegl_node_new_child (gegl,
                                  "operation", "gegl:multiply",
                                  NULL);

  col   = gegl_node_new_child (gegl,
                                  "operation", "gegl:color-overlay",
                                  NULL);


  gaussian    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gaussian-blur",
   "filter", 1,
                                  NULL);


  emboss    = gegl_node_new_child (gegl,
                                  "operation", "gegl:emboss",
                                  NULL);


  imagefileoverlay    = gegl_node_new_child (gegl,
                                  "operation", "port:load",
                                  NULL);

  lightness    = gegl_node_new_child (gegl,
                                  "operation", "gegl:hue-chroma",
                                  NULL);

  mcb    = gegl_node_new_child (gegl,
                                  "operation", "gegl:mean-curvature-blur",
                                  NULL);

  sharpen    = gegl_node_new_child (gegl,
                                  "operation", "gegl:unsharp-mask",
                                  NULL);

  desat   = gegl_node_new_child (gegl,
                                  "operation", "gegl:saturation",
                                  NULL);

grainmerge = gegl_node_new_child (gegl,
                              "operation", "gimp:layer-mode", "layer-mode", 47, "composite-mode", 1, NULL);

overlay = gegl_node_new_child (gegl,
                              "operation", "gimp:layer-mode", "layer-mode", 23, "composite-mode", 3, NULL);

softlight = gegl_node_new_child (gegl,
                              "operation", "gimp:layer-mode", "layer-mode", 45, "composite-mode", 1, NULL);


addition = gegl_node_new_child (gegl,
                                  "operation", "gimp:layer-mode", "layer-mode", 33, "composite-mode", 1, NULL);

  embossblend   = gegl_node_new_child (gegl,
                                  "operation", "gegl:emboss",
                                  NULL);


  dn    = gegl_node_new_child (gegl,
                                  "operation", "gegl:denoise-dct",
                                  NULL);


  gegl_operation_meta_redirect (operation, "gaus", gaussian, "std-dev-x");
  gegl_operation_meta_redirect (operation, "gaus", gaussian, "std-dev-y");
  gegl_operation_meta_redirect (operation, "azimuth", emboss, "azimuth");
  gegl_operation_meta_redirect (operation, "elevation", emboss, "elevation");
  gegl_operation_meta_redirect (operation, "depth", emboss, "depth");
  gegl_operation_meta_redirect (operation, "src", imagefileoverlay, "src");
  gegl_operation_meta_redirect (operation, "lightness", lightness, "lightness");
  gegl_operation_meta_redirect (operation, "mcb", mcb, "iterations");
  gegl_operation_meta_redirect (operation, "sharpen", sharpen, "scale");
  gegl_operation_meta_redirect (operation, "coloroverlay", col, "value");
  gegl_operation_meta_redirect (operation, "denoise", dn, "sigma");

  gegl_node_link_many (input, gray, emboss, gaussian, opacity, mcb, sharpen, multiply2, nop, mcol, lightness, dn, output,  NULL);
  gegl_node_connect (hardlight, "aux", emboss, "output");
  gegl_node_connect (mcol, "aux", col, "output");
  gegl_node_connect (multiply2, "aux", imagefileoverlay, "output");
  gegl_node_link_many (nop, col,  NULL);



  /* now save references to the gegl nodes so we can use them
   * later, when update_graph() is called
   */
  State *state = g_malloc0 (sizeof (State));
  state->input = input;
  state->gray = gray;
  state->gaussian = gaussian;
  state->hardlight = hardlight;
  state->multiply = multiply;
  state->colordodge = colordodge;
  state->emboss = emboss;
  state->embossblend = embossblend;
  state->addition = addition;
  state->plus = plus;
  state->darken = darken;
  state->lighten = lighten;
  state->opacity = opacity;
  state->mcb = mcb;
  state->sharpen = sharpen;
  state->desat = desat;
  state->multiply2 = multiply2;
  state->nop = nop;
  state->mcol = mcol;
  state->imagefileoverlay = imagefileoverlay;
  state->lightness = lightness;
  state->grainmerge = grainmerge;
  state->overlay = overlay;
  state->softlight = softlight;
  state->dn = dn;
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
    "name",        "lb:embosstexture",
    "title",       _("Advance Emboss"),
    "categories",  "Artistic",
    "reference-hash", "em3d33efjf25612ac",
    "description", _("A fork of Gimp's emboss filter that allows texture overlays, blend mode swapping, and smoothing filters. Use alpha lock on transparent images.'"
                     ""),
    NULL);
}

#endif
