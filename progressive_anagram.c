#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 1000
#define MAX_DEPTH 100

MAX_DEPTH_REACHED = 0;

struct letter_counter {
	char letter;
	int counter;
};

struct Tree {
	struct Tree *left;
	struct Tree *right;
	int data_count;
	char* data[MAX];
	char split_on;
};

struct Tree* create(void) {
  struct Tree* newNode = malloc(sizeof(struct Tree));
  newNode->data[0]= NULL;
  newNode->split_on = NULL;
  newNode->data_count = 0;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}



void printTree(struct Tree* node, int level) {
    if (node != NULL) {
        printTree(node->left, level + 1);
	for (int i = 0;i<level;i++) {
		printf("          ");
	}
	if (node->split_on != NULL) {
		printf("%d -----> words: [",level);
		for (int j = 0;j<node->data_count;j++) {
			if (j == node->data_count-1) {
				printf(" %s ]",node->data[j]);
			}
			else {
				printf(" %s,",node->data[j]);
			}
		}
		printf(" | ask: %c\n",node->split_on);
	}
	else {
		printf("%d -----> final result:",level);
		for (int j = 0;j<node->data_count;j++) {
			printf(" %s ",node->data[j]);
		}
		printf("\n");
	}
        printTree(node->right, level + 1);
    }
}



char most_common_letter_finder(char* data[MAX],int word_count) {
	struct letter_counter letter_counter_array[MAX]; /* Counts how many words each letter appears in */
	int letters_in_counter_array = 0; /* Counts how many letters have been added */

	for (int i=0;i<word_count;i++) {
		/* For each word, we reduce them to only unique letters */
		int current_word_length = strlen(data[i]);
		char current_word[current_word_length+1];
		for (int letter_0=0;letter_0<current_word_length;letter_0++) {
			int new_letter = 1;
			for (int letter_1=0;letter_1<current_word_length;letter_1++) {
				if (data[i][letter_0] == current_word[letter_1]) {
					/* this letter is already in current word, so we skip */
				 	new_letter = 0;
				}
			if (new_letter == 1) {
				current_word[letter_0] = data[i][letter_0];
			}
		}
		}
		current_word[current_word_length+1] = '\0';
		int i, j, k;
		char current_letters_seen_in_this_word[MAX];
		int current_letters_seen_in_this_word_count = 0;
		int add_flag = 0;
		for (int j=0;j<current_word_length;j++) {
			/* We search each character, and then add to the big frequency list */
			int found_letter = 0;
			for (int n=0;n<=letters_in_counter_array;n++) {
				if (letter_counter_array[n].letter == current_word[j]) {
						letter_counter_array[n].counter++;
						found_letter = 1;
				}
			}

			if (found_letter == 0) {
					int n = letters_in_counter_array;
					struct letter_counter new;
					new.letter = current_word[j];
					new.counter = 1;
					letter_counter_array[n] = new;
					add_flag = 1;
					letters_in_counter_array++;
				}
		}
	}

	char most_frequent_letter = 0;
	int most_frequent_letter_count = 0;
	for (int n = 0;n<letters_in_counter_array;n++) {
		/*  Search frequency array to find most frequent character  */
	//	printf("letter: %c,frequency: %d\n",letter_counter_array[n].letter,letter_counter_array[n].counter);
		/* Check how many words the letter appears in */
		int how_many_words = 0;
		for (int i=0;i<word_count;i++) {
			int in_this_word = 0;
			/* For each word, we reduce them to only unique letters */
			int current_word_length = strlen(data[i]);
			char* current_word = data[i];
			for (int j=0;j<current_word_length;j++) {
				if (current_word[j] == letter_counter_array[n].letter) {
					in_this_word = 1;
				}
			}
			if (in_this_word == 1) {
				how_many_words++;
			}

		}

		if (how_many_words<word_count) {
			if (letter_counter_array[n].counter > most_frequent_letter_count) {
				most_frequent_letter_count = letter_counter_array[n].counter;
				most_frequent_letter = letter_counter_array[n].letter;
			}
		}

	}
	return most_frequent_letter;
}

int build_tree(struct Tree* node,int depth) {
if (depth>MAX_DEPTH_REACHED) {
	MAX_DEPTH_REACHED = depth;
}
if (depth>MAX_DEPTH) {
	return 0;
}
if (node->data_count == 1) {
	return 1;
}
char most_common_letter = most_common_letter_finder(node->data,node->data_count);
char* left_list[MAX];
int left_list_count = 0;

char* right_list[MAX];
int right_list_count = 0;

node->split_on = most_common_letter;

for (int i=0;i<node->data_count;i++) {
	char* word_to_look_at = node->data[i];
	int in_right = 0;
	for (int j=0;j<strlen(word_to_look_at);j++) {
		if (word_to_look_at[j] == node->split_on) {
			in_right = 1;
		}
	}
	if (in_right == 1) {
		right_list[right_list_count] = word_to_look_at;
		right_list_count++;
	}
	else {
		left_list[left_list_count] = word_to_look_at;
		left_list_count++;
	}


}

struct Tree* node_l = create();
struct Tree* node_r = create();

if (left_list_count == 0) {
	node->left = NULL;
}
else {
    node->left = node_l;
}
if (right_list_count == 0) {
	node->right = NULL;
}
else {
    node->right = node_r;
}

if (right_list_count == 0 && left_list_count == 0) {
	return 1;
}

node_l->data_count = left_list_count;
for (int li = 0;li<left_list_count;li++) {
	node_l->data[li] = left_list[li];
}
build_tree(node_l,depth+1);
node_r->data_count = right_list_count;
for (int ri = 0;ri<right_list_count;ri++) {
	node_r->data[ri] = right_list[ri];
}
build_tree(node_r,depth+1);

return 1;
}


int main(int argc,char** argv) {


struct Tree* inital_node = create();

if (argc<2) {
    printf("\nNo arguments supplied, using zodiac test input\n");
    inital_node->data[0] = "aries";
    inital_node->data[1] = "taurus";
    inital_node->data[2] = "gemini";
    inital_node->data[3] = "cancer";
    inital_node->data[4] = "leo";
    inital_node->data[5] = "virgo";
    inital_node->data[6] = "libra";
    inital_node->data[7] = "scorpio";
    inital_node->data[8] = "sagittarius";
    inital_node->data[9] = "capricorn";
    inital_node->data[10] = "aquarius";
    inital_node->data[11] = "pisces";
    inital_node->data_count = 12;
}
else {
	for (int i=0;i<argc-1;i++) {
		inital_node->data[i] = argv[i+1];
		}
	inital_node->data_count = argc-1;
}


build_tree(inital_node,0);
printTree(inital_node,0);

printf("\nYou would ask at most %d questions\n",MAX_DEPTH_REACHED);





return 0;
}

