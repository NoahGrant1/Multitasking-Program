#include <stdio.h>
#include <sys/types.h>
#include <ctype.h>

int main(int argc, void *argv[])
{
	printf("Parent %d: Welcome to the multitaskng system\n", getpid()); 
	void task1(), task2(char fname[50]), task3( char fname[50]); 
	
	int i, pid; 
	//run 3 child processes 
	for(i = 0; i < 3; i++)
	{
		//create new child process 
		pid = fork(); 
		
		//error handling 
		if(pid < 0)
		{
			perror("Error creating child process\n"); 
		}
		
	    //on success assign the child a task 
		if(pid == 0)
		{
			printf("Child %d: starting...\n", getpid());
			
			//decice upon the appropriate task to assign 
			switch(i + 1) 
			{
                case 1:
                    task1(); 
                    break; 
	            case 2:
				    task2(argv[1]); 
					break; 
                case 3:
				    task3(argv[2]); 
					break;
                default : 
				    perror("No task to assign\n"); 
            }
			
			//return successful creation 
			exit(0); 
		}
	}
	
	//wait for the child process
	for (i = 0; i < 3; i++)
	{
		//decice on what to wait for 
		switch(i+1) 
		{
            case 1:
                wait(&task1); 
                break; 
	        case 2:
				wait(&task2);  
			    break; 
            case 3:
				wait(&task3); 
			    break;
            default : 
				perror("No task to wait for\n"); 
        }
	}
	printf("Parent %d: System Shutting down...\n", getpid()); 
}

//calcuates the average of 10 marks 
void task1()
{
	int j; 
    float numbers[10], sum= 0.0, avg; 
	
	//get number from user 
	printf("Child %d: Begginning average Mark calculation...\n", getpid()); 
	printf("Child %d: Input 10 numbers: \n", getpid()); 
	for (j = 0; j < 10; j++) 
	{
		scanf("%f", &(numbers[j]) );
	}
	
	//display the user inputs 
	printf("Child %d: you have Entered: ", getpid()); 
	for(j = 0; j < 10; j++)
	{
	    printf("%.2f, ", numbers[j]); 
	}
	printf("\n"); 
	
	//calculate the average 
	for ( j = 0; j < 10; j++)
	{
		sum += numbers[j];
	}
	avg = sum/10; 
	
	printf("Child %d: Average marks = %.2f\n",getpid(), avg); 
}

//will count word count of file1
void task2(char fname[50]) 
{
	int count = 0;
    char ch; 	
	printf("Child %d: Counting Words from %s...\n",getpid(), fname); 
	
	//open the file in reading mode 
	FILE *file; 
	file = fopen(fname,"r"); 
	
	//check if file opened 
	if(file == NULL)
	{
		perror("File not found");  
	}
	
	//read and if space is detected increment count 
	while((ch = fgetc(file)) != EOF)
	{
		if( ch == ' ')//code for space 
		{
			count++;
		}
	}
	
	fclose(file); 
	printf("Child %d: The word count is: %d\n",getpid(), count); 
	
}

// will update file 3 
void task3(char fname[50])
{
	printf("Child %d: Updating %s...\n",getpid(), fname);

    //open file in read and write mode 	
	int size = 1024, i; 
	char buffer[size], ch; 
	FILE *file; 
	file = fopen(fname, "r+"); 
	
	//if file is not found 
	if(file == NULL)
	{
		perror("File not found");  
	}
	
	//ignore the updated version text(27 char), read the
	//remaining text and reset the file (clear it). 
	fseek(file, 27,SEEK_SET); 
	fgets(buffer, size, file); 
	fclose(fopen(fname, "w"));
	
	//go to beginning and put new text in file 
    rewind(file);	
	fprintf(file, "This is the updated version ");
	
	//change examine into check 
	const char match[7] = "examine";  
	for ( i = 0; i < size; i++)
	{
	    //repace examine with check 
	}
	
	//put current buffer into file 
	fputs(buffer, file); 
	
	fclose(file);
    printf("Child %d: File update done\n",getpid());
}