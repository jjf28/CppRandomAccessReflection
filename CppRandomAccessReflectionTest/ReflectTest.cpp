#include <gtest/gtest.h>
#include "../CppRandomAccessReflectionLib/Reflect.h"
#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <type_traits>

TEST(ReflectTest, MacroEnumT)
{
    enum_t(TestEnum, uint16_t, {
        first = 1,
        second = 2,
        third = 3
    });
    EXPECT_EQ(sizeof(uint16_t), sizeof(TestEnum));
    EXPECT_EQ(TestEnum::first, 1);
    EXPECT_EQ(TestEnum::second, 2);
    EXPECT_EQ(TestEnum::third, 3);
}

TEST(ReflectTest, MacroCountArguments)
{
    EXPECT_EQ(1, COUNT_ARGUMENTS(a1));
    EXPECT_EQ(2, COUNT_ARGUMENTS(a1,a2));
    EXPECT_EQ(3, COUNT_ARGUMENTS(a1,a2,a3));
    EXPECT_EQ(4, COUNT_ARGUMENTS(a1,a2,a3,a4));
    EXPECT_EQ(5, COUNT_ARGUMENTS(a1,a2,a3,a4,a5));
    EXPECT_EQ(6, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6));
    EXPECT_EQ(7, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7));
    EXPECT_EQ(8, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8));
    EXPECT_EQ(9, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9));
    EXPECT_EQ(10, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10));
    EXPECT_EQ(11, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11));
    EXPECT_EQ(12, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12));
    EXPECT_EQ(13, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13));
    EXPECT_EQ(14, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14));
    EXPECT_EQ(15, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15));
    EXPECT_EQ(16, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16));
    EXPECT_EQ(17, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17));
    EXPECT_EQ(18, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18));
    EXPECT_EQ(19, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19));
    EXPECT_EQ(20, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20));
    EXPECT_EQ(21, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21));
    EXPECT_EQ(22, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22));
    EXPECT_EQ(23, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23));
    EXPECT_EQ(24, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24));
    EXPECT_EQ(25, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25));
    EXPECT_EQ(26, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26));
    EXPECT_EQ(27, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27));
    EXPECT_EQ(28, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28));
    EXPECT_EQ(29, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29));
    EXPECT_EQ(30, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30));
    EXPECT_EQ(31, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31));
    EXPECT_EQ(32, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32));
    EXPECT_EQ(33, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33));
    EXPECT_EQ(34, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34));
    EXPECT_EQ(35, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35));
    EXPECT_EQ(36, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36));
    EXPECT_EQ(37, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37));
    EXPECT_EQ(38, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38));
    EXPECT_EQ(39, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39));
    EXPECT_EQ(40, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40));
    EXPECT_EQ(41, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41));
    EXPECT_EQ(42, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42));
    EXPECT_EQ(43, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43));
    EXPECT_EQ(44, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44));
    EXPECT_EQ(45, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45));
    EXPECT_EQ(46, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46));
    EXPECT_EQ(47, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47));
    EXPECT_EQ(48, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48));
    EXPECT_EQ(49, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49));
    EXPECT_EQ(50, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50));
    EXPECT_EQ(51, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51));
    EXPECT_EQ(52, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52));
    EXPECT_EQ(53, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53));
    EXPECT_EQ(54, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54));
    EXPECT_EQ(55, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55));
    EXPECT_EQ(56, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56));
    EXPECT_EQ(57, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57));
    EXPECT_EQ(58, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58));
    EXPECT_EQ(59, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59));
    EXPECT_EQ(60, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60));
    EXPECT_EQ(61, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61));
    EXPECT_EQ(62, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62));
    EXPECT_EQ(63, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63));
    EXPECT_EQ(64, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64));
    EXPECT_EQ(65, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65));
    EXPECT_EQ(66, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66));
    EXPECT_EQ(67, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67));
    EXPECT_EQ(68, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68));
    EXPECT_EQ(69, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69));
    EXPECT_EQ(70, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70));
    EXPECT_EQ(71, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71));
    EXPECT_EQ(72, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72));
    EXPECT_EQ(73, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73));
    EXPECT_EQ(74, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74));
    EXPECT_EQ(75, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75));
    EXPECT_EQ(76, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76));
    EXPECT_EQ(77, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77));
    EXPECT_EQ(78, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78));
    EXPECT_EQ(79, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79));
    EXPECT_EQ(80, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80));
    EXPECT_EQ(81, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81));
    EXPECT_EQ(82, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82));
    EXPECT_EQ(83, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83));
    EXPECT_EQ(84, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84));
    EXPECT_EQ(85, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85));
    EXPECT_EQ(86, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86));
    EXPECT_EQ(87, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87));
    EXPECT_EQ(88, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88));
    EXPECT_EQ(89, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89));
    EXPECT_EQ(90, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90));
    EXPECT_EQ(91, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91));
    EXPECT_EQ(92, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92));
    EXPECT_EQ(93, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93));
    EXPECT_EQ(94, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94));
    EXPECT_EQ(95, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95));
    EXPECT_EQ(96, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96));
    EXPECT_EQ(97, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97));
    EXPECT_EQ(98, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98));
    EXPECT_EQ(99, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99));
    EXPECT_EQ(100, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100));
    EXPECT_EQ(101, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101));
    EXPECT_EQ(102, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102));
    EXPECT_EQ(103, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103));
    EXPECT_EQ(104, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104));
    EXPECT_EQ(105, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105));
    EXPECT_EQ(106, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106));
    EXPECT_EQ(107, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107));
    EXPECT_EQ(108, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108));
    EXPECT_EQ(109, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109));
    EXPECT_EQ(110, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110));
    EXPECT_EQ(111, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111));
    EXPECT_EQ(112, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112));
    EXPECT_EQ(113, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113));
    EXPECT_EQ(114, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114));
    EXPECT_EQ(115, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115));
    EXPECT_EQ(116, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115,a116));
    EXPECT_EQ(117, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115,a116,a117));
    EXPECT_EQ(118, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115,a116,a117,a118));
    EXPECT_EQ(119, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115,a116,a117,a118,a119));
    EXPECT_EQ(120, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115,a116,a117,a118,a119,a120));
    EXPECT_EQ(121, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115,a116,a117,a118,a119,a120,
        a121));
    EXPECT_EQ(122, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115,a116,a117,a118,a119,a120,
        a121,a122));
    EXPECT_EQ(123, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115,a116,a117,a118,a119,a120,
        a121,a122,a123));
    EXPECT_EQ(124, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115,a116,a117,a118,a119,a120,
        a121,a122,a123,a124));
    EXPECT_EQ(125, COUNT_ARGUMENTS(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115,a116,a117,a118,a119,a120,
        a121,a122,a123,a124,a125));
}

TEST(ReflectTest, MacroForEach)
{
    std::vector<std::string> test;

#define TEST_PUSH_BACK_STR(str) test.push_back(#str);

    FOR_EACH(TEST_PUSH_BACK_STR, a1);
    EXPECT_EQ(1, test.size()); for ( size_t i=0; i<1; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2);
    EXPECT_EQ(2, test.size()); for ( size_t i=0; i<2; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3);
    EXPECT_EQ(3, test.size()); for ( size_t i=0; i<3; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4);
    EXPECT_EQ(4, test.size()); for ( size_t i=0; i<4; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5);
    EXPECT_EQ(5, test.size()); for ( size_t i=0; i<5; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6);
    EXPECT_EQ(6, test.size()); for ( size_t i=0; i<6; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7);
    EXPECT_EQ(7, test.size()); for ( size_t i=0; i<7; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8);
    EXPECT_EQ(8, test.size()); for ( size_t i=0; i<8; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9);
    EXPECT_EQ(9, test.size()); for ( size_t i=0; i<9; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);
    EXPECT_EQ(10, test.size()); for ( size_t i=0; i<10; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11);
    EXPECT_EQ(11, test.size()); for ( size_t i=0; i<11; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12);
    EXPECT_EQ(12, test.size()); for ( size_t i=0; i<12; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13);
    EXPECT_EQ(13, test.size()); for ( size_t i=0; i<13; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14);
    EXPECT_EQ(14, test.size()); for ( size_t i=0; i<14; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15);
    EXPECT_EQ(15, test.size()); for ( size_t i=0; i<15; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16);
    EXPECT_EQ(16, test.size()); for ( size_t i=0; i<16; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17);
    EXPECT_EQ(17, test.size()); for ( size_t i=0; i<17; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18);
    EXPECT_EQ(18, test.size()); for ( size_t i=0; i<18; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19);
    EXPECT_EQ(19, test.size()); for ( size_t i=0; i<19; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20);
    EXPECT_EQ(20, test.size()); for ( size_t i=0; i<20; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21);
    EXPECT_EQ(21, test.size()); for ( size_t i=0; i<21; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22);
    EXPECT_EQ(22, test.size()); for ( size_t i=0; i<22; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23);
    EXPECT_EQ(23, test.size()); for ( size_t i=0; i<23; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24);
    EXPECT_EQ(24, test.size()); for ( size_t i=0; i<24; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25);
    EXPECT_EQ(25, test.size()); for ( size_t i=0; i<25; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26);
    EXPECT_EQ(26, test.size()); for ( size_t i=0; i<26; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27);
    EXPECT_EQ(27, test.size()); for ( size_t i=0; i<27; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28);
    EXPECT_EQ(28, test.size()); for ( size_t i=0; i<28; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29);
    EXPECT_EQ(29, test.size()); for ( size_t i=0; i<29; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30);
    EXPECT_EQ(30, test.size()); for ( size_t i=0; i<30; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31);
    EXPECT_EQ(31, test.size()); for ( size_t i=0; i<31; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32);
    EXPECT_EQ(32, test.size()); for ( size_t i=0; i<32; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33);
    EXPECT_EQ(33, test.size()); for ( size_t i=0; i<33; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34);
    EXPECT_EQ(34, test.size()); for ( size_t i=0; i<34; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35);
    EXPECT_EQ(35, test.size()); for ( size_t i=0; i<35; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36);
    EXPECT_EQ(36, test.size()); for ( size_t i=0; i<36; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37);
    EXPECT_EQ(37, test.size()); for ( size_t i=0; i<37; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38);
    EXPECT_EQ(38, test.size()); for ( size_t i=0; i<38; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39);
    EXPECT_EQ(39, test.size()); for ( size_t i=0; i<39; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40);
    EXPECT_EQ(40, test.size()); for ( size_t i=0; i<40; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41);
    EXPECT_EQ(41, test.size()); for ( size_t i=0; i<41; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42);
    EXPECT_EQ(42, test.size()); for ( size_t i=0; i<42; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43);
    EXPECT_EQ(43, test.size()); for ( size_t i=0; i<43; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44);
    EXPECT_EQ(44, test.size()); for ( size_t i=0; i<44; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45);
    EXPECT_EQ(45, test.size()); for ( size_t i=0; i<45; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46);
    EXPECT_EQ(46, test.size()); for ( size_t i=0; i<46; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47);
    EXPECT_EQ(47, test.size()); for ( size_t i=0; i<47; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48);
    EXPECT_EQ(48, test.size()); for ( size_t i=0; i<48; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49);
    EXPECT_EQ(49, test.size()); for ( size_t i=0; i<49; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50);
    EXPECT_EQ(50, test.size()); for ( size_t i=0; i<50; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51);
    EXPECT_EQ(51, test.size()); for ( size_t i=0; i<51; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52);
    EXPECT_EQ(52, test.size()); for ( size_t i=0; i<52; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53);
    EXPECT_EQ(53, test.size()); for ( size_t i=0; i<53; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54);
    EXPECT_EQ(54, test.size()); for ( size_t i=0; i<54; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55);
    EXPECT_EQ(55, test.size()); for ( size_t i=0; i<55; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56);
    EXPECT_EQ(56, test.size()); for ( size_t i=0; i<56; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57);
    EXPECT_EQ(57, test.size()); for ( size_t i=0; i<57; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58);
    EXPECT_EQ(58, test.size()); for ( size_t i=0; i<58; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59);
    EXPECT_EQ(59, test.size()); for ( size_t i=0; i<59; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60);
    EXPECT_EQ(60, test.size()); for ( size_t i=0; i<60; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61);
    EXPECT_EQ(61, test.size()); for ( size_t i=0; i<61; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62);
    EXPECT_EQ(62, test.size()); for ( size_t i=0; i<62; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63);
    EXPECT_EQ(63, test.size()); for ( size_t i=0; i<63; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64);
    EXPECT_EQ(64, test.size()); for ( size_t i=0; i<64; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65);
    EXPECT_EQ(65, test.size()); for ( size_t i=0; i<65; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66);
    EXPECT_EQ(66, test.size()); for ( size_t i=0; i<66; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67);
    EXPECT_EQ(67, test.size()); for ( size_t i=0; i<67; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68);
    EXPECT_EQ(68, test.size()); for ( size_t i=0; i<68; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69);
    EXPECT_EQ(69, test.size()); for ( size_t i=0; i<69; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70);
    EXPECT_EQ(70, test.size()); for ( size_t i=0; i<70; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71);
    EXPECT_EQ(71, test.size()); for ( size_t i=0; i<71; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72);
    EXPECT_EQ(72, test.size()); for ( size_t i=0; i<72; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73);
    EXPECT_EQ(73, test.size()); for ( size_t i=0; i<73; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74);
    EXPECT_EQ(74, test.size()); for ( size_t i=0; i<74; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75);
    EXPECT_EQ(75, test.size()); for ( size_t i=0; i<75; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76);
    EXPECT_EQ(76, test.size()); for ( size_t i=0; i<76; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77);
    EXPECT_EQ(77, test.size()); for ( size_t i=0; i<77; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78);
    EXPECT_EQ(78, test.size()); for ( size_t i=0; i<78; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79);
    EXPECT_EQ(79, test.size()); for ( size_t i=0; i<79; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80);
    EXPECT_EQ(80, test.size()); for ( size_t i=0; i<80; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81);
    EXPECT_EQ(81, test.size()); for ( size_t i=0; i<81; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82);
    EXPECT_EQ(82, test.size()); for ( size_t i=0; i<82; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83);
    EXPECT_EQ(83, test.size()); for ( size_t i=0; i<83; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84);
    EXPECT_EQ(84, test.size()); for ( size_t i=0; i<84; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85);
    EXPECT_EQ(85, test.size()); for ( size_t i=0; i<85; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86);
    EXPECT_EQ(86, test.size()); for ( size_t i=0; i<86; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87);
    EXPECT_EQ(87, test.size()); for ( size_t i=0; i<87; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88);
    EXPECT_EQ(88, test.size()); for ( size_t i=0; i<88; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89);
    EXPECT_EQ(89, test.size()); for ( size_t i=0; i<89; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90);
    EXPECT_EQ(90, test.size()); for ( size_t i=0; i<90; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91);
    EXPECT_EQ(91, test.size()); for ( size_t i=0; i<91; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92);
    EXPECT_EQ(92, test.size()); for ( size_t i=0; i<92; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93);
    EXPECT_EQ(93, test.size()); for ( size_t i=0; i<93; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94);
    EXPECT_EQ(94, test.size()); for ( size_t i=0; i<94; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95);
    EXPECT_EQ(95, test.size()); for ( size_t i=0; i<95; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96);
    EXPECT_EQ(96, test.size()); for ( size_t i=0; i<96; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97);
    EXPECT_EQ(97, test.size()); for ( size_t i=0; i<97; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98);
    EXPECT_EQ(98, test.size()); for ( size_t i=0; i<98; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99);
    EXPECT_EQ(99, test.size()); for ( size_t i=0; i<99; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100);
    EXPECT_EQ(100, test.size()); for ( size_t i=0; i<100; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101);
    EXPECT_EQ(101, test.size()); for ( size_t i=0; i<101; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102);
    EXPECT_EQ(102, test.size()); for ( size_t i=0; i<102; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103);
    EXPECT_EQ(103, test.size()); for ( size_t i=0; i<103; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104);
    EXPECT_EQ(104, test.size()); for ( size_t i=0; i<104; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105);
    EXPECT_EQ(105, test.size()); for ( size_t i=0; i<105; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106);
    EXPECT_EQ(106, test.size()); for ( size_t i=0; i<106; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107);
    EXPECT_EQ(107, test.size()); for ( size_t i=0; i<107; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108);
    EXPECT_EQ(108, test.size()); for ( size_t i=0; i<108; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109);
    EXPECT_EQ(109, test.size()); for ( size_t i=0; i<109; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110);
    EXPECT_EQ(110, test.size()); for ( size_t i=0; i<110; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111);
    EXPECT_EQ(111, test.size()); for ( size_t i=0; i<111; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112);
    EXPECT_EQ(112, test.size()); for ( size_t i=0; i<112; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113);
    EXPECT_EQ(113, test.size()); for ( size_t i=0; i<113; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114);
    EXPECT_EQ(114, test.size()); for ( size_t i=0; i<114; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115);
    EXPECT_EQ(115, test.size()); for ( size_t i=0; i<115; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115,a116);
    EXPECT_EQ(116, test.size()); for ( size_t i=0; i<116; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115,a116,a117);
    EXPECT_EQ(117, test.size()); for ( size_t i=0; i<117; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115,a116,a117,a118);
    EXPECT_EQ(118, test.size()); for ( size_t i=0; i<118; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115,a116,a117,a118,a119);
    EXPECT_EQ(119, test.size()); for ( size_t i=0; i<119; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115,a116,a117,a118,a119,a120);
    EXPECT_EQ(120, test.size()); for ( size_t i=0; i<120; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115,a116,a117,a118,a119,a120,
        a121);
    EXPECT_EQ(121, test.size()); for ( size_t i=0; i<121; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115,a116,a117,a118,a119,a120,
        a121,a122);
    EXPECT_EQ(122, test.size()); for ( size_t i=0; i<122; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115,a116,a117,a118,a119,a120,
        a121,a122,a123);
    EXPECT_EQ(123, test.size()); for ( size_t i=0; i<123; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115,a116,a117,a118,a119,a120,
        a121,a122,a123,a124);
    EXPECT_EQ(124, test.size()); for ( size_t i=0; i<124; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
    FOR_EACH(TEST_PUSH_BACK_STR, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
        a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
        a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
        a91,a92,a93,a94,a95,a96,a97,a98,a99,a100,a101,a102,a103,a104,a105,a106,a107,a108,a109,a110,a111,a112,a113,a114,a115,a116,a117,a118,a119,a120,
        a121,a122,a123,a124,a125);
    EXPECT_EQ(125, test.size()); for ( size_t i=0; i<125; i++ ) EXPECT_STREQ(std::string("a" + std::to_string(i+1)).c_str(), test[i].c_str()); test.clear();
}

TEST(ReflectTest, MacroLhs)
{
    bool lhs = false;
    bool rhs = true;
    bool lhsResult = LHS((lhs) rhs);
    EXPECT_EQ(lhs, lhsResult);
}

TEST(ReflectTest, MacroRhs)
{
    bool lhs = false;
    bool rhs = true;
    bool rhsResult = RHS((lhs) rhs);
    EXPECT_EQ(rhs, rhsResult);
}

TEST(ReflectTest, ConstexprStrSubstr)
{
    EXPECT_STREQ("a", ConstexprStr::substr<1>("abcdef").value);
    EXPECT_STREQ("ab", ConstexprStr::substr<2>("abcdef").value);
    EXPECT_STREQ("abc", ConstexprStr::substr<3>("abcdef").value);
    EXPECT_STREQ("abcd", ConstexprStr::substr<4>("abcdef").value);
    EXPECT_STREQ("abcde", ConstexprStr::substr<5>("abcdef").value);
    EXPECT_STREQ("abcdef", ConstexprStr::substr<6>("abcdef").value);
    
    EXPECT_STREQ("b", ConstexprStr::substr<1>("abcdef"+1).value);
    EXPECT_STREQ("bc", ConstexprStr::substr<2>("abcdef"+1).value);
    EXPECT_STREQ("bcd", ConstexprStr::substr<3>("abcdef"+1).value);
    EXPECT_STREQ("bcde", ConstexprStr::substr<4>("abcdef"+1).value);
    EXPECT_STREQ("bcdef", ConstexprStr::substr<5>("abcdef"+1).value);
    
    EXPECT_STREQ("c", ConstexprStr::substr<1>("abcdef"+2).value);
    EXPECT_STREQ("cd", ConstexprStr::substr<2>("abcdef"+2).value);
    EXPECT_STREQ("cde", ConstexprStr::substr<3>("abcdef"+2).value);
    EXPECT_STREQ("cdef", ConstexprStr::substr<4>("abcdef"+2).value);
    
    EXPECT_STREQ("d", ConstexprStr::substr<1>("abcdef"+3).value);
    EXPECT_STREQ("de", ConstexprStr::substr<2>("abcdef"+3).value);
    EXPECT_STREQ("def", ConstexprStr::substr<3>("abcdef"+3).value);

    EXPECT_STREQ("e", ConstexprStr::substr<1>("abcdef"+4).value);
    EXPECT_STREQ("ef", ConstexprStr::substr<2>("abcdef"+4).value);

    EXPECT_STREQ("f", ConstexprStr::substr<1>("abcdef"+5).value);
}

TEST(ReflectTest, ConstexprStrLengthBetween)
{
    EXPECT_EQ(0, ConstexprStr::length_between("<>", '<', '>'));
    EXPECT_EQ(1, ConstexprStr::length_between("<1>", '<', '>'));
    EXPECT_EQ(2, ConstexprStr::length_between("<12>", '<', '>'));
    EXPECT_EQ(3, ConstexprStr::length_between("<123>", '<', '>'));
    EXPECT_EQ(4, ConstexprStr::length_between("<1234>", '<', '>'));

    EXPECT_EQ(2, ConstexprStr::length_between("<<>>", '<', '>'));
    EXPECT_EQ(3, ConstexprStr::length_between("<<1>>", '<', '>'));
    EXPECT_EQ(4, ConstexprStr::length_between("<<12>>", '<', '>'));
    EXPECT_EQ(5, ConstexprStr::length_between("<<123>>", '<', '>'));
    EXPECT_EQ(6, ConstexprStr::length_between("<<1234>>", '<', '>'));
}

TEST(ReflectTest, ConstexprStrLengthAfterLast)
{
    EXPECT_EQ(0, ConstexprStr::length_after_last("a b ", ' '));
    EXPECT_EQ(1, ConstexprStr::length_after_last("a b 1", ' '));
    EXPECT_EQ(2, ConstexprStr::length_after_last("a b 12", ' '));
    EXPECT_EQ(3, ConstexprStr::length_after_last("a b 123", ' '));
}

TEST(ReflectTest, ConstexprStrFind)
{
    EXPECT_EQ(0, ConstexprStr::find("abcdefabcdef", 'a'));
    EXPECT_EQ(1, ConstexprStr::find("abcdefabcdef", 'b'));
    EXPECT_EQ(2, ConstexprStr::find("abcdefabcdef", 'c'));
    EXPECT_EQ(3, ConstexprStr::find("abcdefabcdef", 'd'));
    EXPECT_EQ(4, ConstexprStr::find("abcdefabcdef", 'e'));
    EXPECT_EQ(5, ConstexprStr::find("abcdefabcdef", 'f'));
}

TEST(ReflectTest, ConstexprStrFindLastOf)
{
    EXPECT_EQ(6, ConstexprStr::find_last_of("abcdefabcdef", 'a'));
    EXPECT_EQ(7, ConstexprStr::find_last_of("abcdefabcdef", 'b'));
    EXPECT_EQ(8, ConstexprStr::find_last_of("abcdefabcdef", 'c'));
    EXPECT_EQ(9, ConstexprStr::find_last_of("abcdefabcdef", 'd'));
    EXPECT_EQ(10, ConstexprStr::find_last_of("abcdefabcdef", 'e'));
    EXPECT_EQ(11, ConstexprStr::find_last_of("abcdefabcdef", 'f'));
}

TEST(ReflectTest, TypeToStr)
{
    EXPECT_STREQ("int", RfS::TypeToStr<int>::Get().value);

    // Expecting some junk like how it's a struct or class, but it should still contain the pair text
    auto pairStrStruct = RfS::TypeToStr<std::pair<int,int>>::Get();
    std::string typeStr = pairStrStruct.value;
    typeStr.erase(std::remove(typeStr.begin(), typeStr.end(), ' '), typeStr.end());
    EXPECT_TRUE(typeStr.find("pair<int,int") != std::string::npos);

    // Expecting some junk like how it's a struct or class and what allocator it's using, but should contain the map text
    auto mapStrStruct = RfS::TypeToStr<std::map<int,int>>::Get();
    std::string mapStr = mapStrStruct.value;
    mapStr.erase(std::remove(mapStr.begin(), mapStr.end(), ' '), mapStr.end());
    EXPECT_TRUE(mapStr.find("map<int,int") != std::string::npos);
}

TEST(ReflectTest, IsPointable)
{
    EXPECT_FALSE(RfS::is_pointable<int>::value);
    EXPECT_FALSE(RfS::is_pointable<int[2]>::value);
    EXPECT_TRUE(RfS::is_pointable<int*>::value);
    EXPECT_TRUE(RfS::is_pointable<std::shared_ptr<int>>::value);
    EXPECT_TRUE(RfS::is_pointable<std::unique_ptr<int>>::value);
}

TEST(ReflectTest, RemovePointer)
{
    bool isEqual = std::is_same<int, RfS::remove_pointer<int>::type>::value;
    EXPECT_TRUE(isEqual);
    isEqual = std::is_same<int[2], RfS::remove_pointer<int[2]>::type>::value;
    EXPECT_TRUE(isEqual);
    isEqual = std::is_same<int, RfS::remove_pointer<int*>::type>::value;
    EXPECT_TRUE(isEqual);
    isEqual = std::is_same<int, RfS::remove_pointer<std::shared_ptr<int>>::type>::value;
    EXPECT_TRUE(isEqual);
    isEqual = std::is_same<int, RfS::remove_pointer<std::unique_ptr<int>>::type>::value;
    EXPECT_TRUE(isEqual);
}

TEST(ReflectTest, IsStlIterable)
{
    EXPECT_FALSE(RfS::is_stl_iterable<int>::value);
    EXPECT_FALSE(RfS::is_stl_iterable<int*>::value);
    EXPECT_FALSE(RfS::is_stl_iterable<int[2]>::value);
    using ExampleArrayType = std::array<int, 2>;
    EXPECT_TRUE(RfS::is_stl_iterable<ExampleArrayType>::value);
    EXPECT_TRUE(RfS::is_stl_iterable<std::vector<int>>::value);
    EXPECT_TRUE(RfS::is_stl_iterable<std::deque<int>>::value);
    EXPECT_TRUE(RfS::is_stl_iterable<std::forward_list<int>>::value);
    EXPECT_TRUE(RfS::is_stl_iterable<std::list<int>>::value);
    
    EXPECT_FALSE(RfS::is_stl_iterable<std::stack<int>>::value);
    EXPECT_FALSE(RfS::is_stl_iterable<std::queue<int>>::value);
    EXPECT_FALSE(RfS::is_stl_iterable<std::priority_queue<int>>::value);

    EXPECT_TRUE(RfS::is_stl_iterable<std::set<int>>::value);
    EXPECT_TRUE(RfS::is_stl_iterable<std::multiset<int>>::value);
    using ExampleMapType = std::map<int, int>;
    EXPECT_TRUE(RfS::is_stl_iterable<ExampleMapType>::value);
    using ExampleMultiMapType = std::multimap<int, int>;
    EXPECT_TRUE(RfS::is_stl_iterable<ExampleMultiMapType>::value);
    EXPECT_TRUE(RfS::is_stl_iterable<std::unordered_set<int>>::value);
    EXPECT_TRUE(RfS::is_stl_iterable<std::unordered_multiset<int>>::value);
    using ExampleUnorderedMapType = std::map<int, int>;
    EXPECT_TRUE(RfS::is_stl_iterable<ExampleUnorderedMapType>::value);
    using ExampleUnorderedMultiMapType = std::multimap<int, int>;
    EXPECT_TRUE(RfS::is_stl_iterable<ExampleUnorderedMultiMapType>::value);
}

TEST(ReflectTest, IsAdaptor)
{
    EXPECT_FALSE(RfS::is_adaptor<int>::value);
    EXPECT_FALSE(RfS::is_adaptor<std::vector<int>>::value);
    EXPECT_TRUE(RfS::is_adaptor<std::stack<int>>::value);
    EXPECT_TRUE(RfS::is_adaptor<std::queue<int>>::value);
    EXPECT_TRUE(RfS::is_adaptor<std::priority_queue<int>>::value);
}

TEST(ReflectTest, ContainsPointables)
{
    EXPECT_FALSE(RfS::contains_pointables<int>::value);
    EXPECT_FALSE(RfS::contains_pointables<int[2]>::value);
    EXPECT_FALSE(RfS::contains_pointables<std::vector<int>>::value);
    EXPECT_FALSE(RfS::contains_pointables<std::queue<int>>::value);
    EXPECT_FALSE(RfS::contains_pointables<std::set<int>>::value);

    EXPECT_FALSE(RfS::contains_pointables<int*>::value);
    EXPECT_TRUE(RfS::contains_pointables<int*[2]>::value);
    EXPECT_TRUE(RfS::contains_pointables<std::vector<int*>>::value);
    EXPECT_TRUE(RfS::contains_pointables<std::queue<int*>>::value);
    EXPECT_TRUE(RfS::contains_pointables<std::set<int*>>::value);

    EXPECT_FALSE(RfS::contains_pointables<std::shared_ptr<int>>::value);
    EXPECT_TRUE(RfS::contains_pointables<std::shared_ptr<int>[2]>::value);
    EXPECT_TRUE(RfS::contains_pointables<std::vector<std::shared_ptr<int>>>::value);
    EXPECT_TRUE(RfS::contains_pointables<std::queue<std::shared_ptr<int>>>::value);
    EXPECT_TRUE(RfS::contains_pointables<std::set<std::shared_ptr<int>>>::value);

    EXPECT_FALSE(RfS::contains_pointables<std::unique_ptr<int>>::value);
    EXPECT_TRUE(RfS::contains_pointables<std::unique_ptr<int>[2]>::value);
    EXPECT_TRUE(RfS::contains_pointables<std::vector<std::unique_ptr<int>>>::value);
    EXPECT_TRUE(RfS::contains_pointables<std::queue<std::unique_ptr<int>>>::value);
    EXPECT_TRUE(RfS::contains_pointables<std::set<std::unique_ptr<int>>>::value);
}

TEST(ReflectTest, ElementType)
{
    bool isEqual = std::is_same<void, RfS::element_type<int>::type>::value;
    EXPECT_TRUE(isEqual);
    isEqual = std::is_same<void, RfS::element_type<int*>::type>::value;
    EXPECT_TRUE(isEqual);
    isEqual = std::is_same<int, RfS::element_type<int[2]>::type>::value;
    EXPECT_TRUE(isEqual);
    isEqual = std::is_same<int, RfS::element_type<std::vector<int>>::type>::value;
    EXPECT_TRUE(isEqual);
}

TEST(ReflectTest, KeyType)
{
    bool isEqual = std::is_same<void, RfS::key_type<int>::type>::value;
    EXPECT_TRUE(isEqual);
    isEqual = std::is_same<void, RfS::key_type<int*>::type>::value;
    EXPECT_TRUE(isEqual);
    isEqual = std::is_same<void, RfS::key_type<int[2]>::type>::value;
    EXPECT_TRUE(isEqual);
    isEqual = std::is_same<void, RfS::key_type<std::vector<int>>::type>::value;
    EXPECT_TRUE(isEqual);
    isEqual = std::is_same<int, RfS::key_type<std::set<int>>::type>::value;
    EXPECT_TRUE(isEqual);
    isEqual = std::is_same<int, RfS::key_type<std::multiset<int>>::type>::value;
    EXPECT_TRUE(isEqual);
    
    using ExampleMapType = std::map<int, short>;
    isEqual = std::is_same<int, RfS::key_type<ExampleMapType>::type>::value;
    EXPECT_TRUE(isEqual);
    using ExampleMultiMapType = std::multimap<int, short>;
    isEqual = std::is_same<int, RfS::key_type<ExampleMultiMapType>::type>::value;
    EXPECT_TRUE(isEqual);
}

TEST(ReflectTest, ContainsPairs)
{
    using IntPair = std::pair<int, int>;
    EXPECT_FALSE(RfS::contains_pairs<int>::value);
    EXPECT_FALSE(RfS::contains_pairs<int*>::value);
    EXPECT_FALSE(RfS::contains_pairs<int[]>::value);
    EXPECT_FALSE(RfS::contains_pairs<int*[]>::value);
    EXPECT_FALSE(RfS::contains_pairs<std::vector<int>>::value);

    EXPECT_TRUE(RfS::contains_pairs<IntPair[2]>::value);
    EXPECT_TRUE(RfS::contains_pairs<std::vector<IntPair>>::value);
    using ExampleMapType = std::map<int, short>;
    EXPECT_TRUE(RfS::contains_pairs<ExampleMapType>::value);
    using ExampleMultiMapType = std::multimap<int, short>;
    EXPECT_TRUE(RfS::contains_pairs<ExampleMultiMapType>::value);
}

TEST(ReflectTest, IfVoid)
{
    using intType = RfS::if_void<int, float>::type;
    bool isIntType = std::is_same<int, intType>::value;
    EXPECT_TRUE(isIntType);

    using charType = RfS::if_void<char, void>::type;
    bool isCharType = std::is_same<char, charType>::value;
    EXPECT_TRUE(isCharType);

    using floatType = RfS::if_void<void, float>::type;
    bool isFloatType = std::is_same<float, floatType>::value;
    EXPECT_TRUE(isFloatType);

    using voidType = RfS::if_void<void, void>::type;
    bool isVoidType = std::is_same<void, voidType>::value;
    EXPECT_TRUE(isVoidType);
}

TEST(ReflectTest, GetUnderlyingContainer)
{
    // Stacks
    std::stack<int> defaultStack;
    defaultStack.push(0);
    defaultStack.push(1);
    auto stackDefaultUnderlyingContainer = RfS::get_underlying_container(defaultStack);
    EXPECT_EQ(0, *stackDefaultUnderlyingContainer.begin());
    EXPECT_EQ(1, *++stackDefaultUnderlyingContainer.begin());

    std::stack<int, std::vector<int>> vectorStack;
    vectorStack.push(2);
    vectorStack.push(3);
    auto stackUnderlyingVector = RfS::get_underlying_container(vectorStack);
    bool isEqual = std::is_same<std::vector<int>, decltype(stackUnderlyingVector)>::value;
    EXPECT_TRUE(isEqual);
    EXPECT_EQ(2, *stackUnderlyingVector.begin());
    EXPECT_EQ(3, *++stackUnderlyingVector.begin());

    std::stack<int, std::deque<int>> dequeStack;
    dequeStack.push(4);
    dequeStack.push(5);
    auto stackUnderlyingDeque = RfS::get_underlying_container(dequeStack);
    isEqual = std::is_same<std::deque<int>, decltype(stackUnderlyingDeque)>::value;
    EXPECT_TRUE(isEqual);
    EXPECT_EQ(4, *stackUnderlyingDeque.begin());
    EXPECT_EQ(5, *++stackUnderlyingDeque.begin());

    std::stack<int, std::list<int>> listStack;
    listStack.push(6);
    listStack.push(7);
    auto stackUnderlyingList = RfS::get_underlying_container(listStack);
    isEqual = std::is_same<std::list<int>, decltype(stackUnderlyingList)>::value;
    EXPECT_TRUE(isEqual);
    EXPECT_EQ(6, *stackUnderlyingList.begin());
    EXPECT_EQ(7, *++stackUnderlyingList.begin());
    
    // Queues
    std::queue<int> defaultQueue;
    defaultQueue.push(0);
    defaultQueue.push(1);
    auto queueDefaultUnderlyingContainer = RfS::get_underlying_container(defaultQueue);
    EXPECT_EQ(0, *queueDefaultUnderlyingContainer.begin());
    EXPECT_EQ(1, *++queueDefaultUnderlyingContainer.begin());

    std::queue<int, std::vector<int>> vectorQueue;
    vectorQueue.push(2);
    vectorQueue.push(3);
    auto queueUnderlyingVector = RfS::get_underlying_container(vectorQueue);
    isEqual = std::is_same<std::vector<int>, decltype(queueUnderlyingVector)>::value;
    EXPECT_TRUE(isEqual);
    EXPECT_EQ(2, *queueUnderlyingVector.begin());
    EXPECT_EQ(3, *++queueUnderlyingVector.begin());

    std::queue<int, std::deque<int>> dequeQueue;
    dequeQueue.push(4);
    dequeQueue.push(5);
    auto queueUnderlyingDeque = RfS::get_underlying_container(dequeQueue);
    isEqual = std::is_same<std::deque<int>, decltype(queueUnderlyingDeque)>::value;
    EXPECT_TRUE(isEqual);
    EXPECT_EQ(4, *queueUnderlyingDeque.begin());
    EXPECT_EQ(5, *++queueUnderlyingDeque.begin());

    std::queue<int, std::list<int>> listQueue;
    listQueue.push(6);
    listQueue.push(7);
    auto queueUnderlyingList = RfS::get_underlying_container(listQueue);
    isEqual = std::is_same<std::list<int>, decltype(queueUnderlyingList)>::value;
    EXPECT_TRUE(isEqual);
    EXPECT_EQ(6, *queueUnderlyingList.begin());
    EXPECT_EQ(7, *++queueUnderlyingList.begin());

    // Priority Queues
    std::priority_queue<int> defaultPriorityQueue;
    defaultPriorityQueue.push(0);
    defaultPriorityQueue.push(1);
    auto priorityQueueDefaultUnderlyingContainer = RfS::get_underlying_container(defaultPriorityQueue);
    EXPECT_EQ(1, *priorityQueueDefaultUnderlyingContainer.begin());
    EXPECT_EQ(0, *++priorityQueueDefaultUnderlyingContainer.begin());

    std::priority_queue<int, std::vector<int>> vectorPriorityQueue;
    vectorPriorityQueue.push(2);
    vectorPriorityQueue.push(3);
    auto priorityQueueUnderlyingVector = RfS::get_underlying_container(vectorPriorityQueue);
    isEqual = std::is_same<std::vector<int>, decltype(priorityQueueUnderlyingVector)>::value;
    EXPECT_TRUE(isEqual);
    EXPECT_EQ(3, *priorityQueueUnderlyingVector.begin());
    EXPECT_EQ(2, *++priorityQueueUnderlyingVector.begin());

    std::priority_queue<int, std::deque<int>> dequePriorityQueue;
    dequePriorityQueue.push(4);
    dequePriorityQueue.push(5);
    auto priorityQueueUnderlyingDeque = RfS::get_underlying_container(dequePriorityQueue);
    isEqual = std::is_same<std::deque<int>, decltype(priorityQueueUnderlyingDeque)>::value;
    EXPECT_TRUE(isEqual);
    EXPECT_EQ(5, *priorityQueueUnderlyingDeque.begin());
    EXPECT_EQ(4, *++priorityQueueUnderlyingDeque.begin());
}

template <bool condition, typename Function>
void IfConditionTest(Function function)
{
    RfS::ConditionalCall<condition, Function>::call(function);
}

TEST(ReflectTest, ConditionalCall)
{
    bool value = false;
    IfConditionTest<false>([&](auto) {
        value = true;
    });
    EXPECT_FALSE(value);
    IfConditionTest<true>([&](auto) {
        value = true;
    });
    EXPECT_TRUE(value);
}

TEST(ReflectTest, FieldSimple)
{
    size_t fieldIndex = 0;
    char fieldName[] = "fieldName";
    char fieldTypeStr[] = "int";
    size_t fieldArraySize = 0;
    bool fieldIsIterable = false;
    bool fieldContainsPairs = false;
    bool fieldIsReflected = false;

    RfS::Field<> field = { fieldIndex, fieldName, fieldTypeStr, fieldArraySize, fieldIsIterable, fieldContainsPairs, fieldIsReflected };
    
    EXPECT_EQ(fieldIndex, field.index);
    EXPECT_STREQ(fieldName, field.name);
    EXPECT_STREQ(fieldTypeStr, field.typeStr);
    EXPECT_EQ(fieldArraySize, field.arraySize);
    EXPECT_EQ(fieldIsIterable, field.isIterable);
    EXPECT_EQ(fieldContainsPairs, field.containsPairs);
    EXPECT_EQ(fieldIsReflected, field.isReflected);
}

TEST(ReflectTest, FieldTemplated)
{
    size_t fieldIndex = 0;
    char fieldName[] = "fieldName";
    char fieldTypeStr[] = "int";
    size_t fieldArraySize = 0;
    bool fieldIsIterable = false;
    bool fieldContainsPairs = false;
    bool fieldIsReflected = false;

    RfS::Field<int, false> field = { fieldIndex, fieldName, fieldTypeStr, fieldArraySize, fieldIsIterable, fieldContainsPairs, fieldIsReflected };
    
    EXPECT_EQ(fieldIndex, field.index);
    EXPECT_STREQ(fieldName, field.name);
    EXPECT_STREQ(fieldTypeStr, field.typeStr);
    EXPECT_EQ(fieldArraySize, field.arraySize);
    EXPECT_EQ(fieldIsIterable, field.isIterable);
    EXPECT_EQ(fieldContainsPairs, field.containsPairs);
    EXPECT_EQ(fieldIsReflected, field.isReflected);
    
    bool isEqual = std::is_same<int, RfS::Field<int, false>::type>::value;
    EXPECT_TRUE(isEqual);
    isEqual = std::is_same<void, RfS::Field<int, false>::element_type>::value;
    EXPECT_TRUE(isEqual);
    isEqual = std::is_same<void, RfS::Field<int, false>::key_type>::value;
    EXPECT_TRUE(isEqual);

    const auto constField = field;
    bool isConst = std::is_const<decltype(constField)>::value;
    EXPECT_TRUE(isConst);

    const auto & constFieldRef = field;
    isConst = std::is_const<std::remove_reference<decltype(constFieldRef)>::type>::value;
    EXPECT_TRUE(isConst);
}

struct Obj
{
    int first;
    float second;
};

TEST(ReflectTest, ForPrimitive)
{
    RfS::Field<int, false> intField = { 0, "", "", 0, false, false, false };
    RfS::Field<int*, false> intPointerField = { 0, "", "", 0, false, false, false };
    RfS::Field<Obj, true> objField = { 0, "", "", 0, false, false, false };
    int intValue = 0;
    int* intPointer = &intValue;
    Obj objValue = {0, 0.0f};

    int timesVisited = 0;
    intField.ForPrimitive(intValue, [&](auto primitive){
        EXPECT_EQ(intValue, primitive);
        timesVisited++;
    });
    EXPECT_EQ(1, timesVisited);

    timesVisited = 0;
    intPointerField.ForPrimitive(intPointer, [&](auto primitive){
        EXPECT_EQ(intValue, primitive);
        timesVisited++;
    });
    EXPECT_EQ(1, timesVisited);

    timesVisited = 0;
    objField.ForPrimitive(objValue, [&](auto primitive){
        timesVisited++;
    });
    EXPECT_EQ(0, timesVisited);
}

TEST(ReflectTest, ForObject)
{
    RfS::Field<Obj, true> objField = { 0, "", "", 0, false, false, false };
    RfS::Field<Obj*, true> objPointerField = { 0, "", "", 0, false, false, false };
    RfS::Field<int, false> intField = { 0, "", "", 0, false, false, false };
    Obj objValue = {1, 2.2f};
    Obj* objPointerValue = &objValue;
    int intValue = 0;

    int timesVisited = 0;
    objField.ForObject(objValue, [&](auto & object){
        EXPECT_EQ(&objValue, &object);
        timesVisited++;
    });
    EXPECT_EQ(1, timesVisited);

    timesVisited = 0;
    objPointerField.ForObject(objPointerValue, [&](auto & object){
        EXPECT_EQ(&objValue, &object);
        timesVisited++;
    });
    EXPECT_EQ(1, timesVisited);

    timesVisited = 0;
    intField.ForObject(intValue, [&](auto object){
        timesVisited++;
    });
    EXPECT_EQ(0, timesVisited);
}

TEST(ReflectTest, ForPrimitives)
{
    constexpr size_t arraySize = 3;
    using IntArray = int[arraySize];
    RfS::Field<int, false> intField = { 0, "", "", 0, false, false, false };
    RfS::Field<IntArray, false> intArrayField = { 0, "", "", arraySize, false, false, false };
    RfS::Field<IntArray*, false> intArrayPointerField = { 0, "", "", arraySize, false, false, false };
    RfS::Field<std::vector<int>, false> intVectorField = { 0, "", "", 0, false, false, false };
    RfS::Field<std::vector<int>*, false> intVectorPointerField = { 0, "", "", 0, false, false, false };
    int intValue = 0;
    IntArray intArrayValue = { 20, 30, 40 };
    IntArray* intArrayPointerValue = &intArrayValue;
    std::vector<int> intVectorValue = {10, 20, 30};
    std::vector<int>* intVectorPointerValue = &intVectorValue;

    int timesVisited = 0;
    intField.ForPrimitives(intValue, [&](auto primitive){
        timesVisited++;
    });
    EXPECT_EQ(0, timesVisited);
    
    timesVisited = 0;
    intArrayField.ForPrimitives(intArrayValue, [&](auto index, auto primitive){
        switch ( index ) {
            case 0: EXPECT_EQ(primitive, 20); break;
            case 1: EXPECT_EQ(primitive, 30); break;
            case 2: EXPECT_EQ(primitive, 40); break;
            default: EXPECT_TRUE(false); break;
        }
        timesVisited++;
    });
    EXPECT_EQ(3, timesVisited);
    
    timesVisited = 0;
    intArrayPointerField.ForPrimitives(intArrayPointerValue, [&](auto index, auto primitive){
        switch ( index ) {
            case 0: EXPECT_EQ(primitive, 20); break;
            case 1: EXPECT_EQ(primitive, 30); break;
            case 2: EXPECT_EQ(primitive, 40); break;
            default: EXPECT_TRUE(false); break;
        }
        timesVisited++;
    });
    EXPECT_EQ(3, timesVisited);

    timesVisited = 0;
    intVectorField.ForPrimitives(intVectorValue, [&](auto index, auto primitive){
        switch ( index ) {
            case 0: EXPECT_EQ(primitive, 10); break;
            case 1: EXPECT_EQ(primitive, 20); break;
            case 2: EXPECT_EQ(primitive, 30); break;
            default: EXPECT_TRUE(false); break;
        }
        timesVisited++;
    });
    EXPECT_EQ(3, timesVisited);

    timesVisited = 0;
    intVectorPointerField.ForPrimitives(intVectorPointerValue, [&](auto index, auto primitive){
        switch ( index ) {
            case 0: EXPECT_EQ(primitive, 10); break;
            case 1: EXPECT_EQ(primitive, 20); break;
            case 2: EXPECT_EQ(primitive, 30); break;
            default: EXPECT_TRUE(false); break;
        }
        timesVisited++;
    });
    EXPECT_EQ(3, timesVisited);

}
