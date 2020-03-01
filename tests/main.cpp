#include "babkin.h"
#include <gtest/gtest.h>
#include <tuple>

using Babkin64 = Babkin<std::uint64_t>;

struct BabkinTestSuite
    : public ::testing::TestWithParam
    <
        std::tuple
        <
            Babkin64::NBlock,
            Babkin64::CodePair
        >
    >
{
    Babkin64::NBlock input_block;
    Babkin64::CodePair ethalon;
};

TEST_P(BabkinTestSuite, CheckEncodingToPair)
{
    const Babkin64::NBlock& input_block = std::get<0>(GetParam());
    const Babkin64::CodePair& ethalon = std::get<1>(GetParam());
    Babkin64 babkin(input_block.size());
    ASSERT_EQ(babkin.encode(input_block), ethalon);
}

INSTANTIATE_TEST_CASE_P
(
    Babkin,
    BabkinTestSuite,
    ::testing::Values
    (
        std::make_tuple
        (
            Babkin64::NBlock{ 0, 1, 0 },
            Babkin64::CodePair{ 1, 1 }
        ),
        std::make_tuple
        (
            Babkin64::NBlock{ 1, 0, 1, 0 },
            Babkin64::CodePair{ 2, 1 }
        ),
        std::make_tuple
        (
            Babkin64::NBlock{ 0, 0, 0, 0, 0 },
            Babkin64::CodePair{ 0, 0 }
        ),
        std::make_tuple
        (
            Babkin64::NBlock{ 1, 1, 1, 1, 1, 0 },
            Babkin64::CodePair{ 1, 5 }
        ),
        std::make_tuple
        (
            Babkin64::NBlock{ 1, 0, 0, 0, 0, 0, 1 },
            Babkin64::CodePair{ 2, 15 }
        ),
        std::make_tuple
        (
            Babkin64::NBlock{ 1, 1, 1 },
            Babkin64::CodePair{ 0, 0 }
        ),
        std::make_tuple
        (
            Babkin64::NBlock{ 0, 1, 1, 1 },
            Babkin64::CodePair{ 1, 0 }
        ),
        std::make_tuple
        (
            Babkin64::NBlock{ 1, 1, 1, 1, 0 },
            Babkin64::CodePair{ 1, 4 }
        ),
        std::make_tuple
        (
            Babkin64::NBlock{ 1, 1, 1, 0, 1, 1 },
            Babkin64::CodePair{ 1, 3 }
        ),
        std::make_tuple
        (
            Babkin64::NBlock{ 1, 1, 1, 1, 1, 0, 1 },
            Babkin64::CodePair{ 1, 5 }
        ),
        std::make_tuple
        (
            Babkin64::NBlock{ 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1 },
            Babkin64::CodePair{ 5, 402 }
        ),
        std::make_tuple
        (
            Babkin64::NBlock{ 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0 },
            Babkin64::CodePair{ 6, 1482 }
        ),
        std::make_tuple
        (
            Babkin64::NBlock{ 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1 },
            Babkin64::CodePair{ 7, 2106 }
        ),
        std::make_tuple
        (
            Babkin64::NBlock{ 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0 },
            Babkin64::CodePair{ 9, 266214 }
        ),
        std::make_tuple
        (
            Babkin64::NBlock{ 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0 },
            Babkin64::CodePair{ 15, 457204183 }
        ),
        std::make_tuple
        (
            Babkin64::NBlock{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1 },
            Babkin64::CodePair{ 1, 10 }
        ),
        std::make_tuple
        (
            Babkin64::NBlock{ 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0 },
            Babkin64::CodePair{ 5, 2755 }
        ),
        std::make_tuple
        (
            Babkin64::NBlock{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1 },
            Babkin64::CodePair{ 2, 101 }
        ),
        std::make_tuple
        (
            Babkin64::NBlock{ 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0 },
            Babkin64::CodePair{ 7, 99628 }
        ),
        std::make_tuple
        (
            Babkin64::NBlock{ 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1 },
            Babkin64::CodePair{ 7, 1775966 }
        )
    )
);

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
