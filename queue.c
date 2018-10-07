/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q != NULL) {
        q->head = NULL;
        q->tail = NULL;
        q->count = 0;
    }

    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q != NULL) {
        /* How about freeing the list elements and the strings? */
        /* Free queue structure */
        list_ele_t *oldh;
        while (q->head != NULL) {
            oldh = q->head;
            q->head = q->head->next;
            free(oldh->value);  // free the string
            free(oldh);         // free the list element
        }

        free(q);
    }
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* What should you do if the q is NULL? */
    if (q == NULL) {
        return false;
    }

    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    char *value = malloc((strlen(s) + 1) * sizeof(char));

    if (newh != NULL && value != NULL) {
        value[strlen(s)] = '\0';
        strncpy(value, s, strlen(s));

        newh->next = q->head;
        newh->value = value;
        q->head = newh;
        q->count += 1;

        if (q->count == 1) {
            q->tail = newh;
        }

        return true;
    }

    if (newh != NULL) {
        free(newh);
    }
    if (value != NULL) {
        free(value);
    }
    return false;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL) {
        return false;
    }
    if (q->count == 0) {
        return q_insert_head(q, s);
    }

    list_ele_t *newh = malloc(sizeof(list_ele_t));
    char *value = malloc((strlen(s) + 1) * sizeof(char));

    if (newh != NULL && value != NULL && q->tail != NULL) {
        value[strlen(s)] = '\0';
        strncpy(value, s, strlen(s));

        newh->next = NULL;
        newh->value = value;
        q->tail->next = newh;
        q->tail = newh;
        q->count += 1;

        return true;
    }

    if (newh != NULL) {
        free(newh);
    }
    if (value != NULL) {
        free(value);
    }
    return false;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (q == NULL || q->count == 0) {
        return false;
    }
    if (sp != NULL) {
        sp[bufsize - 1] = '\0';
        strncpy(sp, q->head->value, bufsize - 1);
    }

    list_ele_t *oldh;
    oldh = q->head;
    q->head = q->head->next;
    q->count -= 1;

    free(oldh->value);
    free(oldh);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q != NULL) {
        return q->count;
    }

    return 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q != NULL && q->count != 0) {
        q->tail = q->head;

        list_ele_t *prevh = q->head;
        list_ele_t *lasth = q->head->next;
        q->head->next = NULL;

        while (lasth != NULL) {
            q->head = lasth;
            lasth = lasth->next;
            q->head->next = prevh;
            prevh = q->head;
        }
    }
}
