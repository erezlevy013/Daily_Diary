#include <stdlib.h>
#include "Diary.h"

Ad *Create_AD( int _size, int _blockSize )
{
	Ad *ad;
	if((ad = (Ad*)malloc(sizeof(Ad))) == NULL)
	{
		return NULL;
	}
	ad->size = _size;
	ad->blockSize = _blockSize;
	ad->numOfAp = 0;
	if((ad->ApArray = (Ap**)malloc(ad->size * sizeof(Ap))) == NULL)
	{
		free(ad);
		return NULL;
	}
	
	return ad;
}

Ap *Create_Meeting( float _start, float _end, int _room )
{
	Ap *ap;
	static int num_id = 1;
	if(_start >= _end)
	{
		return NULL;
	}
	if((ap = (Ap*)malloc(sizeof(Ap))) == NULL)
	{
		
		return NULL;
	}
	ap->id = num_id++;
	ap->start = _start;
	ap->end = _end;
	ap->room = _room;
	
	return ap;
}

int cheak(Ad *ad, Ap *ap)
{
	int i, indx=0;
	
	for(i=0; i<ad->numOfAp; i++)
	{
		if((*(ad->ApArray+i))->start > ap->start && (*(ad->ApArray+i))->start > ap->end)
		{
			indx = i;
			return indx;
		}
		else if( (*(ad->ApArray+i))->end < ap->start )
		{
			continue;
		}
		else
		{
			
			return -1;
			
		}
	}

	return -2;
}

int Sort_Ap(Ad *ad, Ap *ap)
{
	int i, indx=0, size, j=0;
	
	if((indx = cheak( ad, ap )) == -1)
	{
		return -1;
	}
	if( indx == -2 )
	{
		return ad->numOfAp;
	}
	size = ad->numOfAp - indx;
	for(i=0; i<size; i++)
	{
		(*(ad->ApArray + ad->numOfAp - i )) = (*(ad->ApArray + ad->numOfAp - i - 1)); /* shift R*/
	}	
	return indx;
}

int increase(Ad *ad)
{
	Ap **new_addres;
	Ad *p_ad; 
	if(ad == NULL )
	{
		return -1;
	}
	p_ad = ad;
	if((new_addres = (Ap**)realloc(p_ad->ApArray,(p_ad->size + p_ad->blockSize)*sizeof(Ap))) == NULL )
	{
		return -1;
	}
	p_ad->size = p_ad->size + p_ad->blockSize;
	p_ad->ApArray = new_addres;
	
	return 0;
}

int Insert_Appointment(Ad *ad, Ap *ap)
{
	int indx = 0;
	if(ad == NULL || ap == NULL)
	{
		return -1;
	}
	if(ad->numOfAp == 0) /* first appointment*/
	{
		*(ad->ApArray+ad->numOfAp) = ap;
		ad->numOfAp++;
		return indx;
	}
	if( ad->size == ad->numOfAp ) /*realloc*/
	{
		if(increase(ad) != 0)
		{
			return -1;
		}
	}
	if((indx = Sort_Ap(ad, ap)) == -1) /* index to insert*/
	{
		return -1;
	}
	*(ad->ApArray+indx) = ap;
	ad->numOfAp++;
	return indx;
}

Ap * Find(Ad *ad, float _start)
{
	int i;
	Ap *ap;
	for(i=0; i<ad->numOfAp; i++)
	{
		if( (*(ad->ApArray+i))->start == _start )
		{
			return *(ad->ApArray+i);
		}
	}
	ap->id =0;

	return ap;
}

int Find_Appointment(Ad *ad, Ap *ap)
{
	int i;
	for(i=0; i<ad->numOfAp; i++)
	{
		if( (*(ad->ApArray+i))->id == ap->id )
		{
			return i;
		}
	}
	return -1;
}


int Remove_Appointment(Ad *ad, Ap *ap) /* By id */
{
	int i, indx;
	if(( indx = Find_Appointment(ad, ap)) != -1)
	{
		for(i=indx; i<ad->numOfAp; i++)
		{
			(*(ad->ApArray + i )) = (*(ad->ApArray + i + 1));
		}
		ad->numOfAp--;
		free(ap);
		return 1;	
	}
	
	return 0;
}


int Destroy_AD(Ad *ad)
{
	int i;
	if(ad == NULL)
	{
		return -1;
	}
	for(i=0; i<ad->numOfAp; i++)
	{
		free( ad->ApArray + i );
	}
	free(*ad->ApArray);
	free(ad);
	return 0;
}

void Print_AD(Ad *ad)
{
	int i;
	printf("----------------------------Appointment--------------------------\n");
	printf("|\tStart\t  |\tEnd\t |\tRoom\t|\tId\t|\n");
	for(i=0; i<ad->numOfAp; i++)
	{
		printf("-----------------------------------------------------------------\n");
		printf("|\t%0.2f\t  |\t%0.2f\t |\t%d\t|\t%d\t|\n", (*(ad->ApArray + i))->start, (*(ad->ApArray + i))->end, (*(ad->ApArray + i))->room, (*(ad->ApArray + i))->id);
	}
	printf("-----------------------------------------------------------------\n");
}

int saveToFile (Ad* ad, char* _str)
{
	FILE* diary;
	int i;

	diary = fopen(_str, "w");
	if (diary == NULL)
	{
		return -1;
	}
	if(ad->numOfAp == 0)
	{
		return -2;
	}
	fprintf(diary, "Number of meeting today: %d  \n", ad->numOfAp);
	fputs("|\tStart\t  |\tEnd\t |\tRoom\t|\n",diary);
	for (i=0; i<ad->numOfAp; i++)
	{
		fprintf(diary, "\t%.2f\t \t%.2f\t  \t%d\t\n",(*(ad->ApArray + i))->start,(*(ad->ApArray + i))->end,(*(ad->ApArray + i))->room);
	/*	fprintf(diary, "Start Time: %.2f \t",(*(ad->ApArray + i))->start);
		fprintf(diary, "End Time: %.2f \t", (*(ad->ApArray + i))->end);
		fprintf(diary, "Room: %d \n", (*(ad->ApArray + i))->room);*/
	}

	fclose(diary);

	return 1;
}

int LoadToFile (Ad* ad, char* _str)
{
	FILE* diary;
	int i, size_file =0, room;
	float start, end;
	Ap *ap;

	diary = fopen(_str, "r");
	if (diary == NULL)
	{
		return -1;
	}
	for(i=0; i<ad->numOfAp; i++)
	{
		Remove_Appointment(ad, *(ad->ApArray + i)); 
	}
	fseek(diary, 24, SEEK_SET );
	fscanf(diary, "%d ", &size_file);
	printf("Number of meeting today: %d \n",size_file);
	fseek(diary, 54, SEEK_SET );
	/*printf("----------------------------Appointment--------------------------\n");
	printf("|\tStart\t  |\tEnd\t |\tRoom\t|\tId\t|\n");*/
	
	while(!feof(diary))
	{
		fscanf(diary, "%f  %f  %d",&start,&end,&room);
		/*printf("%.2f  %.2f  %d \n",start,end,room);*/
		ap = Create_Meeting(start, end, room );
		Insert_Appointment(ad, ap);	
	}
	

	fclose(diary);

	return 1;
}







