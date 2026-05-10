#ifndef PGR_SEM_COPAKOND_BOWLINGGAME_H
#define PGR_SEM_COPAKOND_BOWLINGGAME_H

namespace copakond {
    class Mesh;

    enum class BowlingAlleyStatus { IDLE, ROLLING, CLEARING };

    class BowlingGame {
    private:
        float _timeToDespawnBowlingBall = 0.0f;
        bool rollingBowlingBallNow = false;

        int totalScore1 = 0;
        int totalScore2 = 0;
        int totalScore3 = 0;
        int totalScore4 = 0;

        bool bowlingAlleyOpened1 = false;
        bool bowlingAlleyOpened2 = false;
        bool bowlingAlleyOpened3 = false;
        bool bowlingAlleyOpened4 = false;

        float offsetDoor1 = 0.0f;
        float offsetDoor2 = 0.0f;
        float offsetDoor3 = 0.0f;
        float offsetDoor4 = 0.0f;

        BowlingAlleyStatus alleyStatus1 = BowlingAlleyStatus::IDLE;
        BowlingAlleyStatus alleyStatus2 = BowlingAlleyStatus::IDLE;
        BowlingAlleyStatus alleyStatus3 = BowlingAlleyStatus::IDLE;
        BowlingAlleyStatus alleyStatus4 = BowlingAlleyStatus::IDLE;

    public:
        BowlingGame();
        void update(float deltaTime);

        void toggleDoor1() { bowlingAlleyOpened1 = !bowlingAlleyOpened1; }
        void toggleDoor2() { bowlingAlleyOpened2 = !bowlingAlleyOpened2; }
        void toggleDoor3() { bowlingAlleyOpened3 = !bowlingAlleyOpened3; }
        void toggleDoor4() { bowlingAlleyOpened4 = !bowlingAlleyOpened4; }

        Mesh *door1 = nullptr;
        Mesh *door2 = nullptr;
        Mesh *door3 = nullptr;
        Mesh *door4 = nullptr;
    };
}

#endif //PGR_SEM_COPAKOND_BOWLINGGAME_H
