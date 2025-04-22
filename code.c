#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10

//creating array for input requests and storing flight log
int inp_arr[10], flight_log[6];
int Rear = -1, Front = -1, top = -1, val = 0, value, lv = 0;
//using circular array for last 6 dispatches
void logval(int value)
{
    flight_log[val % 6] = value;
    val++;
}
//to display the output as per desired request
void array(int num)
{
    if (num == 1)
    {
        printf("food\n");
    }
    else if (num == 2)
    {
        printf("medicine\n");
    }
    else if (num == 3)
    {
        printf("tools\n");
    }
    else if (num == 4)
    {
        printf("water\n");
    }
    else if (num == 5)
    {
        printf("parts\n");
    }
    else if (num == 6)
    {
        printf("fuel\n");
    }
}
//to add an element(delivery request) to the queue
void enqueue()
{
    int insert_item;
    if (Rear == SIZE - 1)
    {
        printf("requests overflow ; wait for the request to be done \n");
        return;
    }
    if (Front == -1)
    {
        Front = 0;
    }
    printf("enter the delivery request required (1-6): ");
    if (scanf("%d", &insert_item) != 1 || insert_item < 1 || insert_item > 6)
    {
        printf("invalid request type.\n");
        // Clear the invalid input from the buffer
        while (getchar() != '\n');
        return;
    }
    printf("request accepted \n");
    Rear = Rear + 1;
    top = top + 1;
    inp_arr[Rear] = insert_item;
}
//to remove an element- here stands for dispatching the requests
void dequeue()
{
    if (Front == -1 || Front > Rear)
    {
        printf("no requests in the queue \n");
        return;
    }
    printf("request in progress is :\t");
    array(inp_arr[Front]);
    logval(inp_arr[Front]);
    lv++;
    value = inp_arr[Front];
    Front = Front + 1;
}
//removes the top element- helps with priority dispatch which is the first request in the queue
void pop()
{
    if (top == -1)
    {
        printf("no request in the queue\n");
        return;
    }
    printf("request in progress is \t");
    array(inp_arr[top]);
    logval(inp_arr[top]);
    lv++;
    top = top - 1;
    Rear = Rear - 1;
}
//forming a linked list for overloaded drones
struct node
{
    char data[20];
    struct node *next;
};

struct node *head, *newnode, *temp;
//adding nodes to the overloaded drone
void createNodeList()
{
    newnode = (struct node *)malloc(sizeof(struct node));
    if (newnode == NULL)
    {
        perror("malloc failed");
        return;
    }
    printf("enter the drone name to enter: ");
    if (scanf("%19s", newnode->data) != 1)
    {
        printf("invalid input.\n");
        free(newnode);
        while (getchar() != '\n');
        return;
    }
    newnode->next = NULL;
    if (head == NULL)
    {
        head = newnode;
        temp = newnode;
    }
    else
    {
        temp->next = newnode;
        temp = newnode;
    }
}
//double liked list for drones with ready usage
struct dnode
{
    char data[20];
    struct dnode *next;
    struct dnode *prev;
};

struct dnode *dhead, *dnewnode, *dtemp, *duse, *trav, *dlast = NULL;

//adding names to the doubly list
void insert()
{
    dnewnode = (struct dnode *)malloc(sizeof(struct dnode));
    if (dnewnode == NULL)
    {
        perror("malloc failed");
        return;
    }
    printf("enter the name of the drone to include: ");
    if (scanf("%19s", dnewnode->data) != 1)
    {
        printf("invalid input.\n");
        free(dnewnode);
        while (getchar() != '\n');
        return;
    }
    dnewnode->next = NULL;

    if (dhead == NULL)
    {
        dhead = dnewnode;
        dtemp = dnewnode;
        dnewnode->prev = NULL;
        duse = dhead;
        dlast = dhead;
    }
    else
    {
        dtemp->next = dnewnode;
        dnewnode->prev = dtemp;
        dnewnode->next = NULL;
        dtemp = dnewnode;
        dlast = dtemp;
    }
}
//circular linked list for emergency rerouting – fills in the same list
struct cnode
{
    char data[20];
    struct cnode *next;
};

struct cnode *chead, *cnewnode, *ctemp;

//applying emergency rerouting to the drones
void addnode()
{
    cnewnode = (struct cnode *)malloc(sizeof(struct cnode));
    if (cnewnode == NULL)
    {
        perror("malloc failed");
        return;
    }
    printf("enter the name of emergency drone to be rerouted: ");
    if (scanf("%19s", cnewnode->data) != 1)
    {
        printf("invalid input.\n");
        free(cnewnode);
        while (getchar() != '\n');
        return;
    }
    if (chead == NULL)
    {
        chead = cnewnode;
        ctemp = cnewnode;
        cnewnode->next = chead;
    }
    else
    {
        cnewnode->next = chead;
        ctemp->next = cnewnode;
        ctemp = cnewnode;
    }
}
//releasing drones (deleting nodes) when the weather clears
void deletenode()
{
    if (chead == NULL)
    {
        printf("No emergency drones to release.\n");
        return;
    }
    printf("the emergency drone that is rerouted is : %s\n", chead->data);
    struct cnode *temp_c = chead;
    if (chead == ctemp) // Only one node
    {
        chead = NULL;
        ctemp = NULL;
    }
    else
    {
        chead = chead->next;
        ctemp->next = chead;
    }
    free(temp_c);
}
//driving function
int main()
{
    int opt, option, choice, any, select;
    while (1) // Loop until explicitly exited
    {
        printf("\nenter the service to be provided\n");
        printf("1.add delivery request\n2.dispatch\n3.flight log unit\n4.maintenance tracker\n5.exit\n");
        if (scanf("%d", &opt) != 1)
        {
            printf("invalid input. please enter a number between 1 and 5.\n");
            // Clear the invalid input from the buffer
            while (getchar() != '\n');
            continue;
        }

        switch (opt)
        {
        case 1: // case for delivery request
            printf("enter the delivery request required (1-6): ");
            printf("1. food\n2.medicine\n3.tools\n4.water\n5.parts\n6.fuel\n"); 
            enqueue(); // function call to input values
            break;

        case 2: //case for dispatching
            printf("is it a priority dispatch or normal way dispatch??\n");
            printf("if priority press 1 or press any other number: ");
            if (scanf("%d", &option) != 1)
            {
                printf("invalid input. assuming normal dispatch.\n");
                while (getchar() != '\n');
                option = 0; // Treat as normal dispatch
            }

            if (option == 1) // if it a priority dispatch , dispatching the recently added delivery request
            {
                pop();
                if (duse == NULL)
                {
                    printf("no drones available to dispatch, add drones in serviced drone list\n");
                }
                else
                {
                    printf("assigning the dispatch to drone named : %s\n", duse->data);
                    if (duse == dlast)
                    {
                        duse = dhead; // Loop back if at the end
                        if (duse == dlast && duse != NULL) dlast = NULL; // Reset if only one node
                        else if (duse != NULL && duse->prev != NULL) dlast = duse->prev;
                        else dlast = NULL;
                    }
                    else
                    {
                        duse = duse->next;
                        if (dhead != NULL && duse != NULL && duse->prev == dlast) dlast = duse->prev;
                    }
                    if (dhead != NULL && dhead->next == NULL) dlast = dhead;
                }
            }
            else // if it is a normal dispatch, dequeue the needed dispatch
            {
                dequeue();
                if (duse == NULL)
                {
                    printf("no drones available to dispatch, add drones in serviced drone list\n");
                }
                else
                {
                    printf("assigning the dispatch to drone named : %s\n", duse->data);
                    if (duse == dlast)
                    {
                        duse = dhead; // Loop back if at the end
                        if (duse == dlast && duse != NULL) dlast = NULL; // Reset if only one node
                        else if (duse != NULL && duse->prev != NULL) dlast = duse->prev;
                        else dlast = NULL;
                    }
                    else
                    {
                        duse = duse->next;
                        if (dhead != NULL && duse != NULL && duse->prev == dlast) dlast = duse->prev;
                    }
                    if (dhead != NULL && dhead->next == NULL) dlast = dhead;
                }
            }
            break;

        case 3: // displying the flight log
            printf("Displaying the last %d dispatches done\n ", lv < 6 ? lv : 6);
            for (int i = 0; i < (lv < 6 ? lv : 6); i++)
            {
                array(flight_log[i % 6]);
            }
            break;

        case 4: // maintenance tracker
            printf("select the list to work on\n1.overloaded drones\n2.serviced drones\n3.emergency rerouting drones\n4.recently dispatched drones\n");
            if (scanf("%d", &choice) != 1)
            {
                printf("invalid input.\n");
                while (getchar() != '\n');
                break;
            }
            switch (choice)
            {
            case 1: // singly linked list for overloaded drones
                printf("do u want to 1.display names or 2. input names: ");
                if (scanf("%d", &select) != 1)
                {
                    printf("invalid input.\n");
                    while (getchar() != '\n');
                    break;
                }
                if (select == 1)
                {
                    temp = head;
                    if (temp == NULL)
                    {
                        printf("no overloaded drones.\n");
                    }
                    else
                    {
                        printf("overloaded drones:\n");
                        while (temp != NULL)
                        {
                            printf("%s\n", temp->data);
                            temp = temp->next;
                        }
                    }
                }
                else if (select == 2)
                {
                    createNodeList();
                }
                else
                {
                    printf("not a valid option\n");
                }
                break;

            case 2: // doubly list for drones in usage
                printf("do u want to 1.display names or 2. input names: ");
                if (scanf("%d", &select) != 1)
                {
                    printf("invalid input.\n");
                    while (getchar() != '\n');
                    break;
                }
                if (select == 1)
                {
                    dtemp = dhead;
                    if (dtemp == NULL)
                    {
                        printf("no serviced drones.\n");
                    }
                    else
                    {
                        printf("serviced drones:\n");
                        while (dtemp != NULL)
                        {
                            printf("%s\n", dtemp->data);
                            dtemp = dtemp->next;
                        }
                    }
                }
                else if (select == 2)
                {
                    insert();
                }
                else
                {
                    printf("not a valid option\n");
                }
                break;

            case 3: // circular list for emergency rerouting drones
                printf("select one option\n1.add drone\n2.release drone\n3.display drones: ");
                if (scanf("%d", &any) != 1)
                {
                    printf("invalid input.\n");
                    while (getchar() != '\n');
                    break;
                }
                switch (any)
                {
                case 1:
                    addnode();
                    break;

                case 2:
                    deletenode();
                    break;

                case 3:
                    ctemp = chead;
                    if (ctemp == NULL)
                    {
                        printf("no emergency drones.\n");
                    }
                    else
                    {
                        printf("emergency drones:\n");
                        do
                        {
                            printf("%s\n", ctemp->data);
                            ctemp = ctemp->next;
                        } while (ctemp != chead);
                    }
                    break;

                default:
                    printf("enter a valid option!!! exiting options!!\n");
                    break;
                }
                break;

            case 4: // displying the recent dispatches
                if (dhead == NULL || lv == 0)
                {
                    printf("no recent dispatches done.\n");
                }
                else
                {
                    printf("recently dispatched drones and delivery:\n");
                    struct dnode *current = dlast;
                    int count = 0;
                    while (current != NULL && count < lv)
                    {
                        printf("%s ", current->data);
                        array(flight_log[(val - 1 - count + 6) % 6]); // Access log in reverse order
                        current = current->prev;
                        count++;
                        if (current == dhead && count < lv && dhead != dlast) {
                            printf("%s ", current->data);
                            array(flight_log[(val - 1 - count + 6) % 6]);
                            break;
                        }
                    }
                }
                break;

            default:
                printf("not a valid option !!!exiting!!!\n");
                break;
            }
            break;

        case 5:
            printf("program exiting\n");
            exit(0);
            break;

        default:
            printf("not a valid choice!!!\n");
            break;
        }
    }
    return 0;
}
