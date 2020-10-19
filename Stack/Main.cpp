#include <stdio.h>
#include <stdlib.h>


struct node
{
	int data;
	struct node* p;
};

int push(int data, struct node** pptop); 

int pop(struct node** pptop);


int main(void)
{
	struct node* ptop = NULL;
}

int push(int data, struct node** pptop)
{
	struct node* tmp = (struct node*)calloc(1, sizeof(struct node));; /*Создаём новый узел*/

	if (tmp == NULL)
	{
		printf("ERROR: Couldn't allocate memory\n");
		exit(1);
	}

	tmp->data = data; /*Присваеваем новое значение*/
	tmp->p = *pptop;

	*pptop = tmp; /*Переставляем вершину*/
}


int pop(struct node** pptop)
{
	struct node* tmp = *pptop;

	int temp_data = 0;

	if (*pptop == NULL)
	{
		printf("ERROR, Stack is empty\n");
		exit(1);
	}

	temp_data = tmp->data;

	*pptop = tmp->p;

	free(tmp);
	return x;
}