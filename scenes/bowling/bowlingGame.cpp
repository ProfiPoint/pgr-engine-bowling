#include "bowlingGame.h"

#include <algorithm>

#include "../../meshes/mesh.h"
#include "../../meshes/collision/rigidSphere.h"
#include "../../geometry/camera.h"

#include "../../meshes/label/textLabel.h"
#include "../../meshes/label/imageLabel.h"
#include "../../meshes/label/imageMoving.h"
#include "../../meshes/label/imageSequenceLabel.h"

#define DOOR_OPEN_SPEED 0.07f
#define DOOR_MAX_OFFSET 0.45f
#define BALL_DESPAWN_TIME 30.0f
#define BALL_MIN_SPEED -0.5f

namespace copakond {
    int BowlingGame::getClosestAlleyToBowlingBall() {
        float dist1 = glm::distance(bowlingBall->position(), door1->position());
        float dist2 = glm::distance(bowlingBall->position(), door2->position());
        float dist3 = glm::distance(bowlingBall->position(), door3->position());
        float dist4 = glm::distance(bowlingBall->position(), door4->position());

        if (dist1 < dist2 && dist1 < dist3 && dist1 < dist4) { return 1; }
        if (dist2 < dist3 && dist2 < dist4) { return 2; }
        if (dist3 < dist4) { return 3; }
        return 4;
    }

    int BowlingGame::resetBowlingBall() {
        int alley = getClosestAlleyToBowlingBall();
        int count = 0;
        int startIndex = (alley - 1) * 10;
        for (int i = startIndex; i < startIndex + 10 && i < pins.size(); i++) {
            if (pins[i]->isDown()) {
                count++;
            }
        }

        evaluateScore(alley, count);

        if (selectedBowlingBall) { selectedBowlingBall->show(); }
        selectedBowlingBall = nullptr;
        rollingBowlingBallNow = false;
        bowlingBall->disable();
        bowlingBall->position() = glm::vec3(0.0f, 1000.0f, 0.0f);

        return count;
    }

    bool BowlingGame::checkIfBowlingBallHitTheWall() const {
        return bowlingBall->position().x < -11.5f; // if its behind the start of the last wall retrun true
    }


    void BowlingGame::update(float deltaTime) {
        // door opening logic
        if (bowlingAlleyOpened1) {
            offsetDoor1 += deltaTime * DOOR_OPEN_SPEED;
            offsetDoor1 = std::min(offsetDoor1, DOOR_MAX_OFFSET);
        } else {
            offsetDoor1 -= deltaTime * DOOR_OPEN_SPEED;
            offsetDoor1 = std::max(offsetDoor1, 0.0f);
        }
        if (bowlingAlleyOpened2) {
            offsetDoor2 += deltaTime * DOOR_OPEN_SPEED;
            offsetDoor2 = std::min(offsetDoor2, DOOR_MAX_OFFSET);
        } else {
            offsetDoor2 -= deltaTime * DOOR_OPEN_SPEED;
            offsetDoor2 = std::max(offsetDoor2, 0.0f);
        }
        if (bowlingAlleyOpened3) {
            offsetDoor3 += deltaTime * DOOR_OPEN_SPEED;
            offsetDoor3 = std::min(offsetDoor3, DOOR_MAX_OFFSET);
        } else {
            offsetDoor3 -= deltaTime * DOOR_OPEN_SPEED;
            offsetDoor3 = std::max(offsetDoor3, 0.0f);
        }
        if (bowlingAlleyOpened4) {
            offsetDoor4 += deltaTime * DOOR_OPEN_SPEED;
            offsetDoor4 = std::min(offsetDoor4, DOOR_MAX_OFFSET);
        } else {
            offsetDoor4 -= deltaTime * DOOR_OPEN_SPEED;
            offsetDoor4 = std::max(offsetDoor4, 0.0f);
        }
        door1->position().y = offsetDoor1;
        door2->position().y = offsetDoor2;
        door3->position().y = offsetDoor3;
        door4->position().y = offsetDoor4;

        // update bowling ball if rolling
        timeToDespawnBowlingBall -= deltaTime;
        if (rollingBowlingBallNow && timeToDespawnBowlingBall <= 0.0f) {
            resetBowlingBall();
        }

        // make sure the ball keeps moving constantly
        if (bowlingBall->velocity().x > BALL_MIN_SPEED) {
            bowlingBall->velocity().x += BALL_MIN_SPEED / 15;
        }

        // if it touches the wall, then end it 5 seconds, instead of waiting 20 seconds to despawn
        if (checkIfBowlingBallHitTheWall()) { timeToDespawnBowlingBall = glm::min(timeToDespawnBowlingBall, 5.0f); }

        // manage videos
        videoTimeout -= deltaTime;
        if (videoTimeout <= 0.0f) {
            videoSplit1->hide();
            videoSpare2->hide();
            videoStrike3->hide();
            videoMiss4->hide();
            videoTimeout = 999.0f;
        }

        // game logic
        for (int i = 0; i < 4; i++) {
            if (isGameOver[i]) {
                gameOverTimer[i] -= deltaTime;
                if (gameOverTimer[i] <= 0.0f) {
                    resetGameForAlley(i + 1);
                }
            }
        }
    }

    void BowlingGame::resetGameForAlley(int alley) {
        int aIdx = alley - 1;
        currentSubround[aIdx] = 0;
        isGameOver[aIdx] = false;
        gameOverTimer[aIdx] = 0.0f;

        // Pick the right array to clear
        int* scoreNow = score1;
        if (alley == 2) scoreNow = score2;
        if (alley == 3) scoreNow = score3;
        if (alley == 4) scoreNow = score4;

        for(int i = 0; i < TOTAL_ROUNDS * 2 + 1; i++) {
            scoreNow[i] = 0;
        }

        resetPinsForAlley(alley);
        renderText(alley);
    }

    void BowlingGame::throwBall(float power) {
        if (!selectedBowlingBall) { return; }
        if (rollingBowlingBallNow) { return; }

        bowlingBall->enable();
        rollingBowlingBallNow = true;
        timeToDespawnBowlingBall = BALL_DESPAWN_TIME;

        // set position and velocity of the ball based of the camera position
        glm::vec3 camRot = camera->rotation();

        glm::vec3 lookDirection = glm::vec3(
            cos(camRot.y) * cos(camRot.x),
            sin(camRot.x),
            sin(camRot.y) * cos(camRot.x)
        );
        lookDirection = glm::normalize(lookDirection);

        // add offset to prevnet collision
        float spawnDistanceOffset = 1.0f;
        bowlingBall->position() = camera->position() + (lookDirection * spawnDistanceOffset);
        bowlingBall->velocity() = lookDirection * power;
    }

    void BowlingGame::pickBowlingBall(Mesh* bowlingBall, float power) {
        if (selectedBowlingBall) { throwBall(power); return; }

        selectedBowlingBall = bowlingBall;
        bowlingBall->hide();
    }

    void BowlingGame::toggleDoor1() {
        bowlingAlleyOpened1 = !bowlingAlleyOpened1;
        if (bowlingAlleyOpened1) {
            scoreLabel1->show();
            videoIdle1->hide();
        } else {
            scoreLabel1->hide();
            videoIdle1->show();
        }
    }
    void BowlingGame::toggleDoor2() {
        bowlingAlleyOpened2 = !bowlingAlleyOpened2;
        if (bowlingAlleyOpened2) {
            scoreLabel2->show();
            videoIdle2->hide();
        } else {
            scoreLabel2->hide();
            videoIdle2->show();
        }
    }
    void BowlingGame::toggleDoor3() {
        bowlingAlleyOpened3 = !bowlingAlleyOpened3;
        if (bowlingAlleyOpened3) {
            scoreLabel3->show();
            videoIdle3->hide();
        } else {
            scoreLabel3->hide();
            videoIdle3->show();
        }
    }
    void BowlingGame::toggleDoor4() {
        bowlingAlleyOpened4 = !bowlingAlleyOpened4;
        if (bowlingAlleyOpened4) {
            scoreLabel4->show();
            videoIdle4->hide();
        } else {
            scoreLabel4->hide();
            videoIdle4->show();
        }
    }

    // format the given text result score
    void BowlingGame::renderText(int alley) {
        int aIdx = alley - 1;
        int* scoreNow = score1;
        TextLabel* label = scoreLabel1;
        if (alley == 2) { scoreNow = score2; label = scoreLabel2; }
        if (alley == 3) { scoreNow = score3; label = scoreLabel3; }
        if (alley == 4) { scoreNow = score4; label = scoreLabel4; }

        std::string res = "";
        int sum = 0;

        for (int i = 0; i < TOTAL_ROUNDS * 2; i++) {
            sum += scoreNow[i];
            bool hasPlayed = (i < currentSubround[aIdx]);

            if (i % 2 == 0) {  // FIRST THROW
                if (hasPlayed && scoreNow[i] == 10) {
                    res += "X";
                } else if (hasPlayed && scoreNow[i] == 0) {
                    res += "-";
                } else {
                    res += hasPlayed ? std::to_string(scoreNow[i]) : " ";
                }
            } else { // SECOND THROW
                if (hasPlayed && scoreNow[i - 1] == 10) {
                    res += " "; // strike from prev round
                } else if (hasPlayed && scoreNow[i - 1] + scoreNow[i] == 10) {
                    res += "/";
                } else if (hasPlayed && scoreNow[i] == 0) {
                    res += "-";
                } else {
                    res += hasPlayed ? std::to_string(scoreNow[i]) : " ";
                }
            }

            if (i % 2 == 1 && i < TOTAL_ROUNDS * 2 - 1) {
                res += "|";
            } else {
                res += " ";
            }
        }

        if (!res.empty() && res.back() == ' ') { res.pop_back(); }
        res += "|";
        if (sum < 10) { res += "0"; }
        res += std::to_string(sum);

        label->setText(res);
    }

    void BowlingGame::playVideo(BowlingVideoEvent event, int alley) {
        glm::vec3 pos = videoIdle1->position();
        if (alley == 2) { videoIdle2->position(); }
        if (alley == 3) { videoIdle3->position(); }
        if (alley == 4) { videoIdle4->position(); }

        ImageSequenceLabel *videoLabel = videoSplit1; videoTimeout = 8.0f;
        if (event == BowlingVideoEvent::SPARE) { videoLabel = videoSpare2; videoTimeout = 8.0f; }
        if (event == BowlingVideoEvent::STRIKE) { videoLabel = videoStrike3; videoTimeout = 8.0f;}
        if (event == BowlingVideoEvent::MISS) { videoLabel = videoMiss4; videoTimeout = 6.0f; }

        videoSplit1->hide(); videoSplit1->setFrame(0);
        videoSpare2->hide(); videoSpare2->setFrame(0);
        videoStrike3->hide(); videoStrike3->setFrame(0);
        videoMiss4->hide(); videoMiss4->setFrame(0);

        videoLabel->position() = pos;
        videoLabel->show(); videoLabel->setFrame(0);
    }

    void BowlingGame::resetPinsForAlley(int alley) {
        int startIndex = (alley - 1) * 10;

        for (int i = startIndex; i < startIndex + 10 && i < pins.size(); i++) {
            pins[i]->reset();
        }
    }

    void BowlingGame::evaluateScore(int alley, int pinsKnocked) {
        int aIdx = alley - 1;
        if (isGameOver[aIdx]) return;

        int* scoreNow = score1;
        if (alley == 2) scoreNow = score2;
        if (alley == 3) scoreNow = score3;
        if (alley == 4) scoreNow = score4;

        scoreNow[currentSubround[aIdx]] = pinsKnocked;
        bool isFirstThrow = (currentSubround[aIdx] % 2 == 0);

        // STRIKE
        if (pinsKnocked == 10 && isFirstThrow) {
            playVideo(BowlingVideoEvent::STRIKE, alley);
            scoreNow[currentSubround[aIdx] + 1] = 0; // skip 2nd throw
            currentSubround[aIdx] += 2; // next round
            resetPinsForAlley(alley);
        }

        // SPARE
        else if (!isFirstThrow && (scoreNow[currentSubround[aIdx] - 1] + pinsKnocked == 10)) {
            playVideo(BowlingVideoEvent::SPARE, alley);
            currentSubround[aIdx]++;
            resetPinsForAlley(alley);
        }

        // SPLIT
        else if (pinsKnocked == 8) {
            playVideo(BowlingVideoEvent::SPLIT, alley);
            if (!isFirstThrow) resetPinsForAlley(alley);
            currentSubround[aIdx]++;
        }

        // MISS
        else if (pinsKnocked == 0) {
            playVideo(BowlingVideoEvent::MISS, alley);
            if (!isFirstThrow) resetPinsForAlley(alley);
            currentSubround[aIdx]++;
        }

        // OTHER
        else {
            if (!isFirstThrow) resetPinsForAlley(alley);
            currentSubround[aIdx]++;
        }

        renderText(alley);

        // END GAME
        if (currentSubround[aIdx] >= TOTAL_ROUNDS * 2) {
            isGameOver[aIdx] = true;
            gameOverTimer[aIdx] = 15.0f;
        }
    }
}
