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
 * Credit to Øvind Kolas (pippin) for major GEGL contributions
 * 2022 Beaver (GEGL Edge Detection Extract)
 */

/* June 25 2023 recreation of GEGL Graph. If you feed this syntax into
Gimp's GEGL graph you can run this filter without installing it.

gray
edge algorithm=sobel
gegl:threshold value=0.4
invert
color-to-alpha color=#ffffff
gaussian-blur std-dev-x=0.5 std-dev-y=0.5
value-invert
color-overlay value=#0fff00
 */

#include "config.h"
#include <glib/gi18n-lib.h>

#ifdef GEGL_PROPERTIES

property_double (edgeamount, _("Edge Amount"), 10)
   description (_("Strength of Effect"))
   value_range (3.0, 16.0)
   ui_range    (3.0, 16.0)


property_double (threshold, _("Threshold"), 0.76)
    value_range (-0.25, 0.90)
    ui_range    (-0.25, 0.90)
    description(_("Scalar threshold level (overridden if an auxiliary input buffer is provided.)."))

property_double (gaus, _("Blur"), 1.0)
   description (_("Standard deviation (spatial scale factor)"))
   value_range (0.5, 20.0)
   ui_range    (0.5, 20.0)
   ui_gamma    (3.0)
   ui_meta     ("unit", "pixel-distance")
   ui_meta     ("axis", "y")

property_color (value, _("Color"), "#ffffff")
    description (_("The color to paint over the input"))

#else

#define GEGL_OP_META
#define GEGL_OP_NAME     edgeextract
#define GEGL_OP_C_SOURCE edgeextract.c

#include "gegl-op.h"

static void attach (GeglOperation *operation)
{
  GeglNode *gegl = operation->node;
  GeglNode *input, *output, *gray, *edge, *threshold, *c2a, *invert, *vinvert, *color, *gaus;

  input    = gegl_node_get_input_proxy (gegl, "input");
  output   = gegl_node_get_output_proxy (gegl, "output");


  gray = gegl_node_new_child (gegl,
                                  "operation", "gegl:gray",
                                  NULL);


  edge = gegl_node_new_child (gegl,
                                  "operation", "gegl:edge",
                                  NULL);


  threshold = gegl_node_new_child (gegl,
                                  "operation", "gegl:threshold",
                                  NULL);


  c2a = gegl_node_new_child (gegl,
                                  "operation", "gegl:color-to-alpha",
                                  NULL);

   invert = gegl_node_new_child (gegl,
                                  "operation", "gegl:invert",
                                  NULL);


   vinvert = gegl_node_new_child (gegl,
                                  "operation", "gegl:value-invert",
                                  NULL);


   gaus = gegl_node_new_child (gegl,
                                  "operation", "gegl:gaussian-blur",
                                  NULL);


   color = gegl_node_new_child (gegl,
                                  "operation", "gegl:color-overlay",
                                  NULL);

  gegl_operation_meta_redirect (operation, "edgeamount", edge, "amount");
  gegl_operation_meta_redirect (operation, "threshold", threshold, "value");
  gegl_operation_meta_redirect (operation, "gaus", gaus, "std-dev-x");
  gegl_operation_meta_redirect (operation, "gaus", gaus, "std-dev-y");
  gegl_operation_meta_redirect (operation, "value", color, "value");

  gegl_node_link_many (input, gray, edge, threshold, invert, c2a, gaus, vinvert, color, output, NULL);
}

static void
gegl_op_class_init (GeglOpClass *klass)
{
  GeglOperationClass *operation_class;

  operation_class = GEGL_OPERATION_CLASS (klass);

  operation_class->attach = attach;

  gegl_operation_class_set_keys (operation_class,
    "name",        "lb:edge-extract",
    "title",       _("Edge Extraction"),
    "categories",  "Thirdpartyfilters",
    "reference-hash", "456j6bfghd60f4f65s52dac",
    "description", _("Extract edges with the edge sobel algorithm and other things    "
                     ""),
    NULL);
}

#endif
