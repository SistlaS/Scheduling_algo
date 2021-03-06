
#define MAX_SIZE 150
struct Wt{
    int ind;
    float weight;
    int at;
};
// returns the index of the parent node
int parent(int i){
    return (i - 1) / 2;
}

// return the index of the left child 
int left_child(int i){
    return 2*i + 1;
}

// return the index of the right child 
int right_child(int i){
    return 2*i + 2;
}

void swap(struct Wt *x, struct Wt *y){
    struct Wt temp = *x;
    *x = *y;
    *y = temp;
}

// insert the item at the appropriate position
void insert(struct Wt a[], struct Wt data, int *n){
    if (*n >= MAX_SIZE){
        printf("%s\n", "The heap is full. Cannot insert");
        return;
    }
    // insert the time at the last position of the array and move it up
    a[*n] = data;
    *n = *n + 1;
    // move up until the heap property satisfies
    int i = *n - 1;
    while (i != 0 && a[parent(i)].weight < a[i].weight){
        swap(&a[parent(i)], &a[i]);
        i = parent(i);
    }
}

// moves the item at position i of array a
// into its appropriate position
void max_heapify(struct Wt a[], int i, int n){
    int left = left_child(i);
    int right = right_child(i);

    // find the largest among parent, left and right node
    int largest = i;

    // check if the left node is larger than the current node
    if (left <= n && a[left].weight > a[largest].weight){
        largest = left;
    }else if(left <= n && a[left].weight == a[largest].weight){
        //in case of tie the process with least arrival time stays on top
        if(a[left].at <= a[largest].at){
            largest = left;
        }
    }

    // check if the right node is larger than the current node
    if (right <= n && a[right].weight > a[largest].weight){
        largest = right;
    }else if(right <= n && a[right].weight == a[largest].weight){
        //in case of tie the process with least arrival time stays on top
        if(a[right].at <= a[largest].at){
            largest = right;
        }
    }

    // swap the largest node with the current node 
    // and repeat this Wt until the current node is larger than 
    // the right and the left node
    if (largest != i){
        struct Wt temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        max_heapify(a, largest, n);
    }

}

// converts an array into a heap
void build_max_heap(struct Wt a[], int n){
    int i;
    for (i = n/2; i >= 0; i--){
        max_heapify(a, i, n);
    } 
}

// returns the  maximum item of the heap
struct Wt* get_max(struct Wt a[]){
    return &a[0];
}
int is_empty(struct Wt a[], int *n){
    if(*n == 0){
        return 1;
    }
    return 0;
}
// deletes the max item and return
struct Wt extract_max(struct Wt a[], int *n){
    struct Wt max_item = a[0];

    // replace the first item with the last item
    a[0] = a[*n - 1];
    *n = *n - 1;

    // maintain the heap property by heapifying the 
    // first item
    max_heapify(a, 0, *n);
    return max_item;
}

// prints indices of processes in the heap 
void print_heap(struct Wt a[], int n){
    int i;
    for (i = 0; i < n; i++){
        printf("%d\n", a[i].ind+1);
    }
    printf("\n");
}
