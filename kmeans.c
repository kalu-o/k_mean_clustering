#include <stdio.h>
#include <stdlib.h>
#include "kmeans.h"
#include <string.h>
#include <math.h>


/*
 *	Calculates Euclidean distance.
 */
int get_euclidean_dist(const float *p_data, const float *p_centroid, float *distance)
{
    float x1, x2, y1, y2, x_diff, y_diff;
    x1 = p_data[0];
    y1 = p_data[1];

    x2 = p_centroid[0];
    y2 = p_centroid[1];

    x_diff = x1 - x2;
    y_diff = y1 - y2;
    *distance = sqrt(x_diff * x_diff + y_diff * y_diff);
    return 0;
}

/*
 *	Assigns a cluster to a data sample based on Euclidean distance.
 */
int assign_cluster(input_node_t *p_node, const cluster_t *p_cluster)
{

    int i, index_min_dist = 0;
    float distance[NUM_CLUSTER];

    for (i = 0; i < NUM_CLUSTER; i++)
    {
        get_euclidean_dist(p_node->d_point.data, p_cluster[i].centroid, &distance[i]);
        if (distance[i] < distance[index_min_dist]) index_min_dist = i;
    }

    strcpy(p_node->d_point.name_cluster, p_cluster[index_min_dist].name_cluster);
    p_node->d_point.error = distance[index_min_dist];
    return 0;

}

/*
 * Updates cluster means.
 */
int update_cluster_centroid(input_list_t *p_l_input, cluster_t *p_cluster)
{
    float centroid[NUM_CLUSTER][DIM_FEATURE] = {0};
    int i, count[NUM_CLUSTER] = {0};
    input_node_t *p_temp = p_l_input->p_head;
    p_l_input->total_error = 0;
    while  (p_temp != NULL)
    {
        if (strcmp(p_temp->d_point.name_cluster, "Adam") == 0)
        {
            centroid[0][0] += p_temp->d_point.data[0];
            centroid[0][1] += p_temp->d_point.data[1];
            count[0] += 1;
        }
        else if (strcmp(p_temp->d_point.name_cluster, "Bob") == 0)
        {
            centroid[1][0] += p_temp->d_point.data[0];
            centroid[1][1] += p_temp->d_point.data[1];
            count[1] += 1;
        }
        else if (strcmp(p_temp->d_point.name_cluster, "Charley") == 0)
        {
            centroid[2][0] += p_temp->d_point.data[0];
            centroid[2][1] += p_temp->d_point.data[1];
            count[2] += 1;
        }
        else if (strcmp(p_temp->d_point.name_cluster, "David") == 0)
        {
            centroid[3][0] += p_temp->d_point.data[0];
            centroid[3][1] += p_temp->d_point.data[1];
            count[3] += 1;
        }
        else if (strcmp(p_temp->d_point.name_cluster, "Edward") == 0)
        {
            centroid[4][0] += p_temp->d_point.data[0];
            centroid[4][1] += p_temp->d_point.data[1];
            count[4] += 1;
        }
        p_l_input->total_error += p_temp->d_point.error;
        p_temp = p_temp->p_next;
    }

    for (i = 0; i < NUM_CLUSTER; i++)
    {
        p_cluster[i].centroid[0] = (float)centroid[i][0]/count[i];
        p_cluster[i].centroid[1] = (float)centroid[i][1]/count[i];
    }

    return 0;
}

/*
 *	The k-means clustering algorithm.
 */
int kmeans_algorithm(input_list_t *p_l_input, cluster_t *p_cluster)
{
    input_node_t *p_temp = p_l_input->p_head;
    /*
     * Expectation step.
     */
    while  (p_temp != NULL)
    {
        assign_cluster(p_temp, p_cluster);
        p_temp = p_temp->p_next;
    }
    /*
     * Maximisation step.
     */
    update_cluster_centroid(p_l_input, p_cluster);
    return 0;
}

/*
 * Write out cluster names.
 */
int write_cluster_name(char *p_f_name, const input_list_t *p_l_input)
{
    FILE    *p_file;
    input_node_t *p_temp = p_l_input->p_head;
    /*
     *  First, open the text file for reading
     */
    p_file = fopen(p_f_name, "w");
    if (p_file == NULL)
    {
        perror("Could not open file for writing");
        exit(1);
    }
    fprintf(p_file, "error = %.3f\n\n", p_l_input->total_error);

    /*
     *  Write cluster names to the file
     */

    while  (p_temp != NULL)
    {
        fprintf(p_file, "%s \n", p_temp->d_point.name_cluster);
        p_temp = p_temp->p_next;
    }
    fprintf(p_file, "\n");
    close(p_file);
    return 0;
}

/*
 * Main.
 */
int main(int argc, char *argv[])
{
    int i;
    float prev_total_error = MAX_ERROR;
    /*
    * Initialise cluster centroid.
    */
    cluster_t a_clusters[NUM_CLUSTER] =
    {
        {{-0.357, -0.253}, "Adam", 0, 0},
        {{-0.055, 4.392}, "Bob", 0, 0},
        {{2.674, -0.001}, "Charley", 0, 0},
        {{1.044, -1.251}, "David", 0, 0},
        {{-1.495, -0.090}, "Edward", 0, 0}
    };
    input_list_t l_input = {NULL, NULL, 0};
    read_file(argv[1], &l_input);
    kmeans_algorithm(&l_input, a_clusters);
    while ( (prev_total_error - l_input.total_error)  > EPSILON)
    {
        prev_total_error = l_input.total_error;
        kmeans_algorithm(&l_input, a_clusters);
    }
    write_cluster_name(argv[2], &l_input);
    clear_input_list(&l_input);
    return 0;
}
