
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(GameInstanceTest)
{
  {
    GameInstance gi1 ("GI1", 1, 1);
    GameInstance gi2 ("GI2", 2, 2);
    BOOST_REQUIRE_EQUAL(gi1.getId(), 1);
    BOOST_REQUIRE_EQUAL(gi2.getId(), 2);
    BOOST_REQUIRE_EQUAL(gi1.getName(), "GI1");
    BOOST_REQUIRE_EQUAL(gi2.getName(), "GI2");
    BOOST_REQUIRE_EQUAL(gi1.getPosition().x, 0);
    gi1.setPosition(sf::Vector2i (1,0));
    BOOST_REQUIRE_EQUAL(gi1.getPosition().x, 1);
  }
}
/*
  {
    Exemple ex {};
    ex.setX(21);
    BOOST_CHECK_LE(ex.x, 32); // Less than equal
    BOOST_CHECK_GT(ex.x, 11); // Greater than equl
  }
}
*/
/* vim: set sw=2 sts=2 et : */

BOOST_AUTO_TEST_CASE(TestState)
{
  /*BOOST_CHECK_EQUAL(State::turn,0);
  State::turn += 10;
  BOOST_CHECK_EQUAL(State::turn,10);*/
}