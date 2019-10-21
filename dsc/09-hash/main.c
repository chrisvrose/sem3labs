#include<stdio.h>
#include<stdlib.h>
#define TABLE_SIZE 10
#define hash(x) ((x)%(TABLE_SIZE))

int htable[TABLE_SIZE];

void initTable(){
	for(int i=0;i<TABLE_SIZE;i++){
		htable[i] = -1;
	}
}

void display(){
	for(int i=0;i<TABLE_SIZE;i++){
		if(htable[i]>-1){
			printf("%d ",htable[i]);
		}else{
			printf("U ");
		}
		printf("\n");
	}
}

int insert(int data){
	int didInsert=0;
	for(int i=0;i<TABLE_SIZE;i++){
		if(htable[hash(data+i)]==-1){
			///Found empty
			htable[hash(data+i)] = data;
			didInsert=1;
			break;
		}
	}
	return didInsert;
}

int delete(int data){
	int didRemove=0;
	for(int i=0;i<TABLE_SIZE;i++){
		if(htable[hash(data+i)]==data){
			///Found
			htable[hash(data+i)] = -1;
			didRemove=1;
			break;
		}
	}
	return didRemove;
}

int search(int data){
	for(int i=0;i<TABLE_SIZE;i++){
		if(htable[hash(data+i)]==data){
			return htable[hash(data+i)];
		}
	}
	//Not found
	return -1;
}




#define MENU "1.Menu\n2.Insert\n3.Find\n4.Delete\n5.Display\n0.Exit\n"
int main(){
	initTable();
	printf(MENU "\n");int bufferVar,status1,status2;
	for(int choice =0; (printf("\n:"),scanf("%d",&choice)==1);){
		switch(choice){
			case 0:
				printf("...\n");
				return 0;
			case 1:
				printf(MENU "\n");
				break;
			case 2:
				printf("Insert\n:");
				if(scanf("%d",&bufferVar)==1){
					status1 = insert(bufferVar);
					printf("Insertion %s\n",status1?"Successful":"Failed");
				}
				break;
			case 3:
				printf("Find\n:");
				if(scanf("%d",&bufferVar)==1){
					status1 = search(bufferVar);
					if(status1>-1){
						printf("Found: %d\n",status1);
					}else{
						printf("Did not find\n");
					}
				}
				break;
			case 4:
				printf("Delete\n:");
				if(scanf("%d",&bufferVar)==1){
					status1 = delete(bufferVar);
					printf("Deletion %s\n",status1?"Successful":"Failed");
				}
				break;
			case 5:
				printf("Display:\n");
				display();
				break;
			default:
				printf("Invalid");
		}
	}
	return 0;
}
