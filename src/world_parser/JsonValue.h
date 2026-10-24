//
// Created by tobi on 19.10.26.
//

#ifndef RAYTRACER_JSONVALUE_H
#define RAYTRACER_JSONVALUE_H
#include <memory>
#include <unordered_map>
#include <variant>
#include <vector>
#include <string>


class JsonValue {

public:

    using Array = std::vector<JsonValue>;
    using Object = std::unordered_map<std::string, JsonValue>;

    using ValueType = std::variant<
        std::nullptr_t,
        bool,
        float,
        std::string,
        std::shared_ptr<Array>,
        std::shared_ptr<Object>
    >;

    JsonValue() : _data(nullptr) {}
    explicit JsonValue(std::nullptr_t) : _data(nullptr) {}
    explicit JsonValue(bool value) : _data(value) {}
    explicit JsonValue(float value) : _data(value) {}
    explicit JsonValue(const int value) : _data(static_cast<float>(value)) {}
    explicit JsonValue(const std::string& value) : _data(value) {}
    explicit JsonValue(const char* value) : _data(std::string(value)) {}

    static JsonValue createObject() {
        JsonValue val;
        val._data = std::make_shared<Object>();
        return val;
    }

    static JsonValue createArray() {
        JsonValue val;
        val._data = std::make_shared<Array>();
        return val;
    }

    void set(const std::string& key, const JsonValue& value) const {
        if (const auto* obj = std::get_if<std::shared_ptr<Object>>(&_data)) {
            (**obj)[key] = value;
        } else {
            throw std::runtime_error("JsonValue is not a object!");
        }
    }

    void push_back(const JsonValue& value) const {
        if (const auto* arr = std::get_if<std::shared_ptr<Array>>(&_data)) {
            (*arr)->push_back(value);
        } else {
            throw std::runtime_error("JsonValue is not an array");
        }
    }

    JsonValue& operator[](const std::string& key) const {
        if (const auto* obj = std::get_if<std::shared_ptr<Object>>(&_data)) {
            return (**obj)[key];
        }
        throw std::runtime_error("JsonValue is not a object!");
    }


    JsonValue& operator[](const size_t index) const {
        if (const auto* arr = std::get_if<std::shared_ptr<Array>>(&_data)) {
            return (*arr)->at(index);
        }
        throw std::runtime_error("JsonValue is not an array");
    }

    [[nodiscard]] bool contains(const std::string& key) const {
        if (const auto* obj = std::get_if<std::shared_ptr<Object>>(&_data)) {
            return (*obj)->contains(key);
        }

        return false;
    }

    [[nodiscard]] const JsonValue& at(const std::string& key) const {
        if (const auto* obj = std::get_if<std::shared_ptr<Object>>(&_data)) {
            return (**obj).at(key);
        }

        throw std::runtime_error("JsonValue is not an object!");
    }

    [[nodiscard]] std::size_t size() const {
        if (const auto* obj = std::get_if<std::shared_ptr<Array>>(&_data)) {
            return (*obj)->size();
        }

        throw std::runtime_error("JsonValue is not an Array!");
    }


    [[nodiscard]] bool isString() const { return std::holds_alternative<std::string>(_data); }
    [[nodiscard]] bool isNumber() const { return std::holds_alternative<float>(_data); }
    [[nodiscard]] bool isObject() const { return std::holds_alternative<std::shared_ptr<Object>>(_data); }
    [[nodiscard]] bool isArray() const { return std::holds_alternative<std::shared_ptr<Array>>(_data); }
    [[nodiscard]] bool isBool() const { return std::holds_alternative<bool>(_data); }

    [[nodiscard]] const std::string& asString() const { return std::get<std::string>(_data); }
    [[nodiscard]] float asNumber() const { return std::get<float>(_data); }
    [[nodiscard]] bool asBool() const { return std::get<bool>(_data); }

private:
    ValueType _data;

};


#endif //RAYTRACER_JSONVALUE_H
