#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mytrit.h"

using testing::Eq;

namespace {
    class ClassDeclaration : public testing::Test  {
    public:
        trit_set::TritSet A;
        ClassDeclaration(){
            A;
        }
    };
}
TEST_F(ClassDeclaration, nameOfTheTest1) {
    A[4] = trit_set::True;
    ASSERT_EQ(4,A.length());
}
