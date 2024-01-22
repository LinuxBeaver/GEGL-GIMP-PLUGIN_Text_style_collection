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
 * 2023 Beaver GEGL Skeleton Text
 */


#include "config.h"
#include <glib/gi18n-lib.h>

#ifdef GEGL_PROPERTIES

/*

gaussian-blur std-dev-x=30 std-dev-y=30
cubism tile-size=1
color-overlay value=white
lb:threshold-alpha

id=contain

over aux=[
ref=contain
median-blur radius=0

cubism tile-size=10
distance-transform
median-blur radius=0 alpha-percentile=10 neighborhood=diamond

median-blur radius=0

]

crop

id=legacy

gimp:layer-mode layer-mode=hardlight-legacy aux=[ ref=legacy

shadows-highlights

shadows=100
highlights=-95
whitepoint=-10
radius=33.560000000000002
compress=31.800000000000001
shadows-ccorrect=54.390000000000001
highlights-ccorrect=20.5

]

difference-of-gaussians radius1=0 radius2=2.5
median-blur radius=0
color-to-alpha color=black

 */


#define SKELETON_TEXT_MAIN \
" color-overlay value=white lb:threshold-alpha id=contain over aux=[ ref=contain median-blur radius=0 cubism tile-size=10 distance-transform median-blur radius=0 alpha-percentile=10 neighborhood=diamond median-blur radius=0 ] crop id=legacy gimp:layer-mode layer-mode=hardlight-legacy aux=[ ref=legacy shadows-highlights shadows=100 highlights=-95 whitepoint=-10 radius=33.560000000000002 compress=31.800000000000001 shadows-ccorrect=54.390000000000001 highlights-ccorrect=20.5 ] difference-of-gaussians radius1=0 radius2=2.5 median-blur radius=0 color-to-alpha color=black opacity value=3 "\

property_double (xstretch, _("Crunch Skeleton X"), 0.0)
   description  (_("Internal gaussian blur to control the skeletal text"))
   value_range  (0.0, 15.0)
  ui_steps      (0.01, 0.10)
  ui_meta       ("axis", "x")

property_double (ystretch, _("Crunch Skeleton Y"), 0.0)
   description  (_("Internal gaussian blur to control the skeletal text"))
   value_range  (0.0, 15.0)
  ui_steps      (0.01, 0.10)
  ui_meta       ("axis", "y")


property_double (internalcubism, _("Internal cubism tile size"), 1)
   description  (_("Tile Size of Cubism"))
  ui_range (1.0, 10.0)
   value_range  (1.0, 10.0)


property_seed (seed, _("Random seed"), rand)


property_color (color, _("Color"), "#ffffff")
    description (_("Color of the skeletal text"))

#else

#define GEGL_OP_META
#define GEGL_OP_NAME     skeleton
#define GEGL_OP_C_SOURCE skeleton.c

#include "gegl-op.h"

static void attach (GeglOperation *operation)
{
  GeglNode *gegl = operation->node;
  GeglNode *input, *output, *gaussian, *cubism, *graph, *fix, *color;

  input    = gegl_node_get_input_proxy (gegl, "input");
  output   = gegl_node_get_output_proxy (gegl, "output");


   graph   = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string",  SKELETON_TEXT_MAIN,
                                  NULL);


   cubism   = gegl_node_new_child (gegl,
                                  "operation", "gegl:cubism",   
                                  NULL);

   gaussian   = gegl_node_new_child (gegl,
                                  "operation", "gegl:gaussian-blur",   
                                  NULL);

   color   = gegl_node_new_child (gegl,
                                  "operation", "gegl:color-overlay",   
                                  NULL);

   fix   = gegl_node_new_child (gegl,
                                  "operation", "gegl:median-blur", "radius", 0,   
                                  NULL);

  gegl_operation_meta_redirect (operation, "xstretch", gaussian, "std-dev-x");
  gegl_operation_meta_redirect (operation, "ystretch", gaussian, "std-dev-y");
  gegl_operation_meta_redirect (operation, "seed", cubism, "seed");
  gegl_operation_meta_redirect (operation, "internalcubism", cubism, "tile-size");
  gegl_operation_meta_redirect (operation, "color", color, "value");

  gegl_node_link_many (input, gaussian, cubism, graph, color, fix, output, NULL);

}

static void
gegl_op_class_init (GeglOpClass *klass)
{
  GeglOperationClass *operation_class;

  operation_class = GEGL_OPERATION_CLASS (klass);

  operation_class->attach = attach;

  gegl_operation_class_set_keys (operation_class,
    "name",        "lb:skeleton",
    "title",       _("Skeleton Text"),
    "reference-hash", "45g3avaporwave414e",
    "description", _("This filter extracts delicate lines from a distance map (sharp bevel) algorithm to make text appear to have a skeletal structure to it. One can also say it looks like a nervous system or roots underground. "
                     ""),
    "gimp:menu-path", "<Image>/Filters/Text Styling",
    "gimp:menu-label", _("Skeleton Text..."),
    NULL);
}

#endif
