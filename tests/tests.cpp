#define CATCH_CONFIG_MAIN
#include "linked_list.h"
#include "catch.hpp"

TEST_CASE("Can reverse linked list") {

    SECTION("Can reverse linked list with no elements") {
        LinkedList<int> ll;

        REQUIRE(ll.to_string() == "Empty Linked List");
        ll.reverse();
        REQUIRE(ll.to_string() == "Empty Linked List");
    }
}