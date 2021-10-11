#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').
   Zero terminators are not printable (therefore false) */
bool delim_character(char c){
   if (c == '\t' || c == ' ' || c == '\n' || c == '(' || c == ')') {
      return true;   //when printing in %d, true is 1
   }
   return false;     //^^ false is 0

}

/* Return true (non-zero) if c is a non-whitespace
   character (not tab or space).
   Zero terminators are not printable (therefore false) */
bool non_delim_character(char c){
   if(c != '\t' && c != ' ' && c != '\0' && c != '\n' && c != '(' && c != ')') {
      return true;
   }
   return false;

}

/* Returns a pointer to the first character of the next
   space-separated word*/
char *word_start(char* str){     //declared str as char pointer
   //if there is more than one whitespace, continue until the word reaches a non-whitespace character
   for(; delim_character(*str) == 1; str++) {}    //while the value of the character is a whitespace, increment
   
   return str;

}

/* Returns a pointer to the first space character of the zero
terminated string*/
char *end_word(char* str){
   //int counter = 0;            //contains the index of the character, for testing purposes
   for(; non_delim_character(*str) == 1; str++) {
      //counter++;               
   }    //the first whitespace after a word will be considered the end of a word
   //printf("%d\n", counter);    //displays the index of the character 
   return str;
}
// counts the number of words or tokens
int count_tokens(char* str){
   int num_words = 0;
   char *start = word_start(str); 
   char *end;
   bool cont;
   cont = non_delim_character(*start);
   while(cont == 1) {   //if the start of the word is a whitespace, we reached the end of the string!
      num_words++;
      end = end_word(start);
      start = word_start(end);
      cont = non_delim_character(*start);
      
   }

   
   return num_words;

   
}
/* Returns a freshly allocated zero-terminated vector of freshly allocated
   space-separated tokens from zero-terminated str.
   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string"
     tokens[3] = 0
*/
char *copy_str(char *inStr, short len){
   //copy elements of the word into an char array pointer
   char * word = (char *)malloc(len+1 *sizeof(char*));      //allocating memory space for my array
   for(int i = 0; i < len; i++) {
      word[i] += inStr[i];
      //printf("%d ",i); 
   }
   return word;

}

char** tokenize(char* str){
   char ** tokens = (char**)malloc(count_tokens(str)*sizeof(char**)+1);
   char * start = word_start(str);
   char * end = end_word(str);
   for(int i = 0; i < count_tokens(str); i++){
      tokens[i] = copy_str(start, end - start);
      start = word_start(end);
      end = end_word(start);
      //printf("%d\t", i);    //checking if the array indeed has a zero-terminated string at the end
   }
   return tokens;

}


void print_all_tokens(char** tokens){
   
   for(int i = 0; *tokens != NULL; *tokens++) {
      printf("tokens[%d] = ""%s\n", i,*tokens);
      i++;
   }
}
//void main() {

/*testing delim_character
   char p = ' ', p1 = '\t', p2 = 'd';
   bool is_space = delim_character(p);
   bool is_space1 = delim_character(p1);
   bool is_space2 = delim_character(p2);
   printf("p is a whitespace:  \n");
   printf("%d\n",is_space);
   printf("%d\n",is_space1);
   printf("%d\n",is_space2); // 1 1 0
*/

/*testing non_delim_character
   char ch = ' ', ch1 = '\t', ch2 = '1';
   bool not_space = non_delim_character(ch);
   bool not_space1 = non_delim_character(ch1);
   bool not_space2 = non_delim_character(ch2);
   printf("is it a non-space char? \n");
   printf("%d\t %d\t %d\t", not_space, not_space1, not_space2);   // 0 0 1
*/

/*testing a pointer
char word[] = "hello ";
printf("%s\n", word);
char *pointer = word;
for (; 0 >= delim_character(*pointer); pointer++) {      //while value of element is not whitespace, print value of element
   printf("%c\t", *pointer);
}
printf("\n");
*/


/*testing *word_start
char word[] = "hello";
char *start = word_start(word);
printf("%c\n", *start);
*/


/*testing *word_end
char word[] = "hello";
char *end = end_word(word);
printf("%c\n", *end);
*/

/*testing count_tokens
char word[] = "  hello  world  ";
char *pointer = word;
int num = count_tokens(pointer);
printf("%d\n", num);
*/

/*testing copy_str
char word[] = "hello";
char * string = word;
char * copy = copy_str(string, 5);
for(; *copy != '\0'; copy++) {
   printf("%c\n", *copy);
}
*/

/*testing tokenize
char word[] = "  hello world haha  ";
char *token = word;
char ** tokens = tokenize(token);
for (int i = 0; i < count_tokens(token)+1; i++) {
   printf("%s\t", tokens[i]);
}
printf("\n");
*/


/*testing print_all_tokens
char word[] = "  hello world haha  ";
char *token = word;
char **tokens = tokenize(token);
print_all_tokens(tokens);
*/





//}
