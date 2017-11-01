#include <stdio.h>
#include <stdlib.h>

#undef __builtin_strlen
#undef __builtin_strcpy

typedef struct node {
	char letter;
	struct node *next;
} node;

typedef struct string {
	node *head;
	int length;
} string;


string* addChar(string *s, char c);
string* stringConstructor(char s[]);
void strPrintln(string *str);

//These are all the the linked list methods needed to support the string

//add a node to the end
node* append(node *head, char letter) {
	node *tmp;
	tmp = malloc(sizeof(node));
	tmp->letter = letter;
	tmp->next = NULL;
	if(!head)
		head = tmp;
	else {
		node *walker = head;
		while(walker->next)
			walker = walker->next;
		walker->next = tmp;
	}
	return head;
}

node* nodeRemove(node *head, char letter) {
	if(!head)
		return head;
	node *tmp = head;

	if(tmp->letter == letter) {
		head = head->next;
		return head;
	}

	while(tmp->next && tmp->next->letter != letter) {
		tmp = tmp->next;
	}
	if(tmp->next == NULL)
		return head;
	else {
		node *t = tmp->next;
		tmp->next = tmp->next->next;
		free(t);
	}
	return head;
}

//append the head2 list to the head1 list
node* merge(node *head1, node *head2) {
	node *head = head1;
	if(!head1 || !head2)
		return head;
	while(head1->next)
		head1 = head1->next;
	head1->next = head2;
	return head;
}

//return the "index" of a node
int find(node *head, char data) {
	int i = 0;
	if(!head)
		return -1;
	while(head && head->next && head->letter != data) {
		i++;
	}
	if(!head->next)
		return -1;
	else
		return i;
}

//print all the data in the list
void print(node *head) {
	while(head) {
			printf("%c", head->letter);
		head = head->next;
	}
}

//return data from an "index"
char getDataAt(node *head, int i) {
	int k = 0;
	if(!head) {
		return '\0';
	} else {
		while(head && k < i) {
			head = head->next;
			k++;
		}
	}
	if(!head) {
		return '\0';
	} else {
		return head->letter;
	}
}


//These are reimplemented string methods

//make a ll sring from an array string
string* stringConstructor(char s[]) {
	int i = 0;
	int len;
	while(s[i] != '\0')
		i++;
	len = i;
	string *str = malloc(sizeof(str));
	str->length = len;
	for(i = 0; i < len; i++) {
		str = addChar(str, s[i]);
	}
	return str;
}

//add a char to the end of the string
string* addChar(string *s, char c) {
	if(s) {;
		s->head = append(s->head, c);
	} else {
		char str[2] = "\0";
		str[0] = c;
		s = stringConstructor(str);
	}
	s->length = s->length + 1;
	return s;
}

//remove a char from the string
string* removeChar(string *s, char c) {
	if(s) {
		s->head = nodeRemove(s->head, c);
		s->length = s->length - 1;
	}
	return s;
}

//return length of ll string
int strlen(string *s) {
	if(s)
		return s->length;
}

//return character at specific index
char charAt(string *s, int loc) {
	if(s)
		return getDataAt(s->head, loc);
}

//return a pointer tot a copy of a string
string* strcpy(string *s) {
	if(!s)
		return s;
	string *new = malloc(sizeof(string));
	new->length = s->length;
	int i;
	for(i = 0; i < strlen(s); i++) {
			new = addChar(new, charAt(s, i));
	}
	return new;
}

//get index of character
int indexOf(string *s, char c) {
	if(s)
		return find(s->head, c);

}

//combine 2 strings
string* strcat(string *s1, string *s2) {
	string *new = malloc(sizeof(string));
	new->head = merge(s1->head, s2->head);
	new->length = s1->length + s2->length;
	return new;
}

//print a string
void strPrint(string *str) {
	if(str)
		print(str->head);
}

//print a string and a \n
void strPrintln(string *str) {
	if(str) {
		print(str->head);
		printf("\n");
	}
}

//read in a string __of any size!__
string* getInput(char prompt[]) {
	printf(prompt);
	string *input = NULL;
	char c;

	c = getchar();
	input = addChar(input, c);
	while(c != '\n') {
		c = getchar();
		input = addChar(input, c);
	}
	removeChar(input, '\n');
	return input;
}

//reimplement strings as linked lists bc why not
int main() {

	string *input = getInput("Enter a string of any length: ");
	printf("input string: ");
	strPrintln(input);

	string *hardcoded = stringConstructor("hardcoded");
	string *dash = stringConstructor("-");

	string *inputCopy = strcpy(input);
	printf("copied string: ");
	strPrintln(inputCopy);

	inputCopy = strcat(inputCopy, dash);
	inputCopy = strcat(inputCopy, hardcoded);
	printf("concatendated string: ");
	strPrintln(hardcoded);

}
