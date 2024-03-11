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
 * 2023 Beaver, Ocean's Surface

Test this filter without installing by pasting this syntax into Gimp's GEGL graph filter.

id=1  
over   aux=[ color value=#c1c1c1   ]

gimp:layer-mode layer-mode=difference composite-space=rgb-perceptual opacity=0.8 blend-space=auto aux=[ ref=1 noise-solid turbulent=true  x-size=4 y-size=4 detail=1.9  seed=3304 
  
   ]
gimp:layer-mode layer-mode=linear-burn blend-space=rgb-perceptual  opacity=1 aux=[ color value=#89e5ff  ] 
median-blur radius=0
bloom strength=30

 */

#include "config.h"
#include <glib/gi18n-lib.h>

#ifdef GEGL_PROPERTIES


property_double (xnoise, _("Solid Noise Horizontal"), 4.0)
   description (_("Solid Noise's horizontal size setting for the water"))
   value_range (1.0, 9.0)
   ui_range    (1.0, 9.0)
   ui_gamma    (3.0)
    ui_meta     ("axis", "x")

property_double (ynoise, _("Solid Noise Vertical"), 4.0)
   description (_("Solid Noise's verticial size setting for the water"))
   value_range (1.0, 9.0)
   ui_range    (1.0, 9.0)
   ui_gamma    (3.0)
    ui_meta     ("axis", "y")

property_seed (seed, _("Random seed"), rand)

property_double (glow, _("Glow effect on water"), 40.0)
   description (_("Glow effect on the water using the 'bloom filter'"))
   value_range (0.0, 60.0)
   ui_range    (10.0,60.0)
   ui_gamma    (3.0)


property_color  (color, _("Color Overlay"), "#c3eaff")
    description (_("Color of 'Ocean Surface'. Color is blended with an internal linear burn."))

property_double (coloropacity, _("Opacity of Color"), 1.00)
   description (_("Opacity of the color overlay"))
   value_range (0.00, 1.00)
   ui_gamma    (3.0)
  ui_steps      (0.1, 1.0)

#else

#define GEGL_OP_META
#define GEGL_OP_NAME     ocean_surface
#define GEGL_OP_C_SOURCE ocean_surface.c

#include "gegl-op.h"

static void attach (GeglOperation *operation)
{
  GeglNode *gegl = operation->node;
  GeglNode *input, *noise, *median, *white, *linearburn, *difference,  *opacity, *color, *glow, *normal, *output;

  input    = gegl_node_get_input_proxy (gegl, "input");
  output   = gegl_node_get_output_proxy (gegl, "output");

  noise = gegl_node_new_child (gegl,
                                  "operation", "gegl:noise-solid", "turbulent", TRUE, "detail", 1, 
                                  NULL);

  median = gegl_node_new_child (gegl,
                                  "operation", "gegl:median-blur", "radius", 0,  "abyss-policy",     GEGL_ABYSS_NONE,    
                                  NULL);
#define whitecolor \
" color value=white  "\

  white = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", whitecolor,
                                  NULL);

linearburn = gegl_node_new_child (gegl,
                              "operation", "gimp:layer-mode", "layer-mode", 53, "blend-space", 2,  NULL);

  difference = gegl_node_new_child (gegl,
                                  "operation", "gegl:difference", "srgb", TRUE, 
                                  NULL);

  color = gegl_node_new_child (gegl,
                                  "operation", "gegl:color", 
                                  NULL);

  glow = gegl_node_new_child (gegl,
                                  "operation", "gegl:bloom", 
                                  NULL);

  normal = gegl_node_new_child (gegl,
                                  "operation", "gegl:over", 
                                  NULL);

  opacity = gegl_node_new_child (gegl,
                                  "operation", "gegl:opacity", "value", 0.80, 
                                  NULL);


  gegl_node_link_many (input, normal, difference, linearburn, median, glow, output, NULL);
  gegl_node_link_many (noise, opacity,  NULL);
  gegl_node_connect (normal, "aux", white, "output");
  gegl_node_connect (linearburn, "aux", color, "output");
  gegl_node_connect (difference, "aux", opacity, "output");

 gegl_operation_meta_redirect (operation, "xnoise", noise, "x-size"); 
 gegl_operation_meta_redirect (operation, "ynoise", noise, "y-size"); 
 gegl_operation_meta_redirect (operation, "seed", noise, "seed"); 
 gegl_operation_meta_redirect (operation, "color", color, "value"); 
 gegl_operation_meta_redirect (operation, "glow", glow, "strength"); 
 gegl_operation_meta_redirect (operation, "coloropacity", linearburn, "opacity"); 

}

static void
gegl_op_class_init (GeglOpClass *klass)
{
  GeglOperationClass *operation_class;

  operation_class = GEGL_OPERATION_CLASS (klass);

  operation_class->attach = attach;

  gegl_operation_class_set_keys (operation_class,
    "name",        "lb:oceansurface",
    "title",       _("Ocean Surface"),
    "reference-hash", "32jfrrsarah3bonito3rocks34fjefefc",
    "gimp:menu-path", "<Image>/Filters/Render/Fun",
    "gimp:menu-label", _("Ocean Surface..."),
    NULL);
}

#endif
