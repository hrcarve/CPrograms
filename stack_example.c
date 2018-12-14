#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "helperFunctions.h"

// Structure definitions
struct data {
    time_t timestamp;
    char *textPtr; 
};

struct entry {
    double timestamp;
    struct entry *prev;
    struct entry *next;
    struct data *d;
    unsigned int index;
};


struct linkedList{
    time_t timestamp;
    unsigned int size;
    struct entry *head;
    struct entry *tail;
};

double timestamp()
{
   int rc = NOERROR;
   struct timeval tv;
   double ts = 0.0;
   if (gettimeofday(&tv, NULL) != 0) {
      rc = ERROR;
#ifdef TRACE_ERRORS
      fprintf (stderr,"timestamp:  ERROR: got an error from gettimeofday, rc: %i\n",rc);
#endif
      ts = -1;
   } else {
      //Convert the timeval to a double in units of seconds
      ts = (double)tv.tv_sec + ((double)tv.tv_usec / 1000000);
   }

  return ts;
}


// Global Variables
struct linkedList *myLinkedList = NULL;

int i = 0;

// Function Declarations
void push_back(struct entry *);
void push_front(struct entry *);
struct entry *pop_back();
struct entry *pop_front();
void help();

int main(int argc, char *argv[]) {
    struct entry *e = NULL, *temp = NULL;
    struct data *d = NULL;
    char input[100];
	double tempTime;
	//int sizeToUse=sizeof(todoListEntry_t);
	int check;
	char outName[100];
	FILE* fpt;


	//check=initStack(MAX_STACK_SIZE);

	if(argc==1){
		printf("No given file name..\n\n");
		strcpy(outName,"test.dat");
	}

	if(argc==2){
		int count=0;
		fpt=fopen(argv[1],"r");
		strcpy(outName,argv[1]);
		char* inputStr=(char*)malloc(1024*sizeof(char));
		double inputTime;

		/*while(fpt!=NULL&&fscanf(fpt, "%s %lf\n",inputStr,&inputTime)!=EOF){

			if(isStackFull()){
				printf("List full\n\n");
				break;
			}

			todoListEntry_t* newItem=(todoListEntry_t*)malloc(sizeToUse);
			newItem->textPtr=inputStr;
			newItem->ts=inputTime;
			pushStack((void*)newItem);
			count++;

			inputStr=(char*)malloc(1024*sizeof(char));

		}*/

		if(fpt!=NULL){
			printf("Input processed...%d items added\n\n",count);
			fclose(fpt);
		}
		else
			printf("Error when opening file\n\n");
	}
	
	if(argc>2){
		printf("Only one name allowed..Invalid input!\n\n");
		strcpy(outName,"test.dat");
	}



	while(1){
		printf("Enter command:\n\"h\" for help info\n\"q\" for quit\n\"s\" for printing current list\n\"size\" for current stack size\n\"pushTail or pushHead\" to add new item\n\"popHead or popTail\" to pop the last item entered\n\"clear\" to clear everything including files (if exist)\n\"save\" to save the current list to a file\n\n");
		scanf("%s",input);
	
	//help info
		if(strcmp(input,"h")==0)
			help();

		//quit
		if(strcmp(input,"q")==0)
			break;
	/*if(strcmp(input,"s")==0) {
	   while (temp->next != NULL){
            printf("Element = %s\n", d->textPtr );
            temp = temp->next;
     		}
	}	*/
	if(strcmp(input,"popHead")==0) {
	pop_front();
	}
	if(strcmp(input,"popTail")==0) {
	pop_back();
	}
	if(strcmp(input,"pushTail")==0) {

    // Initialize linked list
    myLinkedList = (struct linkedList *)malloc(sizeof(struct linkedList));
    myLinkedList->timestamp = time(NULL);

    // Create some entries
    	 char* tempStr=(char*)calloc(1024,sizeof(char));
          printf("Input string: ");
                //      int size = 50;
                //      fflush(stdin);
                //      fgets(tempStr, size, stdin);
         scanf(" %50[^\n]", tempStr);
         double tempTime = timestamp();

        d = (struct data *)malloc(sizeof(struct data));
        d->timestamp = tempTime;

        d->textPtr = tempStr;

        e = (struct entry *)malloc(sizeof(struct entry));
        e->timestamp = tempTime;
        e->d = d;

        push_back(e);
	i++;	
 
    // Print out data
    temp = myLinkedList->head;
    while (temp != NULL) {
        printf("Element %d contains %f %s \n", temp->index, temp->timestamp, temp->d->textPtr);
        temp = temp->next;
    }

    }
	if(strcmp(input,"pushHead")==0) {


	  myLinkedList = (struct linkedList *)malloc(sizeof(struct linkedList));
    myLinkedList->timestamp = time(NULL);

    // Create some entries
         char* tempStr=(char*)calloc(1024,sizeof(char));
          printf("Input string: ");
                //      int size = 50;
                //      fflush(stdin);
                //      fgets(tempStr, size, stdin);
         scanf(" %50[^\n]", tempStr);
         double tempTime = timestamp();

        d = (struct data *)malloc(sizeof(struct data));
        d->timestamp = tempTime;

        d->textPtr = tempStr;

        e = (struct entry *)malloc(sizeof(struct entry));
        e->timestamp = tempTime;
        e->d = d;

        push_front(e);
        i++;
	
    // Print out data
    temp = myLinkedList->head;
    while (temp != NULL) {
        printf("Element %d contains %f %s\n", temp->index, temp->timestamp, temp->d->textPtr);
        temp = temp->next;
    }
}
	if(strcmp(input,"clear")==0) {
    // Free all the memory
    while (myLinkedList->size) {
        temp = pop_back();
        free(temp->d);
        free(temp);
        temp = NULL;
    }
    free(myLinkedList);
    myLinkedList = NULL;
    
    return 0;
  }
  }
}

void push_back(struct entry *e) {

    // Check if list is initialized
    if (myLinkedList == NULL) {
        perror("UNDECLARED LIST");
        exit(1);
    }

    // If list size is not 0, append
    if (myLinkedList->size) {
        myLinkedList->tail->next = e;
        e->prev = myLinkedList->tail;
    } else {
        myLinkedList->head = e;
    }

    myLinkedList->tail = e;
    myLinkedList->size++;

    // Set the index of entry e
    e->index = myLinkedList->size - 1;
}

void push_front(struct entry *e) {
    struct entry *temp;
    // Check if list is initialized
    if (myLinkedList == NULL) {
        perror("UNDECLARED LIST");
        exit(1);
    }

    // If list size is not 0, prepend
    if (myLinkedList->size) {
        myLinkedList->head->prev = e;
        e->next = myLinkedList->head;
    } else {
        myLinkedList->tail = e;
    }

    myLinkedList->head = e;
    myLinkedList->size++;
	i++;
    // Set indecies
    temp = myLinkedList->head;
    while (temp != myLinkedList->tail) {
        temp->index = i++;
        temp = temp->next;
    }
}

struct entry *pop_back() {
    struct entry *e;

    myLinkedList->size--;   
    // Check if list is initialized
    if (myLinkedList == NULL) {
        perror("UNDECLARED LIST");
        exit(1);
    }

    // Set the back and delete it from the list
    e = myLinkedList->tail;
    if (myLinkedList->size) {
        e->prev->next = NULL;
        myLinkedList->tail = e->prev;
    }
    e->prev = NULL;



    return e;
}

struct entry *pop_front() {
    struct entry *e, *temp;
    int i = 0;

    myLinkedList->size--;
    // Check if list is initialized
    if (myLinkedList == NULL) {
        perror("UNDECLARED LIST");
        exit(1);
    }

    // Set the front and delete from list
    e = myLinkedList->head;
    if (myLinkedList->size) {
        e->next->prev = NULL;
        myLinkedList->head = e->next;
    }
    e->next = NULL;

    

    // Fix indecies
    temp = myLinkedList->head;
    while (temp != myLinkedList->tail) {
        temp->index = i++;
        temp = temp->next;
    }
    
    return e;
}


void help () 
{
   printf("Usage: ./a.out input_file_name  \n"); 
}
