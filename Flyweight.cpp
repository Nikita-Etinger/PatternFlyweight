#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;


class Enemy
{
protected:
    string name;
    string sprite;

public:
    Enemy(string name, string sprite)
    {
        this->name = name;
        this->sprite = sprite;
    }

    virtual void attack() = 0;
    virtual void move() = 0;

    virtual ~Enemy() {}
};

class Goblin : public Enemy
{
public:
    Goblin(string name, string sprite) : Enemy(name, sprite)
    {
    }

    void attack()  
    {
        cout << name << " is attacking!" << endl;
    }

    void move()  
    {
        cout << name << " is moving!" << endl;
    }
};

class Skeleton : public Enemy
{
public:
    Skeleton(string name, string sprite) : Enemy(name, sprite)
    {
    }

    void attack()
    {
        cout << name << " is attacking!" << endl;
    }

    void move()
    {
        cout << name << " is moving!" << endl;
    }
};

class EnemyFactory
{
public:
    virtual Enemy* createEnemy() = 0;
};

class GoblinFactory : public EnemyFactory
{
public:
    Enemy* createEnemy()
    {
        return new Goblin("Goblin", "goblin_sprite");
    }
};

class SkeletonFactory : public EnemyFactory
{
public:
    Enemy* createEnemy()
    {
        return new Skeleton("Skeleton", "skeleton_sprite");
    }
};

class EnemySpawner
{
private:
    vector<Enemy*> enemies;

public:
    void spawnEnemies(EnemyFactory* factory, int count)
    {
        for (int i = 0; i < count; ++i)
        {
            enemies.push_back(factory->createEnemy());
        }
    }

    void performActions()
    {
        for (auto enemy : enemies)
        {
            enemy->attack();
            enemy->move();
        }
    }

    ~EnemySpawner()
    {
        for (auto enemy : enemies)
        {
            delete enemy;
        }
    }
};

int main()
{
    EnemySpawner spawner;

    EnemyFactory* goblinFactory = new GoblinFactory();
    EnemyFactory* skeletonFactory = new SkeletonFactory();

    srand(time(0));

    int goblinCount = rand() % 10 + 1;
    int skeletonCount = rand() % 10 + 1;

    spawner.spawnEnemies(goblinFactory, goblinCount);
    spawner.spawnEnemies(skeletonFactory, skeletonCount);

    spawner.performActions();


    return 0;
}