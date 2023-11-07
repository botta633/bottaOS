#ifndef LIST_H
#define LIST_H
 #include "../includes/debug.h"


// a definition of a doubly linked list based on macOS implementation.
//

#define __probable(x)   __builtin_expect((x), 1)
#define __improbable(x) __builtin_expect((x), 0)


#define LIST_HEAD(name, type) \
  struct name { \
    struct type *lh_first; \
  }

#define LIST_HEAD_INITIALIZER(head) \
{ NULL }

#define LIST_ENTRY(type) \
  struct { \
    struct type *le_next; /* next element */ \
    struct type **prev_element; \
  }

#define LIST_CHEACK_HEAD(head, feild) do { \
  if (__improbable( \
        LIST_FIRST((head)) != NULL && \
        LIST_FIRST((head)) -> field.le_prev !=  \
        &LIST_FIRST((head)))) \
          ASSERT("Bad List Head");\
} while (0)

#define LIST_CHECK_NEXT(elm, field) do {                                \
	if (__improbable(                                               \
	      LIST_NEXT((elm), field) != NULL &&                        \
	      LIST_NEXT((elm), field)->field.le_prev !=                 \
	      &((elm)->field.le_next)))                                 \
	            ASSERT("Bad link elm %p next->prev != elm @%u",     \
	                 (elm), __LINE__);                              \
} while (0)

#define LIST_CHECK_PREV(elm, field) do {                                \
	if (__improbable(*(elm)->field.le_prev != (elm)))               \
	        ASSERT("Bad link elm %p prev->next != elm @%u",          \
	            (elm), __LINE__);                                   \
} while (0)


#define LIST_EMPTY(head)                ((head)->lh_first == NULL)
#define LIST_FIRST(head)                ((head)->lh_first)

#define LIST_FOREACH(var, head, field)  \
  for((var) = LIST_FIRST((head)); \
      (var); \
      (var) = LIST_NEXT((var, field))


#define LIST_INIT(head) do {                                            \
	LIST_FIRST((head)) = NULL;                                      \
} while (0)

#define LIST_INSERT_AFTER(listelm, elm, field) do {                     \
	LIST_CHECK_NEXT(listelm, field);                                \
	if ((LIST_NEXT((elm), field) = LIST_NEXT((listelm), field)) != NULL)\
	        LIST_NEXT((listelm), field)->field.le_prev =            \
	            &LIST_NEXT((elm), field);                           \
	LIST_NEXT((listelm), field) = (elm);                            \
	(elm)->field.le_prev = &LIST_NEXT((listelm), field);            \
} while (0)

#define LIST_INSERT_BEFORE(listelm, elm, field) do {                    \
	LIST_CHECK_PREV(listelm, field);                                \
	(elm)->field.le_prev = (listelm)->field.le_prev;                \
	LIST_NEXT((elm), field) = (listelm);                            \
	*(listelm)->field.le_prev = (elm);                              \
	(listelm)->field.le_prev = &LIST_NEXT((elm), field);            \
} while (0)

#define LIST_INSERT_HEAD(head, elm, field) do {                         \
	LIST_CHECK_HEAD((head), field);                         \
	if ((LIST_NEXT((elm), field) = LIST_FIRST((head))) != NULL)     \
	        LIST_FIRST((head))->field.le_prev = &LIST_NEXT((elm), field);\
	LIST_FIRST((head)) = (elm);                                     \
	(elm)->field.le_prev = &LIST_FIRST((head));                     \
} while (0)

#define LIST_NEXT(elm, field)   ((elm)->field.le_next)

#define LIST_REMOVE(elm, field) do {                                    \
	LIST_CHECK_NEXT(elm, field);                            \
	LIST_CHECK_PREV(elm, field);                            \
	if (LIST_NEXT((elm), field) != NULL)                            \
	        LIST_NEXT((elm), field)->field.le_prev =                \
	            (elm)->field.le_prev;                               \
	*(elm)->field.le_prev = LIST_NEXT((elm), field);                \
	TRASHIT((elm)->field.le_next);                                  \
	TRASHIT((elm)->field.le_prev);                                  \
} while (0)






#endif
