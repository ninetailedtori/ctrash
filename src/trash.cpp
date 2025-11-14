#include "trash.hpp"

#include <utility>

ctrash::trash::trash(std::string name) : t_name(std::move(name)),
                                         t_description(),
                                         t_location() {}

ctrash::trash::trash
(const std::filesystem::path &location) : t_name(location.string()),
                                          t_description(),
                                          t_location(location) {}

ctrash::trash::trash
(
    std::string name,
    std::string description,
    std::filesystem::path location
) : t_name(std::move(name)),
    t_description(std::move(description)),
    t_location(std::move(location)) {}

// Copy/Move Constructors
ctrash::trash::trash(const trash &other) = default;

ctrash::trash::trash(trash &&other) noexcept = default;

// Destructor
ctrash::trash::~trash() = default;

// Getters/Setters
auto ctrash::trash::name() -> std::string & { return t_name; }

auto ctrash::trash::description() -> std::string & { return t_description; }

auto ctrash::trash::location() -> std::filesystem::path & { return t_location; }

auto ctrash::trash::name() const -> std::string { return t_name; }

auto ctrash::trash::description() const -> std::string { return t_description; }

auto ctrash::trash::location() const -> std::filesystem::path
{
    return t_location;
}

auto ctrash::trash::iterator() const -> std::filesystem::directory_iterator
{
    return std::filesystem::directory_iterator(t_location);
}

auto ctrash::trash::operator=(const trash &other) -> ctrash::trash & = default;

auto ctrash::trash::operator=
(trash &&other) noexcept -> ctrash::trash & = default;

auto ctrash::trash::operator==
(const trash &other) const -> bool { return t_location == other.t_location; }

auto ctrash::trash::operator!=
(const trash &other) const -> bool { return t_location != other.t_location; }

auto ctrash::operator<<(std::ostream &os, const trash &trash) -> std::ostream &
{
    return os << trash.t_name
           << "("
           << trash.t_description
           << "): \""
           << trash.t_location.c_str() << "\"";
}
