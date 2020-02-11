/* Author: Gabe Rivera
 * Date: Feb. 11, 2020
 * Course: CS 315, Dr. Finkel
 * Programming Assignment 2: Trees
 * 129 source lines of code: 16 lines in main, 113 lines of funtion code
 */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

struct node{
    int x,y,z;
    struct node *left, *right;
}; // struct for building trees

struct dataPoint{
    int x, y, z;
}; //struct for data points (x,y,z)

struct dataPoint* makePoint(int x, int y, int z){
    struct dataPoint *point = (struct dataPoint*)malloc(sizeof(struct dataPoint));
    point->x = x;
    point->y = y;
    point->z = z;
    return point;
} //function for creating data points used to allocate data into trees

void fillPoint(struct dataPoint *point, int numberOfPoints){
    for(int i = numberOfPoints-1; i >= 0; i--){
        scanf("%d", &point->z);
        scanf("%d", &point->y);
        scanf("%d", &point->x);
        point+=1;
    }
} //function used to fill data points from user input (works for randGen.pl and std input)

struct node* makeNodePackage(struct dataPoint *point){
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->x = point->x;
    newNode->y = point->y;
    newNode->z = point->z;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
} //make node from a "package", where a package is data point consisting of struct (x,y,z)

struct node* treeInit(struct dataPoint *point){
    return makeNodePackage(point);
} //function used to initilize initaly empty trees

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
    
} //fucntion used to insert nodes into a tree, sorted on the x value, ties go left. this function was derived from Dr.Finkels "in class" notes

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
} //fucntion used to insert nodes into a tree, sorted on the y value, ties go left.

void symmetric(struct node *tree){
    if (!tree)
        return;
    symmetric(tree->left);
    printf("(%d, %d, %d)\n",tree->x,tree->y,tree->z);
    symmetric(tree->right);
} //basic symmetrical (inorder) traversal, implemented by Dr. Finkel's in class notes

void pre(struct node *t1,struct node *t2){
    if(t1 == NULL) {// do nothing
    }else{
        insertTreeY(t2, makePoint(t1->x,t1->y,t1->z));
        pre(t1->left,t2);
        pre(t1->right,t2);
    }
} //preorder traversal. Also derived from Dr. Finkels notes

void post(struct node *tree){
    if(tree == NULL) {// do nothing
    }else{
        post(tree->left);
        post(tree->right);
        printf("(%d, %d, %d)\n",tree->x,tree->y,tree->z);
    }
} //postorder traversal from Dr. Finkels notes

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
        else break;
    }
    return closest;
} //helper fucntion to assist finding the closest Y value with respect to the "probe"

struct node *findClosest(struct node *tree, int target){
    struct node *closest = makeNodePackage(makePoint(DBL_MAX,DBL_MAX,DBL_MAX));
    return helper(tree,target,closest);
} //fucntion to find closest probe value

int main(int argc, char *argv[]){
    int dataPoints = atoi(argv[1]);
    int probe;
    struct dataPoint point[dataPoints]; // creates dataPoints number of point structures
    fillPoint(point, dataPoints);
    struct node *t1 = NULL, *t2 = NULL, *t3 = NULL;
    t1 = treeInit(point);
    t2 = treeInit(makePoint(DBL_MAX,DBL_MAX,DBL_MAX));
    for(int i = 1; i < dataPoints; i++)
        insertTreeX(t1, &point[i]);
    symmetric(t1);
    pre(t1,t2);
    post(t2->left);
    scanf("%d",&probe);
    t3 = findClosest(t2,probe);
    printf("(%d, %d, %d)\n",t3->x,t3->y,t3->z);
    return 0;
}
