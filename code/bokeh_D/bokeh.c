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
 * 2022 Beaver, GEGL Bokeh 
 */

/*

Recreation of Bokeh's GEGL Graph --june 24 2023 -- this may not be 100% the same
but it is close enough. If you put this in Gimp's GEGL Graph you can test 
Bokeh without installing it

color value=#ff23cf 
id=1 divide aux=[ ref=1 cell-noise scale=0.12 shape=3 seed=33   ]
median-blur radius=25 percentile=100 neighborhood=circle
color-to-alpha color=#f553ff transparency-threshold=0.3
id=2 multiply aux=[ ref=2 color-overlay value=#ff1300 ]
gaussian-blur std-dev-x=0 std-dev-y=0
median-blur radius=0

This Plugin shows two different ways to embed a color. GEGL Graph strings "hiddencolorbokeh" and GEGL color embedding "hiddencolorbokeh2".
 */

#include "config.h"
#include <glib/gi18n-lib.h>

#ifdef GEGL_PROPERTIES


#define hiddencolorbokeh \
" gegl:color value=#ff23cf "\



/*Silly words like neighborhoodo are here so it does not conflict with Median Blur's ENUM list - that is why I added the o's
NO TWO FILTERS CAN SHARE THE SAME ENUM LIST NAME*/
enum_start (gegl_median_blur_neighborhoodo)
  enum_value (GEGL_MEDIAN_BLUR_NEIGHBORHOOD_SQUAREo,  "square",  N_("Square"))
  enum_value (GEGL_MEDIAN_BLUR_NEIGHBORHOOD_CIRCLEo,  "circle",  N_("Circle"))
  enum_value (GEGL_MEDIAN_BLUR_NEIGHBORHOOD_DIAMONDo, "diamond", N_("Diamond"))
enum_end (GeglMedianBlurNeighborhoodo)


property_enum (neighborhood, _("Shape"),
               GeglMedianBlurNeighborhoodo, gegl_median_blur_neighborhoodo,
               GEGL_MEDIAN_BLUR_NEIGHBORHOOD_CIRCLEo)
  description (_("Median Shapes for the bokeh. Circle, Square and Diamond are the options."))

property_color  (color, _("Color of the Bokeh"), "#ffffff")

property_double  (amount, _("Amount of Bokeh shapes"), 0.12)
    description  (_("The scale of the noise function that increases the amount of individual bokeh shapes"))
    value_range  (0.050, 0.35)


property_seed    (seed, _("Random seed"), rand)
    description  (_("The random seed for the noise function"))

property_int  (size, _("Internal Median to increase Bokeh Size"), 25)
  value_range (1, 80)
  ui_range    (1, 80)
  ui_meta     ("unit", "pixel-distance")
  description (_("Median Blur Radius to increase the size of the bokeh. "))

property_double (opacity, _("Opacity Control"), 0.6)
    description (_("Global opacity value for the bokehs."))
    value_range (0.1, 1.3)
    ui_range    (0.1, 1.3)

property_int (blur, _("Blur"), 2)
   description(_("Blurring tiny bokehs will make it snow"))
   value_range (0, 12)
   ui_range    (0, 12)
   ui_gamma   (1.5)



#else

#define GEGL_OP_META
#define GEGL_OP_NAME     bokeh
#define GEGL_OP_C_SOURCE bokeh.c

#include "gegl-op.h"

static void attach (GeglOperation *operation)
{
  GeglNode *gegl = operation->node;
  GeglNode *input, *output, *c2a, *color, *opacity, *replace, *putinside, *median, *divide, *crop, *repairgeglgraph, *coloroverlay, *blur, *noise;
  GeglColor *hiddencolorbokeh2 = gegl_color_new ("#ff23cf");


  input    = gegl_node_get_input_proxy (gegl, "input");
  output   = gegl_node_get_output_proxy (gegl, "output");


 
  c2a = gegl_node_new_child (gegl,
                                  "operation", "gegl:color-to-alpha", "transparency-threshold", 0.5, "color", hiddencolorbokeh2, NULL);
                               
color = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", hiddencolorbokeh, NULL);
                               
opacity = gegl_node_new_child (gegl,
                                  "operation", "gegl:opacity",
                                  NULL);
median = gegl_node_new_child (gegl,
                                  "operation", "gegl:median-blur", "percentile", 100.0,
                                  NULL);
divide = gegl_node_new_child (gegl,
                                  "operation", "gegl:divide",
                                  NULL);

coloroverlay = gegl_node_new_child (gegl,
                                  "operation", "gegl:color-overlay",
                                  NULL);
noise = gegl_node_new_child (gegl,
                                  "operation", "gegl:cell-noise",
                                  NULL);

blur = gegl_node_new_child (gegl,
                                  "operation", "gegl:lens-blur",
                                  NULL);

replace = gegl_node_new_child (gegl,
                                  "operation", "gegl:src",
                                  NULL);

crop = gegl_node_new_child (gegl,
                                  "operation", "gegl:crop",
                                  NULL);

putinside = gegl_node_new_child (gegl,
                                  "operation", "gegl:nop",
                                  NULL);


  repairgeglgraph      = gegl_node_new_child (gegl, "operation", "gegl:median-blur",
                                         "radius",       0,
                                         NULL);

 /*Repair GEGL Graph is a critical operation for Gimp's non-destructive future.
A median blur at zero radius is confirmed to make no changes to an image. 
This option resets gegl:opacity's value to prevent a known bug where
plugins like clay, glossy balloon and custom bevel glitch out when
drop shadow is applied in a gegl graph below them.*/
 
  gegl_node_link_many (input, putinside, replace, crop, output, NULL);
  gegl_node_connect_from (replace, "aux", repairgeglgraph, "output");
  gegl_node_link_many (putinside, color, divide, median, c2a, coloroverlay, opacity, blur, repairgeglgraph, NULL);

  gegl_node_connect_from (divide, "aux", noise, "output");

    gegl_operation_meta_redirect (operation, "value", color, "value");
    gegl_operation_meta_redirect (operation, "opacity", opacity, "value");
    gegl_operation_meta_redirect (operation, "size", median, "radius");
    gegl_operation_meta_redirect (operation, "color", coloroverlay, "value");
    gegl_operation_meta_redirect (operation, "neighborhood", median, "neighborhood");
    gegl_operation_meta_redirect (operation, "amount", noise, "scale");
    gegl_operation_meta_redirect (operation, "shape", noise, "shape");
    gegl_operation_meta_redirect (operation, "seed", noise, "seed");
    gegl_operation_meta_redirect (operation, "blur", blur, "radius");

}

static void
gegl_op_class_init (GeglOpClass *klass)
{
  GeglOperationClass *operation_class;

  operation_class = GEGL_OPERATION_CLASS (klass);

  operation_class->attach = attach;

  gegl_operation_class_set_keys (operation_class,
    "name",        "lb:bokeh",
    "title",       _("Bokeh Effect -Requires Alpha Channel "),
    "reference-hash", "1a1210akk00k101x2001b2hc",
    "description", _("Create a fake bokeh effect using GEGL. For edits directly on top of the image without layers use the normal or other blending options (like overlay or softlight). If the image is glitching it is because your layer has no alpha channel. "
                     ""),
    "gimp:menu-path", "<Image>/Filters/Render/Fun",
    "gimp:menu-label", _("Bokeh..."),
    NULL);
}

#endif
