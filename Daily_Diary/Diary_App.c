#include "Diary.h"

clear (void)
{    
  while ( getchar() != '\n' );
}
int main()
{
	float start , end ;	
	int room , res, i, flag = 0, res_save=0;
	char str='1', save[50], load_ch='1';
	Ad *ad;
	Ap *ap, *rm_p;
	ad = Create_AD(10,10);
	
	
	
	printf("Welcome,\n");

	while(str != 'q' && str != 'Q')
	{
		
		printf("Please choose an item from the menu\n");
		printf("1) Create Meeting \n2) Insert Appointment \n3) Remove Appointment \n4) Print Appointments\n5) Save Appointments\n6) Load Appointments\n");
		printf("to exit at any step, enter 'q' or 'Q'\n");
		printf("choose : ");
		fflush(stdin);
		scanf("%c",&str);
		
		if(str == 'q' || str == 'Q')
		{
			break;
		}
		else if(str == '1')
		{
			if(!flag)
			{
				printf("\n\n");
				printf("Please enter an hour to start meeting: ");
				scanf("%f",&start);
				printf("Please enter an hour to end meeting: ");
				scanf("%f",&end);
				printf("Please enter room meeting: ");
				scanf("%d",&room);
				ap = Create_Meeting( start, end, room );
				printf("\n");	
				if(start >= end || start < 0 || end > 24)
				{
					
					printf("                     The created meeting failed \n");
					printf("                     Error, hours not coherent\n");
					flag = 0;
					
				}
				else if( cheak(ad,ap) != -1)
				{
					
					printf("                    Create Meeting\n");
					printf("                    Please choose 2 for insert\n");
					flag = 1;
				}
				else
				{
					
					printf("                   The created meeting failed \n");
					printf("                   Already have an appointment at this hour\n");
					flag = 0;
				}

				
			}
			else
			{
				printf("                       insert meeting before...\n");
			}
		}
		else if(str == '2')
		{
			printf("\n\n");
			if(flag)
			{
				Insert_Appointment(ad, ap);
				flag = 0;
				printf("                    Insert appointment\n");
			}
			else
			{
				printf("                    create meeting before...\n");
			}
		}
		else if(str == '3')
		{
			printf("\n\n");
			if(ad->numOfAp > 0)
			{
				
				printf("Please enter the start time you want to remove: ");
				scanf("%f",&start);
				fflush(stdin);
				rm_p = Find(ad, start);
				if(Remove_Appointment(ad, rm_p))
				{
					printf("               Remove appointment\n");
				}
				else
				{
					printf("               No appointment\n");
				}
			}
			else
			{
				printf("                The meeting list is empty\n");
			}
				
		}
		else if(str == '4')
		{
			Print_AD(ad);
		}
		else if(str == '5')
		{	printf("\n\n");
			printf("Please enter the name of the file you want to keep:");
			scanf("%s", save);
			fflush(stdin);
			res_save = saveToFile(ad , save);
			if(res_save)
			{
				printf("                      The save was successful \n");
			}
			else if(res_save == -1)
			{
				printf("                      Save failed \n");
			}
			else
			{
				printf("                      Save failed (Empty file)\n");
			}
		}
		else if(str == '6')
		{
			printf("\n\n");
			printf("Are you sure you want to load a file? \nBecause it will delete you all the appointments ( y |  n )");
			clear();
			fflush(stdin);
			load_ch=getchar();
			
			if(load_ch == 'y')
			{
				printf("Please enter the name of the file you want to load:");
				scanf("%s",save);
				if(LoadToFile (ad, save))
				{
					printf("                      The load was successful \n");
				}
				else
				{
					printf("                      Load failed \n");
				}
				
			}
			else
			{
				printf("                     Loading failed\n");
				continue;
			}
			
		}
		else
		{
			printf("\n                   Choose again: \n");
		}
		printf("\n\n");		
		fflush(stdin);
		scanf("%c",&str);
	}
	

	
	Destroy_AD(ad);
	printf("                        Good bye \n");

	return 0;
}
