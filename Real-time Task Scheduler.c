#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
UserId=Moinul
Password=Moinul909
*/

// Define login credentials
#define USER_ID "Moinul"
#define PASSWORD "Moinul909"

// Task structure to hold task information
typedef struct Task {
    int id;           // Task ID
    int priority;     // Priority of the task (higher value means higher priority)
    char name[50];    // Name of the task
} Task;

// Priority Queue (Max Heap) structure
typedef struct PriorityQueue {
    Task *tasks;        // Array of tasks
    int capacity;       // Maximum capacity of the heap
    int size;           // Current number of tasks in the heap
} PriorityQueue;

// Function to verify login credentials
int login() {
    char inputUserId[50];
    char inputPassword[50];

    printf("Enter User ID: ");
    scanf("%s", inputUserId);

    printf("Enter Password: ");
    scanf("%s", inputPassword);

    // Check if the entered credentials match the predefined credentials
    if (strcmp(inputUserId, USER_ID) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        printf("Login successful!\n\n");
        return 1;  // Return 1 for successful login
    } else {
        printf("Invalid User ID or Password.\n");
        return 0;  // Return 0 for failed login
    }
}

// Function to initialize a priority queue (max heap)
PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->tasks = (Task*)malloc(capacity * sizeof(Task));
    queue->capacity = capacity;
    queue->size = 0;
    return queue;
}

// Swap function for heapify operations
void swap(Task* a, Task* b) {
    Task temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function to maintain the max heap property
void heapify(PriorityQueue* queue, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < queue->size && queue->tasks[left].priority > queue->tasks[largest].priority)
        largest = left;

    if (right < queue->size && queue->tasks[right].priority > queue->tasks[largest].priority)
        largest = right;

    if (largest != i) {
        swap(&queue->tasks[i], &queue->tasks[largest]);
        heapify(queue, largest);
    }
}

// Insert a new task into the priority queue
void insertTask(PriorityQueue* queue, int id, int priority, char* name) {
    if (queue->size == queue->capacity) {
        printf("Error: Priority Queue is full. Cannot insert new task.\n");
        return;
    }

    // Insert the new task at the end of the heap
    int i = queue->size;
    queue->tasks[i].id = id;
    queue->tasks[i].priority = priority;
    strcpy(queue->tasks[i].name, name);
    queue->size++;

    // Fix the max heap property if violated
    while (i != 0 && queue->tasks[(i - 1) / 2].priority < queue->tasks[i].priority) {
        swap(&queue->tasks[i], &queue->tasks[(i - 1) / 2]);
        i = (i - 1) / 2;
    }

    printf("Task '%s' with priority %d added successfully.\n", name, priority);
}

// Extract the task with the highest priority from the priority queue
Task extractMax(PriorityQueue* queue) {
    if (queue->size <= 0) {
        printf("Error: No tasks in the priority queue.\n");
        Task emptyTask = {0, 0, ""};
        return emptyTask;
    }

    if (queue->size == 1) {
        queue->size--;
        return queue->tasks[0];
    }

    // Store the maximum value, and remove it from the heap
    Task root = queue->tasks[0];
    queue->tasks[0] = queue->tasks[queue->size - 1];
    queue->size--;
    heapify(queue, 0);

    return root;
}

// Display the tasks in the priority queue
void displayTasks(PriorityQueue* queue) {
    printf("\nCurrent Tasks in the Priority Queue:\n");
    printf("ID\tPriority\tName\n");
    for (int i = 0; i < queue->size; i++) {
        printf("%d\t%d\t\t%s\n", queue->tasks[i].id, queue->tasks[i].priority, queue->tasks[i].name);
    }
    printf("\n");
}

// Main function to test the real-time task scheduler
int main() {
    // Login mechanism
    if (login()) {
        printf("Access granted. You can use the real-time task scheduler.\n\n");

        // Create a priority queue with a maximum capacity of 10 tasks
        PriorityQueue* queue = createPriorityQueue(10);

        // Insert some tasks into the priority queue
        insertTask(queue, 1, 10, "Task A");
        insertTask(queue, 2, 30, "Task B");
        insertTask(queue, 3, 20, "Task C");
        insertTask(queue, 4, 40, "Task D");
        insertTask(queue, 5, 25, "Task E");

        // Display current tasks
        displayTasks(queue);

        // Execute tasks based on priority
        printf("Executing tasks based on priority...\n");
        while (queue->size > 0) {
            Task maxTask = extractMax(queue);
            printf("Executing Task ID %d: %s with Priority %d\n", maxTask.id, maxTask.name, maxTask.priority);
        }

        // Free allocated memory
        free(queue->tasks);
        free(queue);
    } else {
        printf("Access denied. Exiting program.\n");
    }

    return 0;
}

