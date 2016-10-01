#ifndef FRENCHCARD_H
#define FRENCHCARD_H


class FrenchCard
{
public:
    int suit;
    int rank;

    static const int CLUBS = 0;
    static const int SPADES = 1;
    static const int DIAMONDS = 2;
    static const int HEARTS = 3;

public:
    FrenchCard();
    ~FrenchCard();

    void set(int suit, int);
    bool isRed();
    bool isBlack();
};

#endif // FRENCHCARD_H
