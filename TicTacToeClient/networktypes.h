#ifndef NETWORKTYPES_H
#define NETWORKTYPES_H

enum class ReplyType
{
    Unknown = 0,
    Invalid = 1,
    Test = 2,
    FindGame = 3,
    GameFound = 4,
    SignIn = 5,
    SignUpUser = 6,
    GetStatistics = 7
};

enum class RequestType
{
    Invalid = 0,
    Test = 1,
    FindGame = 2,
    SignIn = 3,
    SignUpUser = 4,
    GetStatistics = 5,
    Unknown = 1000
};

#endif // NETWORKTYPES_H
