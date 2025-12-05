/**
 * @file    trash_context.hpp
 * @brief   Contains ctrash namespace.
 *
 * Most stuff is in here, from trash_object typedef to
 * static functions that handle trashing,
 * to the trash_container object which holds trash
 * locations and relevant metadata.
 */
#pragma once

#include <vector>

#include "trash_item.hpp"

/**
 * @brief Main namespace for definition of libtrash contents.
 */
namespace trash
{
    /**
     * @brief Trash location
     *
     * This class is intended to label a trash location, but also provide a
     * context for item trashing manipulation, whether adding or removing from
     * said trash location object.
     */
    class trash_context
    {
    private:
        /**
         * @brief Name of the trash context
         */
        char *name;
        /**
         * @brief Description of the trash context
         */
        char *description;
        /**
         * @brief Path to the trash location
         *
         * NOTE: We are NOT using unique IDs, but instead we'll use unique
         * locations. The idea is to provide thread-safe access and use of a
         * single instance, and not to have multiple instances of the same
         * location at any point.
         */
        std::filesystem::path location;
        /**
         * @brief Number of items in this trash location
         */
        uint8_t size;
        /**
         * @brief Vector containing all trashed items contained in this trash
         * context
         */
        std::vector<trash_item> items;

    public:
        // Basic Constructors

        /**
         * @brief Default constructor
         */
        trash_context();

        /**
         * @brief Name Constructor.
         *
         * @param name Name of trash context
         */
        explicit trash_context(std::string name);

        /**
         * @brief Location Constructor
         *
         * Name will be assigned to the trash path.
         * @param location Path to trash location
         */
        explicit trash_context(const std::filesystem::path &location);

        /**
         * @brief Initializer List Constructor
         *
         * @param name Name of trash context
         * @param description Description of trash context
         * @param location Path to trash location
         */
        trash_context(
                const char *name,
                const char *description,
                std::filesystem::path location);

        // Copy/Move Constructors

        /**
         * @brief Copy constructor
         *
         * @param other Trash context to copy
         */
        trash_context(const trash_context &other);

        /**
         * @brief Move constructor
         *
         * @param other Trash context to move
         */
        trash_context(trash_context &&other) noexcept;

        // Destructor

        /**
         * @brief Destructor
         */
        ~trash_context();

        // Getters/Setters

        /**
         * @brief Setter
         *
         * @return name
         */
        auto _name() -> std::string &;

        /**
         * @brief Setter
         *
         * @return description
         */
        auto _description() -> std::string &;

        /**
         * @brief Setter
         *
         * When changing the path, remember to move all items to the new trash
         * location.
         * @return location
         */
        auto _location() -> std::filesystem::path &;

        /**
         * @brief Getter
         *
         * @return name
         */
        [[nodiscard]] auto _name() const -> std::string;

        /**
         * @brief Getter
         *
         * @return description
         */
        [[nodiscard]] auto _description() const -> std::string;

        /**
         * @brief Getter
         *
         * @return location
         */
        [[nodiscard]] auto _location() const -> std::filesystem::path;

        /**
         * @brief Getter
         *
         * @return iterator
         */
        [[nodiscard]] auto _iterator() const
                -> std::vector<trash_item>::const_iterator;

        // Operators

        /**
         * @brief Copy operator
         *
         * @param other Trash object to copy
         * @return *this
         */
        auto operator=(const trash_context &other) -> trash_context &;

        /**
         * @brief Move operator
         *
         * @param other Trash object to move
         * @return *this
         */
        auto operator=(trash_context &&other) noexcept -> trash_context &;

        /**
         * @brief Equality operator
         *
         * @param other Trash object to compare
         * @return bool - true if locations are equal
         */
        auto operator==(const trash_context &other) const -> bool;

        /**
         * @brief Inequality operator
         *
         * @param other Trash object to compare
         * @return bool - true if locations are inequal
         */
        auto operator!=(const trash_context &other) const -> bool;

        /**
         * @brief Send file to trash
         *
         * @param f_delete Path of file to trash
         * @return Path to file deleted.
         */
        auto operator+=(std::filesystem::path f_delete)
                -> std::filesystem::path &;

        /**
         * @brief Restore file from trash
         *
         * @param f_restore Path of file to restore
         * @return Path to file restored.
         */
        auto operator-=(std::filesystem::path f_restore)
                -> std::filesystem::path &;

        friend auto operator<<(std::ostream &os, const trash_context &t_context)
                -> std::ostream &;
    };
} // namespace ctrash
