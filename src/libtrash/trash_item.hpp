#pragma once

#include <filesystem>
#include <iostream>

#include <sys/stat.h>

/**
 * @brief Main namespace for definition of libtrash contents.
 */
namespace trash
{
    /**
     * @brief Holds various types that items may be.
     */
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

    std::ostream &operator<<(std::ostream &s, const metadata_type &metadata);

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
        trash_item(const trash_item &other);

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

        /**
         * @brief Getter
         *
         * @return id
         */
        [[nodiscard]] auto _id() const -> const char *;
        /**
         * @brief Getter
         *
         * @return name
         */
        [[nodiscard]] auto _name() const -> const char *;
        /**
         * @brief Getter
         *
         * @return parent
         */
        [[nodiscard]] auto _parent() const -> std::filesystem::path;
    };
} // namespace trash
