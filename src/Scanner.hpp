#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace freebuild {
    struct ScanRegion {
        float minX = 0.f;
        float minY = 0.f;
        float maxX = 0.f;
        float maxY = 0.f;

        bool contains(float x, float y) const {
            return x >= minX && x <= maxX && y >= minY && y <= maxY;
        }
    };

    struct DecorationRecord {
        int objectID = 0;
        float x = 0.f;
        float y = 0.f;
        float rotation = 0.f;
        float scaleX = 1.f;
        float scaleY = 1.f;
        std::string style = "unknown";
    };

    enum class Style {
        Unknown,
        Tech,
        Null,
        Hell
    };

    // Classifies a record using object IDs explicitly supplied by a style profile.
    // Empty profiles intentionally return Unknown rather than guessing.
    Style classify(int objectID,
                   const std::vector<int>& techIDs,
                   const std::vector<int>& nullIDs,
                   const std::vector<int>& hellIDs);

    std::vector<DecorationRecord> filterRegion(
        const std::vector<DecorationRecord>& objects,
        const ScanRegion& region
    );
}
