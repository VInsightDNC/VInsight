/*
 * Copyright 2007-2013 National ICT Australia (NICTA), Australia
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
/*!\file average_filter.c
  \brief Implements a filter which calculates the average over all
  the samples it received over the sample period.
*/

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "oml2/omlc.h"
#include "oml2/oml_filter.h"
#include "ocomm/o_log.h"
#include "oml_value.h"
#include "average_filter.h"

#define FILTER_NAME  "avg"

typedef struct _omlAvgFilterInstanceData InstanceData;

static int
process(OmlFilter* filter, OmlWriter* writer);

static int
sample(OmlFilter* f, OmlValue* value);

void*
omlf_average_new(OmlValueT type, OmlValue* result)
{
  if (! omlc_is_numeric_type (type)) {
    logerror ("%s filter: Can only handle numeric parameters\n", FILTER_NAME);
    return NULL;
  }

  InstanceData* self = (InstanceData *)xmalloc(sizeof(InstanceData));

  if (self) {
    memset(self, 0, sizeof(InstanceData));

    self->sample_sum = 0.;
    self->sample_count = 0;
    self->sample_min = HUGE;
    self->sample_max = -1 * HUGE;
    self->result = result;
    return self;
  } else {
    logerror ("%s filter: Could not allocate %d bytes for instance data\n",
        FILTER_NAME,
        sizeof(InstanceData));
    return NULL;
  }
}

void
omlf_register_filter_average (void)
{
  OmlFilterDef def [] =
    {
      { "avg", OML_DOUBLE_VALUE },
      { "min", OML_DOUBLE_VALUE },
      { "max", OML_DOUBLE_VALUE },
      { NULL, 0 }
    };

  omlf_register_filter (FILTER_NAME,
                        omlf_average_new,
                        NULL,
                        sample,
                        process,
                        NULL,
                        def);
}

static int
sample(OmlFilter* f, OmlValue* value)
{
  InstanceData* self = (InstanceData*)f->instance_data;
  double val;

  if (! omlc_is_numeric (*value))
    return -1;

  val = oml_value_to_double (value);

  self->sample_sum += val;
  if (val < self->sample_min) self->sample_min = val;
  if (val > self->sample_max) self->sample_max = val;
  self->sample_count++;

  return 0;
}

static int
process(OmlFilter* f, OmlWriter* writer)
{
  InstanceData* self = (InstanceData*)f->instance_data;

  if (self->sample_count <= 0)
    return 1;

  omlc_set_double(*oml_value_get_value(&self->result[0]), 1.0 * self->sample_sum / self->sample_count);
  omlc_set_double(*oml_value_get_value(&self->result[1]), self->sample_min);
  omlc_set_double(*oml_value_get_value(&self->result[2]), self->sample_max);

  writer->out(writer, self->result, f->output_count);

  self->sample_max = -1 * HUGE;
  self->sample_min = HUGE;
  self->sample_sum = 0;
  self->sample_count = 0.;

  return 0;
}


/*
 Local Variables:
 mode: C
 tab-width: 2
 indent-tabs-mode: nil
 End:
 vim: sw=2:sts=2:expandtab
*/
