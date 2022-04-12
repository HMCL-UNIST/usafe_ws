/*
 * Copyright 2019 Gianluca Frison, Dimitris Kouzoupis, Robin Verschueren,
 * Andrea Zanelli, Niels van Duijkeren, Jonathan Frey, Tommaso Sartor,
 * Branimir Novoselnik, Rien Quirynen, Rezart Qelibari, Dang Doan,
 * Jonas Koenemann, Yutao Chen, Tobias Schöls, Jonas Schlagenhauf, Moritz Diehl
 *
 * This file is part of acados.
 *
 * The 2-Clause BSD License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.;
 */

#ifndef ACADOS_SOLVER_Spatialbicycle_model_H_
#define ACADOS_SOLVER_Spatialbicycle_model_H_

#include "acados_c/ocp_nlp_interface.h"
#include "acados_c/external_function_interface.h"

#define SPATIALBICYCLE_MODEL_NX     6
#define SPATIALBICYCLE_MODEL_NZ     0
#define SPATIALBICYCLE_MODEL_NU     2
#define SPATIALBICYCLE_MODEL_NP     0
#define SPATIALBICYCLE_MODEL_NBX    1
#define SPATIALBICYCLE_MODEL_NBX0   6
#define SPATIALBICYCLE_MODEL_NBU    2
#define SPATIALBICYCLE_MODEL_NSBX   1
#define SPATIALBICYCLE_MODEL_NSBU   0
#define SPATIALBICYCLE_MODEL_NSH    5
#define SPATIALBICYCLE_MODEL_NSG    0
#define SPATIALBICYCLE_MODEL_NSPHI  0
#define SPATIALBICYCLE_MODEL_NSHN   0
#define SPATIALBICYCLE_MODEL_NSGN   0
#define SPATIALBICYCLE_MODEL_NSPHIN 0
#define SPATIALBICYCLE_MODEL_NSBXN  0
#define SPATIALBICYCLE_MODEL_NS     6
#define SPATIALBICYCLE_MODEL_NSN    0
#define SPATIALBICYCLE_MODEL_NG     0
#define SPATIALBICYCLE_MODEL_NBXN   0
#define SPATIALBICYCLE_MODEL_NGN    0
#define SPATIALBICYCLE_MODEL_NY0    8
#define SPATIALBICYCLE_MODEL_NY     8
#define SPATIALBICYCLE_MODEL_NYN    6
#define SPATIALBICYCLE_MODEL_N      50
#define SPATIALBICYCLE_MODEL_NH     5
#define SPATIALBICYCLE_MODEL_NPHI   0
#define SPATIALBICYCLE_MODEL_NHN    0
#define SPATIALBICYCLE_MODEL_NPHIN  0
#define SPATIALBICYCLE_MODEL_NR     0

#ifdef __cplusplus
extern "C" {
#endif

// ** capsule for solver data **
typedef struct Spatialbicycle_model_solver_capsule
{
    // acados objects
    ocp_nlp_in *nlp_in;
    ocp_nlp_out *nlp_out;
    ocp_nlp_out *sens_out;
    ocp_nlp_solver *nlp_solver;
    void *nlp_opts;
    ocp_nlp_plan *nlp_solver_plan;
    ocp_nlp_config *nlp_config;
    ocp_nlp_dims *nlp_dims;

    // number of expected runtime parameters
    unsigned int nlp_np;

    /* external functions */
    // dynamics

    external_function_param_casadi *forw_vde_casadi;
    external_function_param_casadi *expl_ode_fun;




    // cost






    // constraints
    external_function_param_casadi *nl_constr_h_fun_jac;
    external_function_param_casadi *nl_constr_h_fun;
    external_function_param_casadi *nl_constr_h_fun_jac_hess;




} Spatialbicycle_model_solver_capsule;

Spatialbicycle_model_solver_capsule * Spatialbicycle_model_acados_create_capsule(void);
int Spatialbicycle_model_acados_free_capsule(Spatialbicycle_model_solver_capsule *capsule);

int Spatialbicycle_model_acados_create(Spatialbicycle_model_solver_capsule * capsule);
/**
 * Generic version of Spatialbicycle_model_acados_create which allows to use a different number of shooting intervals than
 * the number used for code generation. If new_time_steps=NULL and n_time_steps matches the number used for code
 * generation, the time-steps from code generation is used.
 */
int Spatialbicycle_model_acados_create_with_discretization(Spatialbicycle_model_solver_capsule * capsule, int n_time_steps, double* new_time_steps);
/**
 * Update the time step vector. Number N must be identical to the currently set number of shooting nodes in the
 * nlp_solver_plan. Returns 0 if no error occurred and a otherwise a value other than 0.
 */
int Spatialbicycle_model_acados_update_time_steps(Spatialbicycle_model_solver_capsule * capsule, int N, double* new_time_steps);
int Spatialbicycle_model_acados_update_params(Spatialbicycle_model_solver_capsule * capsule, int stage, double *value, int np);
int Spatialbicycle_model_acados_solve(Spatialbicycle_model_solver_capsule * capsule);
int Spatialbicycle_model_acados_free(Spatialbicycle_model_solver_capsule * capsule);
void Spatialbicycle_model_acados_print_stats(Spatialbicycle_model_solver_capsule * capsule);

ocp_nlp_in *Spatialbicycle_model_acados_get_nlp_in(Spatialbicycle_model_solver_capsule * capsule);
ocp_nlp_out *Spatialbicycle_model_acados_get_nlp_out(Spatialbicycle_model_solver_capsule * capsule);
ocp_nlp_solver *Spatialbicycle_model_acados_get_nlp_solver(Spatialbicycle_model_solver_capsule * capsule);
ocp_nlp_config *Spatialbicycle_model_acados_get_nlp_config(Spatialbicycle_model_solver_capsule * capsule);
void *Spatialbicycle_model_acados_get_nlp_opts(Spatialbicycle_model_solver_capsule * capsule);
ocp_nlp_dims *Spatialbicycle_model_acados_get_nlp_dims(Spatialbicycle_model_solver_capsule * capsule);
ocp_nlp_plan *Spatialbicycle_model_acados_get_nlp_plan(Spatialbicycle_model_solver_capsule * capsule);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  // ACADOS_SOLVER_Spatialbicycle_model_H_
