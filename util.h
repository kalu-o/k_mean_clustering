#ifndef UTIL_H
#define UTIL_H
/*
 *	Some simple, useful #define's
 */


#define DIM_FEATURE 2
#define NUM_CLUSTER 5
#define MAX_NUM_CHAR 30
#define EPSILON 1e-8
#define MAX_ERROR 1e8

/*
 *	data point structure
 */
typedef struct data_point
{
    float data[DIM_FEATURE];
    char name_cluster[MAX_NUM_CHAR];
    float error;
}data_point_t;

/*
 *	data point structure as a node structure
 */
typedef struct input_node
{
    data_point_t d_point;
    struct input_node *p_next;
}input_node_t;

/*
 *	linked list of data point structure
 */
typedef struct input_list
{
    struct input_node *p_head, *p_tail;
    int l_count;
    float total_error;
}input_list_t;

/*
 *	Function prototypes
 */
int print_list(const input_list_t*);
int insert_node_back(input_list_t*, input_node_t*);
int read_file(char*, input_list_t*);
int clear_input_list(input_list_t*);
#endif // KMEANS_H

