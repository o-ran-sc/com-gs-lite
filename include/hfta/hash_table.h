/* ------------------------------------------------
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

#ifndef __HASH_TABLE_H
#define __HASH_TABLE_H

#include <stdlib.h>
#include <stdio.h>



#define NUM_PRIMES 23

static unsigned int primes[NUM_PRIMES] =  {
	11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853,
	25717, 51437, 102877, 205759, 411527, 823117, 1646237,
	3292489, 6584983, 13169977, 26339969, 52679969
};



template <class key_type, class value_type, class hasher_func, class equal_func>
class hash_table  {

public :
	struct data_item {
		key_type first;
		value_type second;
		data_item* next;	// next data item in overflow chain

		data_item(const key_type& k, const value_type& v) {
			first = k;
			second = v;
			next = NULL;
		 }
	};

	struct hash_bucket {
		data_item* data;	//
		hash_bucket* next_bucket;	// index of the next bucket in the list of used buckets
		hash_bucket* prev_bucket;	// index of the next bucket in the list of used buckets

		hash_bucket() {
			data = NULL;
			next_bucket = 0;	// 0 means no bucket follows this one
			prev_bucket = 0;	// 0 means no bucket precedes this one
		}
	};

	struct iterator {
		hash_bucket* bucket;
		data_item* data;

		iterator& operator++() {
			if (data->next)
				data = data->next;
			else {
				bucket = bucket->next_bucket;
				if (bucket)
					data = bucket->data;
				else
					data = NULL;
			}
			return *this;
		}

//			Like ++, but don't go beyond the end of the bucket chain.
		iterator& next() {
			if (data->next)
				data = data->next;
			else {
				bucket = NULL;
				data = NULL;
			}
			return *this;
		}

		bool operator!=(const iterator& it) {
			return (data != it.data || bucket != it.bucket);
		}

		bool operator==(const iterator& it) {
			return (data == it.data && bucket == it.bucket);
		}

		data_item &operator*() {
			return *data;
		}
	};

private:
	hasher_func hasher;
	equal_func equal;

	double load_factor;

	size_t _size;
	size_t _max_size;
	size_t num_buckets;
	size_t hash_mask;

	// bucket allocation happens on first insert
	// this flag indicates that buckets has been allocated
	unsigned allocated;


	hash_bucket* first_bucket;	// first used bucket
	hash_bucket* last_bucket;	// last used bucket

	hash_bucket* buckets;

	// memory footpritn in bytes
	unsigned int total_memory;

public:


	hash_table(const size_t expected_size = 100000, const double max_load = 1.25) {

		size_t min_buckets = (size_t)(expected_size / max_load);
		load_factor = max_load;
		int nb;
		for(nb=2;nb<min_buckets;nb*=2);
		num_buckets = nb;
		hash_mask = nb-1;

		// we will make hash table start with 0-size and expand of first insertion
		buckets = new hash_bucket[0];
		allocated = 0;

		_size = 0;
		_max_size = 0;
		first_bucket = 0;
		last_bucket = 0;

		total_memory = 0;
	}

	int insert(const key_type& key, const value_type& val) {

		if (__builtin_expect(!allocated, 0)) {		// we expect buckets to be allocated most of the time
			delete buckets;
			buckets = new hash_bucket[num_buckets];
			allocated = 1;	
			total_memory = num_buckets * sizeof(hash_bucket);

			// fprintf(stderr, "Initial allocaton of %d buckets\n", (int)num_buckets);
		}

		data_item* d = new data_item(key, val);
		total_memory += sizeof(data_item);

		// find the insertion bucket
		size_t bucket_index = hasher(key) & hash_mask;
		// if the bucket is empty just add new data_item
		if (!buckets[bucket_index].data) {
			// create new data item

			buckets[bucket_index].data = d;
			if (!first_bucket){
				first_bucket = &buckets[bucket_index];
			}else{
				last_bucket->next_bucket = &buckets[bucket_index];
			}

			if (last_bucket)
				buckets[bucket_index].prev_bucket = last_bucket;

			last_bucket = &buckets[bucket_index];
		} else {	// we already have data items in this bucket
			// prepend the item to overflow chain
			data_item* temp = buckets[bucket_index].data;
			buckets[bucket_index].data = d;
			d->next = temp;
		}
		_size++;
		if(_size>_max_size)
			_max_size = _size;

		return 0;
	}

	data_item *iterate_find(data_item* t, const key_type& key) {
		data_item *temp = t;
			while (temp && !equal(temp->first, key)){
				temp = temp->next;
			}
		return temp;
	}


	iterator find(const key_type& key) {
		iterator iter;

		if (__builtin_expect(!allocated, 0)) {		// we expect buckets to be allocated most of the time
			iter.bucket = NULL;
			iter.data = NULL;
			return iter;
		}		

		// find the insertion bucket
		size_t bucket_index = hasher(key) & hash_mask;
		// if the bucket is empty just add new data_item
		if (!buckets[bucket_index].data) {
			iter.bucket = NULL;
			iter.data = NULL;
		} else {	// we already have data items in this bucket
			data_item* temp = buckets[bucket_index].data;
//			temp = iterate_find(temp,key);

			while (temp && !equal(temp->first, key))
				temp = temp->next;

			iter.data = temp;
			if (!temp)
				iter.bucket = NULL;
			else
				iter.bucket = &buckets[bucket_index];
		}
		return iter;
	}

	void erase(const key_type& key) {

		if (__builtin_expect(!allocated, 0)) {		// we expect buckets to be allocated most of the time
			return;
		}	

		// find the  bucket
		size_t bucket_index = hasher(key) & hash_mask;
		// if the bucket is empty just add new data_item
		if (!buckets[bucket_index].data)
			return;

		data_item* temp = buckets[bucket_index].data;
		data_item* prev = NULL;
		while (temp && !equal(temp->first, key)) {
			prev = temp;
			temp = temp->next;
		}
		if (!temp)
			return;

		// delete this data item from the chain
		_size--;
		if (!prev){ 	// we are deleting the first element in chain
			buckets[bucket_index].data = temp->next;

			if(temp->next == NULL){
				if(buckets[bucket_index].next_bucket){
					buckets[bucket_index].next_bucket->prev_bucket = buckets[bucket_index].prev_bucket;
				}else{
					last_bucket = buckets[bucket_index].prev_bucket;
				}
				if(buckets[bucket_index].prev_bucket){
					buckets[bucket_index].prev_bucket->next_bucket = buckets[bucket_index].next_bucket;
				}else{
					first_bucket = buckets[bucket_index].next_bucket;
				}
				buckets[bucket_index].next_bucket = NULL;
				buckets[bucket_index].prev_bucket = NULL;
			}
		}else{
			prev->next = temp->next;
		}
        delete temp;
        total_memory -= sizeof(data_item);
	}

	void erase_full(const key_type& key) {

		if (__builtin_expect(!allocated, 0)) {		// we expect buckets to be allocated most of the time
			return;
		}

		// find the  bucket
		size_t bucket_index = hasher(key) & hash_mask;
		// if the bucket is empty just add new data_item
		if (!buckets[bucket_index].data)
			return;

		data_item* temp = buckets[bucket_index].data;
		data_item* prev = NULL;
		while (temp && !equal(temp->first, key)) {
			prev = temp;
			temp = temp->next;
		}
		if (!temp)
			return;

		// delete this data item from the chain
		_size--;
		if (!prev){ 	// we are deleting the first element in chain
			buckets[bucket_index].data = temp->next;

			if(temp->next == NULL){
				if(buckets[bucket_index].next_bucket){
					buckets[bucket_index].next_bucket->prev_bucket = buckets[bucket_index].prev_bucket;
				}else{
					last_bucket = buckets[bucket_index].prev_bucket;
				}
				if(buckets[bucket_index].prev_bucket){
					buckets[bucket_index].prev_bucket->next_bucket = buckets[bucket_index].next_bucket;
				}else{
					first_bucket = buckets[bucket_index].next_bucket;
				}
				buckets[bucket_index].next_bucket = NULL;
				buckets[bucket_index].prev_bucket = NULL;
			}
		}else{
			prev->next = temp->next;
		}
//        delete (*temp).first;
//        delete (*temp).second;
        delete temp;
        total_memory -= sizeof(data_item);
	}

	iterator begin() {
		iterator iter;
		// find the first data item
		iter.bucket = first_bucket;
		iter.data = (first_bucket) ? first_bucket->data : NULL;
		return iter;
	}

	iterator end() {
		iterator iter;
		iter.bucket = NULL;
		iter.data = NULL;
		return iter;
	}

	void clear() {
		data_item* temp;
		data_item* next;

		hash_bucket* tmp;
		while (first_bucket) {
			temp = first_bucket->data;
			while ( (next = temp->next) ) {
				delete temp;
				temp = next;
			}
			if(temp) delete(temp);
			first_bucket->data = NULL;
			tmp = first_bucket;
			first_bucket = first_bucket->next_bucket;
			tmp->next_bucket = NULL;
			tmp->prev_bucket = NULL;
		}
		last_bucket = NULL;
		_size = 0;
		total_memory = num_buckets * sizeof(hash_bucket);
	}

	int resize() {
		if (_size) {
			fprintf(stderr, "Error: resizing non-empty hash table\n");
			exit(1);
		}

		double max_load = (1.0 * _max_size) / num_buckets;

		// reize table if its maximum load exceed the load factor
		// OR it was less then half of the load factor
		size_t min_buckets = 0;
		if ((max_load > load_factor) || ((2 * max_load) < load_factor)) {
			min_buckets = ceil(_max_size / load_factor);
		} 
 
 
 		if (min_buckets) {
			// find power-of-2 size large than min_buckets;
			int nb;
			for(nb=2;nb<min_buckets;nb*=2);
			// make sure we actually changing the size
			if (nb != num_buckets) {
				fprintf(stderr, "Resizing from %d to %d buckets\n", (int)num_buckets, nb);
				num_buckets = nb;
				delete[] buckets;
				hash_mask = num_buckets-1;

				buckets = new hash_bucket[num_buckets];
				total_memory = num_buckets * sizeof(hash_bucket);
			}
		}

		return 0;
	}		

	size_t size() const {
		return _size;
	}

	size_t max_size() const {
		return _max_size;
	}

	bool empty() const {
		return (_size == 0);
	}

	~hash_table() {
		clear();
		delete[] buckets;
	}

	unsigned int get_mem_footprint() {
		return total_memory;
	}

};


template <class key_type, class hasher_func, class equal_func>
class hash_set  {

public :
	struct data_item {
		key_type key;
		data_item* next;	// next data item in overflow chain

		data_item(const key_type& k) {
			key = k;
			next = NULL;
		 }
	};

	struct hash_bucket {
		data_item* data;	//
		hash_bucket* next_bucket;	// index of the next bucket in the list of used buckets

		hash_bucket() {
			data = NULL;
			next_bucket = 0;	// 0 means no bucket follows this one
		}
	};

	struct iterator {
		hash_bucket* bucket;
		data_item* data;

		iterator& operator++() {
			if (data->next)
				data = data->next;
			else {
				bucket = bucket->next_bucket;
				if (bucket)
					data = bucket->data;
				else
					data = NULL;
			}
			return *this;
		}

		bool operator!=(const iterator& it) {
			return (data != it.data || bucket != it.bucket);
		}

		bool operator==(const iterator& it) {
			return (data == it.data && bucket == it.bucket);
		}

//			NOTE : not certain if returning ref always works
		key_type &operator*() {
			return data->key;
		}
	};

private:
	hasher_func hasher;
	equal_func equal;

	double load_factor;

	size_t _size;
	size_t _max_size;
	size_t num_buckets;
	size_t hash_mask;

	hash_bucket* first_bucket;	// first used bucket
	hash_bucket* last_bucket;		// last used bucket

	hash_bucket* buckets;

public:

	hash_set(const size_t expected_size = 100000, const double max_load = 1.25) {

		size_t min_buckets = (size_t)(expected_size / max_load);
		load_factor = max_load;
		int nb;
		for(nb=2;nb<min_buckets;nb*=2);
		num_buckets = nb;
		hash_mask = nb-1;
		buckets = new hash_bucket[num_buckets];

		_size = 0;
		_max_size = 0;
		first_bucket = 0;
		last_bucket = 0;
	}

	int insert(const key_type& key) {
		data_item* d = new data_item(key);

		// find the insertion bucket
		size_t bucket_index = hasher(key) & hash_mask;
		// if the bucket is empty just add new data_item
		if (!buckets[bucket_index].data) {
			// create new data item

			buckets[bucket_index].data = d;
			if (!first_bucket)
				first_bucket = &buckets[bucket_index];
			else
				last_bucket->next_bucket = &buckets[bucket_index];
			last_bucket = &buckets[bucket_index];
		} else {	// we already have data items in this bucket
			// prepend the item to overflow chain
			data_item* temp = buckets[bucket_index].data;
			buckets[bucket_index].data = d;
			d->next = temp;
		}
		_size++;
		if(_size>_max_size)
			_max_size = _size;

		return 0;
	}

	iterator find(const key_type& key) {
		iterator iter;

		// find the insertion bucket
		size_t bucket_index = hasher(key) & hash_mask;
		// if the bucket is empty just add new data_item
		if (!buckets[bucket_index].data) {
			iter.bucket = NULL;
			iter.data = NULL;
		} else {	// we already have data items in this bucket
			data_item* temp = buckets[bucket_index].data;
			while (temp && !equal(temp->key, key))
				temp = temp->next;
			iter.data = temp;
			if (!temp)
				iter.bucket = NULL;
			else
				iter.bucket = &buckets[bucket_index];
		}
		return iter;
	}

	void erase(const key_type& key) {
		// find the  bucket
		size_t bucket_index = hasher(key) & hash_mask;
		// if the bucket is empty just add new data_item
		if (!buckets[bucket_index].data)
			return;

		data_item* temp = buckets[bucket_index].data;
		data_item* prev = NULL;
		while (temp && !equal(temp->key, key)) {
			prev = temp;
			temp = temp->next;
		}
		if (!temp)
			return;

		// delete this data item from the chain
		_size--;
		if (!prev) 	// we are deleting the first element in chain
			buckets[bucket_index].data = temp->next;
		else
			prev->next = temp->next;
                delete temp;
	}

	iterator begin() {
		iterator iter;
		// find the first data item
		iter.bucket = first_bucket;
		iter.data = (first_bucket) ? first_bucket->data : NULL;
		return iter;
	}

	iterator end() {
		iterator iter;
		iter.bucket = NULL;
		iter.data = NULL;
		return iter;
	}

	void clear() {
		data_item* temp;
		data_item* next;

		hash_bucket* tmp;
		while (first_bucket) {
			temp = first_bucket->data;
			while ( (next = temp->next) ) {
				delete temp;
				temp = next;
			}
			if(temp) delete(temp);
			first_bucket->data = NULL;
			tmp = first_bucket;
			first_bucket = first_bucket->next_bucket;
			tmp->next_bucket = NULL;
		}
		last_bucket = NULL;
		_size = 0;

	}

	int resize() {
		if (_size) {
			fprintf(stderr, "Error: resizing non-empty hash table\n");
			exit(1);
		}
		
		double max_load = (1.0 * _max_size) / num_buckets;

		// reize table if its maximum load exceed the load factor
		// OR it was less then half of the load factor
		size_t min_buckets = 0;
		if ((max_load > load_factor) || ((2 * max_load) < load_factor)) {
			min_buckets = ceil(_max_size / load_factor);
		} 

		if (min_buckets) {
			// find power-of-2 size large than min_buckets;
			int nb;
			for(nb=2;nb<min_buckets;nb*=2);
			// make sure we actually changing the size
			if (nb != num_buckets) {
				fprintf(stderr, "Resizing from %d to %d buckets\n", (int)num_buckets, nb);
				num_buckets = nb;
				delete[] buckets;
				hash_mask = num_buckets-1;

				buckets = new hash_bucket[num_buckets];		
			}
		}

		return 0;
	}


	size_t size() const {
		return _size;
	}

	bool empty() const {
		return (_size == 0);
	}

	~hash_set() {
		clear();
		delete[] buckets;
	}

};


#endif // __HASH_TABLE_H
