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

namespace ctrash
{
    /**
     * @brief Holds file metadata.
     *
     * @param {dev_t}       st_dev      ID of device containing file
     * @param {ino_t}       st_ino      inode number
     * @param {mode_t}      st_mode     protection
     * @param {nlink_t}     st_nlink    number of hard links
     * @param {uid_t}       st_uid      user ID of owner
     * @param {gid_t}       st_gid      group ID of owner
     * @param {dev_t}       st_rdev     device ID (if special file)
     * @param {off_t}       st_size     total size, in bytes
     * @param {blksize_t}   st_blksize  blocksize for file system I/O
     * @param {blkcnt_t}    st_blocks   number of 512B blocks allocated
     * @param {time_t}      st_atime    time of last access
     * @param {time_t}      st_mtime    time of last modification
     * @param {time_t}      st_ctime    time of last status change
     */
    using f_metadata = struct stat;

    /**
     * @brief Trash location class, with labelling.
     */
    class trash
    {
    private:
        /**
         * @brief Name of trash object.
         */
        std::string t_name;
        /**
         * @brief Description of trash object.
         */
        std::string t_description;

        /**
         * @brief Path to trash location.
         */
        std::filesystem::path t_location;

    public:
        // Basic Constructors

        /**
         * @brief Remove default constructor.
         */
        trash() = delete;

        /**
         * @brief Construct by name.
         * @param name Name of trash object.
         */
        explicit trash(std::string name);

        /**
         * @brief Construct by location. Name will be assigned to path.
         * @param location Path to trash location.
         */
        explicit trash(const std::filesystem::path &location);

        /**
         * @brief Initializer List Constructor
         * @param name Name of trash object
         * @param description Description of trash object
         * @param location Path to trash location
         */
        trash
        (
            std::string name,
            std::string description,
            std::filesystem::path location
        );

        // Copy/Move Constructors

        /**
         * @brief Copy constructor
         * @param other Trash object to copy
         */
        trash(const trash &other);

        /**
         * @brief Move constructor
         * @param other Trash object to move
         */
        trash(trash &&other) noexcept;

        // Destructor

        /**
         * @brief Destructor.
         */
        ~trash();

        // Getters/Setters

        /**
         * @brief Setter
         * @return t_name
         */
        auto name() -> std::string &;

        /**
         * @brief Setter
         * @return t_description
         */
        auto description() -> std::string &;

        /**
         * @brief Setter
         * @return t_location
         */
        auto location() -> std::filesystem::path &;

        /**
         * @brief Getter
         * @return t_name
         */
        [[nodiscard]] auto name() const -> std::string;

        /**
         * @brief Getter
         * @return t_name
         */
        [[nodiscard]] auto description() const -> std::string;

        /**
         * @brief Getter
         * @return t_name
         */
        [[nodiscard]] auto location() const -> std::filesystem::path;

        /**
         * @brief Getter
         * @return t_name
         */
        [[nodiscard]] auto
        iterator() const -> std::filesystem::directory_iterator;

        // Operators

        /**
         * @brief Copy operator
         * @param other Trash object to copy
         * @return *this
         */
        auto operator=(const trash &other) -> trash &;

        /**
         * @brief Move operator
         * @param other Trash object to move
         * @return *this
         */
        auto operator=(trash &&other) noexcept -> trash &;

        /**
         * @brief Equality operator
         * @param other Trash object to compare
         * @return bool - true if locations are equal.
         */
        auto operator==(const trash &other) const -> bool;

        /**
         * @brief Inequality operator
         * @param other Trash object to compare
         * @return bool - true if locations are inequal.
         */
        auto operator!=(const trash &other) const -> bool;

        friend auto operator<<
        (std::ostream &os, const trash &trash) -> std::ostream &;
    };
}
