/* Author: Gabe Rivera
 * Date: Jan. 30, 2020
 * Course: CS 315, Dr. Finkel
 * Programming Assignment 2: Trees
 *
 *
 *
 It takes a single integer parameter: the number n of data points in the tree.
 It reads n points from standard input. Each point has three integer components, which we call X, Y, and Z.
 As it reads those points, it places them in an initially empty binary tree T1 sorted on the X value.
 It traverses T1 in symmetric order, printing each point to standard output on a separate line in this format:
 
 (342, 512, 56311232)
 
 It traverses T1 in preorder, placing each node in an initially empty binary tree T2 sorted on the Y value.
 It traverses T2 in postorder, printing each point on a separate line in the same format as before.
 It reads one more integer from standard input: the probe p, a Y value. It searches for p in T2, printing the last point it encounters as it descends through T2, which might have p itself as its Y value, or its Y value might just be close to p.
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>

struct node{
    int x,y,z;
    struct node *left, *right;
};

struct dataPoint{
    int x, y, z;
};

struct dataPoint* makePoint(int x, int y, int z){
    struct dataPoint *point = (struct dataPoint*)malloc(sizeof(struct dataPoint));
    point->x = x;
    point->y = y;
    point->z = z;
    return point;
}

void fillPoint(struct dataPoint *point, int numberOfPoints){
    for(int i = 0; i < numberOfPoints; i++){
        scanf("%d", &point->x);
        scanf("%d", &point->y);
        scanf("%d", &point->z);
        point++;
    }
}

void printPoint(struct dataPoint *point, int numberOfPoints){
    for(int i = 0; i < numberOfPoints; i++){
        printf("\nData point %d values : ", i);
        printf("(%d, %d, %d)\n", point->x, point->y, point->z);
        point++;
    }
}

struct node* makeNodePackage(struct dataPoint *point){
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->x = point->x;
    newNode->y = point->y;
    newNode->z = point->z;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
    
}

struct node* treeInit(struct dataPoint *point){
    return makeNodePackage(point);
}

void insertTreeX(struct node *tree, struct dataPoint *point){
    struct node *parent = NULL;
    struct node *newNode = makeNodePackage(point);
    
    while(tree != NULL){
        parent = tree;
        tree = (point->x <= tree->x) ? tree->left : tree->right;
    }
    if(point->x <= parent->x){
        parent->left = newNode;
    }else{
        parent->right = newNode;
    }
}

void insertTreeY(struct node *tree, struct dataPoint *point){
    struct node *parent = NULL;
    struct node *newNode = makeNodePackage(point);
    
    while(tree != NULL){
        parent = tree;
        tree = (point->y <= tree->y) ? tree->left : tree->right;
    }
    if(point->y <= parent->y){
        parent->left = newNode;
    }else{
        parent->right = newNode;
    }
}

void symmetric(struct node *tree){
    if (!tree)
        return;
    symmetric(tree->left);
    printf("(%d,%d,%d)\n",tree->x,tree->y,tree->z);
    symmetric(tree->right);
}

void pre(struct node *t1,struct dataPoint *point){
    if(t1 == NULL) {// do nothing
    }else{
        struct dataPoint *point = makePoint(t1->x,t1->y,t1->z);
        point+=1;
        pre(t1->left,point);
        pre(t1->right,point);
    }
}

void post(struct node *tree){
    if(tree == NULL) {// do nothing
    }else{
        post(tree->left);
        post(tree->right);
        printf("(%d,%d,%d)\n",tree->x,tree->y,tree->z);
    }
}

struct dataPoint *nodeToPoint(struct node *tree){
    return makePoint(tree->x,tree->y,tree->z);
}

struct node *helper(struct node *tree, int target, struct node *closest){
    struct node *current = tree;
    while(current != NULL){
        if(abs(target-closest->y) > abs(target-current->y)){
            closest = current;
        }
        if(target < current->y){
            current = current->left;
        }
        else if(target > current->y){
            current = current->right;
        }
        else
            break;
    }
    return closest;
}

struct node *findClosest(struct node *tree, int target){
    struct node *closest = makeNodePackage(makePoint(DBL_MAX,DBL_MAX,DBL_MAX));
    return helper(tree,target,closest);
}

int main(int argc, char *argv[]){
    int dataPoints = atoi(argv[1]);
    int probe;
    struct dataPoint point[dataPoints]; // creates dataPoints number of point structures
    fillPoint(point, dataPoints);
    //printPoint(point, dataPoints);
    printf("\n");
    struct node *t1 = NULL;
    struct node *t2 = NULL;
    t1 = treeInit(point);
    t2 = treeInit(point);
    for(int i = 1; i < dataPoints; i++){
        insertTreeX(t1, &point[i]);
    }
    //printf("Symmetric Traversal on T1 sorted on X value:\n");
    symmetric(t1);
    pre(t1,point);
    for(int i = 1; i < dataPoints; i++)
        insertTreeY(t2,&point[i]);
    //printf("\nPostorder Traversal on T2 sorted on the Y value:\n");
    post(t2);
    scanf("%d",&probe);
    struct node *t3 = findClosest(t2,probe);
    printf("(%d,%d,%d)\n",t3->x,t3->y,t3->z);
    return 0;
}

