#include <gtest/gtest.h>
#include <sstream>
#include "encoder.h"
#include "decoder.h"

class A85Tests : public ::testing::Test {};

TEST_F(A85Tests, EncodeNothingGivesNothing) {
    std::istringstream input("");
    std::ostringstream output;

    encoder(input, output);

    EXPECT_TRUE(output.str().empty());
}

TEST_F(A85Tests, EncodeFourNullsAsZ) {
    std::string zero_block(4, '\0');
    std::istringstream input(zero_block);
    std::ostringstream output;

    encoder(input, output);

    EXPECT_EQ(output.str(), "z");
}

TEST_F(A85Tests, EncodeWordAlpha) {
    std::istringstream input("data");
    std::ostringstream output;

    encoder(input, output);

    EXPECT_EQ(output.str(), "A79Rg");
}

TEST_F(A85Tests, EncodeShortFragment) {
    std::istringstream input("go");
    std::ostringstream output;

    encoder(input, output);

    EXPECT_EQ(output.str(), "B5[");
}

TEST_F(A85Tests, DecodeNothingReturnsNothing) {
    std::istringstream input("");
    std::ostringstream output;

    decoder(input, output);

    EXPECT_TRUE(output.str().empty());
}

TEST_F(A85Tests, DecodeZAsZeros) {
    std::istringstream input("z");
    std::ostringstream output;

    decoder(input, output);

    EXPECT_EQ(output.str(), std::string("\0\0\0\0", 4));
}

TEST_F(A85Tests, DecodeKnownEncodedData) {
    std::istringstream input("A79Rg");
    std::ostringstream output;

    decoder(input, output);

    EXPECT_EQ(output.str(), "data");
}

TEST_F(A85Tests, DecodeShortEncoded) {
    std::istringstream input("B5[");
    std::ostringstream output;

    decoder(input, output);

    EXPECT_EQ(output.str(), "go");
}

TEST_F(A85Tests, EncodeDecodeLoop) {
    const std::string text = "Sample123!";
    std::istringstream input(text);
    std::ostringstream encoded;

    encoder(input, encoded);

    std::istringstream back(encoded.str());
    std::ostringstream decoded;

    decoder(back, decoded);

    EXPECT_EQ(decoded.str(), text);
}

TEST_F(A85Tests, ErrorOnBadCharacter) {
    std::istringstream input("1234\x01");
    std::ostringstream output;

    EXPECT_THROW(decoder(input, output), std::runtime_error);
}

TEST_F(A85Tests, ErrorOnZInWrongPlace) {
    std::istringstream input("A7zRg");
    std::ostringstream output;

    EXPECT_THROW(decoder(input, output), std::runtime_error);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

