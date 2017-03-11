#include <stdio.h>
#include <stdlib.h>


struct Process{
    int Process_ID;
    int Arrival_Time;
    int Burst_Duration;
    int Priority;
    int TurnAroundTime;
    int WaitTime;
};
//**********************************************************
struct Gantt
{
  int Process_ID;
  int Arrival_Time;
  int End_Time;
};

void File_Content(struct  Process Processes[], int number);
void FCFS(struct Process Processes[], int number);
void SJFP(struct Process Processes[], int number);
void PRIORITY(struct Process Processes[], int number);
void RR(struct Process Processes[], int number, int quantum);
void Display_Output(struct  Process Processes[],int number,struct Gantt Rows[],int count, char* filename);

int main(int argc, char **argv)
{

    int number_of_pross = 0;

    	if (argc != 2)
    	{
       		printf("Incorrect number of arguments.\n");
       	 	return -1;
    	}

		FILE* file1 = fopen(argv[1], "r");

  while(!feof(file1))
  {
  char  ch = fgetc(file1);
    if(ch == '\n')
    {
      number_of_pross++;
    }
  }
        struct Process Processes[number_of_pross];

        fseek(file1, 0, SEEK_SET);


        number_of_pross=0;


		while(fscanf(file1, "%d,%d,%d,%d",&Processes[number_of_pross].Process_ID,&Processes[number_of_pross].Arrival_Time,&Processes[number_of_pross].Burst_Duration,&Processes[number_of_pross].Priority) != EOF	)
       {
			number_of_pross++;
        }
        fclose(file1);

            File_Content(Processes,number_of_pross);
            FCFS(Processes,number_of_pross);
            SJFP(Processes,number_of_pross);
            PRIORITY(Processes,number_of_pross);
	
        return 0;
}
//--------------------------------------------------------
void File_Content(struct Process Processes[], int number)
{
    int i;
    printf("PROCESS ID\tARRIVAL TIME\tBURST DURATION\tPRIORITY\n");
    for(i=0;i<number;i++)
    {

        printf("%d\t\t%d\t\t%d\t\t%d\n",Processes[i].Process_ID,Processes[i].Arrival_Time,Processes[i].Burst_Duration,Processes[i].Priority);

    }
}
//---------------------------------------------------------------
void Display_Output(struct  Process Processes[],int number,struct Gantt Rows[],int count, char *filename)
{
      FILE* file;
      int i;
      file=fopen(filename,"w");
      fprintf(file,"PROCESS ID\tARRIVAL TIME\tEND TIME\n");

      for(i=0;i<count;i++)
      {
        fprintf(file,"%10d%10d%10d\n",Rows[i].Process_ID,Rows[i].Arrival_Time,Rows[i].End_Time);
      }

      float avgWait=0;
      float avgTurnAround=0;
      for(i=0;i<number;i++)
      {
          avgWait+=Processes[i].WaitTime;
          avgTurnAround+=Processes[i].TurnAroundTime;
      }
      fprintf(file,"Average Wait Time=%f\n",avgWait/number);
      fprintf(file,"TurnAround Time=%f\n",avgTurnAround/number);
      // Assumption: the value of count recieved is greater than exact number of rows in the Gantt chart by 1. Dont forget to adjust the value if yours is not so.
      fprintf(file,"Throughput=%f\n",((float)number/Rows[count-1].End_Time));
      fclose(file);

}
//------------------------------------------------------------

/*
 Note: Use function Display_Output to display the result. The Processes is the
 updated Processes with their respective waittime, turnAround time.
 Use the array of Gantt Struct to mimic the behaviour of Gantt Chart. Rows is the base name of the same array.
 number is the number of processes which if not changed during processing, is taken care. count is the number of rows in the Gantt chart. 
 
 Number of Processes will not exceed 1000. Create and array of Gantt chart which can accomodate atleast 1000 process.
 */
// -------------FCFS----------------------------------------
//
void FCFS(struct Process Processes[], int number)
{

    //---------Start Processing
  	struct Gantt* Rows = calloc(1500,sizeof(struct Gantt));

	for(int i = 0; i < number; i++){
		for(int j = 0; j < number; j++){
			struct Process process = Processes[i];
			if(Processes[i].Arrival_Time < Processes[j].Arrival_Time){
				process = Processes[i];
				Processes[i] = Processes[j];
				Processes[j] = process;
        		}
			else if(Processes[i].Arrival_Time == Processes[j].Arrival_Time){
				if(Processes[i].Process_ID < Processes[j].Process_ID){
					process = Processes[i];
					Processes[i] = Processes[j];
					Processes[j] = process;
				}
			}
	    	}
	}
	Processes[0].WaitTime = 0;
	for(int i = 1; i < number; i++){
		Processes[i].WaitTime = 0;
		for (int j = 0; j < i; j++){
			Processes[i].WaitTime += Processes[j].Burst_Duration;
		}
	}
	
        for(int i = 0; i < number; i++){
                Rows[i].Process_ID = Processes[i].Process_ID;
                Rows[i].Arrival_Time = Processes[i].WaitTime;
			if(i == 0){
				Rows[i].End_Time = Processes[i].Burst_Duration;
			}
			else{
				for(int j = 0; j < i; j++){
                       			Rows[i].End_Time = Processes[i].WaitTime + Processes[i].Burst_Duration;
        			}                
			}
        }
	
	for(int i = 0; i < number; i++){
		Processes[i].TurnAroundTime = Rows[i].End_Time - Processes[i].Arrival_Time;
		Processes[i].WaitTime = Processes[i].TurnAroundTime - Processes[i].Burst_Duration;
	}
	
	
	
	Display_Output(Processes, number, Rows, number, "FCFS");	
	
    //---------End of Processing
   //Hint: Call function with arguments shown Display_Output(Processes,number,Rows,count,"FCFS");
}
//---------------------SJFP---------------------------------------
void SJFP(struct Process Processes[],int number){
    //---------Start Pro}
//------------------PRIORITY-------------------------------------
void PRIORITY(struct Process Processes[], int number){
     //---------Start Processing
    //---------End of Processing

}



