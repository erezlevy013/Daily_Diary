#include <stdio.h>

typedef struct Appointment
{
	int id;
	float start;
	float end;
	int room;
}Ap;

typedef struct AD
{
	int size;
	int blockSize;
	int numOfAp;
	Ap **ApArray;
	
}Ad;

/*	"Create_AD"
description: allocate struct of AD, allocate array of AP**	
input:   size - allocation size, blockSize- allocation size.
output: pointer to a Ad 
error:  NULL
*/
Ad *Create_AD(int _size, int _blockSize);

/*	"Create_Meeting"
description:  allocate array of AP*	
input:   start time, end time, room.
output: pointer to a AP 
error:  NULL
*/
Ap *Create_Meeting( float _start, float _end, int _room );

/*	"Insert_Appointment"
description:  insert appointment to array
input:   Ad (*ad), Ap( *ap)
output: indx of array 
error:  -1
*/
int Insert_Appointment(Ad *ad, Ap *ap);

/*	"Remove_Appointment"
description:  remove appointment from array
input:   Ad (*ad), Ap( *ap)
output: (1)->if remove else (0) 
*/
int Remove_Appointment(Ad *ad, Ap *ap);

/*	"Find_Appointment"
description:  search appointment from array
input:   Ad (*ad), Ap( *ap)
output: index if find
error:  -1
*/
int Find_Appointment(Ad *ad, Ap *ap);

/*	"Destroy_AD"
description:  (free) delete  all appointments from array
input:   Ad (*ad)
output: (0)-> ok
error:  -1
*/
int Destroy_AD(Ad *ad);

/*	"Print_AD"
description:  print all appointments from array
input:   Ad (*ad)
output: print
error:  -1
*/
void Print_AD(Ad *ad);

Ap * Find(Ad *ad, float _start);
