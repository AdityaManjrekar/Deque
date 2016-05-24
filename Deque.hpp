//g++ -std=c++11 test.cpp -lstdc++ -Wl,--no-as-needed -ldl
//g++ test.cpp -o test.o -std=c++11 -ldl
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include<iostream>
#include <typeinfo>
#define Deque_DEFINE(t)\
struct Deque_##t##_Iterator\
{\
t *object;\
int iterator_counter;\
int equal_flag;\
int size_of_array;\
int length;\
int first;\
int last,dec_counter;\
bool (*equal)(Deque_##t##_Iterator&,Deque_##t##_Iterator);\
void (*inc)(Deque_##t##_Iterator *);\
t &(*deref)(Deque_##t##_Iterator *);\
void (*dec)(Deque_##t##_Iterator *);\
bool (*compare)(const t&,const t&);\
};\
\
struct Deque_##t\
{\
t *object;\
int length,first,last,size_of_array,clear_flag,incr;\
char type_name[sizeof("Deque_"#t)]="Deque_"#t;\
int (*size)(Deque_##t *);\
int (*empty)(Deque_##t *);\
int (*equal)(Deque_##t ,Deque_##t );\
void (*dtor)(Deque_##t *);\
void (*push_back)(Deque_##t *,t);\
void (*push_front)(Deque_##t *,t);\
void (*pop_back)(Deque_##t *);\
void (*pop_front)(Deque_##t *);\
void (*clear)(Deque_##t *);\
t &(*front)(Deque_##t *);\
t &(*back)(Deque_##t *);\
Deque_##t##_Iterator (*begin)(Deque_##t *);\
Deque_##t##_Iterator (*end)(Deque_##t *);\
t &(*at)(Deque_##t *,int);\
bool (*compare)(const t&,const t&);\
};\
\
int Deque_##t##_equal(Deque_##t deq1,Deque_##t deq2)\
{\
	int flag =0;\
	int size1 = deq1.length;\
	int size2 = deq2.length;\
	if(size1==size2)\
	{\
		 for (int i = 0; i < size1+1; i++) \
			{	t t1 = deq1.at(&deq1, i);\
				t t2 = deq2.at(&deq2, i);\
				bool x = deq1.compare(t1,t2);\
				bool x1 = deq1.compare(t2,t1);\
				if(x || x1)\
				{\
					flag = 1;\
					break;\
				}\
				else\
					continue;\
			}\
			if(flag==1)\
				return 0;\
			else\
				return 1;\
	}\
	else\
	return 0;\
}\
int Deque_##t##_size(Deque_##t *deq)\
{\
	return deq->length;\
}\
\
int Deque_##t##_empty(Deque_##t *deq)\
{\
	int empty_Flag = 0;\
	if(deq->length==0)\
		empty_Flag =1;\
	else if(deq->length>0)	\
		empty_Flag =0;\
	return empty_Flag;\
}\
void Deque_##t##_pop_back(Deque_##t *deq)\
{\
	if(deq->length>1){\
	int bck = deq->last;\
	int size = deq->size_of_array;\
	deq->last = ((bck-1)+size)%size;\
	deq->length--;\
		}\
	else if(deq->length==1){\
		deq->first =-1;\
		deq->last =-1;\
		deq->length = 0;\
	}\
}\
void Deque_##t##_pop_front(Deque_##t *deq)\
{\
	if(deq->length>1){\
	int frnt = deq->first;\
	int size = deq->size_of_array;\
	deq->first = ((frnt+1)+size)%size;\
		deq->length--;\
	}\
	else if(deq->length==1){\
		deq->first =-1;\
		deq->last =-1;\
		deq->length = 0;\
	}\
}\
void Deque_##t##_push_back(Deque_##t *deq,t data)\
{\
if(deq->length==0)\
	deq->first=0;\
if(deq->length+1>deq->size_of_array)\
{\
	int old_size = deq->size_of_array;\
	deq->size_of_array = deq->size_of_array *4;\
	deq->object = (t *)realloc(deq->object,(deq->size_of_array*sizeof(t)));\
	int i =0;\
	for(i=0;i<deq->first;i++)\
	{\
		deq->object[old_size+i]=deq->object[i];\
	}\
	deq->last = old_size+i;\
	deq->object[deq->last] = data;\
	deq->length++;\
}\
else if(deq->last+1==deq->size_of_array)\
{\
	deq->last = 0;\
	deq->object[deq->last] = data;\
	deq->length++;\
}\
else\
{	deq->last++;\
	deq->object[deq->last] = data;\
		deq->length++;}\
}\
\
void Deque_##t##_push_front(Deque_##t *deq,t data)\
{\
if(deq->length==0){\
	deq->last=0;\
	deq->first=1;\
}\
if(deq->length+1>deq->size_of_array)\
{\
	int old_size = deq->size_of_array;\
	deq->size_of_array = deq->size_of_array *4;\
	deq->object = (t *)realloc(deq->object,(deq->size_of_array*sizeof(t)));\
	int i =0;\
	for(i=0;i<deq->first;i++)\
	{\
		deq->object[old_size+i]=deq->object[i];\
	}\
	deq->last = old_size+i-1;\
	if(deq->first==0)\
		deq->first = deq->size_of_array-1;\
	else\
		deq->first--;\
	deq->object[deq->first] = data;\
	deq->length++;\
}\
else if(deq->first-1<0)\
{\
	deq->first = deq->size_of_array-1;\
	deq->object[deq->first] = data;\
	deq->length++;\
}\
else\
{\
	deq->first--;\
	deq->object[deq->first] = data;\
	deq->length++;\
}\
}\
t &Deque_##t##_front(Deque_##t *deq)\
{\
return deq->object[deq->first];\
}\
t &Deque_##t##_back(Deque_##t *deq)\
{\
return deq->object[deq->last];\
}\
void Deque_##t##_clear(Deque_##t *deq)\
{\
deq->object = (t *)realloc(deq->object,(0*sizeof(t)));\
deq->clear_flag = 1;\
}\
void Deque_##t##_dtor(Deque_##t *deq)\
{\
if(deq->clear_flag==1)\
{\
	deq->object=NULL;\
	free(deq->object);\
}\
else\
{\
deq->object = (t *)realloc(deq->object,(0*sizeof(t)));\
	deq->object=NULL;\
	free(deq->object);\
}\
}\
\
\
void Deque_##t##_Iterator_inc(Deque_##t##_Iterator *it)\
{\
	if(it->iterator_counter<=it->last)\
		it->iterator_counter++;\
	else if(it->iterator_counter>it->last)\
		{\
			if(it->iterator_counter+1>=it->size_of_array)\
				it->iterator_counter=0;\
			else\
				it->iterator_counter++;\
		}\
}\
t &Deque_##t##_at(Deque_##t  *deq,int pos)\
{\
	if(pos==0)\
	 return deq->object[deq->first];\
	else if(pos==deq->length-1)\
	 return deq->object[deq->last];\
	else if(deq->first==deq->last && pos==0)\
	 return deq->object[deq->first];\
	else if(deq->first>deq->last)\
		return deq->object[pos -(deq->size_of_array-deq->first)];\
	else\
		return deq->object[pos +(deq->first)];\
		\
}\
\
void Deque_##t##_Iterator_dec(Deque_##t##_Iterator *it)\
{\
	if(it->dec_counter > 0)\
	{\
		if(it->first<it->last)\
			it->iterator_counter--;\
		else if(it->first>it->last)\
			{\
				if(it->last-1<0)\
					it->iterator_counter=it->size_of_array-1;\
				else\
					it->iterator_counter--;\
			}\
	}\
	it->dec_counter++;\
}\
t &Deque_##t##_Iterator_deref(Deque_##t##_Iterator *it)\
{\
	return it->object[it->iterator_counter];\
}\
bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator &it1,Deque_##t##_Iterator it2)\
{\
	t obj1 = it1.object[it1.iterator_counter];\
	t obj2 = it2.object[it2.last];\
	if(it1.equal_flag ==1)\
		{\
			it1.equal_flag =0;\
			return true;\
		}\
	else {\
	bool x = it1.compare(obj1,obj2);\
	bool x1 = it1.compare(obj2,obj1);\
		if(!(x || x1))\
			{\
			    it1.equal_flag =1;\
			    return false;\
			}\
		else\
			{\
				it1.equal_flag =0;\
				return false;\
			}\
		}\
}\
Deque_##t##_Iterator Deque_##t##_begin(Deque_##t *deq)\
{\
	Deque_##t##_Iterator it;\
	it.object = deq->object;\
	it.length = deq->length;\
	it.first = deq->first;\
	it.last = deq->last;\
	it.equal_flag =0;\
	it.dec_counter=0;\
	it.size_of_array = deq->size_of_array;\
	it.iterator_counter = deq->first;\
	it.equal = &Deque_##t##_Iterator_equal;\
	it.inc = &Deque_##t##_Iterator_inc;\
	it.deref = &Deque_##t##_Iterator_deref;\
	it.dec = &Deque_##t##_Iterator_dec;\
	it.compare = deq->compare;\
	return it;\
}\
Deque_##t##_Iterator Deque_##t##_end(Deque_##t *deq)\
{\
	Deque_##t##_Iterator it;\
	it.object = deq->object;\
	it.length = deq->length;\
	it.equal_flag =0;\
	it.dec_counter=0;\
	it.first = deq->first;\
	it.last = deq->last;\
	it.size_of_array = deq->size_of_array;\
	it.iterator_counter = deq->last;\
	it.equal = &Deque_##t##_Iterator_equal;\
	it.inc = &Deque_##t##_Iterator_inc;\
	it.deref = &Deque_##t##_Iterator_deref;\
	it.dec = &Deque_##t##_Iterator_dec;\
	it.compare = deq->compare;\
	return it;\
}\
void Deque_##t##_ctor(Deque_##t *deq,bool (*compare)(const t&,const t&))\
{\
deq->length= 0;\
deq->clear_flag= 0;\
deq->first= -1;\
deq->last= -1;\
deq->incr = 1;\
deq->size_of_array = 100;\
deq->object = (t *)calloc(deq->size_of_array,sizeof(t));\
deq->size = &Deque_##t##_size;\
deq->empty = &Deque_##t##_empty;\
deq->push_back = &Deque_##t##_push_back;\
deq->push_front = &Deque_##t##_push_front;\
deq->front = &Deque_##t##_front;\
deq->back = &Deque_##t##_back;\
deq->pop_back = &Deque_##t##_pop_back;\
deq->pop_front = &Deque_##t##_pop_front;\
deq->dtor = &Deque_##t##_dtor;\
deq->begin = &Deque_##t##_begin;\
deq->end = &Deque_##t##_end;\
deq->at = &Deque_##t##_at;\
deq->equal = &Deque_##t##_equal;\
deq->clear = &Deque_##t##_clear;\
deq->compare = compare;\
}
