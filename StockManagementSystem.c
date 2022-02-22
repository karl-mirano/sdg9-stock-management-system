#include <stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct item{
	int itemcode;
	char name[20];
	int iqty;
	float iprice;
}item;

void create_items();
void display_items();
void add_items();
void itemcount();
void search_item();
void update_item();
void delete_item();
void sort_quantity();
void sort_name();

int main(){
	int ch;
	printf("-----------------------------------------------------\n");
	printf("Welcome to Stock Management System!\n");
	printf("-----------------------------------------------------");	
	do{
		printf("\n1. CREATE ITEMS");
		printf("\n2. DISPLAY ITEMS");
		printf("\n3. ADD ITEMS");
		printf("\n4. # OF ITEMS");
		printf("\n5. SEARCH ITEM");
		printf("\n6. UPDATE ITEM");
		printf("\n7. DELETE ITEM");
		printf("\n8. SORT BY ITEM QUANTITY");
		printf("\n9. SORT BY ITEM NAME");
		printf("\n0. LOG OUT");
		
		printf("\nEnter Number: \n");
		scanf("%d", &ch);
	
			if(ch == 1)
				create_items();
			else if(ch == 2)
				display_items();
			else if(ch == 3)
				add_items();
			else if(ch == 4)
				itemcount();
			else if(ch == 5)
				search_item();
			else if(ch == 6)
				update_item();
			else if(ch == 7)
				delete_item();
			else if(ch == 8)
				sort_quantity();
			else if(ch == 9)
				sort_name();
			
	}while(ch!=0);
	
	return 0;
}

void create_items(){
	item *d;
	FILE *fp;
	int n, i, j;
	printf("Enter Number of Items to Create: ");
	scanf("%d", &n);
	fp = fopen("mystocks.txt", "w");
	d = (item*)calloc(n, sizeof(item));
	for(i=0; i<n; i++)
	{
		printf("\n");
		printf("Enter ITEM CODE: ");
		scanf("%d", &d[i]);
		fflush(stdin);
		printf("Enter NAME: ");
		scanf("%[^\n]s", d[i].name);
		printf("Enter QUANTITY: ");
		scanf("%d", &d[i].iqty);
		printf("Enter PRICE: ");
		scanf("%f", &d[i].iprice);
		fwrite(&d[i], sizeof(item), 1, fp);
	}
	fclose(fp);
}
void display_items(){
	item d1;
	FILE *fp;
	fp = fopen("mystocks.txt", "r");
	int j;
	printf("#    ITEM NAME             QTY   PRICE");
	while(fread(&d1, sizeof(item), 1, fp))
	{
		printf("\n%-5d%-20s", d1.itemcode, d1.name);
		printf("%5d%7.2f\n", d1.iqty, d1.iprice);
	}
	fclose(fp);
}

void add_items(){
	item *d;
	FILE *fp;
	int n, i, j;
	printf("Enter Number of Items to Add: ");
	scanf("%d", &n);
	fp = fopen("mystocks.txt", "a");
	d = (item*)calloc(n, sizeof(item));
	for(i=0; i<n; i++)
	{
		printf("\n");
		printf("Enter ITEM CODE: ");
		scanf("%d", &d[i]);
		fflush(stdin);
		printf("Enter NAME: ");
		scanf("%[^\n]s", d[i].name);
		printf("Enter QUANTITY: ");
		scanf("%d", &d[i].iqty);
		printf("Enter PRICE: ");
		scanf("%f", &d[i].iprice);
		fwrite(&d[i], sizeof(item), 1, fp);
	}
	fclose(fp);
}

void itemcount(){
	item d1;
	FILE *fp;
	fp = fopen("mystocks.txt", "a");
	fseek(fp, 0, SEEK_END);
	int n = ftell(fp)/sizeof(item);
	printf("\n\n# OF ITEMS = %d", n);
	fclose(fp);
}

void search_item(){
	item d1;
	FILE *fp;
	fp = fopen("mystocks.txt", "r");
	int j, code, found = 0;
	printf("Enter Item Code to Search: ");
	scanf("%d", &code);
	printf("#    ITEM NAME             QTY   PRICE");
	while(fread(&d1, sizeof(item), 1, fp))
	{
		if(d1.itemcode == code){
			found = 1;
		printf("\n%-5d%-20s", d1.itemcode, d1.name);
		printf("%5d%7.2f\n", d1.iqty, d1.iprice);
		}
	}
	if(!found)
	printf("\nRecord Not Found\n");
	fclose(fp);
}

void update_item(){
	item d1;
	FILE *fp, *fp1;
	fp = fopen("mystocks.txt", "r");
	fp1 = fopen("item.txt", "w");
	int j, code, found = 0;
	printf("Enter # to Update: ");
	scanf("%d", &code);
	while(fread(&d1, sizeof(item), 1, fp))
	{
		if(d1.itemcode == code){
		found = 1;
		fflush(stdin);
		printf("\n");
		printf("Enter New NAME: ");
		scanf("%[^\n]s", d1.name);
		printf("Enter QUANTITY: ");
		scanf("%d", &d1.iqty);
		printf("Enter PRICE: ");
		scanf("%f", &d1.iprice);
	}
	fwrite(&d1, sizeof(item),1, fp1);
	
}
	fclose(fp);
	fclose(fp1);
	if(found){
	fp1 = fopen("item.txt", "r");
	fp = fopen("mystocks.txt", "w");
	
		while (fread(&d1, sizeof(item),1, fp1)){
		fwrite(&d1, sizeof(item), 1 , fp);
	
}
	fclose(fp);
	fclose(fp1);
}
else
printf("\nRecord Not Found\n");
}

void delete_item(){
	item d1;
	FILE *fp, *fp1;
	fp = fopen("mystocks.txt", "r");
	fp1 = fopen("item.txt", "w");
	
	int j, code, found = 0;
	printf("Enter Item Code to Delete: ");
	scanf("%d", &code);
	while(fread(&d1, sizeof(item), 1, fp))
	{
		if(d1.itemcode == code){
			found = 1;
	}
	else
	fwrite(&d1, sizeof(item), 1, fp1);
}
	fclose(fp);
	fclose(fp1);
	if(found){
	fp1 = fopen("item.txt", "r");
	fp = fopen("mystocks.txt", "w");
	
		while (fread(&d1, sizeof(item),1, fp1)){
		fwrite(&d1, sizeof(item), 1 , fp);
	
}
	fclose(fp);
	fclose(fp1);
}
else
printf("\nRecord Not Found\n");
}

void sort_quantity()
{
	item *d, d1;
	FILE *fp, *fp1;
	fp = fopen("mystocks.txt", "r");
	fseek(fp, 0, SEEK_END);
	int i, j;
	int n = ftell(fp)/sizeof(item);
	d = (item*)calloc(n, sizeof(item));
	
	rewind(fp);
	for(i = 0; i < n; i++)
	fread(&d[i], sizeof(item),1, fp);
	for(i = 0; i < n; i++){
		for(j=i+1;j<n;j++){
			if(d[i].iqty<d[j].iqty){
				d1 = d[i];
				d[i] = d[j];
				d[j] = d1;
			}
		}
	}
	printf("#    ITEM NAME             QTY   PRICE");
	for(i = 0; i < n; i++){
		printf("\n%-5d%-20s", d[i].itemcode, d[i].name);
		printf("%5d%7.2f\n", d[i].iqty, d[i].iprice);
	}
	fclose(fp);
}

void sort_name()
{
	item *d, d1;
	FILE *fp, *fp1;
	fp = fopen("mystocks.txt", "r");
	fseek(fp, 0, SEEK_END);
	int i, j;
	int n = ftell(fp)/sizeof(item);
	d = (item*)calloc(n, sizeof(item));
	
	rewind(fp);
	for(i = 0; i < n; i++)
	fread(&d[i], sizeof(item),1, fp);
	for(i = 0; i < n; i++){
		for(j=i+1;j<n;j++){
			if(strcmp(d[i].name, d[j].name)>0){
				d1 = d[i];
				d[i] = d[j];
				d[j] = d1;
			}
		}
	}
	printf("#    ITEM NAME             QTY   PRICE");
	for(i = 0; i < n; i++){
		printf("\n%-5d%-20s", d[i].itemcode, d[i].name);
		printf("%5d%7.2f\n", d[i].iqty, d[i].iprice);
	}
	fclose(fp);
}
