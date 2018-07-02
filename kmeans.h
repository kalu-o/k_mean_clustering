#ifndef KMEANS_H
#define KMEANS_H
#include "util.h"

/*
 *	Some simple, useful #define's
 */

typedef struct cluster
{
    float centroid[DIM_FEATURE];
    char name_cluster[MAX_NUM_CHAR];
    int c_count;
    float c_sum;
}cluster_t;

/*
 *	Function prototypes
 */
int get_euclidean_dist(const float*, const float*, float*);
int assign_cluster(input_node_t*, const cluster_t*);
int update_cluster_centroid(input_list_t*, cluster_t*);
int kmeans_algorithm(input_list_t*, cluster_t*);
int write_cluster_name(char*, const input_list_t*);
#endif // KMEANS_H
