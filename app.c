#include<stdio.h>
#include<time.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
float rate;
int rooms;
int floors;
struct database
{
	char name[10];
	int room_no;
	int adult;
	char contact[10];
	int children;
	char date[11];
	float extra;
	char time[5];
	struct database * next;
};
struct database * start=NULL;
void check_in()
{
	struct database *nv;
	nv=(struct database *)malloc(sizeof(struct database));
	nv->room_no=room_assign();
	if(nv->room_no!=0)
	{

		int i;
		char date_time[24];
		time_t t;
		time(&t);
		strcpy(date_time, ctime(&t));
		nv->extra=0;
		printf("\nEnter customer name: ");
		scanf("%s", &nv->name);
		fflush(stdin);
		printf("\nEnter no. of adult intake: ");
		scanf("%d", &nv->adult);
		printf("\nEnter no. of children intake: ");
		scanf("%d", &nv->children);
		fflush(stdin);
		printf("\nEnter contact no.: ");
		scanf("%s", &nv->contact);
		for(i=4;i<10;i++)
		{
			nv->date[i-4]=date_time[i];
		}
		for(i=19;i<24;i++)
		{
			nv->date[i-13]=date_time[i];
		}
		for(i=11;i<16;i++)
		{
			nv->time[i-11]=date_time[i];
		}
		nv->next=NULL;
		if(start==NULL)
		{
			start=nv;
		}
		else
		{
			struct database *ptr=start;
			while(ptr->next!=NULL)
			{
				ptr=ptr->next;
			}
			ptr->next=nv;
		}
		textcolor(GREEN);
		printf("\nCustomer named: ");
		cprintf("%s", nv->name);
		printf(" is alloted to room no. ");
		cprintf("%d", nv->room_no);
		textcolor(WHITE);
	}
}
int room_assign()
{
	int temp;
	int i, j, parity;
	struct database * ptr;
	for(i=1;i<=floors;i++)
	{
		for(j=1;j<=rooms;j++)
		{
			parity=0;
			temp=(i*100)+j;
			ptr=start;
			while(ptr!=NULL)
			{
				if(ptr->room_no==temp)
				{
					parity=1;
				}
				ptr=ptr->next;
			}
			if(parity==0)
			{
				return temp;
			}
		}
	}
	printf("\nNo rooms available!");
	return 0;
}
void check_status()
{
	struct database * ptr=start;
	int i;
	fflush(stdin);
	clrscr();
	printf("===+==========+=====+=====+==========+=====+===========+============");
	printf("\nRNo|Cust. Name|Adult|Child|Contact No| Time|   Date    |Extra charge");
	printf("\n==============+=====+=====+==========+=====+===========+============\n");
	while(ptr!=NULL)
	{
		printf("%3d|", ptr->room_no);
		printf("%10s|", ptr->name);
		printf("%5d|", ptr->adult);
		printf("%5d|", ptr->children);
		printf("%10s|", ptr->contact);
		printf("%s|", ptr->time);
		printf("%11s|", ptr->date);
		printf("Rs.%5.2f", ptr->extra);
		printf("\n");
		ptr=ptr->next;
	}
}
void enquire_rate_rooms_and_floors()
{
	printf("\nEnter no. of Rooms available: ");
	scanf("%d", &rooms);
	printf("\nEnter no. of Floors available: ");
	scanf("%d", &floors);
	printf("\nEnter rate of one room per day: ");
	scanf("%f", &rate);
}
void add_extra()
{
	float temp;
	int selection;
	int parity=0;
	struct database * ptr=start;
	printf("\nEnter room no. for extra services: ");
	scanf("%d", &selection);
	while(ptr!=NULL)
	{
		if(selection==ptr->room_no)
		{
			parity=1;
			break;
		}
		ptr=ptr->next;
	}
	if(parity==0)
	{
		printf("\nRoom no.not found!");
		return;
	}
	printf("\nEnter amount of extra services taken: ");
	scanf("%f", &temp);
	ptr->extra=ptr->extra+temp;
	printf("\nRs.%.2f added to customer's credit, total credit: Rs.%.2f", temp, ptr->extra);
}
void check_out()
{
	struct database * ptr=start;
	struct database * ptr_prev=start;
	int selection;
	int days;
	float stay_total;
	int parity=0;
	if(start==NULL)
	{
		printf("\nNo rooms. are filled!");
		return;
	}
	printf("\nEnter room no. for checkout: ");
	scanf("%d", &selection);
	while(ptr!=NULL)
	{
		if(selection==ptr->room_no)
		{
			parity=1;
			break;
		}
		ptr=ptr->next;
	}
	if(parity==0)
	{
		printf("\nRoom no.not found!");
		return;
	}
	printf("\nEnter days spent: ");
	scanf("%d", &days);
	stay_total=rate*days;
	clrscr();
	printf("================================");
	printf("\n    XYZ Lodging and Boarding");
	printf("\n================================");
	printf("\nCust. Name: %s", ptr->name);
	printf("\nCheck-in date: %s", ptr->date);
	printf("\nCheck-in time: %s", ptr->time);
	printf("\nAdults: %d  Children: %d", ptr->adult, ptr->children);
	printf("\n================================");
	printf("\nRate=%.2f x Days spent=%d", rate, days);
	printf("\nExtra charge=%.2f", ptr->extra);
	printf("\n================================");
	printf("\nTotal=Stay charge + Extra Charge");
	printf("\n     =%.2f + %.2f", stay_total, ptr->extra);
	printf("\n     =%.2f", stay_total+ptr->extra);
	printf("\n================================");
	printf("\n        Do visit again!         ");
		/*Checkout invoice showing*/
	if(ptr==start)
	{
		if(start->next!=NULL)
		{
			start=start->next;
		}
		else
		{
			start=NULL;
		}
		free(ptr);
		return;
	}
	if(ptr->next==NULL)
	{
		while(ptr_prev->next!=ptr)
		{
			ptr_prev=ptr_prev->next;
		}
		ptr_prev->next=NULL;
		free(ptr);
		return;
	}
	ptr_prev->next=ptr->next;
	free(ptr);
}
void show_menu()
{
	time_t t;
	time(&t);
	clrscr();
	printf("%s", ctime(&t));
	printf("Floors:%d  Rooms:%d  Rate:Rs%.2f/day", floors, rooms, rate);
	printf("\n=====================================");
	printf("\nWelcome to XYZ Hotel management suite");
	printf("\n=====================================");
	printf("\n1.Create check-in order");
	printf("\n2.Create check-out order");
	printf("\n3.Check room status");
	printf("\n4.Add extra charge");
	printf("\n5.EXIT");
}
int main()
{
	int choice;
	clrscr();
	enquire_rate_rooms_and_floors();
	do
	{
		show_menu();
		printf("\nEnter your choice: ");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
			{
				check_in();
				break;
			}
			case 2:
			{
				check_out();
				break;
			}
			case 3:
			{
				check_status();
				break;
			}
			case 4:
			{
				add_extra();
				break;
			}
			case 5:
			{
				goto EXIT;
			}
			default:
			{
				printf("\nInvalid choice!");
			}
		}
		printf("\n");
		system("pause");
	}while(1);
	EXIT:;
	return 0;
}
