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
 * 2022 Beaver (GEGL extrusion) 
 */

/*

GEGL Graph reconstruction. This may not be 100% accurate but is a rough GEGL Graph of this plugim.  If you run this in Gimp's
GEGL Graph filter you can test this plugin without installing it.  LB EDGE SMOOTH AND LB BEVEL IS ANOTHER PLUGIN OF MINE. So 
withot them you can't run this.

lb:edgesmooth

id=1 dst-over aux=[ ref=1 motion-blur-zoom factor=0.06 center-x=-0.24 center-y=0.14 id=2 multiply aux=[ ref=2 lb:bevel    ]

gimp:threshold-alpha 


median-blur radius=4

hue-chroma lightness=0 

lb:edgesmooth

  ]
 */



#include "config.h"
#include <glib/gi18n-lib.h>

#ifdef GEGL_PROPERTIES


property_boolean (behindextrusion, _("Put Extrusion behind image"), TRUE)
  description    (_("Gimp's behind blend mode does pretty much exactly the same thing; this is just a alternative to that for novices. I used the word -pretty much- because this adds an addition edge smooth to the GEGL Graph on the first image to improve the extrusion. When this is disabled the extrusion requires the behind blend mode or to be put on a layer below"))


property_double (center_x, _("Center X"), -2.1)
    value_range (-3.5, 3.5)
    ui_range    (-3.5, 3.5)
    ui_meta     ("axis", "x")
    description(_("Horizontal movability of the extrusion"))

property_double (center_y, _("Center Y"), -1.4)
    value_range (-3.5, 3.5)
    ui_range    (-3.5, 3.5)
    ui_meta     ("axis", "y")
    description(_("Vertical movability of the extrusion"))

property_double (factor, _("Length of extrusion"), 0.009)
    description (_("Increase the length of the extrusion using an internal zoom motion blur. Due to the nature of Zoom Motion Blur depending where your image is on canvas will effect the image."))
    value_range (0, 0.180)
    ui_range    (0, 0.051)
    ui_gamma    (2.0)

property_int (depth, _("Increase roughness"), 14)
    description (_("Internal Bevel's width"))
    value_range (1, 30)


property_double (exposure, _("Darkness to light"), -1.40)
    description (_("Exposure lighting setting"))
  value_range (-3, 0.8)
    ui_range    (-3, 0.8)



#else

#define GEGL_OP_META
#define GEGL_OP_NAME     extrusion
#define GEGL_OP_C_SOURCE extrusion.c

#include "gegl-op.h"


typedef struct
{
  GeglNode *input;
  GeglNode *nr;
  GeglNode *screen;
  GeglNode *edge;
  GeglNode *zmb;
  GeglNode *multiply;
  GeglNode *bevel;
  GeglNode *edgesmoothend;
  GeglNode *edgesmoothbegin;
  GeglNode *alpha;
  GeglNode *brightness;
  GeglNode *median;
  GeglNode *chroma;
  GeglNode *nop;
  GeglNode *opacity;
  GeglNode *behind;
  GeglNode *output;
} State; 


static void attach (GeglOperation *operation)
{
  GeglNode *gegl = operation->node;
  GeglProperties *o = GEGL_PROPERTIES (operation);
  GeglNode *input, *output, *zmb, *edge, *screen, *multiply, *alpha, *behind, *nr,  *nop, *edgesmoothend, *edgesmoothbegin, *bevel, *opacity, *median, *chroma, *brightness;

  input    = gegl_node_get_input_proxy (gegl, "input");
  output   = gegl_node_get_output_proxy (gegl, "output");


  nr = gegl_node_new_child (gegl,
                                  "operation", "gegl:noise-reduction",
                                  NULL);


  screen = gegl_node_new_child (gegl,
                                  "operation", "gegl:screen",
                                  NULL);


  edge = gegl_node_new_child (gegl,
                                  "operation", "gegl:edge", "algorithm", 2,
                                  NULL);
/*2 is code for EdgeDetect Gradient */

  zmb = gegl_node_new_child (gegl,
                                  "operation", "gegl:motion-blur-zoom",
                                  NULL);

   multiply = gegl_node_new_child (gegl,
                                  "operation", "gegl:multiply",
                                  NULL);

   bevel = gegl_node_new_child (gegl,
                                  "operation", "lb:bevel",
                                  NULL);

   edgesmoothend = gegl_node_new_child (gegl,
                                  "operation", "lb:edgesmooth",
                                  NULL);

   edgesmoothbegin = gegl_node_new_child (gegl,
                                  "operation", "lb:edgesmooth",
                                  NULL);

   alpha = gegl_node_new_child (gegl,
                                  "operation", "gimp:threshold-alpha", "value", 1.08,
                                  NULL);

   brightness = gegl_node_new_child (gegl,
                                  "operation", "gegl:exposure",
                                  NULL);

  median = gegl_node_new_child (gegl,
                                  "operation", "gegl:median-blur", "radius", 1.0, "percentile", 50.0,
                                  NULL);

  chroma = gegl_node_new_child (gegl,
                                  "operation", "gegl:hue-chroma",
                                  NULL);

  behind = gegl_node_new_child (gegl,
                                  "operation", "gegl:dst-over",
                                  NULL);


  nop = gegl_node_new_child (gegl,
                                  "operation", "gegl:nop",
                                  NULL);


  opacity = gegl_node_new_child (gegl,
                                  "operation", "gegl:opacity",
                                  NULL);


/* Original graph that isn't needed anymore. This graph can't use blend mode switchers.

  gegl_node_link_many (input, zmb, nop, multiply, alpha, nop2, screen, median, nr, chroma, brightness, edgesmoothend, output, NULL);
  gegl_node_connect_from (multiply, "aux", bevel, "output"); 
  gegl_node_connect_from (screen, "aux", opacity, "output"); 
  gegl_node_link_many (nop, bevel, NULL);
  gegl_node_link_many (nop2, edge, opacity, NULL);
 */



  gegl_operation_meta_redirect (operation, "exposure", brightness, "exposure");
  gegl_operation_meta_redirect (operation, "black_level", brightness, "black-level");
  gegl_operation_meta_redirect (operation, "factor", zmb, "factor");
  gegl_operation_meta_redirect (operation, "center_x", zmb, "center-x");
  gegl_operation_meta_redirect (operation, "center_y", zmb, "center-y");
  gegl_operation_meta_redirect (operation, "depth", bevel, "bevel2");
  gegl_operation_meta_redirect (operation, "opacity", opacity, "value");



/* now save references to the gegl nodes so we can use them
   * later, when update_graph() is called
   */
  State *state = g_malloc0 (sizeof (State));
  state->input = input;
  state->nr = nr;
  state->screen = screen;
  state->edge = edge;
  state->zmb = zmb;
  state->multiply = multiply;
  state->median = median;
  state->bevel = bevel;
  state->edgesmoothbegin = edgesmoothbegin;
  state->edgesmoothend = edgesmoothend;
  state->alpha = alpha;
  state->brightness = brightness;
  state->chroma = chroma;
  state->nop = nop;
  state->opacity = opacity;
  state->behind = behind;
  state->output = output;
  o->user_data = state;
}


/*I NEED HELP FOR SOME REASON THE ONLY FILTER RUNNING HERE IS EDGE SMOOTH. THE OTHERS ARE NOT WORKING - June 23 2023 */

static void
update_graph (GeglOperation *operation)
{
  GeglProperties *o = GEGL_PROPERTIES (operation);
  State *state = o->user_data;
  if (!state) return;
  if (o->behindextrusion)
  {
/*The main GEGL Graph and behind blend mode that everything is inside */
  gegl_node_link_many (state->input, state->edgesmoothbegin, state->behind, state->output, NULL);
  gegl_node_connect_from (state->behind, "aux", state->edgesmoothend, "output"); 
  gegl_node_link_many (state->input, state->zmb, state->nop, state->multiply, state->alpha, state->median,  state->brightness, state->edgesmoothend, NULL);
/*Multiply connects to bevel */
  gegl_node_connect_from (state->multiply, "aux", state->bevel, "output"); 
  gegl_node_link_many (state->nop, state->bevel, NULL);
  }
  else
  {
/*The main GEGL Graph */
  gegl_node_link_many (state->input, state->zmb, state->nop, state->multiply, state->alpha, state->median,  state->brightness, state->edgesmoothend, state->output, NULL);
/*Multiply connects to bevel */
  gegl_node_connect_from (state->multiply, "aux", state->bevel, "output");
  gegl_node_link_many (state->nop, state->bevel, NULL);
  }
}



static void
gegl_op_class_init (GeglOpClass *klass)
{
  GeglOperationClass *operation_class = GEGL_OPERATION_CLASS (klass);
   GeglOperationMetaClass *operation_meta_class = GEGL_OPERATION_META_CLASS (klass);

  operation_class->attach = attach;
  operation_meta_class->update = update_graph;

  gegl_operation_class_set_keys (operation_class,
    "name",        "lb:extrusion",
    "title",       _("Extrusion for styled text"),
    "reference-hash", "156j6bfzaa5014f2ks3b27ac",
    "description", _("GEGL makes a extrusion effect"
                     ""),
    "gimp:menu-path", "<Image>/Filters/Text Styling",
    "gimp:menu-label", _("Extrusion..."),
    NULL);
}

#endif
