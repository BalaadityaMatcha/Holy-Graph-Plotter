#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

struct Cubie {
    glm::vec3 logicalPos;
    glm::mat4 rotation;

    Cubie(glm::vec3 pos) : logicalPos(pos), rotation(glm::mat4(1.0f)) {}
};

class RubiksCube {
public:
    std::vector<Cubie> cubies;

    RubiksCube() {
        for(int x = -1; x <= 1; x++) {
            for(int y = -1; y <= 1; y++) {
                for(int z = -1; z <= 1; z++) {
                    cubies.push_back(Cubie(glm::vec3(x, y, z)));
                }
            }
        }
    }

    void RotateFace(int axis, int layer, float angleDegrees) {
        glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(angleDegrees), 
            glm::vec3(axis == 0 ? 1 : 0, axis == 1 ? 1 : 0, axis == 2 ? 1 : 0));
        
        for (auto& cubie : cubies) {
            bool inLayer = false;
            if (axis == 0 && std::round(cubie.logicalPos.x) == layer) inLayer = true;
            if (axis == 1 && std::round(cubie.logicalPos.y) == layer) inLayer = true;
            if (axis == 2 && std::round(cubie.logicalPos.z) == layer) inLayer = true;

            if (inLayer) {
                glm::vec4 newPos = rot * glm::vec4(cubie.logicalPos, 1.0f);
                cubie.logicalPos = glm::vec3(std::round(newPos.x), std::round(newPos.y), std::round(newPos.z));
                cubie.rotation = rot * cubie.rotation;
            }
        }
    }
};
