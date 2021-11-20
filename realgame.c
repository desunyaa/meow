
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_SZ 256
#define MAX_TRAVELABLE_ROOMS 3
#define MAX_ROOMS 10
#define MAX_VERBS 20
#define MAX_NOUNS 20
#define GOD_ID 9999




//////////CREATURE

struct Noun {
	char  name[50];
	char description[500];
	int happy;
	int noun_id;
	int owner_id;
	int health;
	int position; 
	int wielded; 
	char gender[20];
	char subject_pronoun[16]; 
	char object_pronoun[16]; 
	
	char reflexive_pronoun[21]; 
 //  char ip_pronoun[8];
 //   char dp_pronoun[8];  
	int alive;
	int animate;
	int base_cost;
	int damage;
	int defense;

 //  int weight;
  // int size;


};





void create_noun(struct Noun *subject, char* name, int def_happy, int id, int helf, int pos, char* gender, char* subject_pronoun, char* object_pronoun,char* description,
	int base_cost,  int damage,  int defense);


void create_noun(struct Noun *subject, char* name, int def_happy, int id, int helf, int pos, char* gender, char* subject_pronoun, char* object_pronoun,char* description,
	int base_cost,  int damage,  int defense)
{






	strcpy( subject->name, name);
	subject->happy = def_happy;
	subject->noun_id = id;
	subject->owner_id = GOD_ID;
	subject->wielded = 0;
	subject->health = helf;
	if (helf>0){subject->alive = 1;subject->animate = 1;}
	if (helf==0){subject->alive = 0;subject->animate = 0;}
	if (helf<0){subject->alive = 0;subject->animate = 1;}



	subject->position = pos;
	strcpy( subject->gender , gender);
	strcpy( subject->subject_pronoun , subject_pronoun);
	strcpy( subject->object_pronoun , object_pronoun);
	strcpy( subject->description, description);
//reflexive pronouns
	char stringy[25];
	strcpy( stringy, subject->object_pronoun);
	strcat(stringy, "self");
 //  printf("%s",stringy);

	strcpy( subject->reflexive_pronoun, stringy);
//reflexive pronouns end

	subject->base_cost = base_cost;
	subject->damage = damage;
	subject->defense = defense;


}



struct Room {
	char  name[50];
	char description[500];
	int position;

	int travelable_rooms[MAX_TRAVELABLE_ROOMS];




};


void create_room(struct Room *room, char*  name,char* description, int position, int travelable_rooms[]);


void create_room(struct Room *room, char*  name,char* description, int position, int travelable_rooms[])
{

	
	int jeep;



	for( jeep  = 0; jeep<MAX_TRAVELABLE_ROOMS; jeep = jeep + 1){
		room->travelable_rooms[jeep]=GOD_ID;
	}
	for( jeep  = 0; jeep<MAX_TRAVELABLE_ROOMS; jeep = jeep + 1){
		room->travelable_rooms[jeep]=travelable_rooms[jeep];
	}





	strcpy( room->name, name);
	strcpy( room->description, description);
	room->position = position;

}




/////////////////////////////VERB FUNCTIONS
////////////////////////////



void headpat(struct Noun *subject , struct Noun *direct_object );
void headpat(struct Noun *subject , struct Noun *direct_object )
{


	if((subject->position == direct_object->position) && (direct_object->animate == 0)){
		printf("%s headpats the %s ! that was interesting .\n", subject->name, direct_object->name);
		subject->happy = (subject->happy) + 10;
	}

	if((subject->position == direct_object->position) && (direct_object->alive == 1) && (direct_object->animate == 1)){
		printf("%s headpats the %s ! %s blushes .\n", subject->name, direct_object->name, direct_object->subject_pronoun );
		direct_object->happy = (direct_object->happy) + 5;
	}

	if((subject->position == direct_object->position) && (direct_object->alive == 0) && (direct_object->animate == 1)){
		printf("%s headpats the %s's dead body ! that was not very pleasant .\n", subject->name, direct_object->name);
		subject->happy = (subject->happy) - 10;
	}
	

}



void examine_noun(struct Noun *subject , struct Noun *direct_object );
void examine_noun(struct Noun *subject , struct Noun *direct_object )
{
	if((subject->position == direct_object->position) || (subject->noun_id == direct_object->owner_id)){
		printf("%s examines the %s . %s .\n", subject->name, direct_object->name, direct_object->description );

}
}

void examine_room(struct Noun *subject , struct Room *direct_object );
void examine_room(struct Noun *subject , struct Room *direct_object )
{
	if(subject->position == direct_object->position){
		printf("%s examines the %s . %s .\n", subject->name, direct_object->name, direct_object->description );
	}else{printf("%s is not in the %s !\n", subject->name, direct_object->name);}


}

void move(struct Noun *subject , struct Room *direct_object );
void move(struct Noun *subject , struct Room *direct_object )
{

	printf("%s moves to the %s  .\n", subject->name, direct_object->name );
	subject->position = direct_object->position;


}




void give_noun(struct Noun *subject, struct Noun *direct_object, struct Noun *indirect_object);
void give_noun(struct Noun *subject, struct Noun *direct_object, struct Noun *indirect_object)
{

	if((subject->position == indirect_object->position) && (direct_object->owner_id == subject->noun_id)){
		printf("%s gives the %s to %s .\n", subject->name, direct_object->name, indirect_object->name);
		direct_object->owner_id = indirect_object->noun_id;
		direct_object->wielded = 0;
		
		

	}else{printf("You have no %s to give to the %s !\n", direct_object->name, indirect_object->name);}



}



void take_noun(struct Noun *subject, struct Room *room, struct Noun *direct_object);
void take_noun(struct Noun *subject, struct Room *room, struct Noun *direct_object)
{

	if(direct_object->position == subject->position){
		printf("%s takes the %s .\n", subject->name, direct_object->name);
		direct_object->owner_id = subject->noun_id;
		direct_object->position = -1;
		

	}else{printf("There is no %s in the %s !\n", direct_object->name, room->name);}



}




void drop_noun(struct Noun *subject, struct Room *room, struct Noun *direct_object);
void drop_noun(struct Noun *subject, struct Room *room, struct Noun *direct_object)
{

	if((direct_object->owner_id == subject->noun_id)){
		printf("%s drops the %s .\n", subject->name, direct_object->name);
		direct_object->owner_id = GOD_ID;
		direct_object->position = subject->position;
		direct_object->wielded = 0;
		

	}else{printf("%s does not have a %s to drop!\n",subject->name, direct_object->name);}



}


void wield_noun(struct Noun *subject, struct Noun *direct_object);
void wield_noun(struct Noun *subject, struct Noun *direct_object)
{
if((direct_object->wielded == 0) && (direct_object->owner_id == subject->noun_id)){
		printf("%s wields the %s .\n", subject->name, direct_object->name);
		direct_object->wielded = 1;
		
	
	}else{printf("%s does not have a %s in their inventory to wield !\n",subject->name, direct_object->name);}



}

void unwield_noun(struct Noun *subject, struct Noun *direct_object);
void unwield_noun(struct Noun *subject, struct Noun *direct_object)
{

if((direct_object->wielded == 1) && (direct_object->owner_id == subject->owner_id)){
		printf("%s unwields the %s .\n", subject->name, direct_object->name);
		direct_object->wielded = 0;

	}else{printf("%s is not currently wielding a %s !\n",subject->name, direct_object->name);}



}


///add defense
void attack(struct Noun *subject, struct Noun *direct_object,struct Noun * nouns );
void attack(struct Noun *subject, struct Noun *direct_object,struct Noun * nouns )
{

	int damage = 1;
	int jeep;

	if(subject->position == direct_object->position){
		for( jeep  = 0; (strcmp(nouns[jeep].name,"BUFFER NAME")); jeep = jeep + 1){

			if((nouns[jeep].wielded == 1) &&(nouns[jeep].owner_id == subject->noun_id)){
//            printf("nouns[jeep]->damage %d", nouns[jeep].damage);
				damage = damage + nouns[jeep].damage;


			}


		}
		printf("%s does %d damage to %s .\n", subject->name, damage, direct_object->name);
		direct_object->health = direct_object->health - damage;
		printf(" The %s now has %d health .\n", direct_object->name,  direct_object->health);


	}else{printf("%s is not currently in the same room as %s !\n",subject->name, direct_object->name);}



}

void parse(struct Noun * nouns, struct Room * rooms,int gamerun,int time);
void removeStringTrailingNewline(char *str) ;




/////////////MAIN MAIN MAIN MAIN MAIN/////////////


void main(void){




	struct Noun nouns[MAX_NOUNS];
	struct Room rooms[MAX_ROOMS];



	/// arrays holding room connections

	int basement_connections[MAX_TRAVELABLE_ROOMS]; basement_connections[0] = 0; basement_connections[1] = 1; basement_connections[2] = 0;
	int living_room_connections[MAX_TRAVELABLE_ROOMS]; living_room_connections[0] = 1; living_room_connections[1] = 0; living_room_connections[2] = 0;
	int cave_connections[MAX_TRAVELABLE_ROOMS]; living_room_connections[0] = 2; living_room_connections[1] = 3; living_room_connections[2] = 4;
	int narrow_pathway_connections[MAX_TRAVELABLE_ROOMS]; living_room_connections[0] = 3; living_room_connections[1] = 2; living_room_connections[2] = 4;
	int wide_pathway_connections[MAX_TRAVELABLE_ROOMS]; living_room_connections[0] = 4; living_room_connections[1] = 2; living_room_connections[2] = 4;


	int filler = 0;
	for( filler = 0; (filler < MAX_NOUNS) ; filler++ ){
		create_noun(&nouns[filler], "BUFFER NAME", 90, 2, 10, 0, "BUFFER GENDER", "BUFFER S", "BUFFER S", "BUFFER S", 100,  5,  1);


	}

	for( filler = 0; (filler < MAX_ROOMS) ; filler++ ){
		create_room(&rooms[filler], "BUFFER NAME", "BUFFER DESCRIPTION", 999, basement_connections );


	}
	

///void create_noun(struct Noun *subject, char* name, int def_happy, int id, int helf, int pos, char* gender, char* subject_pronoun, char* object_pronoun,char* description,
/// int base_cost,  int damage,  int defense);

	create_noun(&nouns[0], "anon", 100, 0, 10, 0, "m", "I", "me", "look in the mirror !" , 100,  5,  1);
	create_noun(&nouns[1], "loli", 90, 1, 10, 0, "f", "she", "her", "kawaii oneechan", 100,  5,  1);
	create_noun(&nouns[2], "shota", 90, 2, 10, 0, "m", "he", "him", "a cute boy", 100,  5,  1);
	create_noun(&nouns[3], "katana", 90, 3, 0, 0, "n", "it", "it",  "fine sword", 100,  5,  1);
	create_noun(&nouns[4], "kimono", 90, 4, 0, 1, "n", "it", "it", "traditional silk dress", 100,  5,  1);
	create_noun(&nouns[5], "terry", 90, 5, 10, 1, "m", "he", "him", "holy c", 100,  50,  1);











/// create_room(struct Room *room, char*  name,char* description, int position, int travelable_rooms[MAX_TRAVELABLE_ROOMS]);

	create_room(&rooms[0], "basement", "a nice 'basement', decorated with anime posters . there are stairs to the 'living room' ", 0, basement_connections );
	create_room(&rooms[1], "living room", "the 'living room', there are walls of anime figurine displays . stairs lead down to the 'basement' ", 1, living_room_connections );
	create_room(&rooms[2], "cave", "a dark wet cave with a large pool of water in it. there seem to be somewhat developed pathways leading to other parts of the cave. 'narrow pathway' 'wide pathway' ", 2, cave_connections );
	create_room(&rooms[3], "narrow pathway", "meow", 3, narrow_pathway_connections );
	create_room(&rooms[4], "wide pathway", "meow2", 4, wide_pathway_connections );








//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////









	int gamerun; 
	int time;
	gamerun =1;
	time = 0;




 //static const char *nouns[] = { " candy", " meowni", " shirt", " skirt", "", "", "", "", "", ""};


	////////////////// GAME INTROOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO



	printf("You awake .\nWhat would you like to do ?\n");



	while (gamerun) {




		time++;

		parse(nouns, rooms, gamerun,time);




	}}


	void parse(struct Noun * nouns, struct Room * rooms,int gamerun,int time){




		char comm[MAX_STR_SZ];
		char string_to_parse[MAX_STR_SZ];



		
		
		
		char *room_noun_parse;
		
		
	
		char tokenized_parse[20][20];


		
		int room_object = 0;
		int statcounter = 0;
		int tokencounter =0;

		
		room_noun_parse = 0;
		

		
	

	

		static const char *verbs[] = { "pat", "tickle", "kill", "dev", "examine", "go", "take", "drop", "wield", "unwield", "attack", "give", "BUFFER NAME"};
		static const char *prepositions[] = { "to", "for", "BUFFER NAME" };




		printf(">>> ");

		fgets(comm, MAX_STR_SZ, stdin);

 //        scanf("%s", comm);  // Note: %s is for char arrays and not %f(floats)
 //        printf("comm = %s, \n",comm);

		strcpy(string_to_parse, " ");

		strcat(string_to_parse, comm);

///TOKENIZATION
		char * token = strtok(comm, " ");
   // loop through the string to extract all other tokens
		for(tokencounter=0; token != NULL ; tokencounter++) {

			strcpy(tokenized_parse[tokencounter], token);
			removeStringTrailingNewline(tokenized_parse[tokencounter]);

		///	printf("token %d  = %s \n",tokencounter,tokenized_parse[tokencounter]);
			token = strtok(NULL, " ");
		}

   ///TOKENIZATION END

		int i = 0;
		int preposition = 0;
		int preposition_parse = 1;
		int indirect_object_parse = -1;
		int indirect_object = -1;
		int direct_object_parse = -1;
		int direct_object = -1;
		int	verb_parse = -1; /// NULL POINTER
		int verb = -1;
		


for( i = 0; ((i < tokencounter)) ; i++){
 
 	if(verb_parse){

		for( verb = 0;(strcmp(verbs[verb], "BUFFER NAME") && verb_parse); verb = verb + 1 ){
			verb_parse = strcmp(tokenized_parse[i], verbs[verb]);

			printf("verb parse: %d", verb_parse);



	//    printf("string_to_parse = %s, \n",string_to_parse);

		 }verb--; /// for verb

		}


				


			if (!indirect_object_parse){


				for( direct_object = 0; (strcmp(nouns[direct_object].name, "BUFFER NAME") && direct_object_parse); direct_object = direct_object + 1 ){
		 	direct_object_parse = strcmp(tokenized_parse[i], nouns[direct_object].name);
		 	
		 	



			}direct_object--; ///for direct_object end





			}

			if (indirect_object_parse){

			 for( indirect_object = 0; (strcmp(nouns[indirect_object].name, "BUFFER NAME") && indirect_object_parse); indirect_object = indirect_object + 1 ){
		 	indirect_object_parse = strcmp(tokenized_parse[i], nouns[indirect_object].name);
		 	
		 	



			}indirect_object--; ///for direct_object end
		}





}


///printf(" %s SET AS INDIRECT OBJECT \n %s SET AS DIRECT OBJECT \n",nouns[indirect_object].name, nouns[direct_object].name);
if(direct_object_parse){direct_object=indirect_object;}
int indirect_object_parse2 = -1;






		for( i = 0; ((i < tokencounter) && preposition_parse) ; i++){
			printf("token2 %d  = %s \n",i,tokenized_parse[i]);
			for (preposition=0;(strcmp(prepositions[preposition], "BUFFER NAME") && preposition_parse); preposition=preposition+1){


				preposition_parse = (strcmp(prepositions[preposition], tokenized_parse[i]));
	//			printf("preposition_parse = %d \n prepositions[preposition] = %s \n tokenized_parse[i] = %s \n",preposition_parse, prepositions[preposition],tokenized_parse[i]);
				

			}
		}i--;

int x = i;
int indirect_object2 = 0;
if (preposition_parse == 0){


					for( indirect_object2 = 0; (strcmp(nouns[indirect_object2].name, "BUFFER NAME") && indirect_object_parse2); indirect_object2 = indirect_object2 + 1 ){

						x=i;


						for( x ; ((x < tokencounter) && indirect_object_parse2) ; x++ ){
//							 printf("indirect_object_parse = %d \n nouns[indirect_object].name = .%s. \n tokenized_parse[%d] = .%s. \n",indirect_object_parse, nouns[indirect_object].name,x,tokenized_parse[x]);
		 	   indirect_object_parse2 = strcmp(nouns[indirect_object2].name, tokenized_parse[x]);
		 	   if(!indirect_object_parse2 && (indirect_object !=indirect_object2)){

		 	   		direct_object = indirect_object;
		 	   		indirect_object = indirect_object2;






		 	   }
		 

		 }
		 	
		 	



			}




				}


		 


////printf(" %s SET AS INDIRECT OBJECT \n %s SET AS DIRECT OBJECT \n",nouns[indirect_object].name, nouns[direct_object].name);




	



			for( room_object = 0; (strcmp(rooms[room_object].name, "BUFFER NAME") && !room_noun_parse); room_object = room_object + 1 ){
				
				room_noun_parse = strstr(string_to_parse, rooms[room_object].name);
				printf("room_object = %d",room_object);
				



			}room_object--; ///for direct_object end


//		printf("verb = %d indirect object = %d direct object = %d",verb,indirect_object,direct_object);

 ///parse match events

			if (!verb_parse ){
  ///           printf("MEOW\n");
				


				


////	static const char *verbs[] = { " pat", " tickle", " kill", " dev", " examine", " go", " take", " drop", " wield", " unwield", " attack", "BUFFER NAME", ""};
				if (!indirect_object_parse){

					if ((strcmp(verbs[verb], "pat"))==0){
						headpat(&nouns[0], &nouns[direct_object]);


					}

					if ((strcmp(verbs[verb], "kill"))==0){
						printf("You kill the loli . Fun .\n");
						gamerun = 0;
					}

					if ((strcmp(verbs[verb], "dev"))==0){
						printf("happy = %i, verbs[1] = %s, \n",nouns[1].happy, verbs[1]);
						printf("nouns[direct_object].name = %s, \n",nouns[direct_object].name);
						printf(" rooms[0].name %s rooms[0].description %s ! rooms[0].travelable_rooms[1] %d  .\n", rooms[0].name, rooms[0].description, rooms[0].travelable_rooms[1] );
						nouns[1].happy = nouns[1].happy + 10;

					}

					if ((strcmp(verbs[verb], "examine")==0)&& direct_object_parse){
						examine_noun(&nouns[0], &nouns[direct_object]);

					}

					

					

					if ((strcmp(verbs[verb], "take"))==0){
						
						take_noun( &nouns[0], &rooms[nouns[0].position], &nouns[direct_object]);

					}

					if ((strcmp(verbs[verb], "drop"))==0){

						drop_noun( &nouns[0], &rooms[nouns[0].position], &nouns[direct_object]);

					}
					if ((strcmp(verbs[verb], "wield"))==0){

						wield_noun( &nouns[0],  &nouns[direct_object]);

					}
					if ((strcmp(verbs[verb], "unwield"))==0){

						unwield_noun( &nouns[0],  &nouns[direct_object]);

					}

					if ((strcmp(verbs[verb], "attack"))==0){

						attack(&nouns[0], &nouns[direct_object], nouns);

					}

					if ((strcmp(verbs[verb], "give"))==0){

						give_noun(&nouns[0], &nouns[direct_object], &nouns[indirect_object]);

					}



			}  /// if  noun parse end

			if ( room_noun_parse){printf("WAHTTHEHECK %d %d %s",room_object, verb, verbs[verb] );

				if (((strcmp(verbs[verb], "examine"))==0) && room_noun_parse){
					examine_room(&nouns[0], &rooms[room_object]);
		 //           printf("Tss ~\n");

				}

				if ((strcmp(verbs[verb], "go"))==0){

					move(&nouns[0], &rooms[room_object]);
	 //               printf("Tss ~\n");

				}




			}



	} ///if verb parse end



	for( statcounter = 0;(strcmp(nouns[statcounter].name,"BUFFER NAME")); statcounter = statcounter + 1 ){

			///stat events

		if ( (nouns[statcounter].health < 0 ) && (nouns[statcounter].alive == 1)){

			printf("%s has died !\n",nouns[statcounter].name);
			nouns[statcounter].alive = 0;

		}


	   }  ///for stat events


	}








	void removeStringTrailingNewline(char *str) {
  if (str == NULL)
    return;
  int length = strlen(str);
  if ((str[length-1] == '\n') || (str[length-1] == '\n'))
    str[length-1]  = '\0';
}

