#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

#include <fstream>
#include <iomanip>
#include <sstream>

using namespace geode::prelude;

class $modify(FreeBuildEditorUI, EditorUI) {
    bool init(LevelEditorLayer* editorLayer) {
        if (!EditorUI::init(editorLayer)) return false;

        auto label = CCLabelBMFont::create("SCAN LEVEL", "bigFont.fnt");
        if (!label) return true;

        auto button = CCMenuItemLabel::create(
            label,
            this,
            menu_selector(FreeBuildEditorUI::onFreeBuildScan)
        );
        if (!button) return true;
        button->setScale(0.55f);

        auto menu = CCMenu::create();
        if (!menu) return true;
        menu->addChild(button);
        menu->setPosition({ CCDirector::sharedDirector()->getWinSize().width - 72.f,
                            CCDirector::sharedDirector()->getWinSize().height - 86.f });
        menu->setID("freebuild-scanner-menu");
        this->addChild(menu, 1000);

        return true;
    }

    void onFreeBuildScan(CCObject*) {
        if (!m_editorLayer) {
            FLAlertLayer::create("FreeBuild", "Open a level in the editor before scanning.", "OK")->show();
            return;
        }

        auto objects = m_editorLayer->getAllObjects();
        if (!objects) {
            FLAlertLayer::create("FreeBuild", "Couldn't read the editor objects.", "OK")->show();
            return;
        }

        std::ostringstream json;
        json << "{\n  \"format\": \"freebuild-scan-v1\",\n  \"objects\": [";
        unsigned int written = 0;
        for (unsigned int i = 0; i < objects->count(); ++i) {
            auto object = typeinfo_cast<GameObject*>(objects->objectAtIndex(i));
            if (!object) continue;

            auto pos = object->getPosition();
            if (written) json << ",";
            json << "\n    {"
                 << "\"objectID\":" << object->m_objectID
                 << ",\"x\":" << std::fixed << std::setprecision(3) << pos.x
                 << ",\"y\":" << pos.y
                 << ",\"rotation\":" << object->getRotation()
                 << ",\"scaleX\":" << object->getScaleX()
                 << ",\"scaleY\":" << object->getScaleY()
                 << "}";
            ++written;
        }
        json << (written ? "\n  " : "") << "]\n}\n";

        auto path = Mod::get()->getSaveDir() / "last-scan.json";
        std::ofstream file(path, std::ios::binary);
        if (!file.is_open()) {
            FLAlertLayer::create("FreeBuild", "Couldn't save the scan file. Check Geode's mod storage permissions.", "OK")->show();
            return;
        }
        file << json.str();
        file.close();

        FLAlertLayer::create(
            "FreeBuild Scanner",
            fmt::format("Scanned {} level objects.\nSaved to Geode/mods/community.freebuild/last-scan.json", written),
            "OK"
        )->show();
        log::info("FreeBuild scanned {} level objects into {}", written, path.string());
    }
};

$on_mod(Loaded) {
    log::info("FreeBuild loaded. Open the editor and tap SCAN LEVEL to export level decorations.");
}
