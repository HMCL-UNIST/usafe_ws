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

#ifndef ACADOS_SOLVER_sim_car_H_
#define ACADOS_SOLVER_sim_car_H_

#include "acados_c/ocp_nlp_interface.h"
#include "acados_c/external_function_interface.h"

#define SIM_CAR_NX     7
#define SIM_CAR_NZ     0
#define SIM_CAR_NU     2
#define SIM_CAR_NP     1
#define SIM_CAR_NBX    1
#define SIM_CAR_NBX0   7
#define SIM_CAR_NBU    2
#define SIM_CAR_NSBX   0
#define SIM_CAR_NSBU   2
#define SIM_CAR_NSH    0
#define SIM_CAR_NSG    0
#define SIM_CAR_NSPHI  0
#define SIM_CAR_NSHN   0
#define SIM_CAR_NSGN   0
#define SIM_CAR_NSPHIN 0
#define SIM_CAR_NSBXN  0
#define SIM_CAR_NS     2
#define SIM_CAR_NSN    0
#define SIM_CAR_NG     0
#define SIM_CAR_NBXN   0
#define SIM_CAR_NGN    0
#define SIM_CAR_NY0    9
#define SIM_CAR_NY     9
#define SIM_CAR_NYN    7
#define SIM_CAR_N      40
#define SIM_CAR_NH     0
#define SIM_CAR_NPHI   0
#define SIM_CAR_NHN    0
#define SIM_CAR_NPHIN  0
#define SIM_CAR_NR     0

#ifdef __cplusplus
extern "C" {
#endif

// ** capsule for solver data **
typedef struct sim_car_solver_capsule
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




} sim_car_solver_capsule;

sim_car_solver_capsule * sim_car_acados_create_capsule(void);
int sim_car_acados_free_capsule(sim_car_solver_capsule *capsule);

int sim_car_acados_create(sim_car_solver_capsule * capsule);
/**
 * Generic version of sim_car_acados_create which allows to use a different number of shooting intervals than
 * the number used for code generation. If new_time_steps=NULL and n_time_steps matches the number used for code
 * generation, the time-steps from code generation is used.
 */
int sim_car_acados_create_with_discretization(sim_car_solver_capsule * capsule, int n_time_steps, double* new_time_steps);
/**
 * Update the time step vector. Number N must be identical to the currently set number of shooting nodes in the
 * nlp_solver_plan. Returns 0 if no error occurred and a otherwise a value other than 0.
 */
int sim_car_acados_update_time_steps(sim_car_solver_capsule * capsule, int N, double* new_time_steps);
int sim_car_acados_update_params(sim_car_solver_capsule * capsule, int stage, double *value, int np);
int sim_car_acados_solve(sim_car_solver_capsule * capsule);
int sim_car_acados_free(sim_car_solver_capsule * capsule);
void sim_car_acados_print_stats(sim_car_solver_capsule * capsule);

ocp_nlp_in *sim_car_acados_get_nlp_in(sim_car_solver_capsule * capsule);
ocp_nlp_out *sim_car_acados_get_nlp_out(sim_car_solver_capsule * capsule);
ocp_nlp_solver *sim_car_acados_get_nlp_solver(sim_car_solver_capsule * capsule);
ocp_nlp_config *sim_car_acados_get_nlp_config(sim_car_solver_capsule * capsule);
void *sim_car_acados_get_nlp_opts(sim_car_solver_capsule * capsule);
ocp_nlp_dims *sim_car_acados_get_nlp_dims(sim_car_solver_capsule * capsule);
ocp_nlp_plan *sim_car_acados_get_nlp_plan(sim_car_solver_capsule * capsule);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  // ACADOS_SOLVER_sim_car_H_
