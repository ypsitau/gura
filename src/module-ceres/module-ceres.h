//=============================================================================
// Gura module: ceres
//=============================================================================
#ifndef __GURA_MODULE_CERES_H__
#define __GURA_MODULE_CERES_H__
#include <gura.h>
#include <ceres/ceres.h>
#include <glog/logging.h>
#include "Class_CostFunction.h"
#include "Class_AutoDiffCostFunction.h"
#include "Class_LossFunction.h"
#include "Class_Problem.h"
#include "Class_Solver_Options.h"
#include "Class_Solver_Summary.h"

Gura_BeginModuleHeader(ceres)

Gura_DeclareUserSymbol(Evaluate);

Gura_EndModuleHeader(ceres)

#endif
