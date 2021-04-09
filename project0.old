#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>

struct uniChar{
    char one;
    char two;
    char three;
    char four;
};

struct charCount{
    struct uniChar* character;
    int count;
    int discovery;
};

int isIn(struct charCount* array[],struct uniChar* character, int index){
    for(int i=0; i<index;i++){
        if(array[i]->character->one == character->one
        && array[i]->character->two == character->two
        && array[i]->character->three == character->three
        && array[i]->character->four == character->four){
            return i;
        }
    }
    return -1;
}
int cmp(const void* a, const void* b)
{
    struct charCount* arg1 = *(struct charCount**)a;
    struct charCount* arg2 = *(struct charCount**)b;

    if(arg1->count>arg2->count){
       return -1;
    }
    else if(arg1->count<arg2->count){
        return 1;
    }
    else
        return arg1->discovery<arg2->discovery ? -1 : 1;

}


int main(int argc, char **argv, char** envp){
    int index = 0;
    struct charCount* array[1000000];
    char character;
    int i;
    while((character = getchar()) != EOF){

        if((unsigned char)character < 128){//one byte
            struct uniChar *ch = malloc(sizeof *ch);
            ch->one = character;
            ch->two = (char)0;
            ch->three =(char)0;
            ch->four = (char)0;
            i = isIn(array, ch,index);
            if(i != -1){
                array[i]->count++;
            }
            else{
                struct charCount *counter = malloc(sizeof *counter);
                counter->character = ch;
                counter->count = 1;
                counter->discovery = index;
                array[index] = counter;
                index++;
            }
        }
        else if((unsigned char)character < 224){ //two bytes
            struct uniChar *ch = malloc(sizeof *ch);
            ch->one = character;
            ch->two = getchar();
            ch->three =(char)0;
            ch->four = (char)0;
            i = isIn(array, ch,index);
            if(i != -1){
                array[i]->count++;
            }
            else{
                struct charCount *counter = malloc(sizeof *counter);
                counter->character = ch;
                counter->count = 1;
                counter->discovery = index;
                array[index] = counter;
                index++;
            }
        }
        else if((unsigned char)character < 240){//three bytes
            struct uniChar *ch = malloc(sizeof *ch);
            ch->one = character;
            ch->two = getchar();
            ch->three = getchar();
            ch->four = (char)0;
            i = isIn(array, ch,index);
            if(i != -1){
                array[i]->count++;
            }
            else{
                struct charCount *counter = malloc(sizeof *counter);
                counter->character = ch;
                counter->count = 1;
                counter->discovery = index;
                array[index] = counter;
                index++;
            }
        }
        else{//four bytes
            struct uniChar *ch = malloc(sizeof *ch);
            ch->one = character;
            ch->two = getchar();
            ch->three = getchar();
            ch->four = getchar();
            i = isIn(array, ch,index);
            if(i != -1){
                array[i]->count++;
            }
            else{
                struct charCount *counter = malloc(sizeof *counter);
                counter->character = ch;
                counter->count = 1;
                counter->discovery = index;
                array[index] = counter;
                index++;
            }
        }
    }
    unsigned int uniC = 0;
    setlocale(LC_CTYPE, "");
    qsort(array, index, sizeof(*array), cmp);
    for(int i = 0; i<index;i++){
        if(array[i]->character->four != (char)0){

            uniC= (unsigned int)(unsigned char)array[i]->character->four & 0b00111111;
            uniC+= ((unsigned int)(unsigned char)array[i]->character->three & 0b00111111) << 6;
            uniC+= ((unsigned int)(unsigned char)array[i]->character->two & 0b00111111) << 12;
            uniC+= ((unsigned int)(unsigned char)array[i]->character->one & 0b00000111) << 18;
        }
        else if(array[i]->character->three != (char)0){

            uniC= (unsigned int)(unsigned char)array[i]->character->three & 0b00111111;
            uniC+= ((unsigned int)(unsigned char)array[i]->character->two & 0b00111111) << 6;
            uniC+= ((unsigned int)(unsigned char)array[i]->character->one & 0b00001111) << 12;
        }
        else if(array[i]->character->two != (char)0){
            uniC= (unsigned int)(unsigned char)array[i]->character->two & 0b00111111;
            uniC+= ((unsigned int)(unsigned char)array[i]->character->one & 0b00111111) << 6;
        }
        else{
            uniC = (unsigned int)(unsigned char)array[i]->character->one;
        }

        wprintf(L"%lc", (wchar_t)uniC );
        wprintf(L"%lc",'-');
        wprintf(L"%lc",'>');
        wprintf(L"%d \n",array[i]->count);
    }
}
