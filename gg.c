
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_SZ 256
// SUBJECT PRONOUNS

struct Creature {
   char  name[50];
   int happy;
   int character_id;
   int health;
   int position;
   char gender; 



};






void create_creature(struct Creature *actor, char* nyame, int def_happy, int cid, int helf, int pos, char gend );
void create_creature(struct Creature *actor, char* nyame, int def_happy, int cid, int helf, int pos, char gend )
{


   strcpy( actor->name, nyame);
   actor->happy = def_happy;
   actor->character_id = cid;
   actor->health = helf;
   actor->position = pos;
   actor->gender = gend;

}





/// dobject is the direct object
void headpat(struct Creature *actor , struct Creature *dobject );
void headpat(struct Creature *actor , struct Creature *dobject )
{

   printf("%s headpats the %s ! %s blushes .\n", actor->name, dobject->name);
   dobject->happy = (dobject->happy) + 5;
}



void tickle(struct Creature *actor , struct Creature *dobject );
void tickle(struct Creature *actor , struct Creature *dobject )
{

   printf("%s tickles the %s ! She giggles a bit .\n", actor->name, dobject->name );
   dobject->happy = (dobject->happy) + 10;
}





/////////////MAIN MAIN MAIN MAIN MAIN/////////////


void main(void){


   static const char *verbs[] = { "pat", "tickle", "kill", "dev", "walk", "wait", "kiss", ""};

   static const char *nouns[] = { "candy", "meowni", "shirt", "skirt", ""};





   char comm[MAX_STR_SZ];
   char string_to_parse[MAX_STR_SZ];
   char *verb_parse;
   char *noun_parse;
   int gamerun;
   int happy;
   int time;
   int kisses;
   int max_creatures;
   int max_verbs;



   kisses = 0; 
   gamerun =1;
   time = 0;
   max_creatures = 255;
   max_verbs = 10;



   struct Creature creatures[max_creatures];

///create_creature(struct Creature *actor, char* nyame, int def_happy, int cid, int helf, int pos )
   create_creature(&creatures[0], "nyaaaa", 100, 0, 10, 0, 'm' );
   create_creature(&creatures[1], "loli", 90, 1, 10, 0, 'f' );
   create_creature(&creatures[2], "shota", 90, 2, 10, 0, 'm' );
















   printf("You see a loli .\nWhat would you like to do ?\n");



   while (gamerun) {
      int verb = 0;
      int noun = 0;

      verb_parse = 0;
      noun_parse = 0;
      time++;

      printf(">>> ");

      fgets(comm, MAX_STR_SZ, stdin);

 //        scanf("%s", comm);  // Note: %s is for char arrays and not %f(floats)
 //        printf("comm = %s, \n",comm);
      strcpy( string_to_parse, comm);


      for( verb = 0; (verb < max_verbs) && (!verb_parse); verb = verb + 1 ){
        verb_parse = strstr(string_to_parse, verbs[verb]);
//            printf("string_to_parse = %s, \n",string_to_parse);




///parse match events

        if (verb_parse){
  //            printf("MEOW\n");


            for( noun = 0; (noun < 3) && (!noun_parse); noun = noun + 1 ){
                noun_parse = strstr(string_to_parse, creatures[noun].name);
     //         printf("creatures[noun].name = %s, \n",creatures[noun].name);


                if (noun_parse){






                  if (verb==0){
                      headpat(&creatures[0], &creatures[noun]);


                  }

                  if (verb==1){
                      tickle(&creatures[0], &creatures[noun]);
                  }

                  if (verb==2){
                      printf("You kill the loli . Fun .\n");
                      gamerun = 0;
                  }

                  if (verb==3){
                      printf("happy = %i, verbs[1] = %s, \n",creatures[1].happy, verbs[1]);
                      creatures[1].happy = creatures[1].happy + 10;

                  }



///stat events

                  if ( creatures[1].happy >99 ){
                      if ( kisses == 0 ) {
                         printf("The loli is so happy that she gives you a hug ~\n");
                         kisses++;
                     }



                     if ((kisses == 1 )&& (creatures[1].happy>150)){
                         printf("The loli is delighted ! She gives you a little kiss ~\n");
                         kisses++;
                     }


                 }  



            } ///noun parse





        } ///for noun


    } /// verb parse



         } /// for verb



     }}



