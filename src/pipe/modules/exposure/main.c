#include "modules/api.h"
#include <math.h>
#include <stdlib.h>

void commit_params(dt_graph_t *graph, dt_node_t *node)
{
  float *f = (float *)node->module->committed_param;
  if(node->module->img_param.whitebalance[0] > 0)
  {
    for(int k=0;k<4;k++)
      f[k] = powf(2.0f, ((float*)node->module->param)[0]) *
        node->module->img_param.whitebalance[k];
  }
  else
    for(int k=0;k<4;k++)
      f[k] = powf(2.0f, ((float*)node->module->param)[0]);
  for(int k=0;k<12;k++) f[4+k] = 0.0f;
  if(node->module->img_param.cam_to_rec2020[0] > 0.0f)
  { // camera to rec2020 matrix
    // mat3 in glsl is an array of 3 vec4 column vectors:
    for(int j=0;j<3;j++) for(int i=0;i<3;i++)
      f[4+4*j+i] = node->module->img_param.cam_to_rec2020[3*j+i];
  }
  else
  { // identity
    f[4+0] = f[4+5] = f[4+10] = 1.0f;
  }
}

int init(dt_module_t *mod)
{
  mod->committed_param_size = sizeof(float)*16;
  return 0;
}
