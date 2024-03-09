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
 * 2023 Beaver, Ringed Text
You can test plugin without installing by pasting this syntax into Gimp's GEGL graph (This graph requires another plugin 'ssg' ' this filter ships with it plugins)

id=contain
src aux=[ ref=contain
id=1
dst-out aux=[ ref=1

median-blur radius=5 alpha-percentile=0
lb:ssg radius=0 stroke=6
lb:ssg radius=0 stroke=6
lb:ssg radius=0 stroke=6
lb:ssg radius=0 stroke=6
lb:ssg radius=0 stroke=6
lb:ssg radius=0 stroke=6
]
crop

--end of syntax--

Fun fact about this plugin

It's literally ringed bevel without the bevel and more rings; as the bevel looks bad with many rings.

This is may be my 60th public GEGL plugin 
 */


#include "config.h"
#include <glib/gi18n-lib.h>

#ifdef GEGL_PROPERTIES


enum_start (ring_text)
  enum_value (onering,      "onering",
              N_("One Ring (half structure)"))
  enum_value (tworings,      "tworings",
              N_("Two Rings (one structure)"))
  enum_value (threerings,      "threerings",
              N_("Three Rings (one and a half structures)"))
  enum_value (fourrings,      "fourrings",
              N_("Four Rings (two structures)"))
  enum_value (fiverings,      "fiverings",
              N_("Five Rings (two and a half structures)"))
  enum_value (sixrings,      "sixrings",
              N_("Six Rings (three structures)"))
  enum_value (absurd,      "sixrings",
              N_("Non editable - 16 Rings (8 structures)"))
enum_end (ringtext)
/* This ENUM list has a unique name to avoid conflicts with other plugins or Gimp filters*/

property_enum (rings, _("Amount of rings:"),
    ringtext, ring_text,
    fourrings)
   description  (_("Choose the amount of rings 1-6"))


property_int  (textsize, _("Size of the text"), 3)
  value_range (1, 9)
  ui_range    (1, 9)
  ui_meta     ("unit", "pixel-distance")
  description (_("Median radius to control the size of the text"))


property_int  (ringsize, _("Ring size"), 5)
  value_range (1, 9)
  ui_range    (1, 9)
  ui_meta     ("unit", "pixel-distance")
  description (_("Control the size of the rings. This also creates gaps when bottom bevel's opacity is low. "))

enum_start (shape_of_ringtext)
  enum_value (GEGL_MEDIAN_BLUR_NEIGHBORHOOD_SQUARE,  "square",  N_("Square"))
  enum_value (GEGL_MEDIAN_BLUR_NEIGHBORHOOD_CIRCLE,  "circle",  N_("Circle"))
  enum_value (GEGL_MEDIAN_BLUR_NEIGHBORHOOD_DIAMOND, "diamond", N_("Diamond"))
enum_end (shapeofringtext)

property_enum (ringshape, _("Shape of ring"),
    shapeofringtext, shape_of_ringtext,
               GEGL_MEDIAN_BLUR_NEIGHBORHOOD_CIRCLE)
  description (_("Shape of the Rings that internally uses Median Blur's neighborhood setting (square, circle, diamond). This does not apply to 16 rings mode."))


property_string (syntax, _(""), ANYTHINGGOESHERE)
    ui_meta ("multiline", "true")
  description (_("This plugin provides GEGL syntax to insert in this box. Syntax can do crazy things like make the rings gold. But the syntax needs my other plugins that do NOT ship with this. On the download page of this plugin their will be links to the download of other unrelated plugins Gold Text, Custom Bevel, Glossy Balloon ect... They are not needed for this plugin to work, but are needed to take advantage of the syntax I wrote to make the ringed bevel gold, balloon-esque or whatever. You are also free to write your own syntax to effect the ring text. Literally anything can go here."))

#define ANYTHINGGOESHERE \
"#GEGL Syntax goes here"
/* End of GEGL Graph */

#else

#define GEGL_OP_META
#define GEGL_OP_NAME     ringtext
#define GEGL_OP_C_SOURCE ringtext.c

#include "gegl-op.h"

typedef struct
{
 GeglNode *input;
 GeglNode *erase; 
 GeglNode *s1;
 GeglNode *s2;
 GeglNode *s3;
 GeglNode *s4;
 GeglNode *s5;
 GeglNode *s6;
 GeglNode *crazy;                
 GeglNode *median;
 GeglNode *mediandictator;
 GeglNode *idref; 
 GeglNode *fix;  
 GeglNode *syntax;  
 GeglNode *output;
}State;


static void attach (GeglOperation *operation)
{
  GeglNode *gegl = operation->node;
  GeglProperties *o = GEGL_PROPERTIES (operation);

  State *state = o->user_data = g_malloc0 (sizeof (State));


  state->input    = gegl_node_get_input_proxy (gegl, "input");
  state->output   = gegl_node_get_output_proxy (gegl, "output");

  state->syntax = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", 
                                  NULL);

  state->mediandictator = gegl_node_new_child (gegl,
                                  "operation", "gegl:median-blur", "alpha-percentile", 100.0,  
                                  NULL);

  state->erase = gegl_node_new_child (gegl,
                                  "operation", "gegl:dst-out", 
                                  NULL);

  state->idref = gegl_node_new_child (gegl,
                                  "operation", "gegl:nop", 
                                  NULL);
#define sixteenrings \
" id=contain src aux=[ ref=contain  id=1 dst-out aux=[ ref=1 median-blur radius=5 alpha-percentile=0 lb:ssg radius=0 stroke=2 lb:ssg radius=0 stroke=2 lb:ssg radius=0 stroke=2 lb:ssg radius=0 stroke=2 lb:ssg radius=0 stroke=2 lb:ssg radius=0 stroke=2 lb:ssg radius=0 stroke=2 lb:ssg radius=0 stroke=2 lb:ssg radius=0 stroke=2 lb:ssg radius=0 stroke=2 lb:ssg radius=0 stroke=2 lb:ssg radius=0 stroke=2 lb:ssg radius=0 stroke=2 lb:ssg radius=0 stroke=2 lb:ssg radius=0 stroke=2 lb:ssg radius=0 stroke=2 ] crop   "\


  state->crazy = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", sixteenrings, 
                                  NULL);

  state->fix = gegl_node_new_child (gegl,
                                  "operation", "gegl:median-blur", "radius", 0, 
                                  NULL);

  state->s1 = gegl_node_new_child (gegl,
                                  "operation", "lb:ssg", "radius", 0, "stroke", 7.0,  
                                  NULL);

  state->s2 = gegl_node_new_child (gegl,
                                  "operation", "lb:ssg", "radius", 0, "stroke", 7.0,  
                                  NULL);

  state->s3 = gegl_node_new_child (gegl,
                                  "operation", "lb:ssg", "radius", 0, "stroke", 7.0,  
                                  NULL);

  state->s4 = gegl_node_new_child (gegl,
                                  "operation", "lb:ssg", "radius", 0, "stroke", 7.0,  
                                  NULL);

  state->s5 = gegl_node_new_child (gegl,
                                  "operation", "lb:ssg", "radius", 0, "stroke", 7.0,  
                                  NULL);

  state->s6 = gegl_node_new_child (gegl,
                                  "operation", "lb:ssg", "radius", 0, "stroke", 7.0,  
                                  NULL);

  state->median = gegl_node_new_child (gegl,
                                  "operation", "gegl:median-blur", "radius", 5, "alpha-percentile", 0.0,  
                                  NULL);


/*This is a median blur's radius being called to make the text larger*/
    gegl_operation_meta_redirect (operation, "textsize", state->mediandictator, "radius");

/*This controls the size of ALL ssg nodes except the absurd 16 ring graph*/
    gegl_operation_meta_redirect (operation, "ringsize", state->s1, "stroke");
    gegl_operation_meta_redirect (operation, "ringsize", state->s2, "stroke");
    gegl_operation_meta_redirect (operation, "ringsize", state->s3, "stroke");
    gegl_operation_meta_redirect (operation, "ringsize", state->s4, "stroke");
    gegl_operation_meta_redirect (operation, "ringsize", state->s5, "stroke");
    gegl_operation_meta_redirect (operation, "ringsize", state->s6, "stroke");

/*This controls the shape of the rings; outside of the 16 ring graph. It is lb:ssg grow-shape=square,circle,diamond*/
    gegl_operation_meta_redirect (operation, "ringshape", state->s1, "grow-shape");
    gegl_operation_meta_redirect (operation, "ringshape", state->s2, "grow-shape");
    gegl_operation_meta_redirect (operation, "ringshape", state->s3, "grow-shape");
    gegl_operation_meta_redirect (operation, "ringshape", state->s4, "grow-shape");
    gegl_operation_meta_redirect (operation, "ringshape", state->s5, "grow-shape");
    gegl_operation_meta_redirect (operation, "ringshape", state->s6, "grow-shape");

/*This is where uses can inser GEGL syntax of whatever. Such as custom syntax to make a gold ring text*/
    gegl_operation_meta_redirect (operation, "syntax", state->syntax, "string");

} 

static void update_graph (GeglOperation *operation)
{
  GeglProperties *o = GEGL_PROPERTIES (operation);
  State *state = o->user_data;
  if (!state) return;

switch (o->rings) {
        break;
    case onering:
  gegl_node_link_many (state->input, state->mediandictator,  state->idref, state->erase, state->syntax, state->output, NULL);
  gegl_node_link_many (state->idref, state->median, state->s1, state->fix, NULL);
  gegl_node_connect (state->erase, "aux", state->fix, "output");
        break;
    case tworings:
  gegl_node_link_many (state->input, state->mediandictator,   state->idref, state->erase, state->syntax,  state->output, NULL);
  gegl_node_link_many (state->idref, state->median, state->s1, state->s2, state->fix, NULL);
  gegl_node_connect (state->erase, "aux", state->fix, "output");
        break;
    case threerings:
  gegl_node_link_many (state->input, state->mediandictator,  state->idref, state->erase, state->syntax,  state->output, NULL);
  gegl_node_link_many (state->idref, state->median, state->s1, state->s2, state->s3,   state->fix, NULL);
  gegl_node_connect (state->erase, "aux", state->fix, "output");
        break;
    case fourrings:
  gegl_node_link_many (state->input, state->mediandictator, state->idref, state->erase, state->syntax, state->output, NULL);
  gegl_node_link_many (state->idref, state->median, state->s1, state->s2, state->s3, state->s4, state->fix, NULL);
  gegl_node_connect (state->erase, "aux", state->fix, "output");
        break;
    case fiverings:
  gegl_node_link_many (state->input, state->mediandictator, state->idref, state->erase, state->syntax, state->output, NULL);
  gegl_node_link_many (state->idref, state->median, state->s1, state->s2, state->s3, state->s4, state->s5, state->fix, NULL);
  gegl_node_connect (state->erase, "aux", state->fix, "output");
        break;
    case sixrings:
  gegl_node_link_many (state->input, state->mediandictator, state->idref, state->erase, state->syntax,  state->output, NULL);
  gegl_node_link_many (state->idref, state->median, state->s1, state->s2, state->s3, state->s4, state->s5, state->s6, state->fix,  NULL);
  gegl_node_connect (state->erase, "aux", state->fix, "output");
        break;
    case absurd:
  gegl_node_link_many (state->input, state->mediandictator, state->crazy, state->fix, state->syntax, state->output, NULL);
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
    "name",        "lb:ring",
    "title",       _("Ring Text"),
    "reference-hash", "60d0h30afejkjimmyneutronoperationrescuejetfusion60",
    "description", _("Make Ringed Text"),
    "gimp:menu-path", "<Image>/Filters/Text Styling",
    "gimp:menu-label", _("Ringed Text..."),
    NULL);
}

#endif
