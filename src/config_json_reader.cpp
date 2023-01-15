#include <fstream>
#include "../include/util.hpp"
#include "../include/config_json_reader.hpp"

std::map<std::string, JsonReaderStrategy*> ConfigJsonReader::createOptions() {
    std::map<std::string, JsonReaderStrategy*> options;
    options["speed"] = (new JsonIntReaderStrategy(&m_config->speed))->min(0);

    std::map<std::string, int*> styles;
    styles["head"]            = &m_config->headStyle;
    styles["tail"]            = &m_config->tailStyle;
    options["style"] = new JsonStylesReaderStrategy(m_style_manager, styles);

    return options;
}

std::string& ConfigJsonReader::getError() {
    return m_error;
}

int ConfigJsonReader::getErrorLine() {
    return m_error_line;
}

ConfigJsonReader::ConfigJsonReader(Config *config, StyleManager *style_manager) {
    m_config = config;
    m_style_manager = style_manager;
}

bool ConfigJsonReader::readJsonFile(JsonElement **root, const char *file) {
    std::ifstream ifs(expandUserPath(file));

    if (!ifs.is_open()) {
        root = nullptr;
        return true;
    }

    std::string json(
        (std::istreambuf_iterator<char>(ifs)),
        (std::istreambuf_iterator<char>())
    );
    JsonParser jsonParser;
    if (!jsonParser.parse(json)) {
        m_error = jsonParser.getError();
        m_error_line = jsonParser.getLine();
        return false;
    }

    *root = jsonParser.getElement();
    return true;
}

bool ConfigJsonReader::read(const char *file) {
    JsonElement *root;
    if (!readJsonFile(&root, file)) {
        return false;
    }

    if (root == nullptr) {
        return true;
    }

    std::map<std::string, JsonReaderStrategy*> options = createOptions();

    JsonReader reader(options);
    if (!reader.read(root)) {
        m_error = reader.getError();
        m_error_line = reader.getErrorLine();
        return false;
    }

    return true;
}
