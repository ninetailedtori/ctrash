/**
 * @file    trash.hpp
 * @brief   Contains ctrash namespace.
 *
 * Most stuff is in here, from trash_object typedef to
 * static functions that handle trashing,
 * to the trash_container object which holds trash
 * locations and relevant metadata.
 */
#pragma once

#include <filesystem>
#include <sys/stat.h>
#include <vector>

namespace ctrash
{
    /**
     * @brief This contains all IDs of any trash_contexts that exist at any one
     * time.
     *
     * Used internally to validate that no two trash_contexts share the same ID.
     */
    static std::vector<std::uint8_t> all_contexts{};

    enum item_type
    {
        dir,
        file,
        symlink
    };

#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
    using metadata_type = struct _stat;
#elif defined __APPLE__ || __MACH__ || __FreeBSD__ || __linux__ || unix ||     \
        defined __unix || defined __unix__
    using metadata_type = struct stat;
#endif

    /**
     * @brief This class is for trashed items, and holds all required metadata
     * for lookup and manipulation.
     */
    class trash_item
    {
    private:
        /**
         * @brief System-specific ID for the trashed item.
         */
        const char *id;
        /**
         * @brief Name of the trashed item.
         */
        const char *name;
        /**
         * @brief Original parent of the trashed item.
         */
        const std::filesystem::path parent;
        /**
         * @brief Holds the trashed item's metadata.
         */
        item_type type = std::filesystem::is_directory(parent) ? dir
                         : std::filesystem::is_symlink(parent) ? symlink
                                                               : file;
        metadata_type metadata;
        /**
         * @brief Time the trashed item has been deleted.
         */
        std::uint64_t ti_deleted{};

    public:
        // Basic Constructors

        trash_item() = delete;

        /**
         * @brief Location Constructor
         *
         * @param location Original location of trashed item.
         */
        explicit trash_item(std::filesystem::path location);

        // Copy/Move Constructors

        /**
         * @brief Copy constructor
         *
         * @param other Trashed item to copy
         */
        trash_item(const trash_item &other) = delete;

        /**
         * @brief Move constructor
         *
         * @param other Trashed item to move
         */
        trash_item(trash_item &&other) noexcept;

        // Destructor

        /**
         * @brief Destructor
         */
        ~trash_item();

        // Getters/Setters

        // None of these should be accessed by reference and thus changed.
        [[nodiscard]] auto _id() const -> const char *;
        [[nodiscard]] auto _name() const -> const char *;
        [[nodiscard]] auto _parent() const -> std::filesystem::path;
    };

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
         * @brief Unique ID for trash location object.
         */
        uint8_t id;
        /**
         * @brief Name of the trash location
         */
        char *name;
        /**
         * @brief Description of the trash location
         */
        char *description;
        /**
         * @brief Path to the trash location
         */
        std::filesystem::path location;
        /**
         * @brief Number of items in this trash location.
         */
        uint8_t count;
        /**
         * @brief Vector containing all trashed items contained in this trash
         * location.
         */
        std::vector<trash_item> items;

    public:
        // Basic Constructors

        /**
         * @brief Default constructor
         */
        trash_context() = default;

        /**
         * @brief Name Constructor.
         *
         * @param name Name of trash object
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
         * @param name Name of trash object
         * @param description Description of trash object
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
         * @param other Trash object to copy
         */
        trash_context(const trash_context &other);

        /**
         * @brief Move constructor
         *
         * @param other Trash object to move
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
         * @return t_name
         */
        auto _name() -> std::string &;

        /**
         * @brief Setter
         *
         * @return t_description
         */
        auto _description() -> std::string &;

        /**
         * @brief Setter
         *
         * When changing the path, remember to move all items to the new trash
         * location.
         * @return t_location
         */
        auto _location() -> std::filesystem::path &;

        /**
         * @brief Getter
         *
         * @return t_name
         */
        [[nodiscard]] auto _name() const -> std::string;

        /**
         * @brief Getter
         *
         * @return t_name
         */
        [[nodiscard]] auto _description() const -> std::string;

        /**
         * @brief Getter
         *
         * @return t_name
         */
        [[nodiscard]] auto _location() const -> std::filesystem::path;

        /**
         * @brief Getter
         *
         * @return t_name
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
