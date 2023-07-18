#include "MyContactListener.h"

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>

#include "FloorLevel.h"
#include "Star.h"
#include "Enemy.h"
#include "Box.h"
#include "Rock.h"
#include "Ball.h"
#include "Music.h"
#include "Border.h"
#include "Boss.h"

// Function decleration
void processCollision(GameObject& object1, GameObject& object2);

namespace // anonymous namespace the standard way to make function "static"
{

        // All function collisions
    void ballFloor(GameObject& object1, GameObject& object2){
        Ball& ball = dynamic_cast<Ball&>(object1);
        ball.setInJump();
    }
    void ballRock(GameObject& object1, GameObject& object2)
    {
        Ball& ball = dynamic_cast<Ball&>(object1);
        ball.setInJump();
    }
    void ballBox(GameObject& object1, GameObject& object2)
    {
        Ball& ball = dynamic_cast<Ball&>(object1);
        ball.setInJump();
    }
    void ballEnemy(GameObject& object1, GameObject& object2)
    {
        // dynamic casting for objects
        Ball& ball = dynamic_cast<Ball&>(object1);
        Enemy& enemy = dynamic_cast<Enemy&>(object2);

        // If ball jumped on enemy, kill enemy and give score
        if (enemy.getPosition().y > ball.getPosition().y + ball.getHeight() / 2) {
            enemy.dispose();
            ball.setScore(25);
            Music::instance().playWinEnemy();
        }
        else {
            // enemy has hitted me, decrease life
            ball.dicLife();
            enemy.changeDirection();
            Music::instance().playEnemy();
        }
        ball.jump(enemy.getPosition());
    }
    void ballStar(GameObject& object1, GameObject& object2)
    {
        Ball& ball = dynamic_cast<Ball&>(object1);
        Star& star = dynamic_cast<Star&>(object2);
        // play music of star and add score
        Music::instance().playStar();
        star.dispose();
        ball.setScore(15);
    }
    void ballBorder(GameObject& object1, GameObject& object2) {
        Border& border = dynamic_cast<Border&>(object2);
        border.setTouching();
    }
    void enemyBox(GameObject& object1, GameObject& object2) {
        Enemy& enemy = dynamic_cast<Enemy&>(object1);
        enemy.changeDirection();
    }
    void enemyRock(GameObject& object1, GameObject& object2) {
        Enemy& enemy = dynamic_cast<Enemy&>(object1);
        enemy.changeDirection();
    }
    void enemyBorder(GameObject& object1, GameObject& object2) {
        Enemy& enemy = dynamic_cast<Enemy&>(object1);
        enemy.changeDirection();
    }
    void bossBorder(GameObject& object1, GameObject& object2) {
        Boss& boss = dynamic_cast<Boss&>(object1);
        boss.changeDirection();
        boss.setStanding(3);
    }
    void ballBoss(GameObject& object1, GameObject& object2)
    {
        Ball& ball = dynamic_cast<Ball&>(object1);
        Boss& boss = dynamic_cast<Boss&>(object2);

        // "Ball Allowed to hit the boss only from above and only while boss is standing
        if (boss.getPosition().y > ball.getPosition().y + ball.getHeight() / 2 && boss.isStanding()) {
            boss.dispose();
            boss.setStanding(0);
            ball.setScore(50);
            ball.jump(boss.getPosition());
            Music::instance().playWinEnemy();
        }
        // Boss in movement or hitted me from the side, decrease my life by one.
        else {
            ball.dicLife();
            boss.changeDirection();
            Music::instance().playEnemy();
        }

        // jump anyway in collision
        ball.jump(boss.getPosition());
    }

    void enemyFloor(GameObject& object1, GameObject& object2) {
        Enemy& enemy = dynamic_cast<Enemy&>(object1);
        FloorLevel& floor = dynamic_cast<FloorLevel&>(object2);
        if (floor.getPosition().x + floor.getWidth() / 2 < enemy.getPosition().x + enemy.getWidth())
            enemy.setDirection(-1);
        if (floor.getPosition().x - floor.getWidth() / 2 > enemy.getPosition().x - enemy.getWidth())
            enemy.setDirection(1);
    }
    void enemyEnemy(GameObject& object1, GameObject& object2) {
        Enemy& enemy1 = dynamic_cast<Enemy&>(object1);
        Enemy& enemy2 = dynamic_cast<Enemy&>(object2);
        enemy1.changeDirection();
        enemy2.changeDirection();
    }

    // secondary collision-processing functions that just
    // implement symmetry: swap the parameters and call a
    // primary function
    void floorBall(GameObject& floorLevel, GameObject& ball)
    {
        ballFloor(ball, floorLevel);
    }
    void rockBall(GameObject& rock, GameObject& ball)
    {
        ballRock(ball, rock);
    }
    void boxBall(GameObject& box, GameObject& ball)
    {
        ballBox(ball, box);
    }
    void enemyBall(GameObject& enemy, GameObject& ball)
    {
        ballEnemy(ball, enemy);
    }
    void starBall(GameObject& star, GameObject& ball)
    {
        ballStar(ball, star);
    }
    void borderBall(GameObject& border, GameObject& ball)
    {
        ballBorder(ball, border);
    }
    void boxEnemy(GameObject& box, GameObject& enemy)
    {
        enemyBox(enemy, box);
    }
    void rockEnemy(GameObject& rock, GameObject& enemy)
    {
        enemyRock(enemy, rock);
    }
    void borderEnemy(GameObject& border, GameObject& enemy)
    {
        enemyBorder(enemy, border);
    }
    void borderBoss(GameObject& border, GameObject& boss)
    {
        bossBorder(boss, border);
    }
    void bossBall(GameObject& boss, GameObject& ball)
    {
        ballBoss(ball, boss);
    }
    void floorEnemy(GameObject& floorLevel, GameObject& enemy)
    {
        enemyFloor(enemy, floorLevel);
    }
    // Using section
    using HitFunctionPtr = std::function<void(GameObject&, GameObject&)>;
    // typedef void (*HitFunctionPtr)(GameObject&, GameObject&);
    using Key = std::pair<std::type_index, std::type_index>;
    // std::unordered_map is better, but it requires defining good hash function for pair
    using HitMap = std::map<Key, HitFunctionPtr>;

    // Initialise collisions to function refrences
    HitMap initializeCollisionMap()
    {
        HitMap phm;
        phm[Key(typeid(Ball      ), typeid(FloorLevel))] = &ballFloor;
        phm[Key(typeid(FloorLevel), typeid(Ball      ))] = &floorBall;
        phm[Key(typeid(Ball      ), typeid(Rock      ))] = &ballRock;
        phm[Key(typeid(Rock      ), typeid(Ball      ))] = &rockBall;
        phm[Key(typeid(Ball      ), typeid(Box       ))] = &ballBox;
        phm[Key(typeid(Box       ), typeid(Ball      ))] = &boxBall;
        phm[Key(typeid(Ball      ), typeid(Enemy     ))] = &ballEnemy;
        phm[Key(typeid(Enemy     ), typeid(Ball      ))] = &enemyBall;  
        phm[Key(typeid(Ball      ), typeid(Star      ))] = &ballStar;
        phm[Key(typeid(Star      ), typeid(Ball      ))] = &starBall;
        phm[Key(typeid(Ball      ), typeid(Border    ))] = &ballBorder;
        phm[Key(typeid(Border    ), typeid(Ball      ))] = &borderBall;
        phm[Key(typeid(Enemy     ), typeid(Box       ))] = &enemyBox;
        phm[Key(typeid(Box       ), typeid(Enemy     ))] = &boxEnemy;
        phm[Key(typeid(Enemy     ), typeid(Rock      ))] = &enemyRock;
        phm[Key(typeid(Rock      ), typeid(Enemy     ))] = &rockEnemy;
        phm[Key(typeid(Enemy     ), typeid(Border    ))] = &enemyBorder;
        phm[Key(typeid(Border    ), typeid(Enemy     ))] = &borderEnemy;
        phm[Key(typeid(Boss      ), typeid(Border    ))] = &bossBorder;
        phm[Key(typeid(Border    ), typeid(Boss      ))] = &borderBoss;
        phm[Key(typeid(Ball      ), typeid(Boss      ))] = &ballBoss;
        phm[Key(typeid(Boss      ), typeid(Ball      ))] = &bossBall;
        phm[Key(typeid(Enemy     ), typeid(FloorLevel))] = &enemyFloor;
        phm[Key(typeid(FloorLevel), typeid(Enemy     ))] = &floorEnemy;
        phm[Key(typeid(Enemy     ), typeid(Enemy     ))] = &enemyEnemy;
        return phm;
    }

    // look for collision in the map
    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
    {
        static HitMap collisionMap = initializeCollisionMap();
        auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
        if (mapEntry == collisionMap.end())
        {
            // if collision didnt found, return null for collision
            return nullptr;
        }
        return mapEntry->second;
    }

} // end namespace
// Start collision
void MyContactListener::BeginContact(b2Contact* contact) {
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();

    GameObject* a = reinterpret_cast<GameObject*>(bodyA->GetUserData().pointer);
    GameObject* b = reinterpret_cast<GameObject*>(bodyB->GetUserData().pointer);

    // Process Collisions between two objects
    processCollision(*a, *b);
}

// Process collisions func
void processCollision(GameObject& object1, GameObject& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));
    if (!phf)
    {
        return;
    }
    phf(object1, object2);
}
