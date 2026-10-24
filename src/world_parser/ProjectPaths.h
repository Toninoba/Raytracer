//
// Created by tobi on 10.10.26.
//

#ifndef RAYTRACER_PROJECTPATHS_H
#define RAYTRACER_PROJECTPATHS_H

#include <filesystem>

namespace ProjectPaths {
    namespace fs = std::filesystem;

#ifndef PROJECT_ROOT_DIR
#define PROJECT_ROOT_DIR "."
#endif

    inline const fs::path RootDir = fs::path(PROJECT_ROOT_DIR);
    inline const fs::path WorldDir = RootDir / "worlds";

    inline void ensureDirectoriesExist() {
        fs::create_directories(WorldDir);
    }
}


#endif //RAYTRACER_PROJECTPATHS_H
