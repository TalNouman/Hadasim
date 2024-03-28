#ifndef __TWITTER_TOWERS__
#define __TWITTER_TOWERS__

class TwitterTowers
{
public:
    TwitterTowers();
    ~TwitterTowers();
    void TowersChoice();
    void RectangularTower();
    void TriangleTower();
    void PrintTriangle();

private:
    int m_height;
    int m_width;
};

#endif /* __TWITTER_TOWERS__ */