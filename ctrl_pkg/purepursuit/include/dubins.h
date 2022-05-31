/*
 * Copyright (c) 2008-2018, Andrew Walker
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
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef DUBINS_H
#define DUBINS_H
#ifdef WIN32
#define _USE_MATH_DEFINES
#endif
#include <math.h>

#define EPSILON (10e-10)

typedef enum 
{
    L_SEG = 0,
    S_SEG = 1,
    R_SEG = 2
} SegmentType;

/* The segment types for each of the Path types */
const SegmentType DIRDATA[][3] = {
    { L_SEG, S_SEG, L_SEG },
    { L_SEG, S_SEG, R_SEG },
    { R_SEG, S_SEG, L_SEG },
    { R_SEG, S_SEG, R_SEG },
    { R_SEG, L_SEG, R_SEG },
    { L_SEG, R_SEG, L_SEG }
};

typedef struct 
{
    double alpha;
    double beta;
    double d;
    double sa;
    double sb;
    double ca;
    double cb;
    double c_ab;
    double d_sq;
} DubinsIntermediateResults;

typedef enum 
{
    LSL = 0,
    LSR = 1,
    RSL = 2,
    RSR = 3,
    RLR = 4,
    LRL = 5
} DubinsPathType;

typedef struct 
{
    /* the initial configuration */
    double qi[3];        
    /* the lengths of the three segments */
    double param[3];     
    /* model forward velocity / model angular velocity */
    double rho;          
    /* the path type described */
    DubinsPathType type; 
} DubinsPath;

#define EDUBOK        (0)   /* No error */
#define EDUBCOCONFIGS (1)   /* Colocated configurations */
#define EDUBPARAM     (2)   /* Path parameterisitation error */
#define EDUBBADRHO    (3)   /* the rho value is invalid */
#define EDUBNOPATH    (4)   /* no connection between configurations with this word */

/**
 * Callback function for path sampling
 *
 * @note the q parameter is a configuration
 * @note the t parameter is the distance along the path
 * @note the user_data parameter is forwarded from the caller
 * @note return non-zero to denote sampling should be stopped
 */
typedef int (*DubinsPathSamplingCallback)(double q[3], double t, void* user_data);

int dubins_word(DubinsIntermediateResults* in, DubinsPathType pathType, double out[3]);
int dubins_intermediate_results(DubinsIntermediateResults* in, double q0[3], double q1[3], double rho);

double fmodr( double x, double y)
{
    return x - y*floor(x/y);
}

double mod2pi( double theta )
{
    return fmodr( theta, 2 * M_PI );
}
/**
 * Generate a path from an initial configuration to
 * a target configuration, with a specified maximum turning
 * radii
 *
 * A configuration is (x, y, theta), where theta is in radians, with zero
 * along the line x = 0, and counter-clockwise is positive
 *
 * @param path  - the resultant path
 * @param q0    - a configuration specified as an array of x, y, theta
 * @param q1    - a configuration specified as an array of x, y, theta
 * @param rho   - turning radius of the vehicle (forward velocity divided by maximum angular velocity)
 * @return      - non-zero on error
 */
int dubins_shortest_path(DubinsPath* path, double q0[3], double q1[3], double rho)
{
    int i, errcode;
    DubinsIntermediateResults in;
    double params[3];
    double cost;
    double best_cost = INFINITY;
    int best_word = -1;
    errcode = dubins_intermediate_results(&in, q0, q1, rho);
    if(errcode != EDUBOK) {
        return errcode;
    }


    path->qi[0] = q0[0];
    path->qi[1] = q0[1];
    path->qi[2] = q0[2];
    path->rho = rho;
 
    for( i = 0; i < 6; i++ ) {
        DubinsPathType pathType = (DubinsPathType)i;
        errcode = dubins_word(&in, pathType, params);
        if(errcode == EDUBOK) {
            cost = params[0] + params[1] + params[2];
            if(cost < best_cost) {
                best_word = i;
                best_cost = cost;
                path->param[0] = params[0];
                path->param[1] = params[1];
                path->param[2] = params[2];
                path->type = pathType;
            }
        }
    }
    if(best_word == -1) {
        return EDUBNOPATH;
    }
    return EDUBOK;
}
/**
 * Generate a path with a specified word from an initial configuration to
 * a target configuration, with a specified turning radius 
 *
 * @param path     - the resultant path
 * @param q0       - a configuration specified as an array of x, y, theta
 * @param q1       - a configuration specified as an array of x, y, theta
 * @param rho      - turning radius of the vehicle (forward velocity divided by maximum angular velocity)
 * @param pathType - the specific path type to use
 * @return         - non-zero on error
 */
int dubins_path(DubinsPath* path, double q0[3], double q1[3], double rho, DubinsPathType pathType)
{
    int errcode;
    DubinsIntermediateResults in;
    errcode = dubins_intermediate_results(&in, q0, q1, rho);
    if(errcode == EDUBOK) {
        double params[3];
        errcode = dubins_word(&in, pathType, params);
        if(errcode == EDUBOK) {
            path->param[0] = params[0];
            path->param[1] = params[1];
            path->param[2] = params[2];
            path->qi[0] = q0[0];
            path->qi[1] = q0[1];
            path->qi[2] = q0[2];
            path->rho = rho;
            path->type = pathType;
        }
    }
    return errcode;
}
/**
 * Calculate the length of an initialised path
 *
 * @param path - the path to find the length of
 */
double dubins_path_length( DubinsPath* path )
{
    double length = 0.;
    length += path->param[0];
    length += path->param[1];
    length += path->param[2];
    length = length * path->rho;
    return length;
}
/**
 * Return the length of a specific segment in an initialized path
 *
 * @param path - the path to find the length of
 * @param i    - the segment you to get the length of (0-2)
 */
double dubins_segment_length( DubinsPath* path, int i )
{
    if( (i < 0) || (i > 2) )
    {
        return INFINITY;
    }
    return path->param[i] * path->rho;
}
/**
 * Return the normalized length of a specific segment in an initialized path
 *
 * @param path - the path to find the length of
 * @param i    - the segment you to get the length of (0-2)
 */
double dubins_segment_length_normalized( DubinsPath* path, int i )
{
    if( (i < 0) || (i > 2) )
    {
        return INFINITY;
    }
    return path->param[i];
} 
/**
 * Extract an integer that represents which path type was used
 *
 * @param path    - an initialised path
 * @return        - one of LSL, LSR, RSL, RSR, RLR or LRL 
 */
DubinsPathType dubins_path_type( DubinsPath* path ) 
{
    return path->type;
}

void dubins_segment( double t, double qi[3], double qt[3], SegmentType type)
{
    double st = sin(qi[2]);
    double ct = cos(qi[2]);
    if( type == L_SEG ) {
        qt[0] = +sin(qi[2]+t) - st;
        qt[1] = -cos(qi[2]+t) + ct;
        qt[2] = t;
    }
    else if( type == R_SEG ) {
        qt[0] = -sin(qi[2]-t) + st;
        qt[1] = +cos(qi[2]-t) - ct;
        qt[2] = -t;
    }
    else if( type == S_SEG ) {
        qt[0] = ct * t;
        qt[1] = st * t;
        qt[2] = 0.0;
    }
    qt[0] += qi[0];
    qt[1] += qi[1];
    qt[2] += qi[2];
}
/**
 * Calculate the configuration along the path, using the parameter t
 *
 * @param path - an initialised path
 * @param t    - a length measure, where 0 <= t < dubins_path_length(path)
 * @param q    - the configuration result
 * @returns    - non-zero if 't' is not in the correct range
 */
int dubins_path_sample( DubinsPath* path, double t, double q[3] )
{
    /* tprime is the normalised variant of the parameter t */
    double tprime = t / path->rho;
    double qi[3]; /* The translated initial configuration */
    double q1[3]; /* end-of segment 1 */
    double q2[3]; /* end-of segment 2 */
    const SegmentType* types = DIRDATA[path->type];
    double p1, p2;

    if( t < 0 || t > dubins_path_length(path) ) {
        return EDUBPARAM;
    }

    /* initial configuration */
    qi[0] = 0.0;
    qi[1] = 0.0;
    qi[2] = path->qi[2];

    /* generate the target configuration */
    p1 = path->param[0];
    p2 = path->param[1];
    dubins_segment( p1,      qi,    q1, types[0] );
    dubins_segment( p2,      q1,    q2, types[1] );
    if( tprime < p1 ) {
        dubins_segment( tprime, qi, q, types[0] );
    }
    else if( tprime < (p1+p2) ) {
        dubins_segment( tprime-p1, q1, q,  types[1] );
    }
    else {
        dubins_segment( tprime-p1-p2, q2, q,  types[2] );
    }

    /* scale the target configuration, translate back to the original starting point */
    q[0] = q[0] * path->rho + path->qi[0];
    q[1] = q[1] * path->rho + path->qi[1];
    q[2] = mod2pi(q[2]);

    return EDUBOK;
}
/**
 * Walk along the path at a fixed sampling interval, calling the
 * callback function at each interval
 *
 * The sampling process continues until the whole path is sampled, or the callback returns a non-zero value
 *
 * @param path      - the path to sample
 * @param stepSize  - the distance along the path for subsequent samples
 * @param cb        - the callback function to call for each sample
 * @param user_data - optional information to pass on to the callback
 *
 * @returns - zero on successful completion, or the result of the callback
 */
int dubins_path_sample_many(DubinsPath* path, double stepSize, 
                            DubinsPathSamplingCallback cb, void* user_data)
{
    int retcode;
    double q[3];
    double x = 0.0;
    double length = dubins_path_length(path);
    while( x <  length ) {
        dubins_path_sample( path, x, q );
        retcode = cb(q, x, user_data);
        if( retcode != 0 ) {
            return retcode;
        }
        x += stepSize;
    }
    return 0;
}

/**
 * Convenience function to identify the endpoint of a path
 *
 * @param path - an initialised path
 * @param q    - the configuration result
 */
int dubins_path_endpoint( DubinsPath* path, double q[3] )
{
    return dubins_path_sample( path, dubins_path_length(path) - EPSILON, q );
}
/**
 * Convenience function to extract a subset of a path
 *
 * @param path    - an initialised path
 * @param t       - a length measure, where 0 < t < dubins_path_length(path)
 * @param newpath - the resultant path
 */
int dubins_extract_subpath( DubinsPath* path, double t, DubinsPath* newpath )
{
    /* calculate the true parameter */
    double tprime = t / path->rho;

    if((t < 0) || (t > dubins_path_length(path)))
    {
        return EDUBPARAM; 
    }

    /* copy most of the data */
    newpath->qi[0] = path->qi[0];
    newpath->qi[1] = path->qi[1];
    newpath->qi[2] = path->qi[2];
    newpath->rho   = path->rho;
    newpath->type  = path->type;

    /* fix the parameters */
    newpath->param[0] = fmin( path->param[0], tprime );
    newpath->param[1] = fmin( path->param[1], tprime - newpath->param[0]);
    newpath->param[2] = fmin( path->param[2], tprime - newpath->param[0] - newpath->param[1]);
    return 0;
}

int dubins_intermediate_results(DubinsIntermediateResults* in, double q0[3], double q1[3], double rho)
{
    double dx, dy, D, d, theta, alpha, beta;
    if( rho <= 0.0 ) {
        return EDUBBADRHO;
    }

    dx = q1[0] - q0[0];
    dy = q1[1] - q0[1];
    D = sqrt( dx * dx + dy * dy );
    d = D / rho;
    theta = 0;

    /* test required to prevent domain errors if dx=0 and dy=0 */
    if(d > 0) {
        theta = mod2pi(atan2( dy, dx ));
    }
    alpha = mod2pi(q0[2] - theta);
    beta  = mod2pi(q1[2] - theta);

    in->alpha = alpha;
    in->beta  = beta;
    in->d     = d;
    in->sa    = sin(alpha);
    in->sb    = sin(beta);
    in->ca    = cos(alpha);
    in->cb    = cos(beta);
    in->c_ab  = cos(alpha - beta);
    in->d_sq  = d * d;

    return EDUBOK;
}

int dubins_LSL(DubinsIntermediateResults* in, double out[3]) 
{
    double tmp0, tmp1, p_sq;
    
    tmp0 = in->d + in->sa - in->sb;
    p_sq = 2 + in->d_sq - (2*in->c_ab) + (2 * in->d * (in->sa - in->sb));

    if(p_sq >= 0) {
        tmp1 = atan2( (in->cb - in->ca), tmp0 );
        out[0] = mod2pi(tmp1 - in->alpha);
        out[1] = sqrt(p_sq);
        out[2] = mod2pi(in->beta - tmp1);
        return EDUBOK;
    }
    return EDUBNOPATH;
}


int dubins_RSR(DubinsIntermediateResults* in, double out[3]) 
{
    double tmp0 = in->d - in->sa + in->sb;
    double p_sq = 2 + in->d_sq - (2 * in->c_ab) + (2 * in->d * (in->sb - in->sa));
    if( p_sq >= 0 ) {
        double tmp1 = atan2( (in->ca - in->cb), tmp0 );
        out[0] = mod2pi(in->alpha - tmp1);
        out[1] = sqrt(p_sq);
        out[2] = mod2pi(tmp1 -in->beta);
        return EDUBOK;
    }
    return EDUBNOPATH;
}

int dubins_LSR(DubinsIntermediateResults* in, double out[3]) 
{
    double p_sq = -2 + (in->d_sq) + (2 * in->c_ab) + (2 * in->d * (in->sa + in->sb));
    if( p_sq >= 0 ) {
        double p    = sqrt(p_sq);
        double tmp0 = atan2( (-in->ca - in->cb), (in->d + in->sa + in->sb) ) - atan2(-2.0, p);
        out[0] = mod2pi(tmp0 - in->alpha);
        out[1] = p;
        out[2] = mod2pi(tmp0 - mod2pi(in->beta));
        return EDUBOK;
    }
    return EDUBNOPATH;
}

int dubins_RSL(DubinsIntermediateResults* in, double out[3]) 
{
    double p_sq = -2 + in->d_sq + (2 * in->c_ab) - (2 * in->d * (in->sa + in->sb));
    if( p_sq >= 0 ) {
        double p    = sqrt(p_sq);
        double tmp0 = atan2( (in->ca + in->cb), (in->d - in->sa - in->sb) ) - atan2(2.0, p);
        out[0] = mod2pi(in->alpha - tmp0);
        out[1] = p;
        out[2] = mod2pi(in->beta - tmp0);
        return EDUBOK;
    }
    return EDUBNOPATH;
}

int dubins_RLR(DubinsIntermediateResults* in, double out[3]) 
{
    double tmp0 = (6. - in->d_sq + 2*in->c_ab + 2*in->d*(in->sa - in->sb)) / 8.;
    double phi  = atan2( in->ca - in->cb, in->d - in->sa + in->sb );
    if( fabs(tmp0) <= 1) {
        double p = mod2pi((2*M_PI) - acos(tmp0) );
        double t = mod2pi(in->alpha - phi + mod2pi(p/2.));
        out[0] = t;
        out[1] = p;
        out[2] = mod2pi(in->alpha - in->beta - t + mod2pi(p));
        return EDUBOK;
    }
    return EDUBNOPATH;
}

int dubins_LRL(DubinsIntermediateResults* in, double out[3])
{
    double tmp0 = (6. - in->d_sq + 2*in->c_ab + 2*in->d*(in->sb - in->sa)) / 8.;
    double phi = atan2( in->ca - in->cb, in->d + in->sa - in->sb );
    if( fabs(tmp0) <= 1) {
        double p = mod2pi( 2*M_PI - acos( tmp0) );
        double t = mod2pi(-in->alpha - phi + p/2.);
        out[0] = t;
        out[1] = p;
        out[2] = mod2pi(mod2pi(in->beta) - in->alpha -t + mod2pi(p));
        return EDUBOK;
    }
    return EDUBNOPATH;
}

int dubins_word(DubinsIntermediateResults* in, DubinsPathType pathType, double out[3]) 
{
    int result;
    switch(pathType)
    {
    case LSL:
        result = dubins_LSL(in, out);
        break;
    case RSL:
        result = dubins_RSL(in, out);
        break;
    case LSR:
        result = dubins_LSR(in, out);
        break;
    case RSR:
        result = dubins_RSR(in, out);
        break;
    case LRL:
        result = dubins_LRL(in, out);
        break;
    case RLR:
        result = dubins_RLR(in, out);
        break;
    default:
        result = EDUBNOPATH;
    }
    return result;
}
#endif /* DUBINS_H */

