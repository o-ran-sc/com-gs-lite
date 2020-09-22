/** ------------------------------------------------
Copyright 2014 AT&T Intellectual Property
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 ------------------------------------------- */

#ifndef GROUPBY_OPERATOR_H
#define GROUPBY_OPERATOR_H

#include "host_tuple.h"
#include "base_operator.h"
#include <list>
#include "hash_table.h"


using namespace std;

template <class groupby_func, class group, class aggregate, class hasher_func, class equal_func>
class groupby_operator : public base_operator {
private :
	groupby_func func;
	hash_table<group, aggregate, hasher_func, equal_func> group_table;
	bool flush_finished;
	typename hash_table<group, aggregate, hasher_func, equal_func>::iterator flush_pos;
	int n_patterns;
public:
	groupby_operator(int schema_handle, const char* name) : base_operator(name), func(schema_handle) {
		flush_finished = true;
		n_patterns = func.n_groupby_patterns();
	}

	int accept_tuple(host_tuple& tup, list<host_tuple>& result) {

//			Push out completed groups

		// extract the key information from the tuple and
		// copy it into buffer
		group grp;
		if (!func.create_group(tup, (gs_sp_t)&grp)) {
			if(func.disordered()){
				fprintf(stderr,"Out of order record in %s\n",op_name);
				return 0;
			}
			if (func.flush_needed()){
				flush_old(result);
			}
			if (func.temp_status_received()) {
				host_tuple temp_tup;
				if (!func.create_temp_status_tuple(temp_tup, flush_finished)) {
					temp_tup.channel = output_channel;
					result.push_back(temp_tup);
				}
			}
			tup.free_tuple();
			return 0;
		}
		if(func.disordered()){
			fprintf(stderr,"Out of order record in %s\n",op_name);
			return 0;
		}

		typename hash_table<group, aggregate, hasher_func, equal_func>::iterator iter;
		if ((iter = group_table.find(grp)) != group_table.end()) {
//				Temporal GBvar is part of the group so no flush is needed.
			func.update_aggregate(tup, grp, (*iter).second);
		}else{
			if (func.flush_needed()) {
				flush_old(result);
			}
			if(n_patterns <= 1){
				char aggr_buffer[sizeof(aggregate)];
				// create an aggregate in preallocated buffer
				func.create_aggregate(tup, aggr_buffer);
				// neeed operator= doing a deep copy
				group_table.insert(grp, (*(aggregate*)aggr_buffer));
			}else{
				int p;
// TODO this code is wrong, must check if each pattern is in the group table.
				for(p=0;p<n_patterns;++p){
					// need shallow copy constructor for groups
					group new_grp(grp, func.get_pattern(p));
					char aggr_buffer[sizeof(aggregate)];
					func.create_aggregate(tup, aggr_buffer);
					// neeed operator= doing a deep copy
					group_table.insert(new_grp, (*(aggregate*)aggr_buffer));
				}
			}
		}
		tup.free_tuple();
		return 0;
	}


	int flush(list<host_tuple>& result) {
		host_tuple tup;

		flush_pos = group_table.begin();
//			If the table isn't empty, flush it now.
		if (!group_table.empty()) {
			for (; flush_pos != group_table.end(); ++flush_pos) {
				bool failed = false;
				tup = func.create_output_tuple((*flush_pos).first,(*flush_pos).second, failed);
				if (!failed) {

					tup.channel = output_channel;
					result.push_back(tup);
				}
//				free((*flush_pos).second);
			}
			group_table.clear();
		}

		flush_finished = true;

		return 0;
	}

	int flush_old(list<host_tuple>& result) {

		flush(result);
		group_table.clear();
		group_table.resize();
		return 0;
	}

	int set_param_block(int sz, void * value) {
		func.set_param_block(sz, value);
		return 0;
	}

	int get_temp_status(host_tuple& result) {
		result.channel = output_channel;
		return func.create_temp_status_tuple(result, flush_finished);
	}

	int get_blocked_status () {
		return -1;
	}

	unsigned int get_mem_footprint() {
		return group_table.get_mem_footprint();
	}
};

#endif	// GROUPBY_OPERATOR_H
