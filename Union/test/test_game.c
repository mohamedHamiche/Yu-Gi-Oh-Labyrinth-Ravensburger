#include "unity.h"
#include "player.h"
#include "pile.h"


void setUp(void) {}
void tearDown(void) {}


void test_lirePseudo_should_return_Pseudo(void)
{
    /* Given */
    int index=1;
    //printf("Donnez Martin comme pseudo\n");
    /* When */
    char *resultat = lirePseudo(index);

    /* Then */
    //TEST_ASSERT_EQUAL_STRING("Martin", resultat);
    TEST_ASSERT_NOT_EMPTY(resultat);
    free(resultat);
}

void test_initJoueurM_should_return_JOUEUR(void)
{
    /* Given */
    int index=1;
    /* When */
    JOUEUR *resultat = initJoueurM(index);

    /* Then */
    TEST_ASSERT_NOT_NULL(resultat); 
    TEST_ASSERT_EQUAL_INT(1,resultat->machine);
    TEST_ASSERT_EQUAL_STRING("Machine 1", resultat->pseudo);
    TEST_ASSERT_NOT_EMPTY(resultat->pseudo);
    TEST_ASSERT_EQUAL_INT(0,resultat->nombre_de_points);
    TEST_ASSERT_NULL(resultat->pile_tresor);

    freeJoueur(resultat);
}

void test_initJoueurH_should_return_JOUEUR(void)
{
    /* Given */
    int index=1;
    /* When */
    JOUEUR *resultat = initJoueurH(index);

    /* Then */
    TEST_ASSERT_NOT_NULL(resultat); 
    TEST_ASSERT_EQUAL_INT(0,resultat->machine);
    TEST_ASSERT_NOT_EMPTY(resultat->pseudo);
    TEST_ASSERT_EQUAL_INT(0,resultat->nombre_de_points);
    TEST_ASSERT_NULL(resultat->pile_tresor);

    freeJoueur(resultat);
}

void test_initTabJoueur_should_return_TabJOUEUR_and_NombreTotal(void)
{
    /* Given */
    
    /* When */
    int nbTotal=0;
    JOUEUR **resultat=NULL;
    resultat= initTabJoueur(&nbTotal);    
    TEST_ASSERT_TRUE(nbTotal>0 && nbTotal <= 4);
    /* Then */
    TEST_ASSERT_NOT_NULL(resultat); 
    for(int i=0; i<nbTotal; i++)
    {
        TEST_ASSERT_NOT_NULL(resultat[i]); 
    }
    for(int i=nbTotal; i<4; i++)        
        TEST_ASSERT_NULL(resultat[i]);

    freeTabJoueur(resultat,nbTotal);
}

void test_initPositions(void)
{
    /* Given */
    int nbTotal=0;
    JOUEUR **tabJoueur=initTabJoueur(&nbTotal);
    /* When */
    initPositions(tabJoueur,nbTotal);

    /* Then */
    TEST_ASSERT_EQUAL_INT(0,tabJoueur[0]->postion_actuelle.x); 
    TEST_ASSERT_EQUAL_INT(0,tabJoueur[0]->postion_actuelle.y); 

    TEST_ASSERT_EQUAL_INT(6,tabJoueur[1]->postion_actuelle.x); 
    TEST_ASSERT_EQUAL_INT(6,tabJoueur[1]->postion_actuelle.y); 

    if(nbTotal == 3)
    {
        TEST_ASSERT_EQUAL_INT(0,tabJoueur[2]->postion_actuelle.x); 
        TEST_ASSERT_EQUAL_INT(6,tabJoueur[2]->postion_actuelle.y); 
    }

    if(nbTotal == 4)
    {
        TEST_ASSERT_EQUAL_INT(6,tabJoueur[3]->postion_actuelle.x); 
        TEST_ASSERT_EQUAL_INT(0,tabJoueur[3]->postion_actuelle.y);  
    }
    printPlayers(tabJoueur,nbTotal);
    freeTabJoueur(tabJoueur,nbTotal);
}

void test_appartientTab_should_return_boolean(void)
{
    /* Given */
    int tab[24]={-1};
    tab[12]= 3;

    /* When */
    int resultat= appartientTab(tab,3);

    /* Then */    
    TEST_ASSERT_EQUAL_INT(1,resultat);
}

void test_randomTresors(void)
{
    /* Given */
    int tab[24]={-1};

    /* When */    
    randomTresors(tab);
    
    /* Then */
    for (int i = 0; i < 24; ++i)
    {
        TEST_ASSERT_TRUE(tab[i]!=-1);
    }
    
}

void test_distribuerCartes(void)
{
    /* Given */
    int nbTotal=0;
    JOUEUR **tabJoueur=initTabJoueur(&nbTotal);
    initPositions(tabJoueur,nbTotal);
    /* When */
    distribuerCartes(tabJoueur,nbTotal);

    /* Then */
    TEST_ASSERT_NOT_NULL(tabJoueur[0]->pile_tresor);
    TEST_ASSERT_NOT_NULL(tabJoueur[1]->pile_tresor);

    if(nbTotal == 3)
    {
        TEST_ASSERT_NOT_NULL(tabJoueur[2]->pile_tresor);
    }

    if(nbTotal == 4)
    {
        TEST_ASSERT_NOT_NULL(tabJoueur[3]->pile_tresor); 
    }
    
    
    freeTabJoueur(tabJoueur,nbTotal);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    //Executer ./bin/player pour voir les affichages
    //Executer ./bin/test_game pour voir le résultat des test 
    //Décommenter pour tester le tout
    
    RUN_TEST(test_lirePseudo_should_return_Pseudo);
    RUN_TEST(test_initJoueurM_should_return_JOUEUR);
    RUN_TEST(test_initJoueurH_should_return_JOUEUR);   
    RUN_TEST(test_initTabJoueur_should_return_TabJOUEUR_and_NombreTotal);
    RUN_TEST(test_initPositions);
    RUN_TEST(test_appartientTab_should_return_boolean);
    RUN_TEST(test_randomTresors);
    RUN_TEST(test_distribuerCartes);

    return UNITY_END();
}