/*
Holds cCrowdRender2D and cCrowdAnim2D

0x801b1ee0 cCrowdAnim2D::update(void)
0x801b2124 cCrowdAnim2D::advanceFrame(int, int, eAnimPlayType &)
0x801b21dc cCrowdAnim2D::cCrowdAnim2D(cCrowdRender2D *)
0x801b2238 cCrowdRender2D::constructCrowdAnim2D(void)
0x801b2290 cCrowdRender2D::purge(void)
0x801b2318 cCrowdRender2D::init(void)
0x801b23e4 cCrowdRender2D::~cCrowdRender2D(void)
0x801b2434 cCrowdRender2D::cCrowdRender2D(void)
ends 0x801b2464
*/

#include "crowdrender2d.h"


//void cCrowdRender2D_scoperes_init(void* param_1){
//    return;
//}

int cCrowdRender2D_scoperes__tilde__cCrowdRender2D(int param_1, short param_2){
  if (param_1 != 0) {
    cCrowdRender2D_scoperes_purge();//fn_801B2290(); // purge()
    if (0 < param_2) {
      operator_space_delete(param_1);
    }
  }
  return param_1;
}


void* cCrowdRender2D_scoperes_cCrowdRender2D(void* this){
    cCrowdRender2D_scoperes_init(this);
    return this;
}
