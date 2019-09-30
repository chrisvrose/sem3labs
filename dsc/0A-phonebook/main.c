#include<stdio.h>
#include<stdlib.h>
#include<tree.h>

char menu[]="1.Insert\n2.Remove Entries\n3.Save entries\n4.Load entries\n5.Search entries\n6. Exit\n";

int main(){
	for(int choice=0;(printf("%s",menu),scanf("%d",&choice)==1);){
		switch(choice){
			case 6:
				printf("...\n");
				return 0;
			default:
				printf("Invalid choice\n");
		}
	}
}
