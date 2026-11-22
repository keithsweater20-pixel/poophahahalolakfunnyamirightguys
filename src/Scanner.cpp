#include "Scanner.hpp"

#include <algorithm>

namespace freebuild {
    static bool hasID(const std::vector<int>& ids, int objectID) {
        return std::find(ids.begin(), ids.end(), objectID) != ids.end();
    }

    Style classify(int objectID,
                   const std::vector<int>& techIDs,
                   const std::vector<int>& nullIDs,
                   const std::vector<int>& hellIDs) {
        if (hasID(techIDs, objectID)) return Style::Tech;
        if (hasID(nullIDs, objectID)) return Style::Null;
        if (hasID(hellIDs, objectID)) return Style::Hell;
        return Style::Unknown;
    }

    std::vector<DecorationRecord> filterRegion(
        const std::vector<DecorationRecord>& objects,
        const ScanRegion& region
    ) {
        std::vector<DecorationRecord> result;
        result.reserve(objects.size());
        for (const auto& object : objects) {
            if (region.contains(object.x, object.y)) result.push_back(object);
        }
        return result;
    }
}
