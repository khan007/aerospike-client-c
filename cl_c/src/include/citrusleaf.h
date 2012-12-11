/******************************************************************************
 * Copyright 2008-2012 by Aerospike.  All rights reserved.
 * THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE.  THE COPYRIGHT NOTICE
 * ABOVE DOES NOT EVIDENCE ANY ACTUAL OR INTENDED PUBLICATION.
 ******************************************************************************/

#pragma once

#include "types.h"
#include "async.h"
#include "cluster.h"
#include "info.h"
#include "kv.h"
#include "lookup.h"
#include "mapreduce.h"
#include "object.h"
#include "partition.h"
// #include "query.h"
// #include "scan.h"
// #include "sindex.h"
// #include "sproc.h"

//
// All citrusleaf functions return an integer. This integer is 0 if the
// call has succeeded, and a negative number if it has failed.
// All returns of pointers and objects are done through the parameters.
// (When in C++, use & parameters for return, but we're not there yet)
//
// 'void' return functions are only used for functions that are syntactically
// unable to fail.
//
//
// Call this init function sometime early, create our mutexes and a few other things.
// We'd prefer if this is only called once
//

int citrusleaf_init(void);

void citrusleaf_change_tend_speed(int secs);


/**
 * If you wish to free up resources used by the citrusleaf client in your process,
 * call this - all cl_conn will be invalid, and you'll have to call citrusleaf_init
 * again to do anything
 */
void citrusleaf_shutdown(void);

void citrusleaf_set_debug(bool debug_flag);

/**
 * This call will print stats to stderr
 */
void citrusleaf_print_stats(void);

/**
 * This call is good for testing. Call it when you think you know the values. If the key doesn't exist, or
 * the data is incorrect, then the server that is serving the request will spit a failure, and if you're
 * running in the right server debug mode you can examine the error in detail.
 */
cl_rv citrusleaf_verify(cl_cluster *asc, const char *ns, const char *set, const cl_object *key, const cl_bin *bins, int n_bins, int timeout_ms, uint32_t *cl_gen);
cl_rv citrusleaf_delete_verify(cl_cluster *asc, const char *ns, const char *set, const cl_object *key, const cl_write_parameters *cl_w_p);

/**
 * This call allows the caller to specify the operation - read, write, add, etc.  Multiple operations
 * can be specified in a single call.
 */

cl_rv citrusleaf_operate(cl_cluster *asc, const char *ns, const char *set, const cl_object *key, cl_operation *operations, int n_operations, const cl_write_parameters *cl_w_p, int replace, uint32_t *generation);
cl_rv citrusleaf_operate_digest(cl_cluster *asc, const char *ns, cf_digest *d, cl_operation *operations, int n_operations, const cl_write_parameters *cl_w_p, int replace, uint32_t *generation);

/**
 * This debugging call can be useful for tracking down errors and coordinating with server failures
 * gets the digest for a particular set and key
 */
int citrusleaf_calculate_digest(const char *set, const cl_object *key, cf_digest *digest);
