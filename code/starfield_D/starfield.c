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
 * 2022 Beaver (GEGL starfield)
 */

/*
You can test starfield without installing it by giving this info to Gimp's GEGL Graph filter.
This graph may not be a 100% accurate representation of it, but it is close enough.
 
id=1 src  aux=[ ref=1 color ] crop
color-overlay value=#ffffff
crop
noise-hsv saturation-distance=0.000 value-distance=-2  holdness=2 seed=4 
invert
levels   out-high=3.60 in-high=0.3
gamma value=25
gaussian-blur std-dev-x=1.0 std-dev-y=1.0
crop
softglow
 */


#include "config.h"
#include <glib/gi18n-lib.h>

#ifdef GEGL_PROPERTIES

#define TUTORIALG \
" id=1 src  aux=[ ref=1 color ] crop "\
/* This GEGL Graph allows it to apply on transparent surfaces. When this filter was first released in Summer 2022 it required an opaque background. */

property_double (saturation_distance, _("Add background Stars and enhance color"), 0.035)
  value_range   (0.025, 0.046)


property_double (value_distance, _("Amount of Stars"), 0.055)
  value_range   (0.043, 0.065)

property_seed   (seed, _("Random seed"), rand)


property_double (out_high, _("Make Stars Brighter"), 4.15)
    description (_("Highest luminance level in output"))
    ui_range    (3.95, 4.2)

property_double (gamma, _("Size range of Stars"), 14)
   description(_("Slide up to only show large stars. Slide down to only show small stars"))
   ui_range (0, 40)


property_double (std_dev, _("Blur Stars"), 1.0)
   description (_("Blur the stars. An Alt use for this can make snow"))
   value_range (0.0, 7.0)
   ui_range    (0.24, 7.0)
   ui_gamma    (3.0)
   ui_meta     ("unit", "pixel-distance")

property_double (saturation, _("Add Color to Stars"), 0.0)
    description(_("Scale, strength of effect"))
    value_range (0.0, 1.0)
    ui_range (0.0, 1.0)

property_double (factor, _("Zoom Motion Blur"), 0.00)
    value_range (0, 0.30)
    ui_range    (0.0, 0.30)
    ui_gamma    (2.0)


#else

#define GEGL_OP_META
#define GEGL_OP_NAME     starfield
#define GEGL_OP_C_SOURCE starfield.c

#include "gegl-op.h"

static void attach (GeglOperation *operation)
{
  GeglNode *gegl = operation->node;
  GeglNode *input, *output, *graph, *color, *noise, *invert, *levels, *gamma, *blur, *glow, *saturation, *zmb;

  input    = gegl_node_get_input_proxy (gegl, "input");
  output   = gegl_node_get_output_proxy (gegl, "output");
  GeglColor *starcolor = gegl_color_new ("#ffffff");


  color = gegl_node_new_child (gegl,
                                  "operation", "gegl:color-overlay",
                                   "value", starcolor, NULL);
       

  graph = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", TUTORIALG,
                                  NULL);


  noise = gegl_node_new_child (gegl,
                                  "operation", "gegl:noise-hsv", "holdness", 8,
                                  NULL);

  invert = gegl_node_new_child (gegl,
                                  "operation", "gegl:invert",
                                  NULL);

  levels = gegl_node_new_child (gegl,
                                  "operation", "gegl:levels", "in-high", 0.33,
                                  NULL);

  gamma = gegl_node_new_child (gegl,
                                  "operation", "gegl:gamma",
                                  NULL);

  blur = gegl_node_new_child (gegl,
                                  "operation", "gegl:gaussian-blur",
                                  NULL);

  saturation = gegl_node_new_child (gegl,
                                  "operation", "gegl:saturation",
                                  NULL);

  glow = gegl_node_new_child (gegl,
                                  "operation", "gegl:softglow",
                                  NULL);

  zmb = gegl_node_new_child (gegl,
                                  "operation", "gegl:motion-blur-zoom",
                                  NULL);

    gegl_operation_meta_redirect (operation, "saturation_distance", noise, "saturation-distance");
    gegl_operation_meta_redirect (operation, "value_distance", noise, "value-distance");
    gegl_operation_meta_redirect (operation, "seed", noise, "seed");
    gegl_operation_meta_redirect (operation, "gamma", gamma, "value");
    gegl_operation_meta_redirect (operation, "std_dev", blur, "std-dev-x");
    gegl_operation_meta_redirect (operation, "std_dev", blur, "std-dev-y");
    gegl_operation_meta_redirect (operation, "out_high", levels, "out-high");
    gegl_operation_meta_redirect (operation, "saturation", saturation, "scale");
    gegl_operation_meta_redirect (operation, "factor", zmb, "factor");
    gegl_operation_meta_redirect (operation, "string",  graph, "string");


  gegl_node_link_many (input, graph, color, noise, invert, levels, gamma, blur, glow, saturation, zmb, output, NULL);




}

static void
gegl_op_class_init (GeglOpClass *klass)
{
  GeglOperationClass *operation_class;

  operation_class = GEGL_OPERATION_CLASS (klass);

  operation_class->attach = attach;

  gegl_operation_class_set_keys (operation_class,
    "name",        "gegl:starfield",
    "title",       _("Starfield"),
    "categories",  "Aristic",
    "reference-hash", "45eak6vgah28vf20fno25sb2ac",
    "description", _("Render a Starry Night with GEGL. "
                     ""),
    "gimp:menu-path", "<Image>/Filters/Render/Fun",
    "gimp:menu-label", _("Starfield..."),
    NULL);
}

#endif
