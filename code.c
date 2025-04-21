#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 5
#define MAX_LOG_SIZE 10

// Queue for delivery requests
int inp_arr[MAX_SIZE];
int Rear = -1;
int Front = -1;

// Flight log
char flight_log[MAX_LOG_SIZE][50];
int log_index = 0;

// Function to add a delivery log entry
void logval(char delivery_type[]) {
    strcpy(flight_log[log_index], delivery_type);
    log_index = (log_index + 1) % MAX_LOG_SIZE;
}

// Function to print delivery type
void array(int value) {
    if (value == 1)
        printf("Food\n");
    else if (value == 2)
        printf("Medicine\n");
    else if (value == 3)
        printf("Tools\n");
    else if (value == 4)
        printf("Clothes\n");
    else if (value == 5)
        printf("Others\n");
    else
        printf("Invalid\n");
}

// Function to add a delivery request to the queue
void enqueue(int value) {
    if ((Front == 0 && Rear == MAX_SIZE - 1) || (Rear == (Front - 1) % (MAX_SIZE - 1))) {
        printf("Queue is Full\n");
        return;
    } else if (Front == -1) {
        Front = Rear = 0;
        inp_arr[Rear] = value;
    } else if (Rear == MAX_SIZE - 1 && Front != 0) {
        Rear = 0;
        inp_arr[Rear] = value;
    } else {
        Rear++;
        inp_arr[Rear] = value;
    }
    printf("Element %d is inserted in Queue\n", value);
}

// Function to process a standard delivery request from the queue
int dequeue() {
    int value;
    if (Front == -1) {
        printf("Queue is Empty\n");
        return -1; // Return -1 to indicate an error
    }
    value = inp_arr[Front];
    printf("Element %d is deleted from Queue\n", value);
    if (Front == Rear) {
        Front = Rear = -1;
    } else if (Front == MAX_SIZE - 1) {
        Front = 0;
    } else {
        Front++;
    }
    return value;
}

// Function to process a priority delivery request (from the top of the queue)
int pop() {
    int value;
    if (Front == -1) {
        printf("Queue is Empty\n");
        return -1; // Return -1 to indicate an error
    }
    value = inp_arr[Front];
    printf("Element %d is deleted from Queue\n", value);
    if (Front == Rear) {
        Front = Rear = -1;
    } else {
        Front++;
    }
    return value;
}

// Structure for overloaded drones (singly linked list)
struct node {
    int data;
    struct node *next;
};
struct node *head = NULL;

// Function to create a singly linked list of overloaded drones
void createNodeList(int value) {
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    ptr->data = value;
    ptr->next = NULL;
    if (head == NULL) {
        head = ptr;
    } else {
        struct node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = ptr;
    }
}

// Structure for drones in service (doubly linked list)
struct dnode {
    int data;
    struct dnode *next;
    struct dnode *prev;
};
struct dnode *dhead = NULL;

// Function to insert a drone into the doubly linked list of serviced drones
void insert(int value) {
    struct dnode *ptr = (struct dnode *)malloc(sizeof(struct dnode));
    ptr->data = value;
    ptr->next = NULL;
    ptr->prev = NULL;
    if (dhead == NULL) {
        dhead = ptr;
    } else {
        struct dnode *temp = dhead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = ptr;
        ptr->prev = temp;
    }
}

// Structure for drones needing emergency rerouting (circular singly linked list)
struct cnode {
    int data;
    struct cnode *next;
};
struct cnode *chead = NULL;

// Function to add a drone to the circular linked list for emergency rerouting
void addnode(int value) {
    struct cnode *ptr = (struct cnode *)malloc(sizeof(struct cnode));
    ptr->data = value;
    if (chead == NULL) {
        chead = ptr;
        ptr->next = chead;
    } else {
        struct cnode *temp = chead;
        while (temp->next != chead) {
            temp = temp->next;
        }
        temp->next = ptr;
        ptr->next = chead;
    }
}

// Function to remove a drone from the emergency rerouting list
void deletenode(int value) {
    if (chead == NULL) {
        printf("List is empty\n");
        return;
    }
    struct cnode *temp = chead, *prev = NULL;
    if (temp->data == value && temp->next == chead) {
        free(temp);
        chead = NULL;
        return;
    }
    while (temp->next != chead) {
        if (temp->data == value) {
            if (temp == chead) {
                while (temp->next != chead)
                    temp = temp->next;
                chead = temp->next;
                temp->next = chead;
                free(temp);
                return;
            } else {
                prev->next = temp->next;
                free(temp);
                return;
            }
        }
        prev = temp;
        temp = temp->next;
    }
    if (temp->data == value) {
        prev->next = chead;
        free(temp);
        return;
    }
    printf("Element %d not found in the list\n", value);
}

int main() {
    int choice, value;
    while (1) {
        printf("\n1. Add delivery request\n");
        printf("2. Dispatch drone\n");
        printf("3. Show recent deliveries\n");
        printf("4. Show/Manage Drone Status\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter delivery type (1-5):\n");
                printf("1. Food\n2. Medicine\n3. Tools\n4. Clothes\n5. Others\n");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                printf("1. Standard Delivery\n2. Priority Delivery\n");
                int deliveryChoice;
                scanf("%d", &deliveryChoice);
                if (deliveryChoice == 1) {
                    value = dequeue();
                    if (value != -1) {
                        printf("Drone dispatched for standard delivery of: ");
                        array(value);
                        logval("Standard Delivery");
                    }
                } else if (deliveryChoice == 2) {
                    value = pop();
                    if (value != -1) {
                        printf("Drone dispatched for priority delivery of: ");
                        array(value);
                        logval("Priority Delivery");
                    }
                } else {
                    printf("Invalid choice\n");
                }
                break;
            case 3:
                printf("Recent Deliveries:\n");
                if (log_index == 0 && strlen(flight_log[0]) == 0) {
                    printf("No deliveries yet\n");
                } else {
                    for (int i = 0; i < MAX_LOG_SIZE; i++) {
                        if (strlen(flight_log[i]) != 0)
                            printf("%s\n", flight_log[i]);
                    }
                }
                break;
            case 4:
                printf("1. Show Overloaded Drones\n");
                printf("2. Show Drones in Service\n");
                printf("3. Show Drones Needing Emergency Rerouting\n");
                printf("4. Show Flight Log\n");
                printf("Enter your choice: ");
                int droneChoice;
                scanf("%d", &droneChoice);
                if (droneChoice == 1) {
                    if (head == NULL) {
                        printf("No overloaded drones\n");
                    } else {
                        printf("Overloaded Drones: ");
                        struct node *temp = head;
                        while (temp != NULL) {
                            printf("%d ", temp->data);
                            temp = temp->next;
                        }
                        printf("\n");
                    }
                } else if (droneChoice == 2) {
                    if (dhead == NULL) {
                        printf("No drones in service\n");
                    } else {
                        printf("Drones in Service: ");
                        struct dnode *dtemp = dhead;
                        while (dtemp != NULL) { // Changed condition to dtemp != NULL
                            printf("%d ", dtemp->data);
                            dtemp = dtemp->next;
                        }
                        printf("\n");
                    }
                } else if (droneChoice == 3) {
                    if (chead == NULL) {
                        printf("No drones needing emergency rerouting\n");
                    } else {
                        printf("Drones Needing Emergency Rerouting: ");
                        struct cnode *ctemp = chead;
                        do {
                            printf("%d ", ctemp->data); // Corrected printf to print ctemp->data
                            ctemp = ctemp->next;
                        } while (ctemp != chead);
                        printf("\n");
                    }
                } else if (droneChoice == 4) {
                    printf("Flight Log:\n");
                    if (log_index == 0 && strlen(flight_log[0]) == 0) {
                        printf("No flights logged yet\n");
                    } else {
                         for (int i = 0; i < MAX_LOG_SIZE; i++) {
                            if (strlen(flight_log[i]) != 0)
                                printf("%s\n", flight_log[i]);
                        }
                    }
                }else {
                    printf("Invalid choice\n");
                }
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}

