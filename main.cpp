#include <stdio.h>
#include <cstdlib>
#include <cstring>  
#include <x86intrin.h>
#include <stdint.h>

struct huffman_node;

struct huffman_tree{
	huffman_node* base_node;
};

huffman_tree* create_huffman_tree(huffman_node* base_node)
{
	huffman_tree* tree = (huffman_tree*)malloc(sizeof(huffman_tree));
	tree -> base_node = base_node;

	return tree;
}


struct huffman_leaf
{
	int count;
	char letter;
	char code;
};

struct huffman_node{
	huffman_node* childNode;
	huffman_leaf* leaf;
	huffman_node* parent;
};

huffman_node* create_huffman_node(){
	huffman_node* node = (huffman_node*)malloc(sizeof(huffman_node));
	//node -> left = NULL;
	//node -> right = NULL;
	//node -> parent = NULL;
	return node;
}

void delete_huffman_node(huffman_node* ptr){
	free(ptr);
}


struct char_buffer{
	char letter;
	int count;
	char_buffer* next_char_node;
	char_buffer* prev_char_node;
};

char_buffer* create_char_buffer(char first_letter, int count_of_first_letter){
	char_buffer* charsArrStart = (char_buffer*)malloc(sizeof(char_buffer));
	charsArrStart -> letter = first_letter;
	charsArrStart -> count = count_of_first_letter;
	charsArrStart -> prev_char_node = NULL;
	charsArrStart -> next_char_node = NULL;
	return charsArrStart;
}

void delete_char_buffer(char_buffer*base_node){
	char_buffer* temp_next = base_node -> next_char_node;
	char_buffer* temp = base_node;
	
	while(temp_next != NULL)
	{
		free(temp);
		temp = temp_next;
		temp_next = temp_next -> next_char_node;
	}
	free(temp);

}

void add_new_char_buffer_node(char_buffer* base_node , char letter_in)
{
	char_buffer* temp_node = base_node;

	short exsist = 0;

	while(temp_node -> next_char_node != NULL)
	{	
		if(temp_node -> letter == letter_in)
		{
			temp_node -> count++;
			exsist = 1;
		}
		temp_node -> next_char_node -> prev_char_node = temp_node;
		temp_node = temp_node -> next_char_node;
	}
	
	if(temp_node -> letter == letter_in)
	{
		temp_node -> count++;
		exsist = 1;
	}

	if(exsist == 0)
		temp_node -> next_char_node = create_char_buffer(letter_in, 1);

}

void print_char_buffer(char_buffer* start_node)
{
	char_buffer* temp_node = start_node;
	while(temp_node -> next_char_node != NULL)
	{
		printf("%c - %d \n", temp_node -> letter, temp_node -> count);
		temp_node = temp_node -> next_char_node;
	}
	printf("%c - %d \n", temp_node -> letter, temp_node -> count);
}

void swap_char_buffers(char_buffer* node1, char_buffer* node2)
{	
	char node1letter = node1 -> letter;
	int node1count = node1 -> count; 
    node1 -> letter = node2 -> letter;
    node1 -> count = node2 -> count; 
    
    node2 -> count = node1count;
    node2 -> letter = node1letter;
}

void sort_char_buffer_array(char_buffer* start) 
{ 
    int swapped, i; 
    char_buffer* ptr1; 
    char_buffer* lptr = NULL; 
  
    if (start == NULL) 
        return; 
  
    do
    { 
        swapped = 0; 
        ptr1 = start; 
  
        while (ptr1->next_char_node != lptr) 
        { 
            if (ptr1->count < ptr1->next_char_node->count) 
            {  
                swap_char_buffers(ptr1, ptr1->next_char_node); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next_char_node; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
} 

void construct_huffman_tree(char_buffer* letters)
{

}

void convert_message_huffman_nodes(char* mess){
	char_buffer* base_node = create_char_buffer(mess[0], 1);

	for(int i = 1; i < strlen(mess); ++i)
	{
		add_new_char_buffer_node(base_node, mess[i]);
	}

	print_char_buffer(base_node);
	

	printf("-----SORT-----\n");
	sort_char_buffer_array(base_node);
	print_char_buffer(base_node);
	delete_char_buffer(base_node);
}

int main(){
	char* message = (char*)"bgttthyyaaaabbbbsssaaabbbdddaaaaabbbssssserega";
	printf("%s\n", message);
	convert_message_huffman_nodes(message);
	printf("---------------");
	return 0;
}