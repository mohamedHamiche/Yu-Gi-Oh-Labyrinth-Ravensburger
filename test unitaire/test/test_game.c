#include "unity.h"
#include "player.h"


void setUp(void) {}
void tearDown(void) {}


void test_lirePseudo_should_returnPseudo(void)
{
    /* Given */
    
    /* When */
    char *resultat = lirePseudo(1);

    /* Then */
    TEST_ASSERT_EQUAL_STRING("Mohamed", resultat);
}

//void test_programVersion_should_returnGoodVersion(void)
//{
    /* Given */

    /* When */
  //  const char* version = programVersion();

    /* Then */
    //TEST_ASSERT_EQUAL_STRING("0.1-SNAPSHOT", version);
//}


int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_lirePseudo_should_returnPseudo);
    //RUN_TEST(test_programVersion_should_returnGoodVersion);
    return UNITY_END();
}
