/*
 * Copyright 2008-2015 Aerospike, Inc.
 *
 * Portions may be licensed to Aerospike, Inc. under one or more contributor
 * license agreements.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */
#include <aerospike/as_async.h>

/******************************************************************************
 * FUNCTIONS
 *****************************************************************************/

uint32_t
as_async_get_pending(as_cluster* cluster)
{
	as_nodes* nodes = as_nodes_reserve(cluster);
	uint32_t pending = 0;

	for (uint32_t i = 0; i < nodes->size; ++i) {
		pending += ck_pr_load_32(&nodes->array[i]->async_pending);
	}

	as_nodes_release(nodes);
	return pending;
}

uint32_t
as_async_get_connections(as_cluster* cluster)
{
	as_nodes* nodes = as_nodes_reserve(cluster);
	uint32_t count = 0;

	for (uint32_t i = 0; i < nodes->size; ++i) {
		count += ck_pr_load_32(&nodes->array[i]->async_conn);
	}

	as_nodes_release(nodes);
	return count;
}
